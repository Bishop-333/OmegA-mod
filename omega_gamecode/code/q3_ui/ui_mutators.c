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
/*
=======================================================================

GAME OPTIONS MENU

=======================================================================
*/

#include "ui_local.h"

#define ART_FRAMEL "menu/art_blueish/frame2_l"
#define ART_FRAMER "menu/art_blueish/frame1_r"
#define ART_BACK0 "menu/art_blueish/back_0"
#define ART_BACK1 "menu/art_blueish/back_1"

#define MUTATORS_X_POS 320

#define ID_BACK 127
#define ID_AIRCONTROL 128
#define ID_AUTOHOP 129
#define ID_CHAOS 130
#define ID_DOUBLE_JUMP 131
#define ID_GUIDED_ROCKETS 132
#define ID_HEADSHOT_ONLY 133
#define ID_LEAVE_CORPSE 134
#define ID_NO_INVIS_WALLS 135
#define ID_OVERBOUNCE 136
#define ID_PLASMA_BOUNCE 137
#define ID_PROPHUNT 138
#define ID_RAIL_THROUGH_WALLS 139
#define ID_SLICK_GROUND 140
#define ID_SPECTATE_ON_DEATH 141

typedef struct {
	menuframework_s menu;

	menutext_s banner;
	menubitmap_s framel;
	menubitmap_s framer;

	menuradiobutton_s aircontrol;
	menuradiobutton_s autohop;
	menuradiobutton_s chaos;
	menuradiobutton_s doubleJump;
	menuradiobutton_s guidedRockets;
	menuradiobutton_s headshotOnly;
	menuradiobutton_s leaveCorpse;
	menuradiobutton_s noInvisWalls;
	menuradiobutton_s overbounce;
	menuradiobutton_s plasmaBounce;
	menuradiobutton_s prophunt;
	menuradiobutton_s railThroughWalls;
	menuradiobutton_s slickGround;
	menuradiobutton_s spectateOnDeath;

	menubitmap_s back;
} mutatorsOptions_t;

static mutatorsOptions_t mutatorsOptions_s;

