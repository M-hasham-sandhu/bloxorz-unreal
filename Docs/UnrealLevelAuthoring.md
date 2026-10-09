# Unreal level authoring — Bloxorz Level Designer

Open the project at `D:\Unreal\BloxorzUnreal\BloxorzUnreal.uproject`. In Unreal, choose **Tools → Bloxorz Level Designer**. The console command `Bloxorz.LevelDesigner` opens the same tab. This is an editor-only C++/Slate tool; it is not required in a packaged game.

## Create and paint a puzzle

1. Click **New puzzle**. The tool creates a uniquely named `NewLevel` Data Asset in `/Game/Levels`. Rename the asset in the Content Browser if desired, and set its **Data → Level Id** in Details.
2. In Details, set **Data → Grid Size** (1..64 cells per axis), **Start → Orientation**, and optionally Par Moves. The canvas reads those dimensions directly. Shrinking does not silently delete out-of-bounds tiles: validation reports them so you can undo, enlarge the grid, or remove the records deliberately.
3. Select a brush and click/drag over the grid. Normal, Fragile, Switch, Bridge and Erase support dragging. Start, Goal and Link use individual clicks.
4. Place Start on supported cells. Start only sets its anchor; a flat start needs both occupied cells supported. Goal sets the goal coordinate and its tile, replacing the previous Goal tile with Normal.
5. Click **Save**. Puzzles persist as `.uasset` files, not C++ tile arrays. Existing assets can be selected with the picker beneath the toolbar.

Coordinates are bottom-left origin: X right, Y up. Each cell displays its coordinates and type/ID. `S` is the starting anchor; `G` is the goal; `A`/`B` distinguish light/heavy switches; `BR` is a bridge. A flat anchor is the minimum occupied coordinate. Switch targets and other precise records are editable in Details.

### Small two-move test

Create a 4×1 puzzle. Paint Normal at `(0,0)`, `(1,0)`, `(2,0)`; place Goal at `(3,0)`; place a Standing Start at `(0,0)`. Validate: the solution should be `RR`. Save and choose **Play selected**.

## Switches and bridge groups

Select Switch, set a unique Brush ID such as `sw1` (or click **Auto ID**), and optionally enable **Heavy switch** before painting. For another independent switch, choose a new ID. Heavy switches fire only upright and once per reset; light switches toggle on occupied-cell landings.

Select Bridge and use a distinct ID such as `br1`. All bridge cells sharing that ID form one group. Auto ID suggests a free ID but does not automatically change the brush on every stroke, allowing an entire group to be painted with the same ID.

Select Link and click a switch then a bridge, or a bridge then a switch. This toggles that bridge ID in the switch's Targets. Repeat the pair to unlink it. Inspect Targets in Details to confirm the connection. Repainting the same switch type preserves its existing links; erasing or changing a tile to a different type deliberately removes its old record. Bridge groups start closed, and support is checked before switch effects.

Painting strokes and links use Unreal transactions. Undo/Redo are available through the editor's normal commands. The canvas is a data preview, not a 3D map-building viewport.

## Validate and play

**Validate / solve** checks dimensions, duplicate/out-of-bounds cells, initial support, a single matching Goal tile, switch IDs, and bridge target integrity. A bounded breadth-first search then uses the runtime simulation to find a shortest solution. Status shows the move count and `U/D/L/R` path. Budget exhaustion is reported as **unknown**, not unsolvable. Large switch-state spaces may require a higher validation budget or a simpler puzzle.

**Play selected** requires a solved, structurally valid puzzle, saves it, and launches that asset in a standalone play session using the Puzzle map. It does not insert it into the campaign or modify the open map. Custom puzzle previews do not write campaign best-move/progression data.

## Campaign without code changes

Click **Add to campaign** to append the selected level to `/Game/Levels/DA_Campaign`. Click **Campaign order** to edit that asset's Levels array in Details: reorder, remove or replace references, then **Save**. To return to level Details, select a puzzle in the asset picker.

Normal gameplay loads DA_Campaign's ordered soft references; the loader contains no puzzle layouts or hardcoded level count. New campaign levels require saving assets, not recompilation. Rebuild only when changing gameplay or editor code. `/Game/Levels` is included in packaging cook settings.

The 15 original layouts are stored in `DA_Level_01` through `DA_Level_15`. `Docs/UnityCampaign.json` remains their migration reference. `Tools/migrate_campaign_assets.py` is a one-time migration/verification tool: it refuses to overwrite existing edited levels and never replaces an existing campaign. It is not a live Unity synchronization system.

## Boundaries

This version is a manual grid authoring tool, not a random/procedural puzzle generator. Validation establishes solvability, not puzzle quality or difficulty. Review feel, teaching order and presentation by playing the selected level. Asset names, IDs, and campaign ordering are designer responsibilities; campaign progress currently keys best moves by index, so reordering an existing shipped campaign requires a separate progress-migration policy.
