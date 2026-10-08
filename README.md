# Obsidian Fold

A C++ Unreal Engine 5.8 recreation of the mechanics found in the accompanying Unity Bloxorz reference project. The project uses original engine primitives and runtime-created materials; no Friv branding or proprietary presentation assets are included.

## Architecture

- `FBloxorzSimulation` is a pure deterministic rules layer. Puzzle outcomes do not depend on collision or physics.
- `ABloxorzBoard` owns runtime state, builds authored tile data, and turns state transitions into presentation.
- `ABloxorzPlayerController` maps keyboard input to discrete commands; input is locked during movement.
- All authoring records and presentation timings are Blueprint-exposed.

The showcase is a faithful data port of Unity `Level_14`, selected because it covers normal/fragile tiles, light and heavy switches, two bridge links, gaps, falling, restart, and upright-only completion.

## Controls

- Move: WASD or arrow keys
- Restart: R

## Build and tests

Generate project files, build `BloxorzUnrealEditor Win64 Development`, then run automation tests matching `Bloxorz.Simulation`.
