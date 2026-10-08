import unreal as u
r=u.AssetRegistryHelpers.get_asset_registry()
r.scan_paths_synchronous(["/Niagara"],force_rescan=True)
for a in r.get_assets_by_path("/Niagara/DefaultAssets/Templates/Systems",recursive=True):
    u.log("NIAGARA_TEMPLATE "+str(a.package_name)+" "+str(a.asset_name))
source=u.load_asset("/Niagara/DefaultAssets/Templates/Systems/RadialBurst")
if source:
    for name in ["NS_Landing","NS_Complete"]:
        if not u.EditorAssetLibrary.does_asset_exist("/Game/FX/"+name):
            u.AssetToolsHelpers.get_asset_tools().duplicate_asset(name,"/Game/FX",source)
    u.EditorAssetLibrary.save_directory("/Game/FX",only_if_is_dirty=False,recursive=True)
    u.log("FX_BUILD_SUCCESS")
