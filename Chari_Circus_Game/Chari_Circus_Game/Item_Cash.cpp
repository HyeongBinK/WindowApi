#include "Item_Cash.h"
#include "GameManager.h"

Item_Cash::Item_Cash() : GameObject(IMAGE::IMAGE_CASH , 1)
{
	m_iImage_X = (m_BitMap[IMAGE_CASH].GetSize().cx);
	m_iImage_Y = (m_BitMap[IMAGE_CASH].GetSize().cy);
	m_iy = SCREEN_HEIGHT * 0.35f;
}

Item_Cash::~Item_Cash()
{
}

void Item_Cash::Update(float DeltaTime)
{
	
}

void Item_Cash::Draw(HDC hdc)
{
	m_BitMap->Draw(hdc, m_iXPoint, m_iy);
}

void Item_Cash::GetXPoint(int NewX)
{
	m_iXPoint = NewX + X_CORRECT_POINT;
}