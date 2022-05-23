#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

void GameManager::Init(HWND hWnd)
{
	hdc = GetDC(hWnd);
	BitMapManager::GetInstance()->Init(hdc);
	Select_Interface::GetInstance()->Init();
	BackgroundManager::GetInstance()->Init();
	InGame_Interface::GetInstance()->Init();
	m_eGameState = GAME_STATE::GAME_STATE_SELECT_SCENE;
	GetWindowRect(hWnd, &windowRect);
	backDC = CreateCompatibleDC(hdc);
	character = new Player;
	FO = new FireObstacle;
	FR = new FireRing;
	G = new Goal;
	m_fFIreObstacle_Term = FO->GetFireObstaclTerm();
	Clear();
	//m_bDeadFlag = false;
}

void GameManager::Release(HWND hWnd)
{
	delete character;
	delete FO;
	delete FR;
	delete G;

	DeleteObject(backDC);
	ReleaseDC(hWnd, hdc);
}

void GameManager::Clear()
{
	 m_iScore = 0;
	 m_iTotalScore = 0;
	 m_iLife = 3;
	 m_fDistance = 0; 
	 m_fMemoDeltaTime = 0;
	 m_bIs_Dead = false; 
}

void GameManager::Update(float DeltaTime)
{
		switch (m_eGameState)
		{
		case GAME_STATE::GAME_STATE_SELECT_SCENE:
			Select_Interface::GetInstance()->Update(DeltaTime);
			if (Select_Interface::GetInstance()->GetSelectSceneFlag() == false)
			{
				m_eGameState = GAME_STATE::GAME_STATE_PLAY_SCENE;
				Select_Interface::GetInstance()->Clear();
			}
			break;
		case GAME_STATE::GAME_STATE_PLAY_SCENE:
		{
			if (m_bIs_Dead == false)
			{
				BackgroundManager::GetInstance()->Update(DeltaTime, character->GetSpeed());
				m_fDistance = BackgroundManager::GetInstance()->GetDistance();
				if (character->GetPlayerIsGoal() == true)
				{
					InGame_Interface::GetInstance()->SetFixFlag();
				}
				InGame_Interface::GetInstance()->Update(DeltaTime, BackgroundManager::GetInstance()->GetDistance(), m_iTotalScore, m_iLife);
				FO->SetDistance(m_fDistance);
				FR->SetPlayerSpeed(character->GetSpeed());
				FR->SetDistance(m_fDistance);
				FO->Update(DeltaTime);
				if(character->GetPlayerIsGoal() == false)
				FR->Update(DeltaTime);
				G->Update(DeltaTime);
				character->SetDistance(m_fDistance);
				character->Update(DeltaTime);

				if (FO->ColliderCheck(character->GetPlayerCollider()) == true)
				{
					character->PlayerGetDammaged();
					m_bIs_Dead = true;
				}

				if (FR->ColliderCheck(character->GetPlayerCollider()) == true)
				{
					character->PlayerGetDammaged();
					m_bIs_Dead = true;
				}

				if (FR->ScoreUpCheck(character->GetPlayerCollider()) == true)
				{
					if(FR->GetCashFlag() ==true)
						ScoreUp(500);
					else
					ScoreUp(100);
				}
				ScoreUpdate();
			}
			else
			{
				m_fMemoDeltaTime += DeltaTime;

				if (m_fMemoDeltaTime >= DEAD_ANIMATION_DELTATICK)
				{
					m_bIs_Dead = false;
					m_iLife--;
					if(m_fDistance < SCREEN_FIX_DISTANCE)
					BackgroundManager::GetInstance()->SetDistance((FO->GetPlayerPassFireNumber()*m_fFIreObstacle_Term) - m_fFIreObstacle_Term*0.5f);
					else if (m_fDistance >= SCREEN_FIX_DISTANCE)
					{
						BackgroundManager::GetInstance()->SetDistance(SCREEN_FIX_DISTANCE - 100);
					}
					character->ResetState();
					FR->SetPosition();
					m_fMemoDeltaTime = 0;
				}
			}

			if (m_iLife < 0 || (InGame_Interface::GetInstance()->IsEnd() == true))
			{
				BackgroundManager::GetInstance()->SetDistance(0);
				InGame_Interface::GetInstance()->Clear();
				FO->Clear();
				FR->Clear();
				character->ResetState();
				
				m_eGameState = GAME_STATE::GAME_STATE_SELECT_SCENE;
				Clear();
			}
		}
			break;
		case GAME_STATE::GAME_STATE_END_SCENE:
			break;
		default:
			return;
		}
}

void GameManager::Draw(float DeltaTime)
{
	backBitmap = CreateDIBSectionRe(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
	oldBack = (HBITMAP)SelectObject(backDC, backBitmap);


		switch (m_eGameState)
		{
		case GAME_STATE::GAME_STATE_SELECT_SCENE:
			Select_Interface::GetInstance()->Draw(backDC, DeltaTime);
			break;
		case GAME_STATE::GAME_STATE_PLAY_SCENE:
			BackgroundManager::GetInstance()->Draw(backDC, DeltaTime);
			InGame_Interface::GetInstance()->Draw(backDC);
			FO->Draw(backDC);
			FR->Draw(backDC);
			if(m_fDistance >= SCREEN_FIX_DISTANCE)
			G->Draw(backDC);
			character->Draw(backDC);

			break;
		case GAME_STATE::GAME_STATE_END_SCENE:
			break;
		default:
			return;
		}
	

	BitBlt(hdc, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, backDC, 0, 0, SRCCOPY);
	SelectObject(backDC, oldBack);
	DeleteObject(backBitmap);
}

void GameManager::LifeDown()
{
	m_iLife--;
}

void GameManager::ScoreUp(int Score)
{
	m_iScore += Score;
}

void GameManager::ScoreUpdate()
{
	m_iTotalScore = FO->GetPlayerPassFireNumber() * 100 + m_iScore;
}

#ifdef _Debug
void GameManager::DebugRectangle(RECT rect)
{
	Rectangle(backDC, rect.left, rect.top, rect.right, rect.bottom);
}
#endif // _Debug

