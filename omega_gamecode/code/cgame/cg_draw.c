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
// cg_draw.c -- draw all of the graphical elements during
// active (after loading) gameplay

#include "cg_local.h"

#ifdef MISSIONPACK
#include "../ui/ui_shared.h"

// used for scoreboard
extern displayContextDef_t cgDC;
menuDef_t *menuScoreboard = NULL;
#else
int drawTeamOverlayModificationCount = -1;
#endif

int sortedTeamPlayers[TEAM_MAXOVERLAY];
int	numSortedTeamPlayers;

char systemChat[256];
char teamChat1[256];
char teamChat2[256];

static int CG_DrawPickupItem( int y );

#ifdef MISSIONPACK

int CG_Text_Width(const char *text, float scale, int limit) {
  int count,len;
	float out;
	glyphInfo_t *glyph;
	float useScale;
// FIXME: see ui_main.c, same problem
//	const unsigned char *s = text;
	const char *s = text;
	fontInfo_t *font = &cgDC.Assets.textFont;
	if (scale <= cg_smallFont.value) {
		font = &cgDC.Assets.smallFont;
	} else if (scale > cg_bigFont.value) {
		font = &cgDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
  out = 0;
  if (text) {
    len = strlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		count = 0;
		while (s && *s && count < len) {
			if ( Q_IsColorString(s) ) {
				s += 2;
				continue;
			} else {
				glyph = &font->glyphs[(int)*s]; // TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
				out += glyph->xSkip;
				s++;
				count++;
			}
    }
  }
  return out * useScale;
}

int CG_Text_Height(const char *text, float scale, int limit) {
  int len, count;
	float max;
	glyphInfo_t *glyph;
	float useScale;
// TTimo: FIXME
//	const unsigned char *s = text;
	const char *s = text;
	fontInfo_t *font = &cgDC.Assets.textFont;
	if (scale <= cg_smallFont.value) {
		font = &cgDC.Assets.smallFont;
	} else if (scale > cg_bigFont.value) {
		font = &cgDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
  max = 0;
  if (text) {
    len = strlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		count = 0;
		while (s && *s && count < len) {
			if ( Q_IsColorString(s) ) {
				s += 2;
				continue;
			} else {
				glyph = &font->glyphs[(int)*s]; // TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
	      if (max < glyph->height) {
		      max = glyph->height;
			  }
				s++;
				count++;
			}
    }
  }
  return max * useScale;
}

void CG_Text_PaintChar(float x, float y, float width, float height, float scale, float s, float t, float s2, float t2, qhandle_t hShader) {
  float w, h;
  w = width * scale;
  h = height * scale;
  CG_AdjustFrom640( &x, &y, &w, &h );
  trap_R_DrawStretchPic( x, y, w, h, s, t, s2, t2, hShader );
}

void CG_Text_Paint(float x, float y, float scale, vec4_t color, const char *text, float adjust, int limit, int style) {
  int len, count;
	vec4_t newColor;
	glyphInfo_t *glyph;
	float useScale;
	fontInfo_t *font = &cgDC.Assets.textFont;
	if (scale <= cg_smallFont.value) {
		font = &cgDC.Assets.smallFont;
	} else if (scale > cg_bigFont.value) {
		font = &cgDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
  if (text) {
// TTimo: FIXME
//		const unsigned char *s = text;
		const char *s = text;
		trap_R_SetColor( color );
		memcpy(&newColor[0], &color[0], sizeof(vec4_t));
    len = strlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		count = 0;
		while (s && *s && count < len) {
			glyph = &font->glyphs[(int)*s]; // TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
      //int yadj = Assets.textFont.glyphs[text[i]].bottom + Assets.textFont.glyphs[text[i]].top;
      //float yadj = scale * (Assets.textFont.glyphs[text[i]].imageHeight - Assets.textFont.glyphs[text[i]].height);
			if ( Q_IsColorString( s ) ) {
				memcpy( newColor, g_color_table[ColorIndex(*(s+1))], sizeof( newColor ) );
				newColor[3] = color[3];
				trap_R_SetColor( newColor );
				s += 2;
				continue;
			} else {
				float yadj = useScale * glyph->top;
				if (style == ITEM_TEXTSTYLE_SHADOWED || style == ITEM_TEXTSTYLE_SHADOWEDMORE) {
					int ofs = style == ITEM_TEXTSTYLE_SHADOWED ? 1 : 2;
					colorBlack[3] = newColor[3];
					trap_R_SetColor( colorBlack );
					CG_Text_PaintChar(x + ofs, y - yadj + ofs, 
														glyph->imageWidth,
														glyph->imageHeight,
														useScale, 
														glyph->s,
														glyph->t,
														glyph->s2,
														glyph->t2,
														glyph->glyph);
					colorBlack[3] = 1.0;
					trap_R_SetColor( newColor );
				}
				CG_Text_PaintChar(x, y - yadj, 
													glyph->imageWidth,
													glyph->imageHeight,
													useScale, 
													glyph->s,
													glyph->t,
													glyph->s2,
													glyph->t2,
													glyph->glyph);
				// CG_DrawPic(x, y - yadj, scale * cgDC.Assets.textFont.glyphs[text[i]].imageWidth, scale * cgDC.Assets.textFont.glyphs[text[i]].imageHeight, cgDC.Assets.textFont.glyphs[text[i]].glyph);
				x += (glyph->xSkip * useScale) + adjust;
				s++;
				count++;
			}
		}
		trap_R_SetColor( NULL );
	}
}


#endif

/*
==============
CG_DrawField

Draws large numbers for status bar and powerups
==============
*/
#ifndef MISSIONPACK
static void CG_DrawField( float x, float y, int width, int value, float char_width, float char_height ) {
	char	num[16], *ptr;
	int		l;
	int		frame;

	if ( width < 1 ) {
		return;
	}

	// draw number string
	if ( width > 5 ) {
		width = 5;
	}

	switch ( width ) {
	case 1:
		value = value > 9 ? 9 : value;
		value = value < 0 ? 0 : value;
		break;
	case 2:
		value = value > 99 ? 99 : value;
		value = value < -9 ? -9 : value;
		break;
	case 3:
		value = value > 999 ? 999 : value;
		value = value < -99 ? -99 : value;
		break;
	case 4:
		value = value > 9999 ? 9999 : value;
		value = value < -999 ? -999 : value;
		break;
	}

	Com_sprintf (num, sizeof(num), "%i", value);
	l = strlen(num);
	if (l > width)
		l = width;
	x += char_width*(width - l);

	ptr = num;
	while (*ptr && l)
	{
		if (*ptr == '-')
			frame = STAT_MINUS;
		else
			frame = *ptr -'0';

		CG_DrawPic( x,y, char_width, char_height, cgs.media.numberShaders[frame] );
		x += char_width;
		ptr++;
		l--;
	}
}
#endif // MISSIONPACK

/*
================
CG_Draw3DModel

================
*/
void CG_Draw3DModel( float x, float y, float w, float h, qhandle_t model, qhandle_t skin, vec3_t origin, vec3_t angles ) {
	refdef_t		refdef;
	refEntity_t		ent;

	if ( !cg_draw3dIcons.integer || !cg_drawIcons.integer ) {
		return;
	}

	CG_AdjustFrom640( &x, &y, &w, &h );

	memset( &refdef, 0, sizeof( refdef ) );

	memset( &ent, 0, sizeof( ent ) );
	AnglesToAxis( angles, ent.axis );
	VectorCopy( origin, ent.origin );
	ent.hModel = model;
	ent.customSkin = skin;
	ent.renderfx = RF_NOSHADOW;		// no stencil shadows

	refdef.rdflags = RDF_NOWORLDMODEL;

	AxisClear( refdef.viewaxis );

	refdef.fov_x = 30;
	refdef.fov_y = 30;

	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;

	refdef.time = cg.time;

	trap_R_ClearScene();
	trap_R_AddRefEntityToScene( &ent );
	trap_R_RenderScene( &refdef );
}

/*
================
CG_Draw3DHead

================
*/
static void CG_Draw3DHead( float x, float y, float w, float h, qhandle_t model, qhandle_t skin, vec3_t origin, vec3_t angles, clientInfo_t *ci ) {
	refdef_t		refdef;
	refEntity_t		ent;

	if ( !cg_draw3dIcons.integer || !cg_drawIcons.integer ) {
		return;
	}

	CG_AdjustFrom640( &x, &y, &w, &h );

	memset( &refdef, 0, sizeof( refdef ) );

	memset( &ent, 0, sizeof( ent ) );
	AnglesToAxis( angles, ent.axis );
	VectorCopy( origin, ent.origin );
	ent.hModel = model;
	ent.customSkin = skin;
	ent.shaderRGBA[0] = ci->color2[0] * 255;
	ent.shaderRGBA[1] = ci->color2[1] * 255;
	ent.shaderRGBA[2] = ci->color2[2] * 255;
	ent.renderfx = RF_NOSHADOW;		// no stencil shadows

	refdef.rdflags = RDF_NOWORLDMODEL;

	AxisClear( refdef.viewaxis );

	refdef.fov_x = 30;
	refdef.fov_y = 30;

	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;

	refdef.time = cg.time;

	trap_R_ClearScene();
	trap_R_AddRefEntityToScene( &ent );
	trap_R_RenderScene( &refdef );
}

/*
================
CG_DrawHead

Used for both the status bar and the scoreboard
================
*/
void CG_DrawHead( float x, float y, float w, float h, int clientNum, vec3_t headAngles ) {
	clipHandle_t	cm;
	clientInfo_t	*ci;
	float			len;
	vec3_t			origin;
	vec3_t			mins, maxs;

	ci = &cgs.clientinfo[ clientNum ];

	if ( cg_draw3dIcons.integer ) {
		cm = ci->headModel;
		if ( !cm ) {
			return;
		}

		// offset the origin y and z to center the head
		trap_R_ModelBounds( cm, mins, maxs );

		origin[2] = -0.5 * ( mins[2] + maxs[2] );
		origin[1] = 0.5 * ( mins[1] + maxs[1] );

		// calculate distance so the head nearly fills the box
		// assume heads are taller than wide
		len = 0.7 * ( maxs[2] - mins[2] );		
		origin[0] = len / 0.268;	// len / tan( fov/2 )

		// allow per-model tweaking
		VectorAdd( origin, ci->headOffset, origin );

		CG_Draw3DHead( x, y, w, h, ci->headModel, ci->headSkin, origin, headAngles, ci );
	} else if ( cg_drawIcons.integer ) {
		CG_DrawPic( x, y, w, h, ci->modelIcon );
	}

	// if they are deferred, draw a cross out
	if ( ci->deferred ) {
		CG_DrawPic( x, y, w, h, cgs.media.deferShader );
	}
}

/*
================
CG_DrawFlagModel

Used for both the status bar and the scoreboard
================
*/
void CG_DrawFlagModel( float x, float y, float w, float h, int team, qboolean force2D ) {
	qhandle_t		cm;
	float			len;
	vec3_t			origin, angles;
	vec3_t			mins, maxs;
	qhandle_t		handle;

	if ( !force2D && cg_draw3dIcons.integer ) {

		VectorClear( angles );

		cm = cgs.media.redFlagModel;

		// offset the origin y and z to center the flag
		trap_R_ModelBounds( cm, mins, maxs );

		origin[2] = -0.5 * ( mins[2] + maxs[2] );
		origin[1] = 0.5 * ( mins[1] + maxs[1] );

		// calculate distance so the flag nearly fills the box
		// assume heads are taller than wide
		len = 0.55 * ( maxs[2] - mins[2] );		
		origin[0] = len / 0.268;	// len / tan( fov/2 )

		angles[YAW] = cg.time * 45 / 2048.0;;

		if( team == TEAM_RED ) {
			handle = cgs.media.redFlagModel;
			if(cgs.gametype == GT_DOUBLE_D){
				if(cgs.redflag == TEAM_BLUE)
					handle = cgs.media.blueFlagModel;
				if(cgs.redflag == TEAM_FREE)
					handle = cgs.media.neutralFlagModel;
				if(cgs.redflag == TEAM_NONE)
					handle = cgs.media.neutralFlagModel;
			}
		} else if( team == TEAM_BLUE ) {
			handle = cgs.media.blueFlagModel;
			if(cgs.gametype == GT_DOUBLE_D){
				if(cgs.redflag == TEAM_BLUE)
					handle = cgs.media.blueFlagModel;
				if(cgs.redflag == TEAM_FREE)
					handle = cgs.media.neutralFlagModel;
				if(cgs.redflag == TEAM_NONE)
					handle = cgs.media.neutralFlagModel;
			}
		} else if( team == TEAM_FREE ) {
			handle = cgs.media.neutralFlagModel;
		} else {
			return;
		}
		CG_Draw3DModel( x, y, w, h, handle, 0, origin, angles );
	} else if ( cg_drawIcons.integer ) {
		gitem_t *item;

		if( team == TEAM_RED ) {
			item = BG_FindItemForPowerup( PW_REDFLAG );
		} else if( team == TEAM_BLUE ) {
			item = BG_FindItemForPowerup( PW_BLUEFLAG );
		} else if( team == TEAM_FREE ) {
			item = BG_FindItemForPowerup( PW_NEUTRALFLAG );
		} else {
			return;
		}
		if (item) {
		  CG_DrawPic( x, y, w, h, cg_items[ ITEM_INDEX(item) ].icon );
		}
	}
}

/*
================
CG_DrawStatusBarHead

================
*/
#ifndef MISSIONPACK

static void CG_DrawStatusBarHead( float x ) {
	vec3_t		angles;
	float		size;
	float		frac;

	VectorClear( angles );

	if ( cg.time >= cg.headEndTime ) {
		// select a new head angle
		cg.headStartYaw = cg.headEndYaw;
		cg.headStartPitch = cg.headEndPitch;
		cg.headStartTime = cg.headEndTime;
		cg.headEndTime = cg.time + 100 + random() * 2000;

		cg.headEndYaw = 180 + 20 * cos( crandom()*M_PI );
		cg.headEndPitch = 5 * cos( crandom()*M_PI );
	}

	size = ICON_SIZE * 1.25;

	// if the server was frozen for a while we may have a bad head start time
	if ( cg.headStartTime > cg.time ) {
		cg.headStartTime = cg.time;
	}

	frac = ( cg.time - cg.headStartTime ) / (float)( cg.headEndTime - cg.headStartTime );
	frac = frac * frac * ( 3 - 2 * frac );
	angles[YAW] = cg.headStartYaw + ( cg.headEndYaw - cg.headStartYaw ) * frac;
	angles[PITCH] = cg.headStartPitch + ( cg.headEndPitch - cg.headStartPitch ) * frac;

	if ( cg_statusBarStyle.integer == 2 ) {
		return;
	} else {
		CG_DrawHead( x, 480 - size, size, size, 
				cg.snap->ps.clientNum, angles );
	}
}
#endif // MISSIONPACK

/*
================
CG_DrawStatusBarFlag

================
*/
#ifndef MISSIONPACK
static void CG_DrawStatusBarFlag( float x, int team ) {
	CG_DrawFlagModel( x - ICON_SIZE, 480 - ICON_SIZE * 1.1, ICON_SIZE * 1.1, ICON_SIZE * 1.1, team, qfalse );
}
#endif // MISSIONPACK

/*
================
CG_DrawTeamBackground

================
*/
void CG_DrawTeamBackground( int x, int y, int w, int h, float alpha, int team )
{
	vec4_t		hcolor;

	if ( !cg_drawTeamBackground.integer ) {
		return;
	}

	if ( team == TEAM_RED ) {
		hcolor[0] = 1;
		hcolor[1] = 0;
		hcolor[2] = 0;
		hcolor[3] = alpha;
	} else if ( team == TEAM_BLUE ) {
		hcolor[0] = 0;
		hcolor[1] = 0.25;
		hcolor[2] = 1;
		hcolor[3] = alpha;
	} else {
		hcolor[0] = 0;
		hcolor[1] = 0;
		hcolor[2] = 0;
		hcolor[3] = alpha;
	}
	trap_R_SetColor( hcolor );
	CG_DrawPic( x, y, w, h, cgs.media.teamStatusBar );
	trap_R_SetColor( NULL );
}

/*
================
CG_GetWeaponColors

================
 */

static vec4_t weaponColors[WP_NUM_WEAPONS] =
	{
	{ 1.0, 1.0, 1.0, 1.0 }, // WP_NONE
	{ 0.0, 0.8, 1.0, 1.0 }, // WP_GAUNTLET,
	{ 1.0, 1.0, 0.0, 1.0 }, // WP_MACHINEGUN,
	{ 1.0, 0.4, 0.0, 1.0 }, // WP_SHOTGUN,
	{ 0.0, 0.6, 0.0, 1.0 }, // WP_GRENADE_LAUNCHER,
	{ 1.0, 0.0, 0.0, 1.0 }, // WP_ROCKET_LAUNCHER,
	{ 1.0, 1.0, 0.6, 1.0 }, // WP_LIGHTNING,
	{ 0.0, 1.0, 0.0, 1.0 }, // WP_RAILGUN,
	{ 1.0, 0.0, 1.0, 1.0 }, // WP_PLASMAGUN,
	{ 0.0, 0.4, 1.0, 1.0 }, // WP_BFG,
	{ 0.4, 0.6, 0.0, 1.0 }, // WP_GRAPPLING_HOOK,
	{ 1.0, 0.6, 0.6, 1.0 }, // WP_NAILGUN,
	{ 1.0, 0.6, 0.4, 1.0 }, // WP_PROX_LAUNCHER,
	{ 0.8, 0.8, 0.8, 1.0 }, // WP_CHAINGUN,
	};

static float *CG_GetWeaponColor( int weapon ) {
	if ( weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ) {
		return weaponColors[0];
	}
	return weaponColors[weapon];
}

/*
================
CG_DrawStatusBar

================
*/
#ifndef MISSIONPACK
static void CG_DrawStatusBar( void ) {
	int			color;
	centity_t	*cent;
	playerState_t	*ps;
	int			value;
	vec4_t		hcolor;
	vec3_t		angles;
	vec3_t		origin;
        qhandle_t	handle;
	int weaponSelect = CG_GetWeaponSelect();
        
	static float colors[4][4] = { 
//		{ 0.2, 1.0, 0.2, 1.0 } , { 1.0, 0.2, 0.2, 1.0 }, {0.5, 0.5, 0.5, 1} };
		{ 1.0f, 0.69f, 0.0f, 1.0f },    // normal
		{ 1.0f, 0.2f, 0.2f, 1.0f },     // low health
		{ 0.5f, 0.5f, 0.5f, 1.0f },     // weapon firing
		{ 1.0f, 1.0f, 1.0f, 1.0f } };   // health > 100

	if ( cg_drawStatus.integer == 0 ) {
		return;
	}

	// draw the team background
	if ( !(cg.snap->ps.pm_flags & PMF_FOLLOW) ) //If not following anybody:
		CG_DrawTeamBackground( 0, 420, 640, 60, 0.33f, cg.snap->ps.persistant[PERS_TEAM] );
	else //Sago: If we follow find the teamcolor of the guy we follow. It might not be our own team!
		CG_DrawTeamBackground( 0, 420, 640, 60, 0.33f, cgs.clientinfo[ cg.snap->ps.clientNum ].team );

	cent = &cg_entities[cg.snap->ps.clientNum];
	ps = &cg.snap->ps;

	VectorClear( angles );

	// draw any 3D icons first, so the changes back to 2D are minimized
	if (cent->currentState.weapon && cg_weapons[ cent->currentState.weapon ].ammoModel) {
		origin[0] = 70;
		origin[1] = 0;
		origin[2] = 0;
		angles[YAW] = 90 + 20 * sin(cg.time / 1000.0);
		CG_Draw3DModel(CHAR_WIDTH * 1.5 + TEXT_ICON_SPACE, 450, ICON_SIZE / 1.5, ICON_SIZE / 1.5,
				cg_weapons[ cent->currentState.weapon ].ammoModel, 0, origin, angles);
	}

	CG_DrawStatusBarHead( 289 );

	if( cg.predictedPlayerState.powerups[PW_REDFLAG] ) {
		CG_DrawStatusBarFlag( 470 + CHAR_WIDTH*1.5 + TEXT_ICON_SPACE + ICON_SIZE, TEAM_RED );
	} else if( cg.predictedPlayerState.powerups[PW_BLUEFLAG] ) {
		CG_DrawStatusBarFlag( 470 + CHAR_WIDTH*1.5 + TEXT_ICON_SPACE + ICON_SIZE, TEAM_BLUE );
	} else if( cg.predictedPlayerState.powerups[PW_NEUTRALFLAG] ) {
		CG_DrawStatusBarFlag( 470 + CHAR_WIDTH*1.5 + TEXT_ICON_SPACE + ICON_SIZE, TEAM_FREE );
	}

	if ( ps->stats[ STAT_HEALTH ] ) {
		origin[0] = 90;
		origin[1] = 0;
		origin[2] = -10;
		angles[YAW] = ( cg.time & 2047 ) * 360 / 2048.0;
		CG_Draw3DModel( 185 - CHAR_WIDTH * 1.75 - TEXT_ICON_SPACE, 429 - CHAR_HEIGHT / 3, ICON_SIZE * 1.25, ICON_SIZE * 1.25, cgs.media.smallCrossModel, 0, origin, angles );
	}

	if ( ps->stats[ STAT_ARMOR ] ) {
		origin[0] = 90;
		origin[1] = 0;
		origin[2] = -10;
		angles[YAW] = ( cg.time & 2047 ) * 360 / 2048.0;
		CG_Draw3DModel( 355 + CHAR_WIDTH*3 + TEXT_ICON_SPACE, 429, ICON_SIZE, ICON_SIZE,
					   cgs.media.armorModel, 0, origin, angles );
	}
        
        if( cgs.gametype == GT_HARVESTER ) {
		origin[0] = 90;
		origin[1] = 0;
		origin[2] = -10;
		angles[YAW] = ( cg.time & 2047 ) * 360 / 2048.0;
		if( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE ) {
			handle = cgs.media.redCubeModel;
		} else {
			handle = cgs.media.blueCubeModel;
		}
		CG_Draw3DModel( 470 + CHAR_WIDTH*3 + TEXT_ICON_SPACE, 432, ICON_SIZE, ICON_SIZE, handle, 0, origin, angles );
	}
        
        
	//
	// ammo
	//
	if ( cent->currentState.weapon ) {
		value = ps->ammo[weaponSelect];
		if ( value > -1 ) {
			if ( cg.predictedPlayerState.weaponstate == WEAPON_FIRING
				&& cg.predictedPlayerState.weaponTime > 100 ) {
				// draw as dark grey when reloading
				trap_R_SetColor( colors[2] );	// dark grey
			} else {
				trap_R_SetColor( CG_GetWeaponColor( weaponSelect ) );
			}
			
			if ( cg_statusBarStyle.integer == 2 ) {
				if ( value >= 100 ) {
					CG_DrawField (295, 452, 3, value, AMMO_CHAR_WIDTH, AMMO_CHAR_HEIGHT);
				} else if ( value >= 10 ) {
					CG_DrawField (287, 452, 3, value, AMMO_CHAR_WIDTH, AMMO_CHAR_HEIGHT);
				} else {
					CG_DrawField (279, 452, 3, value, AMMO_CHAR_WIDTH, AMMO_CHAR_HEIGHT);
				}
			} else {
				CG_DrawField (0, 452, 3, value, AMMO_CHAR_WIDTH, AMMO_CHAR_HEIGHT);
			}
			trap_R_SetColor( NULL );

			// draw a 2D icon for ammo
			if (!cg_draw3dIcons.integer && cg_drawIcons.integer) {
				qhandle_t	icon;

				icon = cg_weapons[ weaponSelect ].ammoIcon;
				if ( icon ) {
					if ( cg_statusBarStyle.integer == 2 ) {
						CG_DrawPic( 307, 422, ICON_SIZE / 2, ICON_SIZE / 2, icon );
					} else {
						CG_DrawPic( AMMO_CHAR_WIDTH * 3 + TEXT_ICON_SPACE, 452, ICON_SIZE / 2, ICON_SIZE / 2, icon );
					}
				}
			}
		}
	}

	//
	// health
	//
	value = ps->stats[STAT_HEALTH];
	if ( value > 100 ) {
		trap_R_SetColor( weaponColors[7] );		// green
	} else if (value > 25) {
		trap_R_SetColor( colors[3] );	// white
	} else if (value > 0) {
		color = (cg.time >> 8) & 1;	// flash
		trap_R_SetColor( colors[color] );
	} else {
		trap_R_SetColor( colors[1] );	// red
	}

	// stretch the health up when taking damage
	CG_DrawField ( 185, 429, 3, value, CHAR_WIDTH, CHAR_HEIGHT);
	CG_ColorForHealth( hcolor );
	trap_R_SetColor( hcolor );
	// if we didn't draw a 3D icon, draw a 2D icon for health
	if ( !cg_draw3dIcons.integer && cg_drawIcons.integer ) {
		CG_DrawPic( 185 - CHAR_WIDTH * 1.5 - TEXT_ICON_SPACE, 428, ICON_SIZE, ICON_SIZE, cgs.media.healthIcon );
	}


	//
	// armor
	//
	value = ps->stats[STAT_ARMOR];
	if (value > 100 ) {
		trap_R_SetColor( colors[0] );
		CG_DrawField (355, 429, 3, value, CHAR_WIDTH, CHAR_HEIGHT);
		trap_R_SetColor( NULL );
		// if we didn't draw a 3D icon, draw a 2D icon for armor
		if ( !cg_draw3dIcons.integer && cg_drawIcons.integer ) {
			CG_DrawPic( 355 + CHAR_WIDTH * 3 + TEXT_ICON_SPACE, 428, ICON_SIZE, ICON_SIZE, cgs.media.armorIcon );
		}
	} else if (value > 0 ) {
		trap_R_SetColor( colors[3] ); // white
		CG_DrawField(355, 429, 3, value, CHAR_WIDTH, CHAR_HEIGHT);
		trap_R_SetColor( NULL );
		// if we didn't draw a 3D icon, draw a 2D icon for armor
		if ( !cg_draw3dIcons.integer && cg_drawIcons.integer ) {
			CG_DrawPic( 355 + CHAR_WIDTH * 3 + TEXT_ICON_SPACE, 428, ICON_SIZE, ICON_SIZE, cgs.media.armorIcon );
		}

	}
        
        //Skulls!
        if(cgs.gametype == GT_HARVESTER)
        {
            value = ps->generic1;
            if (value > 0 ) {
                    trap_R_SetColor( colors[0] );
                    CG_DrawField (470, 432, 3, value, CHAR_WIDTH, CHAR_HEIGHT);
                    trap_R_SetColor( NULL );
                    // if we didn't draw a 3D icon, draw a 2D icon for skull
                    if ( !cg_draw3dIcons.integer && cg_drawIcons.integer ) {
                            if( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE ) {
                                    handle = cgs.media.redCubeIcon;
                            } else {
                                    handle = cgs.media.blueCubeIcon;
                            }
                            CG_DrawPic( 470 + CHAR_WIDTH*3 + TEXT_ICON_SPACE, 432, ICON_SIZE, ICON_SIZE, handle );
                    }

            }
        }
}
#endif

/*
===========================================================================================

  UPPER RIGHT CORNER

===========================================================================================
*/

/*
================
CG_DrawAttacker

================
*/
static float CG_DrawAttacker( float y ) {
	int			t;
	float		size;
	vec3_t		angles;
	const char	*info;
	const char	*name;
	int			clientNum;

	if ( cg.predictedPlayerState.stats[STAT_HEALTH] <= 0 ) {
		return y;
	}

	if ( !cg.attackerTime ) {
		return y;
	}

	clientNum = cg.predictedPlayerState.persistant[PERS_ATTACKER];
	if ( clientNum < 0 || clientNum >= MAX_CLIENTS || clientNum == cg.snap->ps.clientNum ) {
		return y;
	}

	t = cg.time - cg.attackerTime;
	if ( t > ATTACKER_HEAD_TIME ) {
		cg.attackerTime = 0;
		return y;
	}

	size = ICON_SIZE * 1.25;

	angles[PITCH] = 0;
	angles[YAW] = 180;
	angles[ROLL] = 0;
	CG_DrawHead( 640 - size, y, size, size, clientNum, angles );

	info = CG_ConfigString( CS_PLAYERS + clientNum );
	name = Info_ValueForKey(  info, "n" );
	y += size;
	CG_DrawBigString( 640 - ( Q_PrintStrlen( name ) * BIGCHAR_WIDTH), y, name, 0.5 );

	return y + BIGCHAR_HEIGHT + 2;
}

/*
================
CG_DrawSpeedMeter

================
*/
static float CG_DrawSpeedMeter( float y ) {
	char        *s;
	int         w;
	vec_t       *vel;
	int         speed;
	float       color[4];

	/* speed meter can get in the way of the scoreboard */
	if ( cg.scoreBoardShowing ) {
		return y;
	}

	vel = cg.snap->ps.velocity;
	/* ignore vertical component of velocity */
	speed = sqrt(vel[0] * vel[0] + vel[1] * vel[1]);

	s = va( "%iu/s", speed );

	w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;

	color[0] = color[1] = color[2] = 1.0;
	color[3] = 0.5;

	if (cg_drawSpeed.integer == 1) {
		/* top left-hand corner of screen */
		CG_DrawStringExt( 635 - CG_DrawStrlen( s ) * TINYCHAR_WIDTH, y + 2, s, color, qfalse, qtrue, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0 );
		return y + TINYCHAR_HEIGHT + 4;
	} else {
		/* center of screen */
		CG_DrawBigString( 320 - w / 2, 300, s, 1.0F);
		return y;
	}
}

/*
==================
CG_DrawSnapshot
==================
*/
static float CG_DrawSnapshot( float y ) {
	char		*s;
	int			w;

	s = va( "time:%i snap:%i cmd:%i", cg.snap->serverTime, 
		cg.latestSnapshotNum, cgs.serverCommandSequence );
	w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;

	CG_DrawBigString( 635 - w, y + 2, s, 1.0F);

	return y + BIGCHAR_HEIGHT + 4;
}

/*
==================
CG_DrawFPS
==================
*/
#define	FPS_FRAMES	4
static float CG_DrawFPS( float y ) {
	char		*s;
	int			w;
	static int	previousTimes[FPS_FRAMES];
	static int	index;
	int		i, total;
	int		fps;
	static	int	previous;
	int		t, frameTime;
	float		color[4];

	// don't use serverTime, because that will be drifting to
	// correct for internet lag changes, timescales, timedemos, etc
	t = trap_Milliseconds();
	frameTime = t - previous;
	previous = t;

	previousTimes[index % FPS_FRAMES] = frameTime;
	index++;
	if ( index > FPS_FRAMES ) {
		// average multiple frames together to smooth changes out a bit
		total = 0;
		for ( i = 0 ; i < FPS_FRAMES ; i++ ) {
			total += previousTimes[i];
		}
		if ( !total ) {
			total = 1;
		}
		fps = 1000 * FPS_FRAMES / total;

		s = va( "%ifps", fps );
		w = CG_DrawStrlen( s ) * TINYCHAR_WIDTH;

		color[0] = color[1] = color[2] = 1.0;
		color[3] = 0.5;

		CG_DrawStringExt( 635 - w, y + 2, s, color, qfalse, qtrue, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0 );
	}

	return y + TINYCHAR_HEIGHT + 4;
}

/*
=================
CG_DrawTimer
=================
*/
static float CG_DrawTimer( int y ) {
	char		*s;
	int			mins, seconds, tens;
	int			msec;

	msec = cg.time - cgs.levelStartTime;

	seconds = msec / 1000;
	mins = seconds / 60;
	seconds -= mins * 60;
	tens = seconds / 10;
	seconds -= tens * 10;

	s = va( "%i:%i%i", mins, tens, seconds );

	if (cg_drawTimer.integer == 1) {
		/* customizable timer */
		CG_DrawStringExt( cg_timerX.integer - CG_DrawStrlen( s ) * cg_timerWidth.integer / 2, cg_timerY.integer, s, colorWhite, qfalse, qtrue, cg_timerWidth.integer, cg_timerHeight.integer, 0 );
		return y;
	} else if (cg_drawTimer.integer == 2) {
		/* top of screen */
		CG_DrawStringExt( 318 - CG_DrawStrlen( s ) * 25 / 2, 2, s, colorWhite, qfalse, qtrue, 25, 25, 0);
		return y;
	} else {
		/* top right-hand corner of screen */
		CG_DrawStringExt( 619 - CG_DrawStrlen( s ) * TINYCHAR_WIDTH / 2, y + 2, s, colorWhite, qfalse, qtrue, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0 );
		return y + TINYCHAR_HEIGHT + 4;

	}
}

/*
CG_DrawDoubleDominationThings
 *
 *Sago: Might be relevant for debugging missionpack.
*/

/*static float CG_DrawDoubleDominationThings( float y ) {
	char		*s;
	int			w;
	int 		statusA, statusB;
	statusA = cgs.redflag;
	statusB = cgs.blueflag;

	if(statusA == TEAM_NONE) {
		s = va("Point A not spawned");
	} else
	if(statusA == TEAM_FREE) {
		s = va("Point A is not controlled");
	} else
	if(statusA == TEAM_RED) {
		s = va("Point A is controlled by RED");
	} else
	if(statusA == TEAM_BLUE) {
		s = va("Point A is controlled by BLUE");
	} else
		s = va("Point A has an error");
	w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
	CG_DrawSmallString( 635 - w, y + 2, s, 1.0F);
	y+=SMALLCHAR_HEIGHT+4;

	if(statusB == TEAM_NONE) {
		s = va("Point B not spawned");
	} else
	if(statusB == TEAM_FREE) {
		s = va("Point B is not controlled");
	} else
	if(statusB == TEAM_RED) {
		s = va("Point B is controlled by RED");
	} else
	if(statusB == TEAM_BLUE) {
		s = va("Point B is controlled by BLUE");
	} else
		s = va("Point B has an error");
	w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
	CG_DrawSmallString( 635 - w, y + 2, s, 1.0F);

	if( ( ( statusB == statusA ) && ( statusA == TEAM_RED ) ) ||
		( ( statusB == statusA ) && ( statusA == TEAM_BLUE ) ) ) {
		s = va("Capture in: %i",(cgs.timetaken+10*1000-cg.time)/1000+1);
		w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
		y+=SMALLCHAR_HEIGHT+4;
		CG_DrawSmallString( 635 - w, y + 2, s, 1.0F);
	}

	return y + SMALLCHAR_HEIGHT+4;
}*/

/*
=================
CG_DrawLMSmode
=================
*/

static float CG_DrawLMSmode( float y ) {
	char		*s;
	int		w;

	if(cgs.lms_mode == 0) {
		s = va("LMS: Point/round + OT");
	} else
	if(cgs.lms_mode == 1) {
		s = va("LMS: Point/round - OT");
	} else
	if(cgs.lms_mode == 2) {
		s = va("LMS: Point/kill + OT");
	} else
	if(cgs.lms_mode == 3) {
		s = va("LMS: Point/kill - OT");
	} else
		s = va("LMS: Unknown mode");

	w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
	CG_DrawSmallString( 635 - w, y + 2, s, 1.0F);

	return y + SMALLCHAR_HEIGHT+4;
}

/*
=================
CG_DrawCTFoneway
=================
*/

static float CG_DrawCTFoneway( float y ) {
	char		*s;
	int		w;
	vec4_t		color;

	if(cgs.gametype != GT_CTF_ELIMINATION)
		return y;

	memcpy(color,g_color_table[ColorIndex(COLOR_WHITE)],sizeof(color));

	if( (cgs.elimflags&EF_ONEWAY)==0) {
		return y; //nothing to draw
	} else
	if(cgs.attackingTeam == TEAM_BLUE) {
		memcpy(color,g_color_table[ColorIndex(COLOR_BLUE)],sizeof(color));
		s = va("Blue team on offence");
	} else
	if(cgs.attackingTeam == TEAM_RED) {
		memcpy(color,g_color_table[ColorIndex(COLOR_RED)],sizeof(color));
		s = va("Red team on offence");
	} else
		s = va("Unknown team on offence");

	w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
	CG_DrawSmallStringColor( 635 - w, y + 2, s, color);

	return y + SMALLCHAR_HEIGHT+4;
}

/*
=================
CG_DrawEliminationDeathMessage
=================
*/

/*static float CG_DrawEliminationDeathMessage( float y ) {
	char		*s;
	int			w;

	s = va("You are waiting for a new round");
	w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
	CG_DrawSmallString( 635 - w, y + 2, s, 1.0F);

	return y + SMALLCHAR_HEIGHT+4;
}*/

/*
=================
CG_DrawDomStatus
=================
*/

static float CG_DrawDomStatus( float y ) {
	int 		i,w; 
	char		*s;
	vec4_t		color;
	
	for(i = 0;i < cgs.domination_points_count;i++) {
		switch(cgs.domination_points_status[i]) {
			case TEAM_RED:
				memcpy(color,g_color_table[ColorIndex(COLOR_RED)],sizeof(color));
				break;
			case TEAM_BLUE:
				memcpy(color,g_color_table[ColorIndex(COLOR_BLUE)],sizeof(color));
				break;
			default:
				memcpy(color,g_color_table[ColorIndex(COLOR_WHITE)],sizeof(color));
				break;			
		}
		
		s = va("%s",cgs.domination_points_names[i]);
		w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
		CG_DrawSmallStringColor( 635 - w, y + 2, s, color);
		y += SMALLCHAR_HEIGHT+4;
			
	}

	return y;
}


/*
=================
CG_DrawEliminationTimer
=================
*/
static float CG_DrawEliminationTimer( float y ) {
	char		*s;
	int			w;
	int			mins, seconds, tens, sec;
	int			msec;
	vec4_t			color;
	const char	*st;
	int cw;
	int rst;
	static qboolean fightPlayed = qfalse;

        

	rst = cgs.roundStartTime;

        if(cg.time>rst && !cgs.roundtime && cg.time -rst>100)
            return y;

	if(cg_elimination_activewarmup.integer < 3 && cg.time<rst)
            return y;

	if(cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR)
            return y;

	if(cg.scoreBoardShowing )
            return y;

	//default color is white
	memcpy(color,g_color_table[ColorIndex(COLOR_WHITE)],sizeof(color));

	//msec = cg.time - cgs.levelStartTime;
	if(cg.time>rst) //We are started
	{
		msec = cgs.roundtime*1000 - (cg.time -rst);
		if(msec<=30*1000-1) //<= 30 seconds
			memcpy(color,g_color_table[ColorIndex(COLOR_YELLOW)],sizeof(color));
		if(msec<=10*1000-1) //<= 10 seconds
			memcpy(color,g_color_table[ColorIndex(COLOR_RED)],sizeof(color));
		msec += 1000; //120-1 instead of 119-0
	}
	else
	{
		//Warmup
		msec = -cg.time +rst;
		memcpy(color,g_color_table[ColorIndex(COLOR_GREEN)],sizeof(color));
		sec = msec/1000;
		msec += 1000; //5-1 instead of 4-0
		fightPlayed = qfalse;
/***
Lots of stuff
****/
	if(cg.warmup == 0)
	{
		st = va( "Round in: %i", sec + 1 );
		if ( sec != cg.warmupCount ) {
			cg.warmupCount = sec;
			switch ( sec ) {
			case 0:
				trap_S_StartLocalSound( cgs.media.count1Sound, CHAN_ANNOUNCER );
				break;
			case 1:
				trap_S_StartLocalSound( cgs.media.count2Sound, CHAN_ANNOUNCER );
				break;
			case 2:
				trap_S_StartLocalSound( cgs.media.count3Sound, CHAN_ANNOUNCER );
				break;
			default:
				break;
			}
		} 
		switch ( cg.warmupCount ) {
		case 0:
			cw = 22;
			break;
		case 1:
			cw = 20;
			break;
		case 2:
			cw = 18;
			break;
		default:
			cw = 16;
			break;
		}
		w = CG_DrawStrlen( st );
		if ( cg.warmupCount < cg_elimination_activewarmup.integer ) {
			CG_DrawStringExt( 320 - w * cw/2, 70, st, colorWhite,
					qfalse, qtrue, cw, (int)(cw * 1.5), 0 );
		}
	}
/*
Lots of stuff
*/
	}

	if ( cg.time>rst && cg.time -rst<100 && !fightPlayed && cg_elimination_activewarmup.integer ) {
		trap_S_StartLocalSound( cgs.media.countFightSound, CHAN_ANNOUNCER );
		CG_CenterPrint( "FIGHT!", 80, 24 );
		fightPlayed = qtrue;
	}

	seconds = msec / 1000;
	mins = seconds / 60;
	seconds -= mins * 60;
	tens = seconds / 10;
	seconds -= tens * 10;

	if(msec>=0)
		s = va( " %i:%i%i", mins, tens, seconds );
	else
		s = va( " Overtime");
	w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
	
	CG_DrawBigStringColor( 635 - w, y + 2, s, color);

	return y + BIGCHAR_HEIGHT + 4;
}


/*
=================
CG_DrawTeamOverlay
=================
*/

static float CG_DrawTeamOverlay( float y, qboolean right, qboolean upper ) {
	int x, w, h, xx;
	int i, j, len;
	const char *p;
	vec4_t		hcolor;
	int pwidth, lwidth;
	int plyrs;
	char st[16];
	clientInfo_t *ci;
	gitem_t	*item;
	int ret_y, count;

	if ( !cg_drawTeamOverlay.integer ) {
		return y;
	}

	if ( cg.snap->ps.persistant[PERS_TEAM] != TEAM_RED && cg.snap->ps.persistant[PERS_TEAM] != TEAM_BLUE ) {
		return y; // Not on any team
	}

	plyrs = 0;

	// max player name width
	pwidth = 0;
	count = (numSortedTeamPlayers > 8) ? 8 : numSortedTeamPlayers;
	for (i = 0; i < count; i++) {
		ci = cgs.clientinfo + sortedTeamPlayers[i];
		if ( ci->infoValid && ci->team == cg.snap->ps.persistant[PERS_TEAM]) {
			plyrs++;
			len = CG_DrawStrlen(ci->name);
			if (len > pwidth)
				pwidth = len;
		}
	}

	if (!plyrs)
		return y;

	if (pwidth > TEAM_OVERLAY_MAXNAME_WIDTH)
		pwidth = TEAM_OVERLAY_MAXNAME_WIDTH;

	// max location name width
	lwidth = 0;
	for (i = 1; i < MAX_LOCATIONS; i++) {
		p = CG_ConfigString(CS_LOCATIONS + i);
		if (p && *p) {
			len = CG_DrawStrlen(p);
			if (len > lwidth)
				lwidth = len;
		}
	}

	if (lwidth > TEAM_OVERLAY_MAXLOCATION_WIDTH)
		lwidth = TEAM_OVERLAY_MAXLOCATION_WIDTH;

	w = (pwidth + lwidth + 4 + 7) * TINYCHAR_WIDTH;

	if ( right )
		x = 640 - w;
	else
		x = 0;

	h = plyrs * TINYCHAR_HEIGHT;

	if ( upper ) {
		ret_y = y + h;
	} else {
		y -= h;
		ret_y = y;
	}

	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED ) {
		hcolor[0] = 1.0f;
		hcolor[1] = 0.0f;
		hcolor[2] = 0.0f;
		hcolor[3] = 0.33f;
	} else { // if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE )
		hcolor[0] = 0.0f;
		hcolor[1] = 0.25f;
		hcolor[2] = 1.0f;
		hcolor[3] = 0.33f;
	}
	trap_R_SetColor( hcolor );
	CG_DrawPic( x, y, w, h, cgs.media.teamStatusBar );
	trap_R_SetColor( NULL );

	for (i = 0; i < count; i++) {
		ci = cgs.clientinfo + sortedTeamPlayers[i];
		if ( ci->infoValid && ci->team == cg.snap->ps.persistant[PERS_TEAM]) {

			hcolor[0] = hcolor[1] = hcolor[2] = hcolor[3] = 1.0;

			xx = x + TINYCHAR_WIDTH;

			CG_DrawStringExt( xx, y,
				ci->name, hcolor, qfalse, qfalse,
				TINYCHAR_WIDTH, TINYCHAR_HEIGHT, TEAM_OVERLAY_MAXNAME_WIDTH);

			if (lwidth) {
				p = CG_ConfigString(CS_LOCATIONS + ci->location);
				if (!p || !*p)
					p = "unknown";
				len = CG_DrawStrlen(p);
				if (len > lwidth)
					len = lwidth;

//				xx = x + TINYCHAR_WIDTH * 2 + TINYCHAR_WIDTH * pwidth + 
//					((lwidth/2 - len/2) * TINYCHAR_WIDTH);
				xx = x + TINYCHAR_WIDTH * 2 + TINYCHAR_WIDTH * pwidth;
				CG_DrawStringExt( xx, y,
					p, hcolor, qfalse, qfalse, TINYCHAR_WIDTH, TINYCHAR_HEIGHT,
					TEAM_OVERLAY_MAXLOCATION_WIDTH);
			}

			CG_GetColorForHealth( ci->health, ci->armor, hcolor );

			Com_sprintf (st, sizeof(st), "%3i %3i", ci->health,	ci->armor);

			xx = x + TINYCHAR_WIDTH * 3 + 
				TINYCHAR_WIDTH * pwidth + TINYCHAR_WIDTH * lwidth;

			CG_DrawStringExt( xx, y,
				st, hcolor, qfalse, qfalse,
				TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0 );

			// draw weapon icon
			xx += TINYCHAR_WIDTH * 3;

			if ( cg_weapons[ci->curWeapon].weaponIcon ) {
				CG_DrawPic( xx, y, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 
					cg_weapons[ci->curWeapon].weaponIcon );
			} else {
				CG_DrawPic( xx, y, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 
					cgs.media.deferShader );
			}

			// Draw powerup icons
			if (right) {
				xx = x;
			} else {
				xx = x + w - TINYCHAR_WIDTH;
			}
			for (j = 0; j <= PW_NUM_POWERUPS; j++) {
				if (ci->powerups & (1 << j)) {

					item = BG_FindItemForPowerup( j );

					if (item) {
						CG_DrawPic( xx, y, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 
						trap_R_RegisterShader( item->icon ) );
						if (right) {
							xx -= TINYCHAR_WIDTH;
						} else {
							xx += TINYCHAR_WIDTH;
						}
					}
				}
			}

			y += TINYCHAR_HEIGHT;
		}
	}

	return ret_y;
//#endif
}

static void CG_DrawFragMsgIcons(fragInfo_t fi, int i) {
	int	x_offset;
	int	spacing;
	int	h;
#ifdef MISSIONPACK
	float	*color;
	int imageWidth = 10;
	int imageHeight = 10;
#else
	vec4_t	hcolor;
#endif

	h = (cgs.teamChatPos - cgs.teamLastChatPos) * TINYCHAR_HEIGHT;

#ifdef MISSIONPACK
	color = CG_FadeColor(fi.fragTime, FRAGMSG_FADETIME);
	if (!color) {
		trap_R_SetColor(NULL);
		return;
	}
	trap_R_SetColor(color);

	spacing = 3;
	imageWidth = 10;

	if (fi.attackerName[0] != '\0') {
		CG_Text_Paint(FRAGMSG_X, FRAGMSG_Y + (i * 16) - h, 0.20, color,
				fi.attackerName, 0, 0, ITEM_TEXTSTYLE_SHADOWED);
		x_offset = CG_Text_Width(fi.attackerName, 0.20, 0) + spacing;
	} else x_offset = 0;

	CG_DrawPic(FRAGMSG_X + x_offset, FRAGMSG_Y + (i * 16) - imageHeight - h,
			imageWidth, imageHeight, fi.causeShader);

			x_offset += imageWidth + spacing;

		CG_Text_Paint(FRAGMSG_X + x_offset, FRAGMSG_Y + (i * 16) - h, 0.20, color,
			fi.targetName, 0, 0, ITEM_TEXTSTYLE_SHADOWED);

	if (fi.teamFrag) {
		x_offset += CG_Text_Width(fi.targetName, 0.20, 0) + spacing;
		CG_Text_Paint(FRAGMSG_X + x_offset, FRAGMSG_Y + (i * 16) - h, 0.20, color,
				"(^1TEAMMATE^7)", 0, 0, ITEM_TEXTSTYLE_SHADOWED);
	}
#else
	hcolor[0] = hcolor[1] = hcolor[2] = hcolor[3] = 1.0;
	trap_R_SetColor(hcolor);
	spacing = 3;

	if (fi.attackerName[0] != '\0') {
		if ( fi.attackerTeam == TEAM_RED ) {
			CG_DrawStringExt(FRAGMSG_X, FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h,
					fi.attackerName, colorCornellRed, qtrue, qfalse,
					TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0);
		} else if ( fi.attackerTeam == TEAM_BLUE ) {
			CG_DrawStringExt(FRAGMSG_X, FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h,
					fi.attackerName, colorRoyalBlue, qtrue, qfalse,
					TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0);
		} else {
			CG_DrawStringExt(FRAGMSG_X, FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h,
					fi.attackerName, hcolor, qfalse, qfalse,
					TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0);
		}
		x_offset = CG_DrawStrlen(fi.attackerName) * TINYCHAR_WIDTH + spacing;
	} else x_offset = 0;

	CG_DrawPic(FRAGMSG_X + x_offset, FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h,
			TINYCHAR_WIDTH, TINYCHAR_HEIGHT, fi.causeShader);

	x_offset += TINYCHAR_WIDTH + spacing;

	if ( fi.targetTeam == TEAM_RED ) {
		CG_DrawStringExt(FRAGMSG_X + x_offset, FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h,
				fi.targetName, colorCornellRed, qtrue, qfalse,
				TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0);
	} else if ( fi.targetTeam == TEAM_BLUE ) {
		CG_DrawStringExt(FRAGMSG_X + x_offset, FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h,
				fi.targetName, colorRoyalBlue, qtrue, qfalse,
				TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0);
	} else {
		CG_DrawStringExt(FRAGMSG_X + x_offset, FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h,
				fi.targetName, hcolor, qfalse, qfalse,
				TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0);
	}

	if (fi.teamFrag) {
		x_offset += CG_DrawStrlen(fi.targetName) * TINYCHAR_WIDTH + spacing;
		CG_DrawStringExt(FRAGMSG_X + x_offset,
			FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h, "(^1TEAMMATE^7)", hcolor,
			qfalse, qfalse, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0);
	}

#endif
	trap_R_SetColor(NULL);
}

static void CG_DrawFragMsgText(char *msg, int i) {
#ifdef MISSIONPACK
	float	*color;
#else
	vec4_t	hcolor;
#endif
	int	h;

	h = (cgs.teamChatPos - cgs.teamLastChatPos) * TINYCHAR_HEIGHT;

#ifdef MISSIONPACK
	color = CG_FadeColor(cgs.fragMsg[i].fragTime, FRAGMSG_FADETIME);
	if (!color) {
		trap_R_SetColor(NULL);
		return;
	}
	trap_R_SetColor(color);
	CG_Text_Paint(FRAGMSG_X, FRAGMSG_Y + (i * 13) - h, 0.20, color, msg, 0, 0,
			ITEM_TEXTSTYLE_SHADOWED);
#else
	hcolor[0] = hcolor[1] = hcolor[2] = hcolor[3] = 1.0;
	trap_R_SetColor(hcolor);

	CG_DrawStringExt(FRAGMSG_X, FRAGMSG_Y + (i * TINYCHAR_HEIGHT) - h,
			msg, hcolor, qfalse, qfalse, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0);
#endif
	trap_R_SetColor(NULL);
}

static void CG_DrawFragMessage( void ) {
	int	i;
	for (i = FRAGMSG_MAX - 1; i >= 0; i--) {
		if (cgs.fragMsg[i].targetName[0] != '\0') {
			// remove frag message after elapsed time
			if (cg.time > cgs.fragMsg[i].fragTime + FRAGMSG_FADETIME) {
				memset(&cgs.fragMsg[i], 0, sizeof(fragInfo_t));
			}
		}
		if (cgs.fragMsg[i].targetName[0] != '\0') {
			if (cg_obituaryOutput.integer == 2) {
				CG_DrawFragMsgText(cgs.fragMsg[i].message, i);
			}
			else if (cg_obituaryOutput.integer >= 3) {
				CG_DrawFragMsgIcons(cgs.fragMsg[i], i);
			}
		}
	}
}

/*
=====================
CG_DrawUpperRight

=====================
*/
static void CG_DrawUpperRight(stereoFrame_t stereoFrame)
{
	float	y;

	y = 0;

	if ( cgs.gametype >= GT_TEAM && cgs.ffa_gt!=1 && cg_drawTeamOverlay.integer == 1 ) {
		y = CG_DrawTeamOverlay( y, qtrue, qtrue );
	}
	/*if ( cgs.gametype == GT_DOUBLE_D ) {
		y = CG_DrawDoubleDominationThings(y);
	} 
	else*/
	if ( cgs.gametype == GT_LMS && cg.showScores ) {
		y = CG_DrawLMSmode(y);
	}
	else
	if ( cgs.gametype == GT_CTF_ELIMINATION ) {
		y = CG_DrawCTFoneway(y);
	}
	else
	if ( cgs.gametype == GT_DOMINATION ) {
		y = CG_DrawDomStatus(y);
	}
	
	if ( cg_drawSnapshot.integer ) {
		y = CG_DrawSnapshot( y );
	}
	if (cg_drawFPS.integer && (stereoFrame == STEREO_CENTER || stereoFrame == STEREO_RIGHT)) {
		y = CG_DrawFPS( y );
	}
	if (cgs.gametype==GT_ELIMINATION || cgs.gametype == GT_CTF_ELIMINATION || cgs.gametype==GT_LMS) {
		y = CG_DrawEliminationTimer( y );
		/*if (cgs.clientinfo[ cg.clientNum ].isDead)
			y = CG_DrawEliminationDeathMessage( y);*/
	}

	if ( cg_drawSpeed.integer ) {
		y = CG_DrawSpeedMeter( y );
	}
	if ( cg_drawTimer.integer ) {
		y = CG_DrawTimer( y );
	}
#ifndef MISSIONPACK
	if ( cg_drawItemPickup.integer ) {
		y = CG_DrawPickupItem( y );
	}
#endif
	if ( cg_drawAttacker.integer ) {
		y = CG_DrawAttacker( y );
	}

}

/*
===========================================================================================

  LOWER RIGHT CORNER

===========================================================================================
*/

/*
=================
CG_DrawScores

Draw the small two score display
=================
*/
#ifndef MISSIONPACK
static float CG_DrawScores( float y ) {
	const char	*s;
	int			s1, s2, score;
	int			x, w;
	int			v;
	vec4_t		color;
	float		y1;
	gitem_t		*item;
        int statusA,statusB;
        
        statusA = cgs.redflag;
        statusB = cgs.blueflag;

	s1 = cgs.scores1;
	s2 = cgs.scores2;

	y -=  BIGCHAR_HEIGHT + 8;

	y1 = y;

	// draw from the right side to left
	if ( cgs.gametype >= GT_TEAM && cgs.ffa_gt!=1) {
		x = 640;
		color[0] = 0.0f;
		color[1] = 0.25f;
		color[2] = 1.0f;
		color[3] = 0.5f;
		s = va( "%2i", s2 );
		w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH + 8;
		x -= w;
		CG_FillRect( x, y-4,  w, BIGCHAR_HEIGHT+8, color );
		if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE ) {
			CG_DrawPic( x, y-4, w, BIGCHAR_HEIGHT+8, cgs.media.selectShader );
		}
		CG_DrawStringExt( x + 4, y, s, colorWhite, qfalse, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );

		if ( cgs.gametype == GT_CTF || cgs.gametype == GT_CTF_ELIMINATION) {
			// Display flag status
			item = BG_FindItemForPowerup( PW_BLUEFLAG );

			if (item) {
				y1 = y - BIGCHAR_HEIGHT - 8;
				if( cgs.blueflag >= 0 && cgs.blueflag <= 2 ) {
					CG_DrawPic( x, y1-4, w, BIGCHAR_HEIGHT+8, cgs.media.blueFlagShader[cgs.blueflag] );
				}
			}
		}
                
                if ( cgs.gametype == GT_DOUBLE_D ) {
			// Display Domination point status
			
				y1 = y - 32;//BIGCHAR_HEIGHT - 8;
				if( cgs.redflag >= 0 && cgs.redflag <= 3 ) {
					CG_DrawPic( x, y1-4, w, 32, cgs.media.ddPointSkinB[cgs.blueflag] );
				}
		}
                
		color[0] = 1.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
		color[3] = 0.5f;
		s = va( "%2i", s1 );
		w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH + 8;
		x -= w;
		CG_FillRect( x, y-4,  w, BIGCHAR_HEIGHT+8, color );
		if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED ) {
			CG_DrawPic( x, y-4, w, BIGCHAR_HEIGHT+8, cgs.media.selectShader );
		}
		CG_DrawStringExt( x + 4, y, s, colorWhite, qfalse, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );

		if ( cgs.gametype == GT_CTF || cgs.gametype == GT_CTF_ELIMINATION ) {
			// Display flag status
			item = BG_FindItemForPowerup( PW_REDFLAG );

			if (item) {
				y1 = y - BIGCHAR_HEIGHT - 8;
				if( cgs.redflag >= 0 && cgs.redflag <= 2 ) {
					CG_DrawPic( x, y1-4, w, BIGCHAR_HEIGHT+8, cgs.media.redFlagShader[cgs.redflag] );
				}
			}
		}
                
                if ( cgs.gametype == GT_DOUBLE_D ) {
			// Display Domination point status
			
				y1 = y - 32;//BIGCHAR_HEIGHT - 8;
				if( cgs.redflag >= 0 && cgs.redflag <= 3 ) {
					CG_DrawPic( x, y1-4, w, 32, cgs.media.ddPointSkinA[cgs.redflag] );
				}
                                
                        
                                
                        //Time till capture:
                        if( ( ( statusB == statusA ) && ( statusA == TEAM_RED ) ) ||
                            ( ( statusB == statusA ) && ( statusA == TEAM_BLUE ) ) ) {
                                s = va("%i",(cgs.timetaken+10*1000-cg.time)/1000+1);
                                w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
                                CG_DrawBigString( x + 32+8-w/2, y-28, s, 1.0F );
                        }
		}
                
                if ( cgs.gametype == GT_OBELISK ) {
                    s = va("^1%3i%% ^4%3i%%",cg.redObeliskHealth,cg.blueObeliskHealth);
                    CG_DrawSmallString( x, y-28, s, 1.0F);
                }
                
                

		if ( cgs.gametype >= GT_CTF && cgs.ffa_gt==0) {
			v = cgs.capturelimit;
		} else {
			v = cgs.fraglimit;
		}
		if ( v ) {
			s = va( "%2i", v );
			w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH + 8;
			x -= w;
			CG_DrawStringExt( x + 4, y, s, colorWhite, qfalse, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
		}

		if ( cgs.gametype == GT_CTF_ELIMINATION || cgs.gametype == GT_ELIMINATION ) {
			if ( cgs.gametype == GT_CTF_ELIMINATION ) {
				y1 = y - BIGCHAR_HEIGHT - 34;
			} else {
				y1 = y - BIGCHAR_HEIGHT - 11;
			}

			color[0] = 0.0f;
			color[1] = 0.25f;
			color[2] = 1.0f;
			color[3] = 0.5f;
			x = 640;
			s = va( "%i", cgs.blueLivingCount );
			w = CG_DrawStrlen( s ) * MEDIUMCHAR_WIDTH + 8;
			x -= w + 20;
			CG_DrawPic( x, y1, 20, 20, cgs.media.blueCubeIcon );
			CG_DrawStringExt( x+24, y1+2, s, color, qfalse, qtrue, MEDIUMCHAR_WIDTH, MEDIUMCHAR_HEIGHT, 0 );

			color[0] = 1.0f;
			color[1] = 0.0f;
			color[2] = 0.0f;
			color[3] = 0.5f;
			x -= 40;
			s = va( "%i", cgs.redLivingCount );
			w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH + 8;
			CG_DrawPic( x, y1, 20, 20, cgs.media.redCubeIcon );
			CG_DrawStringExt( x+24, y1+2, s, color, qfalse, qtrue, MEDIUMCHAR_WIDTH, MEDIUMCHAR_HEIGHT, 0 );
		}

	} else {
		qboolean	spectator;

		x = 640;
		score = cg.snap->ps.persistant[PERS_SCORE];
		spectator = ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR );

		// always show your score in the second box if not in first place
		if ( s1 != score ) {
			s2 = score;
		}
		if ( s2 != SCORE_NOT_PRESENT ) {
			s = va( "%2i", s2 );
			w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH + 8;
			x -= w;
			if ( !spectator && score == s2 && score != s1 ) {
				color[0] = 1.0f;
				color[1] = 0.5f;
				color[2] = 0.0f;
				color[3] = 0.5f;
				CG_FillRect( x, y-4,  w, BIGCHAR_HEIGHT+8, color );
				CG_DrawPic( x, y-4, w, BIGCHAR_HEIGHT+8, cgs.media.selectShader );
			} else {
				color[0] = 0.5f;
				color[1] = 0.5f;
				color[2] = 0.5f;
				color[3] = 0.5f;
				CG_FillRect( x, y-4,  w, BIGCHAR_HEIGHT+8, color );
			}	
			CG_DrawStringExt( x + 4, y, s, colorWhite, qfalse, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
		}

		// first place
		if ( s1 != SCORE_NOT_PRESENT ) {
			s = va( "%2i", s1 );
			w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH + 8;
			x -= w;
			if ( !spectator && score == s1 ) {
				color[0] = 0.0f;
				color[1] = 0.5f;
				color[2] = 1.0f;
				color[3] = 0.5f;
				CG_FillRect( x, y-4,  w, BIGCHAR_HEIGHT+8, color );
				CG_DrawPic( x, y-4, w, BIGCHAR_HEIGHT+8, cgs.media.selectShader );
			} else {
				color[0] = 0.25f;
				color[1] = 0.25f;
				color[2] = 0.25f;
				color[3] = 0.5f;
				CG_FillRect( x, y-4,  w, BIGCHAR_HEIGHT+8, color );
			}	
			CG_DrawStringExt( x + 4, y, s, colorWhite, qfalse, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
		}

		if ( cgs.fraglimit ) {
			s = va( "%2i", cgs.fraglimit );
			w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH + 8;
			x -= w;
			CG_DrawStringExt( x + 4, y, s, colorWhite, qfalse, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0 );
		}

	}

	return y1 - 8;
}
#endif // MISSIONPACK

/*
================
CG_DrawPowerups
================
*/
#ifndef MISSIONPACK
static float CG_DrawPowerups( float y ) {
	int		sorted[MAX_POWERUPS];
	int		sortedTime[MAX_POWERUPS];
	int		i, j, k;
	int		active;
	playerState_t	*ps;
	int		t;
	gitem_t	*item;
	int		x;
	int		color;
	float	size;
	float	f;
	static float colors[2][4] = { 
    { 0.2f, 1.0f, 0.2f, 1.0f } , 
    { 1.0f, 0.2f, 0.2f, 1.0f } 
  };

	ps = &cg.snap->ps;

	if ( ps->stats[STAT_HEALTH] <= 0 ) {
		return y;
	}

	// sort the list by time remaining
	active = 0;
	for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
		if ( !ps->powerups[ i ] ) {
			continue;
		}
		t = ps->powerups[ i ] - cg.time;
		// ZOID--don't draw if the power up has unlimited time (999 seconds)
		// This is true of the CTF flags
		if ( t < 0 || t > 999000) {
			continue;
		}

                item = BG_FindItemForPowerup( i );
                if ( item && item->giType == IT_PERSISTANT_POWERUP)
                    continue; //Don't draw persistant powerups here!

		// insert into the list
		for ( j = 0 ; j < active ; j++ ) {
			if ( sortedTime[j] >= t ) {
				for ( k = active - 1 ; k >= j ; k-- ) {
					sorted[k+1] = sorted[k];
					sortedTime[k+1] = sortedTime[k];
				}
				break;
			}
		}
		sorted[j] = i;
		sortedTime[j] = t;
		active++;
	}

	// draw the icons and timers
	x = 640 - ICON_SIZE - CHAR_WIDTH * 2;
	for ( i = 0 ; i < active ; i++ ) {
		item = BG_FindItemForPowerup( sorted[i] );

    if (item) {

		  color = 1;

		  y -= ICON_SIZE;

		  trap_R_SetColor( colors[color] );
		  CG_DrawField( x, y, 2, sortedTime[ i ] / 1000, CHAR_WIDTH, CHAR_HEIGHT );

		  t = ps->powerups[ sorted[i] ];
		  if ( t - cg.time >= POWERUP_BLINKS * POWERUP_BLINK_TIME ) {
			  trap_R_SetColor( NULL );
		  } else {
			  vec4_t	modulate;

			  f = (float)( t - cg.time ) / POWERUP_BLINK_TIME;
			  f -= (int)f;
			  modulate[0] = modulate[1] = modulate[2] = modulate[3] = f;
			  trap_R_SetColor( modulate );
		  }

		  if ( cg.powerupActive == sorted[i] && 
			  cg.time - cg.powerupTime < PULSE_TIME ) {
			  f = 1.0 - ( ( (float)cg.time - cg.powerupTime ) / PULSE_TIME );
			  size = ICON_SIZE * ( 1.0 + ( PULSE_SCALE - 1.0 ) * f );
		  } else {
			  size = ICON_SIZE;
		  }

		  CG_DrawPic( 640 - size, y + ICON_SIZE / 2 - size / 2, 
			  size, size, trap_R_RegisterShader( item->icon ) );
    }
	}
	trap_R_SetColor( NULL );

	return y;
}
#endif // MISSIONPACK

/*
=====================
CG_DrawLowerRight

=====================
*/
#ifndef MISSIONPACK
static void CG_DrawLowerRight( void ) {
	float	y;

	y = 468 - ICON_SIZE;

	if ( cgs.gametype >= GT_TEAM && cgs.ffa_gt!=1 && cg_drawTeamOverlay.integer == 2 ) {
		y = CG_DrawTeamOverlay( y, qtrue, qfalse );
	} 

	y = CG_DrawScores( y + 4 );
	y = CG_DrawPowerups( y + 4 );
}
#endif // MISSIONPACK

/*
===================
CG_DrawPickupItem
===================
*/
#ifndef MISSIONPACK
static int CG_DrawPickupItem( int y ) {
	int		value;
	int w;
	float	*fadeColor;

	if ( cg.snap->ps.stats[STAT_HEALTH] <= 0 ) {
		return y;
	}

	value = cg.itemPickup;
	w = CG_DrawStrlen( bg_itemlist[ value ].pickup_name ) * TINYCHAR_WIDTH;
	if ( value ) {
		fadeColor = CG_FadeColor( cg.itemPickupTime, 3000 );
		if ( fadeColor ) {
			CG_RegisterItemVisuals( value );
			trap_R_SetColor( fadeColor );
			CG_DrawPic( 625, y, ICON_SIZE/4, ICON_SIZE/4, cg_items[ value ].icon );
			CG_DrawStringExt( 622 - w, y + 2.5, bg_itemlist[ value ].pickup_name, fadeColor, qfalse, qfalse, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0 );
			trap_R_SetColor( NULL );
		}
	}
	
	return y;
}
#endif // MISSIONPACK

/*
=====================
CG_DrawLowerLeft

=====================
*/
#ifndef MISSIONPACK
static void CG_DrawLowerLeft( void ) {
	float	y;

	y = 468 - ICON_SIZE;

	if ( cgs.gametype >= GT_TEAM && cgs.ffa_gt!=1 && cg_drawTeamOverlay.integer == 3 ) {
		y = CG_DrawTeamOverlay( y, qfalse, qfalse );
	} 
}
#endif // MISSIONPACK


//===========================================================================================

/*
=================
CG_DrawTeamInfo
=================
*/
#ifndef MISSIONPACK
static void CG_DrawTeamInfo( void ) {
	int w, h;
	int i, len;
	vec4_t		hcolor;
	int		chatHeight;

#define CHATLOC_Y 420 // bottom end
#define CHATLOC_X 0

	if (cg_teamChatHeight.integer < TEAMCHAT_HEIGHT)
		chatHeight = cg_teamChatHeight.integer;
	else
		chatHeight = TEAMCHAT_HEIGHT;
	if (chatHeight <= 0)
		return; // disabled

	if (cgs.teamLastChatPos != cgs.teamChatPos) {
		if (cg.time - cgs.teamChatMsgTimes[cgs.teamLastChatPos % chatHeight] > cg_teamChatTime.integer) {
			cgs.teamLastChatPos++;
		}

		h = (cgs.teamChatPos - cgs.teamLastChatPos) * TINYCHAR_HEIGHT;

		w = 0;

		for (i = cgs.teamLastChatPos; i < cgs.teamChatPos; i++) {
			len = CG_DrawStrlen(cgs.teamChatMsgs[i % chatHeight]);
			if (len > w)
				w = len;
		}
		w *= TINYCHAR_WIDTH;
		w += TINYCHAR_WIDTH * 2;

		if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED ) {
			hcolor[0] = 1.0f;
			hcolor[1] = 0.0f;
			hcolor[2] = 0.0f;
			hcolor[3] = 0.33f;
		} else if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE ) {
			hcolor[0] = 0.0f;
			hcolor[1] = 0.25f;
			hcolor[2] = 1.0f;
			hcolor[3] = 0.33f;
		} else {
			hcolor[0] = 0.0f;
			hcolor[1] = 1.0f;
			hcolor[2] = 0.0f;
			hcolor[3] = 0.33f;
		}

		trap_R_SetColor( hcolor );
		CG_DrawPic( CHATLOC_X, CHATLOC_Y - h, 640, h, cgs.media.teamStatusBar );
		trap_R_SetColor( NULL );

		hcolor[0] = hcolor[1] = hcolor[2] = 1.0f;
		hcolor[3] = 1.0f;

		for (i = cgs.teamChatPos - 1; i >= cgs.teamLastChatPos; i--) {
			CG_DrawStringExt( CHATLOC_X + TINYCHAR_WIDTH, 
				CHATLOC_Y - (cgs.teamChatPos - i)*TINYCHAR_HEIGHT, 
				cgs.teamChatMsgs[i % chatHeight], hcolor, qfalse, qfalse,
				TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0 );
		}
	}
}
#endif // MISSIONPACK

