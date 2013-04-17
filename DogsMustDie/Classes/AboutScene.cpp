#include "AboutScene.h"
using namespace cocos2d;

AboutScene::AboutScene(void)
{

}

AboutScene::~AboutScene(void)
{
}

bool AboutScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		m_pAboutLayer = AboutLayer::create();
		this->addChild(m_pAboutLayer, 0);
		bRet = true;
	} while (0);
	return bRet;
}
