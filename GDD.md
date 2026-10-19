GAME DESIGN DOCUMENT

Project: Project EX

Engine: Unreal Engine 5
Genre: First-Person PvE Extraction Shooter
Players: 1–3 (Solo / Cooperative)
Art Style: Low-Poly

I want this to be DARK, maybe horror adjacent? I want the vibe to be unique, I love the cult stuff in tarkov. I love games that do a modern crossover with fantasy/cryptid/horror. SCP stuff, but I dont know the SCP copy pasta slop. 

⸻

1. Game Overview

1.1 Concept

A first-person PvE extraction shooter focused on challenging combat, meaningful looting, persistent progression, and dynamic AI encounters.

Players enter instanced raids alone or with friends, complete objectives, acquire equipment, and attempt to extract alive.

The world features multiple AI factions that interact and fight independently of the player.

1.2 Design Pillars

High-Stakes Extraction

* Death results in losing equipment carried into the raid.
* Successful extraction preserves acquired loot.
* Alternative extraction methods reward progression and preparation.

Living PvE World

* Multiple AI factions with distinct behaviors.
* AI factions interact and fight independently.
* Random raid events modify enemy populations, loot, and environmental conditions.

Meaningful Progression

* Players begin with basic equipment.
* Better equipment becomes available through looting, traders, and quests.
* Progression unlocks additional maps, opportunities, and extraction options.

Player-Friendly Complexity

* Deep inventory and equipment systems.
* Quality-of-life features reduce unnecessary inventory management.
* Complex mechanics should provide meaningful gameplay rather than artificial inconvenience.

1.3 Inspirations

* Escape from Tarkov
* SurrounDead
* Deadline Escape
* The Division (1&2)
* Mad Max Movies
* Literally I love this stuff, but I've grown and realized zombies are contrived and saturated. 

1.4 Unique Selling Points

* [What makes this different from other extraction shooters?]
    Low barrier to entry, consistent development, Coop, PVE only to start. Unique world/systems. TBD really. 
* [What experience should players remember?]
    I want there to be a challenge, they should remember what it was like to tackle a challenge with a friend, or a particular cool piece of loot that they got. I think I really like reds from chinese looter games. 
* [Why would someone choose this over existing games?]
  Idk man. 

⸻

2. Core Gameplay Loop

2.1 Primary Loop

1. Prepare equipment and weapons.
2. Obtain Quests (Could be dailies and weeklys)
3. Select a map and enter a raid.
4. Explore, loot, fight, and complete objectives.
5. Locate and reach an extraction point.
6. Complete any extraction requirements.
7. Extract successfully or die.
8. Manage acquired loot and equipment.
9. Visit traders, complete quests, and upgrade equipment.
10. Repeat.

2.2 Raid Structure

Raid Duration: Per Map
Player Count: 1–3
Map Size: Small initially, expanding to larger maps
Respawning: Disabled
Death Penalty: Loss of carried equipment, except "safe" methods

Questions to Resolve:

* Are raids time-limited?
    Yes
* Can players enter raids at different times of day?
    a single rotating clock to keep time for all the world. 
* Are weather conditions randomized?
  Yes and can be tied to events
* Can players leave raids early?
  After 5 minutes they can leave. 
* Does every map have multiple extraction points?
  Some do, but I might make a linear map. 

⸻

3. Player Movement & Combat

3.1 Movement

* Walking
* Sprinting
* Crouching
* Prone
* Leaning (MUST, IF YOU GAME IS FPS YOU NEED LEANING DUDE)
* Jumping
* [Vaulting / Mantling]
* Sliding, but how to not make this crazy

3.2 Weapon Systems

* Firearms with different handling characteristics.
* Weapon attachments and customization.
* Ammunition management.
* Reloading and magazine management.
* Weapon durability: Yes
* Weapon malfunctions: I mean yeah but how


3.3 Damage & Health

* Player health system: Yes
* Individual body-part damage: I wish, not sure how. 
* Armor and penetration mechanics: Math or something, idk maybe a flat 4>3 = 100% damage and 3>4 = 70% damage or something.
* Healing and medical items: I think Bleeds, splints, surgery?, medkits of diff levels, stims? Crafting in raid? Probably not.
* Injury mechanics: TBD

3.4 Combat Philosophy

Combat should feel good, smooth like a call of duty, however, recoil should matter, attachements and weight should affect how fast you aim. You should be able to lean annd hold an angle for Ai to walk into. Flash grenades can blind you, grenades etc. A good mix of tatical with also being able to do crazy fast fun movement/shooting, but if you make a positioning mistake you can get got. Headshots should feel REALLY good somehow. 

⸻

4. Inventory & Equipment

4.1 Inventory System