/*
=================
MutatorsOptions_Event
=================
*/
static void MutatorsOptions_Event( void *ptr, int notification ) {

	if ( notification != QM_ACTIVATED ) {
		return;
	}

	switch ( ( (menucommon_s *)ptr )->id ) {
		case ID_AIRCONTROL:
			if ( mutatorsOptions_s.aircontrol.curvalue ) {
				trap_Cvar_SetValue( "pmove_aircontrol", 1 );
			} else {
				trap_Cvar_SetValue( "pmove_aircontrol", 0 );
			}
			break;

		case ID_AUTOHOP:
			if ( mutatorsOptions_s.autohop.curvalue ) {
				trap_Cvar_SetValue( "pmove_autohop", 1 );
			} else {
				trap_Cvar_SetValue( "pmove_autohop", 0 );
			}
			break;

		case ID_CHAOS:
			if ( mutatorsOptions_s.chaos.curvalue ) {
				trap_Cvar_SetValue( "g_chaos", 1 );
			} else {
				trap_Cvar_SetValue( "g_chaos", 0 );
			}
			break;

		case ID_DOUBLE_JUMP:
			if ( mutatorsOptions_s.doubleJump.curvalue ) {
				trap_Cvar_SetValue( "pmove_doublejump", 1 );
			} else {
				trap_Cvar_SetValue( "pmove_doublejump", 0 );
			}
			break;

		case ID_GUIDED_ROCKETS:
			if ( mutatorsOptions_s.guidedRockets.curvalue ) {
				trap_Cvar_SetValue( "g_guidedRockets", 1 );
			} else {
				trap_Cvar_SetValue( "g_guidedRockets", 0 );
			}
			break;

		case ID_HEADSHOT_ONLY:
			if ( mutatorsOptions_s.headshotOnly.curvalue ) {
				trap_Cvar_SetValue( "g_headshotOnly", 1 );
			} else {
				trap_Cvar_SetValue( "g_headshotOnly", 0 );
			}
			break;

		case ID_LEAVE_CORPSE:
			if ( mutatorsOptions_s.leaveCorpse.curvalue ) {
				trap_Cvar_SetValue( "g_leaveCorpse", 1 );
			} else {
				trap_Cvar_SetValue( "g_leaveCorpse", 0 );
			}
			break;

		case ID_NO_INVIS_WALLS:
			if ( mutatorsOptions_s.noInvisWalls.curvalue ) {
				trap_Cvar_SetValue( "g_noInvisWalls", 1 );
			} else {
				trap_Cvar_SetValue( "g_noInvisWalls", 0 );
			}
			break;

		case ID_OVERBOUNCE:
			if ( mutatorsOptions_s.overbounce.curvalue ) {
				trap_Cvar_SetValue( "pmove_overbounce", 1 );
			} else {
				trap_Cvar_SetValue( "pmove_overbounce", 0 );
			}
			break;

		case ID_PLASMA_BOUNCE:
			if ( mutatorsOptions_s.plasmaBounce.curvalue ) {
				trap_Cvar_SetValue( "g_plasmaBounce", 1 );
			} else {
				trap_Cvar_SetValue( "g_plasmaBounce", 0 );
			}
			break;

		case ID_PROPHUNT:
			if ( mutatorsOptions_s.prophunt.curvalue ) {
				trap_Cvar_SetValue( "g_prophunt", 1 );
			} else {
				trap_Cvar_SetValue( "g_prophunt", 0 );
			}
			break;

		case ID_RAIL_THROUGH_WALLS:
			if ( mutatorsOptions_s.railThroughWalls.curvalue ) {
				trap_Cvar_SetValue( "g_railThroughWalls", 1 );
			} else {
				trap_Cvar_SetValue( "g_railThroughWalls", 0 );
			}
			break;

		case ID_SLICK_GROUND:
			if ( mutatorsOptions_s.slickGround.curvalue ) {
				trap_Cvar_SetValue( "g_slickGround", 1 );
			} else {
				trap_Cvar_SetValue( "g_slickGround", 0 );
			}
			break;

		case ID_SPECTATE_ON_DEATH:
			if ( mutatorsOptions_s.spectateOnDeath.curvalue ) {
				trap_Cvar_SetValue( "g_spectateOnDeath", 1 );
			} else {
				trap_Cvar_SetValue( "g_spectateOnDeath", 0 );
			}
			break;

		case ID_BACK:
			UI_PopMenu();
			break;
	}
}

