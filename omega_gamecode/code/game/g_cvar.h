#ifdef EXTERN_G_CVAR
#define G_CVAR( vmCvar, cvarName, defaultString, cvarFlags, modificationCount, trackChange, teamShader ) extern vmCvar_t vmCvar;
#endif

#ifdef DECLARE_G_CVAR
#define G_CVAR( vmCvar, cvarName, defaultString, cvarFlags, modificationCount, trackChange, teamShader ) vmCvar_t vmCvar;
#endif

#ifdef G_CVAR_LIST
#define G_CVAR( vmCvar, cvarName, defaultString, cvarFlags, modificationCount, trackChange, teamShader ) { &vmCvar, cvarName, defaultString, cvarFlags, modificationCount, trackChange, teamShader },
#endif

// don't override the cheat state set by the system
G_CVAR( g_cheats, "sv_cheats", "", 0, 0, qfalse, qfalse )

G_CVAR( g_restarted, "g_restarted", "0", CVAR_ROM, 0, qfalse, qfalse )
G_CVAR( g_mapname, "mapname", "", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse, qfalse )

// latched vars
G_CVAR( g_gametype, "g_gametype", "0", CVAR_SERVERINFO | CVAR_USERINFO | CVAR_LATCH, 0, qfalse, qfalse )

G_CVAR( g_maxclients, "sv_maxclients", "8", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_maxGameClients, "g_maxGameClients", "0", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse, qfalse )

