models/players/sorceress/rings
{
	{
		map models/players/sorceress/rings.tga
		rgbGen lightingDiffuse
		blendfunc gl_one gl_one
	}
}

models/players/sorceress/redrings
{
	{
		map models/players/sorceress/redrings.tga
		rgbGen lightingDiffuse
		blendfunc gl_one gl_one
	}
}

models/players/sorceress/defaultrings
{
	{
		map models/players/sorceress/defaultrings.tga
		rgbGen lightingDiffuse
		blendfunc gl_one gl_one
	}
}

models/players/sorceress/drowhead
{
	cull disable
	{
		map models/players/sorceress/drowhead.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/drowhead.tga
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
		map models/players/sorceress/reddrowhead.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/reddrowhead.tga
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
		map models/players/sorceress/drowhead.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/hairspec.tga
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
		map models/players/sorceress/drowbody.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/drowbody.tga
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
		map models/players/sorceress/reddrowhead.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/hairspec.tga
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
		map models/players/sorceress/reddrowbody.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/reddrowbody.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/sorceress/defaultdrowhair
{
	cull disable
	{
		map models/players/sorceress/defaultdrowhead.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/hairspec.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/sorceress/defaultdrowbody
{
	cull disable
	{
		map models/players/sorceress/defaultdrowbody.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/players/sorceress/defaultdrowbody.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}
