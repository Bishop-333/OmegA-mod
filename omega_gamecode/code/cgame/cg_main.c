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
// cg_main.c -- initialization and primary entry point for cgame
#include "cg_local.h"

int forceModelModificationCount = -1;
int forceTeamSkinsModificationCount = -1;
int enemyModelModificationCount = -1;
int teamModelModificationCount = -1;
int selfSoundsModificationCount = -1;
int enemySoundsModificationCount = -1;
int teamSoundsModificationCount = -1;

void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum );
void CG_Shutdown( void );

// extension interface
qboolean linearLight = qfalse;
qboolean can_trap_Cvar_SetDescription = qfalse;

#ifdef Q3_VM
qboolean (*trap_GetValue)( char *value, int valueSize, const char *key );
void (*trap_R_AddLinearLightToScene)( const vec3_t start, const vec3_t end, float intensity, float r, float g, float b );
void (*trap_Cvar_SetDescription)( const char *var_name, const char *var_description );
#else
int dll_com_trapGetValue;
int dll_trap_Cvar_SetDescription;
#endif

/*
================
vmMain

This is the only way control passes into the module.
This must be the very first function compiled into the .q3vm file
================
*/
intptr_t vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11 ) {

	switch ( command ) {
		case CG_INIT:
			CG_Init( arg0, arg1, arg2 );
			return 0;
		case CG_SHUTDOWN:
			CG_Shutdown();
			return 0;
		case CG_CONSOLE_COMMAND:
			return CG_ConsoleCommand();
		case CG_DRAW_ACTIVE_FRAME:
			CG_DrawActiveFrame( arg0, arg1, arg2 );
			CG_FairCvars();
			return 0;
		case CG_CROSSHAIR_PLAYER:
			return CG_CrosshairPlayer();
		case CG_LAST_ATTACKER:
			return CG_LastAttacker();
		case CG_KEY_EVENT:
			CG_KeyEvent( arg0, arg1 );
			return 0;
		case CG_MOUSE_EVENT:
			CG_MouseEvent( arg0, arg1 );
			return 0;
		case CG_EVENT_HANDLING:
			CG_EventHandling( arg0 );
			return 0;
		default:
			CG_Error( "vmMain: unknown command %i", command );
			break;
	}
	return -1;
}

cg_t cg;
cgs_t cgs;
centity_t cg_entities[MAX_GENTITIES];
weaponInfo_t cg_weapons[MAX_WEAPONS];
itemInfo_t cg_items[MAX_ITEMS];

#define DECLARE_CG_CVAR
#include "cg_cvar.h"
#undef DECLARE_CG_CVAR

typedef struct {
	vmCvar_t *vmCvar;
	char *cvarName;
	char *defaultString;
	int cvarFlags;
	const char *description;
} cvarTable_t;

static cvarTable_t cvarTable[] = {

#define CG_CVAR_LIST
#include "cg_cvar.h"
#undef CG_CVAR_LIST

};

static int cvarTableSize = sizeof( cvarTable ) / sizeof( cvarTable[0] );

