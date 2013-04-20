#ifndef StarObject_h__
#define StarObject_h__

#include "GameObject.h"

// StarObject��ָ�ܹ���ս�Ķ���
// Ŀǰ��Ϊ����:
// 1. ����
// 2. ���ɲ���

// ���ǵ�ɾ�����̱Ƚ�����
// ���������m_body��������Ϊ���ǿ����ڱ�һ���õ��ֺ�
// ��һ������ȥ�����ǵ�;��
// �������ǽ���ֻ������visible����ʾɾ��
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

