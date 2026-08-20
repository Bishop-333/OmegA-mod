logoTitle
{
	nopicmip
	cull disable
	{
		clampmap textures/base_wall/chrome_env2.jpg
		tcGen environment 
	}
	{
		map textures/effects/tinfx
		rgbGen const ( 0.5 0.75 1 )
		tcGen environment 
	}
	{
		map textures/omega/electric
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
		map textures/effects/tinfx
		rgbGen const ( 0.5 0.75 1 )
		tcGen environment 
	}
}

menu/art/cut_frame
{
	nopicmip
	{
		map menu/art/cutred
		blendfunc filter
	}
	{
		map menu/art/cut_frame
		blendfunc blend
	}
}

menu/art/addbotframe
{
	nopicmip
	{
		map menu/art/addbotred
		blendfunc filter
	}
	{
		map menu/art/addbotframe
		blendfunc blend
	}
}