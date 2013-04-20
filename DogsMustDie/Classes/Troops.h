#ifndef Troops_h__
#define Troops_h__

#include "cocos2d.h"
#include "FightObject.h"

using namespace cocos2d;


class Planet;
class Face;
class Troops : public FightObject
{
public:	
	Troops();
	bool init();

	static Troops* createWithForceSide(int force);
	void initWithForceSide(int force);		

	CC_SYNTHESIZE(CCSprite*, m_pBubble, Bubble );
	CC_SYNTHESIZE(Face*, m_pFace, Face);
	CC_SYNTHESIZE(CCLabelTTF*, m_pFightUnitLabel, FightUnitLabel );
	CC_SYNTHESIZE(Planet*, m_pHomePort, HomePort);  // 母港必然是Planet
	CC_SYNTHESIZE(GameObject*, m_pTargetObject, TargetObject);   // 目的地要么是Star，要么是Planet
	CC_SYNTHESIZE(CCSprite*, m_pCarriedStar, CarriedStar);

	void setFightUnitCount(int input);
	int getMaximumUnitCount();
	CCPoint getBox2dObjectSize();
	float getAbsoluteSpeed();

	
	void gotoTarget();
	void goHome();

	bool isInReturn() {return m_bIsInReturn;}


	void setTroopsType(int troopsType) { m_nTroopsType = troopsType; }
	int getTroopsType() { return m_nTroopsType; }
	void setHasGotStar(bool got);
	bool hasGotStar() {return m_bHasGotStar;}

private:
	int m_nTroopsType; // 是否是追星星的Troop
	bool m_bHasGotStar;  // 是否带着星星，因为回来时不一定带着星星，可能已经被别人抢走了
	bool m_bIsInReturn;
	float speedCoefficient;
};

#endif // Troops_h__
