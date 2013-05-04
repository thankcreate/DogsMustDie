#ifndef Stage1_03Scene_h__
#define Stage1_03Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage1_03Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage1_03Scene);
	virtual StageBaseLayer* getMainStageLayer();
		
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 25; }
};

#endif // Stage1_03Scene_h__