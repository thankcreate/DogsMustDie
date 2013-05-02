//
//  StageStartupCGScene.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#ifndef __DogsMustDie__StageStartupCGScene__
#define __DogsMustDie__StageStartupCGScene__

#include "cocos2d.h"
#include "StageStartupCGLayer.h"

class StageStartupCGScene : public cocos2d::CCScene
{
public:
	StageStartupCGScene(void);
	~StageStartupCGScene(void);

	virtual bool init();
	CREATE_FUNC(StageStartupCGScene);

	CC_SYNTHESIZE(StageStartupCGLayer*, _StageStartupCGLayer, StageStartupCGLayer);
};

#endif /* defined(__DogsMustDie__StageStartupCGScene__) */