/*
=================
MutatorsOptions_MenuInit
=================
*/
static void MutatorsOptions_MenuInit( void ) {
	int y;

	memset( &mutatorsOptions_s, 0, sizeof( mutatorsOptions_t ) );

	UI_MutatorsOptionsMenu_Cache();

	mutatorsOptions_s.menu.wrapAround = qtrue;
	mutatorsOptions_s.menu.fullscreen = qtrue;

	mutatorsOptions_s.banner.generic.type = MTYPE_BTEXT;
	mutatorsOptions_s.banner.generic.x = 320;
	mutatorsOptions_s.banner.generic.y = 16;
	mutatorsOptions_s.banner.string = "MUTATORS";
	mutatorsOptions_s.banner.color = color_white;
	mutatorsOptions_s.banner.style = UI_CENTER;

	mutatorsOptions_s.framel.generic.type = MTYPE_BITMAP;
	mutatorsOptions_s.framel.generic.name = ART_FRAMEL;
	mutatorsOptions_s.framel.generic.flags = QMF_INACTIVE;
	mutatorsOptions_s.framel.generic.x = 0;
	mutatorsOptions_s.framel.generic.y = 78;
	mutatorsOptions_s.framel.width = 256;
	mutatorsOptions_s.framel.height = 329;

	mutatorsOptions_s.framer.generic.type = MTYPE_BITMAP;
	mutatorsOptions_s.framer.generic.name = ART_FRAMER;
	mutatorsOptions_s.framer.generic.flags = QMF_INACTIVE;
	mutatorsOptions_s.framer.generic.x = 376;
	mutatorsOptions_s.framer.generic.y = 76;
	mutatorsOptions_s.framer.width = 256;
	mutatorsOptions_s.framer.height = 334;

	y = 240 - 6.5 * ( BIGCHAR_HEIGHT + 2 );
	mutatorsOptions_s.aircontrol.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.aircontrol.generic.name = "Air Control:";
	mutatorsOptions_s.aircontrol.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.aircontrol.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.aircontrol.generic.id = ID_AIRCONTROL;
	mutatorsOptions_s.aircontrol.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.aircontrol.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.autohop.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.autohop.generic.name = "Autohop:";
	mutatorsOptions_s.autohop.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.autohop.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.autohop.generic.id = ID_AUTOHOP;
	mutatorsOptions_s.autohop.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.autohop.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.chaos.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.chaos.generic.name = "Chaos:";
	mutatorsOptions_s.chaos.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.chaos.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.chaos.generic.id = ID_CHAOS;
	mutatorsOptions_s.chaos.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.chaos.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.doubleJump.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.doubleJump.generic.name = "Double Jump:";
	mutatorsOptions_s.doubleJump.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.doubleJump.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.doubleJump.generic.id = ID_DOUBLE_JUMP;
	mutatorsOptions_s.doubleJump.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.doubleJump.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.guidedRockets.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.guidedRockets.generic.name = "Guided Rockets:";
	mutatorsOptions_s.guidedRockets.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.guidedRockets.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.guidedRockets.generic.id = ID_GUIDED_ROCKETS;
	mutatorsOptions_s.guidedRockets.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.guidedRockets.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.headshotOnly.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.headshotOnly.generic.name = "Headshot Only:";
	mutatorsOptions_s.headshotOnly.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.headshotOnly.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.headshotOnly.generic.id = ID_HEADSHOT_ONLY;
	mutatorsOptions_s.headshotOnly.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.headshotOnly.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.leaveCorpse.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.leaveCorpse.generic.name = "Leave Corpse:";
	mutatorsOptions_s.leaveCorpse.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.leaveCorpse.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.leaveCorpse.generic.id = ID_LEAVE_CORPSE;
	mutatorsOptions_s.leaveCorpse.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.leaveCorpse.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.noInvisWalls.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.noInvisWalls.generic.name = "No Invisible Walls:";
	mutatorsOptions_s.noInvisWalls.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.noInvisWalls.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.noInvisWalls.generic.id = ID_NO_INVIS_WALLS;
	mutatorsOptions_s.noInvisWalls.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.noInvisWalls.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.overbounce.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.overbounce.generic.name = "Overbounce:";
	mutatorsOptions_s.overbounce.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.overbounce.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.overbounce.generic.id = ID_OVERBOUNCE;
	mutatorsOptions_s.overbounce.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.overbounce.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.plasmaBounce.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.plasmaBounce.generic.name = "Plasma Bounce:";
	mutatorsOptions_s.plasmaBounce.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.plasmaBounce.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.plasmaBounce.generic.id = ID_PLASMA_BOUNCE;
	mutatorsOptions_s.plasmaBounce.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.plasmaBounce.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.prophunt.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.prophunt.generic.name = "Prop Hunt:";
	mutatorsOptions_s.prophunt.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.prophunt.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.prophunt.generic.id = ID_PROPHUNT;
	mutatorsOptions_s.prophunt.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.prophunt.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.railThroughWalls.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.railThroughWalls.generic.name = "Rail Through Walls:";
	mutatorsOptions_s.railThroughWalls.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.railThroughWalls.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.railThroughWalls.generic.id = ID_RAIL_THROUGH_WALLS;
	mutatorsOptions_s.railThroughWalls.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.railThroughWalls.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.slickGround.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.slickGround.generic.name = "Slick Ground:";
	mutatorsOptions_s.slickGround.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.slickGround.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.slickGround.generic.id = ID_SLICK_GROUND;
	mutatorsOptions_s.slickGround.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.slickGround.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.spectateOnDeath.generic.type = MTYPE_RADIOBUTTON;
	mutatorsOptions_s.spectateOnDeath.generic.name = "Spectate On Death:";
	mutatorsOptions_s.spectateOnDeath.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	mutatorsOptions_s.spectateOnDeath.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.spectateOnDeath.generic.id = ID_SPECTATE_ON_DEATH;
	mutatorsOptions_s.spectateOnDeath.generic.x = MUTATORS_X_POS;
	mutatorsOptions_s.spectateOnDeath.generic.y = y;

	y += BIGCHAR_HEIGHT + 2;
	mutatorsOptions_s.back.generic.type = MTYPE_BITMAP;
	mutatorsOptions_s.back.generic.name = ART_BACK0;
	mutatorsOptions_s.back.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
	mutatorsOptions_s.back.generic.callback = MutatorsOptions_Event;
	mutatorsOptions_s.back.generic.id = ID_BACK;
	mutatorsOptions_s.back.generic.x = 0;
	mutatorsOptions_s.back.generic.y = 480 - 64;
	mutatorsOptions_s.back.width = 128;
	mutatorsOptions_s.back.height = 64;
	mutatorsOptions_s.back.focuspic = ART_BACK1;

	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.banner );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.framel );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.framer );

	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.aircontrol );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.autohop );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.chaos );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.doubleJump );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.guidedRockets );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.headshotOnly );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.leaveCorpse );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.noInvisWalls );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.overbounce );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.plasmaBounce );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.prophunt );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.railThroughWalls );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.slickGround );
	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.spectateOnDeath );

	Menu_AddItem( &mutatorsOptions_s.menu, &mutatorsOptions_s.back );

	mutatorsOptions_s.aircontrol.curvalue = trap_Cvar_VariableValue( "pmove_aircontrol" );
	mutatorsOptions_s.autohop.curvalue = trap_Cvar_VariableValue( "pmove_autohop" );
	mutatorsOptions_s.chaos.curvalue = trap_Cvar_VariableValue( "g_chaos" );
	mutatorsOptions_s.doubleJump.curvalue = trap_Cvar_VariableValue( "pmove_doublejump" );
	mutatorsOptions_s.guidedRockets.curvalue = trap_Cvar_VariableValue( "g_guidedRockets" );
	mutatorsOptions_s.headshotOnly.curvalue = trap_Cvar_VariableValue( "g_headshotOnly" );
	mutatorsOptions_s.leaveCorpse.curvalue = trap_Cvar_VariableValue( "g_leaveCorpse" );
	mutatorsOptions_s.noInvisWalls.curvalue = trap_Cvar_VariableValue( "g_noInvisWalls" );
	mutatorsOptions_s.overbounce.curvalue = trap_Cvar_VariableValue( "pmove_overbounce" );
	mutatorsOptions_s.plasmaBounce.curvalue = trap_Cvar_VariableValue( "g_plasmaBounce" );
	mutatorsOptions_s.prophunt.curvalue = trap_Cvar_VariableValue( "g_prophunt" );
	mutatorsOptions_s.railThroughWalls.curvalue = trap_Cvar_VariableValue( "g_railThroughWalls" );
	mutatorsOptions_s.slickGround.curvalue = trap_Cvar_VariableValue( "g_slickGround" );
	mutatorsOptions_s.spectateOnDeath.curvalue = trap_Cvar_VariableValue( "g_spectateOnDeath" );
}

/*
===============
UI_MutatorsOptionsMenu_Cache
===============
*/
void UI_MutatorsOptionsMenu_Cache( void ) {

	trap_R_RegisterShaderNoMip( ART_FRAMEL );
	trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
}

/*
===============
UI_MutatorsOptionsMenu
===============
*/
void UI_MutatorsOptionsMenu( void ) {
	MutatorsOptions_MenuInit();
	UI_PushMenu( &mutatorsOptions_s.menu );
}
