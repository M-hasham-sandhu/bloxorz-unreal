# Validation and review checklist

## Automated evidence

- Unreal 5.8.3 Development Editor compiled and linked successfully.
- Five tests passed: RollTable, TileRules, HeavySwitchAndSupportOrder, PivotEndpoints, AllLevelsSolvable.
- The campaign solver found a valid path for all 15 imported levels, including level 15's 39-move path. This proves solvability under the ported rules, not exhaustive visual QA of every path.
- An actual rendered Board replay completed level 14 in 19 moves, exercising rolling, fragile support, switches, bridges, and completion outside the pure solver.
- Captures are in Saved/Screenshots/WindowsEditor; logs are in Saved/Logs. These generated artifacts are not source-controlled.

## Presentation decisions

The camera fits projected board bounds, including block height, to the viewport with HUD clearance. Mild perspective and near-axis yaw retain directional clarity. Motion blur is disabled, exposure is fixed, and landing camera displacement is small and damped. Symbols distinguish switch types; fragile tiles have crack markings; goals have a real aperture.

Tile bodies/caps use instancing and per-instance color. Only moving bridge transforms update each frame. Lightweight original sparks are capped at 100 concurrent particles, with restrained Niagara impact/completion bursts. No puzzle outcome uses physics. Profiling runs skip progress writes.

Rendering defaults use conventional shadows, FXAA, and medium shadow/post-processing/effect scalability, with Lumen disabled. On the RTX 4060 Laptop GPU, the 1600×900 offscreen level-15 smoke comparison measured 7.99 ms mean / 9.88 ms p95 across 1,128 sampled frame intervals, versus 80.95 ms mean with the initial Lumen/virtual-shadow setup. These short editor-runtime samples include neither a packaged-build trace nor comprehensive gameplay workloads. FXAA favors latency over temporal edge smoothing; TAA can be enabled for presentation capture, at a measured cost in this environment.

The final animated level-15 run completed 39 moves with the project defaults and measured 22.54 ms mean / 36.30 ms p95 across 755 samples. This is the more representative smoke result; the static comparison's 8 ms must not be advertised as sustained gameplay performance. A stable 60 FPS target is not yet verified. The regression suite was also running headlessly during this final sample, so a standalone packaged trace is needed before further tuning decisions.

## Manual review still required

- Rapid keyboard input, focus loss, and mouse interaction feel.
- Audio loudness/mix on the intended device; offscreen rendering is not a listening test.
- Falling/revive/restart/menu transitions across every level and unusual input timing.
- Camera/HUD on ultrawide, portrait, high-DPI, and tiny windows beyond rendered smoke checks.
- Packaged Development/Shipping build and a longer Unreal Insights GPU/CPU capture at target resolution. Editor/offscreen frame intervals are not shipping performance.

Passing the solver is not final portfolio acceptance. A human playthrough and presentation review remain part of that acceptance.
