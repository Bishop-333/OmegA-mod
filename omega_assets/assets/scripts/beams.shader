lightningBolt
{
	cull disable
	{
		animmap 30 textures/oafx/lbeam3 textures/oafx/lbeam4 textures/oafx/lbeam5 textures/oafx/lbeam6 textures/oafx/lbeam7 textures/oafx/lbeam8 textures/oafx/lbeam5 textures/oafx/lbeam7 
		blendfunc add
		tcMod scale 0.5 1
		tcMod scroll -1 0
	}
	{
		animmap 40 textures/oafx/lbeam8 textures/oafx/lbeam7 textures/oafx/lbeam4 textures/oafx/lbeam5 textures/oafx/lbeam6 textures/oafx/lbeam3 textures/oafx/lbeam7 textures/oafx/lbeam4 
		blendfunc add
		tcMod scale 0.2 1
		tcMod scroll -0.3 0
	}
}

lightningBoltnew
{
	cull none
	nopicmip
	{
		map textures/oafx/lightningscroll
		blendfunc add
		tcMod scale 0.5 1
		tcMod scroll -1.6 0
	}
	{
		map textures/oafx/lightningscroll
		blendfunc add
		tcMod scale -0.5 -1
		tcMod scroll -4.2 0
	}
}

lightningBoltNewNPM
{
	cull disable
	{
		animmap 30 textures/oafx/lbeam3 textures/oafx/lbeam4 textures/oafx/lbeam5 textures/oafx/lbeam6 textures/oafx/lbeam7 textures/oafx/lbeam8 textures/oafx/lbeam5 textures/oafx/lbeam7 
		blendfunc add
		tcMod scale 0.5 1
		tcMod scroll -1 0
	}
	{
		animmap 40 textures/oafx/lbeam8 textures/oafx/lbeam7 textures/oafx/lbeam4 textures/oafx/lbeam5 textures/oafx/lbeam6 textures/oafx/lbeam3 textures/oafx/lbeam7 textures/oafx/lbeam4 
		blendfunc add
		tcMod scale 0.2 1
		tcMod scroll -0.3 0
	}
}

