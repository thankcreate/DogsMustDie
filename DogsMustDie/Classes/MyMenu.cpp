#include "MyMenu.h"

MyMenu::MyMenu()
{

}

void MyMenu::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 10, true);
}
