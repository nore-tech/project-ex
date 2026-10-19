// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectEX_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
	PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_BulletCountUpdatedDelegate__DelegateSignature(ETypeConstructPhase);
	PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_DamagedDelegate__DelegateSignature(ETypeConstructPhase);
	PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_PawnDeathDelegate__DelegateSignature(ETypeConstructPhase);
	PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_SprintStateChangedDelegate__DelegateSignature(ETypeConstructPhase);
	PROJECTEX_API UFunction* Z_Construct_UDelegateFunction_ProjectEX_UpdateSprintMeterDelegate__DelegateSignature(ETypeConstructPhase);
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_ProjectEX;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_ProjectEX(ETypeConstructPhase)
	{
		if (!Z_Registration_Info_UPackage__Script_ProjectEX.OuterSingleton)
		{
		static FTypeConstructFunc* SingletonFuncArray[] = {
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_ProjectEX_BulletCountUpdatedDelegate__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_ProjectEX_DamagedDelegate__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_ProjectEX_PawnDeathDelegate__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_ProjectEX_SprintStateChangedDelegate__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_ProjectEX_UpdateSprintMeterDelegate__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/ProjectEX",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000000,
			0x185F8643,
			0xE6519375,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_ProjectEX.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_ProjectEX.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_ProjectEX(Z_Construct_UPackage__Script_ProjectEX, TEXT("/Script/ProjectEX"), Z_Registration_Info_UPackage__Script_ProjectEX, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x185F8643, 0xE6519375));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
