#include "Stage2_05Scene.h"
#include "Stage2_05Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_05Scene::getMainStageLayer()
{
	return Stage2_05Layer::create();
}



const char* Stage2_05Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_5.mp3";
}