/*
=================
CG_RegisterCvars
=================
*/
static void CG_RegisterCvars( void ) {
	int i;
	cvarTable_t *cv;
	char var[MAX_TOKEN_CHARS];

	for ( i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++ ) {
		trap_Cvar_Register( cv->vmCvar, cv->cvarName,
		                    cv->defaultString, cv->cvarFlags );
		if ( can_trap_Cvar_SetDescription && cv->description ) {
			trap_Cvar_SetDescription( cv->cvarName, cv->description );
		}
	}

	// see if we are also running the server on this machine
	trap_Cvar_VariableStringBuffer( "sv_running", var, sizeof( var ) );
	cgs.localServer = atoi( var );

	forceModelModificationCount = cg_forceModel.modificationCount;
	forceTeamSkinsModificationCount = cg_forceTeamSkins.modificationCount;
	enemyModelModificationCount = cg_enemyModel.modificationCount;
	teamModelModificationCount = cg_teamModel.modificationCount;

	trap_Cvar_Register( NULL, "model", DEFAULT_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
	trap_Cvar_Register( NULL, "headmodel", DEFAULT_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
	trap_Cvar_Register( NULL, "team_model", DEFAULT_TEAM_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
	trap_Cvar_Register( NULL, "team_headmodel", DEFAULT_TEAM_HEAD, CVAR_USERINFO | CVAR_ARCHIVE );
}

/*																																			
===================
CG_Initialize
===================
 */
static void CG_Initialize( void ) {
	int i;
	cvarTable_t *cv;

	if ( !cg_omegaInitialized.integer ) {
		for ( i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++ ) {
			trap_Cvar_Set( cv->cvarName, cv->defaultString );
			trap_Cvar_Update( cv->vmCvar );
		}
		trap_SendConsoleCommand( "unbind MOUSE2\n" );
		trap_SendConsoleCommand( "bind MOUSE2 +zoom\n" );
		trap_Cvar_Set( "cg_omegaInitialized", "1" );
	}
}

/*																																			
===================
CG_ForceModelChange
===================
*/
static void CG_ForceModelChange( void ) {
	int i;

	for ( i = 0; i < MAX_CLIENTS; i++ ) {
		cgs.clientinfo[i].infoValid = qfalse;
	}

	for ( i = 0; i < MAX_CLIENTS; i++ ) {
		const char *clientInfo;

		clientInfo = CG_ConfigString( CS_PLAYERS + i );
		if ( !clientInfo[0] ) {
			continue;
		}
		CG_NewClientInfo( i );
	}
	CG_LoadDeferredPlayers();
}

/*
=================
CG_UpdateCvars
=================
*/
void CG_UpdateCvars( void ) {
	int i;
	cvarTable_t *cv;

	for ( i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++ ) {
		//unlagged - client options
		// clamp the value between 0 and 999
		// negative values would suck - people could conceivably shoot other
		// players *long* after they had left the area, on purpose
		if ( cv->vmCvar == &cg_cmdTimeNudge ) {
			CG_Cvar_ClampInt( cv->cvarName, cv->vmCvar, 0, 999 );
		}
		// cl_timenudge less than -50 or greater than 50 doesn't actually
		// do anything more than -50 or 50 (actually the numbers are probably
		// closer to -30 and 30, but 50 is nice and round-ish)
		// might as well not feed the myth, eh?
		else if ( cv->vmCvar == &cl_timeNudge ) {
			CG_Cvar_ClampInt( cv->cvarName, cv->vmCvar, -50, 50 );
		}
		//unlagged - client options
		else if ( cv->vmCvar == &cg_errorDecay ) {
			CG_Cvar_ClampInt( cv->cvarName, cv->vmCvar, 0, 250 );
		}
		trap_Cvar_Update( cv->vmCvar );
	}

	// check for modifications here

	// If team overlay is on, ask for updates from the server. If its off,
	// let the server know so we don't receive it
	if ( drawTeamOverlayModificationCount != cg_drawTeamOverlay.modificationCount ) {
		drawTeamOverlayModificationCount = cg_drawTeamOverlay.modificationCount;

		if ( cg_drawTeamOverlay.integer > 0 ) {
			trap_Cvar_Set( "teamoverlay", "1" );
		} else {
			trap_Cvar_Set( "teamoverlay", "0" );
		}
	}

	// if force model changed
	if ( forceModelModificationCount != cg_forceModel.modificationCount ) {
		forceModelModificationCount = cg_forceModel.modificationCount;
		CG_ForceModelChange();
	}
	if ( forceTeamSkinsModificationCount != cg_forceTeamSkins.modificationCount ) {
		forceTeamSkinsModificationCount = cg_forceTeamSkins.modificationCount;
		CG_ForceModelChange();
	}
	if ( enemyModelModificationCount != cg_enemyModel.modificationCount ) {
		enemyModelModificationCount = cg_enemyModel.modificationCount;
		CG_ForceModelChange();
	}
	if ( teamModelModificationCount != cg_teamModel.modificationCount ) {
		teamModelModificationCount = cg_teamModel.modificationCount;
		CG_ForceModelChange();
	}

	// if force sounds changed
	if ( selfSoundsModificationCount != cg_selfSounds.modificationCount ) {
		selfSoundsModificationCount = cg_selfSounds.modificationCount;
		CG_ForceSoundsChange();
	}
	if ( enemySoundsModificationCount != cg_enemySounds.modificationCount ) {
		enemySoundsModificationCount = cg_enemySounds.modificationCount;
		CG_ForceSoundsChange();
	}
	if ( teamSoundsModificationCount != cg_teamSounds.modificationCount ) {
		teamSoundsModificationCount = cg_teamSounds.modificationCount;
		CG_ForceSoundsChange();
	}
}

/*
=================
CG_CrosshairPlayer
=================
*/
int CG_CrosshairPlayer( void ) {
	if ( cg.time > ( cg.crosshairClientTime + 1000 ) ) {
		return -1;
	}
	return cg.crosshairClientNum;
}

/*
=================
CG_LastAttacker
=================
*/
int CG_LastAttacker( void ) {
	if ( !cg.attackerTime ) {
		return -1;
	}
	return cg.snap->ps.persistant[PERS_ATTACKER];
}

/*
=================
CG_Printf
=================
*/
void QDECL CG_Printf( const char *msg, ... ) {
	va_list argptr;
	char text[1024];

	va_start( argptr, msg );
	Q_vsnprintf( text, sizeof( text ), msg, argptr );
	va_end( argptr );

	trap_Print( text );
}

/*
=================
CG_Error
=================
*/
void QDECL CG_Error( const char *msg, ... ) {
	va_list argptr;
	char text[1024];

	va_start( argptr, msg );
	Q_vsnprintf( text, sizeof( text ), msg, argptr );
	va_end( argptr );

	trap_Error( text );
}

/*
=================
Com_Error
=================
*/
void QDECL Com_Error( int level, const char *error, ... ) {
	va_list argptr;
	char text[1024];

	va_start( argptr, error );
	Q_vsnprintf( text, sizeof( text ), error, argptr );
	va_end( argptr );

	CG_Error( "%s", text );
}

/*
=================
Com_Printf
=================
*/
void QDECL Com_Printf( const char *msg, ... ) {
	va_list argptr;
	char text[1024];

	va_start( argptr, msg );
	Q_vsnprintf( text, sizeof( text ), msg, argptr );
	va_end( argptr );

	CG_Printf( "%s", text );
}

/*
================
CG_Argv
================
*/
const char *CG_Argv( int arg ) {
	static char buffer[MAX_STRING_CHARS];

	trap_Argv( arg, buffer, sizeof( buffer ) );

	return buffer;
}

//========================================================================

/*
=================
CG_RegisterItemSounds

The server says this item is used on this level
=================
*/
static void CG_RegisterItemSounds( int itemNum ) {
	gitem_t *item;
	char data[MAX_QPATH];
	char *s, *start;
	int len;

	item = &bg_itemlist[itemNum];

	if ( item->pickup_sound ) {
		trap_S_RegisterSound( item->pickup_sound, qfalse );
	}

	// parse the space separated precache string for other media
	s = item->sounds;
	if ( !s || !s[0] )
		return;

	while ( *s ) {
		start = s;
		while ( *s && *s != ' ' ) {
			s++;
		}

		len = s - start;
		if ( len >= MAX_QPATH || len < 5 ) {
			CG_Error( "PrecacheItem: %s has bad precache string",
			          item->classname );
			return;
		}
		memcpy( data, start, len );
		data[len] = 0;
		if ( *s ) {
			s++;
		}

		if ( !strcmp( data + len - 3, "wav" ) ) {
			trap_S_RegisterSound( data, qfalse );
		}
	}
}

/*
=================
CG_RegisterSounds

called during a precache command
=================
*/
static void CG_RegisterSounds( void ) {
	int i;
	char items[MAX_ITEMS + 1];
	char name[MAX_QPATH];
	const char *soundName;

	cgs.media.oneMinuteSound = trap_S_RegisterSound( "sound/feedback/1_minute.wav", qtrue );
	cgs.media.fiveMinuteSound = trap_S_RegisterSound( "sound/feedback/5_minute.wav", qtrue );
	cgs.media.suddenDeathSound = trap_S_RegisterSound( "sound/feedback/sudden_death.wav", qtrue );
	cgs.media.oneFragSound = trap_S_RegisterSound( "sound/feedback/1_frag.wav", qtrue );
	cgs.media.twoFragSound = trap_S_RegisterSound( "sound/feedback/2_frags.wav", qtrue );
	cgs.media.threeFragSound = trap_S_RegisterSound( "sound/feedback/3_frags.wav", qtrue );
	cgs.media.count3Sound = trap_S_RegisterSound( "sound/feedback/three.wav", qtrue );
	cgs.media.count2Sound = trap_S_RegisterSound( "sound/feedback/two.wav", qtrue );
	cgs.media.count1Sound = trap_S_RegisterSound( "sound/feedback/one.wav", qtrue );
	cgs.media.countFightSound = trap_S_RegisterSound( "sound/feedback/fight.wav", qtrue );
	cgs.media.countPrepareSound = trap_S_RegisterSound( "sound/feedback/prepare.wav", qtrue );

	// N_G: Another condition that makes no sense to me, see for
	// yourself if you really meant this
	// Sago: Makes perfect sense: Load team game stuff if the gametype is a teamgame and not an exception (like GT_LMS)
	if ( ( ( cgs.gametype >= GT_TEAM ) && ( cgs.ffa_gt != 1 ) ) ||
	     cg_buildScript.integer ) {

		cgs.media.captureAwardSound = trap_S_RegisterSound( "sound/teamplay/flagcapture_yourteam.wav", qtrue );
		cgs.media.redLeadsSound = trap_S_RegisterSound( "sound/feedback/redleads.wav", qtrue );
		cgs.media.blueLeadsSound = trap_S_RegisterSound( "sound/feedback/blueleads.wav", qtrue );
		cgs.media.teamsTiedSound = trap_S_RegisterSound( "sound/feedback/teamstied.wav", qtrue );
		cgs.media.hitTeamSound = trap_S_RegisterSound( "sound/feedback/hit_teammate.wav", qtrue );

		cgs.media.redScoredSound = trap_S_RegisterSound( "sound/teamplay/voc_red_scores.wav", qtrue );
		cgs.media.blueScoredSound = trap_S_RegisterSound( "sound/teamplay/voc_blue_scores.wav", qtrue );

		cgs.media.captureYourTeamSound = trap_S_RegisterSound( "sound/teamplay/flagcapture_yourteam.wav", qtrue );
		cgs.media.captureOpponentSound = trap_S_RegisterSound( "sound/teamplay/flagcapture_opponent.wav", qtrue );

		cgs.media.returnYourTeamSound = trap_S_RegisterSound( "sound/teamplay/flagreturn_yourteam.wav", qtrue );
		cgs.media.returnOpponentSound = trap_S_RegisterSound( "sound/teamplay/flagreturn_opponent.wav", qtrue );

		cgs.media.takenYourTeamSound = trap_S_RegisterSound( "sound/teamplay/flagtaken_yourteam.wav", qtrue );
		cgs.media.takenOpponentSound = trap_S_RegisterSound( "sound/teamplay/flagtaken_opponent.wav", qtrue );

		cgs.media.flagDroppedSound = trap_S_RegisterSound( "sound/teamplay/flag_dropped.wav", qtrue );

		if ( cgs.gametype == GT_CTF || cgs.gametype == GT_CTF_ELIMINATION || cg_buildScript.integer ) {
			cgs.media.redFlagReturnedSound = trap_S_RegisterSound( "sound/teamplay/voc_red_returned.wav", qtrue );
			cgs.media.blueFlagReturnedSound = trap_S_RegisterSound( "sound/teamplay/voc_blue_returned.wav", qtrue );
			cgs.media.enemyTookYourFlagSound = trap_S_RegisterSound( "sound/teamplay/voc_enemy_flag.wav", qtrue );
			cgs.media.yourTeamTookEnemyFlagSound = trap_S_RegisterSound( "sound/teamplay/voc_team_flag.wav", qtrue );
		}

		if ( cgs.gametype == GT_1FCTF || cg_buildScript.integer ) {
			// FIXME: get a replacement for this sound ?
			cgs.media.neutralFlagReturnedSound = trap_S_RegisterSound( "sound/teamplay/flagreturn_opponent.wav", qtrue );
			cgs.media.yourTeamTookTheFlagSound = trap_S_RegisterSound( "sound/teamplay/voc_team_1flag.wav", qtrue );
			cgs.media.enemyTookTheFlagSound = trap_S_RegisterSound( "sound/teamplay/voc_enemy_1flag.wav", qtrue );
		}

		if ( cgs.gametype == GT_OBELISK || cg_buildScript.integer ) {
			cgs.media.yourBaseIsUnderAttackSound = trap_S_RegisterSound( "sound/teamplay/voc_base_attack.wav", qtrue );
		}
	}

	if ( cgs.gametype == GT_1FCTF || cgs.gametype == GT_CTF || cgs.gametype == GT_CTF_ELIMINATION || cgs.gametype == GT_POSSESSION || cg_buildScript.integer ) {
		cgs.media.youHaveFlagSound = trap_S_RegisterSound( "sound/teamplay/voc_you_flag.wav", qtrue );
	}

	cgs.media.holyShitSound = trap_S_RegisterSound( "sound/feedback/voc_holyshit.wav", qtrue );

	cgs.media.tracerSound = trap_S_RegisterSound( "sound/weapons/machinegun/buletby1.wav", qfalse );
	cgs.media.selectSound = trap_S_RegisterSound( "sound/weapons/change.wav", qfalse );
	cgs.media.wearOffSound = trap_S_RegisterSound( "sound/items/wearoff.wav", qfalse );
	cgs.media.useNothingSound = trap_S_RegisterSound( "sound/items/use_nothing.wav", qfalse );
	cgs.media.gibSound = trap_S_RegisterSound( "sound/player/gibsplt1.wav", qfalse );
	cgs.media.gibBounce1Sound = trap_S_RegisterSound( "sound/player/gibimp1.wav", qfalse );
	cgs.media.gibBounce2Sound = trap_S_RegisterSound( "sound/player/gibimp2.wav", qfalse );
	cgs.media.gibBounce3Sound = trap_S_RegisterSound( "sound/player/gibimp3.wav", qfalse );

	// LEILEI

	cgs.media.lspl1Sound = trap_S_RegisterSound( "sound/le/splat1.wav", qfalse );
	cgs.media.lspl2Sound = trap_S_RegisterSound( "sound/le/splat2.wav", qfalse );
	cgs.media.lspl3Sound = trap_S_RegisterSound( "sound/le/splat3.wav", qfalse );

	cgs.media.lbul1Sound = trap_S_RegisterSound( "sound/le/bullet1.wav", qfalse );
	cgs.media.lbul2Sound = trap_S_RegisterSound( "sound/le/bullet2.wav", qfalse );
	cgs.media.lbul3Sound = trap_S_RegisterSound( "sound/le/bullet3.wav", qfalse );

	cgs.media.lshl1Sound = trap_S_RegisterSound( "sound/le/shell1.wav", qfalse );
	cgs.media.lshl2Sound = trap_S_RegisterSound( "sound/le/shell2.wav", qfalse );
	cgs.media.lshl3Sound = trap_S_RegisterSound( "sound/le/shell3.wav", qfalse );

	cgs.media.useInvulnerabilitySound = trap_S_RegisterSound( "sound/items/invul_activate.wav", qfalse );
	cgs.media.invulnerabilityImpactSound1 = trap_S_RegisterSound( "sound/items/invul_impact_01.wav", qfalse );
	cgs.media.invulnerabilityImpactSound2 = trap_S_RegisterSound( "sound/items/invul_impact_02.wav", qfalse );
	cgs.media.invulnerabilityImpactSound3 = trap_S_RegisterSound( "sound/items/invul_impact_03.wav", qfalse );
	cgs.media.invulnerabilityJuicedSound = trap_S_RegisterSound( "sound/items/invul_juiced.wav", qfalse );

	cgs.media.doublerSound = trap_S_RegisterSound( "sound/items/cl_doubler.wav", qfalse );
	cgs.media.guardSound = trap_S_RegisterSound( "sound/items/cl_guard.wav", qfalse );
	cgs.media.scoutSound = trap_S_RegisterSound( "sound/items/cl_scout.wav", qfalse );
	cgs.media.obeliskHitSound1 = trap_S_RegisterSound( "sound/items/obelisk_hit_01.wav", qfalse );
	cgs.media.obeliskHitSound2 = trap_S_RegisterSound( "sound/items/obelisk_hit_02.wav", qfalse );
	cgs.media.obeliskHitSound3 = trap_S_RegisterSound( "sound/items/obelisk_hit_03.wav", qfalse );
	cgs.media.obeliskRespawnSound = trap_S_RegisterSound( "sound/items/obelisk_respawn.wav", qfalse );

	cgs.media.teleInSound = trap_S_RegisterSound( "sound/world/telein.wav", qfalse );
	cgs.media.teleOutSound = trap_S_RegisterSound( "sound/world/teleout.wav", qfalse );
	cgs.media.respawnSound = trap_S_RegisterSound( "sound/items/respawn1.wav", qfalse );

	cgs.media.noAmmoSound = trap_S_RegisterSound( "sound/weapons/noammo.wav", qfalse );

	cgs.media.talkSound = trap_S_RegisterSound( "sound/player/talk.wav", qfalse );
	cgs.media.landSound = trap_S_RegisterSound( "sound/player/land1.wav", qfalse );

	switch ( cg_hitsound.integer ) {
		case 0:
		default:
			cgs.media.hitSound = trap_S_RegisterSound( "sound/feedback/hit1.wav", qfalse );
			break;
	};

	switch ( cg_killsound.integer ) {
		case 0:
		default:
			cgs.media.killSound = trap_S_RegisterSound( "sound/feedback/hithi.wav", qfalse );
			break;
	};

	cgs.media.hitSoundHighArmor = trap_S_RegisterSound( "sound/feedback/hithi.wav", qfalse );
	cgs.media.hitSoundLowArmor = trap_S_RegisterSound( "sound/feedback/hitlo.wav", qfalse );
	cgs.media.cashSound = trap_S_RegisterSound( "sound/feedback/cash.wav", qfalse );

	cgs.media.impressiveSound = trap_S_RegisterSound( "sound/feedback/impressive.wav", qtrue );
	cgs.media.excellentSound = trap_S_RegisterSound( "sound/feedback/excellent.wav", qtrue );
	cgs.media.deniedSound = trap_S_RegisterSound( "sound/feedback/denied.wav", qtrue );
	cgs.media.humiliationSound = trap_S_RegisterSound( "sound/feedback/humiliation.wav", qtrue );
	cgs.media.assistSound = trap_S_RegisterSound( "sound/feedback/assist.wav", qtrue );
	cgs.media.defendSound = trap_S_RegisterSound( "sound/feedback/defense.wav", qtrue );
	cgs.media.headshotSound = trap_S_RegisterSound( "sound/feedback/accuracy.wav", qtrue );
	cgs.media.rampageSound = trap_S_RegisterSound( "sound/feedback/frags.wav", qtrue );

	cgs.media.notificationSound = trap_S_RegisterSound( "sound/misc/notification.wav", qtrue );

	cgs.media.takenLeadSound = trap_S_RegisterSound( "sound/feedback/takenlead.wav", qtrue );
	cgs.media.tiedLeadSound = trap_S_RegisterSound( "sound/feedback/tiedlead.wav", qtrue );
	cgs.media.lostLeadSound = trap_S_RegisterSound( "sound/feedback/lostlead.wav", qtrue );

	cgs.media.watrInSound = trap_S_RegisterSound( "sound/player/watr_in.wav", qfalse );
	cgs.media.watrOutSound = trap_S_RegisterSound( "sound/player/watr_out.wav", qfalse );
	cgs.media.watrUnSound = trap_S_RegisterSound( "sound/player/watr_un.wav", qfalse );

	cgs.media.jumpPadSound = trap_S_RegisterSound( "sound/world/jumppad.wav", qfalse );

	for ( i = 0; i < 4; i++ ) {
		Com_sprintf( name, sizeof( name ), "sound/player/footsteps/step%i.wav", i + 1 );
		cgs.media.footsteps[FOOTSTEP_NORMAL][i] = trap_S_RegisterSound( name, qfalse );

		Com_sprintf( name, sizeof( name ), "sound/player/footsteps/boot%i.wav", i + 1 );
		cgs.media.footsteps[FOOTSTEP_BOOT][i] = trap_S_RegisterSound( name, qfalse );

		Com_sprintf( name, sizeof( name ), "sound/player/footsteps/flesh%i.wav", i + 1 );
		cgs.media.footsteps[FOOTSTEP_FLESH][i] = trap_S_RegisterSound( name, qfalse );

		Com_sprintf( name, sizeof( name ), "sound/player/footsteps/mech%i.wav", i + 1 );
		cgs.media.footsteps[FOOTSTEP_MECH][i] = trap_S_RegisterSound( name, qfalse );

		Com_sprintf( name, sizeof( name ), "sound/player/footsteps/energy%i.wav", i + 1 );
		cgs.media.footsteps[FOOTSTEP_ENERGY][i] = trap_S_RegisterSound( name, qfalse );

		Com_sprintf( name, sizeof( name ), "sound/player/footsteps/splash%i.wav", i + 1 );
		cgs.media.footsteps[FOOTSTEP_SPLASH][i] = trap_S_RegisterSound( name, qfalse );

		Com_sprintf( name, sizeof( name ), "sound/player/footsteps/clank%i.wav", i + 1 );
		cgs.media.footsteps[FOOTSTEP_METAL][i] = trap_S_RegisterSound( name, qfalse );
	}

	// only register the items that the server says we need
	Q_strncpyz( items, CG_ConfigString( CS_ITEMS ), sizeof( items ) );

	for ( i = 1; i < bg_numItems; i++ ) {
		CG_RegisterItemSounds( i );
	}

	for ( i = 1; i < MAX_SOUNDS; i++ ) {
		soundName = CG_ConfigString( CS_SOUNDS + i );
		if ( !soundName[0] ) {
			break;
		}
		if ( soundName[0] == '*' ) {
			continue; // custom sound
		}
		cgs.gameSounds[i] = trap_S_RegisterSound( soundName, qfalse );
	}

	// FIXME: only needed with item
	cgs.media.flightSound = trap_S_RegisterSound( "sound/items/flight.wav", qfalse );
	cgs.media.medkitSound = trap_S_RegisterSound( "sound/items/use_medkit.wav", qfalse );
	cgs.media.quadSound = trap_S_RegisterSound( "sound/items/damage3.wav", qfalse );
	cgs.media.sfx_ric1 = trap_S_RegisterSound( "sound/weapons/machinegun/ric1.wav", qfalse );
	cgs.media.sfx_ric2 = trap_S_RegisterSound( "sound/weapons/machinegun/ric2.wav", qfalse );
	cgs.media.sfx_ric3 = trap_S_RegisterSound( "sound/weapons/machinegun/ric3.wav", qfalse );
	cgs.media.sfx_railg = trap_S_RegisterSound( "sound/weapons/railgun/railgf1a.wav", qfalse );
	cgs.media.sfx_rockexp = trap_S_RegisterSound( "sound/weapons/rocket/rocklx1a.wav", qfalse );
	cgs.media.sfx_plasmaexp = trap_S_RegisterSound( "sound/weapons/plasma/plasmx1a.wav", qfalse );
	cgs.media.sfx_proxexp = trap_S_RegisterSound( "sound/weapons/proxmine/wstbexpl.wav", qfalse );
	cgs.media.sfx_nghitflesh = trap_S_RegisterSound( "sound/weapons/nailgun/wnalimpl.wav", qfalse );
	cgs.media.sfx_nghitmetal = trap_S_RegisterSound( "sound/weapons/nailgun/wnalimpm.wav", qfalse );
	cgs.media.weaponHoverSound = trap_S_RegisterSound( "sound/weapons/weapon_hover.wav", qfalse );
	cgs.media.kamikazeExplodeSound = trap_S_RegisterSound( "sound/items/kam_explode.wav", qfalse );
	cgs.media.kamikazeImplodeSound = trap_S_RegisterSound( "sound/items/kam_implode.wav", qfalse );
	cgs.media.kamikazeFarSound = trap_S_RegisterSound( "sound/items/kam_explode_far.wav", qfalse );
	cgs.media.winnerSound = trap_S_RegisterSound( "sound/feedback/voc_youwin.wav", qfalse );
	cgs.media.loserSound = trap_S_RegisterSound( "sound/feedback/voc_youlose.wav", qfalse );

	cgs.media.wstbimplSound = trap_S_RegisterSound( "sound/weapons/proxmine/wstbimpl.wav", qfalse );
	cgs.media.wstbimpmSound = trap_S_RegisterSound( "sound/weapons/proxmine/wstbimpm.wav", qfalse );
	cgs.media.wstbimpdSound = trap_S_RegisterSound( "sound/weapons/proxmine/wstbimpd.wav", qfalse );
	cgs.media.wstbactvSound = trap_S_RegisterSound( "sound/weapons/proxmine/wstbactv.wav", qfalse );

	cgs.media.regenSound = trap_S_RegisterSound( "sound/items/regen.wav", qfalse );
	cgs.media.protectSound = trap_S_RegisterSound( "sound/items/protect3.wav", qfalse );
	cgs.media.n_healthSound = trap_S_RegisterSound( "sound/items/n_health.wav", qfalse );
	cgs.media.hgrenb1aSound = trap_S_RegisterSound( "sound/weapons/grenade/hgrenb1a.wav", qfalse );
	cgs.media.hgrenb2aSound = trap_S_RegisterSound( "sound/weapons/grenade/hgrenb2a.wav", qfalse );

	cgs.media.freezeSound = trap_S_RegisterSound( "sound/player/freeze.ogg", qfalse );
}

//===================================================================================

/*
=================
CG_RegisterGraphics

This function may execute for a couple of minutes with a slow disk.
=================
*/
static void CG_RegisterGraphics( void ) {
	int i;
	char items[MAX_ITEMS + 1];
	static char *sb_nums[11] = {
	    "gfx/2d/numbers/zero_32b",
	    "gfx/2d/numbers/one_32b",
	    "gfx/2d/numbers/two_32b",
	    "gfx/2d/numbers/three_32b",
	    "gfx/2d/numbers/four_32b",
	    "gfx/2d/numbers/five_32b",
	    "gfx/2d/numbers/six_32b",
	    "gfx/2d/numbers/seven_32b",
	    "gfx/2d/numbers/eight_32b",
	    "gfx/2d/numbers/nine_32b",
	    "gfx/2d/numbers/minus_32b",
	};

	// clear any references to old media
	memset( &cg.refdef, 0, sizeof( cg.refdef ) );
	trap_R_ClearScene();

	CG_LoadingString( cgs.mapname );

	trap_R_LoadWorldMap( cgs.mapname );

	// precache status bar pics
	CG_LoadingString( "game media" );

	for ( i = 0; i < 11; i++ ) {
		cgs.media.numberShaders[i] = trap_R_RegisterShader( sb_nums[i] );
	}

	cgs.media.botSkillShaders[0] = trap_R_RegisterShader( "menu/art/skill1.tga" );
	cgs.media.botSkillShaders[1] = trap_R_RegisterShader( "menu/art/skill2.tga" );
	cgs.media.botSkillShaders[2] = trap_R_RegisterShader( "menu/art/skill3.tga" );
	cgs.media.botSkillShaders[3] = trap_R_RegisterShader( "menu/art/skill4.tga" );
	cgs.media.botSkillShaders[4] = trap_R_RegisterShader( "menu/art/skill5.tga" );

	cgs.media.viewBloodShader = trap_R_RegisterShader( "viewBloodBlend" );

	cgs.media.deferShader = trap_R_RegisterShaderNoMip( "gfx/2d/defer.tga" );

	cgs.media.scoreboardName = trap_R_RegisterShaderNoMip( "menu/tab/name.tga" );
	cgs.media.scoreboardPing = trap_R_RegisterShaderNoMip( "menu/tab/ping.tga" );
	cgs.media.scoreboardScore = trap_R_RegisterShaderNoMip( "menu/tab/score.tga" );
	cgs.media.scoreboardTime = trap_R_RegisterShaderNoMip( "menu/tab/time.tga" );

	cgs.media.smokePuffShader = trap_R_RegisterShader( "smokePuff" );
	cgs.media.smokePuffRageProShader = trap_R_RegisterShader( "smokePuffRagePro" );
	cgs.media.shotgunSmokePuffShader = trap_R_RegisterShader( "shotgunSmokePuff" );
	cgs.media.nailPuffShader = trap_R_RegisterShader( "nailtrail" );
	cgs.media.blueProxMine = trap_R_RegisterModel( "models/weaphits/proxmineb.md3" );
	cgs.media.plasmaBallShader = trap_R_RegisterShader( "sprites/plasma1" );
	cgs.media.bloodTrailShader = trap_R_RegisterShader( "bloodTrail" );
	cgs.media.snowTrailShader = trap_R_RegisterShader( "snowTrail" );
	cgs.media.lagometerShader = trap_R_RegisterShader( "gfx/2d/lag.tga" );
	cgs.media.connectionShader = trap_R_RegisterShader( "disconnected" );

	cgs.media.waterBubbleShader = trap_R_RegisterShader( "waterBubble" );

	cgs.media.tracerShader = trap_R_RegisterShader( "gfx/misc/tracer" );
	cgs.media.selectShader = trap_R_RegisterShader( "gfx/2d/select" );

	cgs.media.bfgShader = trap_R_RegisterShader( "icons/iconw_bfg" );
	cgs.media.chaingunShader = trap_R_RegisterShader( "icons/iconw_chaingun" );
	cgs.media.gauntletShader = trap_R_RegisterShader( "icons/iconw_gauntlet" );
	cgs.media.grapplehookShader = trap_R_RegisterShader( "icons/iconw_grapple" );
	cgs.media.grenadeShader = trap_R_RegisterShader( "icons/iconw_grenade" );
	cgs.media.kamikazeShader = trap_R_RegisterShader( "icons/iconw_kamikaze" );
	cgs.media.lightninggunShader = trap_R_RegisterShader( "icons/iconw_lightning" );
	cgs.media.machinegunShader = trap_R_RegisterShader( "icons/iconw_machinegun" );
	cgs.media.nailgunShader = trap_R_RegisterShader( "icons/iconw_nailgun" );
	cgs.media.plasmaShader = trap_R_RegisterShader( "icons/iconw_plasma" );
	cgs.media.proxlauncherShader = trap_R_RegisterShader( "icons/iconw_proxlauncher" );
	cgs.media.railgunShader = trap_R_RegisterShader( "icons/iconw_railgun" );
	cgs.media.rocketShader = trap_R_RegisterShader( "icons/iconw_rocket" );
	cgs.media.shotgunShader = trap_R_RegisterShader( "icons/iconw_shotgun" );
	cgs.media.skullShader = trap_R_RegisterShader( "icons/skull" );

	for ( i = 0; i < NUM_CROSSHAIRS; i++ ) {
		cgs.media.crosshairShader[i] = trap_R_RegisterShader( va( "gfx/2d/crosshairs/crosshair%d", i + 1 ) );
		cgs.media.crosshairOutlineShader[i] = trap_R_RegisterShader( va( "gfx/2d/crosshairs/crosshair%d_outline", i + 1 ) );
	}

	cgs.media.backTileShader = trap_R_RegisterShader( "gfx/2d/backtile" );
	cgs.media.noammoShader = trap_R_RegisterShader( "icons/noammo" );

	// powerup shaders
	cgs.media.quadShader = trap_R_RegisterShader( "powerups/quad" );
	cgs.media.quadWeaponShader = trap_R_RegisterShader( "powerups/quadWeapon" );
	cgs.media.battleSuitShader = trap_R_RegisterShader( "powerups/battleSuit" );
	cgs.media.battleWeaponShader = trap_R_RegisterShader( "powerups/battleWeapon" );
	cgs.media.invisShader = trap_R_RegisterShader( "powerups/invisibility" );
	cgs.media.regenShader = trap_R_RegisterShader( "powerups/regen" );
	cgs.media.hastePuffShader = trap_R_RegisterShader( "hasteSmokePuff" );
	cgs.media.frozenShader = trap_R_RegisterShader( "playerIceShell" );
	cgs.media.thawingShader = trap_R_RegisterShader( "playerThawingShell" );
	cgs.media.spawnPointShader = trap_R_RegisterShader( "spawnPoint" );
	cgs.media.transparentWeaponShader = trap_R_RegisterShader( "transparentWeapon" );

	if ( cgs.gametype == GT_CTF || BG_IsElimTeamGametype( cgs.gametype ) || cgs.gametype == GT_1FCTF || cgs.gametype == GT_HARVESTER || cg_buildScript.integer ) {
		cgs.media.redCubeModel = trap_R_RegisterModel( "models/powerups/orb/r_orb.md3" );
		cgs.media.blueCubeModel = trap_R_RegisterModel( "models/powerups/orb/b_orb.md3" );
		cgs.media.redCubeIcon = trap_R_RegisterShader( "icons/skull_red" );
		cgs.media.blueCubeIcon = trap_R_RegisterShader( "icons/skull_blue" );
	}

	// bright players shader
	cgs.media.brightPlayers = trap_R_RegisterShader( "brightPlayers" );
	cgs.media.brightPlayers2 = trap_R_RegisterShader( "brightPlayers2" );

	//For Double Domination:
	if ( cgs.gametype == GT_DOUBLE_D ) {
		cgs.media.ddPointSkinA[TEAM_RED] = trap_R_RegisterShaderNoMip( "icons/icona_red" );
		cgs.media.ddPointSkinA[TEAM_BLUE] = trap_R_RegisterShaderNoMip( "icons/icona_blue" );
		cgs.media.ddPointSkinA[TEAM_FREE] = trap_R_RegisterShaderNoMip( "icons/icona_white" );
		cgs.media.ddPointSkinA[TEAM_NONE] = trap_R_RegisterShaderNoMip( "icons/noammo" );

		cgs.media.ddPointSkinB[TEAM_RED] = trap_R_RegisterShaderNoMip( "icons/iconb_red" );
		cgs.media.ddPointSkinB[TEAM_BLUE] = trap_R_RegisterShaderNoMip( "icons/iconb_blue" );
		cgs.media.ddPointSkinB[TEAM_FREE] = trap_R_RegisterShaderNoMip( "icons/iconb_white" );
		cgs.media.ddPointSkinB[TEAM_NONE] = trap_R_RegisterShaderNoMip( "icons/noammo" );
	}

	if ( cgs.gametype == GT_CTF || cgs.gametype == GT_CTF_ELIMINATION || cgs.gametype == GT_1FCTF || cgs.gametype == GT_POSSESSION || cgs.gametype == GT_HARVESTER || cg_buildScript.integer ) {
		if ( cg_flagStyle.integer == 2 ) {
			cgs.media.redFlagModel = trap_R_RegisterModel( "models/flags2/r_flag.md3" );
			cgs.media.blueFlagModel = trap_R_RegisterModel( "models/flags2/b_flag.md3" );
		} else {
			cgs.media.redFlagModel = trap_R_RegisterModel( "models/flags/r_flag.md3" );
			cgs.media.blueFlagModel = trap_R_RegisterModel( "models/flags/b_flag.md3" );
		}
		cgs.media.neutralFlagModel = trap_R_RegisterModel( "models/flags/n_flag.md3" );
		cgs.media.redFlagShader[0] = trap_R_RegisterShaderNoMip( "icons/iconf_red1" );
		cgs.media.redFlagShader[1] = trap_R_RegisterShaderNoMip( "icons/iconf_red2" );
		cgs.media.redFlagShader[2] = trap_R_RegisterShaderNoMip( "icons/iconf_red3" );
		cgs.media.blueFlagShader[0] = trap_R_RegisterShaderNoMip( "icons/iconf_blu1" );
		cgs.media.blueFlagShader[1] = trap_R_RegisterShaderNoMip( "icons/iconf_blu2" );
		cgs.media.blueFlagShader[2] = trap_R_RegisterShaderNoMip( "icons/iconf_blu3" );
		cgs.media.flagPoleModel = trap_R_RegisterModel( "models/flag2/flagpole.md3" );
		cgs.media.flagFlapModel = trap_R_RegisterModel( "models/flag2/flagflap3.md3" );

		cgs.media.redFlagFlapSkin = trap_R_RegisterSkin( "models/flag2/red.skin" );
		cgs.media.blueFlagFlapSkin = trap_R_RegisterSkin( "models/flag2/blue.skin" );
		cgs.media.neutralFlagFlapSkin = trap_R_RegisterSkin( "models/flag2/white.skin" );

		cgs.media.redFlagBaseModel = trap_R_RegisterModel( "models/mapobjects/flagbase/red_base.md3" );
		cgs.media.blueFlagBaseModel = trap_R_RegisterModel( "models/mapobjects/flagbase/blue_base.md3" );
		cgs.media.neutralFlagBaseModel = trap_R_RegisterModel( "models/mapobjects/flagbase/ntrl_base.md3" );
	}

	if ( cgs.gametype == GT_1FCTF || cgs.gametype == GT_POSSESSION || cg_buildScript.integer ) {
		cgs.media.neutralFlagModel = trap_R_RegisterModel( "models/flags/n_flag.md3" );
		cgs.media.flagShader[0] = trap_R_RegisterShaderNoMip( "icons/iconf_neutral1" );
		cgs.media.flagShader[1] = trap_R_RegisterShaderNoMip( "icons/iconf_red2" );
		cgs.media.flagShader[2] = trap_R_RegisterShaderNoMip( "icons/iconf_blu2" );
		cgs.media.flagShader[3] = trap_R_RegisterShaderNoMip( "icons/iconf_neutral3" );
	}

	if ( cgs.gametype == GT_OBELISK || cg_buildScript.integer ) {
		cgs.media.rocketExplosionShader = trap_R_RegisterShader( "rocketExplosion" );
		cgs.media.overloadBaseModel = trap_R_RegisterModel( "models/powerups/overload_base.md3" );
		cgs.media.overloadTargetModel = trap_R_RegisterModel( "models/powerups/overload_target.md3" );
		cgs.media.overloadLightsModel = trap_R_RegisterModel( "models/powerups/overload_lights.md3" );
		cgs.media.overloadEnergyModel = trap_R_RegisterModel( "models/powerups/overload_energy.md3" );
	}

	if ( cgs.gametype == GT_HARVESTER || cg_buildScript.integer ) {
		cgs.media.harvesterModel = trap_R_RegisterModel( "models/powerups/harvester/harvester.md3" );
		cgs.media.harvesterRedSkin = trap_R_RegisterSkin( "models/powerups/harvester/red.skin" );
		cgs.media.harvesterBlueSkin = trap_R_RegisterSkin( "models/powerups/harvester/blue.skin" );
		cgs.media.harvesterNeutralModel = trap_R_RegisterModel( "models/powerups/obelisk/obelisk.md3" );
	}

	cgs.media.dustPuffShader = trap_R_RegisterShader( "hasteSmokePuff" );

	if ( ( ( cgs.gametype >= GT_TEAM ) && ( cgs.ffa_gt != 1 ) ) ||
	     cg_buildScript.integer ) {

		cgs.media.friendThroughWallsShader = trap_R_RegisterShader( "sprites/foe2.tga" );
		cgs.media.redQuadShader = trap_R_RegisterShader( "powerups/blueflag" );
		cgs.media.blueKamikazeShader = trap_R_RegisterShader( "models/weaphits/kamikblu" );
	}
	cgs.media.friendShader = trap_R_RegisterShader( "sprites/foe" );

	cgs.media.teamStatusBar = trap_R_RegisterShader( "gfx/2d/colorbar.tga" );

	cgs.media.armorModel = trap_R_RegisterModel( "models/powerups/armor/armor_yel.md3" );
	cgs.media.armorIcon = trap_R_RegisterShaderNoMip( "icons/iconr_yellow" );

	cgs.media.omegaLogoModel = trap_R_RegisterModel( "models/mapobjects/logo/logo.md3" );

	cgs.media.machinegunBrassModel = trap_R_RegisterModel( "models/weapons2/shells/m_shell.md3" );
	cgs.media.shotgunBrassModel = trap_R_RegisterModel( "models/weapons2/shells/s_shell.md3" );

	cgs.media.gibAbdomen = trap_R_RegisterModel( "models/gibs/abdomen.md3" );
	cgs.media.gibArm = trap_R_RegisterModel( "models/gibs/arm.md3" );
	cgs.media.gibChest = trap_R_RegisterModel( "models/gibs/chest.md3" );
	cgs.media.gibFist = trap_R_RegisterModel( "models/gibs/fist.md3" );
	cgs.media.gibFoot = trap_R_RegisterModel( "models/gibs/foot.md3" );
	cgs.media.gibForearm = trap_R_RegisterModel( "models/gibs/forearm.md3" );
	cgs.media.gibIntestine = trap_R_RegisterModel( "models/gibs/intestine.md3" );
	cgs.media.gibLeg = trap_R_RegisterModel( "models/gibs/leg.md3" );
	cgs.media.gibSkull = trap_R_RegisterModel( "models/gibs/skull.md3" );
	cgs.media.gibBrain = trap_R_RegisterModel( "models/gibs/brain.md3" );

	cgs.media.smoke2 = trap_R_RegisterModel( "models/weapons2/shells/s_shell.md3" );

	cgs.media.balloonShader = trap_R_RegisterShader( "sprites/balloon3" );

	cgs.media.bloodExplosionShader = trap_R_RegisterShader( "bloodExplosion" );

	cgs.media.bulletFlashModel = trap_R_RegisterModel( "models/weaphits/bullet.md3" );
	cgs.media.ringFlashModel = trap_R_RegisterModel( "models/weaphits/ring02.md3" );
	cgs.media.dishFlashModel = trap_R_RegisterModel( "models/weaphits/boom01.md3" );
	cgs.media.teleportEffectModel = trap_R_RegisterModel( "models/misc/telep.md3" );
	cgs.media.teleportEffectShader = trap_R_RegisterShader( "teleportEffect" );
	cgs.media.kamikazeEffectModel = trap_R_RegisterModel( "models/weaphits/kamboom2.md3" );
	cgs.media.kamikazeShockWave = trap_R_RegisterModel( "models/weaphits/kamwave.md3" );
	cgs.media.kamikazeHeadModel = trap_R_RegisterModel( "models/powerups/kamikazi.md3" );
	cgs.media.guardPowerupModel = trap_R_RegisterModel( "models/powerups/guard_player.md3" );
	cgs.media.scoutPowerupModel = trap_R_RegisterModel( "models/powerups/scout_player.md3" );
	cgs.media.doublerPowerupModel = trap_R_RegisterModel( "models/powerups/doubler_player.md3" );
	cgs.media.ammoRegenPowerupModel = trap_R_RegisterModel( "models/powerups/ammo_player.md3" );
	cgs.media.invulnerabilityImpactModel = trap_R_RegisterModel( "models/powerups/shield/impact.md3" );
	cgs.media.invulnerabilityJuicedModel = trap_R_RegisterModel( "models/powerups/shield/juicer.md3" );
	cgs.media.medkitUsageModel = trap_R_RegisterModel( "models/powerups/regen.md3" );

	cgs.media.invulnerabilityPowerupModel = trap_R_RegisterModel( "models/powerups/shield/shield.md3" );
	cgs.media.medalImpressive = trap_R_RegisterShaderNoMip( "medal_impressive" );
	cgs.media.medalExcellent = trap_R_RegisterShaderNoMip( "medal_excellent" );
	cgs.media.medalGauntlet = trap_R_RegisterShaderNoMip( "medal_gauntlet" );
	cgs.media.medalDefend = trap_R_RegisterShaderNoMip( "medal_defend" );
	cgs.media.medalAssist = trap_R_RegisterShaderNoMip( "medal_assist" );
	cgs.media.medalCapture = trap_R_RegisterShaderNoMip( "medal_capture" );
	cgs.media.medalHeadshot = trap_R_RegisterShaderNoMip( "medal_headshot" );
	cgs.media.medalRampage = trap_R_RegisterShaderNoMip( "medal_frags" );

	cgs.media.smileyHappy = trap_R_RegisterShader( "sprites/happy" );
	cgs.media.smileySad = trap_R_RegisterShader( "sprites/sad" );
	cgs.media.smileyAngry = trap_R_RegisterShader( "sprites/angry" );
	cgs.media.smileyMoon = trap_R_RegisterShader( "sprites/moon" );

	// LEILEI SHADERS
	cgs.media.lsmkShader1 = trap_R_RegisterShader( "leismoke1" );
	cgs.media.lsmkShader2 = trap_R_RegisterShader( "leismoke2" );
	cgs.media.lsmkShader3 = trap_R_RegisterShader( "leismoke3" );
	cgs.media.lsmkShader4 = trap_R_RegisterShader( "leismoke4" );

	cgs.media.lsplShader = trap_R_RegisterShader( "leisplash" );
	cgs.media.lspkShader1 = trap_R_RegisterShader( "leispark" );
	cgs.media.lspkShader2 = trap_R_RegisterShader( "leispark2" );
	cgs.media.lbumShader1 = trap_R_RegisterShader( "leiboom1" );
	cgs.media.lfblShader1 = trap_R_RegisterShader( "leifball" );

	cgs.media.lbldShader1 = trap_R_RegisterShader( "leiblood1" );
	cgs.media.lbldShader2 = trap_R_RegisterShader( "leiblood2" ); // this is a mark, by the way

	// New Bullet Marks
	cgs.media.lmarkmetal1 = trap_R_RegisterShader( "leimetalmark1" );
	cgs.media.lmarkmetal2 = trap_R_RegisterShader( "leimetalmark2" );
	cgs.media.lmarkmetal3 = trap_R_RegisterShader( "leimetalmark3" );
	cgs.media.lmarkmetal4 = trap_R_RegisterShader( "leimetalmark4" );
	cgs.media.lmarkbullet1 = trap_R_RegisterShader( "leibulletmark1" );
	cgs.media.lmarkbullet2 = trap_R_RegisterShader( "leibulletmark2" );
	cgs.media.lmarkbullet3 = trap_R_RegisterShader( "leibulletmark3" );
	cgs.media.lmarkbullet4 = trap_R_RegisterShader( "leibulletmark4" );

	memset( cg_items, 0, sizeof( cg_items ) );
	memset( cg_weapons, 0, sizeof( cg_weapons ) );

	// only register the items that the server says we need
	Q_strncpyz( items, CG_ConfigString( CS_ITEMS ), sizeof( items ) );

	for ( i = 1; i < bg_numItems; i++ ) {
		if ( items[i] == '1' || cg_buildScript.integer ) {
			CG_LoadingItem( i );
			CG_RegisterItemVisuals( i );
		}
	}

	// wall marks
	cgs.media.bulletMarkShader = trap_R_RegisterShader( "gfx/damage/bullet_mrk" );
	cgs.media.burnMarkShader = trap_R_RegisterShader( "gfx/damage/burn_med_mrk" );
	cgs.media.holeMarkShader = trap_R_RegisterShader( "gfx/damage/hole_lg_mrk" );
	cgs.media.energyMarkShader = trap_R_RegisterShader( "gfx/damage/plasma_mrk" );
	cgs.media.shadowMarkShader = trap_R_RegisterShader( "markShadow" );
	cgs.media.shadow2MarkShader = trap_R_RegisterShader( "markShadow2" );
	cgs.media.wakeMarkShader = trap_R_RegisterShader( "wake" );
	cgs.media.bloodMarkShader = trap_R_RegisterShader( "bloodMark" );

	// register the inline models
	cgs.numInlineModels = trap_CM_NumInlineModels();
	for ( i = 1; i < cgs.numInlineModels; i++ ) {
		char name[10];
		vec3_t mins, maxs;
		int j;

		Com_sprintf( name, sizeof( name ), "*%i", i );
		cgs.inlineDrawModel[i] = trap_R_RegisterModel( name );
		trap_R_ModelBounds( cgs.inlineDrawModel[i], mins, maxs );
		for ( j = 0; j < 3; j++ ) {
			cgs.inlineModelMidpoints[i][j] = mins[j] + 0.5 * ( maxs[j] - mins[j] );
		}
	}

	// register all the server specified models
	for ( i = 1; i < MAX_MODELS; i++ ) {
		const char *modelName;

		modelName = CG_ConfigString( CS_MODELS + i );
		if ( !modelName[0] ) {
			break;
		}
		cgs.gameModels[i] = trap_R_RegisterModel( modelName );
	}

	CG_ClearParticles();
}

/*																																			
=======================
CG_BuildSpectatorString
=======================
*/
void CG_BuildSpectatorString( void ) {
	int i;
	cg.spectatorList[0] = 0;
	for ( i = 0; i < MAX_CLIENTS; i++ ) {
		if ( cgs.clientinfo[i].infoValid && cgs.clientinfo[i].team == TEAM_SPECTATOR ) {
			Q_strcat( cg.spectatorList, sizeof( cg.spectatorList ), va( "%s     ", cgs.clientinfo[i].name ) );
		}
	}
	i = strlen( cg.spectatorList );
	if ( i != cg.spectatorLen ) {
		cg.spectatorLen = i;
		cg.spectatorWidth = -1;
	}
}

/*																																			
===================
CG_RegisterClients
===================
*/
static void CG_RegisterClients( void ) {
	int i;

	CG_LoadingClient( cg.clientNum );
	CG_NewClientInfo( cg.clientNum );

	for ( i = 0; i < MAX_CLIENTS; i++ ) {
		const char *clientInfo;

		if ( cg.clientNum == i ) {
			continue;
		}

		clientInfo = CG_ConfigString( CS_PLAYERS + i );
		if ( !clientInfo[0] ) {
			continue;
		}
		CG_LoadingClient( i );
		CG_NewClientInfo( i );
	}
	CG_BuildSpectatorString();
}

//===========================================================================

/*
=================
CG_ConfigString
=================
*/
const char *CG_ConfigString( int index ) {
	if ( index < 0 || index >= MAX_CONFIGSTRINGS ) {
		CG_Error( "CG_ConfigString: bad index: %i", index );
	}
	return cgs.gameState.stringData + cgs.gameState.stringOffsets[index];
}

//==================================================================

/*
======================
CG_StartMusic
======================
*/
void CG_StartMusic( void ) {
	char *s;
	char parm1[MAX_QPATH], parm2[MAX_QPATH];

	// start the background music
	if ( *cg_music.string && Q_stricmp( cg_music.string, "none" ) ) {
		s = (char *)cg_music.string;
	} else {
		s = (char *)CG_ConfigString( CS_MUSIC );
		Q_strncpyz( parm1, COM_Parse( &s ), sizeof( parm1 ) );
		Q_strncpyz( parm2, COM_Parse( &s ), sizeof( parm2 ) );

		trap_S_StartBackgroundTrack( parm1, parm2 );
	}
}

/*
=================
CG_Init

Called after every level change or subsystem restart
Will perform callbacks to make the loading info screen update.
=================
*/
void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum ) {
	char  value[MAX_CVAR_VALUE_STRING];
	const char *s;

	// clear everything
	memset( &cgs, 0, sizeof( cgs ) );
	memset( &cg, 0, sizeof( cg ) );
	memset( cg_entities, 0, sizeof( cg_entities ) );
	memset( cg_weapons, 0, sizeof( cg_weapons ) );
	memset( cg_items, 0, sizeof( cg_items ) );

	cg.clientNum = clientNum;

	cgs.processedSnapshotNum = serverMessageNum;
	cgs.serverCommandSequence = serverCommandSequence;

	trap_Cvar_VariableStringBuffer( "//trap_GetValue", value, sizeof( value ) );
	if ( value[0] ) {
#ifdef Q3_VM
		trap_GetValue = (void*)~atoi( value );
		if ( trap_GetValue( value, sizeof( value ), "trap_R_AddLinearLightToScene_Q3E" ) ) {
			trap_R_AddLinearLightToScene = (void*)~atoi( value );
			linearLight = qtrue;
		}
		if ( trap_GetValue( value, sizeof( value ), "trap_Cvar_SetDescription_Q3E" ) ) {
			trap_Cvar_SetDescription = (void*)~atoi( value );
			can_trap_Cvar_SetDescription = qtrue;
		}
#else
		dll_com_trapGetValue = atoi( value );
		if ( trap_GetValue( value, sizeof( value ), "trap_R_AddLinearLightToScene_Q3E" ) ) {
			dll_trap_R_AddLinearLightToScene = atoi( value );
			linearLight = qtrue;
		}
		if ( trap_GetValue( value, sizeof( value ), "trap_Cvar_SetDescription_Q3E" ) ) {
			dll_trap_Cvar_SetDescription = atoi( value );
			can_trap_Cvar_SetDescription = qtrue;
		}
#endif
	}

	// load a few needed things before we do any screen updates
	cgs.media.charsetShader = trap_R_RegisterShader( "gfx/2d/bigchars" );
	cgs.media.charsetShader16 = trap_R_RegisterShader( "gfx/2d/bigchars16" );
	cgs.media.charsetShader32 = trap_R_RegisterShader( "gfx/2d/bigchars32" );
	cgs.media.charsetShader64 = trap_R_RegisterShader( "gfx/2d/bigchars64" );
	cgs.media.whiteShader = trap_R_RegisterShader( "white" );
	cgs.media.charsetProp = trap_R_RegisterShaderNoMip( "menu/art/font1_prop" );
	cgs.media.charsetPropGlow = trap_R_RegisterShaderNoMip( "menu/art/font1_prop_glo" );
	cgs.media.charsetPropB = trap_R_RegisterShaderNoMip( "menu/art/font2_prop" );

	CG_RegisterCvars();

	CG_Initialize();

	CG_InitConsoleCommands();

	cg.weaponSelect = WP_MACHINEGUN;

	cgs.redflag = cgs.blueflag = -1; // For compatibility, default to unset for
	cgs.flagStatus = -1;
	// old servers

	// get the rendering configuration from the client system
	trap_GetGlconfig( &cgs.glconfig );
	cgs.screenXScale = cgs.glconfig.vidWidth / 640.0;
	cgs.screenYScale = cgs.glconfig.vidHeight / 480.0;

	// get the gamestate from the client system
	trap_GetGameState( &cgs.gameState );

	// check version
	s = CG_ConfigString( CS_GAME_VERSION );
	if ( strcmp( s, GAME_VERSION ) ) {
		CG_Error( "Client/Server game mismatch: %s/%s", GAME_VERSION, s );
	}

	s = CG_ConfigString( CS_LEVEL_START_TIME );
	cgs.levelStartTime = atoi( s );

	CG_ParseServerinfo();

	CG_ParseSysteminfo();

	// load the new map
	CG_LoadingString( "collision map" );

	trap_CM_LoadMap( cgs.mapname );

	cg.loading = qtrue; // force players to load instead of defer

	CG_LoadingString( "sounds" );

	CG_RegisterSounds();

	CG_LoadingString( "graphics" );

	CG_RegisterGraphics();

	CG_LoadingString( "clients" );

	CG_RegisterClients(); // if low on memory, some clients will be deferred

	cg.loading = qfalse; // future players will be deferred

	CG_InitLocalEntities();

	CG_InitMarkPolys();

	// remove the last loading update
	cg.infoScreenText[0] = 0;

	// Make sure we have update values (scores)
	CG_SetConfigValues();

	CG_StartMusic();

	CG_LoadingString( "" );

	CG_ShaderStateChanged();

	//Init challenge system
	challenges_init();

	addChallenge( GENERAL_TEST );

	trap_S_ClearLoopingSounds( qtrue );

	CG_ForceSoundsChange();
}

/*
=================
CG_Shutdown

Called before every level change or subsystem restart
=================
*/
void CG_Shutdown( void ) {
	// some mods may need to do cleanup work here,
	// like closing files or archiving session data
	challenges_save();
}

/*
==================
CG_EventHandling

 type	0 - no event handling
	1 - team menu
	2 - hud editor
==================
*/
void CG_EventHandling( int type ) {
}

/*
==================
CG_KeyEvent
==================
*/
void CG_KeyEvent( int key, qboolean down ) {
}

/*
==================
CG_MouseEvent
==================
*/
void CG_MouseEvent( int x, int y ) {
}

//unlagged - attack prediction #3
// moved from g_weapon.c
/*
======================
SnapVectorTowards

Round a vector to integers for more efficient network
transmission, but make sure that it rounds towards a given point
rather than blindly truncating. This prevents it from truncating 
into a wall.
======================
*/
void SnapVectorTowards( vec3_t v, vec3_t to ) {
	int i;

	for ( i = 0; i < 3; i++ ) {
		if ( to[i] <= v[i] ) {
			v[i] = (int)v[i];
		} else {
			v[i] = (int)v[i] + 1;
		}
	}
}
//unlagged - attack prediction #3

static qboolean do_vid_restart = qfalse;

void CG_FairCvars( void ) {
	qboolean vid_restart_required = qfalse;
	char rendererinfos[128];

	if ( cgs.gametype == GT_SINGLE_PLAYER ) {
		trap_Cvar_VariableStringBuffer( "r_vertexlight", rendererinfos, sizeof( rendererinfos ) );
		if ( cg_autovertex.integer && atoi( rendererinfos ) == 0 ) {
			trap_Cvar_Set( "r_vertexlight", "1" );
			vid_restart_required = qtrue;
		}
		return; //Don't do anything in single player
	}

	if ( cgs.videoflags & VF_LOCK_CVARS_BASIC ) {
		//Lock basic cvars.
		trap_Cvar_VariableStringBuffer( "r_subdivisions", rendererinfos, sizeof( rendererinfos ) );
		if ( atoi( rendererinfos ) > 80 ) {
			trap_Cvar_Set( "r_subdivisions", "80" );
			vid_restart_required = qtrue;
		}
	}

	if ( cgs.videoflags & VF_LOCK_CVARS_EXTENDED ) {
		//Lock extended cvars.
		trap_Cvar_VariableStringBuffer( "r_subdivisions", rendererinfos, sizeof( rendererinfos ) );
		if ( atoi( rendererinfos ) > 20 ) {
			trap_Cvar_Set( "r_subdivisions", "20" );
			vid_restart_required = qtrue;
		}

		trap_Cvar_VariableStringBuffer( "r_picmip", rendererinfos, sizeof( rendererinfos ) );
		if ( atoi( rendererinfos ) > 3 ) {
			trap_Cvar_Set( "r_picmip", "3" );
			vid_restart_required = qtrue;
		} else if ( atoi( rendererinfos ) < 0 ) {
			trap_Cvar_Set( "r_picmip", "0" );
			vid_restart_required = qtrue;
		}
		trap_Cvar_VariableStringBuffer( "r_intensity", rendererinfos, sizeof( rendererinfos ) );
		if ( atoi( rendererinfos ) > 2 ) {
			trap_Cvar_Set( "r_intensity", "2" );
			vid_restart_required = qtrue;
		} else if ( atoi( rendererinfos ) < 0 ) {
			trap_Cvar_Set( "r_intensity", "0" );
			vid_restart_required = qtrue;
		}

		trap_Cvar_VariableStringBuffer( "r_mapoverbrightbits", rendererinfos, sizeof( rendererinfos ) );
		if ( atoi( rendererinfos ) > 2 ) {
			trap_Cvar_Set( "r_mapoverbrightbits", "2" );
			vid_restart_required = qtrue;
		} else if ( atoi( rendererinfos ) < 0 ) {
			trap_Cvar_Set( "r_mapoverbrightbits", "0" );
			vid_restart_required = qtrue;
		}

		trap_Cvar_VariableStringBuffer( "r_overbrightbits", rendererinfos, sizeof( rendererinfos ) );
		if ( atoi( rendererinfos ) > 2 ) {
			trap_Cvar_Set( "r_overbrightbits", "2" );
			vid_restart_required = qtrue;
		} else if ( atoi( rendererinfos ) < 0 ) {
			trap_Cvar_Set( "r_overbrightbits", "0" );
			vid_restart_required = qtrue;
		}
	}

	if ( cgs.videoflags & VF_LOCK_VERTEX ) {
		trap_Cvar_VariableStringBuffer( "r_vertexlight", rendererinfos, sizeof( rendererinfos ) );
		if ( atoi( rendererinfos ) != 0 ) {
			trap_Cvar_Set( "r_vertexlight", "0" );
			vid_restart_required = qtrue;
		}
	} else if ( cg_autovertex.integer ) {
		trap_Cvar_VariableStringBuffer( "r_vertexlight", rendererinfos, sizeof( rendererinfos ) );
		if ( atoi( rendererinfos ) == 0 ) {
			trap_Cvar_Set( "r_vertexlight", "1" );
			vid_restart_required = qtrue;
		}
	}

	if ( vid_restart_required && do_vid_restart )
		trap_SendConsoleCommand( "vid_restart" );

	do_vid_restart = qtrue;
}