/*
===================
CG_DrawHoldableItem
===================
*/
#ifndef MISSIONPACK
static void CG_DrawHoldableItem( void ) { 
	int		value;

	value = cg.snap->ps.stats[STAT_HOLDABLE_ITEM];
	if ( value ) {
		CG_RegisterItemVisuals( value );
		CG_DrawPic( 640-ICON_SIZE, (SCREEN_HEIGHT-ICON_SIZE)/2, ICON_SIZE, ICON_SIZE, cg_items[ value ].icon );
	}

}
#endif // MISSIONPACK

#ifndef MISSIONPACK
/*
===================
CG_DrawPersistantPowerup
===================
*/
#if 1 // sos001208 - DEAD // sago - ALIVE
static void CG_DrawPersistantPowerup( void ) { 
	int		value;

	value = cg.snap->ps.stats[STAT_PERSISTANT_POWERUP];
	if ( value ) {
		CG_RegisterItemVisuals( value );
		CG_DrawPic( 640-ICON_SIZE, (SCREEN_HEIGHT-ICON_SIZE)/2 - ICON_SIZE, ICON_SIZE, ICON_SIZE, cg_items[ value ].icon );
	}
}
#endif
#endif // MISSIONPACK


/*
===================
CG_RewardTime
===================
*/
int CG_RewardTime( int idx ) {
	return REWARD_TIME + cg.rewardSoundDelay[idx] + 200;
}

