"""Create an original ambient loop and a lightweight instanced pulse material.
UnrealEditor-Cmd PROJECT -run=pythonscript -script=<absolute forward-slash path>
"""
import unreal as u
import math, os, wave, array

tools=u.AssetToolsHelpers.get_asset_tools()
lib=u.MaterialEditingLibrary
path="/Game/Art/M_ContactPulse"
material=u.load_asset(path) if u.EditorAssetLibrary.does_asset_exist(path) else tools.create_asset("M_ContactPulse","/Game/Art",u.Material,u.MaterialFactoryNew())
lib.delete_all_material_expressions(material)
material.set_editor_property("used_with_instanced_static_meshes",True)
material.set_editor_property("shading_model",u.MaterialShadingModel.MSM_UNLIT)
channels=[]
for index in range(3):
    node=lib.create_material_expression(material,u.MaterialExpressionPerInstanceCustomData,-800,index*100)
    node.set_editor_property("data_index",index);channels.append(node)
ab=lib.create_material_expression(material,u.MaterialExpressionAppendVector,-560,0)
rgb=lib.create_material_expression(material,u.MaterialExpressionAppendVector,-360,0)
interp=lib.create_material_expression(material,u.MaterialExpressionVertexInterpolator,-160,0)
for src,dest,pin in [(channels[0],ab,"A"),(channels[1],ab,"B"),(ab,rgb,"A"),(channels[2],rgb,"B"),(rgb,interp,"")]:
    assert lib.connect_material_expressions(src,"",dest,pin)
gain=lib.create_material_expression(material,u.MaterialExpressionConstant,-160,200);gain.set_editor_property("r",2.2)
multiply=lib.create_material_expression(material,u.MaterialExpressionMultiply,60,0)
lib.connect_material_expressions(interp,"",multiply,"A");lib.connect_material_expressions(gain,"",multiply,"B")
lib.connect_material_property(multiply,"",u.MaterialProperty.MP_EMISSIVE_COLOR)
lib.recompile_material(material);assert u.EditorAssetLibrary.save_loaded_asset(material)

rate=32000;duration=32.0
def frequency(midi):
    return round((440*2**((midi-69)/12))*duration)/duration
chords=[[48,55,59,64],[45,52,55,60],[41,48,52,57],[43,50,57,60]]
voicings=[[frequency(note) for note in chord] for chord in chords]
melody=[72,76,79,76,69,72,76,72,65,69,72,69,67,74,77,74]
notes=[frequency(note) for note in melody]
samples=array.array("f")
peak=0.0;energy=0.0
for i in range(int(rate*duration)):
    t=i/rate;chord=int(t/8)%4;local=t%8
    blend=max(0.0,min(1.0,(local-6)/2));blend=blend*blend*(3-2*blend)
    left=right=0.0
    for c,weight in [(chord,1-blend),((chord+1)%4,blend)]:
        for n,freq in enumerate(voicings[c]):
            phase=2*math.pi*freq*t
            tone=math.sin(phase)+.16*math.sin(2*phase)+.05*math.sin(3*phase)
            amplitude=.023*weight*(.88+.12*math.sin(2*math.pi*t/duration+n))
            left+=tone*amplitude*(1.0 if n%2==0 else .84)
            right+=tone*amplitude*(.84 if n%2==0 else 1.0)
    step=int(t/2)
    for prior in range(4):
        event=(step-prior)%16;age=(t-2*event)%duration
        if age>=7:continue
        envelope=(1-math.exp(-age*35))*math.exp(-age*.85)*max(0,1-age/7)**2
        phase=2*math.pi*notes[event]*age
        note=(math.sin(phase)+.18*math.sin(2*phase)+.06*math.sin(3*phase))*.055*envelope
        left+=note*(1 if event%2 else .72);right+=note*(.72 if event%2 else 1)
    samples.extend((left,right));peak=max(peak,abs(left),abs(right));energy+=left*left+right*right
rms=math.sqrt(energy/len(samples))
normalization=min(.65/max(peak,1e-6),.14/max(rms,1e-6))
pcm=array.array("h",(int(max(-1,min(1,s*normalization)) * 32767) for s in samples))
folder=os.path.join(u.Paths.project_dir(),"Intermediate","GeneratedArt");os.makedirs(folder,exist_ok=True)
wav=os.path.join(folder,"AmbientPuzzle.wav")
with wave.open(wav,"wb") as file:
    file.setnchannels(2);file.setsampwidth(2);file.setframerate(rate);file.writeframes(pcm.tobytes())
task=u.AssetImportTask();task.filename=wav;task.destination_path="/Game/Audio";task.destination_name="AmbientPuzzle";task.automated=True;task.replace_existing=True;task.save=True
tools.import_asset_tasks([task])
music=u.load_asset("/Game/Audio/AmbientPuzzle")
assert music
music.set_editor_property("looping",True)
assert u.EditorAssetLibrary.save_loaded_asset(music)
u.log("BLOXORZ_PRESENTATION_ASSETS_READY duration=32s stereo peak={:.4f} rms={:.4f} looping=True".format(peak*normalization,rms*normalization))
