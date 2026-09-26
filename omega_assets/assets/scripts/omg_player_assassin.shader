models/players/assassin/pm_upper
{
	cull disable
	{
		map models/players/assassin/upper
		rgbGen lightingDiffuse
	}
	{
		map models/players/assassin/upper
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/assassin/pm_upper
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/assassin/pm_lower
{
	cull disable
	{
		map models/players/assassin/lower
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/assassin/lower
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/assassin/pm_lower
		alphaFunc GE128
		rgbGen entity
	}
}
