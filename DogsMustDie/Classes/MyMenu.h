#ifndef MyMenu_h__
#define MyMenu_h__

#include "cocos2d.h"

using namespace cocos2d;

// 因为在弹出层里需要屏蔽后层的按键点击，把弹出层的优先级设高了
// 所以弹出层本身的按键也会被屏蔽
// 故设此类专用于弹出层的Menu
// 之所以不直接setHandlerPriority是因为其时序很难把握，易崩溃
class MyMenu : public CCMenu
{
public:
	MyMenu();
	CREATE_FUNC(MyMenu);

	virtual void registerWithTouchDispatcher();

};

#endif // MyMenu_h__
