//*******************************
//DEFAULT_SKIN:
//*******************************
models/players/merman/fins
{
	cull disable
	{
		map /models/players/merman/fins
		blendfunc blend
		rgbGen lightingDiffuse
	}
}
models/players/merman/skin
{
	{
		map /models/players/merman/skin
		rgbGen lightingDiffuse
		
	}
}
models/players/merman/brac
{
	cull disable
	{
		map /models/players/merman/brac
		rgbGen lightingDiffuse
	}
	// {
		// map /textures/effects/tinfx.jpg
		// blendfunc add
		// rgbGen lightingDiffuse
		// tcGen environment 
	// }
	// {
		// map /models/players/merman/brac
		// blendfunc blend
		// rgbGen lightingDiffuse
	// }
}
//*******************************
//RED_SKIN:
//*******************************
models/players/merman/finsred
{
	cull disable
	{
		map models/players/merman/finsred
		blendfunc blend
		rgbGen lightingDiffuse
	}
}
models/players/merman/skinred
{
	{
		map models/players/merman/skinred
		rgbGen lightingDiffuse
	}
}
models/players/merman/bracred
{
	cull disable
	{
		map models/players/merman/bracred
		rgbGen lightingDiffuse
	}
	// {
		// map textures/effects/specular
		// blendfunc add
		// rgbGen lightingDiffuse
		// tcGen environment 
	// }
}
//*******************************
//BLUE_SKIN:
//*******************************
models/players/merman/finsblue
{
	cull disable
	{
		map models/players/merman/finsblue
		blendfunc blend
		rgbGen lightingDiffuse
	}
}
models/players/merman/skinblue
{
	{
		map models/players/merman/skinblue
		rgbGen lightingDiffuse
		
	}
}
models/players/merman/bracblue
{
	cull disable
	{
		map models/players/merman/bracblue
		rgbGen lightingDiffuse
	}
	// {
		// map textures/effects/specular
		// blendfunc add
		// rgbGen lightingDiffuse
		// tcGen environment 
	// }
}
//*******************************
//PM_SKIN:
//*******************************
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