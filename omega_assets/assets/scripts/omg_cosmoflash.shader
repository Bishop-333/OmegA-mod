textures/cosmo_sfx/flag_scimitar_brown1
{
        qer_editorimage textures/cosmo_sfx/flag_scimitar_brown1
        surfaceparm nomarks
        surfaceparm alphashadow
        cull none
	nopicmip
        
    {
        map textures/cosmo_sfx/flag_scimitar_brown1
        blendFunc GL_ONE GL_ZERO
        alphaFunc GE128
        depthWrite
		rgbGen identity
	}
    {
		map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
		rgbGen identity
	}

}

textures/cosmo_sfx/flag_oa_brown1
{
        qer_editorimage textures/cosmo_sfx/flag_oa_brown1
        surfaceparm nomarks
        surfaceparm alphashadow
        cull none
	nopicmip
        
    {
        map textures/cosmo_sfx/flag_oa_brown
        blendFunc GL_ONE GL_ZERO
        alphaFunc GE128
		rgbGen identity
	}
    {
		map $lightmap
		rgbGen identity
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
	}
}

textures/cosmo_sfx/flag_oa_red1
{
        qer_editorimage textures/cosmo_sfx/flag_oa_red1
        surfaceparm nomarks
        surfaceparm alphashadow
        cull none
	nopicmip
        
    {
        map textures/cosmo_sfx/flag_oa_red1
        blendFunc GL_ONE GL_ZERO
        alphaFunc GE128
		rgbGen identity
	}
    {
		map $lightmap
		rgbGen identity
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
	}
}

textures/cosmo_sfx/flag_oa_blue1
{
        qer_editorimage textures/cosmo_sfx/flag_oa_blue1
        surfaceparm nomarks
        surfaceparm alphashadow
        cull none
	nopicmip
        
    {
        map textures/cosmo_sfx/flag_oa_blue1
        blendFunc GL_ONE GL_ZERO
        alphaFunc GE128
		rgbGen identity
	}
    {
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
		rgbGen identity
	}
}
