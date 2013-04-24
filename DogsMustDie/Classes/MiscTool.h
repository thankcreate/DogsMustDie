#ifndef MiscTool_h__
#define MiscTool_h__

#include "cocos2d.h"

using namespace cocos2d;


// 工具类，大部分都是static方法
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

