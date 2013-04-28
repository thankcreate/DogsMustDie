#include "StageSelectFrameSprite.h"
#include "SubStageItem.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"



StageSelectFrameSprite* StageSelectFrameSprite::create(CCNode* parent, CCObject* target, SEL_MenuHandler handler, int mBigIndex, const char* title)
{
	StageSelectFrameSprite* pRet = new StageSelectFrameSprite();

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	if(mBigIndex >= LOCK_BEGIN_INDEX)
	{
		bool bPurchased = LoadBooleanFromXML(KEY_PRO_UPGRADE_PURCHASED);
		if(!bPurchased)
		{
			pRet->initWithFile("StageSelect_frame_locked.png");
			return pRet;
		}
		else
		{
			pRet->initWithFile("StageSelect_frame.png");
		}

	}
	else
	{
		pRet->initWithFile("StageSelect_frame.png");
	}
#else
	pRet->initWithFile("StageSelect_frame.png");
#endif

	// 3. 标题
	CCSprite* pTitle= CCSprite::create(title);		
	pTitle->setPosition(ccp(pRet->boundingBox().size.width / 2 - 15, 340));
	pRet->addChild(pTitle, 1);

	// 4. 选关按钮
	float originX = 107;
	float originY = 240;
	float intervalX  = 125;
	float intervalY = 74;

	int xNum = 3;
	int yNum = 3;

	CCMenu* pStageMenu = CCMenu::create(NULL);
	pStageMenu->setPosition(CCPointZero);	
	pRet->addChild(pStageMenu, 1);

	for(int i = 0; i < xNum; i++)
	{
		for(int j = 0; j < yNum; j++)
		{
			SubStageItem* item = SubStageItem::create(mBigIndex, j * xNum + i + 1, 
				target, handler);
			item->setPosition(ccp(originX + i * intervalX, originY - j * intervalY));
			pStageMenu->addChild(item);
		}
	}


	if (pRet)
	{		
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

