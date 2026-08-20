models/weapons2/shotgun/skinoa
{
	{
		map models/weapons2/shotgun/shotgun
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/spec/gunmetal
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
	{
		map gfx/fx/detail/d_met
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
	{
		map models/weapons2/shotgun/shotgun
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
		map models/weapons2/shotgun/shotgun_laser
		blendfunc add
		tcMod scroll 0.3 0
	}
}

