#ifndef Stage3_09Layer_h__
#define Stage3_09Layer_h__

#include "Stage3_09Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_09Layer : public StageBaseLayer
{
public:
	Stage3_09Layer();

	CREATE_FUNC(Stage3_09Layer);

	CC_SYNTHESIZE(Planet*, m_pCat, Cat);
	CC_SYNTHESIZE(Planet*, m_pDog, Dog);
	CC_SYNTHESIZE(Planet*, m_pThird, Third);
	CC_SYNTHESIZE(Planet*, m_pMiddle1, Middle1);
	CC_SYNTHESIZE(Planet*, m_pMiddle2, Middle2);
	CC_SYNTHESIZE(Planet*, m_pMiddle3, Middle3);

	bool init();
	void initPlanets();		
	void run1(float dt);
	void run3(float dt);
	void run2(float dt);
	void restoreAI(float dt);

	int m_nCount1;
	int m_nCount2;
	int m_nCount3;
};

#endif // Stage3_09Layer_h__

