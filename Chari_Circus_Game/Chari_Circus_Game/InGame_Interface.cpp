#include "InGame_Interface.h"

InGame_Interface* InGame_Interface::m_this = NULL;

void InGame_Interface::Init()
{
	Clear();
	m_font = CreateFontA(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "�ü�");
}

void InGame_Interface::Release()
{
	DeleteObject(m_font);
}

void InGame_Interface::Clear()
{
	m_iPlayerLife = 3; //�÷��̾� ������ �÷��̾��������ܱ׸���������
	m_fDistance = 0; // �÷��̾� �Ÿ� 
	m_iPlayerScore = 0; //�÷��̾� ����(�⺻0, ��ֹ������� + 100, ���ָӴϾ����۸����� + 500)
	m_iPlayerBonnusScore = MAX_BONNUS_SCORE; // Ŭ����Ÿ�ӿ����� ���ʽ� ����(1������ �ð��� ����) 
	m_bFixFlag = false;
}

void InGame_Interface::EraseLifeIcon()
{
	if(m_iPlayerLife > 0)
	m_iPlayerLife--;
}

void InGame_Interface::Update(float DeltaTime, float NewDistance, int NewPlayerScore, int NewPlayerLife)
{
	if (m_bFixFlag == false)
	{
		if (NewDistance < SCREEN_FIX_DISTANCE)
			m_fDistance = NewDistance;
		m_iPlayerScore = NewPlayerScore;
		m_iPlayerLife = NewPlayerLife;
		if (m_fDistance < GOALDISTANCE)
			m_iPlayerBonnusScore -= MINUS_BONNUS_SCORE_TERM * DeltaTime;
	}
	else
		ShowResult(DeltaTime);
}

void InGame_Interface::Draw(HDC hdc)
{
	SelectObject(hdc, m_font);
	SetTextColor(hdc, RGB(255, 127, 0));
	SetBkMode(hdc, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�.

	string str;
	BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_INTERFACE1)->Draw(hdc, (SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_INTERFACE1)->GetSize().cx) * 0.5f, SCREEN_HEIGHT * 0.05f);
	str = "Score : ";
	TextOutA(hdc,SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, str.c_str(), str.length());
	str = to_string(m_iPlayerScore);
	TextOutA(hdc, SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f, str.c_str(), str.length());
	str = "BONNUS : ";
	TextOutA(hdc, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, str.c_str(), str.length());
	str = to_string(m_iPlayerBonnusScore);
	TextOutA(hdc, SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.1f, str.c_str(), str.length());
	str = "BONNUS : ";

	for (int i = 0; i < m_iPlayerLife; i++)
	{
		BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_INTERFACE2)->Draw(hdc, (SCREEN_WIDTH - BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_INTERFACE2)->GetSize().cx) * (0.85f + i*0.03f), SCREEN_HEIGHT * 0.13f); 
	}
	
	for (int i = 0; i < 10; i++)
	{
		BitMapManager::GetInstance()->GetImage(IMAGE::IMAGE_INTERFACE3)->Draw(hdc, (GOALDISTANCE * (i*0.1f)) - m_fDistance, SCREEN_HEIGHT * 0.8f);
		str = to_string(100 - i * 10);
		TextOutA(hdc, (GOALDISTANCE * (i * 0.1f)) - m_fDistance + 30, SCREEN_HEIGHT * 0.8f + 5, str.c_str(), str.length());
	}
}

void InGame_Interface::ShowResult(float DeltaTIme)
{
	if (m_iPlayerBonnusScore > 0)
	{
		m_iPlayerScore += (1000) * DeltaTIme;
		m_iPlayerBonnusScore -= (1000) * DeltaTIme;
	}
	else if (m_iPlayerBonnusScore < 0)
	{
		m_iPlayerScore += m_iPlayerBonnusScore;
		m_iPlayerBonnusScore = 0;
	}
}

void InGame_Interface::SetFixFlag()
{
	m_bFixFlag = true;
}
