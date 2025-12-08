/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
// cg_servercmds.c -- reliably sequenced text commands sent by the server
// these are processed at snapshot transition time, so there will definately
// be a valid snapshot this frame

#include "cg_local.h"
#include "../../ui/menudef.h" // bk001205 - for Q3_ui as well

typedef struct {
	const char *order;
	int taskNum;
} orderTask_t;

/*
=================
CG_ParseScores
=================
*/
static void CG_ParseScores( void ) {
	int i, powerups;

	cg.numScores = atoi( CG_Argv( 1 ) );
	if ( cg.numScores > MAX_CLIENTS ) {
		cg.numScores = MAX_CLIENTS;
	}

	cg.teamScores[0] = atoi( CG_Argv( 2 ) );
	cg.teamScores[1] = atoi( CG_Argv( 3 ) );

	cgs.roundStartTime = atoi( CG_Argv( 4 ) );

	//Update thing in lower-right corner
	if ( cgs.gametype == GT_ELIMINATION || cgs.gametype == GT_CTF_ELIMINATION ) {
		cgs.scores1 = cg.teamScores[0];
		cgs.scores2 = cg.teamScores[1];
	}

	memset( cg.scores, 0, sizeof( cg.scores ) );

#define NUM_DATA 17
#define FIRST_DATA 4

	for ( i = 0; i < cg.numScores; i++ ) {
		//
		cg.scores[i].client = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 1 ) );
		cg.scores[i].score = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 2 ) );
		cg.scores[i].ping = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 3 ) );
		cg.scores[i].time = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 4 ) );
		cg.scores[i].scoreFlags = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 5 ) );
		powerups = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 6 ) );
		cg.scores[i].accuracy = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 7 ) );
		cg.scores[i].impressiveCount = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 8 ) );
		cg.scores[i].excellentCount = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 9 ) );
		cg.scores[i].guantletCount = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 10 ) );
		cg.scores[i].defendCount = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 11 ) );
		cg.scores[i].assistCount = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 12 ) );
		cg.scores[i].perfect = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 13 ) );
		cg.scores[i].captures = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 14 ) );
		cg.scores[i].isDead = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 15 ) );
		cg.scores[i].kills = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 16 ) );
		cg.scores[i].deaths = atoi( CG_Argv( i * NUM_DATA + FIRST_DATA + 17 ) );
		//cgs.roundStartTime =

		if ( cg.scores[i].client < 0 || cg.scores[i].client >= MAX_CLIENTS ) {
			cg.scores[i].client = 0;
		}
		cgs.clientinfo[cg.scores[i].client].score = cg.scores[i].score;
		cgs.clientinfo[cg.scores[i].client].powerups = powerups;
		cgs.clientinfo[cg.scores[i].client].isDead = cg.scores[i].isDead;

		cg.scores[i].team = cgs.clientinfo[cg.scores[i].client].team;
	}
}

/*
=================
CG_ParseAccuracy
=================
*/
static void CG_ParseAccuracy( void ) {
	int i;

	for ( i = WP_MACHINEGUN; i < WP_NUM_WEAPONS; i++ ) {
		cg.accuracys[i - WP_MACHINEGUN][0] = atoi( CG_Argv( ( i - WP_MACHINEGUN ) * 2 + 1 ) );
		cg.accuracys[i - WP_MACHINEGUN][1] = atoi( CG_Argv( ( i - WP_MACHINEGUN ) * 2 + 2 ) );
#if DEBUG
		CG_Printf( "W: %i   shots: %i   Hits: %i\n", i, cg.accuracys[i][0], cg.accuracys[i][1] );
#endif
	}
}

/*
=================
CG_ParseElimination
=================
*/
static void CG_ParseElimination( void ) {
	if ( cgs.gametype == GT_ELIMINATION || cgs.gametype == GT_CTF_ELIMINATION ) {
		cgs.scores1 = atoi( CG_Argv( 1 ) );
		cgs.scores2 = atoi( CG_Argv( 2 ) );
	}
	cgs.roundStartTime = atoi( CG_Argv( 3 ) );
}

