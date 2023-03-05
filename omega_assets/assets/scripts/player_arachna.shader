models/players/arachna/hair
{
	cull disable
	{
		map models/players/arachna/hair.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/hairspec.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/hairred
{
	cull disable
	{
		map models/players/arachna/hairred.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/hairspec.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/jewelry
{
	cull disable
	{
		map models/players/arachna/jewelry.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/jewelry.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/jewelry3
{
	cull disable
	{
		map models/players/arachna/jewelry3.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map gfx/fx/spec/jewelry.tga
		blendfunc gl_dst_color gl_dst_alpha
		rgbGen lightingDiffuse
		tcGen environment 
		depthFunc equal
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/torso
{
	{
		map models/players/arachna/torso.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/arachna/torso.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/torsoblue
{
	{
		map models/players/arachna/torsoblue.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/arachna/torsoblue.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/torsored
{
	{
		map models/players/arachna/torsored.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/arachna/torsored.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/spider
{
	{
		map models/players/arachna/spider.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/arachna/spider.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/redspider
{
	{
		map models/players/arachna/redspider.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/arachna/redspider.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/bluespider
{
	{
		map models/players/arachna/bluespider.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/arachna/bluespider.tga
		blendfunc gl_src_alpha gl_one
		rgbGen lightingDiffuse
		alphaGen lightingSpecular
		detail
	}
}

models/players/arachna/forlorna_hair
{
     cull disable
        {
                map models/players/arachna/forlorna_hair.tga
                alphaFunc GE128
		depthWrite
		rgbGen lightingDiffuse
        }
}

models/players/arachna/forlorna_jewelry
{
     cull disable
        {
                map models/players/arachna/forlorna_jewelry.tga
                alphaFunc GE128
		depthWrite
		rgbGen lightingDiffuse
        }
}
