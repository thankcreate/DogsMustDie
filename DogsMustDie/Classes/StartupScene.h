//
//  StartupScene.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#ifndef __DogsMustDie__StartupScene__
#define __DogsMustDie__StartupScene__

#include "cocos2d.h"
#include "StartupLayer.h"
#include "Box2D/Box2D.h"

class StartupScene : public cocos2d::CCScene
{
public:
	StartupScene(void);
	~StartupScene(void);
    
	virtual bool init();
	CREATE_FUNC(StartupScene);
    
	CC_SYNTHESIZE(StartupLayer*, _startupLayer, StartupLayer);
};

#endif /* defined(__DogsMustDie__StartupScene__) */