/*
=================
CG_ParseMappage

Sago: This parses values from the server rather directly. Some checks are performed, but beware if you change it or new
security holes are found
=================
*/
static void CG_ParseMappage( void ) {
	char command[1024];
	const char *temp;
	const char *c;
	int i;

	temp = CG_Argv( 1 );
	for ( c = temp; *c; ++c ) {
		switch ( *c ) {
			case '\n':
			case '\r':
			case ';':
				//The server tried something bad!
				return;
				break;
		}
	}
	Q_strncpyz( command, va( "ui_mappage %s", temp ), 1024 );
	for ( i = 2; i < 12; i++ ) {
		temp = CG_Argv( i );
		for ( c = temp; *c; ++c ) {
			switch ( *c ) {
				case '\n':
				case '\r':
				case ';':
					//The server tried something bad!
					return;
					break;
			}
		}
		if ( strlen( temp ) < 1 )
			temp = "---";
		Q_strcat( command, 1024, va( " %s ", temp ) );
	}
	trap_SendConsoleCommand( command );
}

/*
=================
CG_ParseDDtimetaken
=================
*/
static void CG_ParseDDtimetaken( void ) {
	cgs.timetaken = atoi( CG_Argv( 1 ) );
}

/*
=================
CG_ParseDomPointNames
=================
*/
static void CG_ParseDomPointNames( void ) {
	int i, j;
	cgs.domination_points_count = atoi( CG_Argv( 1 ) );
	if ( cgs.domination_points_count >= MAX_DOMINATION_POINTS )
		cgs.domination_points_count = MAX_DOMINATION_POINTS;
	for ( i = 0; i < cgs.domination_points_count; i++ ) {
		Q_strncpyz( cgs.domination_points_names[i], CG_Argv( 2 ) + i * MAX_DOMINATION_POINTS_NAMES, MAX_DOMINATION_POINTS_NAMES - 1 );
		for ( j = MAX_DOMINATION_POINTS_NAMES - 1; cgs.domination_points_names[i][j] < '0' && j > 0; j-- ) {
			cgs.domination_points_names[i][j] = 0;
		}
	}
}

/*
=================
CG_ParseDomScores
=================
*/
static void CG_ParseDomStatus( void ) {
	int i;
	if ( cgs.domination_points_count != atoi( CG_Argv( 1 ) ) ) {
		cgs.domination_points_count = 0;
		return;
	}
	for ( i = 0; i < cgs.domination_points_count; i++ ) {
		cgs.domination_points_status[i] = atoi( CG_Argv( 2 + i ) );
	}
}

/*
=================
CG_ParseChallenge
=================
*/
static void CG_ParseChallenge( void ) {
	addChallenge( atoi( CG_Argv( 1 ) ) );
}

/*
=================
CG_ParseObeliskHealth
=================
*/
static void CG_ParseObeliskHealth( void ) {
	cg.redObeliskHealth = atoi( CG_Argv( 1 ) );
	cg.blueObeliskHealth = atoi( CG_Argv( 2 ) );
}

/*
=================
CG_ParseRespawnTime

Sets the respawn counter for the client.
=================
*/
static void CG_ParseRespawnTime( void ) {
	cg.respawnTime = atoi( CG_Argv( 1 ) );
}

/*
=================
CG_ParseTeam
=================
*/
static void CG_ParseTeam( void ) {
	//TODO: Add code here
	if ( cg_voip_teamonly.integer )
		trap_Cvar_Set( "cl_voipSendTarget", CG_Argv( 1 ) );
}

/*
=================
CG_ParseAttackingTeam
=================
*/
static void CG_ParseAttackingTeam( void ) {
	int temp;
	temp = atoi( CG_Argv( 1 ) );
	if ( temp == TEAM_RED )
		cgs.attackingTeam = TEAM_RED;
	else if ( temp == TEAM_BLUE )
		cgs.attackingTeam = TEAM_BLUE;
	else
		cgs.attackingTeam = TEAM_NONE; //Should never happen.
}

