#pragma once
#include "BaseHeader.h"
#include "Card.h"

#define CARDTOTALNUMBER 20
#define FRONTCARDNUMBER_DEFAULT -1
#define GAMETOTALPAGE 2

enum GAMEPAGE
{
	GAMEPAGE_eSTARTPAGE = 0,
	GAMEPAGE_ePLAYPAGE,
	//GAMEPAGE_eRESULTPAGE
};

class GameManager
{
private :
	static GameManager* m_hThis;

	HDC hdc;
	vector<IMAGE> ImageList;
	vector<Card> CardList;
	int m_iGameTimer =0;
	int m_iMemoFrontCardNumber[2] = { FRONTCARDNUMBER_DEFAULT, FRONTCARDNUMBER_DEFAULT };
	int m_nTimeCheck = 0;
	int m_iCurrentGamePage = 0;
public :
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}

	RECT StartButton = {300, 350, 400, 450};
	RECT TIMERBOX = { 300, 800, 400, 850 };
	RECT CLEARBOX = { 100, 400, 600, 600 };
	void DrawStartButton(); //게임시작시 시작버튼그리는 함수
	void StartButtonColliderCheck(const POINT& point, HWND hWnd); //게임시작버튼 마우스클릭체크 
	void DrawBackGroundImage(); //백그라운드 이미지 그리기
	void MakeRandomCard();//랜덤카드이미지생성(2장이상일시 안되게끔)
	void CollocateCard(); //카드배치
	void DrawAllCard(); //모든 카드 그리기(업데이트)
	void ColliderCheck(const POINT& point, HWND hWnd); //카트클릭체크
	void CheckMatchUp(HWND hWnd);
	void GameTimerUp();
	bool GameFinishCheck();
	void ShowTimer(); 
	void ShowFinish();
	void Init(HWND hWnd);
	void Release(HWND hWnd);
	inline int GetCurrentPage()
	{
		return m_iCurrentGamePage;
	}
};

