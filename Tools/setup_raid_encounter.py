import unreal

OUT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Saved\setup_raid_encounter.txt"
MAP_PATH = "/Game/FirstPerson/Lvl_FirstPerson"
BP_FOLDER = "/Game/ProjectEX/Blueprints"
lines = []


def note(message):
    lines.append(str(message))
    unreal.log(str(message))


def ensure_blueprint(name, parent, defaults):
    path = "{0}/{1}".format(BP_FOLDER, name)
    if not unreal.EditorAssetLibrary.does_asset_exist(path):
        factory = unreal.BlueprintFactory()
        factory.set_editor_property("parent_class", parent)
        asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(name, BP_FOLDER, unreal.Blueprint, factory)
        note("CREATED {0} {1}".format(path, asset))
    blueprint = unreal.EditorAssetLibrary.load_asset(path)
    unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
    generated = unreal.EditorAssetLibrary.load_blueprint_class(path)
    cdo = unreal.get_default_object(generated)
    for key, value in defaults.items():
        cdo.set_editor_property(key, value)
    unreal.EditorAssetLibrary.save_asset(path, False)
    return generated


enemy_class = ensure_blueprint("BP_Enemy", unreal.ProjectEXEnemy, {
    "max_health": 100.0,
    "move_speed": 380.0,
    "detection_range": 1000.0,
    "attack_range": 170.0,
    "attack_damage": 8.0,
    "attack_cooldown": 1.5,
})
zone_class = ensure_blueprint("BP_ExtractionZone", unreal.ProjectEXExtractionZone, {
    "countdown": 10.0,
    "radius": 200.0,
})

unreal.EditorLoadingAndSavingUtils.load_map(MAP_PATH)
actor_sub = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)

for actor in actor_sub.get_all_level_actors():
    label = actor.get_actor_label()
    if label == "EX_Enemy_01" or label.startswith("EX_Raid_"):
        note("REMOVED " + label)
        actor_sub.destroy_actor(actor)

rotation = unreal.Rotator(0.0, 0.0, 0.0)


def spawn(cls, label, location, yaw=0.0):
    rot = unreal.Rotator(0.0, 0.0, 0.0)
    rot.yaw = yaw
    actor = actor_sub.spawn_actor_from_class(cls, location, rot)
    actor.set_actor_label(label)
    note("SPAWNED {0} at {1}".format(label, actor.get_actor_location()))
    return actor


# Navigation bounds covering the walled arena. The navmesh itself is generated at runtime.
volume = actor_sub.spawn_actor_from_object(unreal.NavMeshBoundsVolume.static_class(), unreal.Vector(0.0, 0.0, 150.0), rotation)
if volume:
    volume.set_actor_label("EX_Raid_NavBounds")
    volume.set_actor_scale3d(unreal.Vector(20.0, 20.0, 4.0))
    origin, extent = volume.get_actor_bounds(False)
    note("NAV_BOUNDS origin {0} extent {1}".format(origin, extent))
else:
    note("NAV_BOUNDS spawn failed")

enemy_a = spawn(enemy_class, "EX_Raid_Enemy_A", unreal.Vector(1300.0, 700.0, 100.0), 180.0)
enemy_a.set_editor_property("patrol_points", [unreal.Vector(0.0, 0.0, 0.0), unreal.Vector(0.0, -1400.0, 0.0)])
enemy_b = spawn(enemy_class, "EX_Raid_Enemy_B", unreal.Vector(-600.0, -1250.0, 100.0), 90.0)
enemy_b.set_editor_property("patrol_points", [unreal.Vector(0.0, 0.0, 0.0), unreal.Vector(-650.0, 650.0, 0.0)])
enemy_c = spawn(enemy_class, "EX_Raid_Enemy_C", unreal.Vector(600.0, 1250.0, 100.0), -90.0)
enemy_c.set_editor_property("patrol_radius", 400.0)

zone = spawn(zone_class, "EX_Raid_Extraction", unreal.Vector(-1000.0, -1000.0, 0.0))
zone.set_editor_property("display_name", "Southwest Exfil")
cover = [
    ("/Game/PolygonPrototype/Meshes/Props/SM_Prop_Barrier_01", unreal.Vector(-720.0, -720.0, 0.0), 45.0),
    ("/Game/PolygonPrototype/Meshes/Props/SM_Prop_Crate_01", unreal.Vector(900.0, 950.0, 0.0), 10.0),
    ("/Game/PolygonPrototype/Meshes/Props/SM_Prop_Crate_02", unreal.Vector(1050.0, -100.0, 0.0), 0.0),
    ("/Game/PolygonPrototype/Meshes/Props/SM_Prop_Barrier_01", unreal.Vector(950.0, -950.0, 0.0), -45.0),
    ("/Game/PolygonPrototype/Meshes/Props/SM_Prop_Crate_03", unreal.Vector(-450.0, 1000.0, 0.0), 25.0),
]
for index, (path, location, yaw) in enumerate(cover):
    mesh = unreal.EditorAssetLibrary.load_asset(path)
    if not mesh:
        note("MISSING " + path)
        continue
    rot = unreal.Rotator(0.0, 0.0, 0.0)
    rot.yaw = yaw
    actor = actor_sub.spawn_actor_from_object(mesh, location, rot)
    actor.set_actor_label("EX_Raid_Cover_{0}".format(index))
    origin, extent = actor.get_actor_bounds(False)
    note("COVER {0} extent {1}".format(path.split("/")[-1], extent))

for actor in actor_sub.get_all_level_actors():
    if "NavMesh" in actor.get_class().get_name() or "NavigationData" in actor.get_class().get_name():
        note("NAV_ACTOR {0} {1}".format(actor.get_class().get_name(), actor.get_actor_label()))

note("SAVE_LEVEL " + str(unreal.get_editor_subsystem(unreal.LevelEditorSubsystem).save_current_level()))

with open(OUT, "w", encoding="utf-8") as handle:
    handle.write("\n".join(lines))