Grid-based inventory with items occupying different amounts of space.

Planned Features:

* Drag-and-drop inventory.
* Rotatable items.
* Equipment slots.
* Backpacks and containers.
* Search functionality.
* Sorting and filtering.
* Automatic sorting.
* Pop-out sorting table.
* Item stacking.
* Context menus.
* Automatically Moving items to fill empty slots if you try and drag something on top. 

4.2 Storage Cases

Specialized containers for organizing equipment.

Examples:

* Weapon cases.
* Ammunition cases.
* Medical cases.
* General storage cases.
* BIG VERSION of cases
* Key case
* Badge (like dogtags) case
* Attachement storage?
* What about gear storage? Backpack/presets?

Questions:

* Can cases be taken into raids? SOME not all. 
* Are cases restricted to certain item categories? YES. 
* Can players upgrade stash capacity? Should be quest rewards and/or levels/cost. 

4.3 Equipment Slots

* Primary weapon
* Secondary weapon
* Sidearm
* Headwear
* Body armor
* Tactical rig
* Backpack
* Pockets
* Secure Pouch Slot
* Slots for "special" things like compass, map etc. 

4.4 Inventory Quality of Life

EHHHH, I will come up with this as I play test. Im so picky. 

⸻

5. Maps & Environments

5.1 Map Progression

Maps progressively increase in difficulty, enemy equipment quality, and potential rewards.

Earlier maps remain accessible and relevant. Maybe rare keys that have crazy loot in them? Bosses drop rare keys? 

5.2 Planned Maps

Map 1: Town Of Sunnyside

* Theme: Small Remote Town, maybe kinda western, cabin in the woods. Core town space, with some outbuildings, a main road. Not easy to get lost. 
* Size: Small
* Difficulty: Beginner
* Factions: Fanatics, Enemy Survivors
* Points of Interest: Bank, Sherriff station, general store
* Extractions: End of the road big baracade, boat on the coast or something, a car that can be in the woods but is conditional 
* Unique Mechanics: Nothing, No dangers outside of the core game. 

Map 2: Happy Acres Statepark

* Theme: Scary forest, big center focus of a church with outbuildings, small cabins dotted, campsites, moonshine place maybe
* Size: Medium
* Difficulty: Intermediate
* Factions: Fanatics, Cultists, Enemy survivors
* Points of Interest: Church, Bunker/Basement Scary, Hillbilly trailer/Moonshine Place
* Extractions: ATV randomly available, plane?, idk tbd.

Future Maps
More Town, maybe a mall/warehouse that is part of the town, some major plot point that keeps the town alive but was actually the bad guys place
A big CITY
A BIG Hospital or asylum or something
Farm?

5.3 Environmental Design

* Explorable interiors.
* Meaningful cover.
* Multiple routes through major locations.
* High-risk, high-reward loot areas.
* Environmental storytelling.

⸻

6. Extraction System

6.1 Standard Extractions

Regular extraction points should involve some level of risk or challenge.

Possible mechanics:

* Clearing hostile enemies.
* Defending an extraction location.
* Waiting for transportation.
* Activating equipment.
* Holding a position.

6.2 Alternative Extractions

Additional extraction options unlocked through preparation or progression.

Possible requirements:

* Keys.
* Trader reputation.
* Quest completion.
* Special equipment.
* Map-specific objectives.

6.3 Extraction Design Philosophy

Alternative extractions should reward preparation and progression by offering different or safer escape opportunities.

Not every extraction should require identical mechanics.

6.4 Open Questions

* Are extraction locations randomized?
* Can extractions become unavailable?
* Can AI interrupt extraction?
* Do extraction requirements scale with squad size?

⸻

7. AI & Factions

7.1 AI Philosophy

AI should create believable encounters rather than exist solely as stationary targets.

Enemies should react to:

* Gunfire.
* Nearby combat.
* Player movement.
* Other factions.
* Threats and casualties.

7.2 Faction System

Faction 1: [Name]

* Description:
* Equipment:
* Hostility:
* Combat Behavior:
* Spawn Locations:

Faction 2: [Name]

* Description:
* Equipment:
* Hostility:
* Combat Behavior:
* Spawn Locations:

Faction 3: [Name]

* Description:
* Equipment:
* Hostility:
* Combat Behavior:
* Spawn Locations:

7.3 Faction Relationships

Factions may be friendly, neutral, or hostile toward one another.

Relationships may influence:

* Combat encounters.
* Patrol routes.
* Territory control.
* Player interactions.

7.4 AI Behaviors

Initial Implementation

* Patrol.
* Detect threats.
* Seek cover.
* Attack enemies.
* Investigate sounds.
* Engage opposing factions.

Future Improvements

