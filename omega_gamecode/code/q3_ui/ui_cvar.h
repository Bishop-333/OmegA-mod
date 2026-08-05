#ifdef EXTERN_UI_CVAR
	#define UI_CVAR( vmCvar, cvarName, defaultString, cvarFlags ) extern vmCvar_t vmCvar;
#endif

#ifdef DECLARE_UI_CVAR
	#define UI_CVAR( vmCvar, cvarName, defaultString, cvarFlags ) vmCvar_t vmCvar;
#endif

#ifdef UI_CVAR_LIST
	#define UI_CVAR( vmCvar, cvarName, defaultString, cvarFlags ) { & vmCvar, cvarName, defaultString, cvarFlags },
#endif

UI_CVAR( ui_ffa_fraglimit, "ui_ffa_fraglimit", "20", CVAR_ARCHIVE )
UI_CVAR( ui_ffa_timelimit, "ui_ffa_timelimit", "0", CVAR_ARCHIVE )

UI_CVAR( ui_tourney_fraglimit, "ui_tourney_fraglimit", "0", CVAR_ARCHIVE )
UI_CVAR( ui_tourney_timelimit, "ui_tourney_timelimit", "15", CVAR_ARCHIVE )

UI_CVAR(ui_team_fraglimit, "ui_team_fraglimit", "0", CVAR_ARCHIVE )
UI_CVAR( ui_team_timelimit, "ui_team_timelimit", "20", CVAR_ARCHIVE )
UI_CVAR( ui_team_friendly, "ui_team_friendly", "1", CVAR_ARCHIVE )

UI_CVAR(ui_ctf_capturelimit, "ui_ctf_capturelimit", "8", CVAR_ARCHIVE )
UI_CVAR( ui_ctf_timelimit, "ui_ctf_timelimit", "30", CVAR_ARCHIVE )
UI_CVAR( ui_ctf_friendly, "ui_ctf_friendly", "0", CVAR_ARCHIVE )

UI_CVAR(ui_1fctf_capturelimit, "ui_1fctf_capturelimit", "8", CVAR_ARCHIVE )
UI_CVAR( ui_1fctf_timelimit, "ui_1fctf_timelimit", "30", CVAR_ARCHIVE )
UI_CVAR( ui_1fctf_friendly, "ui_1fctf_friendly", "0", CVAR_ARCHIVE )

UI_CVAR(ui_overload_capturelimit, "ui_overload_capturelimit", "8", CVAR_ARCHIVE )
UI_CVAR( ui_overload_timelimit, "ui_overload_timelimit", "30", CVAR_ARCHIVE )
UI_CVAR( ui_overload_friendly, "ui_overload_friendly", "0", CVAR_ARCHIVE )

UI_CVAR( ui_harvester_capturelimit, "ui_harvester_capturelimit", "20", CVAR_ARCHIVE )
UI_CVAR( ui_harvester_timelimit, "ui_harvester_timelimit", "30", CVAR_ARCHIVE )
UI_CVAR( ui_harvester_friendly, "ui_harvester_friendly", "0", CVAR_ARCHIVE )

UI_CVAR(ui_elimination_capturelimit, "ui_elimination_capturelimit", "8", CVAR_ARCHIVE )
UI_CVAR( ui_elimination_timelimit, "ui_elimination_timelimit", "20", CVAR_ARCHIVE )

UI_CVAR( ui_ctf_elimination_capturelimit, "ui_ctf_elimination_capturelimit", "8", CVAR_ARCHIVE )
UI_CVAR( ui_ctf_elimination_timelimit, "ui_ctf_elimination_timelimit", "30", CVAR_ARCHIVE )

UI_CVAR( ui_lms_fraglimit, "ui_lms_fraglimit", "20", CVAR_ARCHIVE )
UI_CVAR( ui_lms_timelimit, "ui_lms_timelimit", "0", CVAR_ARCHIVE )

UI_CVAR(ui_dd_capturelimit, "ui_dd_capturelimit", "8", CVAR_ARCHIVE )
UI_CVAR( ui_dd_timelimit, "ui_dd_timelimit", "30", CVAR_ARCHIVE )
UI_CVAR( ui_dd_friendly, "ui_dd_friendly", "0", CVAR_ARCHIVE )

UI_CVAR(ui_dom_capturelimit, "ui_dom_capturelimit", "500", CVAR_ARCHIVE )
UI_CVAR( ui_dom_timelimit, "ui_dom_timelimit", "30", CVAR_ARCHIVE )
UI_CVAR( ui_dom_friendly, "ui_dom_friendly", "0", CVAR_ARCHIVE )

UI_CVAR(ui_pos_scorelimit, "ui_pos_scorelimit", "300", CVAR_ARCHIVE )
UI_CVAR( ui_pos_timelimit, "ui_pos_timelimit", "20", CVAR_ARCHIVE )

