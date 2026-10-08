import unreal as u
for path in ['/Game/Art/M_Surface','/Game/Art/M_Instanced']:
    m=u.load_asset(path)
    m.set_editor_property('used_with_instanced_static_meshes',True)
    u.MaterialEditingLibrary.recompile_material(m)
    u.EditorAssetLibrary.save_loaded_asset(m)
u.log('MATERIAL_USAGE_FIXED')
