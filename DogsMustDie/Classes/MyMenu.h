#ifndef MyMenu_h__
#define MyMenu_h__

#include "cocos2d.h"

using namespace cocos2d;

// ��Ϊ�ڵ���������Ҫ���κ��İ���������ѵ���������ȼ������
// ���Ե����㱾��İ���Ҳ�ᱻ����
// �������ר���ڵ������Menu
// ֮���Բ�ֱ��setHandlerPriority����Ϊ��ʱ����Ѱ��գ��ױ���
class MyMenu : public CCMenu
{
public:
	MyMenu();
	CREATE_FUNC(MyMenu);

	virtual void registerWithTouchDispatcher();

};

#endif // MyMenu_h__
