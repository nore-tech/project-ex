import os
import unreal

OUT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Saved\place_weapons.txt"
ACTOR_ROOT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Content\__ExternalActors__\FirstPerson\Lvl_FirstPerson"
MAP_PATH = "/Game/FirstPerson/Lvl_FirstPerson"
lines = []


def note(message):
    lines.append(str(message))
    unreal.log(str(message))


def finish():
    with open(OUT, "w", encoding="utf-8") as handle:
        handle.write("\n".join(lines))


def list_assets(path):
    found = set()
    if not os.path.isdir(path):
        return found
    for dirpath, _, filenames in os.walk(path):
        for name in filenames:
            if name.endswith(".uasset"):
                found.add(os.path.join(dirpath, name))
    return found


def add_vec(a, b):
    return unreal.Vector(a.x + b.x, a.y + b.y, a.z + b.z)


def scale_vec(vector, scale):
    return unreal.Vector(vector.x * scale, vector.y * scale, vector.z * scale)


def trace_channel():
    if hasattr(unreal.TraceTypeQuery, "ECC_VISIBILITY"):
        return unreal.TraceTypeQuery.ECC_VISIBILITY
    return unreal.TraceTypeQuery.TRACE_TYPE_QUERY1


def hit_blocked(hit):
    if not hit:
        return False
    for name in ("blocking_hit", "b_blocking_hit"):
        if hasattr(hit, name):
            return bool(getattr(hit, name))
    if not getattr(hit_blocked, "logged", False):
        hit_blocked.logged = True
        fields = [name for name in dir(hit) if not name.startswith("_")]
        note("HIT_FIELDS " + ", ".join(fields))
    return False


def hit_impact(hit):
    for name in ("impact_point", "location"):
        if hasattr(hit, name):
            return getattr(hit, name)
    return None


def trace(world, start, end):
    return unreal.SystemLibrary.line_trace_single(
        world,
        start,
        end,
        trace_channel(),
        True,
        [],
        unreal.DrawDebugTrace.NONE,
        False,
        unreal.LinearColor(1.0, 0.0, 0.0, 1.0),
        unreal.LinearColor(0.0, 1.0, 0.0, 1.0),
        0.0,
    )


def floor_location(world, point):
    start = unreal.Vector(point.x, point.y, point.z + 400.0)
    end = unreal.Vector(point.x, point.y, point.z - 1200.0)
    hit = trace(world, start, end)
    impact = hit_impact(hit) if hit_blocked(hit) else None
    if impact:
        return unreal.Vector(impact.x, impact.y, impact.z + 30.0)
    return unreal.Vector(point.x, point.y, point.z + 30.0)


before = list_assets(ACTOR_ROOT)
note("EXTERNAL_BEFORE " + str(len(before)))

unreal.EditorLoadingAndSavingUtils.load_map(MAP_PATH)
actor_sub = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
world = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem).get_editor_world()
actors = actor_sub.get_all_level_actors()
note("ACTOR_COUNT " + str(len(actors)))

starts = []
for actor in actors:
    class_name = actor.get_class().get_name()
    label = actor.get_actor_label()
    if class_name == "PlayerStart" or class_name.endswith("PlayerStart"):
        starts.append(actor)
        note("START {0} {1}".format(label, actor.get_actor_location()))
    if "Pickup" in class_name or label.startswith("EX_"):
        note("EXISTING {0} {1} {2}".format(class_name, label, actor.get_actor_location()))

if any(actor.get_actor_label() == "EX_Pistol" for actor in actors):
    ground_z = (starts[0].get_actor_location().z + 40.0) if starts else 342.0
    for actor in actors:
        if actor.get_actor_label().startswith("EX_"):
            location = actor.get_actor_location()
            location.z = ground_z
            actor.set_actor_location(location, False, False)
            note("RAISED {0} to {1}".format(actor.get_actor_label(), location))
    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    note("SAVE_LEVEL " + str(level_editor.save_current_level()))
    finish()
else:
    if not starts:
        origin = unreal.Vector(0.0, 0.0, 100.0)
        forward = unreal.Vector(1.0, 0.0, 0.0)
        right = unreal.Vector(0.0, 1.0, 0.0)
        note("NO_PLAYER_START using origin")
    else:
        start = starts[0]
        origin = start.get_actor_location()
        rotation = start.get_actor_rotation()
        forward = unreal.MathLibrary.get_forward_vector(rotation)
        right = unreal.MathLibrary.get_right_vector(rotation)

    directions = [
        ("forward", forward),
        ("right", right),
        ("back", scale_vec(forward, -1.0)),
        ("left", scale_vec(right, -1.0)),
    ]
    eye = unreal.Vector(origin.x, origin.y, origin.z + 60.0)
    chosen_name = "forward"
    chosen_point = add_vec(origin, scale_vec(forward, 220.0))
    for name, direction in directions:
        candidate = add_vec(origin, scale_vec(direction, 220.0))
        candidate_eye = unreal.Vector(candidate.x, candidate.y, candidate.z + 60.0)
        hit = trace(world, eye, candidate_eye)
        blocked = hit_blocked(hit)
        note("DIR {0} blocked={1} point={2}".format(name, blocked, candidate))
        if not blocked:
            chosen_name = name
            chosen_point = candidate
            break

    note("CHOSEN " + chosen_name)

    pistol = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Weapons/DA_Pistol")
    rifle = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Weapons/DA_Rifle")
    ammo_9 = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Weapons/DA_Ammo_9mm")
    ammo_556 = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Weapons/DA_Ammo_556")
    note("ASSETS pistol={0} rifle={1} ammo9={2} ammo556={3}".format(pistol, rifle, ammo_9, ammo_556))

    layout = [
        ("EX_Pistol", pistol, 1, -1),
        ("EX_9mm_A", ammo_9, 60, -1),
        ("EX_9mm_B", ammo_9, 60, -1),
        ("EX_Rifle", rifle, 1, -1),
        ("EX_556_A", ammo_556, 60, -1),
        ("EX_556_B", ammo_556, 60, -1),
    ]

    rotation = unreal.Rotator(0.0, 0.0, 0.0)
    rotation.roll = 0.0
    rotation.pitch = 0.0
    rotation.yaw = 0.0

    for index, (label, definition, quantity, magazine) in enumerate(layout):
        point = add_vec(chosen_point, scale_vec(right, (index - 2.5) * 80.0))
        location = floor_location(world, point)
        location.z = origin.z + 40.0
        actor = actor_sub.spawn_actor_from_class(unreal.ProjectEXPickup, location, rotation)
        actor.set_actor_label(label)
        actor.set_editor_property("item_definition", definition)
        actor.set_editor_property("quantity", quantity)
        actor.set_editor_property("stored_magazine", magazine)
        note("SPAWNED {0} qty={1} at {2}".format(label, quantity, actor.get_actor_location()))

    level_editor = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    saved = level_editor.save_current_level()
    note("SAVE_LEVEL " + str(saved))

after = list_assets(ACTOR_ROOT)
new_files = sorted(after - before)
note("NEW_FILES " + str(len(new_files)))
for path in new_files:
    note("NEW " + path)
finish()
