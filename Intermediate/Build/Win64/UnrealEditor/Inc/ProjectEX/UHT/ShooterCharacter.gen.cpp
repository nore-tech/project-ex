// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShooterCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeShooterCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UPawnNoiseEmitterComponent(ETypeConstructPhase);
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_BulletCountUpdatedDelegate__DelegateSignature(ETypeConstructPhase);
PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_DamagedDelegate__DelegateSignature(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AProjectEXCharacter(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterCharacter(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterCharacter(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_IShooterWeaponHolder(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FBulletCountUpdatedDelegate *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_ProjectEX_BulletCountUpdatedDelegate__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_ProjectEX_eventBulletCountUpdatedDelegate_Parms
	{
		int32 MagazineSize;
		int32 Bullets;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FBulletCountUpdatedDelegate constinit property declarations ***********
	static const UECodeGen_Private::FIntPropertyParams NewProp_MagazineSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Bullets;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FBulletCountUpdatedDelegate constinit property declarations *************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FBulletCountUpdatedDelegate Property Definitions **********************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MagazineSize = { "MagazineSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectEX_eventBulletCountUpdatedDelegate_Parms, MagazineSize), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Bullets = { "Bullets", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectEX_eventBulletCountUpdatedDelegate_Parms, Bullets), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MagazineSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Bullets,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FBulletCountUpdatedDelegate Property Definitions ************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX, nullptr, "BulletCountUpdatedDelegate__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_ProjectEX_eventBulletCountUpdatedDelegate_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_ProjectEX_eventBulletCountUpdatedDelegate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProjectEX_BulletCountUpdatedDelegate__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FBulletCountUpdatedDelegate *********************************************

// ********** Begin Delegate FDamagedDelegate ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_ProjectEX_DamagedDelegate__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_ProjectEX_eventDamagedDelegate_Parms
	{
		float LifePercent;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDamagedDelegate constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LifePercent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDamagedDelegate constinit property declarations ************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDamagedDelegate Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LifePercent = { "LifePercent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectEX_eventDamagedDelegate_Parms, LifePercent), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LifePercent,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FDamagedDelegate Property Definitions ***********************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX, nullptr, "DamagedDelegate__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_ProjectEX_eventDamagedDelegate_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_ProjectEX_eventDamagedDelegate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProjectEX_DamagedDelegate__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FDamagedDelegate ********************************************************

// ********** Begin Class AShooterCharacter Function BP_OnDeath ************************************
static FName NAME_AShooterCharacter_BP_OnDeath = FName(TEXT("BP_OnDeath"));
void AShooterCharacter::BP_OnDeath()
{
	UFunction* Func = FindFunctionChecked(NAME_AShooterCharacter_BP_OnDeath);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AShooterCharacter_BP_OnDeath_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called to allow Blueprint code to react to this character's death */" },
#endif
		{ "DisplayName", "On Death" },
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called to allow Blueprint code to react to this character's death" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnDeath constinit property declarations ****************************
// ********** End Function BP_OnDeath constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AShooterCharacter, nullptr, "BP_OnDeath", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_AShooterCharacter_BP_OnDeath(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class AShooterCharacter Function BP_OnDeath **************************************

// ********** Begin Class AShooterCharacter Function DoStartFiring *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AShooterCharacter_DoStartFiring_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles start firing input */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles start firing input" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoStartFiring constinit property declarations *************************
// ********** End Function DoStartFiring constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AShooterCharacter, nullptr, "DoStartFiring", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_AShooterCharacter_DoStartFiring(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(AShooterCharacter::execDoStartFiring)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoStartFiring();
	P_NATIVE_END;
}
// ********** End Class AShooterCharacter Function DoStartFiring ***********************************

// ********** Begin Class AShooterCharacter Function DoStopFiring **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AShooterCharacter_DoStopFiring_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles stop firing input */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles stop firing input" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoStopFiring constinit property declarations **************************
// ********** End Function DoStopFiring constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AShooterCharacter, nullptr, "DoStopFiring", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_AShooterCharacter_DoStopFiring(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(AShooterCharacter::execDoStopFiring)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoStopFiring();
	P_NATIVE_END;
}
// ********** End Class AShooterCharacter Function DoStopFiring ************************************

// ********** Begin Class AShooterCharacter Function DoSwitchWeapon ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AShooterCharacter_DoSwitchWeapon_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles switch weapon input */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles switch weapon input" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoSwitchWeapon constinit property declarations ************************
// ********** End Function DoSwitchWeapon constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AShooterCharacter, nullptr, "DoSwitchWeapon", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_AShooterCharacter_DoSwitchWeapon(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(AShooterCharacter::execDoSwitchWeapon)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoSwitchWeapon();
	P_NATIVE_END;
}
// ********** End Class AShooterCharacter Function DoSwitchWeapon **********************************

// ********** Begin Class AShooterCharacter ********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_AShooterCharacter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A player controllable first person shooter character\n *  Manages a weapon inventory through the IShooterWeaponHolder interface\n *  Manages health and death\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Shooter/ShooterCharacter.h" },
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A player controllable first person shooter character\nManages a weapon inventory through the IShooterWeaponHolder interface\nManages health and death" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PawnNoiseEmitter_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AI Noise emitter component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI Noise emitter component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FireAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fire weapon input action */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fire weapon input action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SwitchWeaponAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Switch weapon input action */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Switch weapon input action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FirstPersonWeaponSocket_MetaData[] = {
		{ "Category", "Weapons" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the first person mesh weapon socket */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the first person mesh weapon socket" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ThirdPersonWeaponSocket_MetaData[] = {
		{ "Category", "Weapons" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the third person mesh weapon socket */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the third person mesh weapon socket" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxAimDistance_MetaData[] = {
		{ "Category", "Aim" },
		{ "ClampMax", "100000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max distance to use for aim traces */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max distance to use for aim traces" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHP_MetaData[] = {
		{ "Category", "Health" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max HP this character can have */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max HP this character can have" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TeamByte_MetaData[] = {
		{ "Category", "Team" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Team ID for this character*/" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Team ID for this character" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathTag_MetaData[] = {
		{ "Category", "Team" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Actor tag to grant this character when it dies */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor tag to grant this character when it dies" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerTag_MetaData[] = {
		{ "Category", "Tags" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Tag to pass to weapons and projectiles to identify their AI perception noise as player-generated */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tag to pass to weapons and projectiles to identify their AI perception noise as player-generated" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RespawnTime_MetaData[] = {
		{ "Category", "Destruction" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Variant_Shooter/ShooterCharacter.h" },
		{ "Units", "s" },
	};
#endif // WITH_METADATA

// ********** Begin Class AShooterCharacter constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PawnNoiseEmitter;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FireAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SwitchWeaponAction;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FirstPersonWeaponSocket;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ThirdPersonWeaponSocket;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxAimDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHP;
	static const UECodeGen_Private::FBytePropertyParams NewProp_TeamByte;
	static const UECodeGen_Private::FNamePropertyParams NewProp_DeathTag;
	static const UECodeGen_Private::FNamePropertyParams NewProp_PlayerTag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RespawnTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AShooterCharacter constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DoStartFiring"), .Pointer = &AShooterCharacter::execDoStartFiring },
		{ .NameUTF8 = UTF8TEXT("DoStopFiring"), .Pointer = &AShooterCharacter::execDoStopFiring },
		{ .NameUTF8 = UTF8TEXT("DoSwitchWeapon"), .Pointer = &AShooterCharacter::execDoSwitchWeapon },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AShooterCharacter_BP_OnDeath, "BP_OnDeath" }, // 809e72334efc126a9dca87186569766ea411a7b4
		{ &Z_Construct_UFunction_AShooterCharacter_DoStartFiring, "DoStartFiring" }, // e3e9e44fe98c2af7f56ff5de7e4e4fc2bc29b7de
		{ &Z_Construct_UFunction_AShooterCharacter_DoStopFiring, "DoStopFiring" }, // b5bc63712a953059659087b4819b6da6f5d54f44
		{ &Z_Construct_UFunction_AShooterCharacter_DoSwitchWeapon, "DoSwitchWeapon" }, // 0e139562fcabe2ec692f33e117e0e319af5843ff
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AShooterCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class AShooterCharacter Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PawnNoiseEmitter = { "PawnNoiseEmitter", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, PawnNoiseEmitter), Z_Construct_UClass_UPawnNoiseEmitterComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PawnNoiseEmitter_MetaData), NewProp_PawnNoiseEmitter_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FireAction = { "FireAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, FireAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FireAction_MetaData), NewProp_FireAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SwitchWeaponAction = { "SwitchWeaponAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, SwitchWeaponAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SwitchWeaponAction_MetaData), NewProp_SwitchWeaponAction_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_FirstPersonWeaponSocket = { "FirstPersonWeaponSocket", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, FirstPersonWeaponSocket), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FirstPersonWeaponSocket_MetaData), NewProp_FirstPersonWeaponSocket_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ThirdPersonWeaponSocket = { "ThirdPersonWeaponSocket", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, ThirdPersonWeaponSocket), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThirdPersonWeaponSocket_MetaData), NewProp_ThirdPersonWeaponSocket_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxAimDistance = { "MaxAimDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, MaxAimDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxAimDistance_MetaData), NewProp_MaxAimDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxHP = { "MaxHP", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, MaxHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHP_MetaData), NewProp_MaxHP_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_TeamByte = { "TeamByte", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, TeamByte), nullptr, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TeamByte_MetaData), NewProp_TeamByte_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_DeathTag = { "DeathTag", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, DeathTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathTag_MetaData), NewProp_DeathTag_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_PlayerTag = { "PlayerTag", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, PlayerTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerTag_MetaData), NewProp_PlayerTag_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RespawnTime = { "RespawnTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterCharacter, RespawnTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RespawnTime_MetaData), NewProp_RespawnTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PawnNoiseEmitter,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FireAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SwitchWeaponAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FirstPersonWeaponSocket,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ThirdPersonWeaponSocket,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxAimDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TeamByte,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeathTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlayerTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RespawnTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class AShooterCharacter Property Definitions *************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AProjectEXCharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_UShooterWeaponHolder, (int32)VTABLE_OFFSET(AShooterCharacter, IShooterWeaponHolder), false },  // 39b689deab2104edff98847c12cb917141317594
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_AShooterCharacter,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void AShooterCharacter_StaticRegisterNativesAShooterCharacter()
{
	UClass* Class = AShooterCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AShooterCharacter;
UClass* Z_Construct_UClass_AShooterCharacter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = AShooterCharacter;
		if (!Z_Registration_Info_UClass_AShooterCharacter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ShooterCharacter"),
				Z_Registration_Info_UClass_AShooterCharacter.InnerSingleton,
				AShooterCharacter_StaticRegisterNativesAShooterCharacter,
				DataSizeOf<TClass>(),
				alignof(TClass),
				TClass::StaticClassFlags,
				TClass::StaticClassCastFlags(),
				TClass::StaticConfigName(),
				(UClass::ClassConstructorType)InternalConstructor<TClass>,
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
				UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
				&TClass::Super::StaticClass,
				&TClass::WithinClass::StaticClass
			);
		}
		return Z_Registration_Info_UClass_AShooterCharacter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_AShooterCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AShooterCharacter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_AShooterCharacter.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AShooterCharacter);
AShooterCharacter::~AShooterCharacter() {}
// ********** End Class AShooterCharacter **********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_ShooterCharacter_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AShooterCharacter, TEXT("AShooterCharacter"), &Z_Registration_Info_UClass_AShooterCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AShooterCharacter), 506775419U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_ShooterCharacter_h__Script_ProjectEX_f369683eba7f4aba6db4785fea9c6d3e69e9557c{
	TEXT("/Script/ProjectEX"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
