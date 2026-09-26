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

m5
{
	{
		map textures/proto2/concrete03
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/skinspecmult
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map textures/proto2/concrete03
		blendfunc blend
		rgbGen lightingDiffuse
	}
}
