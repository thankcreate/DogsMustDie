#ifndef OptionDelegate_h__
#define OptionDelegate_h__



#include "cocos2d.h"

using namespace cocos2d;

class OptionDelegate
{
public:
	virtual void opGoBack() {};
	virtual void opReStart() {};
	virtual void opSound(bool isOn){}
};

#endif // OptionDelegate_h__