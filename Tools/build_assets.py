"""Rebuild original presentation assets inside Unreal Editor's Python commandlet.
Run: UnrealEditor-Cmd PROJECT -run=pythonscript -script=.../Tools/build_assets.py
"""
import unreal as u
import os, math, wave, struct
root = u.Paths.project_dir()
out = os.path.join(root, "Intermediate", "GeneratedArt")
os.makedirs(out, exist_ok=True)
assets=u.AssetToolsHelpers.get_asset_tools()
lib=u.MaterialEditingLibrary

def material(name, instanced=False):
    path="/Game/Art/"+name
    m=u.load_asset(path) or assets.create_asset(name,"/Game/Art",u.Material,u.MaterialFactoryNew())
    lib.delete_all_material_expressions(m)
    m.set_editor_property('used_with_instanced_static_meshes',True)
    color=lib.create_material_expression(m,u.MaterialExpressionVectorParameter,-600,0)
    color.set_editor_property("parameter_name","Color")
    color.set_editor_property("default_value",u.LinearColor(.2,.3,.4,1))
    output=color
    if instanced:
        channels=[]
        for i in range(3):
            n=lib.create_material_expression(m,u.MaterialExpressionPerInstanceCustomData,-850,i*120)
            n.set_editor_property("data_index",i)
            channels.append(n)
        a=lib.create_material_expression(m,u.MaterialExpressionAppendVector,-600,0)
        b=lib.create_material_expression(m,u.MaterialExpressionAppendVector,-400,0)
        lib.connect_material_expressions(channels[0],"",a,"A");lib.connect_material_expressions(channels[1],"",a,"B")
        lib.connect_material_expressions(a,"",b,"A");lib.connect_material_expressions(channels[2],"",b,"B")
        interp=lib.create_material_expression(m,u.MaterialExpressionVertexInterpolator,-200,0)
        lib.connect_material_expressions(b,"",interp,"");output=interp
    lib.connect_material_property(output,"",u.MaterialProperty.MP_BASE_COLOR)
    for param,default,prop in [("Metallic",.3,u.MaterialProperty.MP_METALLIC),("Roughness",.34,u.MaterialProperty.MP_ROUGHNESS)]:
        n=lib.create_material_expression(m,u.MaterialExpressionScalarParameter,-400,300)
        n.set_editor_property("parameter_name",param);n.set_editor_property("default_value",default)
        lib.connect_material_property(n,"",prop)
    glow=lib.create_material_expression(m,u.MaterialExpressionScalarParameter,-400,500)
    glow.set_editor_property("parameter_name","Glow");glow.set_editor_property("default_value",0)
    mult=lib.create_material_expression(m,u.MaterialExpressionMultiply,-100,300)
    lib.connect_material_expressions(color,"",mult,"A");lib.connect_material_expressions(glow,"",mult,"B")
    lib.connect_material_property(mult,"",u.MaterialProperty.MP_EMISSIVE_COLOR)
    lib.recompile_material(m);u.EditorAssetLibrary.save_loaded_asset(m)
material("M_Surface")
material("M_Instanced",True)

# Original rounded box, sampled from six cube faces. OBJ uses centimetres.
vertices=[];faces=[]
n=10
for axis,sign in [(0,1),(0,-1),(1,1),(1,-1),(2,1),(2,-1)]:
    base=len(vertices);other=[i for i in range(3) if i!=axis]
    for j in range(n+1):
        for i in range(n+1):
            p=[0.,0.,0.];p[axis]=sign*50;p[other[0]]=-50+i*100/n;p[other[1]]=-50+j*100/n
            q=[max(-44,min(44,v)) for v in p];d=[p[k]-q[k] for k in range(3)]
            length=math.sqrt(sum(v*v for v in d));v=[q[k]+6*d[k]/length for k in range(3)]
            vertices.append(v)
    for j in range(n):
        for i in range(n):
            a=base+j*(n+1)+i;b=a+1;c=a+n+2;d=a+n+1
            va,vb,vc=vertices[a],vertices[b],vertices[c]
            ab=[vb[k]-va[k] for k in range(3)];ac=[vc[k]-va[k] for k in range(3)]
            normal=[ab[1]*ac[2]-ab[2]*ac[1],ab[2]*ac[0]-ab[0]*ac[2],ab[0]*ac[1]-ab[1]*ac[0]]
            f=[a,b,c,d] if normal[axis]*sign>0 else [a,d,c,b]
            faces.extend([(f[0],f[1],f[2]),(f[0],f[2],f[3])])
