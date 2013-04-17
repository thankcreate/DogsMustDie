#include "SettingScene.h"
using namespace cocos2d;

SettingScene::SettingScene(void)
{

}

SettingScene::~SettingScene(void)
{
}

bool SettingScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		m_pSettingLayer = SettingLayer::create();
		this->addChild(m_pSettingLayer, 0);
		bRet = true;
	} while (0);
	return bRet;
}
