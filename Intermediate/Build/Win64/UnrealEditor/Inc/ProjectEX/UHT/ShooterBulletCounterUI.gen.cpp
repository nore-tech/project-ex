// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShooterBulletCounterUI.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeShooterBulletCounterUI() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_UShooterBulletCounterUI(ETypeConstructPhase);
PROJECTEX_API UClass* Z_Construct_UClass_UShooterBulletCounterUI(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UShooterBulletCounterUI Function BP_Damaged ******************************
struct ShooterBulletCounterUI_eventBP_Damaged_Parms
{
	float LifePercent;
};
static FName NAME_UShooterBulletCounterUI_BP_Damaged = FName(TEXT("BP_Damaged"));
void UShooterBulletCounterUI::BP_Damaged(float LifePercent)
{
	ShooterBulletCounterUI_eventBP_Damaged_Parms Parms;
	Parms.LifePercent=LifePercent;
	UFunction* Func = FindFunctionChecked(NAME_UShooterBulletCounterUI_BP_Damaged);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UShooterBulletCounterUI_BP_Damaged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Allows Blueprint to update sub-widgets with the new life total and play a damage effect on the HUD */" },
#endif
		{ "DisplayName", "Damaged" },
		{ "ModuleRelativePath", "Variant_Shooter/UI/ShooterBulletCounterUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Allows Blueprint to update sub-widgets with the new life total and play a damage effect on the HUD" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_Damaged constinit property declarations ****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LifePercent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_Damaged constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_Damaged Property Definitions ***************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LifePercent = { "LifePercent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ShooterBulletCounterUI_eventBP_Damaged_Parms, LifePercent), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LifePercent,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_Damaged Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UShooterBulletCounterUI, nullptr, "BP_Damaged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<ShooterBulletCounterUI_eventBP_Damaged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(ShooterBulletCounterUI_eventBP_Damaged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UShooterBulletCounterUI_BP_Damaged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class UShooterBulletCounterUI Function BP_Damaged ********************************

// ********** Begin Class UShooterBulletCounterUI Function BP_UpdateBulletCounter ******************
struct ShooterBulletCounterUI_eventBP_UpdateBulletCounter_Parms
{
	int32 MagazineSize;
	int32 BulletCount;
};
static FName NAME_UShooterBulletCounterUI_BP_UpdateBulletCounter = FName(TEXT("BP_UpdateBulletCounter"));
void UShooterBulletCounterUI::BP_UpdateBulletCounter(int32 MagazineSize, int32 BulletCount)
{
	ShooterBulletCounterUI_eventBP_UpdateBulletCounter_Parms Parms;
	Parms.MagazineSize=MagazineSize;
	Parms.BulletCount=BulletCount;
	UFunction* Func = FindFunctionChecked(NAME_UShooterBulletCounterUI_BP_UpdateBulletCounter);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UShooterBulletCounterUI_BP_UpdateBulletCounter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Shooter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Allows Blueprint to update sub-widgets with the new bullet count */" },
#endif
		{ "DisplayName", "UpdateBulletCounter" },
		{ "ModuleRelativePath", "Variant_Shooter/UI/ShooterBulletCounterUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Allows Blueprint to update sub-widgets with the new bullet count" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_UpdateBulletCounter constinit property declarations ****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MagazineSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BulletCount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_UpdateBulletCounter constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_UpdateBulletCounter Property Definitions ***************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MagazineSize = { "MagazineSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ShooterBulletCounterUI_eventBP_UpdateBulletCounter_Parms, MagazineSize), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_BulletCount = { "BulletCount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ShooterBulletCounterUI_eventBP_UpdateBulletCounter_Parms, BulletCount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MagazineSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BulletCount,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_UpdateBulletCounter Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UShooterBulletCounterUI, nullptr, "BP_UpdateBulletCounter", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<ShooterBulletCounterUI_eventBP_UpdateBulletCounter_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(ShooterBulletCounterUI_eventBP_UpdateBulletCounter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UShooterBulletCounterUI_BP_UpdateBulletCounter(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class UShooterBulletCounterUI Function BP_UpdateBulletCounter ********************

// ********** Begin Class UShooterBulletCounterUI **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UShooterBulletCounterUI_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple bullet counter UI widget for a first person shooter game\n */" },
#endif
		{ "IncludePath", "Variant_Shooter/UI/ShooterBulletCounterUI.h" },
		{ "ModuleRelativePath", "Variant_Shooter/UI/ShooterBulletCounterUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple bullet counter UI widget for a first person shooter game" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UShooterBulletCounterUI constinit property declarations ******************
// ********** End Class UShooterBulletCounterUI constinit property declarations ********************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UShooterBulletCounterUI_BP_Damaged, "BP_Damaged" }, // ace5553c16a40935a679f9b51f0bd1f94b703d60
		{ &Z_Construct_UFunction_UShooterBulletCounterUI_BP_UpdateBulletCounter, "BP_UpdateBulletCounter" }, // 50f87983d007e418b6814714d2c56656c05ff842
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UShooterBulletCounterUI>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_ProjectEX,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UShooterBulletCounterUI,
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
FClassRegistrationInfo Z_Registration_Info_UClass_UShooterBulletCounterUI;
UClass* Z_Construct_UClass_UShooterBulletCounterUI(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UShooterBulletCounterUI;
		if (!Z_Registration_Info_UClass_UShooterBulletCounterUI.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ShooterBulletCounterUI"),
				Z_Registration_Info_UClass_UShooterBulletCounterUI.InnerSingleton,
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
		return Z_Registration_Info_UClass_UShooterBulletCounterUI.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UShooterBulletCounterUI.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UShooterBulletCounterUI.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UShooterBulletCounterUI.OuterSingleton;
}
#undef UHT_STATICS
UShooterBulletCounterUI::UShooterBulletCounterUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UShooterBulletCounterUI);
UShooterBulletCounterUI::~UShooterBulletCounterUI() {}
// ********** End Class UShooterBulletCounterUI ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_UI_ShooterBulletCounterUI_h__Script_ProjectEX_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UShooterBulletCounterUI, TEXT("UShooterBulletCounterUI"), &Z_Registration_Info_UClass_UShooterBulletCounterUI, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UShooterBulletCounterUI), 2188070721U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_project_ex_Source_ProjectEX_Variant_Shooter_UI_ShooterBulletCounterUI_h__Script_ProjectEX_9967af8d608041eba828a24314383926351b3c5c{
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
