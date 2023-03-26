powerups/invisibility
{
	cull disable
	{
		map gfx/damage/shadow.tga
		blendfunc blend
		tcMod rotate 86
		tcGen environment 
		alphaGen wave sin 0.03 0 0 0 
	}
}

//too invisible
powerups/invisibilityOLD
{
	cull disable
	deformVertexes wave 64 sin 0 1 0 1 
	{
		map textures/oafx/inviso.tga
		blendfunc gl_dst_color gl_src_color
		tcMod rotate 53
	}
	{
		map textures/oafx/inviso.tga
		blendfunc gl_dst_color gl_src_color
		tcMod rotate -86
	}
}

smallcrossEnv
{
	// the crosses bounce with a 0.93 frequency and they're down in the 0.5 phase, but doesn't really matter since they respawn with random a start
	cull disable
	{
		map textures/effects/smallhelth
		blendfunc gl_src_alpha gl_one
		tcMod scroll 1 0.1
		tcGen environment 
		alphaGen wave sin 0.3 0.2 0.5 0
	}
	{
		map textures/effects/smallhelth_spec
		blendfunc gl_src_alpha gl_one
		tcMod scroll 1 0.1
		tcGen environment 
		alphaGen lightingSpecular
	}
}

mediumcrossEnv
{
	// the crosses bounce with a 0.93 frequency and they're down in the 0.5 phase, but doesn't really matter since they respawn with random a start
	cull disable
	{
		map textures/effects/mediumhelth
		blendfunc gl_src_alpha gl_one
		tcMod scroll 1 0.2
		tcMod scale 0.5 0.5
		tcGen environment 
		alphaGen wave sin 0.3 0.2 0.5 0
	}
	{
		map textures/effects/mediumhelth_spec
		blendfunc gl_src_alpha gl_one
		tcMod scroll 1 0.2
		tcMod scale 0.5 0.5
		tcGen environment 
		alphaGen lightingSpecular
	}
}


largecrossEnv
{
	// the crosses bounce with a 0.93 frequency and they're down in the 0.5 phase, but doesn't really matter since they respawn with random a start
	cull disable
	{
		map textures/effects/largehelth
		blendfunc gl_src_alpha gl_one
		tcMod scroll 1 0.2
		tcMod scale 0.5 0.5
		tcGen environment 
		alphaGen wave sin 0.3 0.2 0.5 0
	}
	{
		map textures/effects/largehelth_spec
		blendfunc gl_src_alpha gl_one
		tcMod scroll 1 0.2
		tcMod scale 0.5 0.5
		tcGen environment 
		alphaGen lightingSpecular
	}
}

megacrossEnv
{
	// the crosses bounce with a 0.93 frequency and they're down in the 0.5 phase, but doesn't really matter since they respawn with random a start
	cull disable
	{
		map textures/effects/megahelth
		blendfunc gl_src_alpha gl_one
		tcMod scroll 1 0.1
		tcGen environment 
		alphaGen wave sin 0.3 0.2 0.5 0
	}
	{
		map textures/effects/megahelth_spec
		blendfunc gl_src_alpha gl_one
		tcMod scroll 1 0.2
		tcGen environment 
		alphaGen lightingSpecular
	}
}

/*
powerups/quadi
{
	{
		map textures/oafx/quadmultshell.tga
		blendfunc gl_dst_color gl_src_color
		tcMod rotate 53
	}
}
*/

powerups/quad
{
	deformVertexes wave 100 sin 0.5 0 0 0 
	{
		map textures/oafx/quadshell.tga
		blendfunc add
		tcMod rotate 75
		tcGen environment 
	}
}

