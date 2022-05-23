#pragma once
#include "GameObject.h"
#include "Item_Cash.h"

#define FIRERING_NUMBER 4 //�����ϳ��� �Ҳɸ� ����
#define FIRERING_ANIM_DELTATICK 0.2f //ū�Ҳɸ��ִϸ��̼� ���� ��(�����Ҳ��� �ִϸ��̼��̾���)
#define IMAGE_TERM 25 //���� �̷�� 2���� �̹��� ������ ��
#define FIRERING_DEFAULT_SPEED 300
#define LITTLE_FIRERING_DEFAULT_SPEED 500
#define RING_TERM 500 //���� �������� ����
#define COLLIDERBOX_HEIGHT 30 //�浹üũ�ڽ��� ����
#define COLLIDERBOX_SCOREUPBOX_TERM 40 //�浹üũ�ڽ��� ���ھ��üũ�ڽ��� �Ÿ�����

enum FIRERING_TYPE
{
	FIRERING_TYPE_START,
	FIRERING_TYPE_LL = 0,
	FIRERING_TYPE_LR,
	FIRERING_TYPE_L1,
	FIRERING_TYPE_R1,
	FIRERING_TYPE_L2,
	FIRERING_TYPE_R2,
	FIRERING_TYPE_END
};

class FireRing : public GameObject
{
private : 
	FIRERING_TYPE Image[2]; //��̹����� ������
	float m_fMemoDeltaTime; //���� ��ŸŸ���� ���.
	float m_fDistance; //�÷��̾�Ÿ�
	float m_fPlayerSpeed; //�÷��̾� ���ǵ�
	Item_Cash ItemCash;
	POINT FR_Point[FIRERING_NUMBER]; 
	RECT FR_ColliderBox[FIRERING_NUMBER];
	RECT FR_SCOREUPBOX[FIRERING_NUMBER];
	float m_fFireRingSpeed[FIRERING_NUMBER];
	bool m_bPlayerPassFlag[FIRERING_NUMBER]; //�÷��̾ �н��ϸ� true �ƴϸ� false �������� �ʱ�ȭ
	bool m_bFireRingLoop; //true ���Ǹ� ������ ������Ų��
	bool m_bCashFlag; //ĳ���������� ������ Ʈ�� �ƴϸ� false
	RECT ColliderArea; //�÷��̾� �ڽ��� ��ֹ� �ݸ����� �ε������������Ǵ� ����

	int m_iImageX; //ū�Ҳɸ�����̹�����x ������
	int m_iImageY; //ū�Ҳɸ�����̹�����y ������
	int m_iImageXL; //�����Ҳɸ�����̹�����x ������
	int m_iImageYL; //�����Ҳɸ�����̹�����y ������

public:
	FireRing();
	~FireRing();
	void SetPosition();
	void SetSpeed();
	void SetColliderBox();
	void SetScoreUpBox();
	bool ColliderCheck(RECT PlayerColliderbox);
	bool ScoreUpCheck(RECT PlayerColliderbox);
	void Update(float DeltaTime);
	void Draw(HDC hdc);
	void ResetPlayPassFlag();
	void Clear();
	void SetDistance(float NewDistance);
	void SetPlayerSpeed(float NewSpeed);
	inline bool GetCashFlag()
	{
		return m_bCashFlag;
	}
};

