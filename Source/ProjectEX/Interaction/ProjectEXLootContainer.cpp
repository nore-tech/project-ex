// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXLootContainer.h"
#include "ProjectEX.h"
#include "ProjectEXInventoryComponent.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXLootComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

AProjectEXLootContainer::AProjectEXLootContainer()
{
	bReplicates = true;
	ContainerName = NSLOCTEXT("ProjectEX", "DefaultContainerName", "Container");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ChestFinder(TEXT("/Game/PolygonPrototype/Meshes/Props/SM_Prop_Chest_Wood_01.SM_Prop_Chest_Wood_01"));
	if (ChestFinder.Succeeded())
	{
		Mesh->SetStaticMesh(ChestFinder.Object);
	}
}

void AProjectEXLootContainer::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		return;
	}

	if (Contents.Num() == 0)
	{
		UProjectEXItemDefinition* Bandage = LoadObject<UProjectEXItemDefinition>(nullptr, TEXT("/Game/FirstPerson/DA_Bandage.DA_Bandage"));
		UProjectEXItemDefinition* Scrap = LoadObject<UProjectEXItemDefinition>(nullptr, TEXT("/Game/FirstPerson/DA_Scrap.DA_Scrap"));
		UProjectEXItemDefinition* Bottle = LoadObject<UProjectEXItemDefinition>(nullptr, TEXT("/Game/FirstPerson/DA_WaterBottle.DA_WaterBottle"));
		UProjectEXItemDefinition* Medkit = LoadObject<UProjectEXItemDefinition>(nullptr, TEXT("/Game/FirstPerson/DA_MedicalKit.DA_MedicalKit"));

		const int32 Roll = FMath::RandRange(0, 2);
		if (Roll == 0)
		{
			AddItem(Bandage, FMath::RandRange(1, 3));
			AddItem(Scrap, 1);
		}
		else if (Roll == 1)
		{
			AddItem(Bottle, 1);
			AddItem(Bandage, 2);
		}
		else
		{
			AddItem(Medkit, 1);
			AddItem(Scrap, 1);
		}
	}

	NotifyContentsChanged();
}

void AProjectEXLootContainer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectEXLootContainer, Contents);
	DOREPLIFETIME(AProjectEXLootContainer, GridColumns);
	DOREPLIFETIME(AProjectEXLootContainer, GridRows);
	DOREPLIFETIME(AProjectEXLootContainer, ContainerName);
}

FText AProjectEXLootContainer::GetInteractionPrompt_Implementation() const
{
	return NSLOCTEXT("ProjectEX", "SearchContainer", "Search");
}

bool AProjectEXLootContainer::CanInteract_Implementation(APawn* Interactor) const
{
	return Interactor != nullptr;
}

void AProjectEXLootContainer::Interact_Implementation(APawn* Interactor)
{
	if (!HasAuthority() || !CanInteract_Implementation(Interactor))
	{
		return;
	}

	if (UProjectEXLootComponent* Loot = Interactor->FindComponentByClass<UProjectEXLootComponent>())
	{
		Loot->OpenLoot(this);
		OnContainerOpened(Interactor);
	}
}

