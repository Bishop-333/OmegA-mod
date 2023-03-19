models/weapons2/railgun/muzzlecenter
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weapons2/railgun/f_plasma.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		clampmap models/weapons2/railgun/f_railgun.tga
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons2/railgun/flare
{
	nopicmip
	deformVertexes autosprite
	{
		map models/weapons2/railgun/flare.tga
		blendfunc add
		rgbGen wave noise 0.5 0.5 0 1 
	}
}

models/weapons2/railgun/skin
{
	nopicmip
	{
		map models/weapons2/railgun/skin.tga
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/detail/d_met.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
	{
		map models/weapons2/railgun/skin.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/weapons2/railgun/energy
{
	nopicmip
	{
		map models/weapons2/railgun/scrolly.tga
		rgbGen entity
		tcMod scroll -2 0
	}
	{
		map models/weapons2/railgun/scrolly.tga
		blendfunc add
		rgbGen entity
		tcMod scroll -1 0
	}
	{
		map models/weapons2/railgun/railcore.tga
		blendfunc gl_dst_color gl_src_color
		rgbGen const ( 0.52549 0.533333 0.858824 )
		tcMod scale 1.1 1
		tcMod scroll -3 0
	}
}

models/weapons2/railgun/glass
{
	cull disable
	nopicmip
	{
		map textures/effects/tinfx2.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map $whiteimage 
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
}

railgunFlash
{
	cull disable
	nopicmip
	{
		clampmap models/weapons2/railgun/f_railgun2.tga
		blendfunc add
		rgbGen entity
		tcMod rotate -74
	}
	{
		clampmap models/weapons2/railgun/f_railgun2.tga
		blendfunc add
		rgbGen entity
		tcMod rotate 53
	}
}

railDisc
{
	cull disable
	nopicmip
	{
		clampmap models/weapons2/railgun/f_railgun3.tga
		blendfunc add
		rgbGen Vertex
		tcMod rotate 130
	}
}

railCore
{
	sort nearest
	cull disable
	nopicmip
	{
		map models/weapons2/railgun/railcore.tga
		blendfunc add
		rgbGen Vertex
		tcMod scroll -1 0
	}
}

