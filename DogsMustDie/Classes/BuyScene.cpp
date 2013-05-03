#include "BuyScene.h"
using namespace cocos2d;

BuyScene::BuyScene(void)
{

}

BuyScene::~BuyScene(void)
{
}

bool BuyScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		m_pBuyLayer = BuyLayer::create();
		this->addChild(m_pBuyLayer, 0);
		bRet = true;
	} while (0);
	return bRet;
}
