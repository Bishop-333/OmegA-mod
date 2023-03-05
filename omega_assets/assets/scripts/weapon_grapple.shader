models\weapons2\grapple\hookgun
{
	nopicmip
	{
		map models/weapons2/grapple/hookgun.tga
		rgbGen lightingDiffuse
	}
}

models\weapons2\grapple\hook
{
	nopicmip
	{
		map models/weapons2/grapple/hook.tga
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/grapple/hookspec.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

grappleRope
{
	cull disable
	nopicmip
	{
		map models/weapons2/grapple/hookbeam.tga
		alphaFunc GE128
	}
}

