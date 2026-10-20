# Project state

Last updated: 2026-10-20

## Status

Unreal Engine 5.8 PvE extraction shooter. C++ owns gameplay. Native UMG owns the inventory. Listen-server co-op is the intended network model. Stay on `main`.

## Verified

Confirmed in a launched 1920×1080 game session on 2026-10-20:

- Tab opens and closes the inventory.
- The character column and pocket grid are visible. The container column stays hidden when nothing is being searched.
- Picking up a world rifle with F adds it to the pocket grid (8 of 60 cells).
- Double-click equips that rifle into Primary 1. The slot showed "Rifle 30" and the HUD showed Rifle 30/30.

The display used for that session was 1920×1080 only.

## Implemented

Code exists. Gameplay beyond the list above was not verified in that session:

- Server-authoritative hitscan fire, reload, recoil, ammo consumption.
- First-person sway, bob, aim, and procedural reload presentation.
- Grid drag, rotate, shift-transfer, ctrl-equip, right-click menu.
- Searchable containers (`AProjectEXLootContainer`, default 6×4) and loot transfer RPCs.
- Health, `HealAmount` items, and `AProjectEXTargetDummy` reset through interact.
- `AProjectEXDamagePad`.
- Equipment slots: Primary, Secondary, Helmet, Body Armor, Backpack.
- Blueprint configuration surface added 2026-10-20. See `docs/BLUEPRINT_SETUP.md`. Not exercised in editor Blueprint assets. No `.uasset` Blueprints were created.

## Incomplete

- Face mask, glasses, badge, sidearm, melee, gadgets, tactical-rig grid, and backpack grid have no backend. The inventory UI draws them as labels only.
- No loot table on containers.
- Nested container inventories are not implemented.
- `OnWeaponReloaded` runs on the server after ammo is consumed. A remote client does not receive that cosmetic event.
- Drag, rotate, shift-click, ctrl-click, right-click, and container search were not retested in the 2026-10-20 session.

## Focus

Core player movement and interactions. Do not start extraction, AI, traders, or new equipment slots unless asked.

## Latest work

Blueprint subclassing and cosmetic events on existing classes. Persistent docs: `docs/PROJECT_STATE.md`, `docs/DECISIONS.md`, `docs/CODEBASE_MAP.md`, `docs/BLUEPRINT_SETUP.md`.

## Next task

In the editor, create `BP_Rifle`, `BP_Pistol`, and `BP_LootContainer` using `docs/BLUEPRINT_SETUP.md`. Confirm the existing Synty meshes and first-person offsets on those assets. Do not change the test level unless asked.
