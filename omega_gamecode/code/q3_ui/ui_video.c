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
#include "ui_local.h"

void GraphicsOptions_MenuInit( void );

/*
=======================================================================

DRIVER INFORMATION MENU

=======================================================================
*/

#define DRIVERINFO_FRAMEL "menu/art_blueish/frame2_l"
#define DRIVERINFO_FRAMER "menu/art_blueish/frame1_r"
#define DRIVERINFO_BACK0 "menu/art_blueish/back_0"
#define DRIVERINFO_BACK1 "menu/art_blueish/back_1"
#define DRIVERINFO_ARROWS0 "menu/art_blueish/arrows_vert_0"
#define DRIVERINFO_ARROWS_UP "menu/art_blueish/arrows_vert_top"
#define DRIVERINFO_ARROWS_DOWN "menu/art_blueish/arrows_vert_bot"

static char *driverinfo_artlist[] =
    {
        DRIVERINFO_FRAMEL,
        DRIVERINFO_FRAMER,
        DRIVERINFO_BACK0,
        DRIVERINFO_BACK1,
        DRIVERINFO_ARROWS0,
        DRIVERINFO_ARROWS_UP,
        DRIVERINFO_ARROWS_DOWN,
        NULL,
};

#define ID_SCROLL_UP 98
#define ID_SCROLL_DOWN 99
#define ID_DRIVERINFOBACK 100

typedef struct
{
	menuframework_s menu;
	menutext_s banner;
	menubitmap_s back;
	menubitmap_s framel;
	menubitmap_s framer;
	menubitmap_s arrows;
	menubitmap_s up;
	menubitmap_s down;
	char stringbuff[4096];
	char *strings[256];
	int numstrings;
	int row;
} driverinfo_t;

static driverinfo_t s_driverinfo;

/*
=================
DriverInfo_Event
=================
*/
static void DriverInfo_Event( void *ptr, int event ) {
	if ( event != QM_ACTIVATED )
		return;

	switch ( ( (menucommon_s *)ptr )->id ) {
		case ID_SCROLL_UP:
			if ( s_driverinfo.row > 0 ) {
				s_driverinfo.row--;
			}
			break;

		case ID_SCROLL_DOWN:
			if ( s_driverinfo.row + 13 < s_driverinfo.numstrings / 2 ) {
				s_driverinfo.row++;
			}
			break;

		case ID_DRIVERINFOBACK:
			UI_PopMenu();
			break;
	}
}

/*
=================
DriverInfo_MenuDraw
=================
*/
static void DriverInfo_MenuDraw( void ) {
	int i;
	int y;

	Menu_Draw( &s_driverinfo.menu );

	UI_DrawString( 320, 80, "VENDOR", UI_CENTER | UI_SMALLFONT, color_red );
	UI_DrawString( 320, 152, "PIXELFORMAT", UI_CENTER | UI_SMALLFONT, color_red );
	UI_DrawString( 320, 192, "EXTENSIONS", UI_CENTER | UI_SMALLFONT, color_red );

	UI_DrawString( 320, 80 + 16, uis.glconfig.vendor_string, UI_CENTER | UI_SMALLFONT, text_color_normal );
	UI_DrawString( 320, 96 + 16, uis.glconfig.version_string, UI_CENTER | UI_SMALLFONT, text_color_normal );
	UI_DrawString( 320, 112 + 16, uis.glconfig.renderer_string, UI_CENTER | UI_SMALLFONT, text_color_normal );
	UI_DrawString( 320, 152 + 16, va( "color(%d-bits) Z(%d-bits) stencil(%d-bits)", uis.glconfig.colorBits, uis.glconfig.depthBits, uis.glconfig.stencilBits ), UI_CENTER | UI_SMALLFONT, text_color_normal );

	// double column
	y = 192 + 16;
	for ( i = s_driverinfo.row; i < s_driverinfo.row + 13; i++ ) {
		UI_DrawString( 320 - 4, y, s_driverinfo.strings[i * 2], UI_RIGHT | UI_SMALLFONT, text_color_normal );
		UI_DrawString( 320 + 4, y, s_driverinfo.strings[i * 2 + 1], UI_LEFT | UI_SMALLFONT, text_color_normal );
		y += SMALLCHAR_HEIGHT;
	}

	if ( s_driverinfo.numstrings & 1 )
		UI_DrawString( 320, y, s_driverinfo.strings[s_driverinfo.numstrings - 1], UI_CENTER | UI_SMALLFONT, text_color_normal );
}

/*
=================
DriverInfo_MenuKey
=================
*/
static sfxHandle_t DriverInfo_MenuKey( int key ) {
	if ( key == K_MWHEELUP || key == K_UPARROW ) {
		if ( s_driverinfo.row > 0 ) {
			s_driverinfo.row--;
			return menu_move_sound;
		} else if ( key == K_UPARROW ) {
			return menu_buzz_sound;
		}
	}

	if ( key == K_MWHEELDOWN || key == K_DOWNARROW ) {
		if ( s_driverinfo.row + 13 < s_driverinfo.numstrings / 2 ) {
			s_driverinfo.row++;
			return menu_move_sound;
		} else if ( key == K_DOWNARROW ) {
			return menu_buzz_sound;
		}
	}

	return Menu_DefaultKey( &s_driverinfo.menu, key );
}

/*
=================
DriverInfo_Cache
=================
*/
void DriverInfo_Cache( void ) {
	int i;

	// touch all our pics
	for ( i = 0;; i++ ) {
		if ( !driverinfo_artlist[i] )
			break;
		trap_R_RegisterShaderNoMip( driverinfo_artlist[i] );
	}
}

