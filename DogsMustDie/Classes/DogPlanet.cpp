#include "DogPlanet.h"

DogPlanet::DogPlanet()
{

}

bool DogPlanet::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Planet::init());
		m_nForceSide = kForceSideDog;

		initWithFile("Planet_dog.png");


		CCSprite* dogAvatar = CCSprite::create("Dog_normal.png");
		CCSize planetSize = this->boundingBox().size;
		dogAvatar->setPosition(ccp(planetSize.width / 2 - 2, planetSize.height / 2 - 3));
		this->addChild(dogAvatar);

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

