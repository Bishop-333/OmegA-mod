//eh
sprites/friend
{
	nomipmaps
	{
		map sprites/friend1
		blendfunc blend
	}
}

sprites/foe
{
	nomipmaps
	{
		map sprites/foe2
		blendfunc blend
		rgbGen vertex
	}
}

models/flags/b_flag
{
	cull disable
	nopicmip
	deformVertexes wave 40 sin 1 4 0 1.5 
	deformVertexes wave 10 square 0 1 0.25 0.1 
	{
		map textures/sfx/proto_zzztblu3
		rgbGen identity
		tcMod turb 1 1 0.5 0.3
		tcGen environment 
	}
	{
		map models/flags/b_flag
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map textures/effects/flagenv
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
}

models/flags/b_pole
{
	nopicmip
	{
		map textures/base_wall/chrome_env
		rgbGen lightingDiffuse
		tcMod scale 0.5 0.5
		tcGen environment 
	}
	{
		map models/flags/pole
		blendfunc filter
		rgbGen identity
	}
}

models/flags/r_pole
{
	nopicmip
	{
		map textures/effects/envmapgold
		rgbGen lightingDiffuse
		tcMod scale 0.5 0.5
		tcGen environment 
	}
	{
		map models/flags/pole
		blendfunc filter
		rgbGen identity
	}
}

models/flags/r_flag
{
	cull disable
	nopicmip
	deformVertexes wave 40 sin 1 4 0 1.5 
	deformVertexes wave 10 square 0 1 0.25 0.1 
	{
		map textures/sfx/proto_zzzt
		rgbGen identity
		tcMod turb 1 1 0.5 0.3
		tcGen environment 
	}
	{
		map models/flags/r_flag
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map textures/effects/flagenv
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
}

models/flags/bflagface
{
	cull none
	nopicmip
	nomipmaps
	{
		clampmap models/flags2/bflagface1.jpg
		blendfunc add
		rgbGen identity
	}
}

models/flags/rflagface
{
	cull none
	nopicmip
	nomipmaps
	{
		clampmap models/flags2/rflagface1.jpg
		blendfunc add
		rgbGen identity
	}
}

