f_bfg3
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weapons2/bfg/f_bfg3
		blendfunc add
		rgbGen const ( 0.376471 0.576471 0.403922 )
		tcMod rotate 8288
	}
	{
		clampmap models/weapons2/bfg/f_bfg3
		blendfunc add
		rgbGen const ( 0.478431 0.603922 0.447059 )
		tcMod rotate -2288
		tcMod stretch sin 1.3 0 0 0 
	}
}

f_bfg1
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weapons2/bfg/f_bfg3
		blendfunc add
		rgbGen const ( 0.376471 0.576471 0.403922 )
		tcMod rotate 8288
	}
	{
		clampmap models/weapons2/bfg/f_bfg3
		blendfunc add
		rgbGen const ( 0.478431 0.603922 0.447059 )
		tcMod rotate -2288
		tcMod stretch sin 1.3 0 0 0 
	}
}

f_bfg2
{
	cull disable
	nopicmip
	{
		clampmap models/weapons2/bfg/f_bfg2
		blendfunc add
		rgbGen const ( 0.694118 0.694118 0.694118 )
		tcMod rotate 2122
	}
	{
		clampmap models/weapons2/bfg/f_bfg2
		blendfunc add
		rgbGen const ( 0.286275 0.54902 0.25098 )
		tcMod rotate -3201
		tcMod stretch sin 1.3 0 0 0 
	}
}

BFGNexus
{
	nopicmip
	deformVertexes autosprite
	{
		clampmap models/weaphits/bfg
		blendfunc add
		tcMod rotate 999
	}
	{
		clampmap models/weaphits/bfg3
		blendfunc add
		rgbGen const ( 0.188235 0.247059 0.180392 )
		tcMod rotate 700
		tcMod stretch sin 1.3 0.3 0 4 
	}
	{
		clampmap models/weaphits/bfg2
		blendfunc add
		rgbGen const ( 0.254902 0.352941 0.227451 )
		tcMod rotate 244
		tcMod stretch sin 1.3 0.3 0 4 
	}
}

BFGTrail
{
	cull disable
	nopicmip
	{
		clampmap models/weaphits/bfg2
		blendfunc add
		rgbGen const ( 0.694118 0.694118 0.694118 )
		tcMod rotate 1522
	}
	{
		clampmap models/weaphits/bfg2
		blendfunc add
		rgbGen const ( 0.286275 0.54902 0.25098 )
		tcMod rotate -1222
		tcMod stretch sin 1.3 0.3 0 4 
	}
}
