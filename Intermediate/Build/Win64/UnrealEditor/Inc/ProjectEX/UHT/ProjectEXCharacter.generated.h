// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ProjectEXCharacter.h"

#ifdef PROJECTEX_ProjectEXCharacter_generated_h
#error "ProjectEXCharacter.generated.h already included, missing '#pragma once' in ProjectEXCharacter.h"
#endif
#define PROJECTEX_ProjectEXCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AProjectEXCharacter ******************************************************
#define FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoMove); \
	DECLARE_FUNCTION(execDoAim);


struct Z_Construct_UClass_AProjectEXCharacter_Statics;
PROJECTEX_API UClass* Z_Construct_UClass_AProjectEXCharacter(ETypeConstructPhase);

#define FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_AProjectEXCharacter_Statics; \
	friend PROJECTEX_API UClass* ::Z_Construct_UClass_AProjectEXCharacter(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(AProjectEXCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectEX"), Z_Construct_UClass_AProjectEXCharacter) \
	DECLARE_SERIALIZER(AProjectEXCharacter)


#define FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AProjectEXCharacter(AProjectEXCharacter&&) = delete; \
	AProjectEXCharacter(const AProjectEXCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectEXCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectEXCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AProjectEXCharacter) \
	NO_API virtual ~AProjectEXCharacter();


#define FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h_21_PROLOG
#define FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AProjectEXCharacter;

// ********** End Class AProjectEXCharacter ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_project_ex_Source_ProjectEX_ProjectEXCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
