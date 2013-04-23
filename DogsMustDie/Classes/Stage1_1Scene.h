#ifndef Stage1_1Scene_h__
#define Stage1_1Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage1_1Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage1_1Scene);
	virtual StageBaseLayer* getMainStageLayer();
	void gotoNext();
	const char* getBGMFileName();
};

#endif // Stage1_1Scene_h__