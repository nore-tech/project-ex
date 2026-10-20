import unreal

OUT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Saved\weapon_assets.txt"
lines = []

def note(message):
    lines.append(str(message))
    unreal.log(str(message))

def finish():
    folder = unreal.Paths.project_saved_dir()
    with open(OUT, "w", encoding="utf-8") as handle:
        handle.write("\n".join(lines))

def mesh_long_axis(path):
    mesh = unreal.EditorAssetLibrary.load_asset(path)
    bounds = mesh.get_bounds()
    extent = bounds.box_extent
    note("MESH {0} extent=({1:.1f},{2:.1f},{3:.1f})".format(path, extent.x, extent.y, extent.z))
    axes = {"x": extent.x, "y": extent.y, "z": extent.z}
    return max(axes, key=axes.get)

def make_data_asset(name, folder, asset_class):
    package = folder + "/" + name
    if unreal.EditorAssetLibrary.does_asset_exist(package):
        note("EXISTS " + package)
        return unreal.EditorAssetLibrary.load_asset(package)
    factory = unreal.DataAssetFactory()
    factory.set_editor_property("data_asset_class", asset_class)
    asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(name, folder, None, factory)
    note("CREATED " + package + " " + str(asset))
    return asset

def rotation_for_axis(axis):
    rotation = unreal.Rotator(0.0, 0.0, 0.0)
    if axis == "y":
        rotation.yaw = -90.0
    elif axis == "z":
        rotation.pitch = -90.0
    return rotation

folder = "/Game/FirstPerson/Weapons"
rifle_axis = mesh_long_axis("/Game/PolygonPrototype/Meshes/Weapons/SK_Prop_Rifle_01")
pistol_axis = mesh_long_axis("/Game/PolygonPrototype/Meshes/Weapons/SK_Prop_Pistol_01")
note("AXIS rifle={0} pistol={1}".format(rifle_axis, pistol_axis))

ammo_9 = make_data_asset("DA_Ammo_9mm", folder, unreal.ProjectEXItemDefinition)
ammo_556 = make_data_asset("DA_Ammo_556", folder, unreal.ProjectEXItemDefinition)
pistol_data = make_data_asset("DA_PistolData", folder, unreal.ProjectEXWeaponData)
rifle_data = make_data_asset("DA_RifleData", folder, unreal.ProjectEXWeaponData)
pistol_item = make_data_asset("DA_Pistol", folder, unreal.ProjectEXWeaponItemDefinition)
rifle_item = make_data_asset("DA_Rifle", folder, unreal.ProjectEXWeaponItemDefinition)

ammo_icon_9 = unreal.EditorAssetLibrary.load_asset("/Game/PolygonPrototype/Meshes/Icons/SM_Icon_Ammo_01")
ammo_icon_556 = unreal.EditorAssetLibrary.load_asset("/Game/PolygonPrototype/Meshes/Icons/SM_Icon_Ammo_03")

def set_ammo(asset, label, mesh):
    asset.set_editor_property("display_name", unreal.Text(label))
    asset.set_editor_property("max_stack_size", 60)
    asset.set_editor_property("grid_width", 1)
    asset.set_editor_property("grid_height", 1)
    asset.set_editor_property("weight", 0.02)
    if mesh:
        asset.set_editor_property("world_mesh", mesh)
        note("AMMO MESH " + label + " " + mesh.get_path_name())
    else:
        note("AMMO MESH MISSING " + label)

set_ammo(ammo_9, "9mm", ammo_icon_9)
set_ammo(ammo_556, "5.56", ammo_icon_556)

sound = unreal.EditorAssetLibrary.load_asset("/Game/Weapons/GrenadeLauncher/Audio/FirstPersonTemplateWeaponFire02")
rifle_mesh = unreal.EditorAssetLibrary.load_asset("/Game/PolygonPrototype/Meshes/Weapons/SK_Prop_Rifle_01")
pistol_mesh = unreal.EditorAssetLibrary.load_asset("/Game/PolygonPrototype/Meshes/Weapons/SK_Prop_Pistol_01")

pistol_offset = unreal.Vector(28.0, 10.0, -10.0)
rifle_offset = unreal.Vector(36.0, 12.0, -12.0)

pistol_data.set_editor_property("display_name", unreal.Text("Pistol"))
pistol_data.set_editor_property("fire_mode", unreal.ProjectEXFireMode.SEMI)
pistol_data.set_editor_property("damage", 34.0)
pistol_data.set_editor_property("fire_interval", 0.18)
pistol_data.set_editor_property("magazine_size", 15)
pistol_data.set_editor_property("reload_duration", 1.6)
pistol_data.set_editor_property("recoil_pitch", 1.1)
pistol_data.set_editor_property("recoil_yaw", 0.35)
pistol_data.set_editor_property("range", 6000.0)
pistol_data.set_editor_property("ammo_type", ammo_9)
pistol_data.set_editor_property("view_mesh", pistol_mesh)
pistol_data.set_editor_property("view_offset", pistol_offset)
pistol_data.set_editor_property("view_rotation", rotation_for_axis(pistol_axis))
pistol_data.set_editor_property("view_scale", 0.7)
pistol_data.set_editor_property("ads_offset", unreal.Vector(22.0, 0.0, -3.0))
pistol_data.set_editor_property("ads_rotation", rotation_for_axis(pistol_axis))
pistol_data.set_editor_property("ads_fov", 76.0)
pistol_data.set_editor_property("ads_speed", 14.0)
pistol_data.set_editor_property("sway_degrees", 3.2)
pistol_data.set_editor_property("sway_speed", 13.0)
pistol_data.set_editor_property("bob_horizontal", 1.15)
pistol_data.set_editor_property("bob_vertical", 0.75)
pistol_data.set_editor_property("bob_speed", 1.65)
pistol_data.set_editor_property("sprint_bob_multiplier", 1.8)
pistol_data.set_editor_property("aim_sway_scale", 0.3)
pistol_data.set_editor_property("aim_bob_scale", 0.25)
pistol_data.set_editor_property("visual_kick_distance", 4.0)
pistol_data.set_editor_property("visual_kick_pitch", 5.5)
pistol_data.set_editor_property("visual_kick_recovery", 12.0)
pistol_data.set_editor_property("reload_drop_distance", 16.0)
pistol_data.set_editor_property("reload_drop_pitch", 22.0)
pistol_data.set_editor_property("tracer_interval", 1)
pistol_data.set_editor_property("sight_offset", unreal.Vector(0.0, -3.0, 7.0))
pistol_data.set_editor_property("muzzle_offset", unreal.Vector(0.0, 13.0, 1.0))
pistol_data.set_editor_property("grip_offset", 4.0)
pistol_data.set_editor_property("grip_style", unreal.ProjectEXGripStyle.PISTOL)
pistol_data.set_editor_property("right_hand_offset", unreal.Vector(0.0, -2.0, -6.0))
pistol_data.set_editor_property("left_hand_offset", unreal.Vector(4.0, -1.0, -7.0))
pistol_data.set_editor_property("fire_sound", sound)

