firstnailtrail
{
	nopicmip
	{
		map models/weapons/nailgun/nailtrail.tga
		blendfunc blend
		tcMod rotate 24
	}
	{
		map models/weapons/nailgun/nailtrail.tga
		blendfunc blend
		tcMod rotate -12
	}
}

nailtrail
{
	nopicmip
	{
		clampmap models/weapons/nailgun/nailtrail.tga
		blendfunc blend
		tcMod rotate 64
		tcMod stretch sawtooth 0.5 1 0 3.6 
		alphaGen wave inversesawtooth 0 1 0 3.6 
	}
	{
		clampmap models/weapons/nailgun/nailtrail.tga
		blendfunc blend
		tcMod rotate 565
		tcMod stretch sawtooth 0.5 1 0 3.6 
		alphaGen wave inversesawtooth 0 1 0 3.6 
	}
}

nailgunFlash
{
	cull disable
	nopicmip
	{
		clampmap models/weapons/nailgun/nailfire.tga
		blendfunc add
		rgbGen identity
		tcMod rotate 6666
	}
}

models/weapons/nailgun/nailgun
{
	nopicmip
	{
		map models/weapons/nailgun/nailgun.tga
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/nailgun/glow.tga
		blendfunc add
		rgbGen wave sin 0.25 0.75 0 0.25 
	}
}

models/weapons/nailgun/nail
{
	nopicmip
	{
		map models/weapons/nailgun/shineycrys.tga
		rgbGen identity
		tcMod scroll 1 0
		tcGen environment 
	}
}

