#include "AdViewManager.h"
#include "Defines.h"

AdViewManager::AdViewManager() :
m_pAdView(NULL)
{

}

AdViewManager* AdViewManager::m_pInstance = NULL;

AdViewManager* AdViewManager::sharedInstance()
{
	if(!m_pInstance)
		m_pInstance = new AdViewManager();
	return m_pInstance;
}

void AdViewManager::show(CCNode* parent )
{
	if(m_pAdView == NULL)
	{
		CCSize size = WIN_SIZE;
		setAdView(CCAdView::create(kCCAdSizeBanner, "a15159a123e53f4"));		
		m_pAdView->setAlignment(kCCHorizontalAlignmentCenter, kCCVerticalAlignmentBottom);
		m_pAdView->useLocation(kCCLocationCoarse);
		parent->addChild(m_pAdView, 20);		
	}
	m_pAdView->loadAd();
	m_pAdView->setVisible(true);
}

void AdViewManager::hide()
{
	if(m_pAdView)
	{
		m_pAdView->setVisible(false);
	}
}

AdViewManager::~AdViewManager()
{
	CC_SAFE_RELEASE(m_pAdView);
}


