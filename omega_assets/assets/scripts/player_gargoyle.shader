models/players/gargoyle/buh
{
	{
		map models/players/gargoyle/blue
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/red
		blendfunc add
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/bared
		blendfunc add
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/skinspecmult
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
		map models/players/gargoyle/red
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/red
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/blue
{
	{
		map models/players/gargoyle/blue
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/blue
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/stone
{
	{
		map models/players/gargoyle/stone
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/stone
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map gfx/fx/detail/d_stone
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
}

models/players/gargoyle/bared
{
	{
		map models/players/gargoyle/bared
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/bared
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
		map models/players/gargoyle/morphedwings
		blendfunc add
	}
}

models/players/gargoyle/membranecray
{
	cull disable
	{
		map models/players/gargoyle/wings
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/specwing
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
		map models/players/gargoyle/wings-stone
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/gargoyle/specwing
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
		map models/players/gargoyle/wings-yellow
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/specwing
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
		map models/players/gargoyle/wings-blue
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/specwing
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/gargoyle/morphedgarg
{
	{
		map models/players/gargoyle/morphedgarg
	}
	{
		map models/players/gargoyle/morphedshader
		blendfunc add
		tcMod scroll -0.2 0.3
		tcGen environment 
	}
	{
		map models/players/gargoyle/morphedgarg
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx2
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
		map models/players/gargoyle/morphedgarg_red
	}
	{
		map models/players/gargoyle/morphedshader_red
		blendfunc add
		tcMod scroll -0.2 0.3
		tcGen environment 
	}
	{
		map models/players/gargoyle/morphedgarg_red
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/gargoyle/morphedwings_red
{
	cull disable
	{
		map models/players/gargoyle/morphedwings_red
		blendfunc add
	}
}

// PM SKIN
models/players/gargoyle/pm
{
	{
		map models/players/gargoyle/bared
		rgbGen lightingDiffuse
	}
	{
		map models/players/gargoyle/bared
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/gargoyle/pm
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/gargoyle/pm_membranecray
{
	cull disable
	{
		map models/players/gargoyle/pm_wings
		blendfunc blend
		rgbGen entity
	}
	{
		map models/players/gargoyle/specwing
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