/*
=================
UI_DriverInfo_Menu
=================
*/
static void UI_DriverInfo_Menu( void ) {
	char *eptr;
	int i;
	int len;

	// zero set all our globals
	memset( &s_driverinfo, 0, sizeof( driverinfo_t ) );

	DriverInfo_Cache();

	s_driverinfo.menu.fullscreen = qtrue;
	s_driverinfo.menu.draw = DriverInfo_MenuDraw;
	s_driverinfo.menu.key = DriverInfo_MenuKey;

	s_driverinfo.banner.generic.type = MTYPE_BTEXT;
	s_driverinfo.banner.generic.x = 320;
	s_driverinfo.banner.generic.y = 16;
	s_driverinfo.banner.string = "DRIVER INFO";
	s_driverinfo.banner.color = color_white;
	s_driverinfo.banner.style = UI_CENTER;

	s_driverinfo.framel.generic.type = MTYPE_BITMAP;
	s_driverinfo.framel.generic.name = DRIVERINFO_FRAMEL;
	s_driverinfo.framel.generic.flags = QMF_INACTIVE;
	s_driverinfo.framel.generic.x = 0;
	s_driverinfo.framel.generic.y = 78;
	s_driverinfo.framel.width = 256;
	s_driverinfo.framel.height = 329;

	s_driverinfo.framer.generic.type = MTYPE_BITMAP;
	s_driverinfo.framer.generic.name = DRIVERINFO_FRAMER;
	s_driverinfo.framer.generic.flags = QMF_INACTIVE;
	s_driverinfo.framer.generic.x = 376;
	s_driverinfo.framer.generic.y = 76;
	s_driverinfo.framer.width = 256;
	s_driverinfo.framer.height = 334;

	s_driverinfo.arrows.generic.type = MTYPE_BITMAP;
	s_driverinfo.arrows.generic.name = DRIVERINFO_ARROWS0;
	s_driverinfo.arrows.generic.flags = QMF_LEFT_JUSTIFY | QMF_INACTIVE;
	s_driverinfo.arrows.generic.callback = DriverInfo_Event;
	s_driverinfo.arrows.generic.x = 512 + 48 + 48;
	s_driverinfo.arrows.generic.y = 240 - 64 + 48;
	s_driverinfo.arrows.width = 64;
	s_driverinfo.arrows.height = 128;

	s_driverinfo.up.generic.type = MTYPE_BITMAP;
	s_driverinfo.up.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS | QMF_MOUSEONLY;
	s_driverinfo.up.generic.callback = DriverInfo_Event;
	s_driverinfo.up.generic.id = ID_SCROLL_UP;
	s_driverinfo.up.generic.x = 512 + 48 + 48;
	s_driverinfo.up.generic.y = 240 - 64 + 48;
	s_driverinfo.up.width = 64;
	s_driverinfo.up.height = 64;
	s_driverinfo.up.focuspic = DRIVERINFO_ARROWS_UP;

	s_driverinfo.down.generic.type = MTYPE_BITMAP;
	s_driverinfo.down.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS | QMF_MOUSEONLY;
	s_driverinfo.down.generic.callback = DriverInfo_Event;
	s_driverinfo.down.generic.id = ID_SCROLL_DOWN;
	s_driverinfo.down.generic.x = 512 + 48 + 48;
	s_driverinfo.down.generic.y = 240 + 48;
	s_driverinfo.down.width = 64;
	s_driverinfo.down.height = 64;
	s_driverinfo.down.focuspic = DRIVERINFO_ARROWS_DOWN;

	s_driverinfo.back.generic.type = MTYPE_BITMAP;
	s_driverinfo.back.generic.name = DRIVERINFO_BACK0;
	s_driverinfo.back.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
	s_driverinfo.back.generic.callback = DriverInfo_Event;
	s_driverinfo.back.generic.id = ID_DRIVERINFOBACK;
	s_driverinfo.back.generic.x = 0;
	s_driverinfo.back.generic.y = 480 - 64;
	s_driverinfo.back.width = 128;
	s_driverinfo.back.height = 64;
	s_driverinfo.back.focuspic = DRIVERINFO_BACK1;

	// TTimo: overflow with particularly long GL extensions (such as the gf3)
	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=399
	// NOTE: could have pushed the size of stringbuff, but the list is already out of the screen
	// (no matter what your resolution)
	Q_strncpyz( s_driverinfo.stringbuff, uis.glconfig.extensions_string, 4096 );

	// build null terminated extension strings
	eptr = s_driverinfo.stringbuff;
	while ( s_driverinfo.numstrings < 160 && *eptr ) {
		while ( *eptr == ' ' )
			*eptr++ = '\0';

		// track start of valid string
		if ( *eptr && *eptr != ' ' )
			s_driverinfo.strings[s_driverinfo.numstrings++] = eptr;

		while ( *eptr && *eptr != ' ' )
			eptr++;
	}

	// safety length strings for display
	for ( i = 0; i < s_driverinfo.numstrings; i++ ) {
		len = strlen( s_driverinfo.strings[i] );
		if ( len > 128 ) {
			s_driverinfo.strings[i][len - 1] = '>';
			s_driverinfo.strings[i][len] = '\0';
		}
	}

	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.banner );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.framel );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.framer );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.arrows );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.up );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.down );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.back );

	UI_PushMenu( &s_driverinfo.menu );
}

/*
=======================================================================

GRAPHICS OPTIONS MENU

=======================================================================
*/

#define GRAPHICSOPTIONS_FRAMEL "menu/art_blueish/frame2_l"
#define GRAPHICSOPTIONS_FRAMER "menu/art_blueish/frame1_r"
#define GRAPHICSOPTIONS_BACK0 "menu/art_blueish/back_0"
#define GRAPHICSOPTIONS_BACK1 "menu/art_blueish/back_1"
#define GRAPHICSOPTIONS_ACCEPT0 "menu/art_blueish/accept_0"
#define GRAPHICSOPTIONS_ACCEPT1 "menu/art_blueish/accept_1"

