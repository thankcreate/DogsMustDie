#include "CatTroops.h"

CatTroops::CatTroops()	
{

}

bool CatTroops::init()
{
	bool bRet = false;
	do 
	{		
		initWithForceSide(kForceSideCat);
		bRet = true;
	}while(0);
	return bRet;	
}

