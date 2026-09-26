models/players/smarine/pm_u_torsob
{
	{
		map models/players/smarine/2u_torso
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/spec/specenv
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/smarine/pm_u_torsob
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/smarine/pm_l_legsb
{
	{
		map models/players/smarine/2l_legs
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/spec/specenv
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/smarine/pm_l_legsb
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/smarine/pm_h_headb
{
	{
		map models/players/smarine/2h_head
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/spec/specenv
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
	{
		map models/players/smarine/pm_h_headb
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}
