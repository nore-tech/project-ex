// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShooterUI.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeShooterUI() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_UShooterUI(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_UShooterUI(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UShooterUI Function BP_UpdateScore ***************************************
struct ShooterUI_eventBP_UpdateScore_Parms
{
	uint8 TeamByte;
	int32 Score;
};
static FName NAME_UShooterUI_BP_UpdateScore = FName(TEXT("BP_UpdateScore"));
void UShooterUI::BP_UpdateScore(uint8 TeamByte, int32 Score)
{
	ShooterUI_eventBP_UpdateScore_Parms Parms;
	Parms.TeamByte=TeamByte;
	Parms.Score=Score;
	UFunction* Func = FindFunctionChecked(NAME_UShooterUI_BP_UpdateScore);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UShooterUI_BP_UpdateScore_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Allows Blueprint to update score sub-widgets */" },
#endif
		{ "DisplayName", "Update Score" },
		{ "ModuleRelativePath", "Variant_Shooter/UI/ShooterUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Allows Blueprint to update score sub-widgets" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_UpdateScore constinit property declarations ************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_TeamByte;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Score;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_UpdateScore constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_UpdateScore Property Definitions ***********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_TeamByte = { "TeamByte", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(ShooterUI_eventBP_UpdateScore_Parms, TeamByte), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Score = { "Score", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ShooterUI_eventBP_UpdateScore_Parms, Score), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TeamByte,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Score,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_UpdateScore Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UShooterUI, nullptr, "BP_UpdateScore", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<ShooterUI_eventBP_UpdateScore_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(ShooterUI_eventBP_UpdateScore_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UShooterUI_BP_UpdateScore(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class UShooterUI Function BP_UpdateScore *****************************************

// ********** Begin Class UShooterUI ***************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UShooterUI_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple scoreboard UI for a first person shooter game\n */" },
#endif
		{ "IncludePath", "Variant_Shooter/UI/ShooterUI.h" },
		{ "ModuleRelativePath", "Variant_Shooter/UI/ShooterUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple scoreboard UI for a first person shooter game" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UShooterUI constinit property declarations *******************************
// ********** End Class UShooterUI constinit property declarations *********************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UShooterUI_BP_UpdateScore, "BP_UpdateScore" }, // 620a6559e6154fb8297629f6f9c565c75a6fbfbf
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UShooterUI>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UShooterUI,
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
FClassRegistrationInfo Z_Registration_Info_UClass_UShooterUI;
UClass* Z_Construct_UClass_UShooterUI(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UShooterUI;
		if (!Z_Registration_Info_UClass_UShooterUI.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ShooterUI"),
				Z_Registration_Info_UClass_UShooterUI.InnerSingleton,
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
		return Z_Registration_Info_UClass_UShooterUI.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UShooterUI.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UShooterUI.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UShooterUI.OuterSingleton;
}
#undef UHT_STATICS
UShooterUI::UShooterUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UShooterUI);
UShooterUI::~UShooterUI() {}
// ********** End Class UShooterUI *****************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_UI_ShooterUI_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UShooterUI, TEXT("UShooterUI"), &Z_Registration_Info_UClass_UShooterUI, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UShooterUI), 4247313729U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_UI_ShooterUI_h__Script_ProjectEX_0760b66a571c49d2af46f4a7ee0af31651593282{
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
