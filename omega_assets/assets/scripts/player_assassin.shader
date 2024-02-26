//*******************************
//DEFAULT_SKIN:
//*******************************
models/players/assassin/upper
{
	cull disable
	{
		map models/players/assassin/upper.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/assassin/upper.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/assassin/lower
{
	cull disable
	{
		map models/players/assassin/lower.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/assassin/lower.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

//*******************************
//BLUE_SKIN:
//*******************************
models/players/assassin/upper-blue
{
	cull disable
	{
		map models/players/assassin/upper-blue.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/assassin/upper-blue.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/assassin/lower-blue
{
	cull disable
	{
		map models/players/assassin/lower-blue.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/assassin/lower-blue.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

//*******************************
//RED_SKIN:
//*******************************
models/players/assassin/upper-red
{
	cull disable
	{
		map models/players/assassin/upper-red.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/assassin/upper-red.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/assassin/lower-red
{
	cull disable
	{
		map models/players/assassin/lower-red.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/assassin/lower-red.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

//*******************************
//GHOST_SKIN:
//*******************************
models/players/assassin/upper_ghost
{
	{
		map models/players/assassin/upper_ghost.tga
		blendfunc blend
		rgbGen wave sin 0.8 0.2 0 0.5 
	}
	{
		map textures/effects/envmap2.tga
		blendfunc add
		rgbGen wave sin 0.9 0.1 0 0.05 
		tcMod scroll -0.2 -0.05
		tcGen environment 
	}
}

models/players/assassin/lower_ghost
{
	{
		map models/players/assassin/lower_ghost.tga
		blendfunc blend
		rgbGen wave sin 0.8 0.2 0 0.5 
	}
	{
		map textures/effects/envmap2.tga
		blendfunc add
		rgbGen wave sin 0.9 0.1 0 0.05 
		tcMod scroll -0.2 -0.05
		tcGen environment 
	}
}

//*******************************
//PM_SKIN:
//*******************************
models/players/assassin/pm_upper
{
	cull disable
	{
		map models/players/assassin/upper.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/assassin/upper.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/assassin/pm_upper.tga
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/assassin/pm_lower
{
	cull disable
	{
		map models/players/assassin/lower.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/assassin/lower.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/assassin/pm_lower.tga
		alphaFunc GE128
		rgbGen entity
	}
}