int32 AProjectEXLootContainer::AddItem(UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds)
{
	if (!Definition || Quantity <= 0 || (HasActorBegunPlay() && !HasAuthority()))
	{
		return 0;
	}

	const int32 Columns = GetGridColumns();
	const int32 Rows = GetGridRows();
	const int32 MaxStack = FMath::Max(1, Definition->MaxStackSize);
	int32 Remaining = Quantity;

	struct FStackPlan
	{
		int32 EntryId = INDEX_NONE;
		int32 Amount = 0;
	};

	TArray<FStackPlan> StackPlans;
	for (const FProjectEXInventoryEntry& Entry : Contents)
	{
		if (Remaining <= 0)
		{
			break;
		}

		if (Entry.Definition != Definition || Entry.Quantity >= MaxStack || Entry.MagazineRounds != MagazineRounds)
		{
			continue;
		}

		const int32 Amount = FMath::Min(MaxStack - Entry.Quantity, Remaining);
		FStackPlan& Plan = StackPlans.AddDefaulted_GetRef();
		Plan.EntryId = Entry.EntryId;
		Plan.Amount = Amount;
		Remaining -= Amount;
	}

	TArray<uint8> Occupied;
	Occupied.SetNumZeroed(Columns * Rows);
	for (const FProjectEXInventoryEntry& Entry : Contents)
	{
		if (!Entry.Definition || Entry.Quantity <= 0)
		{
			continue;
		}

		const FIntPoint Size = Entry.Definition->GetGridSize(Entry.bRotated);
		for (int32 OffsetY = 0; OffsetY < Size.Y; ++OffsetY)
		{
			for (int32 OffsetX = 0; OffsetX < Size.X; ++OffsetX)
			{
				const int32 CellX = Entry.GridX + OffsetX;
				const int32 CellY = Entry.GridY + OffsetY;
				if (CellX >= 0 && CellY >= 0 && CellX < Columns && CellY < Rows)
				{
					Occupied[CellY * Columns + CellX] = 1;
				}
			}
		}
	}

	struct FNewPlan
	{
		int32 X = 0;
		int32 Y = 0;
		bool bRotated = false;
		int32 Chunk = 0;
	};

	TArray<FNewPlan> NewPlans;
	while (Remaining > 0)
	{
		const FIntPoint Normal = Definition->GetGridSize(false);
		const FIntPoint Rotated = Definition->GetGridSize(true);
		int32 X = 0;
		int32 Y = 0;
		int32 Width = Normal.X;
		int32 Height = Normal.Y;
		bool bRotated = false;
		bool bFound = false;

		auto Fits = [&Occupied, Columns, Rows](int32 OriginX, int32 OriginY, int32 RectWidth, int32 RectHeight)
		{
			if (OriginX < 0 || OriginY < 0 || RectWidth <= 0 || RectHeight <= 0 || OriginX + RectWidth > Columns || OriginY + RectHeight > Rows)
			{
				return false;
			}

			for (int32 OffsetY = 0; OffsetY < RectHeight; ++OffsetY)
			{
				for (int32 OffsetX = 0; OffsetX < RectWidth; ++OffsetX)
				{
					if (Occupied[(OriginY + OffsetY) * Columns + (OriginX + OffsetX)] != 0)
					{
						return false;
					}
				}
			}

			return true;
		};

		for (int32 CellY = 0; CellY <= Rows - Normal.Y && !bFound; ++CellY)
		{
			for (int32 CellX = 0; CellX <= Columns - Normal.X; ++CellX)
			{
				if (Fits(CellX, CellY, Normal.X, Normal.Y))
				{
					X = CellX;
					Y = CellY;
					bFound = true;
					break;
				}
			}
		}

		if (!bFound && Normal.X != Normal.Y)
		{
			Width = Rotated.X;
			Height = Rotated.Y;
			bRotated = true;
			for (int32 CellY = 0; CellY <= Rows - Rotated.Y && !bFound; ++CellY)
			{
				for (int32 CellX = 0; CellX <= Columns - Rotated.X; ++CellX)
				{
					if (Fits(CellX, CellY, Rotated.X, Rotated.Y))
					{
						X = CellX;
						Y = CellY;
						bFound = true;
						break;
					}
				}
			}
		}

		if (!bFound)
		{
			return 0;
		}

		FNewPlan& Plan = NewPlans.AddDefaulted_GetRef();
		Plan.X = X;
		Plan.Y = Y;
		Plan.bRotated = bRotated;
		Plan.Chunk = FMath::Min(MaxStack, Remaining);
		Remaining -= Plan.Chunk;

		for (int32 OffsetY = 0; OffsetY < Height; ++OffsetY)
		{
			for (int32 OffsetX = 0; OffsetX < Width; ++OffsetX)
			{
				Occupied[(Y + OffsetY) * Columns + (X + OffsetX)] = 1;
			}
		}
	}

	for (const FNewPlan& Plan : NewPlans)
	{
		FProjectEXInventoryEntry& NewEntry = Contents.AddDefaulted_GetRef();
		NewEntry.EntryId = NextEntryId++;
		NewEntry.Definition = Definition;
		NewEntry.Quantity = Plan.Chunk;
		NewEntry.GridX = Plan.X;
		NewEntry.GridY = Plan.Y;
		NewEntry.bRotated = Plan.bRotated;
		NewEntry.MagazineRounds = MagazineRounds;
	}

	for (const FStackPlan& Plan : StackPlans)
	{
		for (FProjectEXInventoryEntry& Entry : Contents)
		{
			if (Entry.EntryId == Plan.EntryId)
			{
				Entry.Quantity += Plan.Amount;
				break;
			}
		}
	}

	if (HasActorBegunPlay())
	{
		NotifyContentsChanged();
	}

	return Quantity;
}

