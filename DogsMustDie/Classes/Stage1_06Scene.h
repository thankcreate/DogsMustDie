#ifndef Stage1_06Scene_h__
#define Stage1_06Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage1_06Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage1_06Scene);
	virtual StageBaseLayer* getMainStageLayer();

	
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
};

#endif // Stage1_06Scene_h__