#include "cocos2d.h"

using namespace cocos2d;


class ForceSideInfo : public CCObject
{
public:
	ForceSideInfo();

	// return an autorealeased object
	static ForceSideInfo* create(int forceSide, int m_nStarCount); 

	int getForceSide() {return m_nForceSide;}
	int getStarCount() {return m_nStarCount;}
	void setStarCount(int input) {m_nStarCount = input;}
private:
	int m_nStarCount;
	int m_nForceSide;
};