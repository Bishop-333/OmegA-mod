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

NETWORK OPTIONS MENU

=======================================================================
*/

#include "ui_local.h"


#define ART_FRAMEL			"menu/art_blueish/frame2_l"
#define ART_FRAMER			"menu/art_blueish/frame1_r"
#define ART_BACK0			"menu/art_blueish/back_0"
#define ART_BACK1			"menu/art_blueish/back_1"

#define ID_GRAPHICS			10
#define ID_DISPLAY			11
#define ID_SOUND			12
#define ID_NETWORK			13
#define ID_RATE				14
#define ID_ALLOWDOWNLOAD		15
#define ID_FORWARDER			16
#define ID_BACK				17

#define MAX_ADDRLENGTH	30


const char *rate_items[] = {
	"<= 28.8K",
	"33.6K",
	"56K",
	"ISDN",
	"LAN/Cable/xDSL",
	NULL
};

typedef struct {
	menuframework_s	menu;

	menutext_s		banner;
	menubitmap_s	framel;
	menubitmap_s	framer;

	menutext_s		graphics;
	menutext_s		display;
	menutext_s		sound;
	menutext_s		network;

	menulist_s		rate;
	menuradiobutton_s	allowdownload;
	menuradiobutton_s	forwarder;
	menufield_s		address;

	menubitmap_s	back;
} networkOptionsInfo_t;

static networkOptionsInfo_t	networkOptionsInfo;


/*
=================
Network_DrawAddress
=================
*/
static void Network_DrawAddress( void *self ) {
	menufield_s		*f;
	qboolean		focus;
	qboolean		forwarder;
	int				style;
	char			*txt;
	char			c;
	float			*color;
	int				n;
	int				basex, x, y;
	char			address[32];

	f = (menufield_s*)self;
	basex = f->generic.x;
	y = f->generic.y;
	focus = (f->generic.parent->cursor == f->generic.menuPosition);
	forwarder = (networkOptionsInfo.forwarder.curvalue == 1);

	style = UI_LEFT|UI_SMALLFONT;
	if ( forwarder ) {
		color = text_color_normal;
		if( focus ) {
			style |= UI_PULSE;
			color = text_color_highlight;
		}
	} else {
		color = text_color_disabled;
	}

	// draw the actual address
	basex += 48;
	y += PROP_HEIGHT;
	txt = f->field.buffer;
	x = basex;
	if ( forwarder ) {
		while ( (c = *txt) != 30 ) {
			UI_DrawChar( x, y, c, style, color );
			txt++;
			x += SMALLCHAR_WIDTH;
			trap_Cvar_Set( "fwd_addr", networkOptionsInfo.address.field.buffer );
		}
	}

	UI_DrawString( basex - 8 - SMALLCHAR_WIDTH, y, f->generic.name, UI_RIGHT|UI_SMALLFONT, color );

	// draw cursor if we have focus
	if( focus && forwarder ) {
		if ( trap_Key_GetOverstrikeMode() ) {
			c = 11;
		} else {
			c = 10;
		}

		style &= ~UI_PULSE;
		style |= UI_BLINK;

		UI_DrawChar( basex + f->field.cursor * SMALLCHAR_WIDTH, y, c, style, color );
	}
}


/*
=================
UI_NetworkOptionsMenu_Event
=================
*/
static void UI_NetworkOptionsMenu_Event( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_GRAPHICS:
		UI_PopMenu();
		UI_GraphicsOptionsMenu();
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
		break;

	case ID_RATE:
		if( networkOptionsInfo.rate.curvalue == 0 ) {
			trap_Cvar_SetValue( "rate", 2500 );
		}
		else if( networkOptionsInfo.rate.curvalue == 1 ) {
			trap_Cvar_SetValue( "rate", 3000 );
		}
		else if( networkOptionsInfo.rate.curvalue == 2 ) {
			trap_Cvar_SetValue( "rate", 4000 );
		}
		else if( networkOptionsInfo.rate.curvalue == 3 ) {
			trap_Cvar_SetValue( "rate", 5000 );
		}
		else if( networkOptionsInfo.rate.curvalue == 4 ) {
			trap_Cvar_SetValue( "rate", 25000 );
		}
		break;

	case ID_ALLOWDOWNLOAD:
		trap_Cvar_SetValue( "cl_allowDownload", networkOptionsInfo.allowdownload.curvalue );
		trap_Cvar_SetValue( "cl_mapAutoDownload", networkOptionsInfo.allowdownload.curvalue );
		trap_Cvar_SetValue( "sv_allowDownload", networkOptionsInfo.allowdownload.curvalue );
		break;

	case ID_FORWARDER:
		trap_Cvar_SetValue( "fwd_use", networkOptionsInfo.forwarder.curvalue );
		break;

	case ID_BACK:
		UI_PopMenu();
		break;
	}
}


