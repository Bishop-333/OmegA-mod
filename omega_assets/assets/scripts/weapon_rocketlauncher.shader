rocketFlash
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weapons2/rocketl/muzzy.tga
		blendfunc add
		tcMod rotate 1246
	}
}

rocketFlare
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap textures/flares/newflare.tga
		blendfunc add
		rgbGen const ( 0.713726 0.270588 0.121569 )
		tcMod rotate 467
	}
}

rocketThrust
{
	cull disable
	nopicmip
	{
		clampmap textures/flares/newflare.tga
		blendfunc add
		rgbGen const ( 0.713726 0.270588 0.121569 )
		tcMod rotate 467
	}
}

models/weapons2/rocketl/skin
{
	nopicmip
	{
		map models/weapons2/rocketl/skin.tga
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/rocketl/skin.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen const ( 0.286275 0.352941 0.462745 )
		alphaGen lightingSpecular
		detail
	}
	{
		map gfx/fx/detail/d_met.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
}

