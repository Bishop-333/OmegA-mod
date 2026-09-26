models/powerups/holdable/medkit_slime
{	

	{
		map textures/liquids/proto_gruel2.jpg
		tcmod scroll 1 1
		blendfunc add
	}
}

models/powerups/instant/ebase
{
	{
		map textures/effects/envmapgold.jpg
		blendfunc gl_one gl_zero
		tcgen environment
		rgbgen identity
	}
}

models/powerups/instant/ering
{
	{
		map models/powerups/instant/ering.jpg
		blendfunc gl_one gl_one
	}
}

rcad
{
	{
		map textures/effects/regenmap2.jpg
		blendfunc gl_one gl_zero
		tcgen environment
		rgbgen identity
	}
}

models/powerups/instant/rring
{
	{
		map models/powerups/instant/rring.jpg
		blendfunc gl_one gl_one
	}
}

models/powerups/instant/h_center
{
	{
		map textures/effects/hastenv.jpg
		blendfunc gl_one gl_zero
		tcgen environment
		rgbgen identity
	}
}

models/powerups/instant/h_ring
{
	{
		map models/powerups/instant/h_ring.jpg
		blendfunc gl_one gl_one
	}
}

models/powerups/instant/flight_body
{
	{
		map textures/effects/flightenv.jpg
		blendfunc gl_one gl_zero
		tcgen environment
		rgbgen identity
	}
}

models/powerups/instant/flight_ring
{
	{
		map models/powerups/instant/flight_ring.jpg
		blendfunc gl_one gl_one
	}
}

models/powerups/armor/shard_env
{
	{
		map textures/cosmo_liquids/greenliqu1.jpg
		blendfunc add
		tcgen environment
	}
}
