// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShooterProjectile.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeShooterProjectile() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UClass(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UDamageType(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UProjectileMovementComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USphereComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterProjectile(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterProjectile(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class AShooterProjectile Function BP_OnProjectileHit ***************************
struct ShooterProjectile_eventBP_OnProjectileHit_Parms
{
	FHitResult Hit;
};
static FName NAME_AShooterProjectile_BP_OnProjectileHit = FName(TEXT("BP_OnProjectileHit"));
void AShooterProjectile::BP_OnProjectileHit(FHitResult const& Hit)
{
	ShooterProjectile_eventBP_OnProjectileHit_Parms Parms;
	Parms.Hit=Hit;
	UFunction* Func = FindFunctionChecked(NAME_AShooterProjectile_BP_OnProjectileHit);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AShooterProjectile_BP_OnProjectileHit_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Projectile" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Passes control to Blueprint to implement any effects on hit. */" },
#endif
		{ "DisplayName", "On Projectile Hit" },
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Passes control to Blueprint to implement any effects on hit." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Hit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnProjectileHit constinit property declarations ********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Hit;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnProjectileHit constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnProjectileHit Property Definitions *******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Hit = { "Hit", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ShooterProjectile_eventBP_OnProjectileHit_Parms, Hit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Hit_MetaData), NewProp_Hit_MetaData) }; // e0ec7b349cc3b29366a6161006ad7fa74de2944e
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Hit,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_OnProjectileHit Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AShooterProjectile, nullptr, "BP_OnProjectileHit", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<ShooterProjectile_eventBP_OnProjectileHit_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08480800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(ShooterProjectile_eventBP_OnProjectileHit_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AShooterProjectile_BP_OnProjectileHit(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class AShooterProjectile Function BP_OnProjectileHit *****************************

// ********** Begin Class AShooterProjectile *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_AShooterProjectile_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple projectile class for a first person shooter game\n */" },
#endif
		{ "IncludePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple projectile class for a first person shooter game" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Provides collision detection for the projectile */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Provides collision detection for the projectile" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProjectileMovement_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles movement for the projectile */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles movement for the projectile" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseLoudness_MetaData[] = {
		{ "Category", "Projectile|Noise" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Loudness of the AI perception noise done by this projectile on hit */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Loudness of the AI perception noise done by this projectile on hit" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseRange_MetaData[] = {
		{ "Category", "Projectile|Noise" },
		{ "ClampMax", "100000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Range of the AI perception noise done by this projectile on hit */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Range of the AI perception noise done by this projectile on hit" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseTag_MetaData[] = {
		{ "Category", "Noise" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Tag of the AI perception noise done by this projectile on hit */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tag of the AI perception noise done by this projectile on hit" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PhysicsForce_MetaData[] = {
		{ "Category", "Projectile|Hit" },
		{ "ClampMax", "50000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Physics force to apply on hit */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Physics force to apply on hit" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HitDamage_MetaData[] = {
		{ "Category", "Projectile|Hit" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Damage to apply on hit */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Damage to apply on hit" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HitDamageType_MetaData[] = {
		{ "Category", "Projectile|Hit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Type of damage to apply. Can be used to represent specific types of damage such as fire, explosion, etc. */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Type of damage to apply. Can be used to represent specific types of damage such as fire, explosion, etc." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDamageOwner_MetaData[] = {
		{ "Category", "Projectile|Hit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the projectile can damage the character that shot it */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the projectile can damage the character that shot it" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bExplodeOnHit_MetaData[] = {
		{ "Category", "Projectile|Explosion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the projectile will explode and apply radial damage to all actors in range */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the projectile will explode and apply radial damage to all actors in range" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExplosionRadius_MetaData[] = {
		{ "Category", "Projectile|Explosion" },
		{ "ClampMax", "5000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max distance for actors to be affected by explosion damage */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max distance for actors to be affected by explosion damage" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeferredDestructionTime_MetaData[] = {
		{ "Category", "Projectile|Destruction" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How long to wait after a hit before destroying this projectile */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/Weapons/ShooterProjectile.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How long to wait after a hit before destroying this projectile" },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA

// ********** Begin Class AShooterProjectile constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollisionComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProjectileMovement;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseLoudness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseRange;
	static const UECodeGen_Private::FNamePropertyParams NewProp_NoiseTag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PhysicsForce;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HitDamage;
	static const UECodeGen_Private::FClassPropertyParams NewProp_HitDamageType;
	static void NewProp_bDamageOwner_SetBit(void* Obj)
	{
		((AShooterProjectile*)Obj)->bDamageOwner = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDamageOwner;
	static void NewProp_bExplodeOnHit_SetBit(void* Obj)
	{
		((AShooterProjectile*)Obj)->bExplodeOnHit = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bExplodeOnHit;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ExplosionRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeferredDestructionTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AShooterProjectile constinit property declarations *************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AShooterProjectile_BP_OnProjectileHit, "BP_OnProjectileHit" }, // 6c1d3496ae3fbc3eb30e5db239712b4cebf3d93a
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AShooterProjectile>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class AShooterProjectile Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CollisionComponent = { "CollisionComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, CollisionComponent), Z_Construct_UClass_USphereComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionComponent_MetaData), NewProp_CollisionComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ProjectileMovement = { "ProjectileMovement", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, ProjectileMovement), Z_Construct_UClass_UProjectileMovementComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProjectileMovement_MetaData), NewProp_ProjectileMovement_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NoiseLoudness = { "NoiseLoudness", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, NoiseLoudness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseLoudness_MetaData), NewProp_NoiseLoudness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NoiseRange = { "NoiseRange", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, NoiseRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseRange_MetaData), NewProp_NoiseRange_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_NoiseTag = { "NoiseTag", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, NoiseTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseTag_MetaData), NewProp_NoiseTag_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_PhysicsForce = { "PhysicsForce", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, PhysicsForce), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PhysicsForce_MetaData), NewProp_PhysicsForce_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_HitDamage = { "HitDamage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, HitDamage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HitDamage_MetaData), NewProp_HitDamage_MetaData) };
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_HitDamageType = { "HitDamageType", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, HitDamageType), Z_Construct_UClass_UClass, Z_Construct_UClass_UDamageType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HitDamageType_MetaData), NewProp_HitDamageType_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bDamageOwner = { "bDamageOwner", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(AShooterProjectile), &UHT_STATICS::NewProp_bDamageOwner_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDamageOwner_MetaData), NewProp_bDamageOwner_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bExplodeOnHit = { "bExplodeOnHit", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(AShooterProjectile), &UHT_STATICS::NewProp_bExplodeOnHit_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bExplodeOnHit_MetaData), NewProp_bExplodeOnHit_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ExplosionRadius = { "ExplosionRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, ExplosionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExplosionRadius_MetaData), NewProp_ExplosionRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DeferredDestructionTime = { "DeferredDestructionTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterProjectile, DeferredDestructionTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeferredDestructionTime_MetaData), NewProp_DeferredDestructionTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CollisionComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ProjectileMovement,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NoiseLoudness,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NoiseRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NoiseTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PhysicsForce,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HitDamage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HitDamageType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bDamageOwner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bExplodeOnHit,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ExplosionRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeferredDestructionTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class AShooterProjectile Property Definitions ************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_AShooterProjectile,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x009000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_AShooterProjectile;
UClass* Z_Construct_UClass_AShooterProjectile(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = AShooterProjectile;
		if (!Z_Registration_Info_UClass_AShooterProjectile.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ShooterProjectile"),
				Z_Registration_Info_UClass_AShooterProjectile.InnerSingleton,
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
		return Z_Registration_Info_UClass_AShooterProjectile.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_AShooterProjectile.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AShooterProjectile.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_AShooterProjectile.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AShooterProjectile);
AShooterProjectile::~AShooterProjectile() {}
// ********** End Class AShooterProjectile *********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterProjectile_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AShooterProjectile, TEXT("AShooterProjectile"), &Z_Registration_Info_UClass_AShooterProjectile, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AShooterProjectile), 860634862U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterProjectile_h__Script_ProjectEX_aa657a1a04eed0f3fef6244895c65a89d77b4a6f{
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
