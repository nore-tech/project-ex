// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Shooter/Weapons/ShooterWeapon.h"

#ifdef PROJECTEX_ShooterWeapon_generated_h
#error "ShooterWeapon.generated.h already included, missing '#pragma once' in ShooterWeapon.h"
#endif
#define PROJECTEX_ShooterWeapon_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class USkeletalMeshComponent;

// ********** Begin Class AShooterWeapon ***********************************************************
#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetThirdPersonMesh); \
	DECLARE_FUNCTION(execGetFirstPersonMesh); \
	DECLARE_FUNCTION(execOnOwnerDestroyed);


struct Z_Construct_UClass_AShooterWeapon_Statics;
PROJECTEX_API UClass* Z_Construct_UClass_AShooterWeapon(ETypeConstructPhase);

#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h_26_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_AShooterWeapon_Statics; \
	friend PROJECTEX_API UClass* ::Z_Construct_UClass_AShooterWeapon(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(AShooterWeapon, AActor, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectEX"), Z_Construct_UClass_AShooterWeapon) \
	DECLARE_SERIALIZER(AShooterWeapon)


#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h_26_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AShooterWeapon(AShooterWeapon&&) = delete; \
	AShooterWeapon(const AShooterWeapon&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShooterWeapon); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShooterWeapon); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AShooterWeapon) \
	NO_API virtual ~AShooterWeapon();


#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h_23_PROLOG
#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h_26_INCLASS_NO_PURE_DECLS \
	FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AShooterWeapon;

// ********** End Class AShooterWeapon *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeapon_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
