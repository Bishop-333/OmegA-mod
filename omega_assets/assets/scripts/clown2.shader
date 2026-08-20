textures/base_trim/wires01
{
	qer_editorimage textures/base_trim/wires01
	cull none
	surfaceparm alphashadow
	surfaceparm trans
	{
		map textures/base_trim/wires01
		alphafunc GE128
		depthwrite
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
		depthfunc equal
	}
}

textures/base_trim/wires01_ass
{
	qer_editorimage textures/base_trim/wires01_ass
	cull none
	surfaceparm alphashadow
	surfaceparm trans
	{
		map textures/base_trim/wires01_ass
		alphafunc GE128
		depthwrite
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
		depthfunc equal
	}
}

textures/base_trim/wires02
{
	qer_editorimage textures/base_trim/wires02
	cull none
	surfaceparm alphashadow
	surfaceparm trans
	{
		map textures/base_trim/wires02
		alphafunc GE128
		depthwrite
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
		depthfunc equal
	}
}

textures/base_floor/tilefloor7_ow
{
	qer_editorimage textures/base_floor/tilefloor7_ow.jpg
	q3map_lightimage textures/base_floor/tilefloor7_owfx.jpg
	q3map_surfacelight 50
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/base_floor/tilefloor7_ow.jpg
		blendfunc filter
		rgbgen identity
	}
	{
		map textures/base_floor/tilefloor7_owfx.jpg
		blendfunc add
		rgbgen wave sin 2 1 .5 6
	}
	
}

