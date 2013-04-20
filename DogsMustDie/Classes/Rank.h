#ifndef Rank_h__
#define Rank_h__

#include "cocos2d.h"

using namespace cocos2d;

// 这个类是专门来来画星球的军衔的
class Rank : public CCSprite
{
public:
	Rank();
	static Rank* createWithCount(int count);
	void initWithCount( int count );
};

#endif // Rank_h__
