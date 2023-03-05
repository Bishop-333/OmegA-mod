models/players/gargoyle/buh
{
	{
		map models/players/gargoyle/blue.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/red.tga
		blendfunc add
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/bared.tga
		blendfunc add
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/goblin.tga
		blendfunc add
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map $whiteimage 
		blendfunc filter
		rgbGen lightingDiffuse
	}
}

models/players/gargoyle/red
{
	{
		map models/players/gargoyle/red.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/red.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/blue
{
	{
		map models/players/gargoyle/blue.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/blue.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/stone
{
	{
		map models/players/gargoyle/stone.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/stone.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map gfx/fx/detail/d_stone.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
}

models/players/gargoyle/bared
{
	{
		map models/players/gargoyle/bared.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/bared.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/goblin
{
	{
		map models/players/gargoyle/goblin.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/gargoyle/goblin.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/morphedwings
{
	cull disable
	{
		map models/players/gargoyle/morphedwings.tga
		blendfunc add
	}
}

models/players/gargoyle/membranecray
{
	cull disable
	{
		map models/players/gargoyle/wings.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/specwing.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/wings-stone
{
	cull disable
	{
		map models/players/gargoyle/wings-stone.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/gargoyle/specwing.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/membranecrayyellow
{
	cull disable
	{
		map models/players/gargoyle/wings-yellow.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/specwing.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/membranecrayblue
{
	cull disable
	{
		map models/players/gargoyle/wings-blue.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/specwing.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/morphedgarg
{
	{
		map models/players/gargoyle/morphedgarg.tga
	}
	{
		map models/players/gargoyle/morphedshader.tga
		blendfunc add
		tcMod scroll -0.2 0.3
		tcGen environment 
	}
	{
		map models/players/gargoyle/morphedgarg.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx2.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}

// TEAM SKIN EXPLOSION
models/players/gargoyle/morphedgarg_red
{
	{
		map models/players/gargoyle/morphedgarg_red.tga
	}
	{
		map models/players/gargoyle/morphedshader_red.tga
		blendfunc add
		tcMod scroll -0.2 0.3
		tcGen environment 
	}
	{
		map models/players/gargoyle/morphedgarg_red.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/gargoyle/morphedwings_red
{
	cull disable
	{
		map models/players/gargoyle/morphedwings_red.tga
		blendfunc add
	}
}

