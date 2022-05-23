#include "Select_Interface.h"

Select_Interface* Select_Interface::m_this = NULL;

void Select_Interface::Init()
{
	SetStarLocation((SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE1)->GetSize().cx) * 0.5f, SCREEN_HEIGHT * 0.2f);
	m_iCursor = 0;
	CursorLocation.x = SCREEN_WIDTH * 0.2f;
	CursorLocation.y = SCREEN_HEIGHT * 0.5f + 50;
	m_bSelectScene = true;
	m_iStarValue = 0;
	DeltaTimeCount = 0;
}

void Select_Interface::Release()
{
}

void Select_Interface::Clear()
{
	m_iCursor = 0;
	CursorLocation.x = SCREEN_WIDTH * 0.2f;
	CursorLocation.y = SCREEN_HEIGHT * 0.5f + 50;
	m_bSelectScene = true;
	m_iStarValue = 0;
	DeltaTimeCount = 0;
}

void Select_Interface::SetStarLocation(int x, int y)
{
	for (int i = 0; i < GAROSTAR; i++)
	{
		StarLocation[i].x = x + i * BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->GetSize().cx;
		StarLocation[i].y = y - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->GetSize().cy;
		StarLocation[i + GAROSTAR].x = x + i * BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->GetSize().cx;
		StarLocation[i + GAROSTAR].y = y + BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->GetSize().cy * SEROSTAR;
	}

	for (int i = (GAROSTAR * 2); i < (GAROSTAR * 2) + SEROSTAR; i++)
	{
		StarLocation[i].y = y + (i - (GAROSTAR * 2)) * BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->GetSize().cy;
		StarLocation[i].x = x - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->GetSize().cx;
		StarLocation[i + SEROSTAR].y = y + (i- (GAROSTAR * 2) ) * BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->GetSize().cy;
		StarLocation[i + SEROSTAR].x = x + BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->GetSize().cx * GAROSTAR;
	}



}

void Select_Interface::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_UP))
	{
		CursorLocation.y -= CURSOR_Y_MOVELENGTH;
		m_iCursor--;
		if (0 >= m_iCursor)
		{
			m_iCursor = 0;
			CursorLocation.y = SCREEN_HEIGHT * 0.5f + 50;
		}
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		CursorLocation.y += CURSOR_Y_MOVELENGTH;
		m_iCursor++;
		if (3 <= m_iCursor)
		{
			m_iCursor = 3;
			CursorLocation.y = SCREEN_HEIGHT * 0.5f + 50 + 3 * CURSOR_Y_MOVELENGTH;
		}
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		m_bSelectScene = false;
	}

}

void Select_Interface::Draw(HDC hdc, float DeltaTime)
{
	DeltaTimeCount++;
	//BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_BLACK)->Draw(hdc, 0, 0);
	BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE1)->Draw(hdc, (SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE1)->GetSize().cx) * 0.5f, SCREEN_HEIGHT * 0.2f);
	BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU1)->Draw(hdc, (SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU1)->GetSize().cx) * 0.5f, SCREEN_HEIGHT * 0.4f);
	BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU2)->Draw(hdc, (SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU2)->GetSize().cx) * 0.5f, SCREEN_HEIGHT * 0.5f + 50);
	BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU3)->Draw(hdc, (SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU3)->GetSize().cx) * 0.5f, SCREEN_HEIGHT * 0.5f + 50 + CURSOR_Y_MOVELENGTH);
	BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU4)->Draw(hdc, (SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU4)->GetSize().cx) * 0.5f, SCREEN_HEIGHT * 0.5f + 50 + 2 * CURSOR_Y_MOVELENGTH);
	BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU5)->Draw(hdc, (SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_MENU5)->GetSize().cx) * 0.5f, SCREEN_HEIGHT * 0.5f + 50 + 3 * CURSOR_Y_MOVELENGTH);

	BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_POINT)->Draw(hdc, CursorLocation.x, CursorLocation.y);


	for (int i = 0; i < (SEROSTAR + GAROSTAR) * 2; i++)
	{
		switch (m_iStarValue)
		{
		case 0:
			BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE2)->Draw(hdc, StarLocation[i].x, StarLocation[i].y);
			break;
		case 1:
			BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE3)->Draw(hdc, StarLocation[i].x, StarLocation[i].y);
			break;
		case 2:
			BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_TITLE4)->Draw(hdc, StarLocation[i].x, StarLocation[i].y);
			break;
		}
		m_iStarValue++;
		if (m_iStarValue >= 3)
			m_iStarValue = 0;
	}
}
