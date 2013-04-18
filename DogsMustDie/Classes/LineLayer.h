#ifndef LineLayer_h__
#define LineLayer_h__

#include "cocos2d.h"

using namespace cocos2d;

class LineLayer : public CCLayer
{
public:
	LineLayer();
	~LineLayer();

	CREATE_FUNC(LineLayer);

	CCPoint m_pointStart;
	CCPoint m_pointEnd;
	bool m_bNeedDraw;

	void draw();
	void setNeedDraw(bool need);
	void setLine(CCPoint start, CCPoint end);	
	void setStart(CCPoint start);
	void setEnd(CCPoint end);
};

#endif // LineLayer_h__
