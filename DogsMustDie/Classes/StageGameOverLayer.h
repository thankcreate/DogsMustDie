//
//  StageGameOverLayer.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#ifndef __DogsMustDie__StageGameOverLayer__
#define __DogsMustDie__StageGameOverLayer__

#include "cocos2d.h"

using namespace cocos2d;
class StageGameOverLayer : public CCLayer
{
public:
	StageGameOverLayer(void);

	CREATE_FUNC(StageGameOverLayer);

	CC_SYNTHESIZE(CCLabelTTF*, m_pStoryLabel, StoryLabel);

	bool init();	
	void initStory();

	void skipCallback(CCObject* pSender);
	void skipAutoInDelay(float dt);
};


#endif /* defined(__DogsMustDie__StageGameOverLayer__) */

