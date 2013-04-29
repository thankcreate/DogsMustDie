#ifndef Stage1_01Scene_h__
#define Stage1_01Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage1_01Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage1_01Scene);
	virtual StageBaseLayer* getMainStageLayer();

	
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
};

#endif // Stage1_01Scene_h__
