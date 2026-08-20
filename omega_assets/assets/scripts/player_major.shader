models/players/major/buh
{
	{
		map textures/effects/tinfx2
		rgbGen lightingDiffuse
		tcMod rotate 5
		tcGen environment 
	}
}

models/players/major/pm_torso
{
	{
		map /models/players/major/torso
	}
	{
		map /models/players/major/pm_torso
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity	
	}
}

models/players/major/pm_lower
{
	{
		map /models/players/major/lower
	}
	{
		map /models/players/major/pm_lower
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity	
	}
}

