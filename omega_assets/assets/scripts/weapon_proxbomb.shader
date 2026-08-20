models/weaphits/proxflare
{
	nopicmip
	deformVertexes autosprite
	{
		map textures/flares/wide
		blendfunc add
		rgbGen const ( 1 0 0 )
	}
}

models/weaphits/proxflare_b
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap textures/flares/flarey
		blendfunc add
		rgbGen const ( 0 0 1 )
	}
}

models/weaphits/proxlite
{
	cull disable
	nopicmip
	{
		map models/weaphits/proxbomb
		blendfunc gl_dst_color gl_src_color
		rgbGen identity
	}
}

models/weaphits/proxlite_b
{
	cull disable
	nopicmip
	{
		map models/weaphits/proxbomb_b
		blendfunc gl_dst_color gl_src_color
		rgbGen identity
	}
}