rifle_data.set_editor_property("display_name", unreal.Text("Rifle"))
rifle_data.set_editor_property("fire_mode", unreal.ProjectEXFireMode.AUTOMATIC)
rifle_data.set_editor_property("damage", 22.0)
rifle_data.set_editor_property("fire_interval", 0.09)
rifle_data.set_editor_property("magazine_size", 30)
rifle_data.set_editor_property("reload_duration", 2.2)
rifle_data.set_editor_property("recoil_pitch", 0.45)
rifle_data.set_editor_property("recoil_yaw", 0.2)
rifle_data.set_editor_property("range", 8000.0)
rifle_data.set_editor_property("ammo_type", ammo_556)
rifle_data.set_editor_property("view_mesh", rifle_mesh)
rifle_data.set_editor_property("view_offset", rifle_offset)
rifle_data.set_editor_property("view_rotation", rotation_for_axis(rifle_axis))
rifle_data.set_editor_property("view_scale", 0.85)
rifle_data.set_editor_property("ads_offset", unreal.Vector(28.0, 0.0, -4.0))
rifle_data.set_editor_property("ads_rotation", rotation_for_axis(rifle_axis))
rifle_data.set_editor_property("ads_fov", 60.0)
rifle_data.set_editor_property("ads_speed", 8.0)
rifle_data.set_editor_property("sway_degrees", 1.8)
rifle_data.set_editor_property("sway_speed", 11.0)
rifle_data.set_editor_property("bob_horizontal", 0.7)
rifle_data.set_editor_property("bob_vertical", 0.45)
rifle_data.set_editor_property("bob_speed", 1.8)
rifle_data.set_editor_property("sprint_bob_multiplier", 2.1)
rifle_data.set_editor_property("aim_sway_scale", 0.2)
rifle_data.set_editor_property("aim_bob_scale", 0.15)
rifle_data.set_editor_property("visual_kick_distance", 1.8)
rifle_data.set_editor_property("visual_kick_pitch", 1.6)
rifle_data.set_editor_property("visual_kick_recovery", 18.0)
rifle_data.set_editor_property("reload_drop_distance", 11.0)
rifle_data.set_editor_property("reload_drop_pitch", 14.0)
rifle_data.set_editor_property("tracer_interval", 3)
rifle_data.set_editor_property("sight_offset", unreal.Vector(0.0, -20.0, 14.0))
rifle_data.set_editor_property("muzzle_offset", unreal.Vector(0.0, 48.0, 2.0))
rifle_data.set_editor_property("grip_offset", 22.0)
rifle_data.set_editor_property("grip_style", unreal.ProjectEXGripStyle.RIFLE)
rifle_data.set_editor_property("right_hand_offset", unreal.Vector(-3.0, -18.0, -9.0))
rifle_data.set_editor_property("left_hand_offset", unreal.Vector(7.0, 14.0, -6.0))
rifle_data.set_editor_property("fire_sound", sound)

def set_weapon_item(asset, label, width, height, data, mesh):
    asset.set_editor_property("display_name", unreal.Text(label))
    asset.set_editor_property("max_stack_size", 1)
    asset.set_editor_property("grid_width", width)
    asset.set_editor_property("grid_height", height)
    asset.set_editor_property("weight", 1.0)
    asset.set_editor_property("weapon_data", data)
    asset.set_editor_property("display_skeletal_mesh", mesh)
    asset.set_editor_property("display_skeletal_rotation", rotation_for_axis("y"))
    asset.set_editor_property("display_skeletal_scale", 1.0)
    note("WEAPON MESH " + label + " " + mesh.get_path_name())

set_weapon_item(pistol_item, "Pistol", 2, 1, pistol_data, pistol_mesh)
set_weapon_item(rifle_item, "Rifle", 4, 2, rifle_data, rifle_mesh)

for asset in (ammo_9, ammo_556, pistol_data, rifle_data, pistol_item, rifle_item):
    unreal.EditorAssetLibrary.save_loaded_asset(asset)

note("SAVED pistol_rot_yaw={0} rifle_rot_yaw={1}".format(
    pistol_data.get_editor_property("view_rotation").yaw,
    rifle_data.get_editor_property("view_rotation").yaw))
finish()