/*
=================
CG_ParseTeamCount
=================
*/
static void CG_ParseTeamCount( void ) {
	int livingRed, livingBlue, totalRed, totalBlue;
	int team = TEAM_SPECTATOR;
	qboolean isDead = qfalse;

	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR && cg.snap->ps.pm_flags & PMF_FOLLOW ) {
		team = cg.snap->ps.persistant[PERS_TEAM];
		isDead = ( cg.snap->ps.pm_type == PM_DEAD );
	} else if ( cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR ) {
		team = cg.predictedPlayerState.persistant[PERS_TEAM];
		isDead = ( cg.predictedPlayerState.pm_type == PM_DEAD );
	}

	totalRed = atoi( CG_Argv( 3 ) );
	totalBlue = atoi( CG_Argv( 4 ) );

	if ( cg.warmup < 0 ) {
		cgs.redLivingCount = totalRed;
		cgs.blueLivingCount = totalBlue;
		return;
	}

	livingRed = atoi( CG_Argv( 1 ) );
	livingBlue = atoi( CG_Argv( 2 ) );
	totalRed = atoi( CG_Argv( 3 ) );
	totalBlue = atoi( CG_Argv( 4 ) );

	if ( team == TEAM_RED && totalRed > 1 && livingRed == 1 && livingRed != cgs.redLivingCount && !isDead ) {
		CG_CenterPrint( va( "You are the last one standing" ), 120, BIGCHAR_WIDTH );
		CG_AddBufferedSound( cgs.media.takenOpponentSound );
	}

	if ( team == TEAM_BLUE && totalBlue != 1 && livingBlue == 1 && livingBlue != cgs.blueLivingCount && !isDead ) {
		CG_CenterPrint( va( "You are the last one standing" ), 120, BIGCHAR_WIDTH );
		CG_AddBufferedSound( cgs.media.takenOpponentSound );
	}

	cgs.redLivingCount = livingRed;
	cgs.blueLivingCount = livingBlue;
}

/*
=================
CG_ParseTeamInfo
=================
*/
static void CG_ParseTeamInfo( void ) {
	int i;
	int client;

	numSortedTeamPlayers = atoi( CG_Argv( 1 ) );
	if ( numSortedTeamPlayers < 0 || numSortedTeamPlayers > TEAM_MAXOVERLAY ) {
		CG_Error( "CG_ParseTeamInfo: numSortedTeamPlayers out of range (%d)",
		          numSortedTeamPlayers );
		return;
	}

	for ( i = 0; i < numSortedTeamPlayers; i++ ) {
		client = atoi( CG_Argv( i * 6 + 2 ) );
		if ( client < 0 || client >= MAX_CLIENTS ) {
			CG_Error( "CG_ParseTeamInfo: bad client number: %d", client );
			return;
		}

		sortedTeamPlayers[i] = client;

		cgs.clientinfo[client].location = atoi( CG_Argv( i * 6 + 3 ) );
		cgs.clientinfo[client].health = atoi( CG_Argv( i * 6 + 4 ) );
		cgs.clientinfo[client].armor = atoi( CG_Argv( i * 6 + 5 ) );
		cgs.clientinfo[client].curWeapon = atoi( CG_Argv( i * 6 + 6 ) );
		cgs.clientinfo[client].powerups = atoi( CG_Argv( i * 6 + 7 ) );
	}
}

