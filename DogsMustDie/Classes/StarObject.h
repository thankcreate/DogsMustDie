#ifndef StarObject_h__
#define StarObject_h__

#include "GameObject.h"

// StarObject是指能够作战的对象
// 目前分为三种:
// 1. 星球
// 2. 外派部队
class StarObject : public  GameObject
{
public:
	StarObject();
	CREATE_FUNC(StarObject);
	bool init();
};




#endif // StarObject_h__