/*
===================
CG_DrawReward
===================
*/
static void CG_DrawReward( void ) { 
	float	*color;
	int		i;
	int 		numMedals;
	int 		skip;
	float	x, xx, y, yy;
	float	charWidth, charHeight;
	float	iconSize;
	float	lineLength = 0.0;
	float	scale;
	char	buf[32];

	if ( !cg_drawRewards.integer ) {
		return;
	}

	skip = 0;
	numMedals = 0;
	for (i = 0; i < MAX_REWARDSTACK; ++i) {
		if (cg.rewardTime[i] == -1) {
			cg.rewardTime[i] = cg.time;
		}
		if (cg.rewardTime[i] != 0 && cg.rewardTime[i] + CG_RewardTime(i) > cg.time) {
			numMedals++;
			lineLength += ICON_SIZE * CG_FadeScale( cg.rewardTime[i], CG_RewardTime(i) );
			if (skip) {
				cg.rewardTime[i-skip] = cg.rewardTime[i];
				cg.rewardShader[i-skip] = cg.rewardShader[i];
				cg.rewardCount[i-skip] = cg.rewardCount[i];
				cg.rewardSoundDelay[i-skip] = cg.rewardSoundDelay[i];
				cg. rewardTime[i] = 0;
			}
		} else {
			skip++;
		}
	}

	y = 56;
	x = 320 - lineLength/2;
	for (i = 0; i < numMedals ; i++) {
		color = CG_FadeColor( cg.rewardTime[i], CG_RewardTime(i) );
		scale = CG_FadeScale( cg.rewardTime[i], CG_RewardTime(i) );
		iconSize = ICON_SIZE * scale;
		trap_R_SetColor( color );

		yy = y + (ICON_SIZE - iconSize)/2.0;
		CG_DrawPic( x+2, yy, iconSize-4, iconSize-4, cg.rewardShader[i] );
		charWidth  = SMALLCHAR_WIDTH * scale;
		charHeight = SMALLCHAR_HEIGHT * scale;

		Com_sprintf(buf, sizeof(buf), "%d", cg.rewardCount[i]);
		xx = x + (iconSize - charWidth * CG_DrawStrlen( buf )) / 2;
		CG_DrawStringExt( xx, yy+ iconSize, buf, color, qfalse, qtrue, charWidth, charHeight, 0 );
		x += iconSize;
	}
	trap_R_SetColor( NULL );
}

