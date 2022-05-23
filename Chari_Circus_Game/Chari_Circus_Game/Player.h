#pragma once
#include "GameObject.h"

#define PLAYERSPEED 700
#define RUNANIMATION_DELTATICK 0.05f
#define FINISH_ANIMATION_DELTATICK 0.2f

enum KEY_INPUT
{
	KEY_INPUT_START,
	KEY_INPUT_DEFAULT = 0, //�ƹ��Է¾�����
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
	float m_fSpeed; //���ǵ��ġ
	int m_iJumpMaxHeight; //�����ִ뵵�޳���
	int m_iPlayerOriginal_YLocation; //��ó���� y��ǥ
	float m_fDistance; //�÷��̾��� x�̵�����
	bool m_bCanMove; //false = �װų�, ����, �����Ͽ� �����̸��� ����, true = ���� ��������
	bool m_bJumpState; //false = ���� , true = ������
	bool m_bAccelation; //�̵��� ������ ���ӵ� �ý��� , false : ���� true : ����
	bool m_bFinishFlag; //���ν� �Ҳɸ��� ���߱����� �뵵 false : ����� true : ������
	float m_fMemoDeltaTime; //��ŸŸ�Ӱ��� �ð��������� �̵��ִϸ��̼� ����ϱ����� ���
	float m_fMemoDeltaTIme2; //�ǴϽ� �ִϸ��̼� ������ ���� �뵵
	float PlayerImage_X_Size; //�÷��̾��̹����� x ������(�浹�ڽ��� ����)
	float PlayerImage_Y_Size; //�÷��̾��̹����� y������(�浹�ڽ��� ����)
	RECT PlayerColliderbox; //�÷��̾�ĳ������ �浹üũ�ڽ�
	KEY_INPUT LastInputKey; //�������� �Էµ� Ű
	PLAYER_STATE States;

protected :
public :
	
	Player();
	~Player();

	void Update(float DeltaTime);
	void Draw(HDC hdc);
	void PlayerGetDammaged();
	void PlayerOnGoal(float DeltaTIme);
	void ResetState(); //�÷��̾ ����� �Ұų� �ټҸ��Ͽ����� �ʱ���·� �ǵ����� �뵵
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

