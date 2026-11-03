# STCampfireSync

DJLegends' campfire sync plugin for Skyrim Together. Press **F8** to place a campfire in front of you, or pick up one
you are looking at. Campfires are shared with nearby players by default, including players outside your party, and are removed when their owner leaves the local audience. They last for the
current game session and are not written to saves.

This repository contains only `STCampfireSync.dll` and the files needed to build it. It uses Skyrim Together Plugin
API V1 plus the optional scoped-channel registration export. No Plugin API V2 code is included.

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

## Synchronization audience

`NearbySync=1` selects nearby players on STR builds exporting `SkyrimTogetherRegisterScopedChannel`.
Set `NearbySync=0` for party-only delivery; restart the game after changing it. All participants must use the same mode.
Older executables with only `SkyrimTogetherRequestPluginAPI` fall back to party-only. The log reports the selected mode.
An executable without the V1 export cannot support this plugin, regardless of its release label.

The server checks the sender and recipient's worldspace/interior and range for nearby messages. Campfire resends
its local objects when a peer arrives and removes remote objects when that peer leaves. It does not persist
objects on the server: an owner's campfires are unavailable while the owner is disconnected or out of the area.

Validation still requires two clients: F8 placement/removal, late arrival, leaving/re-entering a cell, party-only
isolation, and nearby synchronization without a party.
