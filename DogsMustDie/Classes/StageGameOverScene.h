//
//  StageGameOverScene.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#ifndef __DogsMustDie__StageGameOverScene__
#define __DogsMustDie__StageGameOverScene__

#include "cocos2d.h"
#include "StageGameOverLayer.h"

class StageGameOverScene : public cocos2d::CCScene
{
public:
	StageGameOverScene(void);
	~StageGameOverScene(void);

	virtual bool init();
	CREATE_FUNC(StageGameOverScene);

	CC_SYNTHESIZE(StageGameOverLayer*, _StageGameOverLayer, StageGameOverLayer);
};

#endif /* defined(__DogsMustDie__StageGameOverScene__) */
