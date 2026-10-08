import unreal as u
lib=u.MaterialEditingLibrary
m=u.load_asset('/Game/Art/M_Instanced')
lib.delete_all_material_expressions(m)
m.set_editor_property('used_with_instanced_static_meshes',True)
channels=[]
for i in range(3):
    node=lib.create_material_expression(m,u.MaterialExpressionPerInstanceCustomData,-800,i*100)
    node.set_editor_property('data_index',i)
    channels.append(node)
a=lib.create_material_expression(m,u.MaterialExpressionAppendVector,-500,0)
b=lib.create_material_expression(m,u.MaterialExpressionAppendVector,-300,0)
assert lib.connect_material_expressions(channels[0],'',a,'A')
assert lib.connect_material_expressions(channels[1],'',a,'B')
assert lib.connect_material_expressions(a,'',b,'A')
assert lib.connect_material_expressions(channels[2],'',b,'B')
interp=lib.create_material_expression(m,u.MaterialExpressionVertexInterpolator,-100,0)
assert lib.connect_material_expressions(b,'',interp,'')
assert lib.connect_material_property(interp,'',u.MaterialProperty.MP_BASE_COLOR)
for value,prop in [(.35,u.MaterialProperty.MP_METALLIC),(.38,u.MaterialProperty.MP_ROUGHNESS)]:
    n=lib.create_material_expression(m,u.MaterialExpressionConstant,-200,300)
    n.set_editor_property('r',value)
    lib.connect_material_property(n,'',prop)
lib.recompile_material(m)
u.EditorAssetLibrary.save_loaded_asset(m)
u.log('INSTANCED_MATERIAL_REPAIRED')