/*
===================
CG_DrawReady
===================
*/
static void CG_DrawReady ( void ) {
	char *s;
	int w;
	if ( !cgs.startWhenReady )
		return;
	if ( cg.warmup >= 0 )
		return;

	if ( cg.readyMask & ( 1 << cg.snap->ps.clientNum ) ) {
		s = "^2You are ready";
	} else {
		s = "^1Type \"\\ready\" to ready up";
	}
	w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
	CG_DrawSmallString( 320 - w / 2, 45, s, 1.0F );
}


/*
===============================================================================

LAGOMETER

===============================================================================
*/

#define	LAG_SAMPLES		128


typedef struct {
	int		frameSamples[LAG_SAMPLES];
	int		frameCount;
	int		snapshotFlags[LAG_SAMPLES];
	int		snapshotSamples[LAG_SAMPLES];
	int		snapshotCount;
} lagometer_t;

lagometer_t		lagometer;

/*
==============
CG_AddLagometerFrameInfo

Adds the current interpolate / extrapolate bar for this frame
==============
*/
void CG_AddLagometerFrameInfo( void ) {
	int			offset;

	offset = cg.time - cg.latestSnapshotTime;
	lagometer.frameSamples[ lagometer.frameCount & ( LAG_SAMPLES - 1) ] = offset;
	lagometer.frameCount++;
}

