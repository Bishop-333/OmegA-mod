logoTitle
{
	nopicmip
	cull disable
	{
		map textures/oafx/orangechrm_2.jpg
		blendfunc add
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
		map textures/oafx/orangechrm_2.jpg
		tcMod rotate 7
		tcGen environment 
	}
}

logoHalo
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap textures/oafx/flare.tga
		blendfunc add
		rgbGen const ( 0.1019 0.3176 0.4941 )
		tcMod rotate -7
	}
	{
		clampmap textures/oafx/flare.tga
		blendfunc add
		rgbGen const ( 0.1019 0.3176 0.4941 )
		tcMod rotate 3
		tcMod stretch sin 1 -0.5 0 0.3 
	}
	{
		clampmap textures/oafx/flare.tga
		blendfunc add
		rgbGen const ( 0.1019 0.3176 0.4941 )
		tcMod rotate 9
		tcMod stretch sin 1 0.4 0 0.6 
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