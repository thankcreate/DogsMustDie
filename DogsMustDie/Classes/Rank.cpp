#include "Rank.h"


Rank::Rank()
{

}

void Rank::initWithCount( int count )
{
	init();
	this->removeAllChildrenWithCleanup(true);

	if(count == 0)
		return;

	this->initWithFile("Rank.png");
	for(int i = 1; i < count; i ++)
	{
		CCSprite* pOneRank = CCSprite::create("Rank.png");
		CCSize selfSize = this->boundingBox().size;
		pOneRank->setPosition(ccp(selfSize.width / 2, selfSize.height * (0.5 + i)));
		this->addChild(pOneRank);
	}
}

Rank* Rank::createWithCount( int count )
{
	if(count <= 0)
	{
		Rank* pResult = new Rank();
		pResult->init();
		return pResult;
	}
	Rank* pResult = new Rank();
	pResult->initWithCount(count);
	return pResult;
}
