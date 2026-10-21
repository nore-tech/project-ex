# Blueprint setup

No Blueprint assets are created by this document. Create them in the editor.

## Blueprint-ready classes

| Class | Kind | Subclass |
| --- | --- | --- |
| `UProjectEXWeaponData` | Data asset | Yes. Stats and first-person pose. |
| `UProjectEXWeaponItemDefinition` | Data asset | Yes. Inventory item pointing at weapon data. |
| `UProjectEXItemDefinition` | Data asset | Yes. Items, ammo, equipment, medical. |
| `AProjectEXPickup` | Actor | Yes. |
| `AProjectEXLootContainer` | Actor | Yes. |
| `AProjectEXTargetDummy` | Actor | Yes. |
| `AProjectEXCharacter` | Character | Yes. The C++ class is abstract. |
| `UProjectEXWeaponComponent` | Component | Yes. Required to implement weapon cosmetic events. |

There is no weapon actor. A firearm is `UProjectEXWeaponData` plus `UProjectEXWeaponItemDefinition`.

## Configurable properties

`UProjectEXWeaponData`: `Damage`, `FireInterval`, `MagazineSize`, `ReloadDuration`, `AmmoType`, `ViewMesh`, `ViewOffset`, `ViewRotation`, `RecoilPitch`, `RecoilYaw`. Also `ViewScale`, `AdsOffset`, `AdsRotation`, `SightOffset`, `MuzzleOffset`, `GripOffset`, `GripStyle`, `RightHandOffset`, `LeftHandOffset`.

`UProjectEXItemDefinition`: `DisplayName`, `WorldMesh`, `DisplaySkeletalMesh`, `EquipKind`, `HealAmount`, `MaxStackSize`, `GridWidth`, `GridHeight`.

`AProjectEXPickup`: `ItemDefinition`, `Quantity`, `StoredMagazine`, `Mesh`. Display name comes from `ItemDefinition.DisplayName`.

`AProjectEXLootContainer`: `ContainerName`, `GridColumns`, `GridRows`, `Mesh`. No loot-table property exists.

`UProjectEXInteractionComponent`: `InteractionRange` (default 250).

`AProjectEXCharacter`: `FallingBrakingDeceleration`, `AirControl`. Other movement values are on the inherited Character Movement component.

`UProjectEXHealthComponent`: `MaxHealth`, `HeadshotMultiplier`. Healing amount is `HealAmount` on the item, not on the component.

`AProjectEXTargetDummy`: `Health` component (`MaxHealth`). Interact calls `RestoreFullHealth`. No separate reset property.

Equipment slots are the enum `EProjectEXEquipmentSlot`: `PrimaryWeapon`, `SecondaryWeapon`, `Helmet`, `BodyArmor`, `Backpack`. There is no sidearm, melee, face, glasses, badge, or gadget slot.

## Blueprint events

Implement these on a Blueprint subclass. They do not change server rules.

- `UProjectEXWeaponComponent.OnWeaponFired` — after the server accepts a shot.
- `UProjectEXWeaponComponent.OnWeaponReloaded` — on the server after reserve ammo is consumed.
- `AProjectEXPickup.OnItemPickedUp` — server, after the stack is added, before the actor is destroyed.
- `AProjectEXLootContainer.OnContainerOpened` — server, when a pawn opens it.

Already present. Do not add duplicates:

- `UProjectEXHealthComponent.OnHealthChanged`, `OnDamageApplied`, `OnDied`
- `AProjectEXLootContainer.OnContentsChanged`

The character Blueprint does not override component events. Subclass `UProjectEXWeaponComponent` and replace the character's Weapon component to use `OnWeaponFired` / `OnWeaponReloaded`.

## Rifle first-person pose

The equipped rifle reads `BP_EX_Rifle`. That Blueprint is not placed in the level. Its root is the camera. `DA_RifleData.PresentationRig` points at it, and the rifle pickup uses `DA_RifleData`.

1. Open `/Game/ProjectEX/Blueprints/BP_EX_Rifle`.
2. Select `HipFireAnchor`. The rifle mesh is attached to it. Move and rotate that anchor. This is hip-fire.
3. Select `ADSAnchor`. Move it until the rear and front sights line up with `AimMarker`, which sits on the camera aim line. This is aim-down-sights.
4. Compile and save.
5. Play `Lvl_FirstPerson`, pick up the rifle, equip it, and hold right mouse to aim.

`ViewOffset` on the data asset does not move this rifle. The anchors do. Aim field of view, transition time, and look sensitivity are `AdsFOV`, `AdsTransitionDuration`, and `AdsLookScale` on `DA_RifleData`.

The pistol has no rig. It still uses the older hand pose.

## BP_LootContainer

Blueprint Class → `ProjectEXLootContainer`. Set `ContainerName`, `GridColumns`, `GridRows`, and the `Mesh` component to an existing static mesh. Place it in a level. There is no loot table; add items with the container's server `AddItem` path or an already authored instance.
