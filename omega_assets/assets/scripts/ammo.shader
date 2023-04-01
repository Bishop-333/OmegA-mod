// // // // SHADERS FOR OPEN ARENA AMMOBOX POWERUPS 
// // // //  jzero --> johnzero@verizon.net
// 1.machinegun
models/powerups/ammo/machammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 1 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/machammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/machammo2.tga
		blendfunc add
		rgbGen identity
	}
}

// 2.shotgun
models/powerups/ammo/shotammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 0.5 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/shotammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/shotammo2.tga
		blendfunc add
		rgbGen identity
	}
}

// 3.grenade launcher
models/powerups/ammo/grenammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0 0.56 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/grenammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/grenammo2.tga
		blendfunc add
		rgbGen identity
	}
}

// 4.lightning gun
models/powerups/ammo/lighammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 1 0.69 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/lighammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/lighammo2.tga
		blendfunc add
		rgbGen identity
	}
}

// 5.plasma gun
models/powerups/ammo/plasammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0.8 0 1 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/plasammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/plasammo2.tga
		blendfunc add
		rgbGen identity
	}
}

//6.rocket launcher
models/powerups/ammo/rockammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 0 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/rockammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/rockammo2.tga
		blendfunc add
		rgbGen identity
	}
}

//7. railgun
models/powerups/ammo/railammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0 1 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/railammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/railammo2.tga
		blendfunc add
		rgbGen identity
	}
}

//8. BFG
models/powerups/ammo/bfgammo
{
	{
		map models/powerups/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerups/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0 0.4 1 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerups/ammo/bfgammo2
{
	{
		map textures/base_wall/metalfloor_wall_14.tga
		rgbGen const ( 0.25 0.25 0.25 )
	}
	{
		map models/powerups/ammo/bfgammo2.tga
		blendfunc add
		rgbGen identity
	}
}