/*
================
CG_ParseServerinfo

This is called explicitly when the gamestate is first received,
and whenever the server updates any serverinfo flagged cvars
================
*/
void CG_ParseServerinfo( void ) {
	const char *info;
	char *mapname;

	info = CG_ConfigString( CS_SERVERINFO );
	cgs.gametype = atoi( Info_ValueForKey( info, "g_gametype" ) );
	//By default do as normal:
	cgs.ffa_gt = 0;
	//See if ffa gametype
	if ( cgs.gametype == GT_LMS || cgs.gametype == GT_POSSESSION ) {
		cgs.ffa_gt = 1;
	}
	trap_Cvar_Set( "g_gametype", va( "%i", cgs.gametype ) );
	cgs.dmflags = atoi( Info_ValueForKey( info, "dmflags" ) );
	cgs.videoflags = atoi( Info_ValueForKey( info, "videoflags" ) );
	cgs.elimflags = atoi( Info_ValueForKey( info, "elimflags" ) );
	cgs.teamflags = atoi( Info_ValueForKey( info, "teamflags" ) );
	cgs.fraglimit = atoi( Info_ValueForKey( info, "fraglimit" ) );
	cgs.capturelimit = atoi( Info_ValueForKey( info, "capturelimit" ) );
	cgs.timelimit = atoi( Info_ValueForKey( info, "timelimit" ) );
	cgs.maxclients = atoi( Info_ValueForKey( info, "sv_maxclients" ) );
	cgs.roundtime = atoi( Info_ValueForKey( info, "elimination_roundtime" ) );
	cgs.nopickup = atoi( Info_ValueForKey( info, "g_rockets" ) ) + atoi( Info_ValueForKey( info, "g_weaponArena" ) ) + atoi( Info_ValueForKey( info, "g_instantgib" ) ) + atoi( Info_ValueForKey( info, "g_elimination" ) );
	cgs.lms_mode = atoi( Info_ValueForKey( info, "g_lms_mode" ) );
	cgs.altExcellent = atoi( Info_ValueForKey( info, "g_altExcellent" ) );
	mapname = Info_ValueForKey( info, "mapname" );
	Com_sprintf( cgs.mapname, sizeof( cgs.mapname ), "maps/%s.bsp", mapname );
	Q_strncpyz( cgs.redTeam, Info_ValueForKey( info, "g_redTeam" ), sizeof( cgs.redTeam ) );
	trap_Cvar_Set( "g_redTeam", cgs.redTeam );
	Q_strncpyz( cgs.blueTeam, Info_ValueForKey( info, "g_blueTeam" ), sizeof( cgs.blueTeam ) );
	trap_Cvar_Set( "g_blueTeam", cgs.blueTeam );

	//unlagged - server options
	// we'll need this for deciding whether or not to predict weapon effects
	cgs.delagHitscan = atoi( Info_ValueForKey( info, "g_delagHitscan" ) );
	trap_Cvar_Set( "g_delagHitscan", va( "%i", cgs.delagHitscan ) );
	//unlagged - server options

	cgs.easierPickup = atoi( Info_ValueForKey( info, "g_easierPickup" ) );
	trap_Cvar_Set( "g_easierPickup", va( "%i", cgs.easierPickup ) );

	cgs.startWhenReady = atoi( Info_ValueForKey( info, "g_startWhenReady" ) );
	trap_Cvar_Set( "g_startWhenReady", va( "%i", cgs.startWhenReady ) );

	//Copy allowed votes directly to the client:
	trap_Cvar_Set( "cg_voteflags", Info_ValueForKey( info, "voteflags" ) );
}

/*
==================
CG_ParseWarmup
==================
*/
static void CG_ParseWarmup( void ) {
	const char *info;
	int warmup;

	info = CG_ConfigString( CS_WARMUP );

	warmup = atoi( info );
	cg.warmupCount = -1;

	if ( warmup == 0 && cg.warmup ) {

	} else if ( warmup > 0 && cg.warmup <= 0 ) {
		{
			trap_S_StartLocalSound( cgs.media.countPrepareSound, CHAN_ANNOUNCER );
		}
	}

	cg.warmup = warmup;
}

/*
=================
CG_ParseReadyMask
=================
*/
static void CG_ParseReadyMask( void ) {
	int readyMask, i;

	readyMask = atoi( CG_Argv( 1 ) );

	if ( cg.warmup >= 0 ) {
		return;
	}

	if ( readyMask != cg.readyMask ) {
		for ( i = 0; i < 32; i++ ) {
			if ( ( cg.readyMask & ( 1 << i ) ) != ( readyMask & ( 1 << i ) ) && !cgs.clientinfo[i].botSkill ) {
				if ( readyMask & ( 1 << i ) ) {
					CG_CenterPrint( va( "%s ^7is ^2ready", cgs.clientinfo[i].name ), 120, BIGCHAR_WIDTH );
				} else {
					CG_CenterPrint( va( "%s ^7is ^1not ready", cgs.clientinfo[i].name ), 120, BIGCHAR_WIDTH );
				}
			}
		}
		cg.readyMask = readyMask;
	}
}

