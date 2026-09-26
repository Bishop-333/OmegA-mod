models/players/kyonshi/pm_torso
{
	{
		map models/players/kyonshi/torso
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/envmapgold
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/torso
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/kyonshi/pm_torso
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/kyonshi/pm_lower
{
	{
		map models/players/kyonshi/lower
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/envmapgold
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/lower
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/kyonshi/pm_lower
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/kyonshi/pm_eyes
{
	{
		map models/players/kyonshi/eyes
		blendFunc gl_one gl_zero
		rgbGen lightingDiffuse
	}
	{
		clampmap textures/effects/skinspecmulttin
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/players/kyonshi/pm_eyes
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/kyonshi/pm_skin
{
	{
		map models/players/kyonshi/skin
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/skinspecmult
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/players/kyonshi/skin
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/kyonshi/pm_skin
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}
