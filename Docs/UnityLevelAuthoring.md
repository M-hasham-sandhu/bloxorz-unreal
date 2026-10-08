# Creating levels with your existing Unity editor

These instructions come from the supplied project's actual `LevelAuthoringWindow`, `LevelDataAssetEditor`, `LevelValidationUtility`, and campaign-loading code. They are source-verified; this guide was not verified by a new interactive Unity authoring session. No Unity files were modified.

## 1. Open and create a level

1. Open `C:\Git\Bloxorz-Clone-Game` in Unity.
2. Choose **Bloxorz → Visual Level Editor**. Alternatively, select an existing level asset and click **Open Visual Level Editor** in its Inspector.
3. Enter a unique **New Level Name**, such as `Level_16`, then click **Create**. The asset is created at `Assets/Levels/Level_16.asset`; an existing asset with that name is rejected rather than overwritten.
4. Check **Level Id** and **Start Orientation**. Start with `Standing` for a conventional level.
5. Set **Width** and **Height**, then click **Resize Grid**. New assets initially use the window's current dimensions, so explicitly set dimensions after creation.

Grid coordinates start at `(0,0)` in the bottom-left. X increases right; Y increases up. The canvas draws the highest Y row at the top. A flat block's anchor is the minimum occupied coordinate: `LyingX` covers anchor and `(x+1,y)`; `LyingY` covers anchor and `(x,y+1)`.

## 2. Paint the layout and markers

- Choose **Paint → Normal**, then click/drag to create the playable surface.
- Choose **Empty** to erase cells and carve gaps. **Fill Grid** uses the current tile brush; **Clear Grid** removes tiles.
- Choose **Fragile** to paint cells that support a flat block but fail an upright block.
- Choose **Start** (or **Markers → Place: Start**) and click the start cell. This places only the start marker: it does **not** automatically add a supporting tile. Paint the supporting tile first, and support both occupied cells if the start pose is flat.
- Choose **Goal** (or **Markers → Place: Goal**) and click a cell. This sets the goal coordinate and replaces that cell with a Goal tile. Completion requires the block to stand upright there.
- Right-click a cell for the quick picker: Empty, Normal, Fragile, Set Start, Set Goal, Switch, Bridge.

Avoid shrinking the grid after finishing a layout: Resize Grid removes out-of-bounds tiles and clamps start/goal coordinates. Clear Grid removes tiles but leaves marker coordinates. Check both markers after either action.

### Tiny starter level

Use a 6×3 grid. Paint Normal tiles at `(1,1)`, `(2,1)`, `(3,1)`, `(4,1)`. Place a Standing start at `(1,1)` and the goal at `(4,1)`. Two right moves should solve it: first lie across `(2,1)` and `(3,1)`, then stand at `(4,1)`.

This is a walkthrough derived from the roll rules, not a newly saved/tested Unity level asset.

## 3. Add switches and bridges

1. Choose **Switch**. Select **Type A** for a light toggle switch or **Type B** for an upright-only one-shot heavy switch.
2. Set/check **Switch ID**. Use separate IDs such as `sw1`, `sw2` for independent switches. **Auto** suggests the next unused ID; do not assume every brush stroke automatically changes the selected ID.
3. Paint the switch cell on a reachable route.
4. Choose **Bridge**, check **Bridge ID**, and paint the bridge cells. Use an ID such as `br1`, distinct from the switch's `sw1`. Multiple bridge cells with the same bridge ID operate as one group.
5. Choose **Link**. Click a switch, then a bridge, or a bridge then a switch. This stores the bridge ID in that switch's target list. For a bridge group, linking one cell targets all cells with that ID.
6. Check **Switch Links** in the tool panel and the matching tint on linked cells. Click an already-linked pair again to unlink it, or use the summary's **Unlink** button. Selection clears after a pair, so repeat the pair selection for each additional bridge group.

Both switch types toggle targets when triggered. Type A reacts to valid occupied-cell landings in either orientation; Type B requires upright contact and fires only once until reset. Bridges start closed. The block cannot use a closed bridge as support on the same move that would activate its switch: support is checked before switch effects.

Important: repainting a switch creates a new entry with an empty target list, even when changing its type. Re-link it afterwards. Shared switch IDs also share the one-shot trigger identity for Type B, so keep independent switches uniquely identified.

## 4. Validate and save

1. Click **Validate Level** in the authoring window, or **Validate Level (BFS Solver)** in the asset Inspector.
2. Read the Unity Console. The tool reports structural warnings and either `SOLVABLE in N moves` or `NOT SOLVABLE`, including explored-state count.
3. Fix missing/incorrect bridge IDs, target links, unsupported starting cells, and goal orientation access. A structural warning can appear even if the solver finds a path that bypasses the defective feature.
4. Save the project/assets outside Play mode, then playtest. Edits mark the asset dirty; creation explicitly saves the new asset, but there is no dedicated Save button in the authoring window.

The solver proves a path under the rules; it does not judge difficulty, camera readability, accidental shortcuts, or player teaching. Verify the intended route as well as the shortest route.

## 5. Make the level available in the game

Creating a level asset does not automatically append it to the campaign.

1. Select `Assets/Levels/LevelSequence.asset`.
2. Add an element to its **Levels** list and drag your new level asset into it. List order determines progression; reorder it if needed.
3. Open `Assets/Scenes/Gameplay Scene.unity` and verify the relevant LevelManager/UI references use that sequence. The supplied scene already references the existing LevelSequence asset.
4. Enter Play mode, use the level-selection flow, and test the level. After finishing the campaign, the Unity LevelManager wraps back to the first level.

For an isolated level test, a LevelManager without a nonempty Level Sequence loads its **Level Data** field. A nonempty sequence takes precedence on normal startup, so assigning only Level Data while leaving the sequence populated will not select your test level. Preserve your normal scene configuration when setting up a temporary test scene.

## 6. Bring it into Unreal

There is currently **no automatic importer**. The Unreal `Docs/UnityCampaign.json` is a snapshot, and the runtime campaign comes from `Source/BloxorzUnreal/Private/BloxorzCampaign.cpp`. Neither editing Unity assets nor changing that JSON alone updates Unreal.

A new port must preserve grid size, start anchor/orientation, goal coordinate, every nonempty tile position/type, IDs, target lists, and switch behavior. Unity enum mappings currently match the port: Empty=0, Normal=1, Fragile=2, Switch=3, Bridge=4, Goal=5; Standing=0, LyingX=1, LyingY=2; Type A=0, Type B=1.

Append the converted level to the Unreal campaign, rebuild, and run the Bloxorz tests and an animated solution replay. Update the campaign test's expected level count when adding levels; it currently asserts 15. For immediate Unreal experimentation, a placed Board actor with a populated Level record overrides the stock campaign. A validated export/import pipeline is the recommended next improvement, not something already present.
