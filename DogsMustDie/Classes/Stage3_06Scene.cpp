#include "Stage3_06Scene.h"
#include "Stage3_06Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_06Scene::getMainStageLayer()
{
	return Stage3_06Layer::create();
}



const char* Stage3_06Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}