/*
==============
CG_AddLagometerSnapshotInfo

Each time a snapshot is received, log its ping time and
the number of snapshots that were dropped before it.

Pass NULL for a dropped packet.
==============
*/
void CG_AddLagometerSnapshotInfo( snapshot_t *snap ) {
	// dropped packet
	if ( !snap ) {
		lagometer.snapshotSamples[ lagometer.snapshotCount & ( LAG_SAMPLES - 1) ] = -1;
		lagometer.snapshotCount++;
		return;
	}

	// add this snapshot's info
	lagometer.snapshotSamples[ lagometer.snapshotCount & ( LAG_SAMPLES - 1) ] = snap->ping;
	lagometer.snapshotFlags[ lagometer.snapshotCount & ( LAG_SAMPLES - 1) ] = snap->snapFlags;
	lagometer.snapshotCount++;
}

/*
==============
CG_DrawDisconnect

Should we draw something differnet for long lag vs no packets?
==============
*/
static void CG_DrawDisconnect( void ) {
	float		x, y;
	int			cmdNum;
	usercmd_t	cmd;
	const char		*s;
	int			w;  // bk010215 - FIXME char message[1024];

	// draw the phone jack if we are completely past our buffers
	cmdNum = trap_GetCurrentCmdNumber() - CMD_BACKUP + 1;
	trap_GetUserCmd( cmdNum, &cmd );
	if ( cmd.serverTime <= cg.snap->ps.commandTime
		|| cmd.serverTime > cg.time ) {	// special check for map_restart // bk 0102165 - FIXME
		return;
	}

	// also add text in center of screen
	s = "Connection Interrupted"; // bk 010215 - FIXME
	w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
	CG_DrawBigString( 320 - w/2, 100, s, 1.0F);

	// blink the icon
	if ( ( cg.time >> 9 ) & 1 ) {
		return;
	}

	x = 640 - 48;
	y = 480 - 48;

	CG_DrawPic( x, y, 48, 48, trap_R_RegisterShader("gfx/2d/net.tga" ) );
}