textures/proto2/cheapfloor
{
	qer_editorimage textures/proto2/marble02b_floor
	{
		map textures/proto2/marble02b_floor
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen vertex
	}
	{
		map textures/proto2/marble02b_floor
		blendfunc add
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/proto2/mirrorfloor
{
	qer_editorimage textures/proto2/marble02b_floor
	portal
	{
		map textures/common/invisible
		blendfunc gl_one gl_one_minus_src_alpha
		depthwrite
	}
	{
		map textures/proto2/marble02b_floor
		blendfunc add
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/proto2/marble02b_s
{
	qer_editorimage textures/proto2/marble02b_s
	surfaceparm metalsteps
	{
		map textures/proto2/marble02b_s
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen vertex
	}
	{
		map textures/proto2/marble02b_s
		blendfunc add
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/proto2/marble02b_s_green
{
	qer_editorimage textures/proto2/marble02b_s
	surfaceparm metalsteps
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/proto2/marble02b_s
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/gothic_button/timbutton
{
	q3map_surfacelight textures/gothic_button/timbutton
	q3map_lightimage textures/gothic_button/timbutton2.jpg
	q3map_surfacelight 20
	
	{
		map textures/gothic_button/timbutton
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen vertex
	}
	{
		map textures/gothic_button/timbutton2.jpg
		blendfunc add
		rgbGen wave sin 1 1 0 0.5
	}
	{
		map textures/gothic_button/timbutton
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/proto2/steam01
{
	qer_editorimage textures/proto2/steam01
	cull none
	surfaceparm trans
	deformvertexes autosprite2
	deformvertexes wave 30 sin 0.1 2 .5 .5
	{
		map textures/proto2/steam01
		tcmod scroll 0 0.4
		blendfunc blend
		rgbgen identity
	}
}

textures/gothic_trim/zinc_shiny
{
	qer_editorimage textures/gothic_trim/zinc_shiny
	{	
		map textures/gothic_trim/zinc_shiny
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen identity
	}
	{
		map textures/gothic_trim/zinc_shiny
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/base_floor/skylight_spec
{
	qer_editorimage textures/base_floor/skylight_spec
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/base_floor/skylight_spec
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/gothic_trim/metalsupport4h_shiny
{
	qer_editorimage textures/gothic_trim/metalsupport4h_shiny
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/gothic_trim/metalsupport4h_shiny
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/gothic_trim/metalsupport4h_trans
{
	qer_editorimage textures/gothic_trim/metalsupport4h_shiny
	surfaceparm nonsolid
	{
		map textures/gothic_trim/metalsupport4h_shiny
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen identity
	}
	{
		map textures/gothic_trim/metalsupport4h_shiny
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/base_wall/bluemetal2_shiny
{
	qer_editorimage textures/base_wall/bluemetal2_shiny
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/base_wall/bluemetal2_shiny
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/base_wall/bluemetal1b_shiny
{
	qer_editorimage textures/base_wall/bluemetal1b_shiny
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/base_wall/bluemetal1b_shiny
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/base_wall/bluemetal2_noisy
{
	qer_editorimage textures/base_wall/bluemetal2_shiny
	surfaceparm metalsteps
	{
		map textures/base_wall/bluemetal2_shiny
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen identity
	}
	{
		map textures/base_wall/bluemetal2_shiny
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/base_wall/bluemetal2_shiny_trans
{
	qer_editorimage textures/base_wall/bluemetal2_shiny
	{
		map textures/base_wall/bluemetal2_shiny
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen identity
	}
	{
		map textures/base_wall/bluemetal2_shiny
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/gothic_trim/gothgrate2
{
	surfaceparm metalsteps
	cull none
	{
		map textures/gothic_trim/gothgrate2
		blendfunc blend
		rgbgen identity
		alphafunc GE128
		depthwrite
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
		depthfunc equal
	}
}

textures/base_wall/metalfloor_wall_14_specular
{
	qer_editorimage textures/base_wall/metalfloor_wall_14_specular
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/base_wall/metalfloor_wall_14_specular
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/clown/metalfloor_wall_14sr
{
	qer_editorimage textures/clown/metalfloor_wall_14sr

	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/clown/metalfloor_wall_14sr
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/base_wall/metalfloor_wall_15ow
{
	qer_editorimage textures/base_wall/metalfloor_wall_15ow
	{
		map textures/base_wall/metalfloor_wall_15ow
		rgbgen identity
	}
	{
		map textures/sfx/zap_scroll2.jpg
		tcmod scale 2 .1
		tcmod scroll -.4 1
		blendfunc add
		rgbgen identity
	}
	{
		map textures/sfx/zap_scroll.jpg
		tcmod scale 2 .1
		tcmod scroll .4 -1
		blendfunc add
		rgbgen identity
	}
	{
		map textures/base_wall/metalfloor_wall_15ow
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
	}
}

textures/base_wall/metalfloor_wall_10
{
	qer_editorimage textures/base_wall/metalfloor_wall_10.jpg
	{
		map textures/base_wall/metalfloor_wall_10.jpg
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen vertex
	}
	{
		map textures/base_wall/metalfloor_wall_10.jpg
		blendfunc add
		rgbgen identity
	}
	{
		map textures/base_wall/metalfloor_wall_10_glow
		blendfunc blend
		rgbGen wave sin 0 1 0 1
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/clown/cheapfloor2
{
	qer_editorimage textures/clown/stone_tile.jpg
	{
		map textures/clown/stone_tile.jpg
		rgbgen identity
	}
	{
		map textures/effects/tinfx
		tcgen environment
		rgbgen vertex
	}
	{
		map textures/clown/stone_tile.jpg
		blendfunc add
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/proto2/c_zinc_shiny
{
	qer_editorimage textures/gothic_trim/zinc_shiny
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/gothic_trim/zinc_shiny
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/proto2/vertex_greenstone
{
	qer_editorimage textures/gothic_block/blocks17i.jpg
	surfaceparm pointlight
	{
		map textures/gothic_block/blocks17i.jpg
		rgbgen oneminusvertex
	}
}

textures/proto2/vertex_cavestone
{
	qer_editorimage textures/organics/pjrock7d.jpg
	surfaceparm pointlight
	{
		map textures/organics/pjrock7d.jpg
		rgbgen oneminusvertex
	}
}

textures/sfx2/redgoal2
{
	surfaceparm nolightmap
	surfaceparm trans
	cull none
	{
		map textures/sfx2/redgoal2
		tcgen environment
		blendfunc add
		tcmod turb .1 .3 .5 .4
		tcmod scale .5 .5
	}
}

textures/sfx2/bluegoal2
{
	surfaceparm nolightmap
	surfaceparm trans
	cull none
	{
		map textures/sfx2/bluegoal2
		tcgen environment
		blendfunc add
		tcmod turb .1 .3 .5 .4
		tcmod scale .5 .5
	}
}

textures/base_wall2/respawn_effect1
{
	qer_editorimage textures/base_wall2/redjet_1
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	cull none
	{
		map textures/base_wall2/redjet_1
		blendfunc add
		tcmod scroll .4 0
		tcmod scale 1 -1
		rgbGen wave sin 0 1 0 .5
	}
	{
		map textures/base_wall2/redjet_2
		blendfunc add
		tcmod scroll -.4 0
		tcmod scale 1 -1
		rgbGen wave sin 1 0 0 1.5
	}
	{
		map textures/base_wall2/redjet_3
		blendfunc add
		tcmod scale 1 -1
	}
}

textures/base_wall2/respawn_effect1_blue
{
	qer_editorimage textures/base_wall2/bluejet_1
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	cull none
	{
		map textures/base_wall2/bluejet_1
		blendfunc add
		tcmod scroll .4 0
		tcmod scale 1 -1
		rgbGen wave sin 0 1 0 .5
	}
	{
		map textures/base_wall2/bluejet_2
		blendfunc add
		tcmod scroll -.4 0
		tcmod scale 1 -1
		rgbGen wave sin 1 0 0 1.5
	}
	{
		map textures/base_wall2/bluejet_3
		blendfunc add
		tcmod scale 1 -1
	}
}

textures/base_wall2/respawn_effect1_ntrl
{
	qer_editorimage textures/base_wall2/ntrljet_1
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	cull none
	{
		map textures/base_wall2/ntrljet_1
		blendfunc add
		tcmod scroll .4 0
		tcmod scale 1 -1
		rgbGen wave sin 0 1 0 .5
	}
	{
		map textures/base_wall2/ntrljet_2
		blendfunc add
		tcmod scroll -.4 0
		tcmod scale 1 -1
		rgbGen wave sin 1 0 0 1.5
	}
	{
		map textures/base_wall2/ntrljet_3
		blendfunc add
		tcmod scale 1 -1
		
	}
}

textures/base_floor/proto_rustygrate2
{
	surfaceparm metalsteps
	surfaceparm nodamage
	cull none
	{
		map textures/base_floor/proto_rustygrate2
		blendFunc gl_one gl_zero	
		rgbGen identity
		alphaFunc GE128
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_floor/rusty_pentagrate
{
	surfaceparm metalsteps
	surfaceparm nodamage
	cull none
	{
		map textures/base_floor/rusty_pentagrate
		blendFunc gl_one gl_zero	
		rgbGen identity
		alphaFunc GE128
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_floor/pjgrate1
{
	surfaceparm metalsteps
	surfaceparm nodamage
	cull none
	{
		map textures/base_floor/pjgrate1
		blendFunc gl_one gl_zero	
		rgbGen identity
		alphaFunc GE128
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_floor/pjgrate2
{
	surfaceparm metalsteps
	surfaceparm nodamage
	cull none
	{
		map textures/base_floor/pjgrate2
		blendFunc gl_one gl_zero	
		rgbGen identity
		alphaFunc GE128
		depthWrite
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		depthFunc equal
	}
}

textures/base_floor/clangspot2
{
	surfaceparm metalsteps
	{
		map textures/base_floor/clangspot2
		rgbgen identity
	}
	{
		map textures/liquids/proto_gruel3
		blendfunc gl_one gl_zero
		tcmod scroll .01 .01
		tcmod turb 0 0.01 0 .1
	}
	{
		map textures/effects/tinfx
		blendfunc add
		tcgen environment
	}
	{
		map textures/base_floor/clangspot2
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendFunc filter
		rgbGen identity
	}
}

textures/proto2/tin_panel
{
	surfaceparm metalsteps
	{
		map textures/effects/tinfx
		blendfunc filter
		tcgen environment
		rgbgen identity
	}
	{
		map textures/proto2/tin_panel
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc gl_dst_color gl_zero
		rgbgen identity
	}
}

textures/proto2/concrete_blue
{
	surfaceparm metalsteps
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/proto2/concrete_blue
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
	{
		map $lightmap
		blendfunc gl_dst_color gl_zero
		rgbgen identity
	}
}

textures/proto2/concrete_red
{
	surfaceparm metalsteps
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/proto2/concrete_red
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}

}

textures/proto2/concrete_bluenfx
{
	qer_editorimage textures/proto2/concrete_blue
	surfaceparm metalsteps
	{
		map textures/proto2/concrete_blue
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
	}
}

textures/proto2/concrete_rednfx
{
	qer_editorimage textures/proto2/concrete_red
	surfaceparm metalsteps
	{
		map textures/proto2/concrete_red
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
	}
}

textures/proto2/concrete01wetwall
{
	{
		map textures/liquids/proto_gruel3
		tcmod scale 5 5
		tcmod scroll 0 -0.2
		rgbgen identity
	}
	{
		map textures/proto2/concrete01wetwall
		blendfunc blend
		rgbgen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbgen identity
	}
}

textures/base_wall/patch10beatup_spec
{
	qer_editorimage textures/base_wall/patch10_beatup4_alpha
	surfaceparm metalsteps
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/base_wall/patch10_beatup4_alpha
		blendfunc gl_dst_color gl_src_alpha
		rgbgen identitylighting
		alphagen lightingspecular
	}
}

textures/base_wall/patch10shiny_trans
{
	qer_editorimage textures/base_wall/patch10.jpg
	surfaceparm nonsolid
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

textures/base_wall2/space_concrete
{
	qer_editorimage textures/base_wall2/space_panel_alt
	{
		map textures/base_wall/concrete1
		rgbgen identity
	}
	{
		map textures/base_wall2/space_panel_alt
		blendfunc filter
		tcmod scale .1 .1
	}
	{
		map textures/base_wall2/space_panel_alt2
		blendfunc filter
		tcmod scale .03 .03
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
	}
}

textures/base_wall2/scuffs1
{
	surfaceparm trans
	surfaceparm nomarks
	surfaceparm nolightmap
	polygonoffset
	{
		map textures/base_wall2/scuffs1
		blendfunc filter
		rgbgen identity
	}
}

textures/proto2/blue_zot
{
	qer_editorimage textures/proto2/blue_zot
	deformvertexes autosprite2
	deformvertexes move 0.23 0.2 0.3 sin 0 5 0 1
	deformvertexes move 0.3 0 0.3 sin 0 5 0 10
	surfaceparm nomarks
	surfaceparm nonsolid
	surfaceparm trans
	surfaceparm nolightmap
	cull none
	{
		map textures/proto2/blue_zot
		blendfunc add
		rgbgen identity
	}
}

textures/proto2/red_zot
{
	qer_editorimage textures/proto2/red_zot
	deformvertexes autosprite2
	deformvertexes move 0.23 0.2 0.3 sin 0 5 0 1
	deformvertexes move 0.3 0 0.3 sin 0 5 0 10
	surfaceparm nomarks
	surfaceparm nonsolid
	surfaceparm trans
	surfaceparm nolightmap
	cull none
	{
		map textures/proto2/red_zot
		blendfunc add
		rgbgen identity
	}
}

textures/proto2/blue_zot2
{
	qer_editorimage textures/proto2/blue_zot2
	q3map_lightimage textures/proto2/blue_zot2
	q3map_surfacelight 100
	deformvertexes autosprite2
	deformvertexes move 0.23 0.2 0.3 sin 0 5 0 1
	deformvertexes move 0.3 0 0.3 sin 0 5 0 10
	surfaceparm nomarks
	surfaceparm nonsolid
	surfaceparm trans
	surfaceparm nolightmap
	cull none
	{
		map textures/proto2/blue_zot2
		blendfunc add
		rgbgen identity
	}
}

textures/proto2/red_zot2
{
	qer_editorimage textures/proto2/red_zot2
	q3map_lightimage textures/proto2/red_zot2
	q3map_surfacelight 100
	deformvertexes autosprite2
	deformvertexes move 0.23 0.2 0.3 sin 0 5 0 1
	deformvertexes move 0.3 0 0.3 sin 0 5 0 10
	surfaceparm nomarks
	surfaceparm nonsolid
	surfaceparm trans
	surfaceparm nolightmap
	cull none
	{
		map textures/proto2/red_zot2
		blendfunc add
		rgbgen identity
	}
}

textures/proto2/blueflare
{
	deformvertexes autosprite
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	cull none
	{
		clampmap textures/proto2/blueflare
		tcmod rotate 25
		blendfunc add
		rgbgen identity
	}
}

textures/proto2/blueflare2
{
	deformvertexes autosprite2
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	cull none
	{
		map textures/proto2/blueflare2
		blendfunc add
		rgbgen identity
	}
}

textures/proto2/redflare
{
	deformvertexes autosprite
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	cull none
	{
		clampmap textures/proto2/redflare
		tcmod rotate 25
		blendfunc add
		rgbgen identity
	}
}

textures/proto2/redflare2
{
	deformvertexes autosprite2
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm nolightmap
	cull none
	{
		map textures/proto2/redflare2
		blendfunc add
		rgbgen identity
	}
}

textures/ctf2/blueteam01
{
	surfaceparm trans
	surfaceparm nomarks
	surfaceparm nolightmap
	polygonoffset
	cull none
	{
		map textures/ctf2/blueteam01
		alphafunc GE128
		blendFunc GL_DST_COLOR GL_ONE
		rgbgen wave sin .9 1 0 .1
	}
}

textures/ctf2/redteam01
{
	surfaceparm trans
	surfaceparm nomarks
	surfaceparm nolightmap
	polygonoffset
	cull none
	{
		map textures/ctf2/redteam01
		alphafunc GE128
		blendFunc GL_DST_COLOR GL_ONE
		rgbgen wave sin .9 1 0 .1
	}
}
//remap shader thingies
textures/ctf2/blueteam02
{
	qer_editorimage textures/ctf2/blueteam01
	surfaceparm trans
	surfaceparm nomarks
	surfaceparm nolightmap
	polygonoffset
	cull none
	{
		map textures/ctf2/blueteam01
		alphafunc GE128
		blendFunc GL_DST_COLOR GL_ONE
		rgbgen wave sin .9 1 0 .1
	}
}

textures/ctf2/redteam02
{
	qer_editorimage textures/ctf2/redteam01
	surfaceparm trans
	surfaceparm nomarks
	surfaceparm nolightmap
	polygonoffset
	cull none
	{
		map textures/ctf2/redteam01
		alphafunc GE128
		blendFunc GL_DST_COLOR GL_ONE
		rgbgen wave sin .9 1 0 .1
	}
}

textures/ctf2/blue_banner02
{
	cull none
	nopicmip
	{
		map textures/ctf2/blue_banner02.jpg
		rgbgen identity
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
	}
}

textures/ctf2/red_banner02
{
	cull none
	nopicmip
	{
		map textures/ctf2/red_banner02.jpg
		rgbgen identity
	}
	{
		map $lightmap
		rgbgen identity
		blendfunc filter
	}
}

textures/ctf/test2_trans
{
	qer_editorimage textures/ctf/test2
	surfaceparm nonsolid
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/ctf/test2
		rgbgen identity
		blendfunc filter
	}
}

textures/ctf/test2_r_trans
{
	qer_editorimage textures/ctf/test2_r
	surfaceparm nonsolid
	{
		map $lightmap
		rgbgen identity
	}
	{
		map textures/ctf/test2_r
		rgbgen identity
		blendfunc filter
	}
}
