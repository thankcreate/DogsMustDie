#include "Stage1_07Scene.h"
#include "Stage1_07Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_07Scene::getMainStageLayer()
{
	return Stage1_07Layer::create();
}



const char* Stage1_07Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_3.mp3";
}