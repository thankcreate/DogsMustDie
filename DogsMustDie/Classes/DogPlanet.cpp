#include "DogPlanet.h"

DogPlanet::DogPlanet()
{

}

bool DogPlanet::init()
{
	bool bRet = false;
	do 
	{		
		initWithForceSide(kForceSideDog);
		bRet = true;
	}while(0);
	return bRet;	
}

