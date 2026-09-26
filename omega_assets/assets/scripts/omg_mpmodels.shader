models/flags/n_flag
{
	cull disable
	deformVertexes wave 40 sin 1 4 0 1.5 
	deformVertexes wave 10 square 0 1 0.25 0.1 
	{
		map textures/base_wall/chrome_env
		rgbGen identity
		tcMod turb 1 1 0.5 0.3
		tcGen environment 
	}
	{
		map models/flags/n_flag
		depthFunc equal
		depthWrite
		alphaFunc GE128
	}
}

models/powerups/ammo/vulcammo2
{
	{
		map textures/base_wall/metalfloor_wall_14
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/vulcammo
		blendfunc add
		rgbGen identity
	}
}

models/powerups/ammo/nailammo2
{
	{
		map textures/base_wall/metalfloor_wall_14
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/nailammo
		blendfunc add
		rgbGen identity
	}
}

models/powerups/ammo/proxammo2
{
	{
		map textures/base_wall/metalfloor_wall_14
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/proxammo
		blendfunc add
		rgbGen identity
	}
}
