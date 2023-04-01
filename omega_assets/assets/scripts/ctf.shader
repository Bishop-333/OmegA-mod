//eh
sprites/friend
{
	nomipmaps
	{
		map sprites/friend1.tga
		blendfunc blend
	}
}

sprites/foe
{
	nomipmaps
	{
		map sprites/foe2.tga
		blendfunc blend
	}
}

models/flags/b_flag
{
	cull disable
	nopicmip
	deformVertexes wave 40 sin 1 4 0 1.5 
	deformVertexes wave 10 square 0 1 0.25 0.1 
	{
		map textures/sfx/proto_zzztblu3.tga
		rgbGen identity
		tcMod turb 1 1 0.5 0.3
		tcGen environment 
	}
	{
		map models/flags/b_flag.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map textures/effects/flagenv.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
}

models/flags/b_pole
{
	nopicmip
	{
		map textures/base_wall/chrome_env.tga
		rgbGen lightingDiffuse
		tcMod scale 0.5 0.5
		tcGen environment 
	}
	{
		map models/flags/pole.tga
		blendfunc filter
		rgbGen identity
	}
}

models/flags/r_pole
{
	nopicmip
	{
		map textures/effects/envmapgold.tga
		rgbGen lightingDiffuse
		tcMod scale 0.5 0.5
		tcGen environment 
	}
	{
		map models/flags/pole.tga
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
		map textures/sfx/proto_zzzt.tga
		rgbGen identity
		tcMod turb 1 1 0.5 0.3
		tcGen environment 
	}
	{
		map models/flags/r_flag.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map textures/effects/flagenv.tga
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
		clampmap models/flags_omega/bflagface1.jpg
		blendfunc add
	}
}

models/flags/rflagface
{
	cull none
	nopicmip
	nomipmaps
	{
		clampmap models/flags_omega/rflagface1.jpg
		blendfunc add
	}
}