#define	MAX_LAGOMETER_PING	900
#define	MAX_LAGOMETER_RANGE	300

/*
==============
CG_DrawLagometer
==============
*/
static void CG_DrawLagometer( void ) {
	int		a, x, y, i;
	float	v;
	float	ax, ay, aw, ah, mid, range;
	int		color;
	float	vscale;

	if ( !cg_lagometer.integer || cgs.localServer || cg.scoreBoardShowing ) {
		CG_DrawDisconnect();
		return;
	}

	//
	// draw the graph
	//
#ifdef MISSIONPACK
	x = 640 - 48;
	y = 480 - 144;
#else
	x = 640 - 48;
	y = 480 - 48;
#endif

	trap_R_SetColor( NULL );
	CG_DrawPic( x, y, 48, 48, cgs.media.lagometerShader );

	ax = x;
	ay = y;
	aw = 48;
	ah = 48;
	CG_AdjustFrom640( &ax, &ay, &aw, &ah );

	color = -1;
	range = ah / 3;
	mid = ay + range;

	vscale = range / MAX_LAGOMETER_RANGE;

	// draw the frame interpoalte / extrapolate graph
	for ( a = 0 ; a < aw ; a++ ) {
		i = ( lagometer.frameCount - 1 - a ) & (LAG_SAMPLES - 1);
		v = lagometer.frameSamples[i];
		v *= vscale;
		if ( v > 0 ) {
			if ( color != 1 ) {
				color = 1;
				trap_R_SetColor( g_color_table[ColorIndex(COLOR_YELLOW)] );
			}
			if ( v > range ) {
				v = range;
			}
			trap_R_DrawStretchPic ( ax + aw - a, mid - v, 1, v, 0, 0, 0, 0, cgs.media.whiteShader );
		} else if ( v < 0 ) {
			if ( color != 2 ) {
				color = 2;
				trap_R_SetColor( g_color_table[ColorIndex(COLOR_BLUE)] );
			}
			v = -v;
			if ( v > range ) {
				v = range;
			}
			trap_R_DrawStretchPic( ax + aw - a, mid, 1, v, 0, 0, 0, 0, cgs.media.whiteShader );
		}
	}

	// draw the snapshot latency / drop graph
	range = ah / 2;
	vscale = range / MAX_LAGOMETER_PING;

	for ( a = 0 ; a < aw ; a++ ) {
		i = ( lagometer.snapshotCount - 1 - a ) & (LAG_SAMPLES - 1);
		v = lagometer.snapshotSamples[i];
		if ( v > 0 ) {
			if ( lagometer.snapshotFlags[i] & SNAPFLAG_RATE_DELAYED ) {
				if ( color != 5 ) {
					color = 5;	// YELLOW for rate delay
					trap_R_SetColor( g_color_table[ColorIndex(COLOR_YELLOW)] );
				}
			} else {
				if ( color != 3 ) {
					color = 3;
					trap_R_SetColor( g_color_table[ColorIndex(COLOR_GREEN)] );
				}
			}
			v = v * vscale;
			if ( v > range ) {
				v = range;
			}
			trap_R_DrawStretchPic( ax + aw - a, ay + ah - v, 1, v, 0, 0, 0, 0, cgs.media.whiteShader );
		} else if ( v < 0 ) {
			if ( color != 4 ) {
				color = 4;		// RED for dropped snapshots
				trap_R_SetColor( g_color_table[ColorIndex(COLOR_RED)] );
			}
			trap_R_DrawStretchPic( ax + aw - a, ay + ah - range, 1, range, 0, 0, 0, 0, cgs.media.whiteShader );
		}
	}

	trap_R_SetColor( NULL );

	if ( cg_nopredict.integer || cg_synchronousClients.integer ) {
		CG_DrawBigString( ax, ay, "snc", 1.0 );
	}

	CG_DrawDisconnect();
}



/*
===============================================================================

CENTER PRINTING

===============================================================================
*/


/*
==============
CG_CenterPrint

Called for important messages that should stay in the center of the screen
for a few moments
==============
*/
void CG_CenterPrint( const char *str, int y, int charWidth ) {
	char	*s;

	Q_strncpyz( cg.centerPrint, str, sizeof(cg.centerPrint) );

	cg.centerPrintTime = cg.time;
	cg.centerPrintY = y;
	cg.centerPrintCharWidth = charWidth;

	// count the number of lines for centering
	cg.centerPrintLines = 1;
	s = cg.centerPrint;
	while( *s ) {
		if (*s == '\n')
			cg.centerPrintLines++;
		s++;
	}
}


/*
===================
CG_DrawCenterString
===================
*/
static void CG_DrawCenterString( void ) {
	char	*start;
	int		l;
	int		x, y, w;
#ifdef MISSIONPACK // bk010221 - unused else
  int h;
#endif
	float	*color;

	if ( !cg.centerPrintTime ) {
		return;
	}

	color = CG_FadeColor( cg.centerPrintTime, 1000 * cg_centertime.value );
	if ( !color ) {
		return;
	}

	trap_R_SetColor( color );

	start = cg.centerPrint;

	y = cg.centerPrintY - cg.centerPrintLines * BIGCHAR_HEIGHT / 2;

	while ( 1 ) {
		char linebuffer[1024];

		for ( l = 0; l < 50; l++ ) {
			if ( !start[l] || start[l] == '\n' ) {
				break;
			}
			linebuffer[l] = start[l];
		}
		linebuffer[l] = 0;

#ifdef MISSIONPACK
		w = CG_Text_Width(linebuffer, 0.5, 0);
		h = CG_Text_Height(linebuffer, 0.5, 0);
		x = (SCREEN_WIDTH - w) / 2;
		CG_Text_Paint(x, y + h, 0.5, color, linebuffer, 0, 0, ITEM_TEXTSTYLE_SHADOWEDMORE);
		y += h + 6;
#else
		w = cg.centerPrintCharWidth * CG_DrawStrlen( linebuffer );

		x = ( SCREEN_WIDTH - w ) / 2;

		CG_DrawStringExt( x, y, linebuffer, color, qfalse, qtrue,
			cg.centerPrintCharWidth, (int)(cg.centerPrintCharWidth * 1.5), 0 );

		y += cg.centerPrintCharWidth * 1.5;
#endif
		while ( *start && ( *start != '\n' ) ) {
			start++;
		}
		if ( !*start ) {
			break;
		}
		start++;
	}

	trap_R_SetColor( NULL );
}

/*
=====================
CG_DrawCenter1FctfString
=====================
*/
static void CG_DrawCenter1FctfString( void ) {
    #ifndef MISSIONPACK
    int		x, y, w;
    float       *color;
    char        *line;
    int status;
    
    if(cgs.gametype != GT_1FCTF)
        return;
    
    status = cgs.flagStatus;
    
    //Sago: TODO: Find the proper defines instead of hardcoded values.
    switch(status)
    {
        case 2:
            line = va("Red has the flag!");
            color = colorRed;
            break;
        case 3:
            line = va("Blue has the flag!");
            color = colorBlue;
            break;
        case 4:
            line = va("Flag dropped!");
            color = colorWhite;
            break;
        default:
            return;
            
    };
    y = 100;
    
    
    w = cg.centerPrintCharWidth * CG_DrawStrlen( line );

    x = ( SCREEN_WIDTH - w ) / 2;

    CG_DrawStringExt( x, y, line, color, qfalse, qtrue,
		cg.centerPrintCharWidth, (int)(cg.centerPrintCharWidth * 1.5), 0 );
    
    
    #endif
}



/*
=====================
CG_DrawCenterDDString
=====================
*/
static void CG_DrawCenterDDString( void ) {
	#ifndef MISSIONPACK
	int		x, y, w;
	float       *color;
	char        *line;
	int 		statusA, statusB;
	int sec;
	static int lastDDSec = -100;


	if(cgs.gametype != GT_DOUBLE_D)
		return;

	statusA = cgs.redflag;
	statusB = cgs.blueflag;

	if( ( ( statusB == statusA ) && ( statusA == TEAM_RED ) ) ||
		( ( statusB == statusA ) && ( statusA == TEAM_BLUE ) ) ) {
	}
	else {
		return; //No team is dominating
	}

	if(statusA == TEAM_BLUE) {
		line = va("Blue scores in %i",(cgs.timetaken+10*1000-cg.time)/1000+1);
		color = colorBlue;
	} else if(statusA == TEAM_RED) {
		line = va("Red scores in %i",(cgs.timetaken+10*1000-cg.time)/1000+1);
		color = colorRed;
	} else {
		lastDDSec = -100;
		return;
	}

	sec = (cgs.timetaken+10*1000-cg.time)/1000+1;
	if(sec!=lastDDSec) {
		//A new number is being displayed... play the sound!
		switch ( sec ) {
			case 1:
				trap_S_StartLocalSound( cgs.media.count1Sound, CHAN_ANNOUNCER );
				break;
			case 2:
				trap_S_StartLocalSound( cgs.media.count2Sound, CHAN_ANNOUNCER );
				break;
			case 3:
				trap_S_StartLocalSound( cgs.media.count3Sound, CHAN_ANNOUNCER );
				break;
			case 10:
				trap_S_StartLocalSound( cgs.media.doublerSound , CHAN_ANNOUNCER );
				break;
			default:
				break;
		}
	}
	lastDDSec = sec;

	y = 100;


	w = cg.centerPrintCharWidth * CG_DrawStrlen( line );

	x = ( SCREEN_WIDTH - w ) / 2;

	CG_DrawStringExt( x, y, line, color, qfalse, qtrue,
		cg.centerPrintCharWidth, (int)(cg.centerPrintCharWidth * 1.5), 0 );

	#endif
}

