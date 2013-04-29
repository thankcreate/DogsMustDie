#include "Stage1_01Scene.h"
#include "Stage1_01Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_01Scene::getMainStageLayer()
{
	return Stage1_01Layer::create();
}


const char* Stage1_01Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}