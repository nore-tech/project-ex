// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Shooter/Weapons/ShooterWeaponHolder.h"

#ifdef PROJECTEX_ShooterWeaponHolder_generated_h
#error "ShooterWeaponHolder.generated.h already included, missing '#pragma once' in ShooterWeaponHolder.h"
#endif
#define PROJECTEX_ShooterWeaponHolder_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Interface UShooterWeaponHolder *************************************************
struct Z_Construct_UClass_UShooterWeaponHolder_Statics;
PROJECTEX_API UClass* Z_Construct_UClass_UShooterWeaponHolder(ETypeConstructPhase);

#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	PROJECTEX_API UShooterWeaponHolder(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UShooterWeaponHolder(UShooterWeaponHolder&&) = delete; \
	UShooterWeaponHolder(const UShooterWeaponHolder&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(PROJECTEX_API, UShooterWeaponHolder); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UShooterWeaponHolder); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UShooterWeaponHolder) \
	virtual ~UShooterWeaponHolder() = default;


#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_17_GENERATED_UINTERFACE_BODY() \
private: \
	friend struct ::Z_Construct_UClass_UShooterWeaponHolder_Statics; \
	friend PROJECTEX_API UClass* ::Z_Construct_UClass_UShooterWeaponHolder(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UShooterWeaponHolder, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/ProjectEX"), Z_Construct_UClass_UShooterWeaponHolder) \
	DECLARE_SERIALIZER(UShooterWeaponHolder)


#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_17_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_17_GENERATED_UINTERFACE_BODY() \
	FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_17_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_17_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IShooterWeaponHolder() {} \
public: \
	typedef UShooterWeaponHolder UClassType; \
	typedef IShooterWeaponHolder ThisClass; \
	[[deprecated("Do not call _getUObject(), use Cast.")]] virtual UObject* _getUObject() const { return nullptr; }


#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_14_PROLOG
#define FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h_17_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UShooterWeaponHolder;

// ********** End Interface UShooterWeaponHolder ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_project_ex_Source_ProjectEX_Variant_Shooter_Weapons_ShooterWeaponHolder_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
