models\weapons2\grapple\hookgun
{
	nopicmip
	{
		map models/weapons2/grapple/hookgun
		rgbGen lightingDiffuse
	}
}

models\weapons2\grapple\hook
{
	nopicmip
	{
		map models/weapons2/grapple/hook
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/grapple/hookspec
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
		map models/weapons2/grapple/hookbeam
		alphaFunc GE128
	}
}

