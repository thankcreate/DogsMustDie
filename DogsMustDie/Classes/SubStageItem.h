#ifndef SubStageItem_h__
#define SubStageItem_h__

#include "cocos2d.h"

using namespace cocos2d;

class SubStageItem : public CCMenuItemImage
{
public:
	SubStageItem();
	static SubStageItem* create(int bigIndex, int smallIndex, CCObject* target, SEL_MenuHandler selector);
	int m_bigIndex;
	int m_smallIndex;
};

#endif // SubStageItem_h__