/*
================
CG_SetConfigValues

Called on load to set the initial values from configure strings
================
*/
void CG_SetConfigValues( void ) {
	const char *s;

	cgs.scores1 = atoi( CG_ConfigString( CS_SCORES1 ) );
	cgs.scores2 = atoi( CG_ConfigString( CS_SCORES2 ) );
	cgs.levelStartTime = atoi( CG_ConfigString( CS_LEVEL_START_TIME ) );
	if ( cgs.gametype == GT_CTF || cgs.gametype == GT_CTF_ELIMINATION || cgs.gametype == GT_DOUBLE_D ) {
		s = CG_ConfigString( CS_FLAGSTATUS );
		cgs.redflag = s[0] - '0';
		cgs.blueflag = s[1] - '0';
	} else if ( cgs.gametype == GT_1FCTF || cgs.gametype == GT_POSSESSION ) {
		s = CG_ConfigString( CS_FLAGSTATUS );
		cgs.flagStatus = s[0] - '0';
	}
	cg.warmup = atoi( CG_ConfigString( CS_WARMUP ) );
}

/*
=====================
CG_ShaderStateChanged
=====================
*/
void CG_ShaderStateChanged( void ) {
	char originalShader[MAX_QPATH];
	char newShader[MAX_QPATH];
	char timeOffset[16];
	const char *o;
	char *n, *t;

	o = CG_ConfigString( CS_SHADERSTATE );
	while ( o && *o ) {
		n = strstr( o, "=" );
		if ( n && *n ) {
			Q_strncpyz( originalShader, o, n - o + 1 );
			n++;
			t = strstr( n, ":" );
			if ( t && *t ) {
				Q_strncpyz( newShader, n, t - n + 1 );
			} else {
				break;
			}
			t++;
			o = strstr( t, "@" );
			if ( o ) {
				Q_strncpyz( timeOffset, t, o - t + 1 );
				o++;
				trap_R_RemapShader( originalShader, newShader, timeOffset );
			}
		} else {
			break;
		}
	}
}

/*
================
CG_ConfigStringModified
================
*/
static void CG_ConfigStringModified( void ) {
	const char *str;
	int num;

	num = atoi( CG_Argv( 1 ) );

	// get the gamestate from the client system, which will have the
	// new configstring already integrated
	trap_GetGameState( &cgs.gameState );

	// look up the individual string that was modified
	str = CG_ConfigString( num );

	// do something with it if necessary
	if ( num == CS_MUSIC ) {
		CG_StartMusic();
	} else if ( num == CS_SERVERINFO ) {
		CG_ParseServerinfo();
	} else if ( num == CS_WARMUP ) {
		CG_ParseWarmup();
	} else if ( num == CS_SCORES1 ) {
		cgs.scores1 = atoi( str );
	} else if ( num == CS_SCORES2 ) {
		cgs.scores2 = atoi( str );
	} else if ( num == CS_LEVEL_START_TIME ) {
		cgs.levelStartTime = atoi( str );
	} else if ( num == CS_VOTE_TIME ) {
		cgs.voteTime = atoi( str );
		cgs.voteModified = qtrue;
	} else if ( num == CS_VOTE_YES ) {
		cgs.voteYes = atoi( str );
		cgs.voteModified = qtrue;
	} else if ( num == CS_VOTE_NO ) {
		cgs.voteNo = atoi( str );
		cgs.voteModified = qtrue;
	} else if ( num == CS_VOTE_STRING ) {
		Q_strncpyz( cgs.voteString, str, sizeof( cgs.voteString ) );
	} else if ( num >= CS_TEAMVOTE_TIME && num <= CS_TEAMVOTE_TIME + 1 ) {
		cgs.teamVoteTime[num - CS_TEAMVOTE_TIME] = atoi( str );
		cgs.teamVoteModified[num - CS_TEAMVOTE_TIME] = qtrue;
	} else if ( num >= CS_TEAMVOTE_YES && num <= CS_TEAMVOTE_YES + 1 ) {
		cgs.teamVoteYes[num - CS_TEAMVOTE_YES] = atoi( str );
		cgs.teamVoteModified[num - CS_TEAMVOTE_YES] = qtrue;
	} else if ( num >= CS_TEAMVOTE_NO && num <= CS_TEAMVOTE_NO + 1 ) {
		cgs.teamVoteNo[num - CS_TEAMVOTE_NO] = atoi( str );
		cgs.teamVoteModified[num - CS_TEAMVOTE_NO] = qtrue;
	} else if ( num >= CS_TEAMVOTE_STRING && num <= CS_TEAMVOTE_STRING + 1 ) {
		Q_strncpyz( cgs.teamVoteString[num - CS_TEAMVOTE_STRING], str, sizeof( cgs.teamVoteString ) );
	} else if ( num == CS_INTERMISSION ) {
		cg.intermissionStarted = atoi( str );
	} else if ( num >= CS_MODELS && num < CS_MODELS + MAX_MODELS ) {
		cgs.gameModels[num - CS_MODELS] = trap_R_RegisterModel( str );
	} else if ( num >= CS_SOUNDS && num < CS_SOUNDS + MAX_SOUNDS ) {
		if ( str[0] != '*' ) { // player specific sounds don't register here
			cgs.gameSounds[num - CS_SOUNDS] = trap_S_RegisterSound( str, qfalse );
		}
	} else if ( num >= CS_PLAYERS && num < CS_PLAYERS + MAX_CLIENTS ) {
		CG_NewClientInfo( num - CS_PLAYERS );
		CG_BuildSpectatorString();
	} else if ( num == CS_FLAGSTATUS ) {
		if ( cgs.gametype == GT_CTF || cgs.gametype == GT_CTF_ELIMINATION || cgs.gametype == GT_DOUBLE_D ) {
			// format is rb where its red/blue, 0 is at base, 1 is taken, 2 is dropped
			cgs.redflag = str[0] - '0';
			cgs.blueflag = str[1] - '0';
		} else if ( cgs.gametype == GT_1FCTF || cgs.gametype == GT_POSSESSION ) {
			cgs.flagStatus = str[0] - '0';
		}
	} else if ( num == CS_SHADERSTATE ) {
		CG_ShaderStateChanged();
	}
}

