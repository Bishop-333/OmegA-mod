smallCross
{
	{
		map models/powerups/armor/shard_env2.jpg
		tcMod rotate -76
		tcGen environment 
	}
	{
		map models/powerups/health/cross.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

mediumCross
{
	{
		map textures/suction/solid_yellow.tga
		tcMod rotate -76
		tcGen environment 
	}
	{
		map models/powerups/health/cross.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

largeCross
{
	{
		map textures/suction/solid_red.tga
		tcMod rotate -76
		tcGen environment 
	}
	{
		map models/powerups/health/cross.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

megaCross
{
	{
		map textures/effects/megahelth.tga
		tcMod rotate -76
		tcGen environment 
	}
	{
		map models/powerups/health/cross.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

smallCrossFlare
{
	deformVertexes autosprite
	{
		clampmap textures/oafx/greenflr1.tga
		blendfunc add
		tcMod rotate -149
		tcMod stretch sin -1 1 0 0.2 
	}
	{
		clampmap textures/oafx/greenflr2.tga
		blendfunc add
		tcMod rotate 1765
		tcMod stretch sin 0 -1.2 0 0.3 
	}
}

oldflare
{
	deformVertexes autosprite
	{
		clampmap textures/oafx/flare.tga
		blendfunc add
		tcMod rotate 12
	}
	{
		clampmap textures/oafx/flare.tga
		blendfunc add
		tcMod rotate -17
	}
}

oldysunFlare
{
	deformVertexes autosprite
	{
		clampmap textures/oafx/flare.tga
		blendfunc add
		tcMod rotate 12
	}
	{
		clampmap textures/oafx/flare.tga
		blendfunc add
		tcMod rotate -17
	}
}

largeCrossFlare
{
	deformVertexes autosprite
	{
		clampmap textures/oafx/orangeflr1.tga
		blendfunc add
		tcMod rotate -46
		tcMod stretch sin -1 0.4 0 0.2 
	}
	{
		clampmap textures/oafx/orangeflr2.tga
		blendfunc add
		tcMod rotate 122
		tcMod stretch inversesawtooth -0.7 -1 0 2 
	}
}

