#include "Player.h"
//#include "GameManager.h"

Player::Player() : GameObject(IMAGE::IMAGE_PLAYER1, PLAYER_STATE::PLAYER_STATE_END)
{
	ResetState();
}

Player::~Player()
{
	
}

void Player::Update(float DeltaTime)
{

	if (States == PLAYER_STATE::PLAYER_STATE_JUMP)
	{
		if (m_bJumpState == true)
		{
			m_iy -= 700 * DeltaTime;
		}
		else m_iy += 700 * DeltaTime;

		if (m_iJumpMaxHeight >= m_iy)
		{
			m_iy <= m_iJumpMaxHeight;
			m_bJumpState = false;
		}
		if (m_iPlayerOriginal_YLocation <= m_iy)
		{
			m_iy = m_iPlayerOriginal_YLocation;
			States = PLAYER_STATE_IDLE;
			m_bAccelation = false;
			LastInputKey == KEY_INPUT::KEY_INPUT_DEFAULT;
			m_bCanMove = true;
		}
	}

	if (m_bCanMove == true)
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			States = PLAYER_STATE_RUN;
			m_bAccelation = true;
			LastInputKey = KEY_INPUT::KEY_INPUT_RIGHT;
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			States = PLAYER_STATE_RUN;
			m_bAccelation = true;
			LastInputKey = KEY_INPUT::KEY_INPUT_LEFT;
		}
		else
		{
			m_bAccelation = false;
			LastInputKey = KEY_INPUT::KEY_INPUT_DEFAULT;
			States = PLAYER_STATE::PLAYER_STATE_IDLE;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			States = PLAYER_STATE_JUMP;
			m_bJumpState = true;
			m_bCanMove = false;
		}
	}

	if (m_bAccelation == true)
	{
		if (States != PLAYER_STATE::PLAYER_STATE_JUMP)
		{
			m_fMemoDeltaTime += DeltaTime;
			if (m_fMemoDeltaTime >= RUNANIMATION_DELTATICK)
			{
				States = PLAYER_STATE::PLAYER_STATE_IDLE;
				if(m_fMemoDeltaTime >= RUNANIMATION_DELTATICK*2)
				m_fMemoDeltaTime = 0;
			}
		}
	}

	if (m_fDistance >= SCREEN_FIX_DISTANCE)
	{
		//m_fSpeed = 300;

		if (LastInputKey == KEY_INPUT::KEY_INPUT_RIGHT)
			m_ix += (m_fSpeed * DeltaTime);
		else if(LastInputKey == KEY_INPUT::KEY_INPUT_LEFT)
			m_ix -= (m_fSpeed * DeltaTime);

	}
	else
		m_ix = 30;

	if (m_fDistance >= GOALDISTANCE - 50)
	{
		PlayerOnGoal(DeltaTime);
		m_bCanMove = false;
	}
	SetColliderBox();
}

void Player::Draw(HDC hdc)
{
	if (m_ix >= SCREEN_WIDTH * 0.85f)
	{
		m_ix = SCREEN_WIDTH * 0.85f;
		m_iy = SCREEN_HEIGHT * 0.5f;
	}
	m_BitMap[States].Draw(hdc, m_ix, m_iy);

#ifdef _Debug
	GameManager::GetInstance()->DebugRectangle(PlayerColliderbox);
#endif // _Debug

}


void Player::PlayerGetDammaged()
{
	States = PLAYER_STATE_DEAD;
	m_bCanMove = false;
}

void Player::ResetState()
{
	m_ix = 30;
	m_iy = SCREEN_HEIGHT * 0.6f;
	m_fSpeed = PLAYERSPEED;
	m_bJumpState = false;
	m_bAccelation = false;
	m_bCanMove = true;
	States = PLAYER_STATE::PLAYER_STATE_IDLE;
	LastInputKey = KEY_INPUT::KEY_INPUT_DEFAULT;
	m_fMemoDeltaTime = 0;
	m_fMemoDeltaTIme2 = 0;
	SetColliderBox();
	m_fDistance = 0;
	m_iPlayerOriginal_YLocation = m_iy;
	m_iJumpMaxHeight = m_iy - 100;
	m_bFinishFlag = false;
}

//void Player::InitialzationLastInputKey()
//{
//	LastInputKey = KEY_INPUT::KEY_INPUT_DEFAULT;
//}

void Player::SetColliderBox()
{
	PlayerImage_X_Size = m_BitMap[States].GetSize().cx;
	PlayerImage_Y_Size = m_BitMap[States].GetSize().cy;

	PlayerColliderbox.left = m_ix + PlayerImage_X_Size * COLLIDER_MAGNIFICATION_LT;
	PlayerColliderbox.top = m_iy + PlayerImage_Y_Size * COLLIDER_MAGNIFICATION_LT;
	PlayerColliderbox.right = PlayerColliderbox.left + PlayerImage_X_Size * COLLIDER_MAGNIFICATION_RB;
	PlayerColliderbox.bottom = PlayerColliderbox.top + PlayerImage_Y_Size * COLLIDER_MAGNIFICATION_RB;
}

void Player::SetDistance(float NewDistance)
{
	m_fDistance = NewDistance;
}

void Player::SetPlayerXPoint(int NewPoint)
{
	m_ix = NewPoint;
}

void Player::PlayerOnGoal(float DeltaTIme)
{
	States = PLAYER_STATE::PLAYER_STATE_GOAL1;
	m_bFinishFlag = true;
	m_fMemoDeltaTIme2 += DeltaTIme;
	if (m_fMemoDeltaTIme2 >= FINISH_ANIMATION_DELTATICK)
	{
		States = PLAYER_STATE_GOAL2;
		if (m_fMemoDeltaTIme2 >= FINISH_ANIMATION_DELTATICK * 2)
		{
			m_fMemoDeltaTIme2 = 0;
		}
	}
}

