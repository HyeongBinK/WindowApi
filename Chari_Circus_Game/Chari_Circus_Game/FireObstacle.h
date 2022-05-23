#pragma once
#include "GameObject.h"

#define FIREOBSTACLE_ANIMATION_TICK 0.1f //불꽃이글이글애니메이션 틱타임
#define FIREOBSTACLE_NUMBER 16 //바닥불꽃장애물 갯수

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
	FIREOBSTACLE_TYPE Image; //어떤이미지가 나올지
	float m_fMemoDeltaTime; //기존 델타타임을 기록.
	float m_fDistance; //플레이어거리
	int m_iPlayerPassFireNumber; //플레이어가 통과한 불꽃의숫자
	POINT X_Locations[FIREOBSTACLE_NUMBER];
	RECT FO_ColliderBox[FIREOBSTACLE_NUMBER];
	RECT ColliderArea; //플레이어 박스랑 장애물 콜리더가 부딛혔을떄생성되는 영역
	int m_iImageX; //출력이미지의x 사이즈
	int m_iImageY; //출력이미지의y 사이즈
	int m_fFireObstacle_Term; //불꽃장애물사이의거리

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

