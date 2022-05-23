#pragma once
//#include "BaseHeader.h"
#include "BitMapManager.h"
#include "Select_Interface.h"
#include "Player.h"
#include "BackgroundManager.h"
#include "FireObstacle.h"
#include "FireRing.h"
#include "Goal.h"
#include "InGame_Interface.h"
//#include "Item_Cash.h"

#define _Debug
#define SAFELENGTH 90
#define DEAD_ANIMATION_DELTATICK 0.5f

enum GAME_STATE
{
	GAME_STATE_START,
	GAME_STATE_SELECT_SCENE =0,
	GAME_STATE_PLAY_SCENE,
	GAME_STATE_END_SCENE,
	GAME_STATE_END
};


class GameManager
{
private :
	static GameManager* m_this;
	HDC hdc;
	GAME_STATE m_eGameState;
	RECT windowRect;
	HDC backDC;
	HBITMAP backBitmap;
	HBITMAP oldBack;
	int m_iScore; //플레이어 점수(불꽃허들 재외)
	int m_iTotalScore;//플레이어 총점수
	int m_iLife; //플레이어 생명갯수
	float m_fFIreObstacle_Term; //불꽃장애물사이의거리 플레이어 부활시의 위치를 정하기위해 가져옴
	Player* character;
	FireObstacle* FO;
	FireRing* FR;
	Goal* G;
	float m_fDistance; //게임이동거리
	float m_fMemoDeltaTime; //캐릭터 사망시나 델타타임을 이용(기록)하기 위한 변수
	bool m_bIs_Dead; //게임일시중단이나 사망시 게임을 잠시 멈추게하기위한 용도 (true : stop, false : play)
	//bool m_bDeadFlag; //장애물에 부딛혀서 생명력줄어들떄 true 
public :

	static GameManager* GetInstance()
	{
		if (NULL == m_this)
		{
			m_this = new GameManager;
		}

		return m_this;
	}
	void Init(HWND hWnd);
	void Release(HWND hWnd);
	void Clear();
	void Update(float DeltaTime);
	void Draw(float DeltaTime);
	void LifeDown(); //장애물에 부딛혀서 목숨감소
	void ScoreUp(int Score); //게임클리어시 남은시간비례해서 보너스점수상승할떄 사용
	void ScoreUpdate(); //장애물을 넘거나 돈주머니를 먹었을떄의 점수계산


	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height)
	{
		BITMAPINFO bm_info;
		ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
		bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bm_info.bmiHeader.biBitCount = 24;
		bm_info.bmiHeader.biWidth = width;
		bm_info.bmiHeader.biHeight = height;
		bm_info.bmiHeader.biPlanes = 1;

		LPVOID pBits;
		return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	}

#ifdef _Debug
	void DebugRectangle(RECT rect);
#endif // _Debug

};