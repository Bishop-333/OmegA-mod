wake
{
	cull disable
	{
		animmap 30 sprites/multwake1 sprites/multwake2 sprites/multwake3 sprites/multwake4 sprites/multwake5 sprites/multwake6 sprites/multwake7 sprites/multwake8 
		blendfunc gl_dst_color gl_src_color
	}
}

newishwake
{
	{
		animmap 8 sprites/splash6 sprites/splash5 sprites/splash4 sprites/splash3 sprites/splash2 
		blendfunc gl_src_alpha gl_one
		alphaGen wave inversesawtooth 0 1 0 8 
	}
	{
		animmap 8 sprites/splash5 sprites/splash4 sprites/splash3 sprites/splash2 sprites/splash6 
		blendfunc gl_src_alpha gl_one
		alphaGen wave sawtooth 0 1 0 8 
	}
}

gfx/misc/tracer
{
	cull disable
	{
		map gfx/misc/tracer2
		blendfunc add
	}
}


gfx/damage/bullet_mrk
{
	nopicmip
	polygonoffset
	{
		map gfx/damage/bulletmult
		blendfunc gl_dst_color gl_src_color
		alphaGen Vertex
	}
}

oldgfx/damage/bullet_mrk
{
	polygonoffset
	{
		map gfx/damage/bullet_mrk
		blendfunc gl_zero gl_one_minus_src_color
		rgbGen Vertex
	}
}

gfx/damage/burn_med_mrk
{
	nopicmip
	polygonoffset
	{
		map gfx/damage/burn_med_mrk
		blendfunc gl_zero gl_one_minus_src_color
		rgbGen Vertex
	}
}

gfx/damage/hole_lg_mrk
{
	nopicmip
	polygonoffset
	{
		map gfx/damage/hole_lg_mrk
		blendfunc gl_zero gl_one_minus_src_color
		rgbGen Vertex
	}
}

gfx/damage/plasma_mrk
{
	nopicmip
	polygonoffset
	{
		map gfx/damage/plasma_mrk
		blendfunc blend
		rgbGen Vertex
		alphaGen Vertex
	}
}

markShadow
{
	polygonoffset
	{
		map gfx/damage/shadow
		blendfunc gl_zero gl_one_minus_src_color
		rgbGen Vertex
	}
}

markShadow2
{
	nopicmip
	nomipmaps
	polygonoffset
	{
		map gfx/damage/shadow2.jpg
		blendfunc gl_one gl_one
		rgbGen Vertex
	}
}

projectionShadow
{
	polygonoffset
	deformvertexes projectionshadow		//need this
	{
		map $whiteimage
		blendfunc filter
		rgbGen wave square 0 0 0 0 
	}
}

oldwake
{
	{
		clampmap sprites/splash
		blendfunc add
		rgbGen wave sin 0.7 0.3 0.25 0.5 
		tcMod rotate 250
		tcMod stretch sin 0.9 0.1 0 0.7 
	}
	{
		clampmap sprites/splash
		blendfunc add
		rgbGen wave sin 0.7 0.3 0.25 0.4 
		tcMod rotate -230
		tcMod stretch sin 0.9 0.05 0 0.9 
	}
}


waterBubble
{
	sort underwater
	cull disable
	{
		map sprites/bubble
		blendfunc blend
		rgbGen Vertex
		alphaGen Vertex
	}
}

