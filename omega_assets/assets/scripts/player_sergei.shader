//*******************************
//DEFAULT_SKIN:
//*******************************
models/players/sergei/face
{
	cull disable
	{
		map models/players/sergei/face.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/face.tga
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
		map models/players/sergei/skin.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/skin.tga
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
		map models/players/sergei/hairs.tga
		rgbGen lightingDiffuse
		depthWrite
		alphaFunc GE128
	}
	{
		map models/players/sergei/hairs.tga
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
		map models/players/sergei/facered.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/facered.tga
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
		map models/players/sergei/skinred.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/skinred.tga
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
		map models/players/sergei/hairsred.tga
		rgbGen lightingDiffuse
		depthWrite
		alphaFunc GE128
	}
	{
		map models/players/sergei/hairsred.tga
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
		map models/players/sergei/faceblue.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/faceblue.tga
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
		map models/players/sergei/skinblue.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/skinblue.tga
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
		map models/players/sergei/hairsblue.tga
		rgbGen lightingDiffuse
		depthWrite
		alphaFunc GE128
	}
	{
		map models/players/sergei/hairsblue.tga
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
		map models/players/sergei/face.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/face.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/sergei/pm_face.tga
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/sergei/pm_skin
{
	cull disable
	{
		map models/players/sergei/skin.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/sergei/skin.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/sergei/pm_skin.tga
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/sergei/pm_hairs
{
	cull disable
	{
		map models/players/sergei/hairs.tga
		rgbGen lightingDiffuse
		depthWrite
		alphaFunc GE128
	}
	{
		map models/players/sergei/hairs.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/sergei/pm_hairs.tga
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

