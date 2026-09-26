models/players/sergei/pm_face
{
	cull disable
	{
		map models/players/sergei/face
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/face
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/sergei/pm_face
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/sergei/pm_skin
{
	cull disable
	{
		map models/players/sergei/skin
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/skin
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/sergei/pm_skin
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/sergei/pm_hairs
{
	cull disable
	{
		map models/players/sergei/hairs
		rgbGen lightingDiffuse
		depthWrite
		alphaFunc GE128
	}
	{
		map models/players/sergei/hairs
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/sergei/pm_hairs
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}