bool AProjectEXLootContainer::TryTakeEntry(APawn* Pawn, int32 EntryId)
{
	if (!HasAuthority() || !Pawn || !CanInteract_Implementation(Pawn))
	{
		return false;
	}

	if (FVector::DistSquared(Pawn->GetActorLocation(), GetActorLocation()) > FMath::Square(400.0f))
	{
		return false;
	}

	int32 Index = INDEX_NONE;
	for (int32 EntryIndex = 0; EntryIndex < Contents.Num(); ++EntryIndex)
	{
		if (Contents[EntryIndex].EntryId == EntryId)
		{
			Index = EntryIndex;
			break;
		}
	}

	if (Index == INDEX_NONE)
	{
		return false;
	}

	UProjectEXInventoryComponent* Inventory = Pawn->FindComponentByClass<UProjectEXInventoryComponent>();
	const FProjectEXInventoryEntry Entry = Contents[Index];
	if (!Inventory || !Entry.Definition || Entry.Quantity <= 0)
	{
		return false;
	}

	const int32 Added = Inventory->AddItem(Entry.Definition, Entry.Quantity, Entry.MagazineRounds);
	if (Added != Entry.Quantity)
	{
		return false;
	}

	Contents.RemoveAt(Index);
	NotifyContentsChanged();
	return true;
}

FText AProjectEXLootContainer::GetContainerName() const
{
	return ContainerName.IsEmpty() ? NSLOCTEXT("ProjectEX", "DefaultContainerName", "Container") : ContainerName;
}

bool AProjectEXLootContainer::IsPawnInRange(const APawn* Pawn) const
{
	return Pawn && FVector::DistSquared(Pawn->GetActorLocation(), GetActorLocation()) <= FMath::Square(400.0f);
}

bool AProjectEXLootContainer::ExtractEntry(int32 EntryId, FProjectEXInventoryEntry& OutEntry)
{
	for (int32 Index = 0; Index < Contents.Num(); ++Index)
	{
		if (Contents[Index].EntryId != EntryId)
		{
			continue;
		}

		OutEntry = Contents[Index];
		Contents.RemoveAt(Index);
		return true;
	}

	return false;
}

bool AProjectEXLootContainer::CanPlaceItem(const UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds, int32 GridX, int32 GridY, bool bRotated, int32 IgnoreEntryId) const
{
	if (!Definition || Quantity <= 0)
	{
		return false;
	}

	const FIntPoint Size = Definition->GetGridSize(bRotated);
	if (GridX < 0 || GridY < 0 || GridX + Size.X > GetGridColumns() || GridY + Size.Y > GetGridRows())
	{
		return false;
	}

	const FProjectEXInventoryEntry* MergeTarget = nullptr;
	for (const FProjectEXInventoryEntry& Other : Contents)
	{
		if (Other.EntryId == IgnoreEntryId || !Other.Definition || Other.Quantity <= 0)
		{
			continue;
		}

		const FIntPoint OtherSize = Other.Definition->GetGridSize(Other.bRotated);
		const bool bOverlaps = GridX < Other.GridX + OtherSize.X
			&& GridX + Size.X > Other.GridX
			&& GridY < Other.GridY + OtherSize.Y
			&& GridY + Size.Y > Other.GridY;
		if (!bOverlaps)
		{
			continue;
		}

		const int32 MaxStack = FMath::Max(1, Other.Definition->MaxStackSize);
		const bool bSameStack = Other.Definition == Definition && Other.MagazineRounds == MagazineRounds;
		if (MergeTarget || !bSameStack || Other.Quantity + Quantity > MaxStack)
		{
			return false;
		}

		MergeTarget = &Other;
	}

	return true;
}

