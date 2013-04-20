#include "StarObject.h"
#include "GameObject.h"

StarObject::StarObject() :
	m_bHasBeenGotBySomeOne(false)
{

}

bool StarObject::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!GameObject::init());
		setType(kGameObjectStar);
		initWithFile("Star.png");

		CCScaleTo* pScaleToSmall = CCScaleTo::create(1, 0.5, 0.5);
		CCScaleTo* pScaleRestore = CCScaleTo::create(1, 1, 1);
		CCSequence* pSeq = CCSequence::createWithTwoActions(pScaleToSmall, pScaleRestore);
		this->runAction(CCRepeatForever::create(pSeq));

		bRet = true;
	}while(0);  

	return bRet;
}

CCPoint StarObject::getBox2dObjectSize()
{
	return ccp(38, 38);
}



void StarObject::destroyInNextUpdate()
{
	// 什么都不干，仅仅为了把这个函数设为private
}

void StarObject::setHasBeenGotBySomeOne( bool isGot )
{
	m_bHasBeenDestroied = true;
	m_bHasBeenGotBySomeOne = true;
	this->stopAllActions();
	setVisible(false);
}

bool StarObject::isDirty()
{
	bool superIsDirty = GameObject::isDirty();
	return (superIsDirty || m_bHasBeenGotBySomeOne);
}
