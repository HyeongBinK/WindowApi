#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

void GameManager::DrawStartButton()
{
	//DrawBackGroundImage();
	string StartText = "START";
	SetTextColor(hdc, RGB(255, 0, 0)); // 문자 색을 붉은색으로 변경.
	SetBkColor(hdc, RGB(0, 0, 0));     // 문자의 배경색을 검은색으로 변경
	DrawTextA(hdc, StartText.c_str(), -1, &StartButton, DT_CENTER | DT_WORDBREAK);
}

void GameManager::StartButtonColliderCheck(const POINT& point, HWND hWnd)
{
	if (PtInRect(&StartButton, point))
	{
		InvalidateRect(hWnd, NULL, false);
		m_iCurrentGamePage++;
		//InvalidateRect(hWnd, NULL, false);
	}
}

void GameManager::DrawBackGroundImage()
{
	BitMap* BackImage;
	RECT BackImageRect;
	BackImage = BitMapManager::GetInstance()->GetImage(IMAGE_END);
	BackImage->Draw(hdc, 0, 0, 700, 900);
}

void GameManager::MakeRandomCard()
{
	while (1)
	{
		int RandomImage = (rand() % IMAGE_BLACK);
		int Count = 0;

		for (auto Image : ImageList)
		{
			if (Image == RandomImage)
				Count++;
		}
		if (Count < 2)
		{
			IMAGE NewImage = static_cast<IMAGE>(RandomImage);
			ImageList.push_back(NewImage);
		}
				
		
		if (ImageList.size() >= CARDTOTALNUMBER)
			return;
	}
}

void GameManager::CollocateCard()
{
	int i = 0;
	for (int x = 0; x < 5; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			Card NewCard;
			NewCard.Init(ImageList[i++], 5 + x * 140, 10 + y * 180);
			//NewCard.Init(IMAGE_DOG, 10 + x * (145 + 10), 10 + y * (235 + 10));
			CardList.push_back(NewCard);
		}
	}
}

void GameManager::DrawAllCard()
{
	//DrawBackGroundImage();
	for (auto card : CardList)
	{
		card.DrawV2(hdc, 120, 180);
	}
}

void GameManager::ColliderCheck(const POINT& point, HWND hWnd)
{
	if (FRONTCARDNUMBER_DEFAULT == m_iMemoFrontCardNumber[1])
	{
		for (int index = 0; CardList.size() > index; index++)
		{
			if (CardList[index].GetCardState() != CARD_FRONT &&
				CardList[index].ColliderCheck(point))
			{
				InvalidateRect(hWnd, NULL, false);

				if (m_iMemoFrontCardNumber[0] == FRONTCARDNUMBER_DEFAULT)
					m_iMemoFrontCardNumber[0] = index;
				else
					m_iMemoFrontCardNumber[1] = index;

				break;
			}
		}
	}
}

void GameManager::CheckMatchUp(HWND hWnd)
{
	if (m_iMemoFrontCardNumber[0] != FRONTCARDNUMBER_DEFAULT &&
		m_iMemoFrontCardNumber[1] != FRONTCARDNUMBER_DEFAULT)
	{
		m_nTimeCheck++;
		if (10 <= m_nTimeCheck)
		{
			m_nTimeCheck = 0;

			if (ImageList[m_iMemoFrontCardNumber[0]] != ImageList[m_iMemoFrontCardNumber[1]])
			{
				CardList[m_iMemoFrontCardNumber[0]].SetCardREAR();
				CardList[m_iMemoFrontCardNumber[1]].SetCardREAR();


				InvalidateRect(hWnd, NULL, false);
			}

			m_iMemoFrontCardNumber[0] = FRONTCARDNUMBER_DEFAULT;
			m_iMemoFrontCardNumber[1] = FRONTCARDNUMBER_DEFAULT;
		}
	}
}

void GameManager::GameTimerUp()
{
	if (m_iCurrentGamePage == GAMEPAGE_ePLAYPAGE)
	{
		if (GameFinishCheck() != true)
		{
			m_iGameTimer++;
			ShowTimer();
		}
		else
		{
			Sleep(1000);
			ShowFinish();
		}
	}
}

bool GameManager::GameFinishCheck()
{
	for (auto card : CardList)
	{
		if (card.GetCardState() != CARD_FRONT)
			return false;	
	}
	return true;
}

void GameManager::ShowTimer()
{
	string TimerText = "Time : ";
	TimerText.append(std::to_string(m_iGameTimer));
	if (!TimerText.empty())
	{
		SetTextColor(hdc, RGB(255, 0, 0)); // 문자 색을 붉은색으로 변경.
		SetBkColor(hdc, RGB(0, 0, 0));     // 문자의 배경색을 검은색으로 변경
		DrawTextA(hdc, TimerText.c_str(), -1, &TIMERBOX, DT_CENTER | DT_WORDBREAK);
	}
}

void GameManager::ShowFinish()
{
	auto font = CreateFontA(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, "궁서");
	auto oldFont = SelectObject(hdc, font);

	string ClearText = "Game Clear";
	SetTextColor(hdc, RGB(255, 0, 0)); // 문자 색을 붉은색으로 변경.
	SetBkColor(hdc, RGB(0, 0, 0));     // 문자의 배경색을 검은색으로 변경

	DrawTextA(hdc, ClearText.c_str(), -1, &CLEARBOX, DT_CENTER | DT_WORDBREAK);
	SelectObject(hdc, oldFont);
	DeleteObject(font);
	DeleteObject(oldFont);
}

void GameManager::Init(HWND hWnd)
{
	hdc = GetDC(hWnd);
	BitMapManager::GetInstance()->Init(hdc);

}

void GameManager::Release(HWND hWnd)
{
	ReleaseDC(hWnd, hdc);
}