#define ID_BACK2 101
#define ID_MODE 102
#define ID_DRIVERINFO 103
#define ID_GRAPHICS 104
#define ID_DISPLAY 105
#define ID_SOUND 106
#define ID_NETWORK 107
#define ID_RATIO 108

typedef struct {
	menuframework_s menu;

	menutext_s banner;
	menubitmap_s framel;
	menubitmap_s framer;

	menutext_s graphics;
	menutext_s display;
	menutext_s sound;
	menutext_s network;

	menulist_s renderer;
	menulist_s desktop;
	menulist_s ratio;
	menulist_s mode;
	menulist_s fs;
	menulist_s fbo;
	menulist_s flares;
	menulist_s bloom;
	menulist_s dynamiclights;
	menulist_s drawfps;
	menulist_s shadows;
	menuslider_s tq;
	menulist_s aniso;
	menulist_s anti;
	menulist_s noborder;
	menutext_s driverinfo;

	menubitmap_s apply;
	menubitmap_s back;
} graphicsoptions_t;

typedef struct
{
	int renderer;
	qboolean desktop;
	int mode;
	qboolean fullscreen;
	qboolean fbo;
	qboolean flares;
	qboolean bloom;
	qboolean dynamiclights;
	qboolean drawfps;
	int shadows;
	int tq;
	int aniso;
	int anti;
	qboolean noborder;
} InitialVideoOptions_s;

static InitialVideoOptions_s s_ivo;
static graphicsoptions_t s_graphicsoptions;

static const char *builtinResolutions[] =
    {
        "320x240",
        "400x300",
        "512x384",
        "640x480",
        "800x600",
        "960x720",
        "1024x768",
        "1152x864",
        "1280x1024",
        "1600x1200",
        "2048x1536",
        "856x480",
        NULL };

static const char *knownRatios[][2] =
    {
        { "1.25:1", "5:4" },
        { "1.33:1", "4:3" },
        { "1.50:1", "3:2" },
        { "1.56:1", "14:9" },
        { "1.60:1", "16:10" },
        { "1.67:1", "5:3" },
        { "1.78:1", "16:9" },
        { "2.37:1", "21:9" },
        { NULL, NULL } };

#define MAX_RESOLUTIONS 32

static const char *ratios[MAX_RESOLUTIONS];
static char ratioBuf[MAX_RESOLUTIONS][8];
static int ratioToRes[MAX_RESOLUTIONS];
static int resToRatio[MAX_RESOLUTIONS];

static char resbuf[MAX_STRING_CHARS];
static const char *detectedResolutions[MAX_RESOLUTIONS];

static const char **resolutions = builtinResolutions;
static qboolean resolutionsDetected = qfalse;

/*
=================
GraphicsOptions_FindBuiltinResolution
=================
*/
static int GraphicsOptions_FindBuiltinResolution( int mode ) {
	int i;

	if ( !resolutionsDetected )
		return mode;

	if ( mode < 0 )
		return -1;

	for ( i = 0; builtinResolutions[i]; i++ ) {
		if ( !Q_stricmp( builtinResolutions[i], detectedResolutions[mode] ) )
			return i;
	}

	return -1;
}

/*
=================
GraphicsOptions_FindDetectedResolution
=================
*/
static int GraphicsOptions_FindDetectedResolution( int mode ) {
	int i;

	if ( !resolutionsDetected )
		return mode;

	if ( mode < 0 )
		return -1;

	for ( i = 0; detectedResolutions[i]; i++ ) {
		if ( !Q_stricmp( builtinResolutions[mode], detectedResolutions[i] ) )
			return i;
	}

	return -1;
}

/*
=================
GraphicsOptions_GetAspectRatios
=================
*/
static void GraphicsOptions_GetAspectRatios( void ) {
	int i, r;

	// build ratio list from resolutions
	for ( r = 0; resolutions[r]; r++ ) {
		int w, h;
		char *x;
		char str[sizeof( ratioBuf[0] )];

		// calculate resolution's aspect ratio
		x = strchr( resolutions[r], 'x' ) + 1;

		Q_strncpyz( str, resolutions[r], x - resolutions[r] );
		w = atoi( str );
		h = atoi( x );
		Com_sprintf( str, sizeof( str ), "%.2f:1", (float)w / (float)h );

		// rename common ratios ("1.33:1" -> "4:3")
		for ( i = 0; knownRatios[i][0]; i++ ) {
			if ( !Q_stricmp( str, knownRatios[i][0] ) ) {
				Q_strncpyz( str, knownRatios[i][1], sizeof( str ) );
				break;
			}
		}

		// add ratio to list if it is new
		// establish res/ratio relationship
		for ( i = 0; ratioBuf[i][0]; i++ ) {
			if ( !Q_stricmp( str, ratioBuf[i] ) )
				break;
		}
		if ( !ratioBuf[i][0] ) {
			Q_strncpyz( ratioBuf[i], str, sizeof( ratioBuf[i] ) );
			ratioToRes[i] = r;
		}
		ratios[r] = ratioBuf[r];
		resToRatio[r] = i;
	}
	ratios[r] = NULL;
}

