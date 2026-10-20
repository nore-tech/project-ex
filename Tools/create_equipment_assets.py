import unreal

OUT = r"C:\Users\Dennis\Documents\GitHub\project-ex\Saved\equipment_assets.txt"
lines = []

def note(message):
    lines.append(str(message))
    unreal.log(str(message))

def finish():
    with open(OUT, "w", encoding="utf-8") as handle:
        handle.write("\n".join(lines))

def make_item(name, folder):
    package = folder + "/" + name
    if unreal.EditorAssetLibrary.does_asset_exist(package):
        note("EXISTS " + package)
        return unreal.EditorAssetLibrary.load_asset(package)
    unreal.EditorAssetLibrary.make_directory(folder)
    factory = unreal.DataAssetFactory()
    factory.set_editor_property("data_asset_class", unreal.ProjectEXItemDefinition)
    asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(name, folder, None, factory)
    note("CREATED " + package + " " + str(asset))
    return asset

def set_gear(asset, label, kind):
    asset.set_editor_property("display_name", unreal.Text(label))
    asset.set_editor_property("max_stack_size", 1)
    asset.set_editor_property("grid_width", 2)
    asset.set_editor_property("grid_height", 2)
    asset.set_editor_property("weight", 1.0)
    asset.set_editor_property("equip_kind", kind)
    asset.set_editor_property("heal_amount", 0.0)
    note("GEAR " + label)

folder = "/Game/FirstPerson/Equipment"
set_gear(make_item("DA_Helmet", folder), "Helmet", unreal.ProjectEXEquipKind.HELMET)
set_gear(make_item("DA_BodyArmor", folder), "Body Armor", unreal.ProjectEXEquipKind.BODY_ARMOR)
set_gear(make_item("DA_Backpack", folder), "Backpack", unreal.ProjectEXEquipKind.BACKPACK)

bandage = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/DA_Bandage")
medkit = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/DA_MedicalKit")
bandage.set_editor_property("display_name", unreal.Text("Bandage"))
bandage.set_editor_property("heal_amount", 20.0)
bandage.set_editor_property("max_stack_size", 5)
medkit.set_editor_property("display_name", unreal.Text("Medical Kit"))
medkit.set_editor_property("heal_amount", 60.0)
medkit.set_editor_property("max_stack_size", 3)
note("HEAL bandage=20 medkit=60")

pistol = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Weapons/DA_Pistol")
rifle = unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Weapons/DA_Rifle")
pistol.set_editor_property("equip_kind", unreal.ProjectEXEquipKind.WEAPON)
rifle.set_editor_property("equip_kind", unreal.ProjectEXEquipKind.WEAPON)
note("WEAPONS marked equippable")

for asset in (
    unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Equipment/DA_Helmet"),
    unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Equipment/DA_BodyArmor"),
    unreal.EditorAssetLibrary.load_asset("/Game/FirstPerson/Equipment/DA_Backpack"),
    bandage,
    medkit,
    pistol,
    rifle,
):
    unreal.EditorAssetLibrary.save_loaded_asset(asset)

note("SAVED")
finish()