/*
=======================
CG_AddToTeamChat
=======================
*/
static void CG_AddToTeamChat( const char *str ) {
	int len;
	char *p, *ls;
	int lastcolor;
	int chatHeight;

	if ( cg_teamChatHeight.integer < TEAMCHAT_HEIGHT ) {
		chatHeight = cg_teamChatHeight.integer;
	} else {
		chatHeight = TEAMCHAT_HEIGHT;
	}

	if ( chatHeight <= 0 || cg_teamChatTime.integer <= 0 ) {
		// team chat disabled, dump into normal chat
		cgs.teamChatPos = cgs.teamLastChatPos = 0;
		return;
	}

	len = 0;

	p = cgs.teamChatMsgs[cgs.teamChatPos % chatHeight];
	*p = 0;

	lastcolor = '7';

	ls = NULL;
	while ( *str ) {
		if ( len > TEAMCHAT_WIDTH - 1 ) {
			if ( ls ) {
				str -= ( p - ls );
				str++;
				p -= ( p - ls );
			}
			*p = 0;

			cgs.teamChatMsgTimes[cgs.teamChatPos % chatHeight] = cg.time;

			cgs.teamChatPos++;
			p = cgs.teamChatMsgs[cgs.teamChatPos % chatHeight];
			*p = 0;
			*p++ = Q_COLOR_ESCAPE;
			*p++ = lastcolor;
			len = 0;
			ls = NULL;
		}

		if ( Q_IsColorString( str ) ) {
			*p++ = *str++;
			lastcolor = *str;
			*p++ = *str++;
			continue;
		}
		if ( *str == ' ' ) {
			ls = p;
		}
		*p++ = *str++;
		len++;
	}
	*p = 0;

	cgs.teamChatMsgTimes[cgs.teamChatPos % chatHeight] = cg.time;
	cgs.teamChatPos++;

	if ( cgs.teamChatPos - cgs.teamLastChatPos > chatHeight )
		cgs.teamLastChatPos = cgs.teamChatPos - chatHeight;
}

/*
===============
CG_MapRestart

The server has issued a map_restart, so the next snapshot
is completely new and should not be interpolated to.

A tournement restart will clear everything, but doesn't
require a reload of all the media
===============
*/
static void CG_MapRestart( void ) {
	if ( cg_showmiss.integer ) {
		CG_Printf( "CG_MapRestart\n" );
	}

	CG_InitLocalEntities();
	CG_InitMarkPolys();
	CG_ClearParticles();

	// make sure the "3 frags left" warnings play again
	cg.fraglimitWarnings = 0;

	cg.timelimitWarnings = 0;

	cg.intermissionStarted = qfalse;

	cgs.voteTime = 0;

	cg.readyMask = 0;

	cg.mapRestart = qtrue;

	CG_StartMusic();

	trap_S_ClearLoopingSounds( qtrue );

	// we really should clear more parts of cg here and stop sounds

	// play the "fight" sound if this is a restart without warmup
	if ( cg.warmup == 0 ) {
		trap_S_StartLocalSound( cgs.media.countFightSound, CHAN_ANNOUNCER );
		CG_CenterPrint( "FIGHT!", 120, GIANTCHAR_WIDTH * 2 );
	}
	trap_Cvar_Set( "cg_thirdPerson", "0" );
}