* Coordinated squad tactics.
* Flanking.
* Retreating.
* Reinforcements.
* Dynamic objectives.
* Looting and scavenging.

⸻

8. Dynamic Raid Events

8.1 Overview

Each raid has a chance to generate a special event that changes the normal gameplay experience.

8.2 Planned Events

Peacekeeping

* Friendly UN forces occupy major points of interest.
* UN forces engage hostile factions.
* Players may cooperate with friendly forces.

Ghost Town

* Normal AI populations are significantly reduced.
* A powerful enemy roams the map.
* Creates tension through isolation and uncertainty.

Gold Rush

* Increased loot quality and quantity.
* Significantly increased hostile AI presence.
* Higher potential rewards and greater risk.

8.3 Additional Event Ideas

* Faction War
* Military Lockdown
* Blackout
* Supply Drop
* [Additional Events]

8.4 Event Rules

* Event probability: TBD
* Multiple simultaneous events: TBD
* Event visibility before deployment: TBD
* Map-specific events: TBD

⸻

9. Loot & Economy

9.1 Loot Categories

* Weapons
* Ammunition
* Armor
* Medical supplies
* Food and consumables
* Weapon attachments
* Keys
* Valuable items
* Quest items
* Crafting materials: TBD

9.2 Loot Distribution

Loot quality and availability may depend on:

* Map difficulty.
* Location.
* Container type.
* Enemy equipment.
* Active raid events.

9.3 Economy

* Currency: TBD
* Trader buy/sell prices: TBD
* Player-to-player trading: TBD
* Flea market: TBD
* Item rarity system: TBD

9.4 Economy Philosophy

[Describe how valuable equipment should feel and how difficult it should be to obtain.]

⸻

10. Traders & Quests

10.1 Trader System

Traders provide equipment, quests, and progression opportunities.

Possible Traders

* Gunsmith
* Quartermaster
* Medical Supplier
* Fixer / Intelligence Dealer

10.2 Trader Progression

* Reputation levels.
* Unlockable equipment.
* Quest requirements.
* Special services.
* Extraction access.

10.3 Quest Types

* Eliminate specific enemies.
* Retrieve items.
* Explore locations.
* Deliver equipment.
* Complete map objectives.
* Survive and extract.

10.4 Quest Design Philosophy

[What makes quests enjoyable rather than repetitive?]

10.5 Cooperative Quest Progression

* Shared objective credit for eligible squad members.
* Shared elimination progress.
* Shared location discovery.
* Individual quest rewards.
* Individual trader reputation.
* Quest eligibility requirements.

⸻

11. Cooperative Multiplayer

11.1 Overview

Support for 1–4 players in cooperative PvE raids.

Initial Networking Approach: Listen server

11.2 Cooperative Features

* Squad deployment.
* Shared quest progress.
* Individual inventories.
* Individual stashes.
* Independent extraction.
* Friendly fire: TBD
* Voice communication: TBD

11.3 Death & Equipment Recovery

Death is permanent for the current raid.

Players lose equipment carried into the raid.

Surviving teammates may recover equipment belonging to deceased squad members.

Recovered equipment is returned to its original owner through an in-game mail or delivery system.

11.4 Open Questions

* What happens if the host dies?
* What happens if the host disconnects?
* Can players reconnect to an active raid?
* How is loot ownership tracked?

⸻

12. Persistent Progression

12.1 Character Progression

* Player level: TBD
* Skills: TBD
* Experience: TBD

12.2 Equipment Progression

Players begin with basic weapons and equipment.

More advanced equipment becomes available through:

* Looting.
* Traders.
* Quests.
* Map progression.
* Defeating difficult enemies.

12.3 Stash Progression

* Storage upgrades.
* Specialized containers.
* Equipment organization.
* Additional functionality: TBD

12.4 Long-Term Goals

[What should players work toward after 20, 50, or 100 hours?]

⸻

13. User Interface & Quality of Life

13.1 Main Interfaces

* Main menu.
* Character equipment.
* Stash.
* Inventory sorting table.
* Traders.
* Quest journal.
* Map selection.
* Raid preparation.
* In-raid HUD.
* Post-raid results.

13.2 Quality-of-Life Goals

* Fast inventory management.
* Searchable storage.
* Clear item descriptions.
* Easy equipment comparison.
* Loadout presets.
* Minimal unnecessary menu navigation.

13.3 Accessibility

* Keybinding customization.
* Graphics settings.
* Audio settings.
* UI scaling.
* Color accessibility options.

⸻

14. Art & Audio Direction

14.1 Visual Style

Selected Style: TBD

Possible directions:

* Low-poly.
* Stylized realism.
* Semi-realistic.

14.2 Environment Assets

