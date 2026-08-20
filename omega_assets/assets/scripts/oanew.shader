lowShotgunFlash
{
	deformVertexes autosprite
	{
		map models/weapons2/shotgun/shotgun_flash
		blendfunc add
	}
}

lowMachgunFlash
{
	deformVertexes autosprite
	{
		map models/weapons2/machinegun/f_machinegun
		blendfunc add
	}
}

lowPlasmaaFlash
{
	deformVertexes autosprite
	{
		map models/weapons2/plasma/f_plasma
		blendfunc add
	}
}

lowRocketlFlash
{
	deformVertexes autosprite
	{
		map models/weapons2/rocketl/f_rocketl
		blendfunc add
	}
}

lowGrenadeFlash
{
	deformVertexes autosprite
	{
		map models/weapons2/grenadel/f_grenadel
		blendfunc add
	}
}

lowRailgunFlash
{
	deformVertexes autosprite
	{
		map models/weapons2/railgun/f_railgun2
		blendfunc add
		rgbGen entity
	}
}

lapscrn
{
	tessSize 64
	{
		map models/mapobjects/laptop/lapscrn
	}
	{
		map models/mapobjects/laptop/invert
		blendfunc gl_one_minus_dst_color gl_one_minus_src_color
		tcGen environment 
	}
}

lowLightnnFlash
{
	deformVertexes autosprite
	{
		map models/weapons2/lightning/f_lightning
		blendfunc add
		tcMod rotate 675756
	}
}

LightnnFlash
{
	cull disable
	{
		animmap 20 models/weapons2/lightning/muzzle1 models/weapons2/lightning/muzzle2 models/weapons2/lightning/muzzle3 
		blendfunc gl_one gl_src_alpha
		rgbGen wave inversesawtooth 0 1 0 20 
	}
	{
		animmap 20 models/weapons2/lightning/muzzle2 models/weapons2/lightning/muzzle3 models/weapons2/lightning/muzzle1 
		blendfunc gl_one gl_src_alpha
		rgbGen wave sawtooth 0 1 0 20 
	}
}

// sawtooth stretch 0 values result in ugly clamping
textures/effects/jumpcirc
{
	q3map_lightimage textures/effects/jumpcirc
	q3map_surfacelight 466
	{
		clampmap textures/effects/jumpcirc
		tcMod stretch sawtooth 0.5 1 0 1 
		tcMod rotate 75
	}
	{
		clampmap textures/effects/jumpcirc
		blendfunc add
		tcMod stretch sawtooth 0.5 1 0 1 
		tcMod rotate -120
	}
}

// textures/effects/jumpcircblue is the same as textures/ctf/blue_telep
// sawtooth stretch 0 values result in ugly clamping
textures/effects/jumpcircblue
{
	q3map_lightimage textures/effects/jumpcircblue
	q3map_surfacelight 466
	{
		clampmap textures/effects/jumpcircblue
		tcMod stretch sawtooth 0.5 1 0 1 
		tcMod rotate 75
	}
	{
		clampmap textures/effects/jumpcircblue
		blendfunc add
		tcMod stretch sawtooth 0.5 1 0 1 
		tcMod rotate -120
	}
}

// textures/effects/jumpcircblue is the same as textures/ctf/blue_telep
// sawtooth stretch 0 values result in ugly clamping
textures/effects/jumpcircred
{
	q3map_lightimage textures/effects/jumpcircred
	q3map_surfacelight 466
	{
		clampmap textures/effects/jumpcircred
		tcMod stretch sawtooth 0.5 1 0 1 
		tcMod rotate 75
	}
	{
		clampmap textures/effects/jumpcircred
		blendfunc add
		tcMod stretch sawtooth 0.5 1 0 1 
		tcMod rotate -120
	}
}

textures/ctf_unified/floor_decal_blue
{
	cull disable
	{
		map textures/symbols/blueteam
		blendfunc add
	}
}

