#ifndef Stage2_05Scene_h__
#define Stage2_05Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_05Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_05Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 43; }
};

#endif // Stage2_05Scene_h__