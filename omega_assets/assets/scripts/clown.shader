textures/clown/blue_banner
{
	
	surfaceparm nomarks
	cull none
	nopicmip
 	deformVertexes wave 256 sin 0 7 0 0.4
	
	{
		map $lightmap
		rgbGen identity
	}
	{
		clampmap textures/clown/blue_banner.jpg
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity

	}
}

textures/clown/red_banner
{
	
	surfaceparm nomarks
	cull none
	nopicmip
	deformVertexes wave 256 sin 0 7 0 0.4
	
	{
		map $lightmap
		rgbGen identity
	}
	{
		clampmap textures/clown/red_banner.jpg
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		
	}
} 

textures/clown/bleeding-wall
{
	qer_editorimage textures/clown/bleeding-wall
	surfaceparm nomarks
	surfaceparm trans
	cull none
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/evil8_base/e8crete03.jpg
		rgbGen identity
		blendFunc GL_ONE GL_ZERO
	}
	{
		map textures/clown/fleshy_t
		blendFunc gl_dst_color gl_zero
		rgbGen identity
		alphaFunc GT0
		depthWrite
		tcMod scroll 0 -.1
		tcMod turb .02 .02 .5 .2
	}
}

textures/clown/portal
{
	qer_editorimage textures/clown/portal
	q3map_surfacelight 1000
	surfaceparm nomarks
	surfaceparm trans
	cull none
	
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/skies/topclouds.jpg
		rgbGen identity
		blendFunc GL_ONE GL_ZERO
	}
	{
		map textures/clown/fleshy_t
		blendFunc GL_ONE GL_ZERO
		rgbGen identity
		alphaGen lightingSpecular
		tcMod rotate 2
		tcMod scroll 0 -1
		
	}
	{
		map textures/clown/fleshy_t
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
		tcMod rotate -2
		tcMod scroll 0 -1
		
	}
}

textures/clown/f_light2
{
	qer_editorimage textures/clown/f_light2
	surfaceparm nomarks
	q3map_surfacelight 5000
	
	
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/clown/f_light2
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
	}
	{
		map textures/clown/f_light2
		blendfunc GL_ONE GL_ONE
	}
}

textures/clown/red_1
{
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	q3map_surfacelight 30
//	cull none
	polygonoffset	
	{
		map textures/clown/red_1
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen wave sin 1 1.4 2 1.2
		depthFunc equal
	}
}

textures/clown/red_2
{
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	q3map_surfacelight 30
	//cull none
	polygonoffset	
	{
		map textures/clown/red_2
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen wave sin 1 1.4 2 1.2
		depthFunc equal
	}
}	

textures/clown/red_3
{
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	q3map_surfacelight 30
//	cull none
	polygonoffset	
	{
		map textures/clown/red_3
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen wave sin 1 1.4 2 1.2
		depthFunc equal
	}
}

textures/clown/blue_1
{
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	q3map_surfacelight 30
//	cull none
	polygonoffset	
	{
		map textures/clown/blue_1
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen wave sin 1 1.4 2 1.2
		depthFunc equal
	}
}

textures/clown/blue_2
{
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	q3map_surfacelight 30
//	cull none
	polygonoffset	
	{
		map textures/clown/blue_2
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen wave sin 1 1.4 2 1.2
		depthFunc equal
	}
}	

textures/clown/blue_3
{
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	q3map_surfacelight 30
//	cull none
	polygonoffset
	{
		map textures/clown/blue_3
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen wave sin 1 1.4 2 1.2
		depthFunc equal
	}
}

//note: the brush this is used on should be made a detail brush
//with this texture on one side, the rest of the sides should 
//be a "nodraw or caulk"
textures/clown/glass
{
		
	{
		map textures/clown/glass
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen identity
		depthFunc equal
	}
}

