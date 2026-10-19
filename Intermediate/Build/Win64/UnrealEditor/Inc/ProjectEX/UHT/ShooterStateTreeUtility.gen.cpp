// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShooterStateTreeUtility.h"
#include "StateTreeDelegate.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeShooterStateTreeUtility() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeConditionCommonBase(ETypeConstructPhase);
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeDelegateDispatcher(ETypeConstructPhase);
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeTaskCommonBase(ETypeConstructPhase);
AIMODULE_API UClass* Z_Construct_UClass_AAIController(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorTask(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationTask(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetCondition(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSenseEnemiesInstanceData(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSenseEnemiesTask(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetRandomFloatData(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetRandomFloatTask(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeShootAtTargetInstanceData(ETypeConstructPhase);
PROJECTEX_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeShootAtTargetTask(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterAIController(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AShooterNPC(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FStateTreeLineOfSightToTargetConditionInstanceData ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeLineOfSightToTargetConditionInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeLineOfSightToTargetConditionInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the FStateTreeLineOfSightToTargetCondition condition\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the FStateTreeLineOfSightToTargetCondition condition" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Targeting character */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Targeting character" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Target_MetaData[] = {
		{ "Category", "Condition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Target to check line of sight for */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Target to check line of sight for" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LineOfSightConeAngle_MetaData[] = {
		{ "Category", "Condition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max allowed line of sight cone angle, in degrees */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max allowed line of sight cone angle, in degrees" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumberOfVerticalLineOfSightChecks_MetaData[] = {
		{ "Category", "Condition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of vertical line of sight checks to run to try and get around low obstacles */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of vertical line of sight checks to run to try and get around low obstacles" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bMustHaveLineOfSight_MetaData[] = {
		{ "Category", "Condition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the condition passes if the character has line of sight */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the condition passes if the character has line of sight" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeLineOfSightToTargetConditionInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Target;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LineOfSightConeAngle;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumberOfVerticalLineOfSightChecks;
	static void NewProp_bMustHaveLineOfSight_SetBit(void* Obj)
	{
		((FStateTreeLineOfSightToTargetConditionInstanceData*)Obj)->bMustHaveLineOfSight = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bMustHaveLineOfSight;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeLineOfSightToTargetConditionInstanceData constinit property declarations 
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeLineOfSightToTargetConditionInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeLineOfSightToTargetConditionInstanceData Property Definitions 
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeLineOfSightToTargetConditionInstanceData, Character), Z_Construct_UClass_AShooterNPC, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeLineOfSightToTargetConditionInstanceData, Target), Z_Construct_UClass_AActor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Target_MetaData), NewProp_Target_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LineOfSightConeAngle = { "LineOfSightConeAngle", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeLineOfSightToTargetConditionInstanceData, LineOfSightConeAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LineOfSightConeAngle_MetaData), NewProp_LineOfSightConeAngle_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NumberOfVerticalLineOfSightChecks = { "NumberOfVerticalLineOfSightChecks", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeLineOfSightToTargetConditionInstanceData, NumberOfVerticalLineOfSightChecks), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumberOfVerticalLineOfSightChecks_MetaData), NewProp_NumberOfVerticalLineOfSightChecks_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bMustHaveLineOfSight = { "bMustHaveLineOfSight", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FStateTreeLineOfSightToTargetConditionInstanceData), &UHT_STATICS::NewProp_bMustHaveLineOfSight_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bMustHaveLineOfSight_MetaData), NewProp_bMustHaveLineOfSight_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Target,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LineOfSightConeAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumberOfVerticalLineOfSightChecks,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bMustHaveLineOfSight,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeLineOfSightToTargetConditionInstanceData Property Definitions 
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	nullptr,
	&NewStructOps,
	"StateTreeLineOfSightToTargetConditionInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeLineOfSightToTargetConditionInstanceData>(),
	alignof(FStateTreeLineOfSightToTargetConditionInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeLineOfSightToTargetConditionInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeLineOfSightToTargetConditionInstanceData ******************

// ********** Begin ScriptStruct FStateTreeLineOfSightToTargetCondition ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetCondition_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeLineOfSightToTargetCondition>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeLineOfSightToTargetCondition); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree condition to check if the character is grounded\n */" },
#endif
		{ "DisplayName", "Has Line of Sight to Target" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree condition to check if the character is grounded" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeLineOfSightToTargetCondition constinit property declarations 
// ********** End ScriptStruct FStateTreeLineOfSightToTargetCondition constinit property declarations 
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeLineOfSightToTargetCondition>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeLineOfSightToTargetCondition>() == std::is_polymorphic<FStateTreeConditionCommonBase>(), "USTRUCT FStateTreeLineOfSightToTargetCondition cannot be polymorphic unless super FStateTreeConditionCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	Z_Construct_UScriptStruct_FStateTreeConditionCommonBase,
	&NewStructOps,
	"StateTreeLineOfSightToTargetCondition",
	nullptr,
	0,
	DataSizeOf<FStateTreeLineOfSightToTargetCondition>(),
	alignof(FStateTreeLineOfSightToTargetCondition),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetCondition;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetCondition(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetCondition.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetCondition.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetCondition, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeLineOfSightToTargetCondition"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetCondition.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetCondition.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetCondition.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetCondition.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeLineOfSightToTargetCondition ******************************

// ********** Begin ScriptStruct FStateTreeFaceActorInstanceData ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeFaceActorInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeFaceActorInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Face Towards Actor StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Face Towards Actor StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AI Controller that will determine the focused actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI Controller that will determine the focused actor" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorToFaceTowards_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Actor that will be faced towards */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor that will be faced towards" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeFaceActorInstanceData constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActorToFaceTowards;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeFaceActorInstanceData constinit property declarations *****
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceActorInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeFaceActorInstanceData Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceActorInstanceData, Controller), Z_Construct_UClass_AAIController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActorToFaceTowards = { "ActorToFaceTowards", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceActorInstanceData, ActorToFaceTowards), Z_Construct_UClass_AActor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorToFaceTowards_MetaData), NewProp_ActorToFaceTowards_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActorToFaceTowards,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeFaceActorInstanceData Property Definitions ****************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	nullptr,
	&NewStructOps,
	"StateTreeFaceActorInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeFaceActorInstanceData>(),
	alignof(FStateTreeFaceActorInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeFaceActorInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeFaceActorInstanceData *************************************

// ********** Begin ScriptStruct FStateTreeFaceActorTask *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeFaceActorTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeFaceActorTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to face an AI-Controlled Pawn towards an Actor\n */" },
#endif
		{ "DisplayName", "Face Towards Actor" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to face an AI-Controlled Pawn towards an Actor" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeFaceActorTask constinit property declarations ***********
// ********** End ScriptStruct FStateTreeFaceActorTask constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceActorTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeFaceActorTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeFaceActorTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeFaceActorTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeFaceActorTask>(),
	alignof(FStateTreeFaceActorTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceActorTask, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeFaceActorTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeFaceActorTask *********************************************

// ********** Begin ScriptStruct FStateTreeFaceLocationInstanceData ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeFaceLocationInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeFaceLocationInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Face Towards Location StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Face Towards Location StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AI Controller that will determine the focused location */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI Controller that will determine the focused location" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FaceLocation_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Location that will be faced towards */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Location that will be faced towards" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeFaceLocationInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FaceLocation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeFaceLocationInstanceData constinit property declarations **
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceLocationInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeFaceLocationInstanceData Property Definitions ***********
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceLocationInstanceData, Controller), Z_Construct_UClass_AAIController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FaceLocation = { "FaceLocation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceLocationInstanceData, FaceLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FaceLocation_MetaData), NewProp_FaceLocation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FaceLocation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeFaceLocationInstanceData Property Definitions *************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	nullptr,
	&NewStructOps,
	"StateTreeFaceLocationInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeFaceLocationInstanceData>(),
	alignof(FStateTreeFaceLocationInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeFaceLocationInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeFaceLocationInstanceData **********************************

// ********** Begin ScriptStruct FStateTreeFaceLocationTask ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeFaceLocationTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeFaceLocationTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to face an AI-Controlled Pawn towards a world location\n */" },
#endif
		{ "DisplayName", "Face Towards Location" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to face an AI-Controlled Pawn towards a world location" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeFaceLocationTask constinit property declarations ********
// ********** End ScriptStruct FStateTreeFaceLocationTask constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceLocationTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeFaceLocationTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeFaceLocationTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeFaceLocationTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeFaceLocationTask>(),
	alignof(FStateTreeFaceLocationTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceLocationTask, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeFaceLocationTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeFaceLocationTask ******************************************

// ********** Begin ScriptStruct FStateTreeSetRandomFloatData **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeSetRandomFloatData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeSetRandomFloatData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeSetRandomFloatData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Set Random Float StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Set Random Float StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinValue_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum random value */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum random value" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxValue_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum random value */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum random value" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutValue_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Output calculated value */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Output calculated value" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeSetRandomFloatData constinit property declarations ******
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OutValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeSetRandomFloatData constinit property declarations ********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeSetRandomFloatData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeSetRandomFloatData Property Definitions *****************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MinValue = { "MinValue", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSetRandomFloatData, MinValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinValue_MetaData), NewProp_MinValue_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxValue = { "MaxValue", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSetRandomFloatData, MaxValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxValue_MetaData), NewProp_MaxValue_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_OutValue = { "OutValue", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSetRandomFloatData, OutValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutValue_MetaData), NewProp_OutValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MinValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeSetRandomFloatData Property Definitions *******************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	nullptr,
	&NewStructOps,
	"StateTreeSetRandomFloatData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeSetRandomFloatData>(),
	alignof(FStateTreeSetRandomFloatData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetRandomFloatData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeSetRandomFloatData, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeSetRandomFloatData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeSetRandomFloatData ****************************************

// ********** Begin ScriptStruct FStateTreeSetRandomFloatTask **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeSetRandomFloatTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeSetRandomFloatTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeSetRandomFloatTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to calculate a random float value within the specified range\n */" },
#endif
		{ "DisplayName", "Set Random Float" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to calculate a random float value within the specified range" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeSetRandomFloatTask constinit property declarations ******
// ********** End ScriptStruct FStateTreeSetRandomFloatTask constinit property declarations ********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeSetRandomFloatTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeSetRandomFloatTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeSetRandomFloatTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeSetRandomFloatTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeSetRandomFloatTask>(),
	alignof(FStateTreeSetRandomFloatTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetRandomFloatTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeSetRandomFloatTask, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeSetRandomFloatTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeSetRandomFloatTask ****************************************

// ********** Begin ScriptStruct FStateTreeShootAtTargetInstanceData *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeShootAtTargetInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeShootAtTargetInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeShootAtTargetInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Shoot At Target StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Shoot At Target StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** NPC that will do the shooting */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NPC that will do the shooting" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Target_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Target to shoot at */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Target to shoot at" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeShootAtTargetInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Target;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeShootAtTargetInstanceData constinit property declarations *
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeShootAtTargetInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeShootAtTargetInstanceData Property Definitions **********
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeShootAtTargetInstanceData, Character), Z_Construct_UClass_AShooterNPC, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeShootAtTargetInstanceData, Target), Z_Construct_UClass_AActor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Target_MetaData), NewProp_Target_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Target,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeShootAtTargetInstanceData Property Definitions ************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	nullptr,
	&NewStructOps,
	"StateTreeShootAtTargetInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeShootAtTargetInstanceData>(),
	alignof(FStateTreeShootAtTargetInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeShootAtTargetInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeShootAtTargetInstanceData, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeShootAtTargetInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeShootAtTargetInstanceData *********************************

// ********** Begin ScriptStruct FStateTreeShootAtTargetTask ***************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeShootAtTargetTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeShootAtTargetTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeShootAtTargetTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to have an NPC shoot at an actor\n */" },
#endif
		{ "DisplayName", "Shoot at Target" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to have an NPC shoot at an actor" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeShootAtTargetTask constinit property declarations *******
// ********** End ScriptStruct FStateTreeShootAtTargetTask constinit property declarations *********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeShootAtTargetTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeShootAtTargetTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeShootAtTargetTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeShootAtTargetTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeShootAtTargetTask>(),
	alignof(FStateTreeShootAtTargetTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeShootAtTargetTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeShootAtTargetTask, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeShootAtTargetTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeShootAtTargetTask *****************************************

// ********** Begin ScriptStruct FStateTreeSenseEnemiesInstanceData ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeSenseEnemiesInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeSenseEnemiesInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeSenseEnemiesInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Sense Enemies StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Sense Enemies StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sensing AI Controller */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sensing AI Controller" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sensing NPC */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sensing NPC" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetActor_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sensed actor to target */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sensed actor to target" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InvestigateLocation_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sensed location to investigate */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sensed location to investigate" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SenseTag_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Tag required on sensed actors */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tag required on sensed actors" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnInvestigateLocationDelegate_MetaData[] = {
		{ "Category", "StateTreeSenseEnemiesInstanceData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** StateTree delegate to broadcast when the AI should move to investigate something suspicious */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree delegate to broadcast when the AI should move to investigate something suspicious" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSeeEnemyDelegate_MetaData[] = {
		{ "Category", "StateTreeSenseEnemiesInstanceData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** StateTree delegate to broadcast when the AI has detected an enemy and should attack it */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree delegate to broadcast when the AI has detected an enemy and should attack it" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnForgetEnemyDelegate_MetaData[] = {
		{ "Category", "StateTreeSenseEnemiesInstanceData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** StateTree delegate to broadcast when the AI has lost track of its target */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree delegate to broadcast when the AI has lost track of its target" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DirectLineOfSightCone_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Line of sight cone half angle to consider a full sense */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Line of sight cone half angle to consider a full sense" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastStimulusStrength_MetaData[] = {
		{ "Category", "StateTreeSenseEnemiesInstanceData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Strength of the last processed stimulus */" },
#endif
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Strength of the last processed stimulus" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastStimulusTime_MetaData[] = {
		{ "Category", "StateTreeSenseEnemiesInstanceData" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeSenseEnemiesInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetActor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InvestigateLocation;
	static const UECodeGen_Private::FNamePropertyParams NewProp_SenseTag;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OnInvestigateLocationDelegate;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OnSeeEnemyDelegate;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OnForgetEnemyDelegate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DirectLineOfSightCone;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LastStimulusStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LastStimulusTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeSenseEnemiesInstanceData constinit property declarations **
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeSenseEnemiesInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeSenseEnemiesInstanceData Property Definitions ***********
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, Controller), Z_Construct_UClass_AShooterAIController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, Character), Z_Construct_UClass_AShooterNPC, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TargetActor = { "TargetActor", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, TargetActor), Z_Construct_UClass_AActor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetActor_MetaData), NewProp_TargetActor_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InvestigateLocation = { "InvestigateLocation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, InvestigateLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InvestigateLocation_MetaData), NewProp_InvestigateLocation_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SenseTag = { "SenseTag", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, SenseTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SenseTag_MetaData), NewProp_SenseTag_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OnInvestigateLocationDelegate = { "OnInvestigateLocationDelegate", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, OnInvestigateLocationDelegate), Z_Construct_UScriptStruct_FStateTreeDelegateDispatcher, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnInvestigateLocationDelegate_MetaData), NewProp_OnInvestigateLocationDelegate_MetaData) }; // f7a4f2c2ff72ddc5290685aa31e77423fbb43f5f
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OnSeeEnemyDelegate = { "OnSeeEnemyDelegate", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, OnSeeEnemyDelegate), Z_Construct_UScriptStruct_FStateTreeDelegateDispatcher, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSeeEnemyDelegate_MetaData), NewProp_OnSeeEnemyDelegate_MetaData) }; // f7a4f2c2ff72ddc5290685aa31e77423fbb43f5f
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OnForgetEnemyDelegate = { "OnForgetEnemyDelegate", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, OnForgetEnemyDelegate), Z_Construct_UScriptStruct_FStateTreeDelegateDispatcher, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnForgetEnemyDelegate_MetaData), NewProp_OnForgetEnemyDelegate_MetaData) }; // f7a4f2c2ff72ddc5290685aa31e77423fbb43f5f
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DirectLineOfSightCone = { "DirectLineOfSightCone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, DirectLineOfSightCone), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DirectLineOfSightCone_MetaData), NewProp_DirectLineOfSightCone_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LastStimulusStrength = { "LastStimulusStrength", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, LastStimulusStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastStimulusStrength_MetaData), NewProp_LastStimulusStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LastStimulusTime = { "LastStimulusTime", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSenseEnemiesInstanceData, LastStimulusTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastStimulusTime_MetaData), NewProp_LastStimulusTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InvestigateLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SenseTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnInvestigateLocationDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnSeeEnemyDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnForgetEnemyDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DirectLineOfSightCone,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LastStimulusStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LastStimulusTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeSenseEnemiesInstanceData Property Definitions *************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	nullptr,
	&NewStructOps,
	"StateTreeSenseEnemiesInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeSenseEnemiesInstanceData>(),
	alignof(FStateTreeSenseEnemiesInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSenseEnemiesInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeSenseEnemiesInstanceData, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeSenseEnemiesInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeSenseEnemiesInstanceData **********************************

// ********** Begin ScriptStruct FStateTreeSenseEnemiesTask ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeSenseEnemiesTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeSenseEnemiesTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeSenseEnemiesTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to have an NPC process AI Perceptions and sense nearby enemies\n */" },
#endif
		{ "DisplayName", "Sense Enemies" },
		{ "ModuleRelativePath", "Variant_Shooter/AI/ShooterStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to have an NPC process AI Perceptions and sense nearby enemies" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeSenseEnemiesTask constinit property declarations ********
// ********** End ScriptStruct FStateTreeSenseEnemiesTask constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeSenseEnemiesTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeSenseEnemiesTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeSenseEnemiesTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeSenseEnemiesTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeSenseEnemiesTask>(),
	alignof(FStateTreeSenseEnemiesTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSenseEnemiesTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeSenseEnemiesTask, (UObject*)Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase::Outer), TEXT("StateTreeSenseEnemiesTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeSenseEnemiesTask ******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_AI_ShooterStateTreeUtility_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData, Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData_Statics::NewStructOps, TEXT("StateTreeLineOfSightToTargetConditionInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetConditionInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeLineOfSightToTargetConditionInstanceData), 2691716825U) },
		{ Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetCondition, Z_Construct_UScriptStruct_FStateTreeLineOfSightToTargetCondition_Statics::NewStructOps, TEXT("StateTreeLineOfSightToTargetCondition"),&Z_Registration_Info_UScriptStruct_FStateTreeLineOfSightToTargetCondition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeLineOfSightToTargetCondition), 1272853017U) },
		{ Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData, Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::NewStructOps, TEXT("StateTreeFaceActorInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceActorInstanceData), 1324132211U) },
		{ Z_Construct_UScriptStruct_FStateTreeFaceActorTask, Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics::NewStructOps, TEXT("StateTreeFaceActorTask"),&Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceActorTask), 2966669904U) },
		{ Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData, Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::NewStructOps, TEXT("StateTreeFaceLocationInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceLocationInstanceData), 3032580562U) },
		{ Z_Construct_UScriptStruct_FStateTreeFaceLocationTask, Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics::NewStructOps, TEXT("StateTreeFaceLocationTask"),&Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceLocationTask), 371170619U) },
		{ Z_Construct_UScriptStruct_FStateTreeSetRandomFloatData, Z_Construct_UScriptStruct_FStateTreeSetRandomFloatData_Statics::NewStructOps, TEXT("StateTreeSetRandomFloatData"),&Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeSetRandomFloatData), 798032271U) },
		{ Z_Construct_UScriptStruct_FStateTreeSetRandomFloatTask, Z_Construct_UScriptStruct_FStateTreeSetRandomFloatTask_Statics::NewStructOps, TEXT("StateTreeSetRandomFloatTask"),&Z_Registration_Info_UScriptStruct_FStateTreeSetRandomFloatTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeSetRandomFloatTask), 1997552021U) },
		{ Z_Construct_UScriptStruct_FStateTreeShootAtTargetInstanceData, Z_Construct_UScriptStruct_FStateTreeShootAtTargetInstanceData_Statics::NewStructOps, TEXT("StateTreeShootAtTargetInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeShootAtTargetInstanceData), 458205245U) },
		{ Z_Construct_UScriptStruct_FStateTreeShootAtTargetTask, Z_Construct_UScriptStruct_FStateTreeShootAtTargetTask_Statics::NewStructOps, TEXT("StateTreeShootAtTargetTask"),&Z_Registration_Info_UScriptStruct_FStateTreeShootAtTargetTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeShootAtTargetTask), 3651040044U) },
		{ Z_Construct_UScriptStruct_FStateTreeSenseEnemiesInstanceData, Z_Construct_UScriptStruct_FStateTreeSenseEnemiesInstanceData_Statics::NewStructOps, TEXT("StateTreeSenseEnemiesInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeSenseEnemiesInstanceData), 3401627551U) },
		{ Z_Construct_UScriptStruct_FStateTreeSenseEnemiesTask, Z_Construct_UScriptStruct_FStateTreeSenseEnemiesTask_Statics::NewStructOps, TEXT("StateTreeSenseEnemiesTask"),&Z_Registration_Info_UScriptStruct_FStateTreeSenseEnemiesTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeSenseEnemiesTask), 580700219U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_AI_ShooterStateTreeUtility_h__Script_ProjectEX_145ea355d054d511ea96e1444a856dfa7aa49c18{
	TEXT("/Script/ProjectEX"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