bool AProjectEXLootContainer::InsertEntryAt(const FProjectEXInventoryEntry& Entry, int32 GridX, int32 GridY, bool bRotated)
{
	if (!Entry.Definition || !CanPlaceItem(Entry.Definition, Entry.Quantity, Entry.MagazineRounds, GridX, GridY, bRotated))
	{
		return false;
	}

	const FIntPoint Size = Entry.Definition->GetGridSize(bRotated);
	for (FProjectEXInventoryEntry& Other : Contents)
	{
		if (!Other.Definition || Other.Quantity <= 0)
		{
			continue;
		}

		const FIntPoint OtherSize = Other.Definition->GetGridSize(Other.bRotated);
		const bool bOverlaps = GridX < Other.GridX + OtherSize.X
			&& GridX + Size.X > Other.GridX
			&& GridY < Other.GridY + OtherSize.Y
			&& GridY + Size.Y > Other.GridY;
		if (!bOverlaps)
		{
			continue;
		}

		Other.Quantity += Entry.Quantity;
		NotifyContentsChanged();
		return true;
	}

	FProjectEXInventoryEntry& NewEntry = Contents.AddDefaulted_GetRef();
	NewEntry = Entry;
	NewEntry.EntryId = NextEntryId++;
	NewEntry.GridX = GridX;
	NewEntry.GridY = GridY;
	NewEntry.bRotated = bRotated;
	NotifyContentsChanged();
	return true;
}

bool AProjectEXLootContainer::TryTakeEntryAt(APawn* Pawn, int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (!HasAuthority() || !IsPawnInRange(Pawn))
	{
		return false;
	}

	UProjectEXInventoryComponent* Inventory = Pawn->FindComponentByClass<UProjectEXInventoryComponent>();
	const FProjectEXInventoryEntry* Source = nullptr;
	for (const FProjectEXInventoryEntry& Entry : Contents)
	{
		if (Entry.EntryId == EntryId)
		{
			Source = &Entry;
			break;
		}
	}

	if (!Inventory || !Source || !Source->Definition || !Inventory->CanAcceptItem(Source->Definition, Source->Quantity, Source->MagazineRounds, GridX, GridY, bRotated))
	{
		return false;
	}

	FProjectEXInventoryEntry Taken;
	if (!ExtractEntry(EntryId, Taken))
	{
		return false;
	}

	if (!Inventory->InsertItemAt(Taken.Definition, Taken.Quantity, Taken.MagazineRounds, GridX, GridY, bRotated))
	{
		Contents.Add(Taken);
		NotifyContentsChanged();
		return false;
	}

	NotifyContentsChanged();
	return true;
}

bool AProjectEXLootContainer::TryDeposit(APawn* Pawn, int32 PlayerEntryId)
{
	if (!HasAuthority() || !IsPawnInRange(Pawn))
	{
		return false;
	}

	UProjectEXInventoryComponent* Inventory = Pawn->FindComponentByClass<UProjectEXInventoryComponent>();
	if (!Inventory)
	{
		return false;
	}

	const TArray<FProjectEXInventoryEntry> Entries = Inventory->GetEntries();
	const FProjectEXInventoryEntry* Source = nullptr;
	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		if (Entry.EntryId == PlayerEntryId)
		{
			Source = &Entry;
			break;
		}
	}

	if (!Source || !Source->Definition || Source->Quantity <= 0)
	{
		return false;
	}

	const int32 Added = AddItem(Source->Definition, Source->Quantity, Source->MagazineRounds);
	if (Added != Source->Quantity)
	{
		return false;
	}

	if (Inventory->RemoveItem(PlayerEntryId, Source->Quantity) != Source->Quantity)
	{
		return false;
	}

	return true;
}

bool AProjectEXLootContainer::TryDepositAt(APawn* Pawn, int32 PlayerEntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (!HasAuthority() || !IsPawnInRange(Pawn))
	{
		return false;
	}

	UProjectEXInventoryComponent* Inventory = Pawn->FindComponentByClass<UProjectEXInventoryComponent>();
	if (!Inventory)
	{
		return false;
	}

	const TArray<FProjectEXInventoryEntry> Entries = Inventory->GetEntries();
	const FProjectEXInventoryEntry* Source = nullptr;
	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		if (Entry.EntryId == PlayerEntryId)
		{
			Source = &Entry;
			break;
		}
	}

	if (!Source || !Source->Definition || !CanPlaceItem(Source->Definition, Source->Quantity, Source->MagazineRounds, GridX, GridY, bRotated))
	{
		return false;
	}

	FProjectEXInventoryEntry Taken = *Source;
	if (Inventory->RemoveItem(PlayerEntryId, Taken.Quantity) != Taken.Quantity)
	{
		return false;
	}

	if (!InsertEntryAt(Taken, GridX, GridY, bRotated))
	{
		Inventory->AddItem(Taken.Definition, Taken.Quantity, Taken.MagazineRounds);
		return false;
	}

	return true;
}