/*
=================
GraphicsOptions_GetInitialVideo
=================
*/
static void GraphicsOptions_GetInitialVideo( void ) {
	s_ivo.renderer = s_graphicsoptions.renderer.curvalue;
	s_ivo.desktop = s_graphicsoptions.desktop.curvalue;
	s_ivo.mode = s_graphicsoptions.mode.curvalue;
	s_ivo.fullscreen = s_graphicsoptions.fs.curvalue;
	s_ivo.fbo = s_graphicsoptions.fbo.curvalue;
	s_ivo.flares = s_graphicsoptions.flares.curvalue;
	s_ivo.bloom = s_graphicsoptions.bloom.curvalue;
	s_ivo.dynamiclights = s_graphicsoptions.dynamiclights.curvalue;
	s_ivo.drawfps = s_graphicsoptions.drawfps.curvalue;
	s_ivo.shadows = s_graphicsoptions.shadows.curvalue;
	s_ivo.tq = s_graphicsoptions.tq.curvalue;
	s_ivo.aniso = s_graphicsoptions.aniso.curvalue;
	s_ivo.anti = s_graphicsoptions.anti.curvalue;
	s_ivo.noborder = s_graphicsoptions.noborder.curvalue;
}

/*
=================
GraphicsOptions_GetResolutions
=================
*/
static void GraphicsOptions_GetResolutions( void ) {
	Q_strncpyz( resbuf, UI_Cvar_VariableString( "r_availableModes" ), sizeof( resbuf ) );
	if ( *resbuf ) {
		char *s = resbuf;
		unsigned int i = 0;
		while ( s && i < sizeof( detectedResolutions ) / sizeof( detectedResolutions[0] ) - 1 ) {
			detectedResolutions[i++] = s;
			s = strchr( s, ' ' );
			if ( s )
				*s++ = '\0';
		}
		detectedResolutions[i] = NULL;

		if ( i > 0 ) {
			resolutions = detectedResolutions;
			resolutionsDetected = qtrue;
		}
	}
}

