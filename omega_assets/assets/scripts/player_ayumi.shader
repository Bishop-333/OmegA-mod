models/players/ayumi/hair
{
	cull disable
	{
		map models/players/ayumi/hair
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

models/players/ayumi/redhair
{
	cull disable
	{
		map models/players/ayumi/redhair
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

models/players/ayumi/bluehair
{
	cull disable
	{
		map models/players/ayumi/bluehair
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

models/players/ayumi/shirt
{
	cull disable
	{
		map models/players/ayumi/shirt
		rgbGen lightingDiffuse
	}
	{
		map models/players/ayumi/shirt
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
		map models/players/ayumi/redshirt
		rgbGen lightingDiffuse
	}
	{
		map models/players/ayumi/redshirt
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
		map models/players/ayumi/blueshirt
		rgbGen lightingDiffuse
	}
	{
		map models/players/ayumi/blueshirt
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
		map models/players/ayumi/body
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/body
{
	{
		map models/players/ayumi/body
		rgbGen lightingDiffuse
	}
	{
		map models/players/ayumi/body
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
		clampmap models/players/ayumi/jet/jet1
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 2 
		tcMod stretch inversesawtooth 1 1 0 2 
	}
	{
		clampmap models/players/ayumi/jet/jet1
		blendfunc add
		rgbGen wave inversesawtooth 0.5 1 0 3 
		tcMod stretch inversesawtooth 1 0.7 0 3 
	}
	{
		clampmap models/players/ayumi/jet/jet1
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod stretch inversesawtooth 1 1 0 1 
	}
	{
		clampmap models/players/ayumi/jet/jet2
		blendfunc add
		rgbGen wave inversesawtooth 0.5 1 0 5 
		tcMod stretch sawtooth 1.9 0.8 0 5 
	}
	{
		clampmap models/players/ayumi/jet/jet2
		blendfunc add
		rgbGen wave inversesawtooth 0.5 1 0 2 
		tcMod stretch sawtooth 0.5 1.2 0 2 
	}
}

models/players/ayumi/jet2
{
	cull disable
	{
		animmap 30 models/players/ayumi/jet/jet3a models/players/ayumi/jet/jet3b models/players/ayumi/jet/jet3c models/players/ayumi/jet/jet3d models/players/ayumi/jet/jet3e models/players/ayumi/jet/jet3f models/players/ayumi/jet/jet3g models/players/ayumi/jet/jet3h 
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 30 
	}
	{
		animmap 30 models/players/ayumi/jet/jet3b models/players/ayumi/jet/jet3c models/players/ayumi/jet/jet3d models/players/ayumi/jet/jet3e models/players/ayumi/jet/jet3f models/players/ayumi/jet/jet3g models/players/ayumi/jet/jet3h models/players/ayumi/jet/jet3a 
		blendfunc add
		rgbGen wave sawtooth 0 1 0 30 
	}
	{
		animmap 15 models/players/ayumi/jet/jet3h models/players/ayumi/jet/jet3g models/players/ayumi/jet/jet3f models/players/ayumi/jet/jet3e models/players/ayumi/jet/jet3d models/players/ayumi/jet/jet3c models/players/ayumi/jet/jet3b models/players/ayumi/jet/jet3a 
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 15 
	}
	{
		animmap 15 models/players/ayumi/jet/jet3g models/players/ayumi/jet/jet3f models/players/ayumi/jet/jet3e models/players/ayumi/jet/jet3d models/players/ayumi/jet/jet3c models/players/ayumi/jet/jet3b models/players/ayumi/jet/jet3a models/players/ayumi/jet/jet3h 
		blendfunc add
		rgbGen wave sawtooth 0 1 0 15 
	}
	{
		animmap 15 models/players/ayumi/jet/jet3smk1 models/players/ayumi/jet/jet3smk2 models/players/ayumi/jet/jet3smk3 models/players/ayumi/jet/jet3smk4 models/players/ayumi/jet/jet3smk5 models/players/ayumi/jet/jet3smk6 models/players/ayumi/jet/jet3smk7 
		blendfunc add
		rgbGen const ( 0.337255 0.184314 0.466667 )
		tcMod rotate 153
	}
	{
		animmap 15 models/players/ayumi/jet/jet3smk7 models/players/ayumi/jet/jet3smk1 models/players/ayumi/jet/jet3smk2 models/players/ayumi/jet/jet3smk3 models/players/ayumi/jet/jet3smk4 models/players/ayumi/jet/jet3smk5 models/players/ayumi/jet/jet3smk6 
		blendfunc add
		rgbGen const ( 0.294118 0.235294 0.482353 )
		tcMod rotate -95
	}
}

models/players/ayumi/bootjenna
{
	cull disable
	{
		map models/players/ayumi/bootjenna
		rgbGen lightingDiffuse
	}
}

models/players/ayumi/bootjenna_red
{
	cull disable
	{
		map models/players/ayumi/bootjenna_red
		rgbGen lightingDiffuse
	}
}

models/players/ayumi/bootjenna_blue
{
	cull disable
	{
		map models/players/ayumi/bootjenna_blue
		rgbGen lightingDiffuse
	}
}

models/players/ayumi/hairjenna
{
	cull disable
	{
		map models/players/ayumi/hairjenna
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/hairjenna_red
{
	cull disable
	{
		map models/players/ayumi/hairjenna_red
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/hairjenna_blue
{
	cull disable
	{
		map models/players/ayumi/hairjenna_blue
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/shirtjenna
{
	cull disable
	{
		map models/players/ayumi/shirtjenna
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/shirtjenna_red
{
	cull disable
	{
		map models/players/ayumi/shirtjenna_red
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/ayumi/shirtjenna_blue
{
	cull disable
	{
		map models/players/ayumi/shirtjenna_blue
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

