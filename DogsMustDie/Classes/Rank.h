#ifndef Rank_h__
#define Rank_h__

#include "cocos2d.h"

using namespace cocos2d;

// �������ר������������ľ��ε�
class Rank : public CCSprite
{
public:
	Rank();
	static Rank* createWithCount(int count);
	void initWithCount( int count );
};

#endif // Rank_h__
