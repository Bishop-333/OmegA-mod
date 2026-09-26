bulletExplosion
{
	cull disable
	{
		map textures/oafx/spark1
		blendfunc gl_one gl_src_alpha
		rgbGen wave inversesawtooth 0 1 0 2.8 
		tcMod scroll -1.5 0
	}
	{
		map textures/oafx/spark3
		blendfunc gl_src_alpha gl_dst_alpha
		rgbGen lightingDiffuse
		tcMod scroll 0 -0.7
		alphaGen wave sawtooth 1 -1 0 1.6 
	}
}

OLDrocketExplosion
{
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 77
		tcMod stretch sin 0.3 0.4 0 0.4 
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 33
		tcMod stretch sin 0.8 -0.4 0 0.1 
	}
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate -17
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate -77
	}
}

bloodExplosion
{
	nopicmip
	{
		clampmap gfx/2d/bloodspew
		blendfunc blend
		tcMod rotate 77
		tcMod stretch sin 0 2 0 0.4 
		alphaGen wave inversesawtooth 0 1 0 1 
	}
	{
		clampmap gfx/2d/bloodspew
		blendfunc blend
		tcMod rotate -43
		tcMod stretch sin 0 1.7 0 0.4 
		alphaGen wave inversesawtooth 0 1 0 1 
	}
}

olderrocketExplosion
{
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 77
		tcMod stretch sin 0 1 0 0.4 
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 33
		tcMod stretch sin 0 1 0 0.4 
	}
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate -17
		tcMod stretch sawtooth 0 1.8 0 1 
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate -77
		tcMod stretch sawtooth 0.3 1 0 1 
	}
}

rocketExplosion
{
	{
		animmap 8 models/weaphits/rlboom/rlboom_1 models/weaphits/rlboom/rlboom_2 models/weaphits/rlboom/rlboom_3 models/weaphits/rlboom/rlboom_4 models/weaphits/rlboom/rlboom_5 models/weaphits/rlboom/rlboom_6 models/weaphits/rlboom/rlboom_7 models/weaphits/rlboom/rlboom_8 
		blendfunc gl_one gl_src_alpha
		rgbGen wave inversesawtooth 0 1 0 8 
	}
	{
		animmap 8 models/weaphits/rlboom/rlboom_2 models/weaphits/rlboom/rlboom_3 models/weaphits/rlboom/rlboom_4 models/weaphits/rlboom/rlboom_5 models/weaphits/rlboom/rlboom_6 models/weaphits/rlboom/rlboom_7 models/weaphits/rlboom/rlboom_8 models/weaphits/rlboom/rlboom_8 
		blendfunc gl_one gl_src_alpha
		rgbGen wave sawtooth 0 1 0 8 
	}
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0.1 0.8 0 1 
		tcMod rotate 33
		tcMod stretch inversesawtooth 0.1 1 0 0.4 
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 17
		tcMod stretch sin 0.2 1 0 0.4 
	}
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave sin 0 1 0 1 
		tcMod rotate -8
		tcMod stretch sawtooth 0.1 1.5 0 1
	}
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0.1 1 0 1
		tcMod rotate -33
		tcMod stretch sawtooth 0.4 0.5 0 1 
	}
}

lasmaExplosion
{
	cull disable
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 4 
		tcMod rotate 300
		tcMod stretch sin 0.3 0.4 0 0.4 
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 4 
		tcMod rotate 122
		tcMod stretch sin 0.8 -0.7 0 0.1 
	}
}

ailExplosion
{
	cull disable
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 12
		tcMod stretch sin 0.3 0.4 0 0.4 
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate 15
		tcMod stretch sin 0.8 -0.4 0 0.1 
	}
	{
		clampmap textures/oa/fiar
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate -12
	}
	{
		clampmap textures/oa/fiar2
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
		tcMod rotate -78
	}
}
