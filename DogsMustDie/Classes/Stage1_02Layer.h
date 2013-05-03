#ifndef Stage1_02Layer_h__
#define Stage1_02Layer_h__

#include "Stage1_02Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage1_02Layer : public StageBaseLayer
{
public:
	Stage1_02Layer();
	
	CREATE_FUNC(Stage1_02Layer);
	
	CC_SYNTHESIZE(Planet*, m_pDog, Dog);
	CC_SYNTHESIZE(Planet*, m_pCatRight, CatRight);

	CC_SYNTHESIZE(CCSprite*, m_pGuideBorder, GuideBorder);
	CC_SYNTHESIZE(CCSprite*, m_pScorePrompt, ScorePrompt);	
	CC_SYNTHESIZE(CCLabelTTF*, m_pScorePromptLabel, ScorePromptLabel);	

	bool init();
	void initPlanets();	
	void attack(float dt);	
	void initGuideLayer(float dt);
	void moveRightGuideLayer(float dt);	
	void initLoadedAction();
	void initLoadedAction(float dt);
	void showScorePrompt(float dt);
	void moveLeftScorePromptLayer(float dt);
	void showNextScorePrompt(float dt);
};

#endif // Stage1_02Layer_h__