textures/ctf_unified/floor_decal_red
{
	cull disable
	{
		map textures/symbols/redteam.jpg
		blendfunc add
	}
}

textures/ctf_unified/monologo_flash_blue
{
	cull disable
	{
		map textures/symbols/blueteam.jpg
	}
}

textures/ctf_unified/monologo_flash_red
{
	cull disable
	{
		map textures/symbols/redteam
	}
}

textures/base_wall/glass01
{
	surfaceparm trans
	cull disable
	{
		map textures/effects/tinfx
		blendfunc add
		rgbGen identity
		tcGen environment 
	}
	{
		map textures/detail/d_met2
		blendfunc gl_dst_color gl_src_color
		tcMod scale 4 4
		detail
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
}

redArmor
{
	{
		map models/powerups/armor/redarmor
		rgbGen lightingDiffuse
	}
	{
		map textures/sfx/specular
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/powerups/armor/redarmor
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

yellowArmor
{
	{
		map models/powerups/armor/yellowarmor
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/spec/spots
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
	}
}

textures/base_floor/metfloor1
{
	surfaceparm metalsteps
	{
		map textures/base_floor/metfloor1
		rgbGen const ( 1 1 1 )
	}
	{
		clampmap textures/base_wall/chrome_env2
		blendfunc add
		rgbGen const ( 0.188235 0.188235 0.188235 )
		tcGen environment 
	}
	{
		map textures/base_floor/metfloor1
		blendfunc filter
		rgbGen const ( 0.737255 0.737255 0.737255 )
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
}

textures/base_trim/tinfx
{
	{
		map textures/base_trim/tinfx
		tcGen environment 
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
}

console
{
	nopicmip
	nomipmaps
        {
		map textures/omega/comp3textd
		blendFunc blend
		tcMod scroll 7.1  0.2
		tcmod scale .8 1
	}
        {
		map textures/omega/logo256.jpg
		blendFunc gl_one gl_one
		rgbGen wave sin 0 1 0 0.5 
	}
}

grassobj
{
	cull disable
	{
		map models/mapobjects/out/grass
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

ameatygib
{
	{
		map models/gibs/genericgibmeat
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/detail/d_sand
		blendfunc gl_dst_color gl_src_color
		rgbGen lightingDiffuse
		tcMod scale 8 8
		alphaGen lightingSpecular
		detail
	}
	{
		map models/gibs/gibmeatspec
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

oalogo
{
	{
		map textures/oa/water
		tcMod scroll 0.01 0.01
	}
	{
		map textures/oa/water
		blendfunc add
		tcMod scroll 0.04 0.01
	}
	{
		map textures/oa/water
		blendfunc add
		tcMod scroll -0.01 -0.02
	}
	{
		map textures/oa/flamelet
		tcMod scroll -0.2 0.4
	}
	{
		map textures/oa/flamelet
		blendfunc add
		tcMod scroll 0.2 0.7
	}
	{
		map textures/oa/flamelet
		blendfunc add
		tcMod scroll 0 0.6
	}
}

//REALLY COOL MENU BACKGROUNDY
menubacknologo_blueish
{
	{
		map textures/liquids/pool3d_3e
		rgbGen const ( 0.627451 0.5 0.796079 )
		tcMod scroll 0.05 0.05
	}
	{
		map textures/liquids/pool3d_3e
		blendfunc gl_dst_color gl_src_color
		rgbGen const ( 0.247059 0.6 0.721569 )
		tcMod scroll -0.02 0.05
		tcMod scale -1.1 0.8
	}
	{
		map gfx/fx/detail/d_ice
		blendfunc gl_dst_color gl_src_color
		tcMod scale 2 2
	}
	{
		map $whiteimage 
		blendfunc filter
		rgbGen const ( 0.121569 0.12549 0.152941 )
		tcMod scale 0.5 1
	}
}

//REALLY COOL MENU BACKGROUNDY
menuback_blueish
{
	{
		map textures/liquids/pool3d_3e
		rgbGen const ( 0.627451 0.5 0.796079 )
		tcMod scroll 0.05 0.05
	}
	{
		map textures/liquids/pool3d_3e
		blendfunc gl_dst_color gl_src_color
		rgbGen const ( 0.247059 0.6 0.721569 )
		tcMod scroll -0.02 0.05
		tcMod scale -1.1 0.8
	}
	{
		map gfx/fx/detail/d_ice
		blendfunc gl_dst_color gl_src_color
		tcMod scale 2 2
	}
	{
		map textures/sfx/logo256
		blendfunc filter
		tcMod scale 0 1
	}
}

//REALLY COOL MENU BACKGROUNDY
menuback
{
	{
		map gfx/fx/detail/d_sand
		rgbGen const ( 0.501961 0.501961 0.501961 )
		tcMod scroll 0.1 0.1
	}
	{
		map gfx/fx/detail/d_sand
		blendfunc gl_dst_color gl_src_color
		rgbGen const ( 0.141176 0.141176 0.141176 )
		tcMod scroll -0.04 0.1
		tcMod scale -1.1 0.8
	}
	{
		map gfx/fx/detail/d_ice
		blendfunc gl_dst_color gl_src_color
		tcMod scale 2 2
	}
}

//REALLY COOL MENU BACKGROUNDY
menubacknologo
{
	{
		map $whiteimage 
		rgbGen const ( 0 0 0 )
	}
}

boomzor
{
	deformVertexes autosprite
	{
		animmap 8 models/weaphits/rlboom/rlboom_1 models/weaphits/rlboom/rlboom_2 models/weaphits/rlboom/rlboom_3 models/weaphits/rlboom/rlboom_4 models/weaphits/rlboom/rlboom_5 models/weaphits/rlboom/rlboom_6 models/weaphits/rlboom/rlboom_7 models/weaphits/rlboom/rlboom_8 
		blendfunc gl_one gl_src_alpha
		rgbGen wave inversesawtooth 0 1 0 8 
	}
	{
		animmap 8 models/weaphits/rlboom/rlboom_2 models/weaphits/rlboom/rlboom_3 models/weaphits/rlboom/rlboom_4 models/weaphits/rlboom/rlboom_5 models/weaphits/rlboom/rlboom_6 models/weaphits/rlboom/rlboom_7 models/weaphits/rlboom/rlboom_8 models/weaphits/rlboom/rlboom_8 
		blendfunc gl_one gl_src_alpha
		rgbGen wave sawtooth 0 1 0 8 
	}
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 77
		tcMod stretch sin 0.3 0.4 0 0.4 
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 33
		tcMod stretch sin 0.8 -0.4 0 0.1 
	}
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate -17
		tcMod stretch sawtooth 0 1.2 0 0.5 
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate -77
	}
}

smokePuff
{
	nopicmip
	cull disable
	{
		clampmap gfx/misc/smokepuff3.jpg
		blendfunc blend
		tcMod rotate -55
		alphaGen Vertex
	}
	{
		clampmap gfx/misc/smokepuff3.jpg
		blendfunc blend
		tcMod rotate 66
		alphaGen Vertex
	}
}

smokePuffRagePro
{
	nopicmip
	cull disable
	{
		map gfx/misc/smokepuffragepro
		blendfunc blend
		alphaGen Vertex
	}
}

hasteSmokePuff
{
	cull disable
	{
		map gfx/misc/hastesmoke
		blendfunc blend
		tcMod rotate 64
		alphaGen Vertex
	}
}

shotgunSmokePuff
{
	nopicmip
	cull disable
	{
		clampmap gfx/misc/smokepuff3.jpg
		blendfunc blend
		tcMod rotate -45
		alphaGen entity
	}
}

sprites/plasma1
{
	nopicmip
	{
		clampmap sprites/plasmaa
		blendfunc gl_src_alpha gl_one
		tcMod rotate -145
	}
	{
		clampmap sprites/plasmaa
		blendfunc gl_src_alpha gl_one
		tcMod rotate 177
	}
}

bfgshot
{
	nopicmip
	cull disable
	deformVertexes autosprite
	{
		clampmap textures/oafx/bfgfx
		blendfunc add
		tcMod rotate -700
	}
	{
		clampmap textures/oafx/bfgfx2
		blendfunc add
		tcMod rotate 54
	}
	{
		clampmap textures/oafx/bfgfx2
		blendfunc add
		tcMod rotate -14
	}
}

bfgsho
{
	cull disable
	deformVertexes autosprite
	{
		clampmap textures/oafx/bfgfx3
		blendfunc add
		tcMod rotate 64
	}
}

// STUPID explosion thing introduced in q3's 1.30 patch
explode11
{
	{
		map textures/sfx/130boom/dpexplosion4_0000
		blendfunc add
	}
}

explode12
{
	{
		map textures/sfx/130boom/dpexplosion4_0001
		blendfunc add
	}
}

explode13
{
	{
		map textures/sfx/130boom/dpexplosion4_0002
		blendfunc add
	}
}

explode14
{
	{
		map textures/sfx/130boom/dpexplosion4_0003
		blendfunc add
	}
}

explode15
{
	{
		map textures/sfx/130boom/dpexplosion4_0004
		blendfunc add
	}
}

explode16
{
	{
		map textures/sfx/130boom/dpexplosion4_0005
		blendfunc add
	}
}

explode17
{
	{
		map textures/sfx/130boom/dpexplosion4_0006
		blendfunc add
	}
}

explode18
{
	{
		map textures/sfx/130boom/dpexplosion4_0007
		blendfunc add
	}
}

explode19
{
	{
		map textures/sfx/130boom/dpexplosion4_0008
		blendfunc add
	}
}

explode110
{
	{
		map textures/sfx/130boom/dpexplosion4_0009
		blendfunc add
	}
}

explode111
{
	{
		map textures/sfx/130boom/dpexplosion4_0010
		blendfunc add
	}
}

explode112
{
	{
		map textures/sfx/130boom/dpexplosion4_0011
		blendfunc add
	}
}

explode113
{
	{
		map textures/sfx/130boom/dpexplosion4_0012
		blendfunc add
	}
}

explode114
{
	{
		map textures/sfx/130boom/dpexplosion4_0013
		blendfunc add
	}
}

explode115
{
	{
		map textures/sfx/130boom/dpexplosion4_0014
		blendfunc add
	}
}

explode116
{
	{
		map textures/sfx/130boom/dpexplosion4_0015
		blendfunc add
	}
}

explode117
{
	{
		map textures/sfx/130boom/dpexplosion4_0016
		blendfunc add
	}
}

explode118
{
	{
		map textures/sfx/130boom/dpexplosion4_0017
		blendfunc add
	}
}

explode119
{
	{
		map textures/sfx/130boom/dpexplosion4_0018
		blendfunc add
	}
}

explode120
{
	{
		map textures/sfx/130boom/dpexplosion4_0019
		blendfunc add
	}
}

explode121
{
	{
		map textures/sfx/130boom/dpexplosion4_0020
		blendfunc add
	}
}

explode122
{
	{
		map textures/sfx/130boom/dpexplosion4_0021
		blendfunc add
	}
}

explode123
{
	{
		map textures/sfx/130boom/dpexplosion4_0022
		blendfunc add
	}
}

explode124
{
	{
		map textures/sfx/130boom/dpexplosion4_0023
		blendfunc add
	}
}

lightningBoltnew
{
	cull none
	nopicmip
	{
		map textures/oafx/lightningscroll
		blendfunc add
		tcMod scale 0.5 1
		tcMod scroll -1.6 0
	}
	{
		map textures/oafx/lightningscroll
		blendfunc add
		tcMod scale -0.5 -1
		tcMod scroll -4.2 0
	}
}

lightningBoltThin
{
	cull none
	nopicmip
	{
		map textures/oafx/lightningthin
		blendfunc add
	}
}

