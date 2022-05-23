#include "BackgroundManager.h"

BackgroundManager* BackgroundManager::m_this = NULL;

void BackgroundManager::Init()
{
	m_bg = new BackGround;
	m_fDistance = 0;
}

void BackgroundManager::Realese()
{
	delete m_bg;
}

void BackgroundManager::Update(float DeltaTIme, float NewPlusDistance)
{
	m_fDistance += NewPlusDistance * DeltaTIme;
	if (m_fDistance <= 0)m_fDistance = 0;
	if (m_fDistance >= GOALDISTANCE) m_fDistance = GOALDISTANCE;
	if (m_fDistance < SCREEN_FIX_DISTANCE)
	{
		m_bg->SetDistance(m_fDistance);
		m_bg->Update(DeltaTIme);
	}
	if (m_fDistance >= GOALDISTANCE)
		m_bg->FinishEffect(DeltaTIme);
}

void BackgroundManager::Draw(HDC hdc, float DeltaTime)
{
	m_bg->Draw(hdc);
}

void BackgroundManager::SetDistance(float NewDistance)
{
	m_fDistance = NewDistance;
}

