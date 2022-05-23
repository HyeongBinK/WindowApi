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
	int m_iScore; //�÷��̾� ����(�Ҳ���� ���)
	int m_iTotalScore;//�÷��̾� ������
	int m_iLife; //�÷��̾� ������
	float m_fFIreObstacle_Term; //�Ҳ���ֹ������ǰŸ� �÷��̾� ��Ȱ���� ��ġ�� ���ϱ����� ������
	Player* character;
	FireObstacle* FO;
	FireRing* FR;
	Goal* G;
	float m_fDistance; //�����̵��Ÿ�
	float m_fMemoDeltaTime; //ĳ���� ����ó� ��ŸŸ���� �̿�(���)�ϱ� ���� ����
	bool m_bIs_Dead; //�����Ͻ��ߴ��̳� ����� ������ ��� ���߰��ϱ����� �뵵 (true : stop, false : play)
	//bool m_bDeadFlag; //��ֹ��� �ε����� ������پ�鋚 true 
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
	void LifeDown(); //��ֹ��� �ε����� �������
	void ScoreUp(int Score); //����Ŭ����� �����ð�����ؼ� ���ʽ���������ҋ� ���
	void ScoreUpdate(); //��ֹ��� �Ѱų� ���ָӴϸ� �Ծ������� �������


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