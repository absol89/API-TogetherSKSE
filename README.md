# STCampfireSync

DJLegends' campfire sync plugin for Skyrim Together. Press **F8** to place a campfire in front of you, or pick up one
you are looking at. Campfires are shared with your party and are removed when their owner leaves. They last for the
current game session and are not written to saves.

This repository contains only `STCampfireSync.dll` and the files needed to build it. It uses Skyrim Together Plugin
API V1 (party messages).

## Requirements

- Skyrim Special Edition **1.6.1170** or **1.7.104**, SKSE and Address Library for SKSE Plugins.
- Skyrim Together **1.8.7-6 or newer** from
  [absol89/TiltedEvolutionScriptFixes](https://github.com/absol89/TiltedEvolutionScriptFixes).
- Visual Studio 2022 with the **Desktop development with C++** workload, [xmake](https://xmake.io), and git.
- CommonLibSSE-NG at commit `b93280e832f263dbef44e44cbe2936622a02f91a`, with the patch in `patches/` applied.

## Build

Put this repository and CommonLibSSE-NG next to each other, then run from this repository (Git Bash shown):

```sh
git clone https://github.com/CharmedBaryon/CommonLibSSE-NG ../CommonLibSSE-NG
git -C ../CommonLibSSE-NG checkout b93280e832f263dbef44e44cbe2936622a02f91a
git -C ../CommonLibSSE-NG apply "$PWD/patches/commonlibsse-ng-skyrim-1.7.patch"
xmake f -p windows -a x64 -m release
xmake build STCampfireSync
```

The DLL and PDB are written to `build/windows/x64/release/`. Keep the PDB beside the DLL for useful crash stacks.

## Install

Copy `STCampfireSync.dll`, `STCampfireSync.pdb`, and `dist/STCampfireSync.ini` to
`Data/SKSE/Plugins/` in the game installation. The default hotkey is F8. `CampfireBaseFormID` defaults to Skyrim's
`Campfire01Burning` (`0x00035F49`).

The plugin log is `Documents/My Games/Skyrim Special Edition/SKSE/STCampfireSync.log`. It stays inactive when Skyrim
Together or its Plugin API V1 is unavailable.

## Credits and license

STCampfireSync is by [DJLegends](https://github.com/DJLegends1011/STCampfireSync), shipped here with permission. This
copy looks up `SkyrimTogetherRequestPluginAPI`, the export name used by Skyrim Together builds 1.8.7-5 and newer.

The project is licensed under GNU GPL v3 (`LICENSE`). The original plugin's license is in
`src/STCampfireSync/LICENSE`; third-party notices for the build are in `dist/THIRD-PARTY-NOTICES.txt`.
