# Bloxorz Unreal — project context and review handoff

## Purpose and current status

The latest presentation pass removes the old visible branding and bottom-left instructions, introduces rounded outcome panels and contact/bridge pulses, and adds an original looping ambient track. Rendering is isolated in `BloxorzHUD.cpp`; music parameters are exposed on the Board. See `Docs/PresentationUpdate.md`. The old internal save-slot name is retained for compatibility. Offscreen gameplay/outcome captures and seven regression tests pass; live audio listening and interactive UI review remain manual.

Recreate the supplied Unity Bloxorz project as a portfolio-oriented Unreal gameplay-engineering project. Deterministic rules, exact rolling, and maintainability take priority over presentation. The current implementation includes all 15 reference levels and a presentation pass; final portfolio acceptance still requires manual playtesting and packaged-build profiling.

Local Unreal project: `D:\Unreal\BloxorzUnreal`.
Unity behavior/data reference: `C:\Git\Bloxorz-Clone-Game`.
Remote: https://github.com/M-hasham-sandhu/bloxorz-unreal.
Implementation review baseline: commit `d494e67` on `main` (previous baseline `a61c671`).

Build environment verified: Unreal 5.8.3, Visual Studio 2022/MSVC 14.44, Windows SDK 10.0.26100. Hardware checked: RTX 4060 Laptop GPU, i7-14700HX, 32 GB RAM.

## Recommended review order in Fork

1. The initial presentation implementation is in `d494e67`. Review the new asset/designer changes in Local Changes; they are not committed or pushed automatically.
2. Read `Public/BloxorzSimulation.h` and `Private/BloxorzSimulation.cpp` under `Source/BloxorzUnreal`: data contracts, twelve roll transitions, support, switch effects, goals.
3. Read `Private/BloxorzCampaignTests.cpp` and `Private/BloxorzSimulationTests.cpp`: test evidence and solver coverage.
4. Read `Public/BloxorzBoard.h` and `Private/BloxorzBoard.cpp`: animation phases, edge pivots, input buffering, bridge animation, camera fit, feedback, saving.
5. Read `Private/BloxorzGameMode.cpp`: input bindings, HUD panels, lighting setup.
6. Check `Config/DefaultEngine.ini`, `Config/DefaultGame.ini`, presentation assets under `Content`, and `Tools/build_assets.py`.

## Architecture and invariants

- `FBloxorzSimulation` is the authoritative, pure grid-rules layer. It consumes level/state data and returns a move result without mutating input state. Physics and mesh transforms never decide puzzle outcomes.
- `FBloxorzLevelData` describes dimensions, start pose, goal, and tile entries. A tile holds position, behavior, identifier, and switch targets.
- `ABloxorzBoard` owns state and presentation. A requested move creates a pending result; animation rotates around the contact edge; valid state commits at landing. Phases distinguish rolling, falling, completion animation, and terminal panels.
- Failed moves preserve the last valid logical state and flags. Revive restores that state; restart reinitializes the level and replenishes three revives.
- World-space grid Y is negative world Y. The fitted camera makes positive grid X read screen-right and positive grid Y read screen-up.
- One command can be buffered during a roll; it expires after 0.35 seconds. Input is discrete key presses, not a continuous held-key repeat scheme.
- `UBloxorzProgress` saves best move counts and unlocked progression locally. Level browsing is not gated by unlock state. Startup currently selects level 1 unless a command-line level override is supplied.

Keep additional puzzle rules in the simulation. Add effects as consumers of resolved outcomes, not as sources of gameplay decisions. Presentation settings and level records are Blueprint-exposed. The campaign now uses editable `UBloxorzLevelAsset` records and a `UBloxorzCampaignAsset` ordered list. The separate editor-only `BloxorzUnrealTools` module provides a Slate grid designer, transactions, structural/BFS validation, campaign editing and standalone preview.

## Reference behavior to preserve

Normal tiles support all poses. Fragile tiles support a flat block but fail an upright one; they do not permanently collapse. Light switches (Unity Type A) toggle their targets on valid occupied-cell landings, including overlapping cells. Heavy switches (Type B) trigger once per reset and only when upright. Linked bridges begin closed. Support is evaluated before switch effects, with no second support check on the same move. Goals require an upright block at the goal coordinate.

The supplied Unity version has no split-block mechanic. Do not infer it from the commercial Bloxorz game. Unreal intentionally adds a completion panel/explicit Continue action instead of Unity's automatic next-level timing, and adds a short input buffer instead of discarding every input during a roll.

## Content and authoring

`Docs/UnityCampaign.json` is a migration snapshot. The live layouts are `/Game/Levels/DA_Level_01` through `DA_Level_15`, and `/Game/Levels/DA_Campaign` controls order. `Private/BloxorzCampaign.cpp` only loads those assets: it contains no puzzle layouts. There is **no live Unity-to-Unreal watcher**; the one-time migration script creates missing assets and refuses to overwrite existing edited levels.

For Unreal authoring, choose Tools → Bloxorz Level Designer and follow [the guide](Docs/UnrealLevelAuthoring.md). Save a puzzle and append/reorder it in the campaign without rebuilding C++. Standalone selected-asset previews do not write campaign progress. The legacy inline Board Level override is retained for compatibility, but Level Asset takes precedence. Campaign progress remains index-keyed; reordering a shipped campaign needs a separate save-migration policy.

Presentation mesh/materials and synthesized sounds were created for this project. Niagara assets derive from Epic's bundled RadialBurst template and remain subject to its engine content license. Unity layouts came from the supplied project. Do not add Friv branding, proprietary assets, or claim a blanket license for all content.

## Verification and known limits

- Development Editor builds and links successfully on Unreal 5.8.3.
- Seven automation tests passed, adding asset validation and editor paint/link coverage to roll/tile rules, heavy-switch/support ordering, pivot endpoints, and campaign solvability. All 15 assets were reloaded and compared against the extraction snapshot, and the asset-backed level-15 replay completed in 39 moves. Interactive tool ergonomics and its standalone play button remain manually unverified.
- Rendered gameplay replays completed level 14 in 19 moves and level 15 in 39 moves. Camera framing was inspected on those boards.
- Final 1600×900 offscreen level-15 run: 22.54 ms mean / 36.30 ms p95 over 755 samples. A separate headless regression run was active during that sample. Do not claim sustained 60 FPS or use the earlier static 8 ms comparison as gameplay performance.
- Human input feel, audio mixing, all-level visual playthroughs, unusual viewport sizes, and packaged Development/Shipping builds remain unverified. See [validation checklist](Docs/Validation.md).

Build the `BloxorzUnrealEditor Win64 Development` target using the engine's Build.bat and the absolute `.uproject` path. Run UnrealEditor-Cmd with `-ExecCmds="Automation RunTests Bloxorz; Quit" -unattended -nullrhi` for the regression suite. Close the editor normally before rebuilding if it holds the gameplay DLL; do not force-kill an editor containing unsaved work.

## Useful next work

1. Manual keyboard/mouse/audio playthrough and edge-case review across the campaign.
2. A repeatable Unity export → Unreal import/generation pipeline, with schema validation and switch-link checks.
3. Expand the new designer with richer 3D previews and difficulty metrics after human authoring review.
4. Packaged-build Unreal Insights capture; reduce remaining frame-time spikes before claiming a stable target.
5. Reformat presentation code into smaller, clearly named units as the feature set grows. The simulation/presentation boundary is already separate, but the Board currently coordinates several presentation responsibilities.
