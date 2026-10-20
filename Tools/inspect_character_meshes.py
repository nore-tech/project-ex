import unreal

OUT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Saved\mesh_inspect.txt"
lines = []

def note(message):
    lines.append(str(message))
    unreal.log(str(message))

paths = [
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Arms_01",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Arms_02",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Arms_03",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Hands_01",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/SK_Character_Dummy_Male_01",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/SK_Character_Male_Face_01",
    "/Game/PolygonPrototype/Meshes/Weapons/SK_Prop_Pistol_01",
    "/Game/PolygonPrototype/Meshes/Weapons/SK_Prop_Rifle_01",
]

actor_sub = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
keywords = ("hand", "head", "sight", "muzzle", "weapon", "grip", "ik")

for path in paths:
    mesh = unreal.EditorAssetLibrary.load_asset(path)
    if not mesh:
        note("MISSING " + path)
        continue
    bounds = mesh.get_bounds()
    extent = bounds.box_extent
    origin = bounds.origin
    skeleton = mesh.get_editor_property("skeleton")
    note("MESH {0}".format(path))
    note("  skeleton={0}".format(skeleton.get_path_name() if skeleton else None))
    note("  extent=({0:.1f},{1:.1f},{2:.1f}) origin=({3:.1f},{4:.1f},{5:.1f})".format(
        extent.x, extent.y, extent.z, origin.x, origin.y, origin.z))

    actor = actor_sub.spawn_actor_from_class(unreal.Actor, unreal.Vector(0.0, 0.0, -50000.0), unreal.Rotator(0.0, 0.0, 0.0))
    component = unreal.new_object(unreal.SkeletalMeshComponent, actor)
    component.set_skeletal_mesh_asset(mesh)
    component.register_component()
    sockets = [str(name) for name in component.get_all_socket_names()]
    bones = [str(name) for name in component.get_bone_names()] if hasattr(component, "get_bone_names") else []
    interesting = [name for name in sockets + bones if any(word in name.lower() for word in keywords)]
    note("  socket_count={0} bone_count={1}".format(len(sockets), len(bones)))
    note("  interesting={0}".format(interesting))
    actor.destroy_actor()

with open(OUT, "w", encoding="utf-8") as handle:
    handle.write("\n".join(lines))
