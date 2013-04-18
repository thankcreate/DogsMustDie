#include "StarObject.h"

StarObject::StarObject()
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

