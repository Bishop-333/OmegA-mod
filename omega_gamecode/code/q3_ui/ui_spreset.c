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
/*
=======================================================================

RESET MENU

=======================================================================
*/

#include "ui_local.h"

#define ART_FRAME "menu/art/cut_frame"

#define ID_NO 100
#define ID_YES 101

typedef struct
{
	menuframework_s menu;
	menutext_s no;
	menutext_s yes;
	int slashX;
} resetMenu_t;

static resetMenu_t s_reset;

/*
=================
Reset_MenuEvent
=================
*/
static void Reset_MenuEvent( void *ptr, int event ) {
	if ( event != QM_ACTIVATED ) {
		return;
	}

	UI_PopMenu();

	if ( ( (menucommon_s *)ptr )->id == ID_NO ) {
		return;
	}

	// reset the game, pop the level menu and restart it so it updates
	UI_NewGame();
	trap_Cvar_SetValue( "ui_spSelection", 0 );
	UI_PopMenu();
	UI_SPLevelMenu();
}

/*
=================
Reset_MenuKey
=================
*/
static sfxHandle_t Reset_MenuKey( int key ) {
	switch ( key ) {
		case K_LEFTARROW:
		case K_RIGHTARROW:
			key = K_TAB;
			break;

		case 'n':
		case 'N':
			Reset_MenuEvent( &s_reset.no, QM_ACTIVATED );
			break;

		case 'y':
		case 'Y':
			Reset_MenuEvent( &s_reset.yes, QM_ACTIVATED );
			break;
	}

	return Menu_DefaultKey( &s_reset.menu, key );
}

/*
=================
Reset_MenuDraw
=================
*/
static void Reset_MenuDraw( void ) {
	UI_DrawNamedPic( 142, 118, 359, 256, ART_FRAME );
	UI_DrawProportionalString( 320, 194 + 10, "RESET GAME?", UI_CENTER | UI_INVERSE, color_red );
	UI_DrawProportionalString( s_reset.slashX, 265, "/", UI_LEFT | UI_INVERSE, color_red );
	Menu_Draw( &s_reset.menu );

	UI_DrawProportionalString( SCREEN_WIDTH / 2, 356 + PROP_HEIGHT * 0, "WARNING: This resets all of the", UI_CENTER | UI_SMALLFONT, color_yellow );
	UI_DrawProportionalString( SCREEN_WIDTH / 2, 356 + PROP_HEIGHT * 1, "single player game variables.", UI_CENTER | UI_SMALLFONT, color_yellow );
	UI_DrawProportionalString( SCREEN_WIDTH / 2, 356 + PROP_HEIGHT * 2, "Do this only if you want to", UI_CENTER | UI_SMALLFONT, color_yellow );
	UI_DrawProportionalString( SCREEN_WIDTH / 2, 356 + PROP_HEIGHT * 3, "start over from the beginning.", UI_CENTER | UI_SMALLFONT, color_yellow );
}

/*
=================
Reset_Cache
=================
*/
static void Reset_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_FRAME );
}
