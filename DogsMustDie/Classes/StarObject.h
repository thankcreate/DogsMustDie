#ifndef StarObject_h__
#define StarObject_h__

#include "GameObject.h"

// StarObject��ָ�ܹ���ս�Ķ���
// Ŀǰ��Ϊ����:
// 1. ����
// 2. ���ɲ���
class StarObject : public  GameObject
{
public:
	StarObject();
	CREATE_FUNC(StarObject);
	bool init();
};




#endif // StarObject_h__

