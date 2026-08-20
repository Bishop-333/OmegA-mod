models/players/sorceress/rings
{
	{
		map models/players/sorceress/rings
		rgbGen lightingDiffuse
		blendfunc gl_one gl_one
	}
}

models/players/sorceress/redrings
{
	{
		map models/players/sorceress/redrings
		rgbGen lightingDiffuse
		blendfunc gl_one gl_one
	}
}

models/players/sorceress/drowhead
{
	cull disable
	{
		map models/players/sorceress/drowhead
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/drowhead
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/sorceress/reddrowhead
{
	cull disable
	{
		map models/players/sorceress/reddrowhead
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/reddrowhead
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/sorceress/drowhair
{
	cull disable
	{
		map models/players/sorceress/drowhead
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/hairspec
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/sorceress/drowbody
{
	cull disable
	{
		map models/players/sorceress/drowbody
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/drowbody
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/sorceress/reddrowhair
{
	cull disable
	{
		map models/players/sorceress/reddrowhead
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/hairspec
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/sorceress/reddrowbody
{
	cull disable
	{
		map models/players/sorceress/reddrowbody
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/reddrowbody
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}