/*
================================================================================

CROSSHAIR

================================================================================
*/


/*
=================
CG_DrawCrosshair
=================
*/
static void CG_DrawCrosshair(void)
{
	float		w, h;
	qhandle_t	hShader;
	float		f;
	float		x, y;
	int			ca = 0; //only to get rid of the warning(not useful)
	int 		currentWeapon;
	
	currentWeapon = cg.predictedPlayerState.weapon;

	if ( !cg_drawCrosshair.integer ) {
		return;
	}

	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR) {
		return;
	}

	if ( cg.renderingThirdPerson ) {
		return;
	}

	// set color based on health
	if ( cg_crosshairHealth.integer ) {
		vec4_t		hcolor;

		CG_ColorForHealth( hcolor );
		trap_R_SetColor( hcolor );
	} else {
                vec4_t         color;
                color[0]=cg_crosshairColorRed.value;
                color[1]=cg_crosshairColorGreen.value;
                color[2]=cg_crosshairColorBlue.value;
                color[3]=1.0f;
		trap_R_SetColor( color );
	}

	if( cg_differentCrosshairs.integer == 1 ){
		switch( currentWeapon ){
			case 1:
				w = h = cg_ch1size.value;
				ca = cg_ch1.integer;
				break;
			case 2:
				w = h = cg_ch2size.value;
				ca = cg_ch2.integer;
				break;
			case 3:
				w = h = cg_ch3size.value;
				ca = cg_ch3.integer;
				break;
			case 4:
				w = h = cg_ch4size.value;
				ca = cg_ch4.integer;
				break;
			case 5:
				w = h = cg_ch5size.value;
				ca = cg_ch5.integer;
				break;
			case 6:
				w = h = cg_ch6size.value;
				ca = cg_ch6.integer;
				break;
			case 7:
				w = h = cg_ch7size.value;
				ca = cg_ch7.integer;
				break;
			case 8:
				w = h = cg_ch8size.value;
				ca = cg_ch8.integer;
				break;
			case 9:
				w = h = cg_ch9size.value;
				ca = cg_ch9.integer;
				break;
			case 10:
				w = h = cg_ch10size.value;
				ca = cg_ch10.integer;
				break;
			case 11:
				w = h = cg_ch11size.value;
				ca = cg_ch11.integer;
				break;
			case 12:
				w = h = cg_ch12size.value;
				ca = cg_ch12.integer;
				break;
			case 13:
				w = h = cg_ch13size.value;
				ca = cg_ch13.integer;
				break;
                        default:
                                w = h = cg_crosshairSize.value;
                                ca = cg_drawCrosshair.integer;
                                break;
		}
	}
	else{
		w = h = cg_crosshairSize.value;
		ca = cg_drawCrosshair.integer;
	}
	
	if( cg_crosshairPulse.integer ){
		// pulse the size of the crosshair when picking up items
		f = cg.time - cg.itemPickupBlendTime;
		if ( f > 0 && f < ITEM_BLOB_TIME ) {
			f /= ITEM_BLOB_TIME;
			w *= ( 1 + f );
			h *= ( 1 + f );
		}
	}

	x = cg_crosshairX.integer;
	y = cg_crosshairY.integer;
	CG_AdjustFrom640( &x, &y, &w, &h );

	if (ca < 0) {
		ca = 0;
	}
	hShader = cgs.media.crosshairShader[ ca % NUM_CROSSHAIRS ];

        if(!hShader)
            hShader = cgs.media.crosshairShader[ ca % 10 ];

	trap_R_DrawStretchPic( x + cg.refdef.x + 0.5 * (cg.refdef.width - w), 
		y + cg.refdef.y + 0.5 * (cg.refdef.height - h), 
		w, h, 0, 0, 1, 1, hShader );
}

/*
=================
CG_DrawCrosshair3D
=================
*/
static void CG_DrawCrosshair3D(void)
{
	float		w, h;
	qhandle_t	hShader;
	float		f;
	int			ca;

	trace_t trace;
	vec3_t endpos;
	float stereoSep, zProj, maxdist, xmax;
	char rendererinfos[128];
	refEntity_t ent;

	if ( !cg_drawCrosshair.integer ) {
		return;
	}

	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR) {
		return;
	}

	if ( cg.renderingThirdPerson ) {
		return;
	}

	w = h = cg_crosshairSize.value;

	// pulse the size of the crosshair when picking up items
	f = cg.time - cg.itemPickupBlendTime;
	if ( f > 0 && f < ITEM_BLOB_TIME ) {
		f /= ITEM_BLOB_TIME;
		w *= ( 1 + f );
		h *= ( 1 + f );
	}

	ca = cg_drawCrosshair.integer;
	if (ca < 0) {
		ca = 0;
	}
	hShader = cgs.media.crosshairShader[ ca % NUM_CROSSHAIRS ];

        if(!hShader)
            hShader = cgs.media.crosshairShader[ ca % 10 ];

	// Use a different method rendering the crosshair so players don't see two of them when
	// focusing their eyes at distant objects with high stereo separation
	// We are going to trace to the next shootable object and place the crosshair in front of it.

	// first get all the important renderer information
	trap_Cvar_VariableStringBuffer("r_zProj", rendererinfos, sizeof(rendererinfos));
	zProj = atof(rendererinfos);
	trap_Cvar_VariableStringBuffer("r_stereoSeparation", rendererinfos, sizeof(rendererinfos));
	stereoSep = zProj / atof(rendererinfos);
	
	xmax = zProj * tan(cg.refdef.fov_x * M_PI / 360.0f);
	
	// let the trace run through until a change in stereo separation of the crosshair becomes less than one pixel.
	maxdist = cgs.glconfig.vidWidth * stereoSep * zProj / (2 * xmax);
	VectorMA(cg.refdef.vieworg, maxdist, cg.refdef.viewaxis[0], endpos);
	CG_Trace(&trace, cg.refdef.vieworg, NULL, NULL, endpos, 0, MASK_SHOT);
	
	memset(&ent, 0, sizeof(ent));
	ent.reType = RT_SPRITE;
	ent.renderfx = RF_DEPTHHACK | RF_CROSSHAIR;
	
	VectorCopy(trace.endpos, ent.origin);
	
	// scale the crosshair so it appears the same size for all distances
	ent.radius = w / 640 * xmax * trace.fraction * maxdist / zProj;
	ent.customShader = hShader;

	trap_R_AddRefEntityToScene(&ent);
}



/*
=================
CG_ScanForCrosshairEntity
=================
*/
static void CG_ScanForCrosshairEntity( void ) {
	trace_t		trace;
	vec3_t		start, end;
	int			content;

	VectorCopy( cg.refdef.vieworg, start );
	VectorMA( start, 131072, cg.refdef.viewaxis[0], end );

	CG_Trace( &trace, start, vec3_origin, vec3_origin, end, 
		cg.snap->ps.clientNum, CONTENTS_SOLID|CONTENTS_BODY );
	if ( trace.entityNum >= MAX_CLIENTS ) {
		return;
	}

	// if the player is in fog, don't show it
	content = CG_PointContents( trace.endpos, 0 );
	if ( content & CONTENTS_FOG ) {
		return;
	}

	// if the player is invisible, don't show it
	if ( cg_entities[ trace.entityNum ].currentState.powerups & ( 1 << PW_INVIS ) ) {
		return;
	}

	// update the fade timer
	cg.crosshairClientNum = trace.entityNum;
	cg.crosshairClientTime = cg.time;
}


/*
=====================
CG_DrawCrosshairNames
=====================
*/
static void CG_DrawCrosshairNames( void ) {
	float		*color;
	float		enemyColor[4];
	char		*name;
	float		w;

	if ( !cg_drawCrosshair.integer ) {
		return;
	}
	if ( !cg_drawCrosshairNames.integer ) {
		return;
	}
	if ( cg.renderingThirdPerson ) {
		return;
	}

	// scan the known entities to see if the crosshair is sighted on one
	CG_ScanForCrosshairEntity();

	// draw the name of the player being looked at
	color = CG_FadeColor( cg.crosshairClientTime, 750 );
	if ( !color ) {
		trap_R_SetColor( NULL );
		return;
	}

	name = cgs.clientinfo[ cg.crosshairClientNum ].name;
#ifdef MISSIONPACK
	color[3] *= 0.5f;
	w = CG_Text_Width(name, 0.3f, 0);
	CG_Text_Paint( 320 - w / 2, 190, 0.3f, color, name, 0, 0, ITEM_TEXTSTYLE_SHADOWED);
#else
	w = CG_DrawStrlen( name ) * SMALLCHAR_WIDTH;
	if ( cgs.clientinfo[ cg.crosshairClientNum ].team == cg.snap->ps.persistant[PERS_TEAM] && cgs.clientinfo[ cg.crosshairClientNum ].team != TEAM_FREE ) {
		CG_DrawSmallString( 320 - w / 2, 250, name, color[3] * 0.5f );
	} else {
		enemyColor[0] = 1.0f;
		enemyColor[1] = 0.5f;
		enemyColor[2] = 0.5f;
		enemyColor[3] = 0.5f;
		CG_DrawSmallStringColor( 320 - w / 2, 250, name, enemyColor );
	}
#endif
	trap_R_SetColor( NULL );
}


//==============================================================================

/*
=================
CG_DrawSpectator
=================
*/
static void CG_DrawSpectator(void) {
	CG_DrawBigString(320 - 9 * 8, 440, "SPECTATOR", 1.0F);
	if ( cgs.gametype == GT_TOURNAMENT ) {
		CG_DrawMediumString(320 - 15 * 6, 460, "waiting to play", 1.0F);
	}
	else if ( cgs.gametype >= GT_TEAM && cgs.ffa_gt!=1 && !cg.scoreBoardShowing ) {
		CG_DrawStringExt(320 - 39 * 4, 460, "press ESC and use the JOIN menu to play", colorWhite, qfalse, qtrue, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0 );
	}
}

/*
=================
CG_DrawVote
=================
*/
static void CG_DrawVote(void) {
	char	*s;
	int		sec;

	if ( !cgs.voteTime ) {
		return;
	}

	// play a talk beep whenever it is modified
	if ( cgs.voteModified ) {
		cgs.voteModified = qfalse;
		trap_S_StartLocalSound( cgs.media.talkSound, CHAN_LOCAL_SOUND );
	}

	sec = ( VOTE_TIME - ( cg.time - cgs.voteTime ) ) / 1000;
	if ( sec < 0 ) {
		sec = 0;
	}
#ifdef MISSIONPACK
	s = va("VOTE(%i):%s yes:%i no:%i", sec, cgs.voteString, cgs.voteYes, cgs.voteNo);
	CG_DrawSmallString( 0, 58, s, 1.0F );
	s = "or press ESC then click Vote";
	CG_DrawSmallString( 0, 67 + SMALLCHAR_HEIGHT + 2, s, 1.0F );
#else
	s = va("VOTE(%i):%s yes(F1):%i no(F2):%i", sec, cgs.voteString, cgs.voteYes, cgs.voteNo );
	CG_DrawSmallString( 0, 67, s, 1.0F );
#endif
}

/*
=================
CG_DrawTeamVote
=================
*/
static void CG_DrawTeamVote(void) {
	char	*s;
	int		sec, cs_offset;

	if ( cgs.clientinfo[cg.clientNum].team == TEAM_RED )
		cs_offset = 0;
	else if ( cgs.clientinfo[cg.clientNum].team == TEAM_BLUE )
		cs_offset = 1;
	else
		return;

	if ( !cgs.teamVoteTime[cs_offset] ) {
		return;
	}

	// play a talk beep whenever it is modified
	if ( cgs.teamVoteModified[cs_offset] ) {
		cgs.teamVoteModified[cs_offset] = qfalse;
		trap_S_StartLocalSound( cgs.media.talkSound, CHAN_LOCAL_SOUND );
	}

	sec = ( VOTE_TIME - ( cg.time - cgs.teamVoteTime[cs_offset] ) ) / 1000;
	if ( sec < 0 ) {
		sec = 0;
	}
	s = va("TEAMVOTE(%i):%s yes:%i no:%i", sec, cgs.teamVoteString[cs_offset],
							cgs.teamVoteYes[cs_offset], cgs.teamVoteNo[cs_offset] );
	CG_DrawSmallString( 0, 90, s, 1.0F );
}


