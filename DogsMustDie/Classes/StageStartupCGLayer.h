//
//  StageStartupCGLayer.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#ifndef __DogsMustDie__StageStartupCGLayer__
#define __DogsMustDie__StageStartupCGLayer__

#include "cocos2d.h"

using namespace cocos2d;
class StageStartupCGLayer : public CCLayer
{
public:
	StageStartupCGLayer(void);
	
	CREATE_FUNC(StageStartupCGLayer);

	CC_SYNTHESIZE(CCLabelTTF*, m_pStoryLabel, StoryLabel);

	bool init();	
	void initStory();

	void skipCallback(CCObject* pSender);
	void skipAutoInDelay(float dt);
};


#endif /* defined(__DogsMustDie__StageStartupCGLayer__) */