/*
=================
CG_RemoveChatEscapeChar
=================
*/
static void CG_RemoveChatEscapeChar( char *text ) {
	int i, l;

	l = 0;
	for ( i = 0; text[i]; i++ ) {
		if ( text[i] == '\x19' )
			continue;
		text[l++] = text[i];
	}
	text[l] = '\0';
}

/*
=================
CG_ParseSpawnpoints
=================
*/
static void CG_ParseSpawnpoints( void ) {
	int i;

	cg.numSpawnpoints = atoi( CG_Argv( 1 ) );

	if ( cg.numSpawnpoints > MAX_SPAWNPOINTS ) {
		cg.numSpawnpoints = MAX_SPAWNPOINTS;
	} else if ( cg.numSpawnpoints < 0 ) {
		cg.numSpawnpoints = 0;
	}

	for ( i = 0; i < cg.numSpawnpoints; i++ ) {
		cg.spawnpoints[i].origin[0] = atoi( CG_Argv( 2 + i * 7 ) );
		cg.spawnpoints[i].origin[1] = atoi( CG_Argv( 3 + i * 7 ) );
		cg.spawnpoints[i].origin[2] = atoi( CG_Argv( 4 + i * 7 ) );
		cg.spawnpoints[i].angle[0] = atoi( CG_Argv( 5 + i * 7 ) );
		cg.spawnpoints[i].angle[1] = atoi( CG_Argv( 6 + i * 7 ) );
		cg.spawnpoints[i].angle[2] = atoi( CG_Argv( 7 + i * 7 ) );
		cg.spawnpoints[i].team = atoi( CG_Argv( 8 + i * 7 ) );
	}
}

