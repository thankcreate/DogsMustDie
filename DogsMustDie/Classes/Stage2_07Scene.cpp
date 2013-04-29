#include "Stage2_07Scene.h"
#include "Stage2_07Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_07Scene::getMainStageLayer()
{
	return Stage2_07Layer::create();
}



const char* Stage2_07Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_2.mp3";
}