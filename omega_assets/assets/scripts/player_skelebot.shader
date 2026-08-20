//*******************************
//DEFAULT_SKIN:
//*******************************

models/players/skelebot/skin1
{
//	cull disable
	{
		map models/players/skelebot/skin1
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
//		tcMod scale 0.1 0.1
		rgbGen lightingDiffuse
	}
}

models/players/skelebot/skin2
{
//	cull disable
	{
		map models/players/skelebot/skin2
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
//		tcMod scale 5 5
		rgbGen lightingDiffuse
	}
}
//		map textures/effects/eyespec

//*******************************
//BLUE_SKIN:
//*******************************

models/players/skelebot/skin1blue
{
	{
		map models/players/skelebot/skin1blue
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
		rgbGen lightingDiffuse
	}
}

models/players/skelebot/skin2blue
{
	{
		map models/players/skelebot/skin2blue
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
		rgbGen lightingDiffuse
	}
}

//*******************************
//RED_SKIN:
//*******************************

models/players/skelebot/skin1red
{
	{
		map models/players/skelebot/skin1red
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
		rgbGen lightingDiffuse
	}
}

models/players/skelebot/skin2red
{
	{
		map models/players/skelebot/skin2red
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
		rgbGen lightingDiffuse
	}
}

//*******************************
//METALSKIN:
//*******************************

models/players/skelebot/skin1metal
{
	{
		map models/players/skelebot/skin1metal
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
		rgbGen lightingDiffuse
	}
}

models/players/skelebot/skin2metal
{
	{
		map models/players/skelebot/skin2metal
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
		rgbGen lightingDiffuse
	}
}

//*******************************
//PM_SKIN:
//*******************************

models/players/skelebot/pm_skin1
{
	{
		map models/players/skelebot/skin1
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
		rgbGen lightingDiffuse
	}
	{
		map models/players/skelebot/pm_skin1
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/skelebot/pm_skin2
{
	{
		map models/players/skelebot/skin2
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx3.jpg
 		blendfunc add
		tcGen environment
		rgbGen lightingDiffuse
	}
	{
		map models/players/skelebot/pm_skin2
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}