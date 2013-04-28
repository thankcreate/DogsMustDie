#include "Stage3_07Scene.h"
#include "Stage3_07Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_07Scene::getMainStageLayer()
{
	return Stage3_07Layer::create();
}



const char* Stage3_07Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}