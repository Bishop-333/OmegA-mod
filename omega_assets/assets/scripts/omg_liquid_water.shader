textures/liquids/vorwater
{
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm water
	cull disable
	{
		map textures/liquids/vorwater
		blendfunc add
		rgbGen const ( 0.501961 0.501961 0.501961 )
		tcMod scroll -0.009 -0.005
	}
	{
		map textures/liquids/vorwater
		blendfunc add
		rgbGen const ( 0.501961 0.501961 0.501961 )
		tcMod scroll 0.004 -0.007
	}
	{
		map $lightmap
		blendFunc gl_dst_color gl_zero
		rgbgen identity		
	}
}