textures/clown/portal_1r
{
	qer_editorimage textures/clown/portal_1r
	surfaceparm noimpact
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nolightmap
	cull disable

	{
		map $lightmap
		blendFunc gl_dst_color gl_one_minus_src_alpha
		rgbGen identity
	}
	{
		map textures/clown/portal_1r
		blendfunc gl_one gl_one
		rgbGen wave inversesawtooth .3 .01 0 .2
	}
	{
		clampmap textures/clown/portal_2r
		blendFunc GL_ONE GL_ONE
		tcMod stretch sin 1.2 .3 0 1.2
	}
	{
		clampmap textures/clown/portal_4r
		blendFunc GL_ONE GL_ONE
		tcMod stretch sin 1.2 .2 0.5 1.2
	}
	{
		clampmap textures/clown/portal_3r
		blendfunc GL_ONE GL_ONE
		tcmod rotate 10
	}
}


textures/clown/dark_sky
{
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm sky
	q3map_lightimage textures/clown/dark_sky
	q3map_sun	.5 .1 .1  50  65  35
	q3map_surfacelight  100
	

	skyparms - 1024 -
	{
	map textures/clown/dark_sky
	tcMod scroll 0.02 0.05
	tcMod scale 2 1
	}
	
	
	
}

textures/clown/r_edge
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	cull none
	
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		depthFunc equal
	}
	{
		map textures/clown/r_edge
		blendFunc GL_ONE GL_ONE
		tcMod turb 3 .3 3 .3
	}
}

textures/clown/b_edge
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	cull none
	
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		depthFunc equal
	}
	{
		map textures/clown/b_edge
		blendFunc GL_ONE GL_ONE
		tcMod turb 3 .3 3 .3
	}
}

textures/clown/ankh_light
{
	qer_editorimage textures/clown/ankh_light.jpg
	surfaceparm nomarks
	q3map_surfacelight 3000
	
	
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/clown/ankh_light.jpg
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
	}
	{
		map textures/clown/ankh_light.jpg
		blendfunc GL_ONE GL_ONE
	}
}

textures/clown/grate_1
{
	surfaceparm nomarks
	cull none
	{
		map textures/clown/grate_1
		blendFunc GL_ONE GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen identity
		depthFunc equal
	}
}

textures/clown/grate_2
{
	
	surfaceparm nomarks
	cull none
	{
		map textures/clown/grate_2
		blendFunc GL_ONE GL_ZERO	
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen identity
		depthFunc equal
	}
}

textures/base_wall/main_q3abanner
{
	nopicmip
	q3map_lightimage textures/base_wall/main_q3abanner.jpg
        q3map_surfacelight 100


	{
		map textures/base_wall/main_q3abanner.jpg
	        rgbGen wave square 0 1 0 .5
	}

	{
		map textures/base_wall/comp3textb.jpg
		blendfunc add
	        rgbGen identity
		tcmod scroll 2 2
		
	}

	{
		map textures/base_wall/comp3text.jpg
		blendfunc add
	        rgbGen identity
		tcmod scroll 3 3
	}


	{
		map $lightmap
	        rgbGen identity
		blendfunc gl_dst_color gl_zero
	}

	{
		map $lightmap
		tcgen environment
		tcmod scale .5 .5
	        rgbGen wave sin .25 0 0 0
		blendfunc add
	}	          		
}   

textures/base_wall/main_q3abanner_r
{
	nopicmip
	q3map_lightimage textures/base_wall/main_q3abanner.jpg
        q3map_surfacelight 100


	{
		map textures/base_wall/main_q3abanner_r.jpg
	        rgbGen wave square 0 1 0 .5
	}

	{
		map textures/base_wall/comp3textb.jpg
		blendfunc add
	        rgbGen identity
		tcmod scroll -2 2
	}

	{
		map textures/base_wall/comp3text.jpg
		blendfunc add
	        rgbGen identity
		tcmod scroll 3 3
	}


	{
		map $lightmap
	        rgbGen identity
		blendfunc gl_dst_color gl_zero
	}

	{
		map $lightmap
		tcgen environment
		tcmod scale .5 .5
	        rgbGen wave sin .25 0 0 0
		blendfunc add
	}	          		
}   

