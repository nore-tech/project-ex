// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Horror/HorrorCharacter.h"

#ifdef PROJECTEX_HorrorCharacter_generated_h
#error "HorrorCharacter.generated.h already included, missing '#pragma once' in HorrorCharacter.h"
#endif
#define PROJECTEX_HorrorCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AHorrorCharacter *********************************************************
#define FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoEndSprint); \
	DECLARE_FUNCTION(execDoStartSprint);


struct Z_Construct_UClass_AHorrorCharacter_Statics;
PROJECTEX_API UClass* Z_Construct_UClass_AHorrorCharacter(ETypeConstructPhase);

#define FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h_22_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_AHorrorCharacter_Statics; \
	friend PROJECTEX_API UClass* ::Z_Construct_UClass_AHorrorCharacter(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(AHorrorCharacter, AProjectEXCharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectEX"), Z_Construct_UClass_AHorrorCharacter) \
	DECLARE_SERIALIZER(AHorrorCharacter)


#define FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h_22_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AHorrorCharacter(AHorrorCharacter&&) = delete; \
	AHorrorCharacter(const AHorrorCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AHorrorCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AHorrorCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AHorrorCharacter) \
	NO_API virtual ~AHorrorCharacter();


#define FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h_19_PROLOG
#define FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h_22_INCLASS_NO_PURE_DECLS \
	FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AHorrorCharacter;

// ********** End Class AHorrorCharacter ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_project_ex_Source_ProjectEX_Variant_Horror_HorrorCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
