import unreal

OUT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Saved\place_enemy.txt"
MAP_PATH = "/Game/FirstPerson/Lvl_FirstPerson"
LABEL = "EX_Enemy_01"
DISTANCE = 1000.0
lines = []


def note(message):
    lines.append(str(message))
    unreal.log(str(message))


def floor_z(world, x, y, top):
    channel = getattr(unreal.TraceTypeQuery, "ECC_VISIBILITY", unreal.TraceTypeQuery.TRACE_TYPE_QUERY1)
    hit = unreal.SystemLibrary.line_trace_single(
        world, unreal.Vector(x, y, top + 300.0), unreal.Vector(x, y, top - 1500.0), channel, True, [],
        unreal.DrawDebugTrace.NONE, False, unreal.LinearColor(1, 0, 0, 1), unreal.LinearColor(0, 1, 0, 1), 0.0)
    if not hit or not getattr(hit, "blocking_hit", getattr(hit, "b_blocking_hit", False)):
        return None
    for name in ("impact_point", "location"):
        if hasattr(hit, name):
            return getattr(hit, name).z
    return None


unreal.EditorLoadingAndSavingUtils.load_map(MAP_PATH)
actor_sub = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
world = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem).get_editor_world()
actors = actor_sub.get_all_level_actors()

if any(actor.get_actor_label() == LABEL for actor in actors):
    note("ALREADY_PLACED")
else:
    start = next((a for a in actors if a.get_class().get_name().endswith("PlayerStart")), None)
    origin = start.get_actor_location() if start else unreal.Vector(0.0, 0.0, 300.0)
    forward = unreal.MathLibrary.get_forward_vector(start.get_actor_rotation()) if start else unreal.Vector(1.0, 0.0, 0.0)
    x = origin.x + forward.x * DISTANCE
    y = origin.y + forward.y * DISTANCE
    ground = floor_z(world, x, y, origin.z)
    z = (ground + 100.0) if ground is not None else origin.z
    note("START {0} FLOOR {1}".format(origin, ground))
    rotation = unreal.MathLibrary.find_look_at_rotation(unreal.Vector(x, y, z), unreal.Vector(origin.x, origin.y, z))
    enemy = actor_sub.spawn_actor_from_class(unreal.ProjectEXEnemy, unreal.Vector(x, y, z), rotation)
    enemy.set_actor_label(LABEL)
    note("SPAWNED {0} at {1}".format(LABEL, enemy.get_actor_location()))
    note("SAVE_LEVEL " + str(unreal.get_editor_subsystem(unreal.LevelEditorSubsystem).save_current_level()))

with open(OUT, "w", encoding="utf-8") as handle:
    handle.write("\n".join(lines))