UI_CVAR(ui_arenasFile, "g_arenasFile", "", CVAR_INIT | CVAR_ROM )
UI_CVAR( ui_botsFile, "g_botsFile", "", CVAR_INIT | CVAR_ROM )
UI_CVAR( ui_spScores1, "g_spScores1", "", CVAR_ARCHIVE )
UI_CVAR( ui_spScores2, "g_spScores2", "", CVAR_ARCHIVE )
UI_CVAR( ui_spScores3, "g_spScores3", "", CVAR_ARCHIVE )
UI_CVAR( ui_spScores4, "g_spScores4", "", CVAR_ARCHIVE )
UI_CVAR( ui_spScores5, "g_spScores5", "", CVAR_ARCHIVE )
UI_CVAR( ui_spAwards, "g_spAwards", "", CVAR_ARCHIVE )
UI_CVAR( ui_spVideos, "g_spVideos", "", CVAR_ARCHIVE )
UI_CVAR( ui_spSkill, "g_spSkill", "3", CVAR_ARCHIVE | CVAR_LATCH )

UI_CVAR( ui_spSelection, "ui_spSelection", "", CVAR_ROM )

UI_CVAR( ui_browserMaster, "ui_browserMaster", "0", CVAR_ARCHIVE )
UI_CVAR( ui_browserGameType, "ui_browserGameType", "0", CVAR_ARCHIVE )
UI_CVAR( ui_browserSortKey, "ui_browserSortKey", "4", CVAR_ARCHIVE )
UI_CVAR( ui_browserShowEmpty, "ui_browserShowEmpty", "1", CVAR_ARCHIVE )

UI_CVAR( ui_brassTime, "cg_brassTime", "2500", CVAR_ARCHIVE )
UI_CVAR( ui_drawCrosshair, "cg_drawCrosshair", "1", CVAR_ARCHIVE )
UI_CVAR( ui_drawCrosshairNames, "cg_drawCrosshairNames", "1", CVAR_ARCHIVE )
UI_CVAR( ui_marks, "cg_marks", "1", CVAR_ARCHIVE )

UI_CVAR( ui_server1, "server1", "", CVAR_ARCHIVE )
UI_CVAR( ui_server2, "server2", "", CVAR_ARCHIVE )
UI_CVAR( ui_server3, "server3", "", CVAR_ARCHIVE )
UI_CVAR( ui_server4, "server4", "", CVAR_ARCHIVE )
UI_CVAR( ui_server5, "server5", "", CVAR_ARCHIVE )
UI_CVAR( ui_server6, "server6", "", CVAR_ARCHIVE )
UI_CVAR( ui_server7, "server7", "", CVAR_ARCHIVE )
UI_CVAR( ui_server8, "server8", "", CVAR_ARCHIVE )
UI_CVAR( ui_server9, "server9", "", CVAR_ARCHIVE )
UI_CVAR( ui_server10, "server10", "", CVAR_ARCHIVE )
UI_CVAR( ui_server11, "server11", "", CVAR_ARCHIVE )
UI_CVAR( ui_server12, "server12", "", CVAR_ARCHIVE )
UI_CVAR( ui_server13, "server13", "", CVAR_ARCHIVE )
UI_CVAR( ui_server14, "server14", "", CVAR_ARCHIVE )
UI_CVAR( ui_server15, "server15", "", CVAR_ARCHIVE )
UI_CVAR( ui_server16, "server16", "", CVAR_ARCHIVE )
UI_CVAR( ui_developer, "developer", "0", CVAR_CHEAT )
UI_CVAR( g_localTeamPref, "g_localTeamPref", "", 0 )

//new in beta 23:
UI_CVAR( ui_browserOnlyHumans, "ui_browserOnlyHumans", "0", CVAR_ARCHIVE )

//new in beta 37:
UI_CVAR( ui_setupchecked, "ui_setupchecked", "0", CVAR_ARCHIVE )
UI_CVAR( ui_browserHidePrivate, "ui_browserHidePrivate", "1", CVAR_ARCHIVE )

//OmegA
UI_CVAR( ui_hide_mature, "ui_hide_mature", "1", CVAR_ARCHIVE )
UI_CVAR( ui_mapvote_filter, "ui_mapvote_filter", "", 0 )
UI_CVAR( ui_saved_bloom, "ui_saved_bloom", "", CVAR_ARCHIVE )
UI_CVAR( ui_saved_desktop, "ui_saved_desktop", "", CVAR_ARCHIVE )
UI_CVAR( ui_saved_maxfps, "ui_saved_maxfps", "", CVAR_ARCHIVE )
UI_CVAR( ui_saved_msaa, "ui_saved_msaa", "", CVAR_ARCHIVE )

#undef UI_CVAR
