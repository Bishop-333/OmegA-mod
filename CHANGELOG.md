# OmegA Changelog

## 3.2
- remove the ratmod delag code
- keep jumping when holding jump with `pmove_autohop`
- new ammo boxes
- new sound when flag is taken
- scoreboard closes immediately when releasing the tab key
- new flags
- no more upscaled weapon for space saving
- servers are displayed with uppercase and lowercase
- more resolutions in the menu settings
- `g_allowDuplicateGuid`
- mute spec with `g_muteSpectators`
- print in the chat when someone join a team instead of displaying it in the center of the screen
- allow bot muting with `g_botChat` instead of `bot_nochat` which was in the engine code

## 3.2.2
- `g_ambientSound`
- pass through invisible / clip walls (ty ratmod) with `clipWalls`
- show spawn during warmup (ty ratmod again) with `cg_showSpawns`
- better pul1ctf textures (ty ratmod again again)
- better scoreboard
- headshot bug fix
- small rocket trail and bullet impact changes imported from OA 0.6.0
- `g_startWhenReady` ignore bots. It means if you are not ready and there are bots, it will not start the game.
- small ui changes (map select and map loading levelshot)
- `cg_brightPlayers` has now 2 types of skins which can be set with 1 or 2
- new skull icons (displayed in frag messages)

## 3.2.3
- show to spectators when the people they watch is zooming  with `cg_showSpecZoom`
- display in the scoreboard when someone is dead or typing
- small particle effect with the shotgun, disable with `cg_shotgunSparks`
- choose to play with only one weapon with `g_weaponArena`, displayed in the server settings instead of `g_rockets`
- new blood effect and fix `cg_leiEnhancement`
- when `g_botchat` = 0, bots don't even stop to type an empty message
- new numbers
- Server name, map name, gametype and lockteam when teams are locked are displayed in the scoreboard
- new shell shaders for quaddamage and battlesuit powerup (we can see the bright outline now)
- add mod-based server filtering, no more OmegA in the gametype filter
- add a Local+Internet filter for servers

## 3.2.4
- remove `clipWalls` as it has bugs
- `g_railgunSpeed` -> `g_railgunFireRate`
- add `rocketFireRate`
- `g_airControl` does the CPM air control instead of just control the movement in air
- fix alpha channels on some textures (like some OmegA logos who have the OpenArena logo hidden in the alpha channel)
- add credits.txt

## 3.2.5
- higher quality menu buttons
- multiply headshot damage with `g_headDamageMultiplicator`
- add the possibility to disable high-pitched hitsound when you frag someone with `cg_killSound` 

## 3.2.6
- new blood effects (screen blood and hit blood)
- `cg_bobgun` activated by default
- fix "Headshot!" message position
- fix SinglePlayer stuck at tutorial
- when you're spawnprotected, you have a battlesuit shell
- `cg_brightPlayers` can now be disabled

## 3.2.7
- no more orbital view when spectating only third-person
- clean compiler warnings
- `cg_trueLightning` enabled by default

## 3.2.8
- new health models/effects
- shotgun laser animation
- new pm skins
- change the impact of effect color bars (first one is for railgun color, second one is for pm skins color)
- better `cg_wallhack`
- `r_ext_supersample` available in graphic settings as "supersampling"
- teleport missile sound

## 3.2.9
- `s_worldSound`, `cg_hitSound`, `cg_killSound` are in the sound settings menu now
- `cg_transparentGun`, `cg_drawGun` in the preferences menu
- `r_drawflat`, `r_mode -2` in the graphic settings menu
- `fwd_use` and `fwd_address` in the network settings menu
- `g_chaos` set every weapon fire-rate to maximum
- `g_railThroughwalls` railgun can kill through a wall
- dead cpm skins become grey
- update defaults
- fix flares with Quake3e/Omega-engine
- `cg_shadows` have now 4 different types
- cleanup (- 4 Mo)
- switch up to openarena with a button in the main menu
- remove statistics in the menu
- new machinegun skin
- Sarge/Neon neons colors change like cpm
- new health models
- `cg_switchCycle` if set to 0, weapon switch will not cycle

## 3.3.0
- better chat balloon
- bind zoom to mouse2 by default
- fix runes pickup sound
- `cg_forceTeamSkins` if set to 0, you can choose the character color you want in team gametypes
- drop flag keybind in the menu
- fix battlesuit
- fix runes effect with `cg_brightPlayers` enabled
- `g_spawnProtect` is 1 second by default now

## 3.3.1
- dmflags settings in the multiplayer menu
- `g_bluerespawtime` and `g_redrespawntime` for team specific respawn time
- new reward system imported from ratmod
- `elimination_items` if set to 1, enable items pickup in elimination modes

## 3.3.2
- ui updates
- favorite server save button
- fix builtin resolutions
- add hdr setting in the menu
- fix ratio display in the menu

## 3.3.3
- better file compression
- add hidden skins
- `g_railThroughwalls` now disables railjump
- `elimination_items` now has an effect in LMS mode
- fix issue with `g_survivorsRespawn` in Elimination CTF
- draw a message when you're the last survivor in your team in elimination modes
- add emotes
- add v-sync setting in the menu
- better damage plums

## 3.3.4
- new pickup items display
- new crosshair names display imported from OpenSandbox
- add random bot option in the in-game menu
- warning clean, fixes and other optimizations

## 3.3.5
- code and assets cleanup
- better and adaptative font
- AI fixes and enhancements
- dynamic lights now for plasma and bfg
- gibs are launched in function of the impact location
- update qvm tools and makefile
- better pmove_aircontrol (CPM accurate)
- better `g_plasmaBounce` (no more grenade sound)
- better `g_guidedRockets` (don't shoot another rocket if your holding attack)
- don't force inactive players to go spectator now it's defined by `g_forcespectator`
- add mutliple explicit cvars (`pmove_doublejump`, `g_spectateOnDeath`, `g_noInvisWalls`)
