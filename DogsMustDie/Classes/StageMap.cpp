#include "StageMap.h"
#include "Defines.h"
#include "StageBaseScene.h"
#include "MyUseDefaultDef.h"

// 硬编码什么的
// c++没有原生dynamic create
// 懒得去自己写一个注册机制了
// 唉，越来越懒 >_< 懒死算了~
#include "Stage1_01Scene.h"
#include "Stage1_02Scene.h"
#include "Stage1_03Scene.h"
#include "Stage1_04Scene.h"
#include "Stage1_05Scene.h"
#include "Stage1_06Scene.h"
#include "Stage1_07Scene.h"
#include "Stage1_08Scene.h"
#include "Stage1_09Scene.h"

#include "Stage2_01Scene.h"
#include "Stage2_02Scene.h"
#include "Stage2_03Scene.h"
#include "Stage2_04Scene.h"
#include "Stage2_05Scene.h"
#include "Stage2_06Scene.h"
#include "Stage2_07Scene.h"
#include "Stage2_08Scene.h"
#include "Stage2_09Scene.h"


#include "Stage3_01Scene.h"
#include "Stage3_02Scene.h"
#include "Stage3_03Scene.h"
#include "Stage3_04Scene.h"
#include "Stage3_05Scene.h"
#include "Stage3_06Scene.h"
#include "Stage3_07Scene.h"
#include "Stage3_08Scene.h"
#include "Stage3_09Scene.h"


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

	StageBaseScene* stage = gotoStageInner(bigIndex, smallIndex);

	if(stage)
		stage->setLevel(bigIndex, smallIndex);
}



void StageMap::gotoStageGameOver()
{

}


// 目测这个函数有270行
// 好爽！
StageBaseScene* StageMap::gotoStageInner( int bigIndex, int smallIndex )
{
	StageBaseScene* stage = NULL;
	if(bigIndex == 1)
	{
		switch(smallIndex)
		{
		case 1:
			{				
				stage = Stage1_01Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 2:
			{				
				stage = Stage1_02Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 3:
			{				
				stage = Stage1_03Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 4:
			{				
				stage = Stage1_04Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 5:
			{				
				stage = Stage1_05Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 6:
			{				
				stage = Stage1_06Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 7:
			{				
				stage = Stage1_07Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 8:
			{				
				stage = Stage1_08Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 9:
			{				
				stage = Stage1_09Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}			
		}
	}

	else if(bigIndex == 2)
	{
		switch(smallIndex)
		{
		case 1:
			{				
				stage = Stage2_01Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 2:
			{				
				stage = Stage2_02Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 3:
			{				
				stage = Stage2_03Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 4:
			{				
				stage = Stage2_04Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 5:
			{				
				stage = Stage2_05Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 6:
			{				
				stage = Stage2_06Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 7:
			{				
				stage = Stage2_07Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 8:
			{				
				stage = Stage2_08Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 9:
			{				
				stage = Stage2_09Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}			
		}
	}

	else if(bigIndex == 3)
	{
		switch(smallIndex)
		{
		case 1:
			{				
				stage = Stage3_01Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 2:
			{				
				stage = Stage3_02Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 3:
			{				
				stage = Stage3_03Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 4:
			{				
				stage = Stage3_04Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 5:
			{				
				stage = Stage3_05Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 6:
			{				
				stage = Stage3_06Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 7:
			{				
				stage = Stage3_07Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 8:
			{				
				stage = Stage3_08Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}
		case 9:
			{				
				stage = Stage3_09Scene::create();				
				CCDirector::sharedDirector()->replaceScene(stage);				
				break;
			}			
		}
	}
	return stage;
}