#include "SubStageItem.h"
#include "PermissionManager.h"

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


	CCSprite* normal = CCSprite::create("StageSelect_tinyblock.png");

	CCString* pStr = CCString::createWithFormat("%d", smallIndex);
	CCLabelTTF* pLabel = CCLabelTTF::create(pStr->getCString(), "8bitoperator JVE.ttf", 55);
	pLabel->setColor(ccWHITE);
	pLabel->setPosition(ccp(42 , 36));
	normal->addChild(pLabel);

	CCSprite* selected = CCSprite::create("StageSelect_tinyblock_pressed.png");

	CCLabelTTF* pLabel2 = CCLabelTTF::create(pStr->getCString(), "8bitoperator JVE.ttf", 55);
	pLabel2->setColor(ccWHITE);
	pLabel2->setPosition(ccp(42 , 36));
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
