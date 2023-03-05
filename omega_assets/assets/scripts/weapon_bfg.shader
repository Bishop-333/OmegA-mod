f_bfg3
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weapons2/bfg/f_bfg3.tga
		blendfunc add
		rgbGen const ( 0.376471 0.576471 0.403922 )
		tcMod rotate 8288
	}
	{
		clampmap models/weapons2/bfg/f_bfg3.tga
		blendfunc add
		rgbGen const ( 0.478431 0.603922 0.447059 )
		tcMod rotate -2288
		tcMod stretch sin 1.3 0 0 0 
	}
}

f_bfg1
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weapons2/bfg/f_bfg3.tga
		blendfunc add
		rgbGen const ( 0.376471 0.576471 0.403922 )
		tcMod rotate 8288
	}
	{
		clampmap models/weapons2/bfg/f_bfg3.tga
		blendfunc add
		rgbGen const ( 0.478431 0.603922 0.447059 )
		tcMod rotate -2288
		tcMod stretch sin 1.3 0 0 0 
	}
}

models/weapons2/bfg/bfgbody
{
	cull disable
	nopicmip
	{
		map models/weapons2/bfg/bfgbody.tga
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/detail/d_met.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
	{
		map models/weapons2/bfg/bfgbody.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/weapons2/bfg/bfgtube
{
	cull disable
	nopicmip
	{
		map models/weapons2/bfg/bfgtube.tga
		blendfunc blend
		rgbGen lightingDiffuse
		tcMod scroll -0.04 0
		alphaGen wave inversesawtooth 0.5 0 0 1 
	}
	{
		map models/weapons2/bfg/bubbles.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		tcMod scale 1.8 1
		tcMod scroll -2 0
	}
	{
		map gfx/fx/spec/robawt.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
}

f_bfg2
{
	cull disable
	nopicmip
	{
		clampmap models/weapons2/bfg/f_bfg2.tga
		blendfunc add
		rgbGen const ( 0.694118 0.694118 0.694118 )
		tcMod rotate 2122
	}
	{
		clampmap models/weapons2/bfg/f_bfg2.tga
		blendfunc add
		rgbGen const ( 0.286275 0.54902 0.25098 )
		tcMod rotate -3201
		tcMod stretch sin 1.3 0 0 0 
	}
}

BFGNexus
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weaphits/bfg.tga
		blendfunc add
		tcMod rotate 999
	}
	{
		clampmap models/weaphits/bfg3.tga
		blendfunc add
		rgbGen const ( 0.188235 0.247059 0.180392 )
		tcMod rotate 700
		tcMod stretch sin 1.3 0.3 0 4 
	}
	{
		clampmap models/weaphits/bfg2.tga
		blendfunc add
		rgbGen const ( 0.254902 0.352941 0.227451 )
		tcMod rotate 244
		tcMod stretch sin 1.3 0.3 0 4 
	}
}

BFGTrail
{
	cull disable
	nopicmip
	{
		clampmap models/weaphits/bfg2.tga
		blendfunc add
		rgbGen const ( 0.694118 0.694118 0.694118 )
		tcMod rotate 1522
	}
	{
		clampmap models/weaphits/bfg2.tga
		blendfunc add
		rgbGen const ( 0.286275 0.54902 0.25098 )
		tcMod rotate -1222
		tcMod stretch sin 1.3 0.3 0 4 
	}
}

