#ifndef StageSelectorFrameSprite_h__
#define StageSelectorFrameSprite_h__

#include "cocos2d.h"

using namespace cocos2d;

class StageSelectFrameSprite : public CCSprite
{
public:	
	static StageSelectFrameSprite* create(CCNode* parent,  CCObject* target, SEL_MenuHandler handler, int mBigIndex, const char* title);
};

#endif // StageSelectorFrameSprite_h__