Asset Packs Under Consideration:

Asset Pack	Purpose	Cost	Notes
TBD	Environment	TBD	
TBD	Weapons	TBD	
TBD	Characters	TBD	
TBD	Animations	TBD	

14.3 Audio

* Weapon sounds.
* Environmental ambience.
* Footsteps.
* AI communication.
* Combat audio.
* Music direction: TBD

⸻

15. Technical Design

15.1 Technology

Engine: Unreal Engine 5
Programming: C++ / Blueprints
Multiplayer: Listen server
Target Platform: Windows PC
Distribution: TBD

15.2 Technical Priorities

* Multiplayer-compatible architecture.
* Server-authoritative gameplay.
* Data-driven items and equipment.
* Modular inventory system.
* Expandable AI faction framework.
* Configurable raid events.
* Persistent player progression.

15.3 Performance Targets

* Target FPS: TBD
* Minimum hardware: TBD
* Recommended hardware: TBD
* Maximum AI population: TBD

⸻

16. Development Roadmap

Phase 1: Pre-production

* Finalize initial design direction.
* Install and configure UE5.
* Research asset packs.
* Establish source control.
* Create initial test project.

Phase 2: Gameplay Prototype

* First-person movement.
* Basic weapons and shooting.
* Basic enemy AI.
* Damage and death.
* Simple loot interaction.

Phase 3: Extraction Prototype

* Raid initialization.
* Loot persistence.
* Extraction mechanics.
* Death and equipment loss.
* Basic stash functionality.

Phase 4: Multiplayer Foundation

* Cooperative connections.
* Replicated movement and combat.
* Shared quest objectives.
* Individual inventory ownership.
* Independent extraction.

Phase 5: Vertical Slice

* One small playable map.
* Basic faction encounters.
* Multiple extraction methods.
* Initial inventory interface.
* One trader.
* Several quests.
* One dynamic raid event.

Phase 6: Expansion

* Additional maps.
* More weapons.
* Advanced AI.
* Additional factions.
* Expanded traders and quests.
* More raid events.

⸻

17. Minimum Viable Product (MVP)

MVP Objective

Deliver a complete, replayable PvE extraction experience on one small map.

Required Features

* Functional first-person combat.
* Basic inventory and stash.
* Lootable containers.
* Enemy AI.
* One playable map.
* Extraction system.
* Persistent equipment and loot.
* Death penalties.
* Basic cooperative multiplayer.

Not Required Initially

* Advanced AI tactics.
* Multiple maps.
* Extensive weapon customization.
* Large trader inventories.
* Complex economy.
* Large quest chains.
* Numerous dynamic events.

⸻

18. Ideas & Backlog

Use this section for ideas that are not yet approved for development.

Idea	Description	Priority	Status
Insurance	Recover certain lost equipment	TBD	Idea
Hideout	Upgradeable player base	TBD	Idea
Faction Reputation	Player relationships with AI factions	TBD	Idea
Dynamic Weather	Changing raid conditions	TBD	Idea
Weapon Durability	Equipment wear and maintenance	TBD	Idea
Crafting	Create equipment from collected materials	TBD	Idea

⸻

19. Design Decisions Log

Record important decisions to avoid repeatedly redesigning systems.

Decision	Reason	Status
PvE-focused gameplay	Focus on AI and cooperative gameplay	Confirmed
1–4 player co-op	Support playing with friends	Confirmed
Permanent raid death	Preserve extraction risk	Confirmed
Grid-based inventory	Deep equipment management	Confirmed
Small initial map	Manageable development scope	Confirmed
Dynamic raid events	Improve replayability	Confirmed
Independent AI factions	Create a living world	Confirmed
Shared quest progress	Reduce cooperative frustration	Confirmed
UE5	Selected development engine	Planned
Stylized/low-poly visuals	Reduce asset production requirements	Under consideration

⸻

20. Open Questions

Use this section to track decisions that still need discussion.

Gameplay

* How realistic should combat be?
* How punishing should injuries be?
* Should players have stamina and weight limits?

Progression

* How quickly should players acquire better equipment?
* How should maps unlock?
* Should player skills improve over time?

Economy

* Should there be a player-driven marketplace?
* How should traders determine prices?
* How rare should high-end equipment be?

Co-op

* Should friendly fire be enabled?
* Should difficulty scale with squad size?
* What happens when the host disconnects?

World

* What is the setting and backstory?
* Who are the factions?
* Why are players entering these locations?
* What motivates extraction?

⸻

21. Development Notes

Current Focus: Pre-production

Next Milestone: Establish UE5 development environment and prototype scope.

Current Blockers: None identified.

Additional Notes:

[Add notes, research, references, screenshots, and development observations here.]
