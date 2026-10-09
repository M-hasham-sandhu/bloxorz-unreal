"""One-time migration of the supplied layout snapshot into designer-owned assets.
Never overwrites existing puzzles/campaign; verify existing data instead.
Run in UnrealEditor-Cmd PROJECT -run=pythonscript -script=<absolute forward-slash path>.
"""
import json
import os
import unreal as u

records=json.load(open(os.path.join(u.Paths.project_dir(),"Docs","UnityCampaign.json"),encoding="utf-8"))
tools=u.AssetToolsHelpers.get_asset_tools()
tile_types=[u.BloxorzTileType.EMPTY,u.BloxorzTileType.NORMAL,u.BloxorzTileType.FRAGILE,u.BloxorzTileType.SWITCH,u.BloxorzTileType.BRIDGE,u.BloxorzTileType.GOAL]
orientations=[u.BloxorzOrientation.STANDING,u.BloxorzOrientation.LYING_X,u.BloxorzOrientation.LYING_Y]
behaviors=[u.BloxorzSwitchBehavior.TOGGLE,u.BloxorzSwitchBehavior.HEAVY_ONE_SHOT]

def create(name, cls):
    factory=u.DataAssetFactory()
    factory.set_editor_property("data_asset_class",cls.static_class())
    result=tools.create_asset(name,"/Game/Levels",cls,factory)
    if not result: raise RuntimeError("Could not create "+name)
    return result

def signature(data):
    return (str(data.level_id),data.grid_size.x,data.grid_size.y,data.start.anchor.x,data.start.anchor.y,orientations.index(data.start.orientation),data.goal.x,data.goal.y,
            sorted((t.position.x,t.position.y,tile_types.index(t.type),str(t.id) if str(t.id)!="None" else "",tuple(str(n) for n in t.targets),behaviors.index(t.switch_behavior)) for t in data.tiles))

levels=[]
for record in records:
    data=u.BloxorzLevelData()
    data.level_id=record["id"]
    data.grid_size=u.IntPoint(*record["size"])
    data.start=u.BloxorzBlockState(anchor=u.IntPoint(*record["start"]),orientation=orientations[record["orientation"]])
    data.goal=u.IntPoint(*record["goal"])
    data.tiles=[u.BloxorzTile(position=u.IntPoint(t["x"],t["y"]),type=tile_types[t["type"]],id=t["id"],targets=t["targets"],switch_behavior=behaviors[t["behavior"]]) for t in record["tiles"]]
    name="DA_"+record["id"]
    asset=u.load_asset("/Game/Levels/"+name)
    if asset:
        if signature(asset.data)!=signature(data): raise RuntimeError("Existing authored asset differs: "+name+". Not overwriting designer changes.")
    else:
        asset=create(name,u.BloxorzLevelAsset)
        asset.set_editor_property("data",data)
        if not u.EditorAssetLibrary.save_loaded_asset(asset): raise RuntimeError("Save failed: "+name)
    levels.append(asset)

campaign=u.load_asset("/Game/Levels/DA_Campaign")
if not campaign:
    campaign=create("DA_Campaign",u.BloxorzCampaignAsset)
    campaign.set_editor_property("levels",levels)
    if not u.EditorAssetLibrary.save_loaded_asset(campaign):raise RuntimeError("Campaign save failed")
u.log("BLOXORZ_ASSET_MIGRATION_VERIFIED: {} levels; existing assets never overwritten".format(len(levels)))
