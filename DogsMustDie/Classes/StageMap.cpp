#include "StageMap.h"
#include "Defines.h"
#include "StageBaseScene.h"
#include "MyUseDefaultDef.h"

#include "Stage1_1Scene.h"
#include "Stage1_2Scene.h"

StageMap* StageMap::m_pInstance = NULL;

StageMap* StageMap::sharedInstance()
{
	if(!m_pInstance)
		m_pInstance = new StageMap();
	return m_pInstance;
}


void StageMap::gotoStage( int bigIndex, int smallIndex )
{
	// 检查是不是要到付费2-1 这是付费关卡的第一关

	int toBig = LoadIntegerFromXML(KEY_PLAYED_TO_BIG, 1);
	int toSmall =  LoadIntegerFromXML(KEY_PLAYED_TO_SMALL, 1);

	if(bigIndex > toBig )
	{
		SaveIntegerToXML(KEY_PLAYED_TO_BIG, bigIndex);
		SaveIntegerToXML(KEY_PLAYED_TO_SMALL, smallIndex);
		SaveUserDefault();
	}
	else if(bigIndex == toBig &&  smallIndex > toSmall)
	{
		SaveIntegerToXML(KEY_PLAYED_TO_BIG, bigIndex);
		SaveIntegerToXML(KEY_PLAYED_TO_SMALL, smallIndex);
		SaveUserDefault();
	}

	StageBaseScene* stage = NULL;
	if(bigIndex == 1)
	{
		switch(smallIndex)
		{
		case 1:
			{				
				stage = Stage1_1Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 2:
			{				
				stage = Stage1_2Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		}
	}

	if(stage)
		stage->setLevel(bigIndex, smallIndex);
}



void gotoStageGameOver()
{

}