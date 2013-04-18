#include "LineLayer.h"

LineLayer::LineLayer() :
	m_bNeedDraw(false)
{

}

LineLayer::~LineLayer()
{

}

void LineLayer::setLine(CCPoint start, CCPoint end)
{
	m_pointStart = start;
	m_pointEnd = end;
}

void LineLayer::setStart(CCPoint start)
{
	m_pointStart = start;
}


void LineLayer::setEnd(CCPoint end)
{
	m_pointEnd = end;
}

void LineLayer::setNeedDraw(bool need)
{
	m_bNeedDraw = need;
}

void LineLayer::draw()
{
	if(!m_bNeedDraw)
		return;
	ccDrawColor4B(255, 104, 0, 255);

	ccPointSize(4);  
	float interval = 10.0f;
	float distance = ccpDistance(m_pointStart, m_pointEnd);
	int count = distance / interval;
	float xInterval = interval / distance * (m_pointEnd.x - m_pointStart.x);
	float yInterval = interval / distance * (m_pointEnd.y - m_pointStart.y);
	for(int i = 0; i < count; i ++)
	{
		ccDrawPoint(ccp(m_pointStart.x + i  * xInterval, m_pointStart.y + i  * yInterval));
		/*ccDrawCircle(ccp(m_pointStart.x + i  * xInterval, m_pointStart.y + i  * yInterval),
			10, CC_DEGREES_TO_RADIANS(360), 60, true);*/
		//break;
	}
}




