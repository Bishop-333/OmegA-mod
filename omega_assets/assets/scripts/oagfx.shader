lagometer
{
	nopicmip
	{
		map gfx/2d/lag
	}
}

gfx/2d/lag
{
	nopicmip
	{
		map gfx/2d/lag
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		
	}
}

disconnected
{
	{
		map gfx/2d/net
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA 
	}
}

levelShotDetail
{
	nopicmip
	{
		map textures/sfx/detail
		blendFunc GL_DST_COLOR GL_SRC_COLOR
		rgbgen identity
	}
}

