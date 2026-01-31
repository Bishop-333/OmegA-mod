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

DISPLAY OPTIONS MENU

=======================================================================
*/

#include "ui_local.h"

#define ART_FRAMEL "menu/art_blueish/frame2_l"
#define ART_FRAMER "menu/art_blueish/frame1_r"
#define ART_BACK0 "menu/art_blueish/back_0"
#define ART_BACK1 "menu/art_blueish/back_1"
#define ART_ACCEPT0 "menu/art_blueish/accept_0"
#define ART_ACCEPT1 "menu/art_blueish/accept_1"

#define ID_GRAPHICS 10
#define ID_DISPLAY 11
#define ID_SOUND 12
#define ID_NETWORK 13
#define ID_BRIGHTNESS 14
#define ID_MAXFPS 15
#define ID_VSYNC 16
#define ID_BACK 17

typedef struct {
	menuframework_s menu;

	menutext_s banner;
	menubitmap_s framel;
	menubitmap_s framer;

	menutext_s graphics;
	menutext_s display;
	menutext_s sound;
	menutext_s network;

	menuslider_s brightness;
	menuslider_s maxfps;

	menulist_s hdr;
	menulist_s vsync;

	menubitmap_s apply;
	menubitmap_s back;
} displayOptionsInfo_t;

typedef struct
{
	qboolean hdr;
	qboolean vsync;
} InitialVideoOptions_s;

static InitialVideoOptions_s s_ido;
static displayOptionsInfo_t displayOptionsInfo;

/*
=================
DisplayOptions_GetInitialDisplay
=================
*/
static void DisplayOptions_GetInitialDisplay( void ) {
	s_ido.hdr = displayOptionsInfo.hdr.curvalue;
	s_ido.vsync = displayOptionsInfo.vsync.curvalue;
}

