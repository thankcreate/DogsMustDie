#include "Stage2_06Scene.h"
#include "Stage2_06Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_06Scene::getMainStageLayer()
{
	return Stage2_06Layer::create();
}



const char* Stage2_06Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_6.mp3";
}