/*
=================
GraphicsOptions_UpdateMenuItems
=================
*/
static void GraphicsOptions_UpdateMenuItems( void ) {
	s_graphicsoptions.ratio.curvalue = resToRatio[s_graphicsoptions.mode.curvalue];

	if ( s_graphicsoptions.desktop.curvalue == 1 ) {
		s_graphicsoptions.ratio.generic.flags |= QMF_GRAYED;
		s_graphicsoptions.mode.generic.flags |= QMF_GRAYED;
	} else {
		s_graphicsoptions.ratio.generic.flags &= ~QMF_GRAYED;
		s_graphicsoptions.mode.generic.flags &= ~QMF_GRAYED;
	}

	if ( s_graphicsoptions.fbo.curvalue == 0 ) {
		s_graphicsoptions.bloom.generic.flags |= QMF_GRAYED;
		s_graphicsoptions.anti.generic.flags |= QMF_GRAYED;
	} else {
		s_graphicsoptions.bloom.generic.flags &= ~QMF_GRAYED;
		s_graphicsoptions.anti.generic.flags &= ~QMF_GRAYED;
	}

	s_graphicsoptions.apply.generic.flags |= QMF_HIDDEN | QMF_INACTIVE;

	if ( s_ivo.renderer != s_graphicsoptions.renderer.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.desktop != s_graphicsoptions.desktop.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.mode != s_graphicsoptions.mode.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.fullscreen != s_graphicsoptions.fs.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.fbo != s_graphicsoptions.fbo.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.flares != s_graphicsoptions.flares.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.bloom != s_graphicsoptions.bloom.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.dynamiclights != s_graphicsoptions.dynamiclights.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.drawfps != s_graphicsoptions.drawfps.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.shadows != s_graphicsoptions.shadows.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.tq != s_graphicsoptions.tq.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.aniso != s_graphicsoptions.aniso.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.anti != s_graphicsoptions.anti.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
	if ( s_ivo.noborder != s_graphicsoptions.noborder.curvalue ) {
		s_graphicsoptions.apply.generic.flags &= ~( QMF_HIDDEN | QMF_INACTIVE );
	}
}

/*
=================
GraphicsOptions_ApplyChanges
=================
*/
static void GraphicsOptions_ApplyChanges( void *unused, int notification ) {
	if ( notification != QM_ACTIVATED )
		return;

	trap_Cvar_SetValue( "r_picmip", 3 - s_graphicsoptions.tq.curvalue );
	trap_Cvar_Set( "r_modeFullscreen", "" );
	if ( s_graphicsoptions.desktop.curvalue == 1 ) {
		trap_Cvar_SetValue( "r_mode", -2 );
		trap_Cvar_Set( "r_modeFullscreen", "-2" );
	} else if ( resolutionsDetected ) {
		// search for builtin mode that matches the detected mode
		int mode;
		if ( s_graphicsoptions.mode.curvalue == -1 || s_graphicsoptions.mode.curvalue >= sizeof( detectedResolutions ) / sizeof( detectedResolutions[0] ) )
			s_graphicsoptions.mode.curvalue = 0;

		mode = GraphicsOptions_FindBuiltinResolution( s_graphicsoptions.mode.curvalue );
		if ( mode == -1 ) {
			char w[16], h[16];
			Q_strncpyz( w, detectedResolutions[s_graphicsoptions.mode.curvalue], sizeof( w ) );
			*strchr( w, 'x' ) = 0;
			Q_strncpyz( h,
			            strchr( detectedResolutions[s_graphicsoptions.mode.curvalue], 'x' ) + 1, sizeof( h ) );
			trap_Cvar_Set( "r_customwidth", w );
			trap_Cvar_Set( "r_customheight", h );
		}

		trap_Cvar_SetValue( "r_mode", mode );
	} else
		trap_Cvar_SetValue( "r_mode", s_graphicsoptions.mode.curvalue );

	if ( s_graphicsoptions.renderer.curvalue == 1 ) {
		trap_Cvar_Set( "cl_renderer", "vulkan" );
	} else {
		trap_Cvar_Set( "cl_renderer", "opengl" );
	}
	trap_Cvar_SetValue( "r_fullscreen", s_graphicsoptions.fs.curvalue );
	trap_Cvar_SetValue( "r_colorbits", 0 );
	trap_Cvar_SetValue( "r_depthbits", 0 );
	trap_Cvar_SetValue( "r_stencilbits", 0 );
	trap_Cvar_SetValue( "r_fbo", s_graphicsoptions.fbo.curvalue );
	trap_Cvar_SetValue( "r_flares", s_graphicsoptions.flares.curvalue );
	trap_Cvar_SetValue( "r_bloom", s_graphicsoptions.bloom.curvalue );
	trap_Cvar_SetValue( "r_dynamiclight", s_graphicsoptions.dynamiclights.curvalue );
	trap_Cvar_SetValue( "cg_drawFPS", s_graphicsoptions.drawfps.curvalue );
	trap_Cvar_SetValue( "r_ext_multisample", s_graphicsoptions.anti.curvalue * 2 );
	trap_Cvar_SetValue( "r_noborder", s_graphicsoptions.noborder.curvalue );

	//r_ext_texture_filter_anisotropic is special
	if ( s_graphicsoptions.aniso.curvalue ) {
		trap_Cvar_SetValue( "r_ext_max_anisotropy", s_graphicsoptions.aniso.curvalue * 2 );
		trap_Cvar_SetValue( "r_ext_texture_filter_anisotropic", qtrue );
	} else
		trap_Cvar_SetValue( "r_ext_texture_filter_anisotropic", qfalse );

	trap_Cvar_SetValue( "com_hunkmegs", 256 );

	if ( s_graphicsoptions.shadows.curvalue == 4 ) {
		trap_Cvar_SetValue( "cg_shadows", 4 );
	} else if ( s_graphicsoptions.shadows.curvalue == 3 ) {
		trap_Cvar_SetValue( "cg_shadows", 3 );
	} else if ( s_graphicsoptions.shadows.curvalue == 2 ) {
		trap_Cvar_SetValue( "cg_shadows", 2 );
		trap_Cvar_SetValue( "r_stencilbits", 8 );
	} else if ( s_graphicsoptions.shadows.curvalue == 1 ) {
		trap_Cvar_SetValue( "cg_shadows", 1 );
	} else {
		trap_Cvar_SetValue( "cg_shadows", 0 );
	}

	trap_Cmd_ExecuteText( EXEC_APPEND, "vid_restart\n" );
}

/*
=================
GraphicsOptions_Event
=================
*/
static void GraphicsOptions_Event( void *ptr, int event ) {

	if ( event != QM_ACTIVATED ) {
		return;
	}

	switch ( ( (menucommon_s *)ptr )->id ) {
		case ID_RATIO:
			s_graphicsoptions.mode.curvalue = ratioToRes[s_graphicsoptions.ratio.curvalue];
			// fall through to apply mode constraints
		case ID_MODE:
			// clamp 3dfx video modes
			s_graphicsoptions.ratio.curvalue = resToRatio[s_graphicsoptions.mode.curvalue];
			break;

		case ID_DRIVERINFO:
			UI_DriverInfo_Menu();
			break;

		case ID_BACK2:
			UI_PopMenu();
			break;

		case ID_GRAPHICS:
			break;

		case ID_DISPLAY:
			UI_PopMenu();
			UI_DisplayOptionsMenu();
			break;

		case ID_SOUND:
			UI_PopMenu();
			UI_SoundOptionsMenu();
			break;

		case ID_NETWORK:
			UI_PopMenu();
			UI_NetworkOptionsMenu();
			break;
	}
}

/*
================
GraphicsOptions_TQEvent
================
*/
static void GraphicsOptions_TQEvent( void *ptr, int event ) {
	if ( event != QM_ACTIVATED ) {
		return;
	}
	s_graphicsoptions.tq.curvalue = (int)( s_graphicsoptions.tq.curvalue + 0.5 );
}

/*
================
GraphicsOptions_MenuDraw
================
*/
static void GraphicsOptions_MenuDraw( void ) {
	//APSFIX - rework this
	GraphicsOptions_UpdateMenuItems();

	Menu_Draw( &s_graphicsoptions.menu );
}

/*
=================
GraphicsOptions_SetMenuItems
=================
*/
static void GraphicsOptions_SetMenuItems( void ) {
	char renderer[MAX_STRING_CHARS];
	char str[MAX_STRING_CHARS];

	trap_Cvar_VariableStringBuffer( "cl_renderer", renderer, sizeof( renderer ) );

	if ( !Q_stricmp( renderer, "vulkan" ) ) {
		s_graphicsoptions.renderer.curvalue = 1;
	} else {
		s_graphicsoptions.renderer.curvalue = 0;
	}

	s_graphicsoptions.mode.curvalue =
	    GraphicsOptions_FindDetectedResolution( trap_Cvar_VariableValue( "r_mode" ) );

	if ( s_graphicsoptions.mode.curvalue < 0 ) {
		if ( resolutionsDetected ) {
			int i;
			char buf[MAX_STRING_CHARS];
			trap_Cvar_VariableStringBuffer( "r_customwidth", buf, sizeof( buf ) - 2 );
			buf[strlen( buf ) + 1] = 0;
			buf[strlen( buf )] = 'x';
			trap_Cvar_VariableStringBuffer( "r_customheight", buf + strlen( buf ), sizeof( buf ) - strlen( buf ) );

			for ( i = 0; detectedResolutions[i]; ++i ) {
				if ( !Q_stricmp( buf, detectedResolutions[i] ) ) {
					s_graphicsoptions.mode.curvalue = i;
					break;
				}
			}
			if ( s_graphicsoptions.mode.curvalue < 0 )
				s_graphicsoptions.mode.curvalue = 0;
		} else {
			s_graphicsoptions.mode.curvalue = 3;
		}
	}
	s_graphicsoptions.fs.curvalue = trap_Cvar_VariableValue( "r_fullscreen" );

	if ( trap_Cvar_VariableValue( "cl_omegaEngine" ) == 1 ) {
		trap_Cvar_VariableStringBuffer( "r_modeFullscreen", str, sizeof( str ) );
	} else {
		memset( str, 0, sizeof( str ) );
	}

	if ( trap_Cvar_VariableValue( "r_mode" ) == -2 || strlen( str ) > 0 ) {
		s_graphicsoptions.desktop.curvalue = 1;
	} else {
		s_graphicsoptions.desktop.curvalue = 0;
	}
	s_graphicsoptions.fbo.curvalue = trap_Cvar_VariableValue( "r_fbo" );
	s_graphicsoptions.flares.curvalue = trap_Cvar_VariableValue( "r_flares" );
	s_graphicsoptions.bloom.curvalue = trap_Cvar_VariableValue( "r_bloom" );
	s_graphicsoptions.dynamiclights.curvalue = trap_Cvar_VariableValue( "r_dynamiclight" );
	s_graphicsoptions.drawfps.curvalue = trap_Cvar_VariableValue( "cg_drawFPS" );
	s_graphicsoptions.shadows.curvalue = trap_Cvar_VariableValue( "cg_shadows" );
	s_graphicsoptions.anti.curvalue = trap_Cvar_VariableValue( "r_ext_multisample" ) / 2;
	s_graphicsoptions.noborder.curvalue = trap_Cvar_VariableValue( "r_noborder" );
	if ( trap_Cvar_VariableValue( "r_ext_texture_filter_anisotropic" ) ) {
		s_graphicsoptions.aniso.curvalue = trap_Cvar_VariableValue( "r_ext_max_anisotropy" ) / 2;
	}
	s_graphicsoptions.tq.curvalue = 3 - trap_Cvar_VariableValue( "r_picmip" );
	if ( s_graphicsoptions.tq.curvalue < 0 ) {
		s_graphicsoptions.tq.curvalue = 0;
	} else if ( s_graphicsoptions.tq.curvalue > 3 ) {
		s_graphicsoptions.tq.curvalue = 3;
	}
}

/*
================
GraphicsOptions_MenuInit
================
*/
void GraphicsOptions_MenuInit( void ) {
	char renderer[MAX_STRING_CHARS];

	static const char *renderer_names[] =
	    {
	        "OpenGL",
	        "Vulkan",
	        NULL };

	static const char *shadows_names[] =
	    {
	        "Off",
	        "Blob",
	        "Stencil",
	        "Vertex",
	        "Circle",
	        NULL };

	static const char *aniso_names[] =
	    {
	        "Off",
	        "2x",
	        "4x",
	        "6x",
	        "8x",
	        "10x",
	        "12x",
	        "14x",
	        "16x",
	        NULL };

	static const char *anti_names[] =
	    {
	        "Off",
	        "2x",
	        "4x",
	        "6x",
	        "8x",
	        NULL };

	static const char *enabled_names[] =
	    {
	        "Off",
	        "On",
	        NULL };

	int y;

	// zero set all our globals
	memset( &s_graphicsoptions, 0, sizeof( graphicsoptions_t ) );

	GraphicsOptions_GetResolutions();
	GraphicsOptions_GetAspectRatios();

	GraphicsOptions_Cache();

	s_graphicsoptions.menu.wrapAround = qtrue;
	s_graphicsoptions.menu.fullscreen = qtrue;
	s_graphicsoptions.menu.draw = GraphicsOptions_MenuDraw;

	s_graphicsoptions.banner.generic.type = MTYPE_BTEXT;
	s_graphicsoptions.banner.generic.x = 320;
	s_graphicsoptions.banner.generic.y = 16;
	s_graphicsoptions.banner.string = "SYSTEM SETUP";
	s_graphicsoptions.banner.color = color_white;
	s_graphicsoptions.banner.style = UI_CENTER;

	s_graphicsoptions.framel.generic.type = MTYPE_BITMAP;
	s_graphicsoptions.framel.generic.name = GRAPHICSOPTIONS_FRAMEL;
	s_graphicsoptions.framel.generic.flags = QMF_INACTIVE;
	s_graphicsoptions.framel.generic.x = 0;
	s_graphicsoptions.framel.generic.y = 78;
	s_graphicsoptions.framel.width = 256;
	s_graphicsoptions.framel.height = 329;

	s_graphicsoptions.framer.generic.type = MTYPE_BITMAP;
	s_graphicsoptions.framer.generic.name = GRAPHICSOPTIONS_FRAMER;
	s_graphicsoptions.framer.generic.flags = QMF_INACTIVE;
	s_graphicsoptions.framer.generic.x = 376;
	s_graphicsoptions.framer.generic.y = 76;
	s_graphicsoptions.framer.width = 256;
	s_graphicsoptions.framer.height = 334;

	s_graphicsoptions.graphics.generic.type = MTYPE_PTEXT;
	s_graphicsoptions.graphics.generic.flags = QMF_RIGHT_JUSTIFY;
	s_graphicsoptions.graphics.generic.id = ID_GRAPHICS;
	s_graphicsoptions.graphics.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.graphics.generic.x = 216;
	s_graphicsoptions.graphics.generic.y = 240 - 2 * PROP_HEIGHT;
	s_graphicsoptions.graphics.string = "GRAPHICS";
	s_graphicsoptions.graphics.style = UI_RIGHT;
	s_graphicsoptions.graphics.color = color_red;

	s_graphicsoptions.display.generic.type = MTYPE_PTEXT;
	s_graphicsoptions.display.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS;
	s_graphicsoptions.display.generic.id = ID_DISPLAY;
	s_graphicsoptions.display.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.display.generic.x = 216;
	s_graphicsoptions.display.generic.y = 240 - PROP_HEIGHT;
	s_graphicsoptions.display.string = "DISPLAY";
	s_graphicsoptions.display.style = UI_RIGHT;
	s_graphicsoptions.display.color = color_red;

	s_graphicsoptions.sound.generic.type = MTYPE_PTEXT;
	s_graphicsoptions.sound.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS;
	s_graphicsoptions.sound.generic.id = ID_SOUND;
	s_graphicsoptions.sound.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.sound.generic.x = 216;
	s_graphicsoptions.sound.generic.y = 240;
	s_graphicsoptions.sound.string = "SOUND";
	s_graphicsoptions.sound.style = UI_RIGHT;
	s_graphicsoptions.sound.color = color_red;

	s_graphicsoptions.network.generic.type = MTYPE_PTEXT;
	s_graphicsoptions.network.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS;
	s_graphicsoptions.network.generic.id = ID_NETWORK;
	s_graphicsoptions.network.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.network.generic.x = 216;
	s_graphicsoptions.network.generic.y = 240 + PROP_HEIGHT;
	s_graphicsoptions.network.string = "NETWORK";
	s_graphicsoptions.network.style = UI_RIGHT;
	s_graphicsoptions.network.color = color_red;

	trap_Cvar_VariableStringBuffer( "cl_renderer", renderer, sizeof( renderer ) );

	y = 240 - 7 * ( BIGCHAR_HEIGHT + 2 );
	s_graphicsoptions.renderer.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.renderer.generic.name = "Renderer:";
	s_graphicsoptions.renderer.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.renderer.generic.x = 400;
	s_graphicsoptions.renderer.generic.y = y;
	s_graphicsoptions.renderer.itemnames = renderer_names;
	y += BIGCHAR_HEIGHT + 2;

	s_graphicsoptions.desktop.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.desktop.generic.name = "Native Resolution:";
	s_graphicsoptions.desktop.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.desktop.generic.x = 400;
	s_graphicsoptions.desktop.generic.y = y;
	s_graphicsoptions.desktop.itemnames = enabled_names;
	y += BIGCHAR_HEIGHT + 2;

	s_graphicsoptions.ratio.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.ratio.generic.name = "Aspect Ratio:";
	s_graphicsoptions.ratio.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.ratio.generic.x = 400;
	s_graphicsoptions.ratio.generic.y = y;
	s_graphicsoptions.ratio.itemnames = ratios;
	s_graphicsoptions.ratio.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.ratio.generic.id = ID_RATIO;
	y += BIGCHAR_HEIGHT + 2;

	// references/modifies "r_mode"
	s_graphicsoptions.mode.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.mode.generic.name = "Resolution:";
	s_graphicsoptions.mode.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.mode.generic.x = 400;
	s_graphicsoptions.mode.generic.y = y;
	s_graphicsoptions.mode.itemnames = resolutions;
	s_graphicsoptions.mode.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.mode.generic.id = ID_MODE;
	y += BIGCHAR_HEIGHT + 2;

	// references/modifies "r_fullscreen"
	s_graphicsoptions.fs.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.fs.generic.name = "Fullscreen:";
	s_graphicsoptions.fs.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.fs.generic.x = 400;
	s_graphicsoptions.fs.generic.y = y;
	s_graphicsoptions.fs.itemnames = enabled_names;
	y += BIGCHAR_HEIGHT + 2;

	// references/modifies "r_fbo"
	if ( ( trap_Cvar_VariableValue( "cl_omegaEngine" ) == 1 ) ) {
		s_graphicsoptions.fbo.generic.type = MTYPE_SPINCONTROL;
		s_graphicsoptions.fbo.generic.name = "FBO:";
		s_graphicsoptions.fbo.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
		s_graphicsoptions.fbo.generic.x = 400;
		s_graphicsoptions.fbo.generic.y = y;
		s_graphicsoptions.fbo.itemnames = enabled_names;
		y += BIGCHAR_HEIGHT + 2;
	}

	// references/modifies "r_flares"
	s_graphicsoptions.flares.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.flares.generic.name = "Flares:";
	s_graphicsoptions.flares.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.flares.generic.x = 400;
	s_graphicsoptions.flares.generic.y = y;
	s_graphicsoptions.flares.itemnames = enabled_names;
	y += BIGCHAR_HEIGHT + 2;

	// references/modifies "r_bloom"
	s_graphicsoptions.bloom.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.bloom.generic.name = "Bloom:";
	s_graphicsoptions.bloom.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.bloom.generic.x = 400;
	s_graphicsoptions.bloom.generic.y = y;
	s_graphicsoptions.bloom.itemnames = enabled_names;
	y += BIGCHAR_HEIGHT + 2;

	// references/modifies "r_dynamiclight"
	s_graphicsoptions.dynamiclights.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.dynamiclights.generic.name = "Dynamic Lights:";
	s_graphicsoptions.dynamiclights.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.dynamiclights.generic.x = 400;
	s_graphicsoptions.dynamiclights.generic.y = y;
	s_graphicsoptions.dynamiclights.itemnames = enabled_names;
	y += BIGCHAR_HEIGHT + 2;

	s_graphicsoptions.drawfps.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.drawfps.generic.name = "Draw FPS:";
	s_graphicsoptions.drawfps.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.drawfps.generic.x = 400;
	s_graphicsoptions.drawfps.generic.y = y;
	s_graphicsoptions.drawfps.itemnames = enabled_names;
	y += BIGCHAR_HEIGHT + 2;

	// references/modifies "cg_shadows"
	s_graphicsoptions.shadows.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.shadows.generic.name = "Shadows:";
	s_graphicsoptions.shadows.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.shadows.generic.x = 400;
	s_graphicsoptions.shadows.generic.y = y;
	s_graphicsoptions.shadows.itemnames = shadows_names;
	y += BIGCHAR_HEIGHT + 2;

	// references/modifies "r_picmip"
	s_graphicsoptions.tq.generic.type = MTYPE_SLIDER;
	s_graphicsoptions.tq.generic.name = "Texture Detail:";
	s_graphicsoptions.tq.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.tq.generic.x = 400;
	s_graphicsoptions.tq.generic.y = y;
	s_graphicsoptions.tq.minvalue = 0;
	s_graphicsoptions.tq.maxvalue = 3;
	s_graphicsoptions.tq.generic.callback = GraphicsOptions_TQEvent;
	y += BIGCHAR_HEIGHT + 2;

	// references/modifies "r_ext_max_anisotropy"
	s_graphicsoptions.aniso.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.aniso.generic.name = "Anisotropy:";
	s_graphicsoptions.aniso.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.aniso.generic.x = 400;
	s_graphicsoptions.aniso.generic.y = y;
	s_graphicsoptions.aniso.itemnames = aniso_names;
	y += 2 + BIGCHAR_HEIGHT;

	// references/modifies "r_ext_multisample"
	s_graphicsoptions.anti.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.anti.generic.name = "Anti-Aliasing:";
	s_graphicsoptions.anti.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.anti.generic.x = 400;
	s_graphicsoptions.anti.generic.y = y;
	s_graphicsoptions.anti.itemnames = anti_names;
	y += 2 + BIGCHAR_HEIGHT;

	// references/modifies "r_noborder"
	s_graphicsoptions.noborder.generic.type = MTYPE_SPINCONTROL;
	s_graphicsoptions.noborder.generic.name = "Borderless Window:";
	s_graphicsoptions.noborder.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
	s_graphicsoptions.noborder.generic.x = 400;
	s_graphicsoptions.noborder.generic.y = y;
	s_graphicsoptions.noborder.itemnames = enabled_names;
	y += 3 * BIGCHAR_HEIGHT;

	s_graphicsoptions.driverinfo.generic.type = MTYPE_PTEXT;
	s_graphicsoptions.driverinfo.generic.flags = QMF_CENTER_JUSTIFY | QMF_PULSEIFFOCUS;
	s_graphicsoptions.driverinfo.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.driverinfo.generic.id = ID_DRIVERINFO;
	s_graphicsoptions.driverinfo.generic.x = 320;
	s_graphicsoptions.driverinfo.generic.y = 396;
	s_graphicsoptions.driverinfo.string = "Driver Info";
	s_graphicsoptions.driverinfo.style = UI_CENTER | UI_SMALLFONT;
	s_graphicsoptions.driverinfo.color = color_red;
	y += BIGCHAR_HEIGHT + 2;

	s_graphicsoptions.back.generic.type = MTYPE_BITMAP;
	s_graphicsoptions.back.generic.name = GRAPHICSOPTIONS_BACK0;
	s_graphicsoptions.back.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
	s_graphicsoptions.back.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.back.generic.id = ID_BACK2;
	s_graphicsoptions.back.generic.x = 0;
	s_graphicsoptions.back.generic.y = 480 - 64;
	s_graphicsoptions.back.width = 128;
	s_graphicsoptions.back.height = 64;
	s_graphicsoptions.back.focuspic = GRAPHICSOPTIONS_BACK1;

	s_graphicsoptions.apply.generic.type = MTYPE_BITMAP;
	s_graphicsoptions.apply.generic.name = GRAPHICSOPTIONS_ACCEPT0;
	s_graphicsoptions.apply.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS | QMF_HIDDEN | QMF_INACTIVE;
	s_graphicsoptions.apply.generic.callback = GraphicsOptions_ApplyChanges;
	s_graphicsoptions.apply.generic.x = 640;
	s_graphicsoptions.apply.generic.y = 480 - 64;
	s_graphicsoptions.apply.width = 128;
	s_graphicsoptions.apply.height = 64;
	s_graphicsoptions.apply.focuspic = GRAPHICSOPTIONS_ACCEPT1;

	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.banner );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.framel );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.framer );

	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.graphics );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.display );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.sound );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.network );

	if ( ( trap_Cvar_VariableValue( "cl_omegaEngine" ) == 1 ) && renderer[0] ) {
		Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.renderer );
	}
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.desktop );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.ratio );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.mode );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.fs );
	if ( trap_Cvar_VariableValue( "cl_omegaEngine" ) == 1 ) {
		Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.fbo );
	}
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.flares );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.bloom );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.dynamiclights );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.drawfps );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.shadows );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.tq );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.aniso );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.anti );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.driverinfo );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.back );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.apply );
	Menu_AddItem( &s_graphicsoptions.menu, (void *)&s_graphicsoptions.noborder );

	GraphicsOptions_SetMenuItems();
	GraphicsOptions_GetInitialVideo();
}

/*
=================
GraphicsOptions_Cache
=================
*/
void GraphicsOptions_Cache( void ) {
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_FRAMEL );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_FRAMER );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_BACK0 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_BACK1 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_ACCEPT0 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_ACCEPT1 );
}

/*
=================
UI_GraphicsOptionsMenu
=================
*/
void UI_GraphicsOptionsMenu( void ) {
	GraphicsOptions_MenuInit();
	UI_PushMenu( &s_graphicsoptions.menu );
	Menu_SetCursorToItem( &s_graphicsoptions.menu, &s_graphicsoptions.graphics );
}
