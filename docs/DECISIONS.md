# Decisions

## Engine

- Unreal Engine 5.8.

## Architecture

- C++ handles core gameplay systems.
- Blueprints handle configuration and presentation.
- Server-authoritative multiplayer gameplay.
- Reuse existing Unreal Engine systems.
- Avoid unnecessary custom implementations.

## Inventory

- Grid-based inventory.
- Drag-and-drop is the primary interaction.
- Item rotation is supported.
- Stackable ammunition.
- No physical magazine inventory system.
- Equipment uses dedicated slots: `PrimaryWeapon`, `SecondaryWeapon`, `Helmet`, `BodyArmor`, `Backpack`.
- TAB opens character inventory.
- Searching a container opens a third panel.
- Shift-click quick-transfers items.
- Ctrl-click quick-equips compatible items into an empty slot.
- Right-click provides contextual item actions.
- Double-click uses a consumable, otherwise equips an empty compatible slot, otherwise transfers when a container is open.

## Weapons

- Weapon configuration should be Blueprint-editable through `UProjectEXWeaponData`.
- Weapon meshes and offsets should be configurable on that data asset.
- Gameplay authority remains in C++ (`UProjectEXWeaponComponent`).
- Cosmetic presentation can use Blueprints (`OnWeaponFired`, `OnWeaponReloaded`).
- There is no separate weapon actor.

## Level design

- Levels are primarily designed manually.
- Do not procedurally generate maps unless requested.
- Do not modify lighting without explicit instruction.
- Reusable gameplay actors (`AProjectEXPickup`, `AProjectEXLootContainer`, `AProjectEXTargetDummy`) should be placeable in existing levels.

## Development

- Preserve existing working systems.
- Prefer targeted changes over broad rewrites.
- Minimize AI context and token consumption.
- Do not assume unverified systems are functional.
- Source code overrides documentation when they disagree.
- Stay on `main`.
