#include "Goal.h"

Goal::Goal() : GameObject(IMAGE::IMAGE_GOAL, 1)
{
	m_ix = SCREEN_WIDTH * 0.85f;
	m_iy = SCREEN_HEIGHT * 0.64f;
}

Goal::~Goal()
{
	
}

void Goal::Update(float DeltaTIme)
{
}

void Goal::Draw(HDC hdc)
{
	m_BitMap->Draw(hdc, m_ix, m_iy);
}