textures/clown/steel_b_shine
{
	qer_editorimage textures/clown/steel_b.jpg
	{
		map textures/clown/steel_b.jpg
		rgbGen identity
	}
	{
		clampmap textures/base_wall/chrome_env.jpg
		blendfunc add
		rgbGen const ( 0.188235 0.188235 0.407843 )
		tcGen environment 
	}
	{
		map textures/clown/steel_b.jpg
		blendfunc filter
		
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/clown/steel_r_shine
{
	qer_editorimage textures/clown/steel_r.jpg
	{
		map textures/clown/steel_r.jpg
		rgbGen identity
	}
	{
		clampmap textures/base_wall/chrome_env.jpg
		blendfunc add
		rgbGen const ( 0.188235 0.188235 0.407843 )
		tcGen environment 
	}
	{
		map textures/clown/steel_r.jpg
		blendfunc filter
		
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/clown/steel_rust_shine
{
	qer_editorimage textures/clown/steel_rust.jpg
	{
		map textures/clown/steel_rust.jpg
		rgbGen identity
	}
	{
		clampmap textures/base_wall/chrome_env.jpg
		blendfunc add
		rgbGen const ( 0.188235 0.188235 0.407843 )
		tcGen environment 
	}
	{
		map textures/clown/steel_r.jpg
		blendfunc filter
		
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/clown/burn_ow
{
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	q3map_surfacelight 30
	cull none	
	
	{
		map textures/clown/burn_ow
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		alphaFunc GT0
		depthWrite
		
	}
	{
		map $lightmap
		blendFunc gl_dst_color gl_one_minus_src_alpha
		rgbGen identity
		depthFunc equal
	}
	
}

textures/gothic_block/mkc_evil_e3window
{
	qer_editorimage textures/gothic_block/windowevil2c_block18c.jpg
	q3map_lightimage textures/gothic_block/evil2cglow.jpg
	q3map_surfacelight 200
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/gothic_block/windowevil2c_block18c.jpg
		blendFunc filter
		rgbGen identity
	}
	{
		map textures/gothic_block/evil2cglow.jpg
		blendfunc add
	}
}

textures/gothic_block/evil_e3bwindow
{
	qer_editorimage textures/gothic_block/windowevil2c_killblock.jpg
	q3map_lightimage textures/gothic_block/evil2ckillblockglow.jpg
	q3map_surfacelight 200
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/gothic_block/windowevil2c_killblock.jpg
		blendFunc filter
		rgbGen identity
	}
	{
		map textures/gothic_block/evil2ckillblockglow.jpg
		blendfunc add
	}
}

textures/gothic_block/evil_e3window
{
	qer_editorimage textures/gothic_block/windowevil2c_block18c.jpg
	q3map_lightimage textures/gothic_block/evil2cglow.jpg
	q3map_surfacelight 900
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/gothic_block/windowevil2c_block18c.jpg
		blendFunc filter
		rgbGen identity
	}
	{
		map textures/gothic_block/evil2cglow.jpg
		blendfunc add
	}
}

textures/gothic_block/evil_e3window_dark
{
	qer_editorimage textures/gothic_block/windowevil2c_block18c.jpg
	q3map_lightimage textures/gothic_block/evil2cglow.jpg
	q3map_surfacelight 100
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/gothic_block/windowevil2c_block18c.jpg
		blendFunc filter
		rgbGen identity
	}
	{
		map textures/gothic_block/evil2cglow.jpg
		blendfunc add
	}
}

textures/gothic_block/wetwall
{
	
        {
	        map textures/gothic_block/wetwall
	        rgbGen identity
	}
        {
		map textures/gothic_block/wetwall_fx
                tcmod scroll 0 -.1
		tcmod scale .9 .1
                blendFunc add
	}
	{
	        map textures/gothic_block/wetwall
		blendFunc blend
		rgbGen identity
	}
        {
		map $lightmap
                blendFunc GL_DST_COLOR GL_ONE_MINUS_SRC_ALPHA
		rgbGen identity
	}
}

textures/ctf/blue_telep2
{
	qer_editorimage textures/effects/jumpcircblue
	q3map_lightimage textures/effects/jumpcircblue
	surfaceparm nonsolid
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm trans
	cull disable
	q3map_surfacelight 455
	{
		clampmap textures/effects/jumpcircblue
		blendfunc add
		tcMod rotate 46
	}
	{
		clampmap textures/sfx/jcb2
		blendfunc add
		tcMod rotate -80
		tcMod stretch sin 0.9 -0.3 0 0.5 
	}
	{
		clampmap textures/sfx/jcb2
		blendfunc add
		tcMod rotate -80
		tcMod stretch sin 0.5 0.3 0 0.5 
	}
}

textures/ctf/red_telep2
{
	qer_editorimage textures/effects/jumpcircred
	q3map_lightimage textures/effects/jumpcircred
	surfaceparm nonsolid
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm trans
	cull disable
	q3map_surfacelight 455
	{
		clampmap textures/effects/jumpcircred
		blendfunc add
		tcMod rotate 46
	}
	{
		clampmap textures/sfx/jcr2
		blendfunc add
		tcMod rotate -80
		tcMod stretch sin 0.9 -0.3 0 0.5 
	}
	{
		clampmap textures/sfx/jcr2
		blendfunc add
		tcMod rotate -80
		tcMod stretch sin 0.5 0.3 0 0.5 
	}
}

textures/gothic_block/blocks18b_ow
{
	qer_editorimage textures/gothic_block/blocks18b_ow
	surfaceparm nomarks
	
	{
		map textures/sfx/fireswirl2.jpg
		tcmod rotate 1
		tcmod turb 1 .4 0 .5
		blendfunc add
	}
	{
		map textures/gothic_block/blocks18b_ow
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/base_floor/proto_rustygrate
{
	surfaceparm metalsteps
	surfaceparm nodamage
	cull none
	{
		map textures/base_floor/proto_rustygrate
		blendFunc gl_one gl_zero	
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_floor/proto_grate
{
	surfaceparm metalsteps
	surfaceparm nodamage
	cull none
	{
		map textures/base_floor/proto_grate
		blendFunc gl_one gl_zero	
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_floor/proto_grate4
{
	surfaceparm metalsteps
	surfaceparm nodamage
	cull none
	{
		map textures/base_floor/proto_grate4
		blendFunc gl_one gl_zero	
		rgbGen identity
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_floor/cybergrate2
{
	surfaceparm metalsteps
	cull none
	{
		map textures/sfx/portal_sfx_ring_electric
		tcmod scroll 1 -1
		blendfunc add
	}
	{
		map textures/base_floor/cybergrate2
		blendFunc blend	
		rgbGen identity
		
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_floor/cybergrate3
{
	surfaceparm metalsteps
	cull none
	{
		map textures/sfx/portal_sfx_ring_electric
		tcmod scroll 1 -1
		blendfunc add
	}
	{
		map textures/base_floor/cybergrate3
		blendFunc blend	
		rgbGen identity
		
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_trim/dark_tin2
{
	qer_editorimage textures/base_trim/dark_tin2.jpg
	{
		//mapped first so it looks good while vertex lit
		map textures/base_trim/dark_tin2.jpg
		rgbGen Identity
	}
	{
		map textures/base_wall/chrome_metal.jpg
		tcGen environment 
		rgbGen oneminusvertex
	}
	{
		map textures/base_trim/dark_tin2.jpg
		blendfunc add
	}
	
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/base_trim/pewter_shiney
{
	qer_editorimage textures/base_trim/pewter_shiney.jpg
	{
		//mapped first so it looks good while vertex lit
		map textures/base_trim/pewter_shiney.jpg
		rgbGen Identity
	}
	{
		map textures/base_wall/chrome_env2.jpg
		tcGen environment 
		rgbGen vertex
	}
	{
		map textures/base_trim/pewter_shiney.jpg
		blendfunc add
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/base_trim/tin
{
	qer_editorimage textures/base_trim/tin
	{
		//mapped first so it looks good while vertex lit
		map textures/base_trim/tin
		rgbGen Identity
	}
	{
		map textures/base_trim/tinfx.jpg
		tcGen environment 
		rgbGen vertex
	}
	{
		map textures/base_trim/tin
		blendfunc add
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/base_floor/hfloor3
{
	qer_editorimage textures/base_floor/hfloor3.jpg
	{
		//mapped first so it looks good while vertex lit
		map textures/base_floor/hfloor3.jpg
		rgbGen Identity
	}
	{
		map textures/base_trim/tinfx.jpg
		tcGen environment 
		rgbGen oneminusvertex
	}
	{
		map textures/base_floor/hfloor3.jpg
		blendfunc add
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/base_wall/comp3b_dark
{
	qer_editorimage textures/base_wall/comp3b_dark.jpg
	q3map_lightimage textures/base_wall/comp3env.jpg
        q3map_surfacelight 10


	{
		map textures/base_wall/comp3textb
	        rgbGen identity
		tcmod scroll -3 3
	}
	{
		map textures/base_wall/comp3text.jpg
		blendfunc add
	        rgbGen identity
		tcmod scroll -3 3
	}
	{
		map textures/base_wall/comp3env.jpg
		tcGen environment
	        blendfunc add
		rgbGen oneminusvertex
	}


	{
		map $lightmap
	        tcGen environment
		blendfunc gl_dst_color gl_one
	}
	{
		map textures/base_wall/comp3b
        	blendFunc blend 
		rgbGen identity
		
	}
	{
		map $lightmap
                blendFunc GL_DST_COLOR GL_ONE_MINUS_SRC_ALPHA
		rgbGen identity
	}

}   

textures/base_wall/comp3b
{
	qer_editorimage textures/base_wall/comp3b
	q3map_lightimage textures/base_wall/comp3env.jpg
        q3map_surfacelight 900

	{
		map textures/base_wall/comp3b
		rgbGen identity
		
	}
	{
		map textures/base_wall/comp3env.jpg
		tcGen environment
		rgbGen identity
	}
	{
		map textures/base_wall/comp3text.jpg
		blendfunc add
	        rgbGen identity
		tcmod scroll 3 3
	}
	{
		map $lightmap
	        tcGen environment
		blendfunc gl_dst_color gl_one
	}
	{
		map textures/base_wall/comp3b
        	blendFunc blend
		rgbGen identity
		
	}
	{
		map $lightmap
                blendFunc GL_DST_COLOR GL_ONE_MINUS_SRC_ALPHA
		rgbGen identity
	}

}  

textures/base_support/x_support
{
	surfaceparm metalsteps
	surfaceparm nomarks
	cull none
	{
		map textures/base_support/x_support
		blendFunc gl_one gl_zero	
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_support/x_support2
{
	surfaceparm metalsteps
	surfaceparm nomarks
	cull none
	{
		map textures/base_support/x_support2
		blendFunc gl_one gl_zero	
		rgbGen identity
		alphaFunc GT0
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_wall/bluemetal1b_chrome
{
	qer_editorimage textures/base_wall/bluemetal1b_shiny
	{
		//mapped first so it looks good while vertex lit
		map textures/base_wall/bluemetal1b_shiny
		rgbGen Identity
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
	}
	{
		map textures/base_wall/bluemetal1b_shiny
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
}

textures/base_wall/bluemetalsupport2fline
{
	qer_editorimage textures/base_wall/bluemetalsupport2fline
	q3map_lightimage textures/clown/bms2fglow
	surfaceparm nomarks
	surfaceparm metalsteps
	q3map_surfacelight 400
	{
		//mapped first so it looks good while vertex lit
		map textures/base_wall/bluemetalsupport2fline
		rgbGen Identity
	}
	{
		map textures/base_wall/bms2fglow
		rgbGen wave sin .4 .3 .5 1.5
		blendfunc filter
	}
	{
		map textures/base_wall/bluemetalsupport2fline
		blendfunc add
		alphaGen lightingSpecular
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
		tcmod scale .5 .5
		blendfunc add
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/tim/redmetalsupport2fline
{
	qer_editorimage textures/tim/redmetalsupport2fline
	q3map_lightimage textures/clown/bms2fl_rglow
	surfaceparm nomarks
	surfaceparm metalsteps
	q3map_surfacelight 400
	{
		//mapped first so it looks good while vertex lit
		map textures/tim/redmetalsupport2fline
		rgbGen Identity
	}
	
	{
		map textures/clown/bms2fl_rglow
		tcmod scroll 1 0
		rgbGen wave sin .4 .3 .5 2
		blendfunc gl_dst_color gl_zero 
	}
	{
		map textures/tim/redmetalsupport2fline
		blendfunc add
		
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
		tcmod scale .5 .5
		blendfunc add
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/base_wall/bluemetalsupport2ftv
{
	qer_editorimage textures/base_wall/bluemetalsupport2ftv
	q3map_lightimage textures/base_wall/bms2ftv_glow
	q3map_surfacelight 10
	
	{
		map textures/base_wall/bluemetalsupport2ftv
		rgbGen identity
		
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
		tcmod scale .5 .5
	}
	{
		map textures/base_wall/bms2ftv_glow
		rgbGen wave sin .4 .3 0 1.1
		blendfunc add
	}
	{
		map textures/base_wall/bluemetalsupport2ftv
		blendFunc add
		rgbGen identity
		
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_wall/bluemetalsupport2e
{
	qer_editorimage textures/base_wall/bluemetalsupport2e
		
	{
		map textures/base_wall/bluemetalsupport2e
		rgbGen identity
		
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
		tcmod scale .5 .5
	}
	{
		map textures/base_wall/bluemetalsupport2e
		blendFunc add
		rgbGen identity
		
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_wall/bluemetalsupport2e2
{
	qer_editorimage textures/base_wall/bluemetalsupport2e2
		
	{
		map textures/base_wall/bluemetalsupport2e2
		rgbGen identity
		
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
		tcmod scale .5 .5
	}
	{
		map textures/base_wall/bluemetalsupport2e2
		blendFunc add
		rgbGen identity
		
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_wall/bluemetalsupport2c_1
{
	qer_editorimage textures/base_wall/bluemetalsupport2c_1.jpg
		
	{
		map textures/base_wall/bluemetalsupport2c_1.jpg
		rgbGen identity
		
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
		tcmod scale .5 .5
	}
	{
		map textures/base_wall/bluemetalsupport2c_1.jpg
		blendFunc add
		rgbGen identity
		
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_wall/bluemetalsupport2c
{
	qer_editorimage textures/base_wall/bluemetalsupport2c.jpg
		
	{
		map textures/base_wall/bluemetalsupport2c.jpg
		rgbGen identity
		
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
		tcmod scale .5 .5
	}
	{
		map textures/base_wall/bluemetalsupport2c.jpg
		blendFunc add
		rgbGen identity
		
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_floor/clangdark_spot
{
	qer_editorimage textures/base_floor/clangdark_spot
	surfaceparm metalsteps
	
	{
		map textures/base_floor/clangdark_spot
		rgbGen identity
	}
	{
		map textures/liquids/proto_gruel2.jpg
		blendfunc gl_one gl_zero
		tcmod scroll .01 .01
		tcmod turb 0 0.01 0 .1
		alphagen lightingspecular
	}
	{
		map textures/base_floor/clangdark_spot
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_floor/diamond2cspot
{
	qer_editorimage textures/base_floor/diamond2cspot
	surfaceparm metalsteps
	
	{
		map textures/base_floor/diamond2cspot
		rgbGen identity
	}
	{
		map textures/liquids/proto_gruel3.jpg
		blendfunc gl_one gl_zero
		tcmod scroll .01 .01
		tcmod turb 0 0.01 0 .1
		alphagen lightingspecular
	}
	{
		map textures/base_floor/diamond2cspot
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/gothic_floor/q1metal7_99spot
{
	qer_editorimage textures/gothic_floor/q1metal7_99spot
	surfaceparm metalsteps
	
	{
		map textures/gothic_floor/q1metal7_99spot
		rgbGen identity
	}
	{
		map textures/liquids/proto_gruel3.jpg
		blendfunc gl_one gl_zero
		tcmod scroll .01 .01
		tcmod turb 0 0.01 0 .1
		alphagen lightingspecular
	}
	{
		map textures/gothic_floor/q1metal7_99spot
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendFunc filter 
		rgbGen identity
	}
}

textures/base_wall/patch10shiny
{
	qer_editorimage textures/base_wall/patch10.jpg
		
	{
		map textures/base_wall/patch10.jpg
		rgbGen identity
		
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
		tcmod scale .5 .5
	}
	{
		map textures/base_wall/patch10.jpg
		blendFunc add
		rgbGen identity
		
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_wall/comp3
{
	qer_editorimage textures/base_wall/comp3.jpg
	q3map_lightimage textures/base_wall/comp3env.jpg
        q3map_surfacelight 100

	{
		map textures/base_wall/comp3b
		rgbGen identity
		
	}
	{
		map textures/clown/text3
	        rgbGen identity
		tcmod scroll 0 0.5
	}

	{
		map textures/clown/text4
		blendfunc add
	        rgbGen identity 
		tcMod scroll 0 0.5 
	}
	{
		map textures/base_wall/comp3env.jpg
		tcGen environment
	        blendfunc add
		rgbGen oneminusvertex
	}

	{
		map $lightmap
	        tcGen environment
		blendfunc gl_dst_color gl_one
	}
	{
		map textures/base_wall/comp3b
        	blendFunc blend
		rgbGen identity
		
	}
	{
		map $lightmap
                blendFunc GL_DST_COLOR GL_ONE_MINUS_SRC_ALPHA
		rgbGen identity
	}

}   

textures/base_wall/concrete_ow
{
	qer_editorimage textures/base_wall/concrete_ow

	{
		map textures/sfx/proto_zzztblu3.jpg
		tcmod scale 1.5 1.5
		tcmod rotate 1
		tcmod turb 8 4 0 5
		rgbgen identity
	}
	{
		map textures/base_wall/concrete_ow
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
		rgbgen identity
	}
	{
		map gfx/fx/detail/d_conc
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		depthfunc equal
	}
}

textures/tim/rconcrete_ow
{
	qer_editorimage textures/tim/rconcrete_ow

	{
		map textures/sfx/fireswirl2.jpg
		tcmod scale 1.5 1.5
		tcmod rotate 1
		tcmod turb 8 4 0 5
		rgbgen identity
	}
	{
		map textures/tim/rconcrete_ow
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
		rgbgen identity
	}
	{
		map gfx/fx/detail/d_conc
		blendfunc gl_dst_color gl_src_color
		tcMod scale 8 8
		depthfunc equal
	}
}

textures/gothic_block/blocks17bloody
{
	qer_editorimage textures/gothic_block/blocks17bloody
	{
		map textures/gothic_block/blocks17bloody
	}
	{
		map textures/liquids/proto_gruel3.jpg
		tcmod scroll .01 .01
		tcmod turb 0 0.01 0 .1
		alphagen lightingspecular
	}
	{
		map textures/gothic_block/blocks17bloody
		blendFunc blend
		rgbGen identity
	}
	{
		map $lightmap
		blendFunc filter 
		rgbGen identity
	}
}

textures/gothic_block/largerblock3blood
{
	qer_editorimage textures/gothic_block/largerblock3blood
	{
		map textures/gothic_block/largerblock3blood
	}
	{
		map textures/liquids/proto_gruel3.jpg
		tcmod scroll .01 .01
		tcmod turb 0 0.01 0 .1
		alphagen lightingspecular
	}
	{
		map textures/gothic_block/largerblock3blood
		blendFunc blend
		rgbGen identity
	}
	{
		map $lightmap
		blendFunc filter 
		rgbGen identity
	}
}

textures/gothic_floor/metalbridge06brokeb
{
	qer_editorimage textures/gothic_floor/metalbridge06brokeb
	{
		map textures/gothic_floor/metalbridge06brokeb
		rgbgen identity
	}
	{
		map textures/sfx/proto_zzztblu3.jpg
		tcmod scale 1.5 1.5
		tcmod rotate 1
		tcmod turb 8 4 0 5
		rgbgen identity
	}
	{
		map textures/gothic_floor/metalbridge06brokeb
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
		rgbgen identity
	}
}

textures/base_wall/chrome_metal
{
	qer_editorimage textures/base_wall/chrome_metal
	{
		map textures/base_wall/chrome_metal
		rgbgen identity
	}
	{
		map textures/base_wall/chrome_env
		tcGen environment
		tcmod scale .5 .5 
		rgbgen vertex
		
	}
	{
		map textures/base_wall/chrome_metal
		blendFunc add
		tcmod scale 0.07 0.06
		rgbGen identity
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/gothic_floor/largerblock3b_ow
{
	qer_editorimage textures/gothic_floor/largerblock3b_ow
	{
		map textures/gothic_floor/largerblock3b_ow
		rgbgen identity
	}
	{
		map textures/sfx/fireswirl2.jpg
		tcmod scale 1.5 1.5
		tcmod rotate 1
		tcmod turb 8 4 0 5
		rgbgen identity
	}
	{
		map textures/gothic_floor/largerblock3b_ow
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
		rgbgen identity
	}
}

textures/base_trim/proto_fence
{
	qer_editorimage textures/base_trim/proto_fence
	surfaceparm trans
	cull none
	{
		map textures/base_trim/proto_fence
		alphafunc GE128
		depthwrite
		tcmod scale 2 2
		rgbgen identity
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
		depthfunc equal
	}
}

textures/skin/skin6move
{
	qer_editorimage textures/skin/skin6move.jpg
	surfaceparm flesh
	tesssize 64
	deformVertexes wave 80 sin 3 2 .5 .9
	{
		map $lightmap
		rgbgen identity
	}
	
	{
		map textures/skin/skin6move.jpg
		blendfunc filter
		rgbgen identity
	}
	
}

textures/skin/chapthroatooz
{
	qer_editorimage textures/skin/chapthroatooz.jpg
	
	{
		map textures/liquids/proto_gruel2.jpg
		
		tcmod scale .5 .5
		tcmod scroll .01 .1
		rgbgen identity
	}
	{
		map textures/skin/chapthroatooz.jpg
		blendfunc add
		rgbgen identity
	}
	
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/clown/fence
{
	qer_editorimage textures/clown/fence
	surfaceparm nonsolid
	surfaceparm trans
	cull none
	{
		map textures/clown/fence
		alphafunc GE128
		depthwrite
		rgbgen identity
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
		depthfunc equal
	}
}

textures/clown/fence_shadow
{
	qer_editorimage textures/clown/fence_shadow
	polygonoffset
	surfaceparm nolightmap
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm trans
	cull none
	{
		map textures/clown/fence_shadow
		alphafunc GE128
		depthwrite
		rgbgen identity
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
		depthfunc equal
	}
}

textures/gothic_trim/metlsupport4i_shiney
{
	qer_editorimage textures/gothic_trim/metalsupport4i
	{
		map textures/gothic_trim/metalsupport4i
		rgbgen identity
	}
	{
		map textures/base_wall/chrome_env
		tcGen environment
		tcmod scale .5 .5 
		rgbgen vertex
		
	}
	{
		map textures/gothic_trim/metalsupport4i
		blendFunc add
		rgbGen identity
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/base_wall/shinybluemetal1
{
	qer_editorimage textures/base_wall/shinybluemetal1.jpg
	{
		//mapped first so it looks good while vertex lit
		map textures/base_wall/shinybluemetal1.jpg
		rgbGen Identity
	}
	{
		map textures/base_wall/chrome_env.jpg
		tcGen environment 
		rgbGen oneminusvertex
	}
	{
		map textures/base_wall/shinybluemetal1.jpg
		blendfunc add
	}
	{
		map $lightmap 
		blendfunc gl_dst_color gl_one_minus_src_alpha
		tcGen lightmap 
	}
}

textures/base_wall/metalfloor_wall_14
{
	qer_editorimage textures/base_wall/metalfloor_wall_14.jpg
	{
		map textures/base_wall/metalfloor_wall_14.jpg
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen vertex
	}
	{
		map textures/base_wall/metalfloor_wall_14.jpg
		blendfunc add
		rgbgen identity
	}
	{
		map textures/base_wall/metalfloor_wall_14_glow
		blendfunc blend
		rgbGen wave sin 0 1 0 1
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