// change anytime vars
G_CVAR( g_dmflags, "dmflags", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_videoflags, "videoflags", "7", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_elimflags, "elimflags", "0", CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( g_voteflags, "voteflags", "0", CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( g_fraglimit, "fraglimit", "20", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_timelimit, "timelimit", "0", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_capturelimit, "capturelimit", "8", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )

G_CVAR( g_synchronousClients, "g_synchronousClients", "0", CVAR_SYSTEMINFO, 0, qfalse, qfalse )
G_CVAR( g_friendlyFire, "g_friendlyFire", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )

G_CVAR( g_teamAutoJoin, "g_teamAutoJoin", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_teamForceBalance, "g_teamForceBalance", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_warmup, "g_warmup", "20", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_doWarmup, "g_doWarmup", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_logfile, "g_log", "games.log", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_logfileSync, "g_logsync", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_password, "g_password", "", CVAR_USERINFO, 0, qfalse, qfalse )

G_CVAR( g_banIPs, "g_banIPs", "", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_filterBan, "g_filterBan", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_needpass, "g_needpass", "0", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse, qfalse )

G_CVAR( g_dedicated, "dedicated", "0", 0, 0, qfalse, qfalse )

G_CVAR( g_speed, "g_speed", "320", 0, 0, qtrue, qfalse )
G_CVAR( g_gravity, "g_gravity", "800", 0, 0, qtrue, qfalse )
G_CVAR( g_gravityModifier, "g_gravityModifier", "0.940", 0, 0, qtrue, qfalse )
G_CVAR( g_damageModifier, "g_damageModifier", "0", 0, 0, qtrue, qfalse )
G_CVAR( g_knockback, "g_knockback", "1000", 0, 0, qtrue, qfalse )
G_CVAR( g_quadfactor, "g_quadfactor", "3", 0, 0, qtrue, qfalse )
G_CVAR( g_weaponRespawn, "g_weaponrespawn", "5", 0, 0, qtrue, qfalse )
G_CVAR( g_weaponTeamRespawn, "g_weaponTeamRespawn", "30", 0, 0, qtrue, qfalse )
G_CVAR( g_forcerespawn, "g_forcerespawn", "20", 0, 0, qtrue, qfalse )
G_CVAR( g_respawntime, "g_respawntime", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_bluerespawntime, "g_bluerespawntime", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_redrespawntime, "g_redrespawntime", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_inactivity, "g_inactivity", "0", 0, 0, qtrue, qfalse )
G_CVAR( g_debugMove, "g_debugMove", "0", 0, 0, qfalse, qfalse )
G_CVAR( g_debugDamage, "g_debugDamage", "0", 0, 0, qfalse, qfalse )
G_CVAR( g_debugAlloc, "g_debugAlloc", "0", 0, 0, qfalse, qfalse )
G_CVAR( g_motd, "g_motd", "", 0, 0, qfalse, qfalse )
G_CVAR( g_motdfile, "g_motdfile", "motd.cfg", 0, 0, qfalse, qfalse )
G_CVAR( g_blood, "com_blood", "2", 0, 0, qfalse, qfalse )

G_CVAR( g_podiumDist, "g_podiumDist", "80", 0, 0, qfalse, qfalse )
G_CVAR( g_podiumDrop, "g_podiumDrop", "70", 0, 0, qfalse, qfalse )

//Votes start:
G_CVAR( g_allowVote, "g_allowVote", "1", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_maxvotes, "g_maxVotes", MAX_VOTE_COUNT, CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_voteNames, "g_voteNames", "/map_restart/nextmap/map/g_gametype/kick/clientkick/g_doWarmup/timelimit/fraglimit/shuffle/", CVAR_ARCHIVE, 0, qfalse, qfalse ) //clientkick g_doWarmup timelimit fraglimit
G_CVAR( g_voteBan, "g_voteBan", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_voteGametypes, "g_voteGametypes", "/0/1/3/4/5/6/7/8/9/10/11/12/13/", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_voteMaxTimelimit, "g_voteMaxTimelimit", "1000", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_voteMinTimelimit, "g_voteMinTimelimit", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_voteMaxFraglimit, "g_voteMaxFraglimit", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_voteMinFraglimit, "g_voteMinFraglimit", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_votemaps, "g_votemapsfile", "votemaps.cfg", 0, 0, qfalse, qfalse )
G_CVAR( g_votecustom, "g_votecustomfile", "votecustom.cfg", 0, 0, qfalse, qfalse )

G_CVAR( g_listEntity, "g_listEntity", "0", 0, 0, qfalse, qfalse )

G_CVAR( g_obeliskHealth, "g_obeliskHealth", "2500", 0, 0, qfalse, qfalse )
G_CVAR( g_obeliskRegenPeriod, "g_obeliskRegenPeriod", "1", 0, 0, qfalse, qfalse )
G_CVAR( g_obeliskRegenAmount, "g_obeliskRegenAmount", "15", 0, 0, qfalse, qfalse )
G_CVAR( g_obeliskRespawnDelay, "g_obeliskRespawnDelay", "10", CVAR_SERVERINFO, 0, qfalse, qfalse )

G_CVAR( g_cubeTimeout, "g_cubeTimeout", "30", 0, 0, qfalse, qfalse )

G_CVAR( g_enableDust, "g_enableDust", "0", CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_enableBreath, "g_enableBreath", "0", CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_proxMineTimeout, "g_proxMineTimeout", "20000", 0, 0, qfalse, qfalse )

G_CVAR( g_smoothClients, "g_smoothClients", "1", 0, 0, qfalse, qfalse )
G_CVAR( pmove_fixed, "pmove_fixed", "0", CVAR_SYSTEMINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( pmove_msec, "pmove_msec", "8", CVAR_SYSTEMINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( pmove_float, "pmove_float", "1", CVAR_SYSTEMINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )

//unlagged - server options
G_CVAR( g_delagHitscan, "g_delagHitscan", "1", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_truePing, "g_truePing", "1", CVAR_ARCHIVE, 0, qtrue, qfalse )
// it's CVAR_SYSTEMINFO so the client's sv_fps will be automagically set to its value
G_CVAR( sv_fps, "sv_fps", "40", CVAR_SYSTEMINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_lagLightning, "g_lagLightning", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
//unlagged - server options

G_CVAR( g_rankings, "g_rankings", "0", 0, 0, qfalse, qfalse )
G_CVAR( g_localTeamPref, "g_localTeamPref", "", 0, 0, qfalse, qfalse )
G_CVAR( g_music, "g_music", "", 0, 0, qfalse, qfalse )
G_CVAR( g_spawnprotect, "g_spawnprotect", "1000", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
//Now for freezetag stuff:
G_CVAR( g_freeze, "g_freeze", "0", CVAR_SERVERINFO | CVAR_LATCH, 0, qtrue, qfalse )
G_CVAR( g_freezeRespawnInplace, "g_freezeRespawnInplace", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_thawTime, "g_thawTime", "3", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_freezeEnvironmentalRespawnDelay, "g_freezeEnvironmentalRespawnDelay", "2", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_thawTimeDied, "g_thawTimeDied", "60", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_autoThawTime, "g_autoThawTime", "60", CVAR_ARCHIVE, 0, qfalse, qfalse )
//Now for elimination stuff:
G_CVAR( g_elimination_selfdamage, "elimination_selfdamage", "0", 0, 0, qtrue, qfalse )
G_CVAR( g_elimination_startHealth, "elimination_startHealth", "200", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_startArmor, "elimination_startArmor", "150", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_bfg, "elimination_bfg", "0", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_roundtime, "elimination_roundtime", "120", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_warmup, "elimination_warmup", "7", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_activewarmup, "elimination_activewarmup", "5", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_allgametypes, "g_elimination", "0", CVAR_LATCH | CVAR_NORESTART, 0, qfalse, qfalse )

G_CVAR( g_elimination_machinegun, "elimination_machinegun", "500", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_shotgun, "elimination_shotgun", "500", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_grenade, "elimination_grenade", "100", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_rocket, "elimination_rocket", "50", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_railgun, "elimination_railgun", "20", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_lightning, "elimination_lightning", "300", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_plasmagun, "elimination_plasmagun", "200", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_chain, "elimination_chain", "0", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_mine, "elimination_mine", "0", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_elimination_nail, "elimination_nail", "0", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )

G_CVAR( g_elimination_ctf_oneway, "elimination_ctf_oneway", "0", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )

G_CVAR( g_elimination_lockspectator, "elimination_lockspectator", "0", CVAR_NORESTART, 0, qtrue, qfalse )

G_CVAR( g_elimination_items, "elimination_items", "0", CVAR_LATCH | CVAR_NORESTART, 0, qtrue, qfalse )

G_CVAR( g_awardpushing, "g_awardpushing", "1", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )

//g_persistantpowerups
G_CVAR( g_runes, "g_runes", "0", CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse, qfalse )

//nexuiz style rocket arena
G_CVAR( g_rockets, "g_rockets", "0", CVAR_SERVERINFO | CVAR_LATCH | CVAR_NORESTART, 0, qfalse, qfalse )

//Instantgib and Vampire thingies
G_CVAR( g_instantgib, "g_instantgib", "0", CVAR_SERVERINFO | CVAR_LATCH, 0, qfalse, qfalse )
G_CVAR( g_vampire, "g_vampire", "0.0", CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_regen, "g_regen", "0", CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_vampireMaxHealth, "g_vampire_max_health", "500", CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_lms_lives, "g_lms_lives", "1", CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_lms_mode, "g_lms_mode", "0", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )

G_CVAR( g_catchup, "g_catchup", "0", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )

G_CVAR( g_autonextmap, "g_autonextmap", "0", CVAR_ARCHIVE | CVAR_NORESTART, 0, qfalse, qfalse )
G_CVAR( g_mappools, "g_mappools", "0\\maps_dm.cfg\\1\\maps_tourney.cfg\\3\\maps_tdm.cfg\\4\\maps_ctf.cfg\\5\\maps_oneflag.cfg\\6\\maps_obelisk.cfg\
\\7\\maps_harvester.cfg\\8\\maps_elimination.cfg\\9\\maps_ctf.cfg\\10\\maps_lms.cfg\\11\\maps_dd.cfg\\12\\maps_dom.cfg\\13\\maps_dm.cfg\\",
        CVAR_ARCHIVE | CVAR_NORESTART, 0, qfalse, qfalse )
G_CVAR( g_humanplayers, "g_humanplayers", "0", CVAR_ROM | CVAR_NORESTART, 0, qfalse, qfalse )
//used for voIP
G_CVAR( g_redTeamClientNumbers, "g_redTeamClientNumbers", "0", CVAR_ROM, 0, qfalse, qfalse )
G_CVAR( g_blueTeamClientNumbers, "g_blueTeamClientNumbers", "0", CVAR_ROM, 0, qfalse, qfalse )

//KK-OAX
G_CVAR( g_sprees, "g_sprees", "sprees.dat", 0, 0, qfalse, qfalse )
G_CVAR( g_altExcellent, "g_altExcellent", "0", CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_spreeDiv, "g_spreeDiv", "5", 0, 0, qfalse, qfalse )

//Used for command/chat flooding
G_CVAR( g_floodMaxDemerits, "g_floodMaxDemerits", "5000", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_floodMinTime, "g_floodMinTime", "2000", CVAR_ARCHIVE, 0, qfalse, qfalse )

//Admin
G_CVAR( g_admin, "g_admin", "admin.dat", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_adminLog, "g_adminLog", "admin.log", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_adminParseSay, "g_adminParseSay", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_adminNameProtect, "g_adminNameProtect", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_adminTempBan, "g_adminTempBan", "2m", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_adminMaxBan, "g_adminMaxBan", "2w", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_specChat, "g_specChat", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_publicAdminMessages, "g_publicAdminMessages", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_maxWarnings, "g_maxWarnings", "3", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_warningExpire, "g_warningExpire", "3600", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_minNameChangePeriod, "g_minNameChangePeriod", "10", 0, 0, qfalse, qfalse )
G_CVAR( g_maxNameChanges, "g_maxNameChanges", "50", 0, 0, qfalse, qfalse )

G_CVAR( g_timestamp_startgame, "g_timestamp", "0001-01-01 00:00:00", CVAR_SERVERINFO, 0, qfalse, qfalse )

G_CVAR( g_grapple, "g_grapple", "0", CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_harvesterFromBodies, "g_harvesterFromBodies", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_developer, "developer", "0", CVAR_CHEAT, 0, qtrue, qfalse )

//OmegA
G_CVAR( g_allowDuplicateGuid, "g_allowDuplicateGuid", "1", 0, 0, qfalse, qfalse )
G_CVAR( g_allowThirdPerson, "g_allowThirdPerson", "1", CVAR_ARCHIVE | CVAR_SYSTEMINFO, 0, qtrue, qfalse )
G_CVAR( g_beheading, "g_beheading", "1", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_broadcastClients, "g_broadcastClients", "0", 0, 0, qfalse, qfalse )
G_CVAR( g_chaos, "g_chaos", "0", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_damagePlums, "g_damagePlums", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_delagProjectiles, "g_delagProjectiles", "150", CVAR_SYSTEMINFO, 0, qfalse, qfalse )
G_CVAR( g_dropFlag, "g_dropFlag", "1", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_easierPickup, "g_easierPickup", "1", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_fastSwitch, "g_fastSwitch", "1", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_forcespectator, "g_forcespectator", "0", 0, 0, qtrue, qfalse )
G_CVAR( g_gauntletDamage, "g_gauntletDamage", "50", 0, 0, qtrue, qfalse )
G_CVAR( g_grenadeSpeed, "g_grenadeSpeed", "700", 0, 0, qtrue, qfalse )
G_CVAR( g_guidedRockets, "g_guidedRockets", "0", CVAR_ARCHIVE | CVAR_SYSTEMINFO, 0, qtrue, qfalse )
G_CVAR( g_headDamageMultiplicator, "g_headDamageMultiplicator", "1", 0, 0, qtrue, qfalse )
G_CVAR( g_headshotOnly, "g_headshotOnly", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_juggernaut, "g_juggernaut", "7", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_juggernautScale, "g_juggernautScale", "1.5", CVAR_ARCHIVE | CVAR_SYSTEMINFO, 0, qtrue, qfalse )
G_CVAR( g_jumppadGrenades, "g_jumppadGrenades", "1", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_leaveCorpse, "g_leaveCorpse", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_lightningDamage, "g_lightningDamage", "7", 0, 0, qtrue, qfalse )
G_CVAR( g_machinegunDamage, "g_machinegunDamage", "6", 0, 0, qtrue, qfalse )
G_CVAR( g_machinegunTeamDamage, "g_machinegunTeamDamage", "7", 0, 0, qtrue, qfalse )
G_CVAR( g_muteSpectators, "g_muteSpectators", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_noInvisWalls, "g_noInvisWalls", "0", CVAR_ARCHIVE | CVAR_SYSTEMINFO, 0, qtrue, qfalse )
G_CVAR( g_plasmaBounce, "g_plasmaBounce", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_prophunt, "g_prophunt", "0", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_railgunDamage, "g_railgunDamage", "80", 0, 0, qtrue, qfalse )
G_CVAR( g_railgunFireRate, "g_railgunFireRate", "1500", 0, 0, qtrue, qfalse )
G_CVAR( g_railgunImpressiveFastReload, "g_railgunImpressiveFastReload", "1", 0, 0, qtrue, qfalse )
G_CVAR( g_railJump, "g_railJump", "1", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_railThroughWalls, "g_railThroughWalls", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_rocketFireRate, "g_rocketFireRate", "800", 0, 0, qtrue, qfalse )
G_CVAR( g_rocketSpeed, "g_rocketSpeed", "1000", 0, 0, qtrue, qfalse )
G_CVAR( g_slickGround, "g_slickGround", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_spectateOnDeath, "g_spectateOnDeath", "0", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_startWhenReady, "g_startWhenReady", "1", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( g_survivorsRespawn, "g_survivorsRespawn", "1", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( g_teamPush, "g_teamPush", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_teleportMissiles, "g_teleportMissiles", "1", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_waterDamage, "g_waterDamage", "1", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_weaponArena, "g_weaponArena", "0", CVAR_SERVERINFO | CVAR_LATCH | CVAR_NORESTART, 0, qfalse, qfalse )
G_CVAR( pmove_aircontrol, "pmove_aircontrol", "0", CVAR_SYSTEMINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( pmove_autohop, "pmove_autohop", "0", CVAR_SYSTEMINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( pmove_doublejump, "pmove_doublejump", "0", CVAR_SYSTEMINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( pmove_overbounce, "pmove_overbounce", "0", CVAR_SYSTEMINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )

#undef G_CVAR