bool AProjectEXLootContainer::TryDepositEquippedAt(APawn* Pawn, EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated)
{
	if (!HasAuthority() || !IsPawnInRange(Pawn))
	{
		return false;
	}

	UProjectEXInventoryComponent* Inventory = Pawn->FindComponentByClass<UProjectEXInventoryComponent>();
	FProjectEXEquippedItem Equipped;
	if (!Inventory || !Inventory->GetEquippedItem(Slot, Equipped) || !Equipped.IsOccupied() || !CanPlaceItem(Equipped.Definition, Equipped.Quantity, Equipped.MagazineRounds, GridX, GridY, bRotated))
	{
		return false;
	}

	FProjectEXEquippedItem Taken;
	if (!Inventory->TakeEquippedItem(Slot, Taken))
	{
		return false;
	}

	FProjectEXInventoryEntry Entry;
	Entry.Definition = Taken.Definition;
	Entry.Quantity = Taken.Quantity;
	Entry.MagazineRounds = Taken.MagazineRounds;
	if (!InsertEntryAt(Entry, GridX, GridY, bRotated))
	{
		Inventory->ReceiveEquippedItem(Slot, Taken.Definition, Taken.Quantity, Taken.MagazineRounds);
		return false;
	}

	return true;
}

bool AProjectEXLootContainer::TryMoveEntry(int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (!HasAuthority())
	{
		return false;
	}

	const FProjectEXInventoryEntry* Source = nullptr;
	for (const FProjectEXInventoryEntry& Entry : Contents)
	{
		if (Entry.EntryId == EntryId)
		{
			Source = &Entry;
			break;
		}
	}

	if (!Source || !Source->Definition || !CanPlaceItem(Source->Definition, Source->Quantity, Source->MagazineRounds, GridX, GridY, bRotated, EntryId))
	{
		return false;
	}

	if (Source->GridX == GridX && Source->GridY == GridY && Source->bRotated == bRotated)
	{
		return true;
	}

	FProjectEXInventoryEntry Taken;
	if (!ExtractEntry(EntryId, Taken))
	{
		return false;
	}

	if (!InsertEntryAt(Taken, GridX, GridY, bRotated))
	{
		Contents.Add(Taken);
		NotifyContentsChanged();
		return false;
	}

	return true;
}

bool AProjectEXLootContainer::TryEquipEntry(APawn* Pawn, int32 EntryId, EProjectEXEquipmentSlot Slot)
{
	if (!HasAuthority() || !IsPawnInRange(Pawn))
	{
		return false;
	}

	UProjectEXInventoryComponent* Inventory = Pawn->FindComponentByClass<UProjectEXInventoryComponent>();
	const FProjectEXInventoryEntry* Source = nullptr;
	for (const FProjectEXInventoryEntry& Entry : Contents)
	{
		if (Entry.EntryId == EntryId)
		{
			Source = &Entry;
			break;
		}
	}

	if (!Inventory || !Source || !Source->Definition)
	{
		return false;
	}

	FProjectEXEquippedItem Existing;
	if (!Inventory->GetEquippedItem(Slot, Existing) || Existing.IsOccupied())
	{
		return false;
	}

	FProjectEXInventoryEntry Taken;
	if (!ExtractEntry(EntryId, Taken))
	{
		return false;
	}

	if (!Inventory->ReceiveEquippedItem(Slot, Taken.Definition, Taken.Quantity, Taken.MagazineRounds))
	{
		Contents.Add(Taken);
		NotifyContentsChanged();
		return false;
	}

	NotifyContentsChanged();
	return true;
}

void AProjectEXLootContainer::OnRep_Contents()
{
	OnContentsChanged.Broadcast();
}

void AProjectEXLootContainer::NotifyContentsChanged()
{
	OnContentsChanged.Broadcast();
	ForceNetUpdate();
}
