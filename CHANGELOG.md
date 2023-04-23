# OmegA Changelog

## 3.2
- removing the ratmod delag code
- Keep jumping when holding jump with `pmove_autohop`
- new ammo boxes
- new sound when flag is taken
- scoreboard close immediatly when releasing the tab key
- new flags
- no more upscaled weapon for space saving
- servers are displayed with uppercase and lowercase
- more resolutions in the menu settings
- `g_allowDuplicateGuid`
- mute spec with `g_muteSpectators`
- when someone join a team it's printed in chat instead of displayed in the center
- bot can be muted with `g_botChat` instead of `bot_nochat` who was in the engine code

## 3.2.2
- `g_ambientSounds`
- pass through invisible / clip walls (ty ratmod) with `clipWalls`
- show spawn during warmup (ty ratmod again) with `cg_showSpawns`
- better pul1ctf textures (ty ratmod again again)
- better scoreboard
- headshot bug fix
- small rocket trail and bullet impact changes imported from OA 0.6.0
- `g_startWhenReady` don't listen to bot anymore. It means if you are not ready and there are bots, it will not start the game.
- small ui changes (map select and map loading levelshot)
- `cg_brightPlayers` has now 2 types of skins which can be set with 1 or 2
- new skull icons (displayed in frag messages)