/*
=================
CG_ServerCommand

The string has been tokenized and can be retrieved with
Cmd_Argc() / Cmd_Argv()
=================
*/
static void CG_ServerCommand( void ) {
	const char *cmd;
	char text[MAX_SAY_TEXT];

	cmd = CG_Argv( 0 );

	if ( !cmd[0] ) {
		// server claimed the command
		return;
	}

	if ( !strcmp( cmd, "cp" ) ) {
		CG_CenterPrint( CG_Argv( 1 ), SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		return;
	}

	if ( !strcmp( cmd, "cs" ) ) {
		CG_ConfigStringModified();
		return;
	}

	if ( !strcmp( cmd, "print" ) ) {
		CG_Printf( "%s", CG_Argv( 1 ) );
		return;
	}

	if ( !strcmp( cmd, "chat" ) ) {
		if ( !cg_teamChatsOnly.integer ) {
			if ( cg_chatBeep.integer )
				trap_S_StartLocalSound( cgs.media.talkSound, CHAN_LOCAL_SOUND );
			Q_strncpyz( text, CG_Argv( 1 ), MAX_SAY_TEXT );
			CG_RemoveChatEscapeChar( text );
			CG_Printf( "%s\n", text );
		}
		return;
	}

	if ( !strcmp( cmd, "tchat" ) ) {
		if ( cg_teamChatBeep.integer )
			trap_S_StartLocalSound( cgs.media.talkSound, CHAN_LOCAL_SOUND );
		Q_strncpyz( text, CG_Argv( 1 ), MAX_SAY_TEXT );
		CG_RemoveChatEscapeChar( text );
		CG_AddToTeamChat( text );
		CG_Printf( "%s\n", text );
		return;
	}
	if ( !strcmp( cmd, "vchat" ) ) {
		return;
	}

	if ( !strcmp( cmd, "vtchat" ) ) {
		return;
	}

	if ( !strcmp( cmd, "vtell" ) ) {
		return;
	}

	if ( !strcmp( cmd, "scores" ) ) {
		CG_ParseScores();
		return;
	}

	if ( !strcmp( cmd, "accs" ) ) {
		CG_ParseAccuracy();
		return;
	}

	if ( !strcmp( cmd, "ddtaken" ) ) {
		CG_ParseDDtimetaken();
		return;
	}

	if ( !strcmp( cmd, "dompointnames" ) ) {
		CG_ParseDomPointNames();
		return;
	}

	if ( !strcmp( cmd, "domStatus" ) ) {
		CG_ParseDomStatus();
		return;
	}

	if ( !strcmp( cmd, "elimination" ) ) {
		CG_ParseElimination();
		return;
	}

	if ( !strcmp( cmd, "mappage" ) ) {
		CG_ParseMappage();
		return;
	}

	if ( !strcmp( cmd, "attackingteam" ) ) {
		CG_ParseAttackingTeam();
		return;
	}

	if ( !strcmp( cmd, "tcount" ) ) {
		CG_ParseTeamCount();
		return;
	}

	if ( !strcmp( cmd, "tinfo" ) ) {
		CG_ParseTeamInfo();
		return;
	}

	if ( !strcmp( cmd, "map_restart" ) ) {
		CG_MapRestart();
		return;
	}

	if ( Q_stricmp( cmd, "remapShader" ) == 0 ) {
		if ( trap_Argc() == 4 ) {
			char shader1[MAX_QPATH];
			char shader2[MAX_QPATH];
			char shader3[MAX_QPATH];

			Q_strncpyz( shader1, CG_Argv( 1 ), sizeof( shader1 ) );
			Q_strncpyz( shader2, CG_Argv( 2 ), sizeof( shader2 ) );
			Q_strncpyz( shader3, CG_Argv( 3 ), sizeof( shader3 ) );

			trap_R_RemapShader( shader1, shader2, shader3 );
		}

		return;
	}

	// loaddeferred can be both a servercmd and a consolecmd
	if ( !strcmp( cmd, "loaddefered" ) ) { // FIXME: spelled wrong, but not changing for demo
		CG_LoadDeferredPlayers();
		return;
	}

	// clientLevelShot is sent before taking a special screenshot for
	// the menu system during development
	if ( !strcmp( cmd, "clientLevelShot" ) ) {
		cg.levelShot = qtrue;
		return;
	}

	// challenge completed is determened by the server. A client should consider this message valid:
	if ( !strcmp( cmd, "ch" ) ) {
		CG_ParseChallenge();
		return;
	}

	if ( !strcmp( cmd, "oh" ) ) {
		CG_ParseObeliskHealth();
		return;
	}

	if ( !strcmp( cmd, "readyMask" ) ) {
		CG_ParseReadyMask();
		return;
	}

	if ( !strcmp( cmd, "respawn" ) ) {
		CG_ParseRespawnTime();
		return;
	}

	if ( !strcmp( cmd, "spawnPoints" ) ) {
		CG_ParseSpawnpoints();
		return;
	}

	if ( !strcmp( cmd, "team" ) ) {
		CG_ParseTeam();
		return;
	}

	if ( !strcmp( cmd, "customvotes" ) ) {
		char infoString[1024];
		int i;
		//TODO: Create a ParseCustomvotes function
		memset( &infoString, 0, sizeof( infoString ) );
		for ( i = 1; i <= 12; i++ ) {
			Q_strcat( infoString, sizeof( infoString ), CG_Argv( i ) );
			Q_strcat( infoString, sizeof( infoString ), " " );
		}
		trap_Cvar_Set( "cg_vote_custom_commands", infoString );
		return;
	}

	if ( !strcmp( cmd, "notification" ) ) {
		if ( cg_drawEmotes.integer ) {
			trap_S_StartLocalSound( cgs.media.notificationSound, CHAN_ANNOUNCER );
		}
		return;
	}

	CG_Printf( "Unknown client game command: %s\n", cmd );
}

/*
====================
CG_ExecuteNewServerCommands

Execute all of the server commands that were received along
with this this snapshot.
====================
*/
void CG_ExecuteNewServerCommands( int latestSequence ) {
	while ( cgs.serverCommandSequence < latestSequence ) {
		if ( trap_GetServerCommand( ++cgs.serverCommandSequence ) ) {
			CG_ServerCommand();
		}
	}
}
