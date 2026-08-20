//*******************************
//DEFAULT_SKIN:
//*******************************
models/players/sergei/face
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
}

models/players/sergei/skin
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
}

models/players/sergei/hairs
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
}

//*******************************
//RED_SKIN:
//*******************************
models/players/sergei/facered
{
	cull disable
	{
		map models/players/sergei/facered
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/facered
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/sergei/skinred
{
	cull disable
	{
		map models/players/sergei/skinred
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/skinred
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/sergei/hairsred
{
	cull disable
	{
		map models/players/sergei/hairsred
		rgbGen lightingDiffuse
		depthWrite
		alphaFunc GE128
	}
	{
		map models/players/sergei/hairsred
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

//*******************************
//BLUE_SKIN:
//*******************************
models/players/sergei/faceblue
{
	cull disable
	{
		map models/players/sergei/faceblue
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/faceblue
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/sergei/skinblue
{
	cull disable
	{
		map models/players/sergei/skinblue
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/skinblue
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/sergei/hairsblue
{
	cull disable
	{
		map models/players/sergei/hairsblue
		rgbGen lightingDiffuse
		depthWrite
		alphaFunc GE128
	}
	{
		map models/players/sergei/hairsblue
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

//*******************************
//PM_SKIN:
//*******************************
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

