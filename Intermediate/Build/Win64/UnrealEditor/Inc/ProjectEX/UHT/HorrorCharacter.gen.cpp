// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HorrorCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeHorrorCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_USpotLightComponent(ETypeConstructPhase);
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AHorrorCharacter(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AProjectEXCharacter(ETypeConstructPhase);
PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_SprintStateChangedDelegate__DelegateSignature(ETypeConstructPhase);
PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_UpdateSprintMeterDelegate__DelegateSignature(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_AHorrorCharacter(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FUpdateSprintMeterDelegate ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_ProjectEX_UpdateSprintMeterDelegate__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_ProjectEX_eventUpdateSprintMeterDelegate_Parms
	{
		float Percentage;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FUpdateSprintMeterDelegate constinit property declarations ************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Percentage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FUpdateSprintMeterDelegate constinit property declarations **************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FUpdateSprintMeterDelegate Property Definitions ***********************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Percentage = { "Percentage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectEX_eventUpdateSprintMeterDelegate_Parms, Percentage), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Percentage,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FUpdateSprintMeterDelegate Property Definitions *************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX, nullptr, "UpdateSprintMeterDelegate__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_ProjectEX_eventUpdateSprintMeterDelegate_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_ProjectEX_eventUpdateSprintMeterDelegate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProjectEX_UpdateSprintMeterDelegate__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FUpdateSprintMeterDelegate **********************************************

// ********** Begin Delegate FSprintStateChangedDelegate *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_ProjectEX_SprintStateChangedDelegate__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_ProjectEX_eventSprintStateChangedDelegate_Parms
	{
		bool bSprinting;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FSprintStateChangedDelegate constinit property declarations ***********
	static void NewProp_bSprinting_SetBit(void* Obj)
	{
		((_Script_ProjectEX_eventSprintStateChangedDelegate_Parms*)Obj)->bSprinting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSprinting;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FSprintStateChangedDelegate constinit property declarations *************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FSprintStateChangedDelegate Property Definitions **********************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSprinting = { "bSprinting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_ProjectEX_eventSprintStateChangedDelegate_Parms), &UHT_STATICS::NewProp_bSprinting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSprinting,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FSprintStateChangedDelegate Property Definitions ************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX, nullptr, "SprintStateChangedDelegate__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_ProjectEX_eventSprintStateChangedDelegate_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_ProjectEX_eventSprintStateChangedDelegate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProjectEX_SprintStateChangedDelegate__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FSprintStateChangedDelegate *********************************************

// ********** Begin Class AHorrorCharacter Function DoEndSprint ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AHorrorCharacter_DoEndSprint_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stops sprinting behavior */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stops sprinting behavior" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoEndSprint constinit property declarations ***************************
// ********** End Function DoEndSprint constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AHorrorCharacter, nullptr, "DoEndSprint", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_AHorrorCharacter_DoEndSprint(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(AHorrorCharacter::execDoEndSprint)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoEndSprint();
	P_NATIVE_END;
}
// ********** End Class AHorrorCharacter Function DoEndSprint **************************************

// ********** Begin Class AHorrorCharacter Function DoStartSprint **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AHorrorCharacter_DoStartSprint_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Starts sprinting behavior */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Starts sprinting behavior" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoStartSprint constinit property declarations *************************
// ********** End Function DoStartSprint constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AHorrorCharacter, nullptr, "DoStartSprint", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_AHorrorCharacter_DoStartSprint(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(AHorrorCharacter::execDoStartSprint)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoStartSprint();
	P_NATIVE_END;
}
// ********** End Class AHorrorCharacter Function DoStartSprint ************************************

// ********** Begin Class AHorrorCharacter *********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_AHorrorCharacter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple first person horror character\n *  Provides stamina-based sprinting\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Horror/HorrorCharacter.h" },
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple first person horror character\nProvides stamina-based sprinting" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpotLight_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Player light source */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Player light source" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SprintAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fire weapon input action */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fire weapon input action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WalkSpeed_MetaData[] = {
		{ "Category", "Walk" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default walk speed when not sprinting or recovering */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default walk speed when not sprinting or recovering" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SprintFixedTickTime_MetaData[] = {
		{ "Category", "Sprint" },
		{ "ClampMax", "1" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time interval for sprinting stamina ticks */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time interval for sprinting stamina ticks" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SprintTime_MetaData[] = {
		{ "Category", "Sprint" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How long we can sprint for, in seconds */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How long we can sprint for, in seconds" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SprintSpeed_MetaData[] = {
		{ "Category", "Sprint" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Walk speed while sprinting */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Walk speed while sprinting" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RecoveringWalkSpeed_MetaData[] = {
		{ "Category", "Recovery" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Walk speed while recovering stamina */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Walk speed while recovering stamina" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RecoveryTime_MetaData[] = {
		{ "Category", "Recovery" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time it takes for the sprint meter to recover */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/HorrorCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time it takes for the sprint meter to recover" },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA

// ********** Begin Class AHorrorCharacter constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpotLight;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SprintAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WalkSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SprintFixedTickTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SprintTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SprintSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RecoveringWalkSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RecoveryTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AHorrorCharacter constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DoEndSprint"), .Pointer = &AHorrorCharacter::execDoEndSprint },
		{ .NameUTF8 = UTF8TEXT("DoStartSprint"), .Pointer = &AHorrorCharacter::execDoStartSprint },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AHorrorCharacter_DoEndSprint, "DoEndSprint" }, // 39def42958aee7899aeeca40b2a90dee672df866
		{ &Z_Construct_UFunction_AHorrorCharacter_DoStartSprint, "DoStartSprint" }, // 15d7d1721c827e02f425153f296a74d470cd57ba
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHorrorCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class AHorrorCharacter Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SpotLight = { "SpotLight", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AHorrorCharacter, SpotLight), Z_Construct_UClass_USpotLightComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpotLight_MetaData), NewProp_SpotLight_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SprintAction = { "SprintAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AHorrorCharacter, SprintAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SprintAction_MetaData), NewProp_SprintAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WalkSpeed = { "WalkSpeed", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AHorrorCharacter, WalkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WalkSpeed_MetaData), NewProp_WalkSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SprintFixedTickTime = { "SprintFixedTickTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AHorrorCharacter, SprintFixedTickTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SprintFixedTickTime_MetaData), NewProp_SprintFixedTickTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SprintTime = { "SprintTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AHorrorCharacter, SprintTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SprintTime_MetaData), NewProp_SprintTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SprintSpeed = { "SprintSpeed", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AHorrorCharacter, SprintSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SprintSpeed_MetaData), NewProp_SprintSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RecoveringWalkSpeed = { "RecoveringWalkSpeed", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AHorrorCharacter, RecoveringWalkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RecoveringWalkSpeed_MetaData), NewProp_RecoveringWalkSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RecoveryTime = { "RecoveryTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AHorrorCharacter, RecoveryTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RecoveryTime_MetaData), NewProp_RecoveryTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpotLight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SprintAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WalkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SprintFixedTickTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SprintTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SprintSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RecoveringWalkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RecoveryTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class AHorrorCharacter Property Definitions **************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AProjectEXCharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_AHorrorCharacter,
	"Game",
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
static void AHorrorCharacter_StaticRegisterNativesAHorrorCharacter()
{
	UClass* Class = AHorrorCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AHorrorCharacter;
UClass* Z_Construct_UClass_AHorrorCharacter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = AHorrorCharacter;
		if (!Z_Registration_Info_UClass_AHorrorCharacter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("HorrorCharacter"),
				Z_Registration_Info_UClass_AHorrorCharacter.InnerSingleton,
				AHorrorCharacter_StaticRegisterNativesAHorrorCharacter,
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
		return Z_Registration_Info_UClass_AHorrorCharacter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_AHorrorCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AHorrorCharacter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_AHorrorCharacter.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AHorrorCharacter);
AHorrorCharacter::~AHorrorCharacter() {}
// ********** End Class AHorrorCharacter ***********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AHorrorCharacter, TEXT("AHorrorCharacter"), &Z_Registration_Info_UClass_AHorrorCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AHorrorCharacter), 3524540429U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h__Script_ProjectEX_344f75c95b66a2f8c091df3f36efc0fd73c2f8ca{
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
