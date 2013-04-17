#ifndef MyMenu_h__
#define MyMenu_h__

#include "cocos2d.h"

using namespace cocos2d;

class MyMenu : public CCMenu
{
public:
	MyMenu();
	CREATE_FUNC(MyMenu);

	virtual void registerWithTouchDispatcher();

};

#endif // MyMenu_h__
