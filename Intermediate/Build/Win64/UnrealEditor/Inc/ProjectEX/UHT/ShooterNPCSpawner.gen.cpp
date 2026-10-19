// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShooterNPCSpawner.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeShooterNPCSpawner() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UClass(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UArrowComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UCapsuleComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterNPCSpawner(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterNPC(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterNPCSpawner(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class AShooterNPCSpawner Function OnNPCDied ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AShooterNPCSpawner_OnNPCDied_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called when the spawned NPC has died */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the spawned NPC has died" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnNPCDied constinit property declarations *****************************
// ********** End Function OnNPCDied constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AShooterNPCSpawner, nullptr, "OnNPCDied", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_AShooterNPCSpawner_OnNPCDied(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(AShooterNPCSpawner::execOnNPCDied)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnNPCDied();
	P_NATIVE_END;
}
// ********** End Class AShooterNPCSpawner Function OnNPCDied **************************************

// ********** Begin Class AShooterNPCSpawner *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_AShooterNPCSpawner_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A basic Actor in charge of spawning Shooter NPCs and monitoring their deaths.\n *  NPCs will be spawned one by one, and the spawner will wait until it dies before spawning a new one.\n */" },
#endif
		{ "IncludePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A basic Actor in charge of spawning Shooter NPCs and monitoring their deaths.\nNPCs will be spawned one by one, and the spawner will wait until it dies before spawning a new one." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnCapsule_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnDirection_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPCClass_MetaData[] = {
		{ "Category", "NPC Spawner" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Type of NPC to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Type of NPC to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialSpawnDelay_MetaData[] = {
		{ "Category", "NPC Spawner" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before spawning the first NPC on game start */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before spawning the first NPC on game start" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnCount_MetaData[] = {
		{ "Category", "NPC Spawner" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of NPCs to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of NPCs to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RespawnDelay_MetaData[] = {
		{ "Category", "NPC Spawner" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before spawning the next NPC after the current one dies */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterNPCSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before spawning the next NPC after the current one dies" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class AShooterNPCSpawner constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnCapsule;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnDirection;
	static const UECodeGen_Private::FClassPropertyParams NewProp_NPCClass;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialSpawnDelay;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SpawnCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RespawnDelay;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AShooterNPCSpawner constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnNPCDied"), .Pointer = &AShooterNPCSpawner::execOnNPCDied },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AShooterNPCSpawner_OnNPCDied, "OnNPCDied" }, // d3ba0d042e9950a14a677ef86a3940789ac98e85
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AShooterNPCSpawner>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class AShooterNPCSpawner Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SpawnCapsule = { "SpawnCapsule", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPCSpawner, SpawnCapsule), Z_Construct_UClass_UCapsuleComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnCapsule_MetaData), NewProp_SpawnCapsule_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SpawnDirection = { "SpawnDirection", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPCSpawner, SpawnDirection), Z_Construct_UClass_UArrowComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnDirection_MetaData), NewProp_SpawnDirection_MetaData) };
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_NPCClass = { "NPCClass", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPCSpawner, NPCClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AShooterNPC, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPCClass_MetaData), NewProp_NPCClass_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_InitialSpawnDelay = { "InitialSpawnDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPCSpawner, InitialSpawnDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialSpawnDelay_MetaData), NewProp_InitialSpawnDelay_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SpawnCount = { "SpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPCSpawner, SpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnCount_MetaData), NewProp_SpawnCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RespawnDelay = { "RespawnDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AShooterNPCSpawner, RespawnDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RespawnDelay_MetaData), NewProp_RespawnDelay_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpawnCapsule,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpawnDirection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPCClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InitialSpawnDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RespawnDelay,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class AShooterNPCSpawner Property Definitions ************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_AShooterNPCSpawner,
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
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void AShooterNPCSpawner_StaticRegisterNativesAShooterNPCSpawner()
{
	UClass* Class = AShooterNPCSpawner::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AShooterNPCSpawner;
UClass* Z_Construct_UClass_AShooterNPCSpawner(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = AShooterNPCSpawner;
		if (!Z_Registration_Info_UClass_AShooterNPCSpawner.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ShooterNPCSpawner"),
				Z_Registration_Info_UClass_AShooterNPCSpawner.InnerSingleton,
				AShooterNPCSpawner_StaticRegisterNativesAShooterNPCSpawner,
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
		return Z_Registration_Info_UClass_AShooterNPCSpawner.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_AShooterNPCSpawner.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AShooterNPCSpawner.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_AShooterNPCSpawner.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AShooterNPCSpawner);
AShooterNPCSpawner::~AShooterNPCSpawner() {}
// ********** End Class AShooterNPCSpawner *********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_AI_ShooterNPCSpawner_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AShooterNPCSpawner, TEXT("AShooterNPCSpawner"), &Z_Registration_Info_UClass_AShooterNPCSpawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AShooterNPCSpawner), 1976896493U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_AI_ShooterNPCSpawner_h__Script_ProjectEX_e52dbc5418516be6c700fcc552b5ea7a62436286{
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
