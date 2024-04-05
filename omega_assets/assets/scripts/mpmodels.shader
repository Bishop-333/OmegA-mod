models/flags/pole
{
	{
		map textures/base_wall/chrome_env.tga
		rgbGen lightingDiffuse
		tcMod scale 0.5 0.5
		tcGen environment 
	}
	{
		map models/flags/pole.tga
		blendfunc filter
		rgbGen identity
	}
}

models/flags/n_flag
{
	cull disable
	deformVertexes wave 40 sin 1 4 0 1.5 
	deformVertexes wave 10 square 0 1 0.25 0.1 
	{
		map textures/base_wall/chrome_env.tga
		rgbGen identity
		tcMod turb 1 1 0.5 0.3
		tcGen environment 
	}
	{
		map models/flags/n_flag.tga
		depthFunc equal
		depthWrite
		alphaFunc GE128
	}
}

models/powerups/orb/r_orb
{
	cull disable
	{
		map textures/effects/tin_red.tga
		blendfunc add
		rgbGen identity
		tcMod turb 1 1 0.5 1
		tcGen environment 
	}
}

models/powerups/orb/b_orb
{
	cull disable
	{
		map textures/effects/tin_blue.tga
		blendfunc add
		rgbGen identity
		tcMod turb 1 1 0.5 1
		tcGen environment 
	}
}

models/powerups/orb/shell
{
	cull disable
	{
		map textures/effects/envmapdimb.tga
		blendfunc add
		tcGen environment 
	}
}

overloadBase
{
	{
		map textures/effects/envmapdim.tga
		rgbGen lightingDiffuse
		tcMod rotate 2
		tcGen environment 
	}
	{
		map textures/effects/envmapdimb.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcMod rotate -7
		tcGen environment 
	}
}

overloadProngs
{
	{
		map textures/effects/envmapdim.tga
		rgbGen lightingDiffuse
		tcMod rotate 2
		tcGen environment 
	}
	{
		map textures/effects/envmapdimb.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcMod rotate -7
		tcGen environment 
	}
}

overloadCrystal
{
	{
		map textures/effects/sky.tga
		rgbGen entity
		tcMod scroll 1 0
		tcGen environment 
	}
	{
		map textures/effects/envmapdim.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcMod rotate 2
		tcGen environment 
	}
	{
		map textures/effects/envmapdimb.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcMod rotate -7
		tcGen environment 
	}
}

overloadSphere
{
	cull disable
	{
		map textures/flares/twilightflare.tga
		blendfunc add
		rgbGen entity
		tcMod rotate 57
		tcMod scroll 3 5
		tcGen environment 
	}
	{
		map textures/flares/twilightflare.tga
		blendfunc add
		rgbGen entity
		tcMod rotate -166
		tcMod scroll -7 -3
		tcGen environment 
	}
}

kamikazePowerup
{
	{
		map textures/effects/envmapdimb.tga
		rgbGen lightingDiffuse
		tcMod rotate 54
		tcGen environment 
	}
}

kamikazeShell
{
	cull disable
	{
		map textures/flares/lava.tga
		blendfunc add
		rgbGen const ( 1 0.513726 0.215686 )
		tcMod rotate 57
		tcMod scroll 3 5
		tcGen environment 
	}
}

scStrip
{
	cull disable
	{
		map models/powerups/scstrip.tga
		blendfunc add
		rgbGen const ( 0.368627 1 0.368627 )
		tcMod scroll -2 0
	}
}

gdStrip
{
	cull disable
	{
		map models/powerups/gdstrip.tga
		blendfunc add
		rgbGen const ( 0.494118 0.372549 0.996078 )
		tcMod scroll -2 0
	}
}

arStrip
{
	cull disable
	{
		map models/powerups/arstrip.tga
		blendfunc add
		rgbGen const ( 1 0.780392 0.368627 )
		tcMod scroll -2 0
	}
}

dbStrip
{
	cull disable
	{
		map models/powerups/dblrstrip.tga
		blendfunc add
		rgbGen const ( 1 0.368627 0.384314 )
		tcMod scroll -2 0
	}
}

runeScout
{
	{
		map textures/effects/tinfx2c.tga
		rgbGen const ( 0.658824 1 0.658824 )
		tcGen environment 
	}
}

runeAmreg
{
	{
		map textures/effects/tinfx2b.tga
		rgbGen const ( 1 0.619608 0.2 )
		tcGen environment 
	}
}

runeGuard
{
	{
		map textures/effects/tinfx2c.tga
		rgbGen const ( 0.47451 0.568627 1 )
		tcGen environment 
	}
}

runeDoubler
{
	{
		map textures/effects/tinfx2c.tga
		rgbGen const ( 1 0.176471 0.176471 )
		tcGen environment 
	}
}

models/powerups/ammo/vulcammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0.560784 0.560784 0.560784 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/nailammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 0.309804 0.309804 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/proxammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0.921569 0.819608 0.588235 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/vulcammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/vulcammo.tga
		blendfunc add
		rgbGen identity
	}
}

models/powerups/ammo/nailammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/nailammo.tga
		blendfunc add
		rgbGen identity
	}
}

models/powerups/ammo/proxammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/proxammo.tga
		blendfunc add
		rgbGen identity
	}
}

popshaft
{
	cull disable
	{
		map models/powerups/telezap.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1.8 
		tcMod scroll 0.6 0
	}
}

popflare
{
	deformVertexes autosprite
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate 766
		tcMod stretch inversesawtooth 0 1 0 1.8 
	}
}

