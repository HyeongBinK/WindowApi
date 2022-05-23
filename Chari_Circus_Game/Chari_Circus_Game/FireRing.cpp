#include "FireRing.h"
//#include "GameManager.h"


FireRing::FireRing() : GameObject(IMAGE::IMAGE_LITTLEFIRERING1, FIRERING_TYPE::FIRERING_TYPE_END)
{
	Image[0] = FIRERING_TYPE_L1;
	Image[1] = FIRERING_TYPE(Image[0] + 1);

	m_iImageX = (m_BitMap[FIRERING_TYPE_L1].GetSize().cx);
	m_iImageY = (m_BitMap[FIRERING_TYPE_L1].GetSize().cy);
	m_iImageXL = (m_BitMap[FIRERING_TYPE_LL].GetSize().cx);
	m_iImageYL = (m_BitMap[FIRERING_TYPE_LL].GetSize().cy);

	Clear();
}

FireRing::~FireRing()

{
	
}

void FireRing::Update(float DeltaTime)
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		FR_Point[i].x -= (m_fFireRingSpeed[i] + m_fPlayerSpeed) * DeltaTime;
		if(i == 3)
		ItemCash.GetXPoint(FR_Point[i].x);
	}
	SetColliderBox();
	SetScoreUpBox();
	m_bFireRingLoop = true;
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		if (FR_Point[i].x > -50)
			m_bFireRingLoop = false;
		
	}
	if (m_bFireRingLoop == true)
		SetPosition();
		

	m_fMemoDeltaTime += DeltaTime;
	if (m_fMemoDeltaTime >= FIRERING_ANIM_DELTATICK)
	{
		if (Image[0] == FIRERING_TYPE_L1)
		{
			Image[0] = FIRERING_TYPE_L2;
			Image[1] = FIRERING_TYPE_R2;
		}
		else
		{
			Image[0] = FIRERING_TYPE_L1;
			Image[1] = FIRERING_TYPE_R1;
		}

		m_fMemoDeltaTime = 0;
	}
}

void FireRing::Draw(HDC hdc)
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		if (i == 3)
		{
			m_BitMap[FIRERING_TYPE_LL].Draw(hdc, FR_Point[i].x, FR_Point[i].y);
			m_BitMap[FIRERING_TYPE_LR].Draw(hdc, FR_Point[i].x + IMAGE_TERM, FR_Point[i].y);
			if(m_bPlayerPassFlag[3] == false)
			ItemCash.Draw(hdc);
		}
		else
		{
			m_BitMap[Image[0]].Draw(hdc, FR_Point[i].x, FR_Point[i].y);
			m_BitMap[Image[1]].Draw(hdc, FR_Point[i].x + IMAGE_TERM, FR_Point[i].y);
		}

#ifdef _Debug
		GameManager::GetInstance()->DebugRectangle(FR_ColliderBox[i]);
#endif // _Debug

#ifdef _Debug
		GameManager::GetInstance()->DebugRectangle(FR_SCOREUPBOX[i]);
#endif // _Debug
	}
	

}

void FireRing::ResetPlayPassFlag()
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
		m_bPlayerPassFlag[i] = false;

	m_bCashFlag = false;
}

void FireRing::SetPosition()
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		FR_Point[i].x = SCREEN_WIDTH + RING_TERM*i;
		

		if (i == 3)
		{
			FR_Point[i].y = SCREEN_HEIGHT * 0.3f;
			ItemCash.GetXPoint(FR_Point[i].x);
		}
		else
			FR_Point[i].y = SCREEN_HEIGHT * 0.35f;
		
	}
	ResetPlayPassFlag();
}

void FireRing::SetSpeed()
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		if (i == 3)
			m_fFireRingSpeed[i] = LITTLE_FIRERING_DEFAULT_SPEED;
		else
			m_fFireRingSpeed[i] = FIRERING_DEFAULT_SPEED;
	}
}

void FireRing::SetColliderBox()
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		if (i==3)
		{
			FR_ColliderBox[i].left = FR_Point[i].x + m_iImageXL * 0.5f;
			FR_ColliderBox[i].top = FR_Point[i].y + m_iImageYL* 0.8f;
			FR_ColliderBox[i].right = FR_ColliderBox[i].left + m_iImageXL;
			FR_ColliderBox[i].bottom = FR_ColliderBox[i].top + COLLIDERBOX_HEIGHT;
		}
		else
		{
			FR_ColliderBox[i].left = FR_Point[i].x + m_iImageX * 0.5f;
			FR_ColliderBox[i].top = FR_Point[i].y + m_iImageY * 0.8f;
			FR_ColliderBox[i].right = FR_ColliderBox[i].left + m_iImageX;
			FR_ColliderBox[i].bottom = FR_ColliderBox[i].top + COLLIDERBOX_HEIGHT;
		}
	}
}

void FireRing::SetScoreUpBox()
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		FR_SCOREUPBOX[i] = FR_ColliderBox[i];
		FR_SCOREUPBOX[i].top -= COLLIDERBOX_SCOREUPBOX_TERM;
		FR_SCOREUPBOX[i].bottom = FR_SCOREUPBOX[i].top + COLLIDERBOX_HEIGHT;
	}
}

bool FireRing::ColliderCheck(RECT PlayerColliderbox)
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		//if (IntersectRect(&ColliderArea, &PlayerColliderbox, &FR_ColliderBox[i]))
			//return true;

	}
	return false;
}

bool FireRing::ScoreUpCheck(RECT PlayerColliderbox)
{
	for (int i = 0; i < FIRERING_NUMBER; i++)
	{
		if (IntersectRect(&ColliderArea, &PlayerColliderbox, &FR_SCOREUPBOX[i]))
		{
			if (m_bPlayerPassFlag[i] == false)
			{
				if(i == 3)
					m_bCashFlag = true;

				m_bPlayerPassFlag[i] = true;
				return true;
			}
		}
	}
	return false;
}

void FireRing::Clear()
{
	m_fMemoDeltaTime = 0;
	m_fDistance = 0;
	m_fPlayerSpeed = 0;
	m_bFireRingLoop = false;
	m_bCashFlag = false;
	SetPosition();
	SetSpeed();
	SetColliderBox();
	SetScoreUpBox();
	ResetPlayPassFlag();
}


void FireRing::SetDistance(float NewDistance)
{
	m_fDistance = NewDistance;
}

void FireRing::SetPlayerSpeed(float NewSpeed)
{
	m_fPlayerSpeed = NewSpeed;
	if (m_fDistance >= SCREEN_FIX_DISTANCE)
		m_fPlayerSpeed = 0;
}
