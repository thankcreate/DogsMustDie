#ifndef StageTemplateScene_h__
#define StageTemplateScene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class StageTemplateScene : public StageBaseScene
{
public:	
	CREATE_FUNC(StageTemplateScene);
	virtual StageBaseLayer* getMainStageLayer();
		
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
};

#endif // StageTemplateScene_h__