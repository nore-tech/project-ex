// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ProjectEXGameMode.h"

#ifdef PROJECTEX_ProjectEXGameMode_generated_h
#error "ProjectEXGameMode.generated.h already included, missing '#pragma once' in ProjectEXGameMode.h"
#endif
#define PROJECTEX_ProjectEXGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AProjectEXGameMode *******************************************************
struct Z_Construct_UClass_AProjectEXGameMode_Statics;
PROJECTEX_API UClass* Z_Construct_UClass_AProjectEXGameMode(ETypeConstructPhase);

#define FID_project_ex_Source_ProjectEX_ProjectEXGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_AProjectEXGameMode_Statics; \
	friend PROJECTEX_API UClass* ::Z_Construct_UClass_AProjectEXGameMode(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(AProjectEXGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectEX"), Z_Construct_UClass_AProjectEXGameMode) \
	DECLARE_SERIALIZER(AProjectEXGameMode)


#define FID_project_ex_Source_ProjectEX_ProjectEXGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AProjectEXGameMode(AProjectEXGameMode&&) = delete; \
	AProjectEXGameMode(const AProjectEXGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectEXGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectEXGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AProjectEXGameMode) \
	NO_API virtual ~AProjectEXGameMode();


#define FID_project_ex_Source_ProjectEX_ProjectEXGameMode_h_12_PROLOG
#define FID_project_ex_Source_ProjectEX_ProjectEXGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_project_ex_Source_ProjectEX_ProjectEXGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_project_ex_Source_ProjectEX_ProjectEXGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AProjectEXGameMode;

// ********** End Class AProjectEXGameMode *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_project_ex_Source_ProjectEX_ProjectEXGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
