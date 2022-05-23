#pragma once
#include "GameObject.h"

#define PLAYERSPEED 700
#define RUNANIMATION_DELTATICK 0.05f
#define FINISH_ANIMATION_DELTATICK 0.2f

enum KEY_INPUT
{
	KEY_INPUT_START,
	KEY_INPUT_DEFAULT = 0, //아무입력없을때
	KEY_INPUT_RIGHT,
	KEY_INPUT_LEFT,
	KEY_INPUT_END,
};

enum PLAYER_STATE
{
	PLAYER_STATE_START,
	PLAYER_STATE_IDLE = 0,
	PLAYER_STATE_RUN,
	PLAYER_STATE_JUMP,
	PLAYER_STATE_GOAL1,
	PLAYER_STATE_GOAL2,
	PLAYER_STATE_DEAD,
	PLAYER_STATE_END,
};

class Player : public GameObject
{
private :
	float m_fSpeed; //스피드수치
	int m_iJumpMaxHeight; //점프최대도달높이
	int m_iPlayerOriginal_YLocation; //맨처음의 y좌표
	float m_fDistance; //플레이어의 x이동길이
	bool m_bCanMove; //false = 죽거나, 점프, 골인하여 조작이막힌 상태, true = 평상시 생존상태
	bool m_bJumpState; //false = 평상시 , true = 점프중
	bool m_bAccelation; //이동중 점프시 가속도 시스템 , false : 없음 true : 있음
	bool m_bFinishFlag; //골인시 불꽃링들 멈추기위한 용도 false : 골못함 true : 골인함
	float m_fMemoDeltaTime; //델타타임과의 시간차에따라 이동애니메이션 재어하기위해 사용
	float m_fMemoDeltaTIme2; //피니쉬 애니메이션 관리를 위한 용도
	float PlayerImage_X_Size; //플레이어이미지의 x 사이즈(충돌박스에 쓰임)
	float PlayerImage_Y_Size; //플레이어이미지의 y사이즈(충돌박스에 쓰임)
	RECT PlayerColliderbox; //플레이어캐릭터의 충돌체크박스
	KEY_INPUT LastInputKey; //마지막에 입력된 키
	PLAYER_STATE States;

protected :
public :
	
	Player();
	~Player();

	void Update(float DeltaTime);
	void Draw(HDC hdc);
	void PlayerGetDammaged();
	void PlayerOnGoal(float DeltaTIme);
	void ResetState(); //플레이어가 목숨을 잃거나 다소모하였을떄 초기상태로 되돌리는 용도
	//void InitialzationLastInputKey();
	void SetColliderBox(); 
	void SetDistance(float NewDistance);
	void SetPlayerXPoint(int NewPoint);
	float GetSpeed()
	{
		switch (LastInputKey)
		{
		case KEY_INPUT::KEY_INPUT_LEFT:
			return -m_fSpeed;
		case KEY_INPUT::KEY_INPUT_RIGHT:
			return m_fSpeed;
		}

		return 0;
	}
	inline RECT GetPlayerCollider()
	{
		return PlayerColliderbox;
	}
	inline bool GetPlayerIsGoal()
	{
		return m_bFinishFlag;
	}


};

