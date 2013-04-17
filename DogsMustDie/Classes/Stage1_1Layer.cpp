#include "Stage1_1Layer.h"

Stage1_1Layer::Stage1_1Layer()
{

}

Stage1_1Layer::~Stage1_1Layer()
{

}

bool Stage1_1Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
			

		bRet = true;
	} while (0);

	return bRet;
}

