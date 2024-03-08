models/weapons2/machinegun/muzzlside
{
	cull disable
	nopicmip
	{
		map models/weapons2/machinegun/muzzlside.tga
		blendfunc add
	}
}

models/weapons2/shells/mgunshell
{
	cull disable
	nopicmip
	{
		map models/weapons2/shells/mgunshell.tga
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
		map models/weapons2/shells/sgunshell.tga
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/shells/mgunshell.tga
		blendfunc add
		rgbGen lightingDiffuse
		tcGen environment 
	}
	{
		map models/weapons2/shells/sgunshell.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

models/weapons2/machinegun/muzzlecenter
{
	nopicmip
	deformVertexes autosprite
	{
		map models/weapons2/machinegun/f_machinegun.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		map models/weapons2/machinegun/f_machinegun.tga
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons2/machinegun/flare
{
	nopicmip
	deformVertexes autosprite
	{
		map models/weapons2/machinegun/flare.tga
		blendfunc add
	}
}

models/weapons2/machinegun/skin
{
	nopicmip
	{
		map models/weapons2/machinegun/mgun.tga
		rgbGen lightingDiffuse
	}
	{
		map gfx/fx/detail/d_met.tga
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		detail
	}
	{
		map gfx/fx/spec/gunmetal.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		alphaGen lightingSpecular
		detail
	}
	{
		map models/weapons2/machinegun/mgun.tga
		blendFunc gl_one gl_zero
		alphaFunc LT128
		rgbGen lightingDiffuse
	}
}

models/weapons2/machinegun/tommy
{
	nopicmip
	{
		map models/weapons2/machinegun/tomtex.tga
		rgbGen lightingDiffuse
	}
	{
		map models/weapons2/machinegun/woodspec.tga
		blendfunc gl_dst_color gl_src_color
		tcGen environment 
	}
	{
		map models/weapons2/machinegun/tomtex.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

