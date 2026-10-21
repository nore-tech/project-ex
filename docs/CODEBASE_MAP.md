# Codebase map

Module `ProjectEX`. New gameplay classes belong under `Source/ProjectEX/` in the folder that matches the system. Do not modify `Variant_Shooter` or `Variant_Horror` for Project EX features.

Authority: the server mutates inventory, equipment, container contents, health, and hits. Clients send request RPCs. Owner-only inventory replication. Do not apply item movement only on the client.

## Player

- `AProjectEXCharacter` — `Source/ProjectEX/ProjectEXCharacter.h`
  Abstract, Blueprintable. Components: interaction, inventory, loot, health, weapon.
  Movement defaults: `FallingBrakingDeceleration`, `AirControl`.
- `AProjectEXGameMode` — `Source/ProjectEX/ProjectEXGameMode.h`

## Interaction

- `UProjectEXInteractionComponent` — `Source/ProjectEX/Interaction/ProjectEXInteractionComponent.h`
  `InteractionRange`, `RequestInteract`, `ServerRequestInteract`.
- `IProjectEXInteractable` — `Source/ProjectEX/Interaction/ProjectEXInteractable.h`
- `AProjectEXPickup` — `Source/ProjectEX/Interaction/ProjectEXPickup.h`
  `ItemDefinition`, `Quantity`, `StoredMagazine`, `SetItemStack`. Event: `OnItemPickedUp`.
- `AProjectEXLootContainer` — `Source/ProjectEX/Interaction/ProjectEXLootContainer.h`
  `ContainerName`, `GridColumns`, `GridRows`, `Mesh`, `AddItem`, `TryTakeEntry`, `TryTakeEntryAt`, `TryDeposit`, `TryDepositAt`, `TryDepositEquippedAt`, `TryMoveEntry`, `TryEquipEntry`, `CanPlaceItem`.
  Events: `OnContainerOpened`, `OnContentsChanged`. No loot table.
- `UProjectEXLootComponent` — `Source/ProjectEX/Interaction/ProjectEXLootComponent.h`
  `OpenLoot`, `CloseLoot`, `RequestClose`, `RequestTake`, `RequestTakeAt`, `RequestDeposit`, `RequestDepositAt`, `RequestDepositEquippedAt`, `RequestMoveContainerItem`, `RequestEquipContainerItem`.

## Inventory and equipment

- `UProjectEXItemDefinition` — `Source/ProjectEX/Inventory/ProjectEXItemDefinition.h`
  `DisplayName`, `WorldMesh`, `DisplaySkeletalMesh`, `EquipKind`, `HealAmount`, `MaxStackSize`, `GridWidth`, `GridHeight`.
- `EProjectEXEquipmentSlot` — `PrimaryWeapon`, `SecondaryWeapon`, `Helmet`, `BodyArmor`, `Backpack`.
- `EProjectEXEquipKind` — `None`, `Weapon`, `Helmet`, `BodyArmor`, `Backpack`.
- `UProjectEXInventoryComponent` — `Source/ProjectEX/Inventory/ProjectEXInventoryComponent.h`
  `AddItem`, `ConsumeItem`, `RemoveItem`, `RequestMoveItem`, `RequestDrop`, `RequestDropStack`, `RequestEquip`, `RequestAutoEquip`, `RequestUnequip`, `RequestUnequipAt`, `RequestMoveEquipped`, `RequestUseItem`, `CanPlaceEntry`, `CanAcceptItem`, `GetEquippedItem`, `SlotAcceptsItem`.
  `GridColumns` default 10, `GridRows` default 6.
- `UProjectEXInventoryWidget` — `Source/ProjectEX/Inventory/ProjectEXInventoryWidget.h`
  Native inventory UI. Drag origin: pockets, container, equipment.

## Weapons

- `UProjectEXWeaponData` — `Source/ProjectEX/Combat/ProjectEXWeaponData.h`
  `Damage`, `FireInterval`, `MagazineSize`, `ReloadDuration`, `AmmoType`, `ViewMesh`, `ViewOffset`, `ViewRotation`, `RecoilPitch`, `RecoilYaw`.
- `UProjectEXWeaponItemDefinition` — `Source/ProjectEX/Combat/ProjectEXWeaponItemDefinition.h`
  `WeaponData`.
- `UProjectEXWeaponComponent` — `Source/ProjectEX/Combat/ProjectEXWeaponComponent.h`
  Server fire and reload. Events: `OnWeaponFired`, `OnWeaponReloaded`.
- `UProjectEXWeaponViewComponent` — `Source/ProjectEX/Combat/ProjectEXWeaponViewComponent.h`
  Local-only pose, attached to the first-person camera. Not Blueprintable.
- `AProjectEXWeaponRig` — `Source/ProjectEX/Combat/ProjectEXWeaponRig.h`
  Unspawned Blueprint (`BP_EX_Rifle`). `HipFireAnchor` and `ADSAnchor` place the equipped rifle. Set on `UProjectEXWeaponData.PresentationRig`.

## Health

- `UProjectEXHealthComponent` — `Source/ProjectEX/Combat/ProjectEXHealthComponent.h`
  `MaxHealth`, `HeadshotMultiplier`, `ApplyDamage`, `Heal`, `RestoreFullHealth`.
  Delegates: `OnHealthChanged`, `OnDamageApplied`, `OnDied`.
- `AProjectEXTargetDummy` — `Source/ProjectEX/Combat/ProjectEXTargetDummy.h`
  Interact calls `RestoreFullHealth`.
- `AProjectEXDamagePad` — `Source/ProjectEX/Combat/ProjectEXDamagePad.h`

## Enemies and raid

- `AProjectEXEnemy`, `AProjectEXEnemyController` — `Source/ProjectEX/Combat/`
  Combat settings, `PatrolPoints`, perception sight, navmesh chase, melee with line of sight. Blueprint: `BP_Enemy`.
- `EProjectEXRaidStatus` and raid state — `AProjectEXPlayerController` (`Source/ProjectEX/ProjectEXPlayerController.h`)
  `GetRaidStatus`, `IsInRaid`, `SetExtractionProgress`, `CompleteExtraction`, `AddRaidKill`, `RequestDeployAgain`. Event: `OnRaidStatusChanged`.
- `AProjectEXExtractionZone` — `Source/ProjectEX/Raid/ProjectEXExtractionZone.h`
  `DisplayName`, `Radius`, `Countdown`, `ZoneColor`. Event: `OnPlayerExtracted`. Blueprint: `BP_ExtractionZone`.
- `UProjectEXRaidWidget` — `Source/ProjectEX/Raid/ProjectEXRaidWidget.h`
  Banner, countdown, damage flash, result panel. Set by `RaidWidgetClass` on the player controller.

## Blueprint base classes

`UProjectEXWeaponData`, `UProjectEXWeaponItemDefinition`, `UProjectEXItemDefinition`, `AProjectEXPickup`, `AProjectEXLootContainer`, `AProjectEXTargetDummy`, `AProjectEXCharacter`, `UProjectEXWeaponComponent`.

Setup steps: `docs/BLUEPRINT_SETUP.md`.
