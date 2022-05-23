#pragma once
#include "GameObject.h"

#define FIREOBSTACLE_ANIMATION_TICK 0.1f //�Ҳ��̱��̱۾ִϸ��̼� ƽŸ��
#define FIREOBSTACLE_NUMBER 16 //�ٴںҲ���ֹ� ����

enum FIREOBSTACLE_TYPE
{
	FIREOBSTACLE_TYPE_START,
	FIREOBSTACLE_TYPE1 =0,
	FIREOBSTACLE_TYPE2,
	FIREOBSTACLE_TYPE_END
};

class FireObstacle : public GameObject
{
private :
	FIREOBSTACLE_TYPE Image; //��̹����� ������
	float m_fMemoDeltaTime; //���� ��ŸŸ���� ���.
	float m_fDistance; //�÷��̾�Ÿ�
	int m_iPlayerPassFireNumber; //�÷��̾ ����� �Ҳ��Ǽ���
	POINT X_Locations[FIREOBSTACLE_NUMBER];
	RECT FO_ColliderBox[FIREOBSTACLE_NUMBER];
	RECT ColliderArea; //�÷��̾� �ڽ��� ��ֹ� �ݸ����� �ε������������Ǵ� ����
	int m_iImageX; //����̹�����x ������
	int m_iImageY; //����̹�����y ������
	int m_fFireObstacle_Term; //�Ҳ���ֹ������ǰŸ�

public:
	FireObstacle();
	~FireObstacle();
	void SetXLocations();
	void SetColliderBox();
	bool ColliderCheck(RECT PlayerColliderbox);
	void Update(float DeltaTime);
	void Draw(HDC hdc);
	void Clear();
	void SetDistance(float NewDistance);
	inline int GetPlayerPassFireNumber()
	{
		return m_iPlayerPassFireNumber;
	}
	int GetFireObstaclTerm()
	{
		return m_fFireObstacle_Term;
	}
};

