#include "CatPlanet.h"

CatPlanet::CatPlanet()
{

}

bool CatPlanet::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Planet::init());
		m_nForceSide = kForceSideCat;

		initWithFile("Planet_cat.png");

		
		CCSprite* catAvatar = CCSprite::create("Cat_normal.png");
		CCSize planetSize = this->boundingBox().size;
		catAvatar->setPosition(ccp(planetSize.width / 2 - 2, planetSize.height / 2 - 3));
		this->addChild(catAvatar);

		CCString* pStr = CCString::createWithFormat("%d", m_nFightUnitCount);
		CCLabelTTF* pLabel = CCLabelTTF::create(pStr->getCString(), "00 Starmap Truetype.ttf", 19);
		ccColor3B ccMyOrange={255, 104, 0};
		pLabel->setColor(ccMyOrange);
		pLabel->setPosition(ccp(planetSize.width - 14 , planetSize.height - 16));
		this->addChild(pLabel);
		

		bRet = true;
	}while(0);
	return bRet;	
}

