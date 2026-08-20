// models/weapons2/shotgun/f_shotgun
//{
//	sort additive
//	cull disable
//	{
//		map	models/weapons2/shotgun/f_shotgun
//		blendfunc add
//	}
//} 

muzzleSprite
{
	sort additive
	cull disable
	deformVertexes autosprite
	{
		map	models/weapons2/shotgun/shotgun_flash
		blendfunc add
	}
}
muzzleSide
{
	sort additive
	deformVertexes autosprite2
	{
		map	models/weapons2/shotgun/shotgun_flashside
		blendfunc add
	}
}

muzzleSphere
{
	sort additive
	cull disable
	{
		map	models/weapons2/shotgun/shotgun_flash
		blendfunc add
	}
}

rocketProjectile
{

	{
		map	models/ammo/rocket/rocket
	rgbGen lightingDiffuse
	}
	{
		map models/weapons2/machinegun/woodspec
		blendfunc gl_dst_color gl_src_color
		//rgbGen lightingDiffuse
		tcGen environment 
	}
}

oldrocketThrustf
{
	deformVertexes autosprite2
	{
		map models/weapons2/machinegun/f_machinegun
		blendfunc add
		tcMod rotate 1246
	}
	{
		map models/weapons2/machinegun/f_machinegun
		blendfunc add
		tcMod rotate -1246
	}
}

rocketFlare
{
	deformVertexes autosprite
	{
		map textures/oafx/rocketflare
		blendfunc add
		
	}
	
}
