#ifndef StarObject_h__
#define StarObject_h__

#include "GameObject.h"

// StarObject是指能够作战的对象
// 目前分为三种:
// 1. 星球
// 2. 外派部队

// 星星的删除过程比较特殊
// 它并不会把m_body除掉，因为星星可能在被一方拿到手后
// 另一方还在去往星星的途中
// 所以星星仅仅只是设置visible来表示删除
class StarObject : public  GameObject
{
public:
	StarObject();
	CREATE_FUNC(StarObject);
	bool init();

	CCPoint getBox2dObjectSize();
	

	void setHasBeenGotBySomeOne(bool isGot);
	bool hasBeenGotBySomeOne() { return m_bHasBeenGotBySomeOne; }
	bool isDirty();

private:
	void destroyInNextUpdate();
	bool m_bHasBeenGotBySomeOne;
};




#endif // StarObject_h__

