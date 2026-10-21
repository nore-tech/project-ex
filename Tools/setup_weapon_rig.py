import unreal

OUT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Saved\setup_weapon_rig.txt"
lines = []


def note(message):
    lines.append(str(message))
    unreal.log(str(message))


mesh = unreal.EditorAssetLibrary.load_asset("/Game/PolygonPrototype/Meshes/Weapons/SK_Prop_Rifle_01")
bounds = mesh.get_bounds()
origin = bounds.origin
extent = bounds.box_extent
note("ORIGIN {0:.1f} {1:.1f} {2:.1f}".format(origin.x, origin.y, origin.z))
note("EXTENT {0:.1f} {1:.1f} {2:.1f}".format(extent.x, extent.y, extent.z))

folder = "/Game/ProjectEX/Blueprints"
path = folder + "/BP_EX_Rifle"
if not unreal.EditorAssetLibrary.does_asset_exist(path):
    factory = unreal.BlueprintFactory()
    factory.set_editor_property("parent_class", unreal.ProjectEXWeaponRig)
    unreal.AssetToolsHelpers.get_asset_tools().create_asset("BP_EX_Rifle", folder, unreal.Blueprint, factory)
    note("CREATED " + path)

blueprint = unreal.EditorAssetLibrary.load_asset(path)
unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
generated = unreal.EditorAssetLibrary.load_blueprint_class(path)
cdo = unreal.get_default_object(generated)

# Mesh space: longest axis is the barrel. Yaw -90 turns a +Y barrel toward camera +X.
# Hip keeps the gun low and to the right. ADS shifts it so the raised rear of the gun
# sits on the camera axis (Y 0, Z 0).
hip = unreal.EditorAssetLibrary.load_asset(path)  # keep a reference
hip_anchor = cdo.get_editor_property("hip_fire_anchor")
ads_anchor = cdo.get_editor_property("ads_anchor")
preview = cdo.get_editor_property("preview_mesh")
ads_preview = cdo.get_editor_property("ads_preview_mesh")

rotation = unreal.Rotator(0.0, -90.0, 0.0)
# Bounds: barrel runs +Y (104 cm, center at Y 20), height 31 cm. Yaw -90 points the barrel down camera +X.
# Hip sits low and right. ADS centers it and lifts the top of the mesh onto the aim line.
hip_anchor.set_editor_property("relative_location", unreal.Vector(40.0, 16.0, -20.0))
hip_anchor.set_editor_property("relative_rotation", rotation)
ads_anchor.set_editor_property("relative_location", unreal.Vector(47.0, 1.0, -15.0))
ads_anchor.set_editor_property("relative_rotation", rotation)
preview.set_editor_property("skeletal_mesh_asset", mesh)
ads_preview.set_editor_property("skeletal_mesh_asset", mesh)
note("HIP {0}".format(hip_anchor.get_editor_property("relative_location")))
note("ADS {0}".format(ads_anchor.get_editor_property("relative_location")))

rifle = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Weapons/DA_RifleData")
rifle.set_editor_property("presentation_rig", generated)
rifle.set_editor_property("ads_fov", 75.0)
rifle.set_editor_property("ads_transition_duration", 0.18)
rifle.set_editor_property("ads_look_scale", 0.75)
note("RIG " + str(rifle.get_editor_property("presentation_rig")))

unreal.EditorAssetLibrary.save_asset(path, False)
unreal.EditorAssetLibrary.save_asset("/Game/FirstPerson/Weapons/DA_RifleData", False)
note("SAVED")

with open(OUT, "w", encoding="utf-8") as handle:
    handle.write("\n".join(lines))
