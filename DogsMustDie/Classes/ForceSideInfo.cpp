#include "ForceSideInfo.h"
#include "Defines.h"

ForceSideInfo::ForceSideInfo() :
m_nStarCount(0),
m_nForceSide(kForceSideCat)
{

}

ForceSideInfo* ForceSideInfo::create( int forceSide, int starCount )
{
	ForceSideInfo* pResult = new ForceSideInfo();
	pResult->autorelease();
	pResult->m_nForceSide = forceSide;
	pResult->m_nStarCount = starCount;
	return pResult;
}