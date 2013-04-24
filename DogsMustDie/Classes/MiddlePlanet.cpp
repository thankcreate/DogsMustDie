#include "MiddlePlanet.h"

MiddlePlanet::MiddlePlanet()
{

}

bool MiddlePlanet::init()
{
	bool bRet = false;
	do 
	{		
		initWithForceSide(kForceSideMiddle);
		bRet = true;
	}while(0);
	return bRet;	
}