/*
powerups/quade
{
	cull disable
	deformVertexes wave 100 sin 1 0 0 0 
	{
		map textures/oafx/quadmultshell
		blendfunc gl_src_alpha gl_one
		tcMod scroll 2 1
		alphaGen wave sin 0.5 0 0 0
		tcGen environment
	}
	{
		map gfx/fx/spec/spots.tga
		blendfunc gl_src_alpha gl_one
		//rgbGen const ( 0.266667 0.423529 0.658824 ) // #446ba8
		rgbGen const ( 0.30196 0.76470 1.0 ) // #4dc3ff
		tcMod scroll 2 1
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}

powerups/quadWeapong
{
	deformVertexes wave 100 sin 1 0 0 0 
	{
		map textures/oafx/quadmultshell
		blendfunc gl_src_alpha gl_one
		tcMod scroll 2 1
		alphaGen wave sin 0.5 0 0 0
		tcGen environment 
	}
	{
		map gfx/fx/spec/spots.tga
		blendfunc gl_src_alpha gl_one
		//rgbGen const ( 0.266667 0.423529 0.658824 ) // #446ba8
		rgbGen const ( 0.30196 0.76470 1.0 ) // #4dc3ff
		tcMod scroll 2 1
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}
*/

powerups/quadWeapon
{
	deformVertexes wave 100 sin 1 0 0 0 
	{
		map textures/oafx/quadshell.tga
		blendfunc add
		tcMod rotate 75
		tcGen environment 
	}
}

powerups/battleSuit
{
	{
		map textures/oafx/suitshell
		blendfunc add
		rgbGen identity
		tcmod turb 0 0.12 0 0.27
	}
	{
		map gfx/fx/spec/skin.tga
		blendfunc gl_src_alpha gl_one
		//rgbGen const ( 0.74902 0.403922 0.176471 ) // #bf672d
		rgbGen const ( 1.0 0.65490 0.25882 ) // #ffa742
		tcMod scroll 0.5 0.5
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}

powerups/battleWeapon
{
	{
		map textures/oafx/suitshell
		blendfunc add
		rgbGen identity
		tcmod turb 0 0.12 0 0.27
	}
	{
		map gfx/fx/spec/skin.tga
		blendfunc gl_src_alpha gl_one
		//rgbGen const ( 0.74902 0.403922 0.176471 ) // #bf672d
		rgbGen const ( 1.0 0.65490 0.25882 ) // #ffa742
		tcMod scroll 0.5 0.5
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}

powerups/regen
{
	deformVertexes wave 100 sin 1 0 0 0 
	{
		map textures/oafx/regenshell.tga
		blendfunc gl_src_alpha gl_one
		tcMod rotate 75
		tcGen environment
		alphaGen wave sin 0.5 0 0 0
	}
	{
		map gfx/fx/spec/skin.tga
		blendfunc gl_src_alpha gl_one
		rgbGen const ( 1 0.50196 0.50196 ) // #ff8080
		tcMod scroll 0.5 0.5
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}

transparentWeapon
{
	nopicmip
	{
		map textures/omega/transparent.tga
		blendfunc add
		tcGen environment
	}
}

brightRedPlayers
{
	cull disable
	deformVertexes wave 100 sin 0.5 0 0 0
	cull back
	{
		map textures/suction/solid_white
		blendfunc add
		rgbGen const ( 1 0 0 )
	}
}

brightYellowPlayers
{
	cull disable
	deformVertexes wave 100 sin 0.5 0 0 0
	cull back
	{
		map textures/suction/solid_white
		blendfunc add
		rgbGen const ( 1 1 0 )
	}
}

brightGreenPlayers
{
	cull disable
	deformVertexes wave 100 sin 0.5 0 0 0
	cull back
	{
		map textures/suction/solid_white
		blendfunc add
		rgbGen const ( 0 1 0 )
	}
}

brightCyanPlayers
{
	cull disable
	deformVertexes wave 100 sin 0.5 0 0 0
	cull back
	{
		map textures/suction/solid_white
		blendfunc add
		rgbGen const ( 0 1 1 )
	}
}

brightBluePlayers
{
	cull disable
	deformVertexes wave 100 sin 0.5 0 0 0
	cull back
	{
		map textures/suction/solid_white
		blendfunc add
		rgbGen const ( 0 0 1 )
	}
}

brightPinkPlayers
{
	cull disable
	deformVertexes wave 100 sin 0.5 0 0 0
	cull back
	{
		map textures/suction/solid_white
		blendfunc add
		rgbGen const ( 1 0 1 )
	}
}

brightWhitePlayers
{
	cull disable
	deformVertexes wave 100 sin 0.5 0 0 0
	cull back
	{
		map textures/suction/solid_white
		blendfunc add
	}
}
