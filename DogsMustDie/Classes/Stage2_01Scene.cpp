#include "Stage2_01Scene.h"
#include "Stage2_01Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_01Scene::getMainStageLayer()
{
	return Stage2_01Layer::create();
}



const char* Stage2_01Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}