#pragma once
#include "GameObject.h"
#include "Item_Cash.h"

#define FIRERING_NUMBER 4 //패턴하나당 불꽃링 갯수
#define FIRERING_ANIM_DELTATICK 0.2f //큰불꽃링애니메이션 변경 텀(작은불꽃은 애니메이션이없음)
#define IMAGE_TERM 25 //링을 이루는 2개의 이미지 사이의 텀
#define FIRERING_DEFAULT_SPEED 300
#define LITTLE_FIRERING_DEFAULT_SPEED 500
#define RING_TERM 500 //링과 링사이의 간격
#define COLLIDERBOX_HEIGHT 30 //충돌체크박스의 높이
#define COLLIDERBOX_SCOREUPBOX_TERM 40 //충돌체크박스와 스코어업체크박스의 거리차이

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
	FIRERING_TYPE Image[2]; //어떤이미지가 나올지
	float m_fMemoDeltaTime; //기존 델타타임을 기록.
	float m_fDistance; //플레이어거리
	float m_fPlayerSpeed; //플레이어 스피드
	Item_Cash ItemCash;
	POINT FR_Point[FIRERING_NUMBER]; 
	RECT FR_ColliderBox[FIRERING_NUMBER];
	RECT FR_SCOREUPBOX[FIRERING_NUMBER];
	float m_fFireRingSpeed[FIRERING_NUMBER];
	bool m_bPlayerPassFlag[FIRERING_NUMBER]; //플레이어가 패스하면 true 아니면 false 링루프시 초기화
	bool m_bFireRingLoop; //true 가되면 링들을 루프시킨다
	bool m_bCashFlag; //캐쉬아이템을 먹으면 트루 아니면 false
	RECT ColliderArea; //플레이어 박스랑 장애물 콜리더가 부딛혔을떄생성되는 영역

	int m_iImageX; //큰불꽃링출력이미지의x 사이즈
	int m_iImageY; //큰불꽃링출력이미지의y 사이즈
	int m_iImageXL; //작은불꽃링출력이미지의x 사이즈
	int m_iImageYL; //작은불꽃링출력이미지의y 사이즈

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

