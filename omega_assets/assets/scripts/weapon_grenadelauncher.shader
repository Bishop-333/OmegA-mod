models/weapons2/grenadel/grenadel
{
	nopicmip
	{
		map models/weapons2/grenadel/grenadel
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/grenadel/grenadel
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
	}
}

models/weapons2/grenadel/newgren
{
	nopicmip
	{
		map models/weapons2/grenadel/newgren
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/grenadel/newgren
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/weapons2/grenadel/blackhandle
{
	nopicmip
	{
		map models/weapons2/grenadel/blackhandle
		rgbGen lightingDiffuse
		tcGen environment 
	}
}

models/weapons2/grenadel/muzside
{
	cull disable
	nopicmip
	{
		map models/weapons2/grenadel/muzzlside
		blendfunc add
	}
}

models/weapons2/grenadel/muzcenter
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weapons2/grenadel/f_plasma
		blendfunc add
		tcMod rotate 1246
	}
	{
		clampmap models/weapons2/grenadel/f_plasma
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons2/grenadel/flare
{
	nopicmip
	deformVertexes autosprite
	{
		map models/weapons2/grenadel/flare
		blendfunc add
		rgbGen wave noise 0.5 0.5 0 1 
	}
}

