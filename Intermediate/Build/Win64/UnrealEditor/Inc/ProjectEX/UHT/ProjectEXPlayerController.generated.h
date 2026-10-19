// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ProjectEXPlayerController.h"

#ifdef PROJECTEX_ProjectEXPlayerController_generated_h
#error "ProjectEXPlayerController.generated.h already included, missing '#pragma once' in ProjectEXPlayerController.h"
#endif
#define PROJECTEX_ProjectEXPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AProjectEXPlayerController ***********************************************
struct Z_Construct_UClass_AProjectEXPlayerController_Statics;
PROJECTEX_API UClass* Z_Construct_UClass_AProjectEXPlayerController(ETypeConstructPhase);

#define FID_project_ex_Source_ProjectEX_ProjectEXPlayerController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_AProjectEXPlayerController_Statics; \
	friend PROJECTEX_API UClass* ::Z_Construct_UClass_AProjectEXPlayerController(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(AProjectEXPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectEX"), Z_Construct_UClass_AProjectEXPlayerController) \
	DECLARE_SERIALIZER(AProjectEXPlayerController)


#define FID_project_ex_Source_ProjectEX_ProjectEXPlayerController_h_20_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AProjectEXPlayerController(AProjectEXPlayerController&&) = delete; \
	AProjectEXPlayerController(const AProjectEXPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectEXPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectEXPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AProjectEXPlayerController) \
	NO_API virtual ~AProjectEXPlayerController();


#define FID_project_ex_Source_ProjectEX_ProjectEXPlayerController_h_17_PROLOG
#define FID_project_ex_Source_ProjectEX_ProjectEXPlayerController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_project_ex_Source_ProjectEX_ProjectEXPlayerController_h_20_INCLASS_NO_PURE_DECLS \
	FID_project_ex_Source_ProjectEX_ProjectEXPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AProjectEXPlayerController;

// ********** End Class AProjectEXPlayerController *************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_project_ex_Source_ProjectEX_ProjectEXPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