obj=os.path.join(out,"SM_RoundedCube.obj")
with open(obj,"w") as f:
    f.write("o RoundedCube\ns 1\n")
    for v in vertices:f.write("v %f %f %f\n"%tuple(v))
    for face in faces:f.write("f %d %d %d\n"%tuple(i+1 for i in face))
task=u.AssetImportTask();task.filename=obj;task.destination_path="/Game/Art";task.destination_name="SM_RoundedCube";task.automated=True;task.replace_existing=True;task.save=True
options=u.FbxImportUI();options.import_mesh=True;options.import_materials=False;options.import_textures=False
options.static_mesh_import_data.set_editor_property("normal_import_method",u.FBXNormalImportMethod.FBXNIM_COMPUTE_NORMALS)
task.options=options
if not u.EditorAssetLibrary.does_asset_exist("/Game/Art/SM_RoundedCube"):
    assets.import_asset_tasks([task])

# Short original synthesized, softly enveloped cues. No third-party samples.
for name,duration,frequency in [("Roll",.12,100),("Land",.16,150),("Switch",.28,640),("Fall",.5,190),("Complete",.8,440)]:
    path=os.path.join(out,name+".wav");rate=44100
    with wave.open(path,"wb") as w:
        w.setnchannels(1);w.setsampwidth(2);w.setframerate(rate)
        data=[]
        for i in range(int(duration*rate)):
            t=i/rate;x=t/duration
            env=min(1,t/.008)*((1-x)**2)
            freq=frequency*(1-.6*x) if name in ("Roll","Land","Fall") else frequency
            value=math.sin(2*math.pi*freq*t)
            if name=="Complete":value=(value+math.sin(2*math.pi*frequency*1.25*t)+math.sin(2*math.pi*frequency*1.5*t))/3
            if name=="Land":value=value*.6+math.sin(i*1.618)*math.exp(-t*65)*.4
            data.append(struct.pack("<h",int(value*env*16000)))
        w.writeframes(b"".join(data))
    t=u.AssetImportTask();t.filename=path;t.destination_path="/Game/Audio";t.automated=True;t.replace_existing=True;t.save=True;assets.import_asset_tasks([t])

# Epic's bundled Niagara burst templates are licensed for use in Unreal projects.
u.AssetRegistryHelpers.get_asset_registry().scan_paths_synchronous(["/Niagara"],force_rescan=True)
source=u.load_asset("/Niagara/DefaultAssets/Templates/Systems/RadialBurst")
if not source:
    raise RuntimeError("Enable Niagara: bundled RadialBurst template is unavailable")
for name in ["NS_Landing","NS_Complete"]:
    if not u.EditorAssetLibrary.does_asset_exist("/Game/FX/"+name):
        assets.duplicate_asset(name,"/Game/FX",source)
# Empty saved world: gameplay construction is owned by the configured C++ game mode.
if not u.EditorAssetLibrary.does_asset_exist("/Game/Maps/Puzzle"):
    u.get_editor_subsystem(u.LevelEditorSubsystem).new_level("/Game/Maps/Puzzle")
u.EditorAssetLibrary.save_directory("/Game",only_if_is_dirty=True,recursive=True)
u.log("BLOXORZ_ASSETS_COMPLETE")
