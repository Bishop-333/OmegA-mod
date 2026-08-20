models/weapons2/machinegun/muzzlside
{
	cull disable
	nopicmip
	{
		map models/weapons2/machinegun/muzzlside
		blendfunc add
	}
}

models/weapons2/shells/mgunshell
{
	cull disable
	nopicmip
	{
		map models/weapons2/shells/mgunshell
		rgbGen lightingDiffuse
		
	}
}


models/weapons2/shells/mgunshell_2
{
	nopicmip
	deformVertexes autosprite
    {
        clampmap models/weapons2/shells/mgunshell_2
        rgbGen lightingDiffuse
	blendFunc blend
	tcMod scale 1.4 1.4
    }

}

shellCase
{
	cull disable
	nopicmip
	{
		map models/weapons2/shells/sgunshell
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/shells/mgunshell
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/weapons2/shells/sgunshell
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/weapons2/machinegun/muzzlecenter
{
	nopicmip
	deformVertexes autosprite
	{
		map models/weapons2/machinegun/f_machinegun
		blendfunc add
		tcMod rotate 1246
	}
	{
		map models/weapons2/machinegun/f_machinegun
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons2/machinegun/flare
{
	nopicmip
	deformVertexes autosprite
	{
		map models/weapons2/machinegun/flare
		blendfunc add
	}
}

models/weapons2/machinegun/skin
{
	{
		map models/weapons2/machinegun/mgun
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/detail/d_met
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
	{
		map gfx/fx/spec/gunmetal
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
	{
		map models/weapons2/machinegun/mgun
		blendFunc gl_one gl_zero
		alphaFunc LT128
		rgbGen lightingDiffuse
	}
}

models/weapons2/machinegun/tommy
{
	nopicmip
	{
		map models/weapons2/machinegun/tomtex
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/machinegun/woodspec
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/weapons2/machinegun/tomtex
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

