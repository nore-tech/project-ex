// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShooterNPC.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeShooterNPC() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_PawnDeathDelegate__DelegateSignature(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AProjectEXCharacter(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterNPC(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterNPC(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterWeapon(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_IShooterWeaponHolder(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FPawnDeathDelegate ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_ProjectEX_PawnDeathDelegate__DelegateSignature_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FPawnDeathDelegate constinit property declarations ********************
// ********** End Delegate FPawnDeathDelegate constinit property declarations **********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX, nullptr, "PawnDeathDelegate__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UDelegateFunction_ProjectEX_PawnDeathDelegate__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FPawnDeathDelegate ******************************************************

// ********** Begin Class AShooterNPC **************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_AShooterNPC_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple AI-controlled shooter game NPC\n *  Executes its behavior through a StateTree managed by its AI Controller\n *  Holds and manages a weapon\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Shooter/AI/ShooterNPC.h" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple AI-controlled shooter game NPC\nExecutes its behavior through a StateTree managed by its AI Controller\nHolds and manages a weapon" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHP_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current HP for this character. It dies if it reaches zero through damage */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current HP for this character. It dies if it reaches zero through damage" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RagdollCollisionProfile_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the collision profile to use during ragdoll death */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the collision profile to use during ragdoll death" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeferredDestructionTime_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait after death before destroying this actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait after death before destroying this actor" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TeamByte_MetaData[] = {
		{ "Category", "Team" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Team byte for this character */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Team byte for this character" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathTag_MetaData[] = {
		{ "Category", "Team" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Actor tag to grant this character when it dies */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor tag to grant this character when it dies" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WeaponClass_MetaData[] = {
		{ "Category", "Weapon" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Type of weapon to spawn for this character */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Type of weapon to spawn for this character" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FirstPersonWeaponSocket_MetaData[] = {
		{ "Category", "Weapons" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the first person mesh weapon socket */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the first person mesh weapon socket" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ThirdPersonWeaponSocket_MetaData[] = {
		{ "Category", "Weapons" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the third person mesh weapon socket */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the third person mesh weapon socket" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AimRange_MetaData[] = {
		{ "Category", "Aim" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max range for aiming calculations */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max range for aiming calculations" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AimVarianceHalfAngle_MetaData[] = {
		{ "Category", "Aim" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Cone variance to apply while aiming */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cone variance to apply while aiming" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinAimOffsetZ_MetaData[] = {
		{ "Category", "Aim" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum vertical offset from the target center to apply when aiming */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum vertical offset from the target center to apply when aiming" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxAimOffsetZ_MetaData[] = {
		{ "Category", "Aim" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum vertical offset from the target center to apply when aiming */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum vertical offset from the target center to apply when aiming" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class AShooterNPC constinit property declarations ******************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHP;
	static const UECodeGen_Private::FNamePropertyParams NewProp_RagdollCollisionProfile;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeferredDestructionTime;
	static const UECodeGen_Private::FBytePropertyParams NewProp_TeamByte;
	static const UECodeGen_Private::FNamePropertyParams NewProp_DeathTag;
	static const UECodeGen_Private::FClassPropertyParams NewProp_WeaponClass;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FirstPersonWeaponSocket;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ThirdPersonWeaponSocket;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AimRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AimVarianceHalfAngle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinAimOffsetZ;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxAimOffsetZ;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AShooterNPC constinit property declarations ********************************
	static FTypeConstructFunc* DependentSingletons[];
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AShooterNPC>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class AShooterNPC Property Definitions *****************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CurrentHP = { "CurrentHP", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, CurrentHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHP_MetaData), NewProp_CurrentHP_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RagdollCollisionProfile = { "RagdollCollisionProfile", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, RagdollCollisionProfile), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RagdollCollisionProfile_MetaData), NewProp_RagdollCollisionProfile_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DeferredDestructionTime = { "DeferredDestructionTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, DeferredDestructionTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeferredDestructionTime_MetaData), NewProp_DeferredDestructionTime_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_TeamByte = { "TeamByte", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, TeamByte), nullptr, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TeamByte_MetaData), NewProp_TeamByte_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_DeathTag = { "DeathTag", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, DeathTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathTag_MetaData), NewProp_DeathTag_MetaData) };
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_WeaponClass = { "WeaponClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, WeaponClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AShooterWeapon, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WeaponClass_MetaData), NewProp_WeaponClass_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_FirstPersonWeaponSocket = { "FirstPersonWeaponSocket", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, FirstPersonWeaponSocket), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FirstPersonWeaponSocket_MetaData), NewProp_FirstPersonWeaponSocket_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ThirdPersonWeaponSocket = { "ThirdPersonWeaponSocket", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, ThirdPersonWeaponSocket), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThirdPersonWeaponSocket_MetaData), NewProp_ThirdPersonWeaponSocket_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AimRange = { "AimRange", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, AimRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AimRange_MetaData), NewProp_AimRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AimVarianceHalfAngle = { "AimVarianceHalfAngle", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, AimVarianceHalfAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AimVarianceHalfAngle_MetaData), NewProp_AimVarianceHalfAngle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MinAimOffsetZ = { "MinAimOffsetZ", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, MinAimOffsetZ), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinAimOffsetZ_MetaData), NewProp_MinAimOffsetZ_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxAimOffsetZ = { "MaxAimOffsetZ", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPC, MaxAimOffsetZ), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxAimOffsetZ_MetaData), NewProp_MaxAimOffsetZ_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RagdollCollisionProfile,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeferredDestructionTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TeamByte,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeathTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WeaponClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FirstPersonWeaponSocket,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ThirdPersonWeaponSocket,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AimRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AimVarianceHalfAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MinAimOffsetZ,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxAimOffsetZ,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class AShooterNPC Property Definitions *******************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AProjectEXCharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_UShooterWeaponHolder, (int32)VTABLE_OFFSET(AShooterNPC, IShooterWeaponHolder), false },  // 39b689deab2104edff98847c12cb917141317594
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_AShooterNPC,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_AShooterNPC;
UClass* Z_Construct_UClass_AShooterNPC(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = AShooterNPC;
		if (!Z_Registration_Info_UClass_AShooterNPC.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ShooterNPC"),
				Z_Registration_Info_UClass_AShooterNPC.InnerSingleton,
				nullptr,
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
		return Z_Registration_Info_UClass_AShooterNPC.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_AShooterNPC.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AShooterNPC.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_AShooterNPC.OuterSingleton;
}
#undef UHT_STATICS
AShooterNPC::AShooterNPC() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AShooterNPC);
AShooterNPC::~AShooterNPC() {}
// ********** End Class AShooterNPC ****************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_AI_ShooterNPC_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AShooterNPC, TEXT("AShooterNPC"), &Z_Registration_Info_UClass_AShooterNPC, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AShooterNPC), 769250485U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_AI_ShooterNPC_h__Script_ProjectEX_b3415870c1658a17a1062446e12faaad38617a9e{
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
