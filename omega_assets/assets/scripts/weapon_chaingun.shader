vulcanFlash
{
	cull disable
	nopicmip
	deformVertexes bulge 3 3 76
	{
		clampmap models/weapons/vulcan/muzzy.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 30 
		tcMod rotate 1554
	}
	{
		clampmap models/weapons/vulcan/muzzy.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 30 
		tcMod rotate -2640
	}
	{
		clampmap models/weapons/vulcan/muzzy.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 30 
		tcMod rotate 7402
		tcMod stretch sin 0 1 0 1 
	}
	{
		clampmap models/weapons/vulcan/muzzy.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 30 
		tcMod rotate -6403
		tcMod stretch sin 0.5 0.5 0 1 
	}
}

models/weapons/vulcan/skin
{
	nopicmip
	{
		map models/weapons/vulcan/skin.tga
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/detail/d_met.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
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

