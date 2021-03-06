#ifndef Stage3_04Scene_h__
#define Stage3_04Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage3_04Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage3_04Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 89; }
};

#endif // Stage3_04Scene_h__