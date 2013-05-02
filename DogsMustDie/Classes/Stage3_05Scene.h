#ifndef Stage3_05Scene_h__
#define Stage3_05Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage3_05Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage3_05Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 53; }
};

#endif // Stage3_05Scene_h__