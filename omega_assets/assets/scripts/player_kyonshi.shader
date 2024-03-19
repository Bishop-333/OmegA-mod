models/players/kyonshi/hair
{
	cull disable
	{
		map models/players/kyonshi/hair.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/kyonshi/torso
{
	{
		map models/players/kyonshi/torso.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/envmapgold.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/torso.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/lower
{
	{
		map models/players/kyonshi/lower.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/envmapgold.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/lower.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/eyes
{
	{
		map models/players/kyonshi/eyes.tga
		rgbGen lightingDiffuse
	}
	{
		clampmap textures/effects/skinspecmulttin.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
}

models/players/kyonshi/eyeserr
{
	{
		map models/players/kyonshi/eyes.tga
		rgbGen lightingDiffuse
	}
	{
		clampmap textures/effects/eyespec.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
}

models/players/kyonshi/skin
{
	{
		map models/players/kyonshi/skin.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/players/kyonshi/skin.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/skinde
{
	{
		map models/players/kyonshi/skin.tga
		rgbGen lightingDiffuse
	}
	{
		map $whiteimage 
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
	}
	{
		map models/players/kyonshi/skin.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/skincrap
{
	{
		map $whiteimage 
		rgbGen lightingDiffuse
	}
	{
		map models/players/kyonshi/skin.tga
		blendfunc gl_dst_color gl_one_minus_src_alpha
		rgbGen identity
		alphaGen lightingSpecular
	}
}

// -----------------------------------------------------------
// RED SKIN!
// -----------------------------------------------------------
models/players/kyonshi/hairred
{
	cull disable
	{
		map models/players/kyonshi/hairred.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/kyonshi/sleevered
{
	cull disable
	{
		map models/players/kyonshi/torsored.tga
		blendfunc blend
		rgbGen lightingDiffuse
		alphaGen wave sin 0.8 0 0 0 
	}
}

models/players/kyonshi/sleeve
{
	cull disable
	{
		map models/players/kyonshi/torso.tga
		blendfunc blend
		rgbGen lightingDiffuse
		alphaGen wave sin 0.8 0 0 0 
	}
}

models/players/kyonshi/sleeveblue
{
	cull disable
	{
		map models/players/kyonshi/torsoblue.tga
		blendfunc blend
		rgbGen lightingDiffuse
		alphaGen wave sin 0.8 0 0 0 
	}
}

models/players/kyonshi/dress
{
	cull disable
	{
		map models/players/kyonshi/lower.tga
		blendfunc blend
		rgbGen lightingDiffuse
		alphaGen wave sin 0.8 0 0 0 
	}
}

models/players/kyonshi/dressblue
{
	cull disable
	{
		map models/players/kyonshi/lowerblue.tga
		blendfunc blend
		rgbGen lightingDiffuse
		alphaGen wave sin 0.8 0 0 0 
	}
}

models/players/kyonshi/dressred
{
	cull disable
	{
		map models/players/kyonshi/lowerred.tga
		blendfunc blend
		rgbGen lightingDiffuse
		alphaGen wave sin 0.8 0 0 0 
	}
}

models/players/kyonshi/torsored
{
	{
		map models/players/kyonshi/torsored.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/envmapgold.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/torsored.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/lowerred
{
	{
		map models/players/kyonshi/lowerred.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/envmapgold.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/lowerred.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/eyesred
{
	{
		map models/players/kyonshi/eyesred.tga
		rgbGen lightingDiffuse
	}
	{
		clampmap textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		clampmap textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		clampmap textures/effects/skinspecmulttin.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
}

models/players/kyonshi/skinred
{
	{
		map models/players/kyonshi/skinred.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/skinspecmult2.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map textures/effects/skinspecmulttin.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/players/kyonshi/skinred.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

// ---------------------------------------------------------
// BLUE SKIN !!!!
// ---------------------------------------------------------
models/players/kyonshi/hairblue
{
	cull disable
	{
		map models/players/kyonshi/hairblue.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/players/kyonshi/torsoblue
{
	{
		map models/players/kyonshi/torsoblue.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx2d.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/torsoblue.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/lowerblue
{
	{
		map models/players/kyonshi/lowerblue.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/tinfx2d.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/lowerblue.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/eyesblue
{
	{
		map models/players/kyonshi/eyesblue.tga
		rgbGen lightingDiffuse
	}
	{
		clampmap textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		clampmap textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		clampmap textures/effects/skinspecmulttin.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
}

models/players/kyonshi/skinblue
{
	{
		map models/players/kyonshi/skinblue.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/skinspecmult2.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map textures/effects/skinspecmulttin.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/players/kyonshi/skinblue.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

// ---------------------------------------------------------
// PM SKIN !!!!
// ---------------------------------------------------------
models/players/kyonshi/pm_torso
{
	{
		map models/players/kyonshi/torso.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/envmapgold.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/torso.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/kyonshi/pm_torso.tga
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/kyonshi/pm_lower
{
	{
		map models/players/kyonshi/lower.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/envmapgold.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/players/kyonshi/lower.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/kyonshi/pm_lower.tga
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/kyonshi/pm_eyes
{
	{
		map models/players/kyonshi/eyes.tga
		blendFunc gl_one gl_zero
		rgbGen lightingDiffuse
	}
	{
		clampmap textures/effects/skinspecmulttin.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/players/kyonshi/pm_eyes.tga
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

models/players/kyonshi/pm_skin
{
	{
		map models/players/kyonshi/skin.tga
		rgbGen lightingDiffuse
	}
	{
		map textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/players/kyonshi/skin.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/players/kyonshi/pm_skin.tga
		blendFunc gl_one gl_zero
		alphaFunc GE128
		rgbGen entity
	}
}

// Hidden skin of recolor experiments.

models/players/kyonshi/skinbeh
{
	{
		map models/players/kyonshi/skinblue.tga
		rgbGen const ( 0.607843 0.788235 0.882353 )
	}
	{
		map textures/effects/skinspecmult2.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map textures/effects/skinspecmult.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map textures/effects/skinspecmulttin.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/players/kyonshi/skinred.tga
		blendfunc blend
		rgbGen const ( 0.411765 0.45098 0.796079 )
	}
	{
		map $whiteimage 
		blendfunc filter
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/torsobeh
{
	{
		map textures/oafx/suitshell.tga
		rgbGen identity
		tcGen environment 
	}
	{
		map models/players/kyonshi/torso.tga
		blendfunc blend
		rgbGen const ( 0.705882 0.0862745 0.972549 )
	}
	{
		map $whiteimage 
		blendfunc filter
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/lowerbeh
{
	{
		map textures/oafx/suitshell.tga
		rgbGen identity
		tcGen environment 
	}
	{
		map models/players/kyonshi/lower.tga
		blendfunc blend
		rgbGen const ( 0.643137 0.0862745 0.972549 )
	}
	{
		map $whiteimage 
		blendfunc filter
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/cuffbeh
{
	cull disable
	{
		map textures/oafx/suitshell.tga
		rgbGen lightingDiffuse
		tcGen environment 
	}
}

models/players/kyonshi/eyesbeh
{
	{
		map models/players/kyonshi/eyes.tga
		rgbGen lightingDiffuse
	}
	{
		clampmap textures/effects/skinspec.tga
		blendfunc add
		tcGen environment 
	}
	{
		map models/players/kyonshi/eyes.tga
		blendfunc filter
	}
	{
		map models/players/kyonshi/eyes.tga
		blendfunc add
		rgbGen lightingDiffuse
	}
}

models/players/kyonshi/hairbeh
{
	cull disable
	{
		map models/players/kyonshi/hair.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}