static qboolean CG_DrawScoreboard( void ) {
#ifdef MISSIONPACK
	static qboolean firstTime = qtrue;
	float fade, *fadeColor;

	if (menuScoreboard) {
		menuScoreboard->window.flags &= ~WINDOW_FORCED;
	}
	if (cg_paused.integer) {
		cg.deferredPlayerLoading = 0;
		firstTime = qtrue;
		return qfalse;
	}

	// should never happen in Team Arena
	if (cgs.gametype == GT_SINGLE_PLAYER && cg.predictedPlayerState.pm_type == PM_INTERMISSION ) {
		cg.deferredPlayerLoading = 0;
		firstTime = qtrue;
		return qfalse;
	}

	// don't draw scoreboard during death while warmup up
	if ( cg.warmup && !cg.showScores ) {
		return qfalse;
	}

	if ( cg.showScores || cg.predictedPlayerState.pm_type == PM_DEAD || cg.predictedPlayerState.pm_type == PM_INTERMISSION ) {
		fade = 1.0;
		fadeColor = colorWhite;
	} else {
		fadeColor = CG_FadeColor( cg.scoreFadeTime, FADE_TIME );
		if ( !fadeColor ) {
			// next time scoreboard comes up, don't print killer
			cg.deferredPlayerLoading = 0;
			cg.killerName[0] = 0;
			firstTime = qtrue;
			return qfalse;
		}
		fade = *fadeColor;
	}																					  


	if (menuScoreboard == NULL) {
		if ( cgs.gametype >= GT_TEAM && cgs.ffa_gt!=1) {
			menuScoreboard = Menus_FindByName("teamscore_menu");
		} else {
			menuScoreboard = Menus_FindByName("score_menu");
		}
	}

	if (menuScoreboard) {
		if (firstTime) {
			CG_SetScoreSelection(menuScoreboard);
			firstTime = qfalse;
		}
		Menu_Paint(menuScoreboard, qtrue);
	}

	// load any models that have been deferred
	if ( ++cg.deferredPlayerLoading > 10 ) {
		CG_LoadDeferredPlayers();
	}

	return qtrue;
#else
        char        *s;
        int w;
        if(cg.respawnTime && cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR && (cgs.gametype < GT_ELIMINATION || cgs.gametype > GT_LMS) ) {
            if(cg.respawnTime>cg.time) {
                s = va("Respawn in: %2.2f",((double)cg.respawnTime-(double)cg.time)/1000.0);
                w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
                CG_DrawSmallStringColor(320-w/2,400, s, colorYellow);
            } else {
                s = va("Click FIRE to respawn");
                w = CG_DrawStrlen( s ) * SMALLCHAR_WIDTH;
                CG_DrawSmallStringColor(320-w/2,400, "Click FIRE to respawn", colorGreen);
            }
        }
	return CG_DrawOldScoreboard();
#endif
}

#define ACCBOARD_XPOS 500
#define ACCBOARD_YPOS 150
#define ACCBOARD_HEIGHT 20
#define ACCBOARD_WIDTH 75
#define ACCITEM_SIZE 16

qboolean CG_DrawAccboard( void ) {
        int counter, i;

        i = 0;

        if( !cg.showAcc ){
                return qfalse;
        }
        trap_R_SetColor( colorWhite );

        for( counter = 0; counter < WP_NUM_WEAPONS ; counter++ ){
                if( cg_weapons[counter+2].weaponIcon && counter != WP_PROX_LAUNCHER && counter != WP_GRAPPLING_HOOK )
                        i++;
        }

        CG_DrawTeamBackground( ACCBOARD_XPOS, ACCBOARD_YPOS, ACCBOARD_WIDTH, ACCBOARD_HEIGHT*(i + 1), 0.33f, TEAM_BLUE );

        i = 0;

        for( counter = 0 ; counter < WP_NUM_WEAPONS ; counter++ ){
                if( cg_weapons[counter+2].weaponIcon && counter != WP_PROX_LAUNCHER && counter != WP_GRAPPLING_HOOK ){
                        CG_DrawPic( ACCBOARD_XPOS + 10, ACCBOARD_YPOS + 10 +i*ACCBOARD_HEIGHT, ACCITEM_SIZE, ACCITEM_SIZE, cg_weapons[counter+2].weaponIcon );
                        if( cg.accuracys[counter][0] > 0 )
                                CG_DrawSmallStringColor(ACCBOARD_XPOS + 10 + ACCITEM_SIZE + 10, ACCBOARD_YPOS + 10 +i*ACCBOARD_HEIGHT + ACCITEM_SIZE/2 - SMALLCHAR_HEIGHT/2 ,
                                         va("%i%s",(int)(((float)cg.accuracys[counter][1]*100)/((float)(cg.accuracys[counter][0]))),"%"), colorWhite);
                        else
                                CG_DrawSmallStringColor(ACCBOARD_XPOS + 10 + ACCITEM_SIZE + 10, ACCBOARD_YPOS + 10 +i*ACCBOARD_HEIGHT + ACCITEM_SIZE/2 - SMALLCHAR_HEIGHT/2 , "-%", colorWhite);
                        i++;
                }
        }

        trap_R_SetColor(NULL);
        return qtrue;
}



/*
=================
CG_DrawIntermission
=================
*/
static void CG_DrawIntermission( void ) {
//	int key;
#ifdef MISSIONPACK
	//if (cg_singlePlayer.integer) {
	//	CG_DrawCenterString();
	//	return;
	//}
#else
	if ( cgs.gametype == GT_SINGLE_PLAYER ) {
		CG_DrawCenterString();
		return;
	}
#endif
	cg.scoreFadeTime = cg.time;
	cg.scoreBoardShowing = CG_DrawScoreboard();
}

/*
=================
CG_DrawFollow
=================
*/
static qboolean CG_DrawFollow( void ) {
	float		x;
	vec4_t		color;
	const char	*name;

	if ( !(cg.snap->ps.pm_flags & PMF_FOLLOW) ) {
		return qfalse;
	}

	if ( cg.scoreBoardShowing ) {
		return qfalse;
	}
	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;


	name = cgs.clientinfo[ cg.snap->ps.clientNum ].name;

	x = 0.5 * ( 640 - SMALLCHAR_WIDTH * CG_DrawStrlen( name ) ) - SMALLCHAR_WIDTH * 3;

	CG_DrawStringExt( x, 40, name, color, qtrue, qfalse, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0 );

	CG_DrawSmallString( x + SMALLCHAR_WIDTH * CG_DrawStrlen( name ), 40, "'s view", 1.0F);

	return qtrue;
}



/*
=================
CG_DrawAmmoWarning
=================
*/
static void CG_DrawAmmoWarning( void ) {
	const char	*s;
	int			w;

	//Don't report in instant gib same with RA
	if(cgs.nopickup)
		return;

	if ( cg_drawAmmoWarning.integer == 0 ) {
		return;
	}

	if ( !cg.lowAmmoWarning ) {
		return;
	}

	if ( cg.lowAmmoWarning == 2 ) {
		s = "OUT OF AMMO";
	} else {
		s = "LOW AMMO WARNING";
	}
	w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
	CG_DrawBigString(320 - w / 2, 64, s, 1.0F);
}


//#ifdef MISSIONPACK
/*
=================
CG_DrawProxWarning
=================
*/
static void CG_DrawProxWarning( void ) {
	char s [32];
	int			w;
  static int proxTime;
  static int proxCounter;
  static int proxTick;

	if( !(cg.snap->ps.eFlags & EF_TICKING ) ) {
    proxTime = 0;
		return;
	}

  if (proxTime == 0) {
    proxTime = cg.time + 5000;
    proxCounter = 5;
    proxTick = 0;
  }

  if (cg.time > proxTime) {
    proxTick = proxCounter--;
    proxTime = cg.time + 1000;
  }

  if (proxTick != 0) {
    Com_sprintf(s, sizeof(s), "INTERNAL COMBUSTION IN: %i", proxTick);
  } else {
    Com_sprintf(s, sizeof(s), "YOU HAVE BEEN MINED");
  }

	w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
	CG_DrawBigStringColor( 320 - w / 2, 64 + BIGCHAR_HEIGHT, s, g_color_table[ColorIndex(COLOR_RED)] );
}
//#endif


/*
=================
CG_DrawWarmup
=================
*/
static void CG_DrawWarmup( void ) {
	int			w;
	int			sec;
	int			i;
	float scale __attribute__ ((unused));
	clientInfo_t	*ci1, *ci2;
	int			cw;
	const char	*s;

	sec = cg.warmup;
	if ( !sec ) {
		return;
	}

	if ( sec < 0 ) {
		s = "Warmup";		
		w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
		CG_DrawStringExt(320 - w / 2, 27, s, colorWhite, qfalse, qfalse, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0);
		cg.warmupCount = 0;
		return;
	}

	if (cgs.gametype == GT_TOURNAMENT) {
		// find the two active players
		ci1 = NULL;
		ci2 = NULL;
		for ( i = 0 ; i < cgs.maxclients ; i++ ) {
			if ( cgs.clientinfo[i].infoValid && cgs.clientinfo[i].team == TEAM_FREE ) {
				if ( !ci1 ) {
					ci1 = &cgs.clientinfo[i];
				} else {
					ci2 = &cgs.clientinfo[i];
				}
			}
		}

		if ( ci1 && ci2 ) {
			s = va( "%s^7 vs %s", ci1->name, ci2->name );
#ifdef MISSIONPACK
			w = CG_Text_Width(s, 0.6f, 0);
			CG_Text_Paint(320 - w / 2, 60, 0.6f, colorWhite, s, 0, 0, ITEM_TEXTSTYLE_SHADOWEDMORE);
#else
			w = CG_DrawStrlen( s );
			if ( w > 640 / BIGCHAR_WIDTH ) {
				cw = 640 / w;
			} else {
				cw = BIGCHAR_WIDTH;
			}
			CG_DrawStringExt( 320 - w * cw/2, 27,s, colorWhite, 
					qfalse, qtrue, cw, (int)(cw * 1.5f), 0 );
#endif
		}
	}

	sec = ( sec - cg.time ) / 1000;
	if ( sec < 0 ) {
		cg.warmup = 0;
		sec = 0;
	}
	s = va( "Starts in: %i", sec + 1 );
	if ( sec != cg.warmupCount ) {
		cg.warmupCount = sec;
		switch ( sec ) {
		case 0:
			trap_S_StartLocalSound( cgs.media.count1Sound, CHAN_ANNOUNCER );
			break;
		case 1:
			trap_S_StartLocalSound( cgs.media.count2Sound, CHAN_ANNOUNCER );
			break;
		case 2:
			trap_S_StartLocalSound( cgs.media.count3Sound, CHAN_ANNOUNCER );
			break;
		default:
			break;
		}
	}
	scale = 0.45f;
	switch ( cg.warmupCount ) {
	case 0:
		cw = 22;
		scale = 0.54f;
		break;
	case 1:
		cw = 20;
		scale = 0.51f;
		break;
	case 2:
		cw = 18;
		scale = 0.48f;
		break;
	default:
		cw = 16;
		scale = 0.45f;
		break;
	}

	if ( cgs.gametype == GT_TOURNAMENT ) {
		w = CG_DrawStrlen( s );
		CG_DrawStringExt( 320 - w * cw/2, 57, s, colorWhite, 
				qfalse, qtrue, cw, (int)(cw * 1.5), 0 );
	} else {
		w = CG_DrawStrlen( s );
		CG_DrawStringExt( 320 - w * cw/2, 27, s, colorWhite, 
				qfalse, qtrue, cw, (int)(cw * 1.5), 0 );
	}
}

//==================================================================================
#ifdef MISSIONPACK
/* 
=================
CG_DrawTimedMenus
=================
*/
void CG_DrawTimedMenus( void ) {
	if (cg.voiceTime) {
		int t = cg.time - cg.voiceTime;
		if ( t > 2500 ) {
			Menus_CloseByName("voiceMenu");
			trap_Cvar_Set("cl_conXOffset", "0");
			cg.voiceTime = 0;
		}
	}
}
#endif
/*
=================
CG_Draw2D
=================
*/
static void CG_Draw2D(stereoFrame_t stereoFrame)
{
#ifdef MISSIONPACK
	if (cgs.orderPending && cg.time > cgs.orderTime) {
		CG_CheckOrderPending();
	}
#endif
	// if we are taking a levelshot for the menu, don't draw anything
	if ( cg.levelShot ) {
		return;
	}

	if ( cg_draw2D.integer == 0 ) {
		return;
	}

	if ( cg.snap->ps.pm_type == PM_INTERMISSION ) {
		CG_DrawIntermission();
		return;
	}

/*
	if (cg.cameraMode) {
		return;
	}
*/
	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR /*|| cg.snap->ps.pm_type == PM_SPECTATOR*/ ) {
		CG_DrawSpectator();

		if(stereoFrame == STEREO_CENTER)
			CG_DrawCrosshair();

		CG_DrawCrosshairNames();
	} else {
		// don't draw any status if dead or the scoreboard is being explicitly shown
		if ( !cg.showScores && cg.snap->ps.stats[STAT_HEALTH] > 0 ) {

#ifdef MISSIONPACK
			if ( cg_drawStatus.integer ) {
				Menu_PaintAll();
				CG_DrawTimedMenus();
			}
#else
			CG_DrawStatusBar();
#endif
      
			CG_DrawAmmoWarning();

			CG_DrawProxWarning();
			if(stereoFrame == STEREO_CENTER)
				CG_DrawCrosshair();
			CG_DrawCrosshairNames();
			CG_DrawWeaponSelect();

                        #ifndef MISSIONPACK
			CG_DrawHoldableItem();
			CG_DrawPersistantPowerup();
			#endif

                        CG_DrawReward();
		}
    
		if ( cgs.gametype >= GT_TEAM && cgs.ffa_gt!=1) {
#ifndef MISSIONPACK
			CG_DrawTeamInfo();
#endif
		}
	}

	CG_DrawVote();
	CG_DrawTeamVote();

	CG_DrawLagometer();

#ifdef MISSIONPACK
	if (!cg_paused.integer) {
		CG_DrawUpperRight(stereoFrame);
	}
#else
	CG_DrawUpperRight(stereoFrame);
#endif

#ifndef MISSIONPACK
	CG_DrawLowerRight();
	CG_DrawLowerLeft();
#endif

	// don't draw center string if scoreboard is up
	cg.scoreBoardShowing = CG_DrawScoreboard();
	if ( !cg.scoreBoardShowing) {
                CG_DrawCenterDDString();
                CG_DrawCenter1FctfString();
		CG_DrawCenterString();

		if ( cgs.clientinfo[cg.clientNum].team != TEAM_SPECTATOR )
			CG_DrawReady();

		CG_DrawFragMessage();

		if ( !CG_DrawFollow() ) {
			CG_DrawWarmup();
		}
	}

        cg.accBoardShowing = CG_DrawAccboard();
}


static void CG_DrawTourneyScoreboard( void ) {
#ifdef MISSIONPACK
#else
	CG_DrawOldTourneyScoreboard();
#endif
}

/*
=====================
CG_DrawActive

Perform all drawing needed to completely fill the screen
=====================
*/
void CG_DrawActive( stereoFrame_t stereoView ) {
	// optionally draw the info screen instead
	if ( !cg.snap ) {
		CG_DrawInformation();
		return;
	}

	// optionally draw the tournement scoreboard instead
	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR &&
		( cg.snap->ps.pm_flags & PMF_SCOREBOARD ) ) {
		CG_DrawTourneyScoreboard();
		return;
	}

	// clear around the rendered view if sized down
	CG_TileClear();

	if(stereoView != STEREO_CENTER)
		CG_DrawCrosshair3D();

	// draw 3D view
	trap_R_RenderScene( &cg.refdef );

	// draw status bar and other floating elements
 	CG_Draw2D(stereoView);
}



