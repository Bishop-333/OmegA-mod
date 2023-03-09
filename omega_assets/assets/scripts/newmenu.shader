logoTitle
{
	nopicmip
	cull disable
	{
		clampmap textures/base_wall/chrome_env2.jpg
		tcGen environment 
	}
	{
		map textures/effects/tinfx.tga
		rgbGen const ( 0.5 0.75 1 )
		tcGen environment 
	}
	{
		map textures/omega/electric.tga
		blendfunc add
		tcMod scroll -0.03 0
	}
}

logoEmblem
{
	nopicmip
	cull disable
	{
		clampmap textures/base_wall/chrome_env2.jpg
		tcGen environment 
	}
	{
		map textures/effects/tinfx.tga
		rgbGen const ( 0.5 0.75 1 )
		tcGen environment 
	}
}

menu/art/cut_frame
{
	nopicmip
	{
		map menu/art/cutred.tga
		blendfunc filter
	}
	{
		map menu/art/cut_frame.tga
		blendfunc blend
	}
}

menu/art/addbotframe
{
	nopicmip
	{
		map menu/art/addbotred.tga
		blendfunc filter
	}
	{
		map menu/art/addbotframe.tga
		blendfunc blend
	}
}