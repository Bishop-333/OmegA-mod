/*
===========================================================================
Copyright (C) 2006 Neil Toronto.

This file is part of the Unlagged source code.

Unlagged source code is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Unlagged source code is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Unlagged source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

//#include "cg_local.h"

#include "cg_local.h"

// we'll need these prototypes
void CG_ShotgunPattern( vec3_t origin, vec3_t origin2, int seed, int otherEntNum );
void CG_Bullet( vec3_t end, int sourceEntityNum, vec3_t normal, qboolean flesh, int fleshEntityNum );

// and this as well
//Must be in sync with g_weapon.c
#define MACHINEGUN_SPREAD 200
#define CHAINGUN_SPREAD 600

/*
=======================
CG_PredictWeaponEffects

Draws predicted effects for the railgun, shotgun, and machinegun. The
lightning gun is done in CG_LightningBolt, since it was just a matter
of setting the right origin and angles.
=======================
*/
void CG_PredictWeaponEffects( centity_t *cent ) {
	vec3_t muzzlePoint, forward, right, up;
	entityState_t *ent = &cent->currentState;

	// if the client isn't us, forget it
	if ( cent->currentState.number != cg.predictedPlayerState.clientNum ) {
		return;
	}

	// if it's not switched on server-side, forget it
	if ( !cgs.delagHitscan ) {
		return;
	}

	// get the muzzle point
	VectorCopy( cg.predictedPlayerState.origin, muzzlePoint );
	muzzlePoint[2] += cg.predictedPlayerState.viewheight;

	// get forward, right, and up
	AngleVectors( cg.predictedPlayerState.viewangles, forward, right, up );
	VectorMA( muzzlePoint, 14, forward, muzzlePoint );

	// was it a rail attack?
	if ( ent->weapon == WP_RAILGUN ) {
		// do we have it on for the rail gun?
		if ( cg_delag.integer & 1 || cg_delag.integer & 16 ) {
			trace_t trace;
			vec3_t endPoint;

			// trace forward
			VectorMA( muzzlePoint, 8192, forward, endPoint );

			// find the rail's end point
			CG_Trace( &trace, muzzlePoint, vec3_origin, vec3_origin, endPoint, cg.predictedPlayerState.clientNum, CONTENTS_SOLID );

			// do the magic-number adjustment
			VectorMA( muzzlePoint, 4, right, muzzlePoint );
			VectorMA( muzzlePoint, -1, up, muzzlePoint );

			if ( !cg.renderingThirdPerson ) {
				if ( cg_drawGun.integer == 2 )
					VectorMA( muzzlePoint, 8, cg.refdef.viewaxis[1], muzzlePoint );
				else if ( cg_drawGun.integer == 3 )
					VectorMA( muzzlePoint, 4, cg.refdef.viewaxis[1], muzzlePoint );
			}

			// draw a rail trail
			CG_RailTrail( &cgs.clientinfo[cent->currentState.number], muzzlePoint, trace.endpos );

			// explosion at end if not SURF_NOIMPACT
			if ( !( trace.surfaceFlags & SURF_NOIMPACT ) ) {
				// predict an explosion
				CG_MissileHitWall( ent->weapon, cg.predictedPlayerState.clientNum, trace.endpos, trace.plane.normal, IMPACTSOUND_DEFAULT );
			}
		}
	}
	// was it a shotgun attack?
	else if ( ent->weapon == WP_SHOTGUN ) {
		// do we have it on for the shotgun?
		if ( cg_delag.integer & 1 || cg_delag.integer & 4 ) {
			int contents;
			vec3_t endPoint, v;

			// do everything like the server does

			SnapVector( muzzlePoint );

			VectorScale( forward, 4096, endPoint );
			SnapVector( endPoint );

			VectorSubtract( endPoint, muzzlePoint, v );
			VectorNormalize( v );
			VectorScale( v, 32, v );
			VectorAdd( muzzlePoint, v, v );

			if ( cgs.glconfig.hardwareType != GLHW_RAGEPRO ) {
				// ragepro can't alpha fade, so don't even bother with smoke
				vec3_t up;

				contents = trap_CM_PointContents( muzzlePoint, 0 );
				if ( !( contents & CONTENTS_WATER ) ) {
					VectorSet( up, 0, 0, 8 );
					CG_SmokePuff( v, up, 32, 1, 1, 1, 0.33f, 900, cg.time, 0, LEF_PUFF_DONT_SCALE, cgs.media.shotgunSmokePuffShader );
				}
			}

			// do the shotgun pellets
			CG_ShotgunPattern( muzzlePoint, endPoint, cg.oldTime % 256, cg.predictedPlayerState.clientNum );
		}
	}
	// was it a machinegun attack?
	else if ( ent->weapon == WP_MACHINEGUN ) {
		// do we have it on for the machinegun?
		if ( cg_delag.integer & 1 || cg_delag.integer & 2 ) {
			// the server will use this exact time (it'll be serverTime on that end)
			int seed = cg.oldTime % 256;
			float r, u;
			trace_t tr;
			qboolean flesh;
			int fleshEntityNum = 0;
			vec3_t endPoint;

			// do everything exactly like the server does

			r = Q_random( &seed ) * M_PI * 2.0f;
			u = sin( r ) * Q_crandom( &seed ) * MACHINEGUN_SPREAD * 16;
			r = cos( r ) * Q_crandom( &seed ) * MACHINEGUN_SPREAD * 16;

			VectorMA( muzzlePoint, 8192 * 16, forward, endPoint );
			VectorMA( endPoint, r, right, endPoint );
			VectorMA( endPoint, u, up, endPoint );

			CG_Trace( &tr, muzzlePoint, NULL, NULL, endPoint, cg.predictedPlayerState.clientNum, MASK_SHOT );

			if ( tr.surfaceFlags & SURF_NOIMPACT ) {
				return;
			}

			// snap the endpos to integers, but nudged towards the line
			SnapVectorTowards( tr.endpos, muzzlePoint );

			// do bullet impact
			if ( tr.entityNum < MAX_CLIENTS ) {
				flesh = qtrue;
				fleshEntityNum = tr.entityNum;
			} else {
				flesh = qfalse;
			}

			// do the bullet impact
			CG_Bullet( tr.endpos, cg.predictedPlayerState.clientNum, tr.plane.normal, flesh, fleshEntityNum );
		}
	}
	// was it a chaingun attack?
	else if ( ent->weapon == WP_CHAINGUN ) {
		// do we have it on for the machinegun?
		if ( cg_delag.integer & 1 || cg_delag.integer & 2 ) {
			// the server will use this exact time (it'll be serverTime on that end)
			int seed = cg.oldTime % 256;
			float r, u;
			trace_t tr;
			qboolean flesh;
			int fleshEntityNum = 0;
			vec3_t endPoint;

			// do everything exactly like the server does

			r = Q_random( &seed ) * M_PI * 2.0f;
			u = sin( r ) * Q_crandom( &seed ) * CHAINGUN_SPREAD * 16;
			r = cos( r ) * Q_crandom( &seed ) * CHAINGUN_SPREAD * 16;

			VectorMA( muzzlePoint, 8192 * 16, forward, endPoint );
			VectorMA( endPoint, r, right, endPoint );
			VectorMA( endPoint, u, up, endPoint );

			CG_Trace( &tr, muzzlePoint, NULL, NULL, endPoint, cg.predictedPlayerState.clientNum, MASK_SHOT );

			if ( tr.surfaceFlags & SURF_NOIMPACT ) {
				return;
			}

			// snap the endpos to integers, but nudged towards the line
			SnapVectorTowards( tr.endpos, muzzlePoint );

			// do bullet impact
			if ( tr.entityNum < MAX_CLIENTS ) {
				flesh = qtrue;
				fleshEntityNum = tr.entityNum;
			} else {
				flesh = qfalse;
			}

			// do the bullet impact
			CG_Bullet( tr.endpos, cg.predictedPlayerState.clientNum, tr.plane.normal, flesh, fleshEntityNum );
		}
	}
}

/*
================
CG_Cvar_ClampInt

Clamps a cvar between two integer values, returns qtrue if it had to.
================
*/
qboolean CG_Cvar_ClampInt( const char *name, vmCvar_t *vmCvar, int min, int max ) {
	if ( vmCvar->integer > max ) {
		CG_Printf( "Allowed values are %d to %d.\n", min, max );

		Com_sprintf( vmCvar->string, MAX_CVAR_VALUE_STRING, "%d", max );
		vmCvar->value = max;
		vmCvar->integer = max;

		trap_Cvar_Set( name, vmCvar->string );
		return qtrue;
	}

	if ( vmCvar->integer < min ) {
		CG_Printf( "Allowed values are %d to %d.\n", min, max );

		Com_sprintf( vmCvar->string, MAX_CVAR_VALUE_STRING, "%d", min );
		vmCvar->value = min;
		vmCvar->integer = min;

		trap_Cvar_Set( name, vmCvar->string );
		return qtrue;
	}

	return qfalse;
}
