#ifndef MiscTool_h__
#define MiscTool_h__

#include "cocos2d.h"

using namespace cocos2d;


// �����࣬�󲿷ֶ���static����
class MiscTool
{
public:
	static CCString* makeLevelScoreString(int big, int small1s);
	static void saveScoreForLevel(int big, int small1, int starCount);
	static int getScoreForLevel(int big, int small1);

	static bool probabilityHit(float prob);
	static int getRandom(int input);
};

#endif // MiscTool_h__

