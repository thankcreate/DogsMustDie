#ifndef Stage1_05Scene_h__
#define Stage1_05Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage1_05Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage1_05Scene);
	virtual StageBaseLayer* getMainStageLayer();

	
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 33; }
};

#endif // Stage1_05Scene_h__