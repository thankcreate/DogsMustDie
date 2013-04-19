#include "CatPlanet.h"

CatPlanet::CatPlanet()
{

}

bool CatPlanet::init()
{
	bool bRet = false;
	do 
	{		
		initWithForceSide(kForceSideCat);
		bRet = true;
	}while(0);
	return bRet;	
}

