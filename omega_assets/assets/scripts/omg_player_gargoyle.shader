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
