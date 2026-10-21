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

## Raid loop (Milestone 2)

- Raid status lives on `AProjectEXPlayerController` (replicated): Preparing (3 s `DeployDelay`) → InRaid → Extracted or Dead. Enemies only target InRaid players. Kills, raid time, and extraction countdown replicate to the owner.
- `AProjectEXExtractionZone` (`Raid/`): server-timed countdown (default 10 s), radius, display name, color. Leaving cancels; re-entering restarts; dead players cannot extract; completion only from InRaid.
- `UProjectEXRaidWidget` (`Raid/`, native UMG): DEPLOYING banner, extraction countdown, red damage flash, EXTRACTED / KILLED IN ACTION panel with Deploy Again. Deploy Again reloads the level (standalone `OpenLevel`; listen server `ServerTravel` once nobody is in raid), so enemies, zones, and timers reset with no duplicates.
- Combat HUD: center crosshair plus hit marker (white hit, red kill) through `ClientConfirmHit`. Enemy label flashes white when hit.
- Enemies: `PatrolPoints` (relative, edit widgets), RVO avoidance, kill credit. Defaults: detection 1000, damage 8, cooldown 1.5.
- Navigation: `RuntimeGeneration=Dynamic` in DefaultEngine.ini plus `EX_Raid_NavBounds`. Verified the navmesh generates in game.
- Blueprints: `/Game/ProjectEX/Blueprints/BP_Enemy`, `BP_ExtractionZone`.
- Level (`Tools/setup_raid_encounter.py`, re-runnable): `EX_Raid_Enemy_A/B/C`, `EX_Raid_Extraction` at (-1000, -1000) "Southwest Exfil", `EX_Raid_NavBounds`, 5 Synty cover props. `EX_Enemy_01` was removed.
- Dev console: `RaidTeleport X Y` (standalone, non-shipping).
- Verified in game 2026-10-20: navmesh, patrol, detection, damage from several enemies, countdown start/cancel/restart, extraction success screen, death failure screen, Deploy Again after both, enemies stop after the player dies or extracts.
- Not verified this session: killing enemies with the rifle, hit marker, enemy ragdoll, listen-server play.
- Known: on the result screen the keyboard needs two presses (first focuses the button); a mouse click is the normal path.

## Enemy (Milestone 1)

- `AProjectEXEnemy` (`Combat/ProjectEXEnemy.h/.cpp`): ACharacter with `UProjectEXHealthComponent`, Synty dummy mesh plus `ThirdPerson_AnimBP`, and a "HOSTILE <hp>" text label. Settings: MaxHealth, MoveSpeed, DetectionRange, AttackRange, AttackDamage, AttackCooldown, PatrolRadius, CorpseLifetime. Its capsule blocks Visibility so player hitscan registers. On death: movement disabled, controller unpossessed, ragdoll (or tip-over without a physics asset), label "DEAD", destroyed after CorpseLifetime.
- `AProjectEXEnemyController` (`Combat/ProjectEXEnemyController.h/.cpp`): AIPerception sight plus close-range detection, MoveTo chase, melee damage on the server when in range with line of sight and the cooldown is ready, idle wander otherwise.
- The level has no NavMesh. Movement falls back to MoveTo without pathfinding, then direct steering.
- `EX_Enemy_01` was replaced by the Milestone 2 encounter. `Tools/place_enemy.py` is superseded by `Tools/setup_raid_encounter.py`.
- Verified in game 2026-10-20: the enemy chases and damages the player (health fell 100 → 10). Not observed: enemy death from player fire.

## Weapon presentation

- The equipped rifle mesh is a local component on the first-person camera. It is not a held actor and it is not attached to a socket.
- `BP_EX_Rifle` (`AProjectEXWeaponRig`) is the pose source. `HipFireAnchor` is hip-fire. `ADSAnchor` is iron-sight aim. `DA_RifleData.PresentationRig` points at that Blueprint, so the rifle pickup uses it.
- Hold right mouse to aim. The blend takes `AdsTransitionDuration` (0.18 s) either way. Aimed field of view is 75. Look scale is 0.75. Releasing, switching, unequipping, or dying leaves aim.
- Firing, ammo, and hitscan are unchanged. Aim does not move the capsule.
- Not verified in a played session after this change: the on-screen hip pose, sight alignment, firing while aimed, and reload. The running game could not be aimed reliably from this session.

## Focus

Playable raid loop: deploy, fight, extract or die, deploy again.

## Latest work

Milestone 2 raid loop (see above).

## Next task

Play a full raid by hand: kill all three enemies with the rifle, confirm the hit marker and enemy death visuals, then extract. Tune enemy damage and detection from `BP_Enemy` if needed.
