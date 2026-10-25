# SFML Game Engine

A C++ and SFML 2.5.1 game engine prototype with a top-down action demo called **Honor Project**. The project brings together a state-based game loop, animated entities, a tile-based world, combat, audio, and weather effects.

## Features

- Main menu and gameplay states managed by a state stack.
- Delta-time updates and a camera that follows the player.
- Eight-direction movement, sprite animation, and melee attacks.
- A grass tile map with scenery, animated trees, obstacle collision, and nearby-tile rendering.
- Mage enemies that pursue the player and fire projectiles.
- A health bar and health restored by defeating enemies.
- Rain effects, ambient sound, attack audio, and background music.

## Requirements

- Windows with Visual Studio 2022 and the **Desktop development with C++** workload.
- MSVC **v143** toolset and a **Windows 10 SDK**, as selected by the project.
- The SFML 2.5.1 headers and libraries in `External/SFML/`, plus the runtime DLLs in `HonorProject/`.

Use an **x64** configuration. Both Debug and Release have SFML include paths and linker settings; the Win32 configurations do not. Release x64 selects C++20.

## Build and run

1. Open `HonorProject.sln` in Visual Studio.
2. Set `HonorProject` as the startup project.
3. Select **Release | x64** or **Debug | x64** and build the solution.
4. Copy the runtime DLLs from `HonorProject/` into the executable's output directory (`x64/Release/` or `x64/Debug/`). Release uses `sfml-*-2.dll`; Debug uses the `sfml-*-d-2.dll` variants. Include `openal32.dll` for audio. Copying all DLLs from `HonorProject/` covers both configurations.
5. In **Project Properties > Configuration Properties > Debugging**, set **Working Directory** to `$(ProjectDir)` for the selected configuration, then run with **F5** or **Ctrl+F5**.

The working directory must be `HonorProject/` so the game can find its relative `Config/` and `Resources/` paths. The build does not automatically copy these folders or the runtime DLLs to the output directory.

Alternatively, use a **Developer PowerShell for Visual Studio 2022** from the repository root:

```powershell
msbuild .\HonorProject.sln /m /p:Configuration=Release /p:Platform=x64
Copy-Item .\HonorProject\*.dll .\x64\Release\
Set-Location .\HonorProject
& ..\x64\Release\HonorProject.exe
```

For a standalone runnable folder, place `Config/`, `Resources/`, and the matching runtime DLLs beside `HonorProject.exe`, then launch with that folder as the working directory.

## Controls

| Input | Action |
| --- | --- |
| W / A / S / D | Move up / left / down / right |
| Left mouse button | Attack |
| Escape | Return from gameplay to the main menu |
| New Game | Start the demo |
| Quit or window close button | Exit the application |

## Configuration

Settings are read from `HonorProject/Config/`:

| File | Purpose |
| --- | --- |
| `window.ini` | Window title, resolution, fullscreen mode, frame limit, VSync, and antialiasing, in that order |
| `supportedKeys.ini` | Maps key names to SFML keyboard codes |
| `controlKeys.ini` | Maps gameplay actions to supported key names |

The default window is **1920 x 1080**, windowed, with a **144 FPS** limit, VSync disabled, and no antialiasing. To change movement bindings, edit `controlKeys.ini` using key names defined in `supportedKeys.ini`.

## Project layout

```text
SFML_Game_Engine/
|-- HonorProject.sln          Visual Studio solution
|-- External/SFML/           SFML headers and link libraries
`-- HonorProject/
    |-- main.cpp             Application entry point
    |-- Game.*               Window, game loop, and state stack
    |-- *State.*             Base state, main menu, and gameplay
    |-- Entity.*, Player.*   Entity behavior and player animation
    |-- Enemy.*, Mage.*      Enemies and combat behavior
    |-- *Bullet.*            Projectile behavior
    |-- Tile*.*, AnimeTree.* Tile map, scenery, and collision
    |-- SpriteAnimation.*    Sprite animation playback
    |-- GUI.*, Button.*      Health display and menu buttons
    |-- Weather.*, Rain.*    Weather effects and ambient audio
    |-- Config/              Window and input configuration
    `-- Resources/           Textures, fonts, music, and sounds
```

## Prototype notes

- The **Settings** menu button is a placeholder.
- The player starts with invincibility enabled in `GameState::initPlayers()`. Health can decrease, but the zero-health return to the menu is suppressed while this flag is enabled.
- The repository currently provides a Visual Studio build; no CMake project or automated test suite is included.

The `.gitignore` excludes Visual Studio caches, per-user settings, executables, and generated build directories. SFML libraries, runtime DLLs, configuration, and game assets remain eligible for version control.
