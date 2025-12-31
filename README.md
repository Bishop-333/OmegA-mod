<div align="center">
<img src="omega_logo.svg" alt="OmegA Logo" width="256">
</div>

# OmegA mod
[![Build](https://github.com/Bishop-333/OmegA-mod/actions/workflows/main.yml/badge.svg)](https://github.com/Bishop-333/OmegA-mod/actions/workflows/main.yml)
![License](https://img.shields.io/badge/License-GPLv2-blue.svg)

**OmegA** is a mod for **OpenArena** designed to polish the original experience and add features for both competitive and casual gameplay. <br>
It integrates improvements from different projects like [Ratmod](https://github.com/rdntcntrl/ratoa_gamecode), [Aftershock](https://github.com/Irbyz/aftershock-xe), and [ioquake3](https://github.com/ioquake/ioq3).

## List of some new cvars

### Movement
| Cvar | Description |
| :--- | :--- |
| `pmove_aircontrol` | Enables CPMA-style air control. |
| `pmove_autohop` | Enables holding jump to hop continuously. |
| `pmove_doublejump` | Enables double jump. |

### Competitive
| Cvar | Description |
| :--- | :--- |
| `cg_brightPlayers` | Enables bright player skins for better visibility. |
| `cg_damagePlums` | Displays floating numbers indicating the damage dealt when hitting an enemy. |
| `g_dropFlag` | Allows the flag carrier to drop it manually (requires binding a key). |
| `g_easierPickup` | Increases the item pickup hitbox height. |
| `g_startWhenReady` | Match waits for all players to type `/ready` to start (requires `g_doWarmup`). |

### HUD
| Cvar | Description |
| :--- | :--- |
| `cg_transparentGun` | Renders your weapon model transparent to have a better field of view. |
| `cg_drawItemPickup` | Displays pickup item names. |
| `cg_timerWidth` / `cg_timerHeight` / `cg_timerX` / `cg_timerY` | Adjusts timer size and position. |
| `cg_zoomAnim` / `cg_zoomAnimSpeed` / `cg_zoomToggle` | Configures zoom. |

### Weapons
| Cvar | Description |
| :--- | :--- |
| `g_gauntletDamage` / `g_lightningDamage` / `g_machinegunDamage` / `g_machinegunTeamDamage` / `g_railgunDamage` | Configures weapon damage. |
| `g_grenadeSpeed` / `g_rocketSpeed` | Configures projectile velocity. |
| `g_railgunFireRate` / `g_rocketFireRate` | Configures weapon fire rate. |
| `g_guidedRockets` | Enables guided missiles when you hold the attack button. |
| `g_plasmaBounce` | Enables plasma orbs bouncing off walls instead of exploding on impact. |
| `g_railJump` | Allows rocket jumps for the railgun. |
| `g_teleportMissiles` | Enables projectiles teleporting through portals. |

### Misc
| Cvar | Description |
| :--- | :--- |
| `cg_ambient` | Allows disabling ambient map sounds. |
| `cg_drawEmotes` | Displays emote bubbles above player heads (requires binding keys). |
| `cg_thinLightningBolt` | Renders a thinner lightning bolt. |
| `g_beheading` | Enables railgun headshots that decapitate enemies (gives the "headshot" medal). |
| `g_weaponArena` | Restricts the match to specific weapons. |

## New assets
- font
- icons
- models
- music (can be heard in slimefac)
- sfx
- skins
- sprites

## Building a pk3

Simply go to your terminal and type :

```sh
cd path/to/your/folder/
make
```

## Links

* Mod DB page : https://www.moddb.com/mods/openarena-omega
* Custom OmegA engine : https://github.com/Bishop-333/OmegA-engine

## Donate

I develop during my free time, if you enjoyed my mod or my engine/fork please consider supporting me by donating !
* paypal.me/fatsakura
