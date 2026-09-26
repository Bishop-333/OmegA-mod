models/players/tony/pm_head
{
	cull disable
	{
		map models/players/tony/head
		rgbGen lightingDiffuse
	}
	{
		map models/players/tony/head
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/tony/pm_head
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/tony/pm_suit
{
	cull disable
	{
		map models/players/tony/suit
		rgbGen lightingDiffuse
	}
	{
		map models/players/tony/suit
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/tony/pm_suit
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}