/*
===============
UI_NetworkOptionsMenu_Init
===============
*/
static void UI_NetworkOptionsMenu_Init( void ) {
	int		y;
	int		rate;

	memset( &networkOptionsInfo, 0, sizeof(networkOptionsInfo) );

	UI_NetworkOptionsMenu_Cache();
	networkOptionsInfo.menu.wrapAround = qtrue;
	networkOptionsInfo.menu.fullscreen = qtrue;

	networkOptionsInfo.banner.generic.type		= MTYPE_BTEXT;
	networkOptionsInfo.banner.generic.flags		= QMF_CENTER_JUSTIFY;
	networkOptionsInfo.banner.generic.x			= 320;
	networkOptionsInfo.banner.generic.y			= 16;
	networkOptionsInfo.banner.string			= "SYSTEM SETUP";
	networkOptionsInfo.banner.color				= color_white;
	networkOptionsInfo.banner.style				= UI_CENTER;

	networkOptionsInfo.framel.generic.type		= MTYPE_BITMAP;
	networkOptionsInfo.framel.generic.name		= ART_FRAMEL;
	networkOptionsInfo.framel.generic.flags		= QMF_INACTIVE;
	networkOptionsInfo.framel.generic.x			= 0;  
	networkOptionsInfo.framel.generic.y			= 78;
	networkOptionsInfo.framel.width				= 256;
	networkOptionsInfo.framel.height			= 329;

	networkOptionsInfo.framer.generic.type		= MTYPE_BITMAP;
	networkOptionsInfo.framer.generic.name		= ART_FRAMER;
	networkOptionsInfo.framer.generic.flags		= QMF_INACTIVE;
	networkOptionsInfo.framer.generic.x			= 376;
	networkOptionsInfo.framer.generic.y			= 76;
	networkOptionsInfo.framer.width				= 256;
	networkOptionsInfo.framer.height			= 334;

	networkOptionsInfo.graphics.generic.type		= MTYPE_PTEXT;
	networkOptionsInfo.graphics.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	networkOptionsInfo.graphics.generic.id			= ID_GRAPHICS;
	networkOptionsInfo.graphics.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.graphics.generic.x			= 216;
	networkOptionsInfo.graphics.generic.y			= 240 - 2 * PROP_HEIGHT;
	networkOptionsInfo.graphics.string				= "GRAPHICS";
	networkOptionsInfo.graphics.style				= UI_RIGHT;
	networkOptionsInfo.graphics.color				= color_red;

	networkOptionsInfo.display.generic.type			= MTYPE_PTEXT;
	networkOptionsInfo.display.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	networkOptionsInfo.display.generic.id			= ID_DISPLAY;
	networkOptionsInfo.display.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.display.generic.x			= 216;
	networkOptionsInfo.display.generic.y			= 240 - PROP_HEIGHT;
	networkOptionsInfo.display.string				= "DISPLAY";
	networkOptionsInfo.display.style				= UI_RIGHT;
	networkOptionsInfo.display.color				= color_red;

	networkOptionsInfo.sound.generic.type			= MTYPE_PTEXT;
	networkOptionsInfo.sound.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	networkOptionsInfo.sound.generic.id				= ID_SOUND;
	networkOptionsInfo.sound.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.sound.generic.x				= 216;
	networkOptionsInfo.sound.generic.y				= 240;
	networkOptionsInfo.sound.string					= "SOUND";
	networkOptionsInfo.sound.style					= UI_RIGHT;
	networkOptionsInfo.sound.color					= color_red;

	networkOptionsInfo.network.generic.type			= MTYPE_PTEXT;
	networkOptionsInfo.network.generic.flags		= QMF_RIGHT_JUSTIFY;
	networkOptionsInfo.network.generic.id			= ID_NETWORK;
	networkOptionsInfo.network.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.network.generic.x			= 216;
	networkOptionsInfo.network.generic.y			= 240 + PROP_HEIGHT;
	networkOptionsInfo.network.string				= "NETWORK";
	networkOptionsInfo.network.style				= UI_RIGHT;
	networkOptionsInfo.network.color				= color_red;

	y = 240 - 1 * (BIGCHAR_HEIGHT+2);
	networkOptionsInfo.rate.generic.type		= MTYPE_SPINCONTROL;
	networkOptionsInfo.rate.generic.name		= "Data Rate:";
	networkOptionsInfo.rate.generic.flags		= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	networkOptionsInfo.rate.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.rate.generic.id			= ID_RATE;
	networkOptionsInfo.rate.generic.x			= 400;
	networkOptionsInfo.rate.generic.y			= y;
	networkOptionsInfo.rate.itemnames			= rate_items;

	y += BIGCHAR_HEIGHT+2;
	networkOptionsInfo.allowdownload.generic.type		= MTYPE_RADIOBUTTON;
	networkOptionsInfo.allowdownload.generic.name		= "Auto Downloading:";
	networkOptionsInfo.allowdownload.generic.flags		= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	networkOptionsInfo.allowdownload.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.allowdownload.generic.id		= ID_ALLOWDOWNLOAD;
	networkOptionsInfo.allowdownload.generic.x		= 400;
	networkOptionsInfo.allowdownload.generic.y		= y;

	y += BIGCHAR_HEIGHT+2;
	networkOptionsInfo.forwarder.generic.type	= MTYPE_RADIOBUTTON;
	networkOptionsInfo.forwarder.generic.name	= "Forwarder:";
	networkOptionsInfo.forwarder.generic.flags	= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	networkOptionsInfo.forwarder.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.forwarder.generic.id		= ID_FORWARDER;
	networkOptionsInfo.forwarder.generic.x		= 400;
	networkOptionsInfo.forwarder.generic.y		= y;

	y += BIGCHAR_HEIGHT+2;
	networkOptionsInfo.address.generic.type		= MTYPE_FIELD;
	networkOptionsInfo.address.generic.name		= "Address:";
	networkOptionsInfo.address.generic.flags	= QMF_NODEFAULTINIT;
	networkOptionsInfo.address.generic.ownerdraw	= Network_DrawAddress;
	networkOptionsInfo.address.field.widthInChars	= MAX_ADDRLENGTH;
	networkOptionsInfo.address.field.maxchars	= MAX_ADDRLENGTH;
	networkOptionsInfo.address.generic.x		= 400 - 40;
	networkOptionsInfo.address.generic.y		= y - 27;
	networkOptionsInfo.address.generic.left		= 192 - 8;
	networkOptionsInfo.address.generic.top		= y - 8;
	networkOptionsInfo.address.generic.right	= 192 + 200;
	networkOptionsInfo.address.generic.bottom	= y + 2 * PROP_HEIGHT;

	networkOptionsInfo.back.generic.type		= MTYPE_BITMAP;
	networkOptionsInfo.back.generic.name		= ART_BACK0;
	networkOptionsInfo.back.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	networkOptionsInfo.back.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.back.generic.id			= ID_BACK;
	networkOptionsInfo.back.generic.x			= 0;
	networkOptionsInfo.back.generic.y			= 480-64;
	networkOptionsInfo.back.width				= 128;
	networkOptionsInfo.back.height				= 64;
	networkOptionsInfo.back.focuspic			= ART_BACK1;

	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.banner );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.framel );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.framer );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.graphics );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.display );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.sound );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.network );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rate );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.allowdownload );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.forwarder );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.address );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.back );

	rate = trap_Cvar_VariableValue( "rate" );
	if( rate <= 2500 ) {
		networkOptionsInfo.rate.curvalue = 0;
	}
	else if( rate <= 3000 ) {
		networkOptionsInfo.rate.curvalue = 1;
	}
	else if( rate <= 4000 ) {
		networkOptionsInfo.rate.curvalue = 2;
	}
	else if( rate <= 5000 ) {
		networkOptionsInfo.rate.curvalue = 3;
	}
	else {
		networkOptionsInfo.rate.curvalue = 4;
	}

	networkOptionsInfo.allowdownload.curvalue = trap_Cvar_VariableValue( "cl_allowDownload" ) != 0;
	networkOptionsInfo.forwarder.curvalue = trap_Cvar_VariableValue( "fwd_use" ) != 0;
	Q_strncpyz( networkOptionsInfo.address.field.buffer, UI_Cvar_VariableString("fwd_addr"), sizeof(networkOptionsInfo.address.field.buffer) );
}


/*
===============
UI_NetworkOptionsMenu_Cache
===============
*/
void UI_NetworkOptionsMenu_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_FRAMEL );
	trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
}


/*
===============
UI_NetworkOptionsMenu
===============
*/
void UI_NetworkOptionsMenu( void ) {
	UI_NetworkOptionsMenu_Init();
	UI_PushMenu( &networkOptionsInfo.menu );
	Menu_SetCursorToItem( &networkOptionsInfo.menu, &networkOptionsInfo.network );
}
