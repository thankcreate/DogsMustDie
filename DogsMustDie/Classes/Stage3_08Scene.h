#ifndef Stage3_08Scene_h__
#define Stage3_08Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage3_08Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage3_08Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 41; }
};

#endif // Stage3_08Scene_h__