#include "FireObstacle.h"
//#include "GameManager.h"


FireObstacle::FireObstacle(): GameObject(IMAGE::IMAGE_FIREOBSTACLE1, FIREOBSTACLE_TYPE::FIREOBSTACLE_TYPE_END),
Image(FIREOBSTACLE_TYPE2)
{
	Clear();
	m_iImageX = (m_BitMap[Image].GetSize().cx);
	m_iImageY = (m_BitMap[Image].GetSize().cy);
	m_fFireObstacle_Term = GOALDISTANCE / FIREOBSTACLE_NUMBER;
}

FireObstacle::~FireObstacle()
{
	
}

void FireObstacle::SetXLocations()
{
	for (int i = 0; i < FIREOBSTACLE_NUMBER; i++)
	{
		X_Locations[i].x = GOALDISTANCE * (i * float(1.0f / FIREOBSTACLE_NUMBER));
	}
}

void FireObstacle::SetColliderBox()
{
	for (int i = 0; i < FIREOBSTACLE_NUMBER; i++)
	{
		FO_ColliderBox[i].left = X_Locations[i].x + m_iImageX*COLLIDER_MAGNIFICATION_LT - m_fDistance;
		FO_ColliderBox[i].top = m_iy + m_iImageY * COLLIDER_MAGNIFICATION_LT;
		FO_ColliderBox[i].right = FO_ColliderBox[i].left + m_iImageX * COLLIDER_MAGNIFICATION_RB;
		FO_ColliderBox[i].bottom = FO_ColliderBox[i].top + m_iImageY * COLLIDER_MAGNIFICATION_RB;
	}
}

bool FireObstacle::ColliderCheck(RECT PlayerColliderbox)
{
	for (int i = 1; i < FIREOBSTACLE_NUMBER; i++)
	{
		if (IntersectRect(&ColliderArea, &PlayerColliderbox, &FO_ColliderBox[i]))
			return true;
		
	}

	/*if (IntersectRect(&ColliderArea, &PlayerColliderbox, &FO_ColliderBox[i]))
	{
	return true;
	}*/
	return false;
}

void FireObstacle::Update(float DeltaTIme)
{
	SetColliderBox();
	if (m_fDistance >= X_Locations[m_iPlayerPassFireNumber + 1].x)
	{
		if(m_iPlayerPassFireNumber + 1 < FIREOBSTACLE_NUMBER)
		m_iPlayerPassFireNumber++;
	}
	m_fMemoDeltaTime += DeltaTIme;

	if (m_fMemoDeltaTime >= FIREOBSTACLE_ANIMATION_TICK)
	{
		if (Image == FIREOBSTACLE_TYPE2)
			Image = FIREOBSTACLE_TYPE1;
		else if (Image == FIREOBSTACLE_TYPE1)
			Image = FIREOBSTACLE_TYPE2;

		m_fMemoDeltaTime = 0;
	}
}

void FireObstacle::Draw(HDC hdc)
{
	for (int i = 1; i < FIREOBSTACLE_NUMBER; i++)
	{
		float x = X_Locations[i].x - m_fDistance;
		if(x >= -m_iImageX && x <= SCREEN_WIDTH)
		m_BitMap[Image].Draw(hdc, x, m_iy);

#ifdef _Debug
		GameManager::GetInstance()->DebugRectangle(FO_ColliderBox[i]);
#endif // _Debug
	}
}

void FireObstacle::Clear()
{
	m_iy = SCREEN_HEIGHT * 0.64f;
	m_fMemoDeltaTime = 0;
	m_fDistance = 0;
	SetXLocations();
	SetColliderBox();
	m_iPlayerPassFireNumber = 0;
}

void FireObstacle::SetDistance(float NewDistance)
{
	if (NewDistance < SCREEN_FIX_DISTANCE)
	{
		m_fDistance = NewDistance;
	}
}
