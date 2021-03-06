#ifndef Stage3_01Scene_h__
#define Stage3_01Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage3_01Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage3_01Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 92; }
};

#endif // Stage3_01Scene_h__