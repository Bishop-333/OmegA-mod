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
