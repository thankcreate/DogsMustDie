#include "SubStageItem.h"
#include "PermissionManager.h"
#include "MiscTool.h"

SubStageItem::SubStageItem() :
m_smallIndex(0),
	m_bigIndex(0)
{

}

SubStageItem* SubStageItem::create(int bigIndex, int smallIndex, CCObject* target, SEL_MenuHandler selector)
{
	SubStageItem *pRet = new SubStageItem();
	pRet->m_bigIndex = bigIndex;
	pRet->m_smallIndex = smallIndex;

	// normal
	CCSprite* normal = CCSprite::create("StageSelect_tinyblock.png");

	CCString* pStr = CCString::createWithFormat("%d", smallIndex);
	CCLabelTTF* pLabel = CCLabelTTF::create(pStr->getCString(), "8bitoperator JVE.ttf", 55);
	pLabel->setColor(ccWHITE);
	pLabel->setPosition(ccp(normal->boundingBox().size.width / 2 , 36));
	normal->addChild(pLabel);

	int score = MiscTool::getScoreForLevel(bigIndex, smallIndex);
	float xInterval = 30;
	if(score >=1)
	{
		// 这里从1开始算i会直观一点
		for(int i = 1 ; i <= 3; i ++)
		{
			CCSprite* pScore = CCSprite::create();
			if(i <= score)			
				pScore->initWithFile("StageSelect_item_score_fill.png");
			else
				pScore->initWithFile("StageSelect_item_score_empty.png");
			pScore->setPosition(ccp(20 + (i - 1) * xInterval, 9));
			normal->addChild(pScore);
		}
	}

	// seleted
	CCSprite* selected = CCSprite::create("StageSelect_tinyblock_pressed.png");
	xInterval = 30;
	if(score >=1)
	{
		// 这里从1开始算i会直观一点
		for(int i = 1 ; i <= 3; i ++)
		{
			CCSprite* pScore = CCSprite::create();
			if(i <= score)			
				pScore->initWithFile("StageSelect_item_score_fill.png");
			else
				pScore->initWithFile("StageSelect_item_score_empty.png");
			pScore->setPosition(ccp(20 + (i - 1) * xInterval, 9));
			selected->addChild(pScore);
		}
	}

	CCLabelTTF* pLabel2 = CCLabelTTF::create(pStr->getCString(), "8bitoperator JVE.ttf", 55);
	pLabel2->setColor(ccWHITE);
	pLabel2->setPosition(ccp(selected->boundingBox().size.width / 2 , 36));
	selected->addChild(pLabel2);

	CCSprite* disabled = CCSprite::create("StageSelect_tinyblock_locked.png");

	if (pRet && pRet->initWithNormalSprite(normal, selected, disabled, target, selector))
	{
		bool enable = PermissionManager::getSharedInstance()->isStageAllowed(bigIndex, smallIndex);
		pRet->setEnabled(enable); 
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
