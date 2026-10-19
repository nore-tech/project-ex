// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HorrorUI.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeHorrorUI() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_UHorrorUI(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_UHorrorUI(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UHorrorUI Function BP_SprintMeterUpdated *********************************
struct HorrorUI_eventBP_SprintMeterUpdated_Parms
{
	float Percent;
};
static FName NAME_UHorrorUI_BP_SprintMeterUpdated = FName(TEXT("BP_SprintMeterUpdated"));
void UHorrorUI::BP_SprintMeterUpdated(float Percent)
{
	HorrorUI_eventBP_SprintMeterUpdated_Parms Parms;
	Parms.Percent=Percent;
	UFunction* Func = FindFunctionChecked(NAME_UHorrorUI_BP_SprintMeterUpdated);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UHorrorUI_BP_SprintMeterUpdated_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Horror" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Passes control to Blueprint to update the sprint meter widgets */" },
#endif
		{ "DisplayName", "Sprint Meter Updated" },
		{ "ModuleRelativePath", "Variant_Horror/UI/HorrorUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Passes control to Blueprint to update the sprint meter widgets" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_SprintMeterUpdated constinit property declarations *****************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Percent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_SprintMeterUpdated constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_SprintMeterUpdated Property Definitions ****************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Percent = { "Percent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(HorrorUI_eventBP_SprintMeterUpdated_Parms, Percent), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Percent,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_SprintMeterUpdated Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UHorrorUI, nullptr, "BP_SprintMeterUpdated", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<HorrorUI_eventBP_SprintMeterUpdated_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(HorrorUI_eventBP_SprintMeterUpdated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHorrorUI_BP_SprintMeterUpdated(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class UHorrorUI Function BP_SprintMeterUpdated ***********************************

// ********** Begin Class UHorrorUI Function BP_SprintStateChanged *********************************
struct HorrorUI_eventBP_SprintStateChanged_Parms
{
	bool bSprinting;
};
static FName NAME_UHorrorUI_BP_SprintStateChanged = FName(TEXT("BP_SprintStateChanged"));
void UHorrorUI::BP_SprintStateChanged(bool bSprinting)
{
	HorrorUI_eventBP_SprintStateChanged_Parms Parms;
	Parms.bSprinting=bSprinting ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_UHorrorUI_BP_SprintStateChanged);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UHorrorUI_BP_SprintStateChanged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Horror" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Passes control to Blueprint to update the sprint meter status */" },
#endif
		{ "DisplayName", "Sprint State Changed" },
		{ "ModuleRelativePath", "Variant_Horror/UI/HorrorUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Passes control to Blueprint to update the sprint meter status" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_SprintStateChanged constinit property declarations *****************
	static void NewProp_bSprinting_SetBit(void* Obj)
	{
		((HorrorUI_eventBP_SprintStateChanged_Parms*)Obj)->bSprinting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSprinting;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_SprintStateChanged constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_SprintStateChanged Property Definitions ****************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSprinting = { "bSprinting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(HorrorUI_eventBP_SprintStateChanged_Parms), &UHT_STATICS::NewProp_bSprinting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSprinting,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_SprintStateChanged Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UHorrorUI, nullptr, "BP_SprintStateChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<HorrorUI_eventBP_SprintStateChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(HorrorUI_eventBP_SprintStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHorrorUI_BP_SprintStateChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class UHorrorUI Function BP_SprintStateChanged ***********************************

// ********** Begin Class UHorrorUI Function OnSprintMeterUpdated **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UHorrorUI_OnSprintMeterUpdated_Statics
struct UHT_STATICS
{
	struct HorrorUI_eventOnSprintMeterUpdated_Parms
	{
		float Percent;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called when the character's sprint meter is updated */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/UI/HorrorUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the character's sprint meter is updated" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnSprintMeterUpdated constinit property declarations ******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Percent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnSprintMeterUpdated constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnSprintMeterUpdated Property Definitions *****************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Percent = { "Percent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(HorrorUI_eventOnSprintMeterUpdated_Parms, Percent), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Percent,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function OnSprintMeterUpdated Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UHorrorUI, nullptr, "OnSprintMeterUpdated", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::HorrorUI_eventOnSprintMeterUpdated_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::HorrorUI_eventOnSprintMeterUpdated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHorrorUI_OnSprintMeterUpdated(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UHorrorUI::execOnSprintMeterUpdated)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Percent);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnSprintMeterUpdated(Z_Param_Percent);
	P_NATIVE_END;
}
// ********** End Class UHorrorUI Function OnSprintMeterUpdated ************************************

// ********** Begin Class UHorrorUI Function OnSprintStateChanged **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UHorrorUI_OnSprintStateChanged_Statics
struct UHT_STATICS
{
	struct HorrorUI_eventOnSprintStateChanged_Parms
	{
		bool bSprinting;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called when the character's sprint state changes */" },
#endif
		{ "ModuleRelativePath", "Variant_Horror/UI/HorrorUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the character's sprint state changes" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnSprintStateChanged constinit property declarations ******************
	static void NewProp_bSprinting_SetBit(void* Obj)
	{
		((HorrorUI_eventOnSprintStateChanged_Parms*)Obj)->bSprinting = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSprinting;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnSprintStateChanged constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnSprintStateChanged Property Definitions *****************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSprinting = { "bSprinting", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(HorrorUI_eventOnSprintStateChanged_Parms), &UHT_STATICS::NewProp_bSprinting_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSprinting,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function OnSprintStateChanged Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UHorrorUI, nullptr, "OnSprintStateChanged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::HorrorUI_eventOnSprintStateChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::HorrorUI_eventOnSprintStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHorrorUI_OnSprintStateChanged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UHorrorUI::execOnSprintStateChanged)
{
	P_GET_UBOOL(Z_Param_bSprinting);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnSprintStateChanged(Z_Param_bSprinting);
	P_NATIVE_END;
}
// ********** End Class UHorrorUI Function OnSprintStateChanged ************************************

// ********** Begin Class UHorrorUI ****************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UHorrorUI_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple UI for a first person horror game\n *  Manages character sprint meter display\n */" },
#endif
		{ "IncludePath", "Variant_Horror/UI/HorrorUI.h" },
		{ "ModuleRelativePath", "Variant_Horror/UI/HorrorUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple UI for a first person horror game\nManages character sprint meter display" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UHorrorUI constinit property declarations ********************************
// ********** End Class UHorrorUI constinit property declarations **********************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnSprintMeterUpdated"), .Pointer = &UHorrorUI::execOnSprintMeterUpdated },
		{ .NameUTF8 = UTF8TEXT("OnSprintStateChanged"), .Pointer = &UHorrorUI::execOnSprintStateChanged },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UHorrorUI_BP_SprintMeterUpdated, "BP_SprintMeterUpdated" }, // ac4be0f4902891095851c8efe90a784e47438df1
		{ &Z_Construct_UFunction_UHorrorUI_BP_SprintStateChanged, "BP_SprintStateChanged" }, // 935fd641ecae21ec1bb4810e5db2c18883f10d1d
		{ &Z_Construct_UFunction_UHorrorUI_OnSprintMeterUpdated, "OnSprintMeterUpdated" }, // 4e924d60a707b99f05b23475f73be475f27bb3d9
		{ &Z_Construct_UFunction_UHorrorUI_OnSprintStateChanged, "OnSprintStateChanged" }, // c8e2b61960730a79d0520737a38264c3c9b45713
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHorrorUI>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UHorrorUI,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x00B010A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UHorrorUI_StaticRegisterNativesUHorrorUI()
{
	UClass* Class = UHorrorUI::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UHorrorUI;
UClass* Z_Construct_UClass_UHorrorUI(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UHorrorUI;
		if (!Z_Registration_Info_UClass_UHorrorUI.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("HorrorUI"),
				Z_Registration_Info_UClass_UHorrorUI.InnerSingleton,
				UHorrorUI_StaticRegisterNativesUHorrorUI,
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
		return Z_Registration_Info_UClass_UHorrorUI.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UHorrorUI.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHorrorUI.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UHorrorUI.OuterSingleton;
}
#undef UHT_STATICS
UHorrorUI::UHorrorUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UHorrorUI);
UHorrorUI::~UHorrorUI() {}
// ********** End Class UHorrorUI ******************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Horror_UI_HorrorUI_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHorrorUI, TEXT("UHorrorUI"), &Z_Registration_Info_UClass_UHorrorUI, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHorrorUI), 2066845875U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Horror_UI_HorrorUI_h__Script_ProjectEX_fa73848ef5e7bd9b32fbcff1c866b8c107632a0e{
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
