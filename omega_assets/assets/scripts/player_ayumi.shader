models/players/ayumi/hair
{
	cull disable
	{
		map models/players/ayumi/hair.tga
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

models/players/ayumi/redhair
{
	cull disable
	{
		map models/players/ayumi/redhair.tga
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

models/players/ayumi/bluehair
{
	cull disable
	{
		map models/players/ayumi/bluehair.tga
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

models/players/ayumi/shirt
{
	cull disable
	{
		map models/players/ayumi/shirt.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/ayumi/shirt.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/ayumi/redshirt
{
	cull disable
	{
		map models/players/ayumi/redshirt.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/ayumi/redshirt.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/ayumi/blueshirt
{
	cull disable
	{
		map models/players/ayumi/blueshirt.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/ayumi/blueshirt.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/ayumi/bodytrans
{
	cull front
	{
		map models/players/ayumi/body.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/body
{
	{
		map models/players/ayumi/body.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/ayumi/body.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/ayumi/jettest
{
	cull disable
	{
		clampmap models/players/ayumi/jet/jet1.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 2 
		tcMod stretch inversesawtooth 1 1 0 2 
	}
	{
		clampmap models/players/ayumi/jet/jet1.tga
		blendfunc add
		rgbGen wave inversesawtooth 0.5 1 0 3 
		tcMod stretch inversesawtooth 1 0.7 0 3 
	}
	{
		clampmap models/players/ayumi/jet/jet1.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod stretch inversesawtooth 1 1 0 1 
	}
	{
		clampmap models/players/ayumi/jet/jet2.tga
		blendfunc add
		rgbGen wave inversesawtooth 0.5 1 0 5 
		tcMod stretch sawtooth 1.9 0.8 0 5 
	}
	{
		clampmap models/players/ayumi/jet/jet2.tga
		blendfunc add
		rgbGen wave inversesawtooth 0.5 1 0 2 
		tcMod stretch sawtooth 0.5 1.2 0 2 
	}
}

models/players/ayumi/jet2
{
	cull disable
	{
		animmap 30 models/players/ayumi/jet/jet3a.tga models/players/ayumi/jet/jet3b.tga models/players/ayumi/jet/jet3c.tga models/players/ayumi/jet/jet3d.tga models/players/ayumi/jet/jet3e.tga models/players/ayumi/jet/jet3f.tga models/players/ayumi/jet/jet3g.tga models/players/ayumi/jet/jet3h.tga 
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 30 
	}
	{
		animmap 30 models/players/ayumi/jet/jet3b.tga models/players/ayumi/jet/jet3c.tga models/players/ayumi/jet/jet3d.tga models/players/ayumi/jet/jet3e.tga models/players/ayumi/jet/jet3f.tga models/players/ayumi/jet/jet3g.tga models/players/ayumi/jet/jet3h.tga models/players/ayumi/jet/jet3a.tga 
		blendfunc add
		rgbGen wave sawtooth 0 1 0 30 
	}
	{
		animmap 15 models/players/ayumi/jet/jet3h.tga models/players/ayumi/jet/jet3g.tga models/players/ayumi/jet/jet3f.tga models/players/ayumi/jet/jet3e.tga models/players/ayumi/jet/jet3d.tga models/players/ayumi/jet/jet3c.tga models/players/ayumi/jet/jet3b.tga models/players/ayumi/jet/jet3a.tga 
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 15 
	}
	{
		animmap 15 models/players/ayumi/jet/jet3g.tga models/players/ayumi/jet/jet3f.tga models/players/ayumi/jet/jet3e.tga models/players/ayumi/jet/jet3d.tga models/players/ayumi/jet/jet3c.tga models/players/ayumi/jet/jet3b.tga models/players/ayumi/jet/jet3a.tga models/players/ayumi/jet/jet3h.tga 
		blendfunc add
		rgbGen wave sawtooth 0 1 0 15 
	}
	{
		animmap 15 models/players/ayumi/jet/jet3smk1.tga models/players/ayumi/jet/jet3smk2.tga models/players/ayumi/jet/jet3smk3.tga models/players/ayumi/jet/jet3smk4.tga models/players/ayumi/jet/jet3smk5.tga models/players/ayumi/jet/jet3smk6.tga models/players/ayumi/jet/jet3smk7.tga 
		blendfunc add
		rgbGen const ( 0.337255 0.184314 0.466667 )
		tcMod rotate 153
	}
	{
		animmap 15 models/players/ayumi/jet/jet3smk7.tga models/players/ayumi/jet/jet3smk1.tga models/players/ayumi/jet/jet3smk2.tga models/players/ayumi/jet/jet3smk3.tga models/players/ayumi/jet/jet3smk4.tga models/players/ayumi/jet/jet3smk5.tga models/players/ayumi/jet/jet3smk6.tga 
		blendfunc add
		rgbGen const ( 0.294118 0.235294 0.482353 )
		tcMod rotate -95
	}
}

models/players/ayumi/bootjenna
{
	cull disable
	{
		map models/players/ayumi/bootjenna.tga
		rgbGen lightingDiffuse
	}
}

models/players/ayumi/bootjenna_red
{
	cull disable
	{
		map models/players/ayumi/bootjenna_red.tga
		rgbGen lightingDiffuse
	}
}

models/players/ayumi/bootjenna_blue
{
	cull disable
	{
		map models/players/ayumi/bootjenna_blue.tga
		rgbGen lightingDiffuse
	}
}

models/players/ayumi/hairjenna
{
	cull disable
	{
		map models/players/ayumi/hairjenna.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/hairjenna_red
{
	cull disable
	{
		map models/players/ayumi/hairjenna_red.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/hairjenna_blue
{
	cull disable
	{
		map models/players/ayumi/hairjenna_blue.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/shirtjenna
{
	cull disable
	{
		map models/players/ayumi/shirtjenna.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/shirtjenna_red
{
	cull disable
	{
		map models/players/ayumi/shirtjenna_red.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/shirtjenna_blue
{
	cull disable
	{
		map models/players/ayumi/shirtjenna_blue.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

