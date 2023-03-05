models/weapons2/plasma/f_plasmagun2
{
	cull disable
	nopicmip
	{
		clampmap textures/flares/lava.tga
		blendfunc add
		rgbGen const ( 0 0.0862745 0.235294 )
		tcMod rotate 8455
		tcMod stretch sin 0 1 0 2 
	}
	{
		clampmap textures/flares/flarey.tga
		blendfunc add
		rgbGen const ( 0.447059 0.623529 0.921569 )
		tcMod rotate 1466
		tcMod stretch sin 0 1 0 1 
	}
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		rgbGen const ( 0.447059 0.623529 0.921569 )
		tcMod rotate -6455
	}
}

models/weapons2/plasma/f_plasmagun3
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons2/plasma/muzzlecenter
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons2/lightning/skinlightning
{
	nopicmip
	{
		map models/weapons2/lightning/skinlightning.tga
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/detail/d_met.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
	{
		map gfx/fx/spec/robawt.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}

models/weapons2/plasma/skin
{
	nopicmip
	{
		map models/weapons2/plasma/skin.tga
		rgbGen identity
	}
	{
		map gfx/fx/detail/d_met.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
	{
		map textures/effects/tinfx2d.tga
		blendfunc add
		rgbGen identity
		tcMod scroll 1 0
		tcMod scale 2 2
	}
	{
		map models/weapons2/plasma/skin.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/spots.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}

models/weapons2/plasma/flare
{
	nopicmip
	deformVertexes autosprite
	{
		map models/weapons2/plasma/flare.tga
		blendfunc add
	}
}

