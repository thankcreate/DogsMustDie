#ifndef Stage3_02Scene_h__
#define Stage3_02Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage3_02Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage3_02Scene);
	virtual StageBaseLayer* getMainStageLayer();

	
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 39; }
};

#endif // Stage3_02Scene_h__