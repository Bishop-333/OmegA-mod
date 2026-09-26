models/players/merman/pm_fins
{
	cull disable
	{
		map /models/players/merman/pm_fins
		blendfunc blend
		rgbGen entity
	}
}

models/players/merman/pm_skin
{
	{
		map /models/players/merman/skin
		rgbGen lightingDiffuse
		
	}
	{
		map /models/players/merman/pm_skin
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity	
	}
}

models/players/merman/pm_brac
{
	cull disable
	{
		map /models/players/merman/pm_brac
		rgbGen entity
	}
}
