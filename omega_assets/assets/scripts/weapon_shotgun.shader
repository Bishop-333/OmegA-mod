models/weapons2/shotgun/skinoa
{
	nopicmip
	{
		map models/weapons2/shotgun/shotgun.tga
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/spec/gunmetal.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
	{
		map gfx/fx/detail/d_met.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
	{
		map models/weapons2/shotgun/shotgun.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen const ( 0.329412 0.490196 0.505882 )
		alphaGen lightingSpecular
		detail
	}
}

models/weapons2/shotgun/shotgun_laser
{
	nopicmip
	{
		map models/weapons2/shotgun/shotgun_laser.tga
		blendfunc add
		tcMod scroll 0.3 0
	}
}

