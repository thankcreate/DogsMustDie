#ifndef Stage1_02Scene_h__
#define Stage1_02Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage1_02Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage1_02Scene);
	virtual StageBaseLayer* getMainStageLayer();

	void gotoNext();
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
};

#endif // Stage1_02Scene_h__