/*
=================
DisplayOptions_UpdateMenuItems
=================
*/
static void DisplayOptions_UpdateMenuItems( void ) {
	displayOptionsInfo.apply.generic.flags |= QMF_HIDDEN | QMF_INACTIVE;

	if ( displayOptionsInfo.vsync.curvalue == 1 ) {
		displayOptionsInfo.maxfps.generic.flags |= QMF_GRAYED;
	} else {
		displayOptionsInfo.maxfps.generic.flags &= ~QMF_GRAYED;
	}

	if ( s_ido.hdr != displayOptionsInfo.hdr.curvalue ) {
		displayOptionsInfo.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ido.vsync != displayOptionsInfo.vsync.curvalue ) {
		displayOptionsInfo.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
}

/*
=================
DisplayOptions_ApplyChanges
=================
*/
static void DisplayOptions_ApplyChanges( void *unused, int notification ) {
	if ( notification != QM_ACTIVATED )
		return;

	if ( displayOptionsInfo.vsync.curvalue == 1 ) {
		trap_Cvar_SetValue( "com_maxfps", 0 );
	} else {
		trap_Cvar_SetValue( "com_maxfps", trap_Cvar_VariableValue( "ui_saved_maxfps" ) );
	}

	trap_Cvar_SetValue( "r_hdr", displayOptionsInfo.hdr.curvalue );
	trap_Cvar_SetValue( "r_swapInterval", displayOptionsInfo.vsync.curvalue );

	trap_Cmd_ExecuteText( EXEC_APPEND, "vid_restart\n" );
}

/*
=================
UI_DisplayOptionsMenu_Event
=================
*/
static void UI_DisplayOptionsMenu_Event( void *ptr, int event ) {
	if ( event != QM_ACTIVATED ) {
		return;
	}

	switch ( ( (menucommon_s *)ptr )->id ) {
		case ID_GRAPHICS:
			UI_PopMenu();
			UI_GraphicsOptionsMenu();
			break;

		case ID_DISPLAY:
			break;

		case ID_SOUND:
			UI_PopMenu();
			UI_SoundOptionsMenu();
			break;

		case ID_NETWORK:
			UI_PopMenu();
			UI_NetworkOptionsMenu();
			break;

		case ID_BRIGHTNESS:
			trap_Cvar_SetValue( "r_gamma", displayOptionsInfo.brightness.curvalue / 10.0f );
			break;

		case ID_MAXFPS:
			if ( (int)displayOptionsInfo.maxfps.curvalue >= displayOptionsInfo.maxfps.maxvalue ) {
				trap_Cvar_SetValue( "com_maxfps", 0 );
			} else {
				trap_Cvar_SetValue( "com_maxfps", (int)displayOptionsInfo.maxfps.curvalue );
			}
			break;

		case ID_VSYNC:
			if ( displayOptionsInfo.vsync.curvalue == 1 ) {
				trap_Cvar_SetValue( "ui_saved_maxfps", (int)displayOptionsInfo.maxfps.curvalue );
				displayOptionsInfo.maxfps.curvalue = displayOptionsInfo.maxfps.maxvalue;
			} else {
				displayOptionsInfo.maxfps.curvalue = trap_Cvar_VariableValue( "ui_saved_maxfps" );
			}
			break;

		case ID_BACK:
			UI_PopMenu();
			break;
	}
}

/*
================
DisplayOptions_MenuDraw
================
*/
static void DisplayOptions_MenuDraw( void ) {
	float *color;
	int x, y;
	int style;
	qboolean focus;
	char buf[32];

	x = displayOptionsInfo.maxfps.generic.x + SMALLCHAR_WIDTH + 100;
	y = displayOptionsInfo.maxfps.generic.y;

	style = UI_SMALLFONT;
	focus = displayOptionsInfo.maxfps.generic.parent->cursor == displayOptionsInfo.maxfps.generic.menuPosition;

	if ( focus ) {
		color = text_color_highlight;
		style |= UI_PULSE;
	} else {
		color = text_color_normal;
	}

	if ( displayOptionsInfo.maxfps.curvalue >= displayOptionsInfo.maxfps.maxvalue ) {
		strcpy( buf, "Unlimited" );
	} else {
		Com_sprintf( buf, sizeof( buf ), "%i", (int)displayOptionsInfo.maxfps.curvalue );
	}

	UI_DrawString( x, y, buf, style, color );

	//APSFIX - rework this
	DisplayOptions_UpdateMenuItems();

	Menu_Draw( &displayOptionsInfo.menu );
}

/*
=================
DisplayOptions_SetMenuItems
=================
*/
static void DisplayOptions_SetMenuItems( void ) {
	displayOptionsInfo.hdr.curvalue = trap_Cvar_VariableValue( "r_hdr" );
	displayOptionsInfo.vsync.curvalue = trap_Cvar_VariableValue( "r_swapInterval" );
}

/*
===============
UI_DisplayOptionsMenu_Init
===============
*/
static void UI_DisplayOptionsMenu_Init( void ) {
	static const char *enabled_names[] =
	    {
	        "Off",
	        "On",
	        NULL };

	int y;

	memset( &displayOptionsInfo, 0, sizeof( displayOptionsInfo ) );

	UI_DisplayOptionsMenu_Cache();
	displayOptionsInfo.menu.wrapAround = qtrue;
	displayOptionsInfo.menu.fullscreen = qtrue;
	displayOptionsInfo.menu.draw = DisplayOptions_MenuDraw;

	displayOptionsInfo.banner.generic.type = MTYPE_BTEXT;
	displayOptionsInfo.banner.generic.flags = QMF_CENTER_JUSTIFY;
	displayOptionsInfo.banner.generic.x = 320;
	displayOptionsInfo.banner.generic.y = 16;
	displayOptionsInfo.banner.string = "SYSTEM SETUP";
	displayOptionsInfo.banner.color = color_white;
	displayOptionsInfo.banner.style = UI_CENTER;

	displayOptionsInfo.framel.generic.type = MTYPE_BITMAP;
	displayOptionsInfo.framel.generic.name = ART_FRAMEL;
	displayOptionsInfo.framel.generic.flags = QMF_INACTIVE;
	displayOptionsInfo.framel.generic.x = 0;
	displayOptionsInfo.framel.generic.y = 78;
	displayOptionsInfo.framel.width = 256;
	displayOptionsInfo.framel.height = 329;

	displayOptionsInfo.framer.generic.type = MTYPE_BITMAP;
	displayOptionsInfo.framer.generic.name = ART_FRAMER;
	displayOptionsInfo.framer.generic.flags = QMF_INACTIVE;
	displayOptionsInfo.framer.generic.x = 376;
	displayOptionsInfo.framer.generic.y = 76;
	displayOptionsInfo.framer.width = 256;
	displayOptionsInfo.framer.height = 334;

	displayOptionsInfo.graphics.generic.type = MTYPE_PTEXT;
	displayOptionsInfo.graphics.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS;
	displayOptionsInfo.graphics.generic.id = ID_GRAPHICS;
	displayOptionsInfo.graphics.generic.callback = UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.graphics.generic.x = 216;
	displayOptionsInfo.graphics.generic.y = 240 - 2 * PROP_HEIGHT;
	displayOptionsInfo.graphics.string = "GRAPHICS";
	displayOptionsInfo.graphics.style = UI_RIGHT;
	displayOptionsInfo.graphics.color = color_red;

	displayOptionsInfo.display.generic.type = MTYPE_PTEXT;
	displayOptionsInfo.display.generic.flags = QMF_RIGHT_JUSTIFY;
	displayOptionsInfo.display.generic.id = ID_DISPLAY;
	displayOptionsInfo.display.generic.callback = UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.display.generic.x = 216;
	displayOptionsInfo.display.generic.y = 240 - PROP_HEIGHT;
	displayOptionsInfo.display.string = "DISPLAY";
	displayOptionsInfo.display.style = UI_RIGHT;
	displayOptionsInfo.display.color = color_red;

	displayOptionsInfo.sound.generic.type = MTYPE_PTEXT;
	displayOptionsInfo.sound.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS;
	displayOptionsInfo.sound.generic.id = ID_SOUND;
	displayOptionsInfo.sound.generic.callback = UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.sound.generic.x = 216;
	displayOptionsInfo.sound.generic.y = 240;
	displayOptionsInfo.sound.string = "SOUND";
	displayOptionsInfo.sound.style = UI_RIGHT;
	displayOptionsInfo.sound.color = color_red;

	displayOptionsInfo.network.generic.type = MTYPE_PTEXT;
	displayOptionsInfo.network.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS;
	displayOptionsInfo.network.generic.id = ID_NETWORK;
	displayOptionsInfo.network.generic.callback = UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.network.generic.x = 216;
	displayOptionsInfo.network.generic.y = 240 + PROP_HEIGHT;
	displayOptionsInfo.network.string = "NETWORK";
	displayOptionsInfo.network.style = UI_RIGHT;
	displayOptionsInfo.network.color = color_red;

	y = 240 - 2 * ( BIGCHAR_HEIGHT + 2 );
	displayOptionsInfo.brightness.generic.type = MTYPE_SLIDER;
	displayOptionsInfo.brightness.generic.name = "Brightness:";
	displayOptionsInfo.brightness.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT | QMF_SLIDER_PERCENTAGE;
	displayOptionsInfo.brightness.generic.callback = UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.brightness.generic.id = ID_BRIGHTNESS;
	displayOptionsInfo.brightness.generic.x = 400;
	displayOptionsInfo.brightness.generic.y = y;
	displayOptionsInfo.brightness.minvalue = 5;
	displayOptionsInfo.brightness.maxvalue = 20;
	if ( !uis.glconfig.deviceSupportsGamma ) {
		displayOptionsInfo.brightness.generic.flags |= QMF_GRAYED;
	}

	y += BIGCHAR_HEIGHT + 2;
	displayOptionsInfo.maxfps.generic.type = MTYPE_SLIDER;
	displayOptionsInfo.maxfps.generic.name = "Max Framerate:";
	displayOptionsInfo.maxfps.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT | QMF_SLIDER_NOVALUE;
	displayOptionsInfo.maxfps.generic.callback = UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.maxfps.generic.id = ID_MAXFPS;
	displayOptionsInfo.maxfps.generic.x = 400;
	displayOptionsInfo.maxfps.generic.y = y;
	displayOptionsInfo.maxfps.minvalue = 10;
	displayOptionsInfo.maxfps.maxvalue = 254;

	y += BIGCHAR_HEIGHT + 2;
	displayOptionsInfo.hdr.generic.type = MTYPE_SPINCONTROL;
	displayOptionsInfo.hdr.generic.name = "HDR:";
	displayOptionsInfo.hdr.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	displayOptionsInfo.hdr.generic.x = 400;
	displayOptionsInfo.hdr.generic.y = y;
	displayOptionsInfo.hdr.itemnames = enabled_names;

	y += BIGCHAR_HEIGHT + 2;
	displayOptionsInfo.vsync.generic.type = MTYPE_SPINCONTROL;
	displayOptionsInfo.vsync.generic.name = "V-Sync:";
	displayOptionsInfo.vsync.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	displayOptionsInfo.vsync.generic.callback = UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.vsync.generic.id = ID_VSYNC;
	displayOptionsInfo.vsync.generic.x = 400;
	displayOptionsInfo.vsync.generic.y = y;
	displayOptionsInfo.vsync.itemnames = enabled_names;

	displayOptionsInfo.back.generic.type = MTYPE_BITMAP;
	displayOptionsInfo.back.generic.name = ART_BACK0;
	displayOptionsInfo.back.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
	displayOptionsInfo.back.generic.callback = UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.back.generic.id = ID_BACK;
	displayOptionsInfo.back.generic.x = 0;
	displayOptionsInfo.back.generic.y = 480 - 64;
	displayOptionsInfo.back.width = 128;
	displayOptionsInfo.back.height = 64;
	displayOptionsInfo.back.focuspic = ART_BACK1;

	displayOptionsInfo.apply.generic.type = MTYPE_BITMAP;
	displayOptionsInfo.apply.generic.name = ART_ACCEPT0;
	displayOptionsInfo.apply.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS | QMF_HIDDEN | QMF_INACTIVE;
	displayOptionsInfo.apply.generic.callback = DisplayOptions_ApplyChanges;
	displayOptionsInfo.apply.generic.x = 640;
	displayOptionsInfo.apply.generic.y = 480 - 64;
	displayOptionsInfo.apply.width = 128;
	displayOptionsInfo.apply.height = 64;
	displayOptionsInfo.apply.focuspic = ART_ACCEPT1;

	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.banner );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.framel );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.framer );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.graphics );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.display );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.sound );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.network );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.brightness );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.maxfps );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.back );
	Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.apply );

	if ( trap_Cvar_VariableValue( "cl_omegaEngine" ) == 1 ) {
		Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.hdr );
		Menu_AddItem( &displayOptionsInfo.menu, (void *)&displayOptionsInfo.vsync );
	}

	displayOptionsInfo.brightness.curvalue = trap_Cvar_VariableValue( "r_gamma" ) * 10;
	if ( trap_Cvar_VariableValue( "com_maxfps" ) == 0 ) {
		displayOptionsInfo.maxfps.curvalue = displayOptionsInfo.maxfps.maxvalue;
	} else {
		displayOptionsInfo.maxfps.curvalue = trap_Cvar_VariableValue( "com_maxfps" );
	}

	DisplayOptions_SetMenuItems();
	DisplayOptions_GetInitialDisplay();
}

/*
===============
UI_DisplayOptionsMenu_Cache
===============
*/
void UI_DisplayOptionsMenu_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_FRAMEL );
	trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( ART_ACCEPT0 );
	trap_R_RegisterShaderNoMip( ART_ACCEPT1 );
}

/*
===============
UI_DisplayOptionsMenu
===============
*/
void UI_DisplayOptionsMenu( void ) {
	UI_DisplayOptionsMenu_Init();
	UI_PushMenu( &displayOptionsInfo.menu );
	Menu_SetCursorToItem( &displayOptionsInfo.menu, &displayOptionsInfo.display );
}
