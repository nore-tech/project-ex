import unreal
OUT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Saved\mesh_bounds.txt"
lines = []
paths = [
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Arms_01",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Arms_02",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Arms_03",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Hands_01",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/SK_Character_Dummy_Male_01",
    "/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/SK_Character_Male_Face_01",
]
for path in paths:
    mesh = unreal.EditorAssetLibrary.load_asset(path)
    skeleton = mesh.get_editor_property("skeleton")
    bounds = mesh.get_bounds()
    extent = bounds.box_extent
    origin = bounds.origin
    lines.append("{0} skeleton={1} extent=({2:.1f},{3:.1f},{4:.1f}) origin=({5:.1f},{6:.1f},{7:.1f})".format(
        path, skeleton.get_name() if skeleton else None, extent.x, extent.y, extent.z, origin.x, origin.y, origin.z))
open(OUT, "w", encoding="utf-8").write("\n".join(lines))
