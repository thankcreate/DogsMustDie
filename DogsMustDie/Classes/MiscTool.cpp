#include "MiscTool.h"
#include "Defines.h "


void MiscTool::saveScoreForLevel( int big, int small1, int score )
{
	// ÿ��һ��ʱ��������һ�صķ���
	// ������ǵ�һ��ͨ����һ�أ��Ƚ���֮ǰ�ķ�����ȡ�ϴ���
	if(score > 3)
		score = 3;
	int scoreBefore = getScoreForLevel(big, small1);
	if(score > scoreBefore)
	{
		CCString* key = makeLevelScoreString(big ,small1);
		SaveIntegerToXML(key->getCString(), score);
		SaveUserDefault();
	}		
}

int MiscTool::getScoreForLevel( int big, int small1 )
{
	CCString* key = makeLevelScoreString(big ,small1);
	return LoadIntegerFromXML(key->getCString(), -1);
}

CCString* MiscTool::makeLevelScoreString( int big, int small1 )
{
	return CCString::createWithFormat("Score_For_Level_%d_%d" ,big, small1);
}

bool MiscTool::probabilityHit( float prob )
{
	if(prob <=0 || prob > 1)
		return false;

	bool hit = CCRANDOM_0_1() < prob;
	return hit;
}

// ����[0, input) �������
int MiscTool::getRandom( int input )
{
	int r = CCRANDOM_0_1() * input;
	if(r == input)
		r = input - 1;

	if(r < 0)
		r = 0;

	return r;
}
