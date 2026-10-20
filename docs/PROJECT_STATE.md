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

## Enemy (Milestone 1)

- `AProjectEXEnemy` (`Combat/ProjectEXEnemy.h/.cpp`): ACharacter with `UProjectEXHealthComponent`, Synty dummy mesh plus `ThirdPerson_AnimBP`, and a "HOSTILE <hp>" text label. Settings: MaxHealth, MoveSpeed, DetectionRange, AttackRange, AttackDamage, AttackCooldown, PatrolRadius, CorpseLifetime. Its capsule blocks Visibility so player hitscan registers. On death: movement disabled, controller unpossessed, ragdoll (or tip-over without a physics asset), label "DEAD", destroyed after CorpseLifetime.
- `AProjectEXEnemyController` (`Combat/ProjectEXEnemyController.h/.cpp`): AIPerception sight plus close-range detection, MoveTo chase, melee damage on the server when in range with line of sight and the cooldown is ready, idle wander otherwise.
- The level has no NavMesh. Movement falls back to MoveTo without pathfinding, then direct steering.
- `EX_Enemy_01` is placed in Lvl_FirstPerson at (1000, 0, 302) by `Tools/place_enemy.py`.
- Verified in game 2026-10-20: the enemy chases and damages the player (health fell 100 → 10). Not observed: enemy death from player fire.

## Focus

Core player movement and interactions, plus the Milestone 1 enemy.

## Latest work

Milestone 1 enemy (see above).

## Next task

Verify in PIE that shooting `EX_Enemy_01` kills it and that its ragdoll or tip-over is visible. Optionally add a NavMeshBoundsVolume for pathed chasing around obstacles.
