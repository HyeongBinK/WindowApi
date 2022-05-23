// MatchUpCardGame.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "MatchUpCardGame.h"
#include"GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MatchUpCardGame");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//아이콘 모양
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;	//프로세스 함수 호출
	WndClass.lpszClassName = lpszClass;	//클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 700, 900,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HDC hdc;
	PAINTSTRUCT ps;
	//static Card card;

	switch (iMessage)
	{
	case WM_CREATE:
		//card.Init(IMAGE_CHICKEN, 500, 200);
		GameManager::GetInstance()->Init(hWnd);
		GameManager::GetInstance()->MakeRandomCard();
		GameManager::GetInstance()->CollocateCard();
		//GameManager::GetInstance()->DrawBackGroundImage();
		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 1000, NULL);
		return 0;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			GameManager::GetInstance()->CheckMatchUp(hWnd);
			break;
		case 2:
			GameManager::GetInstance()->GameTimerUp();
			break;
		}
		//InvalidateRect(hWnd, NULL, false);
		return 0;
	case WM_LBUTTONDOWN:
		POINT Point;
		Point.x = LOWORD(lParam);
		Point.y = HIWORD(lParam);
		switch (GameManager::GetInstance()->GetCurrentPage())
		{
		case GAMEPAGE_eSTARTPAGE:
			GameManager::GetInstance()->StartButtonColliderCheck(Point, hWnd);
			return 0;
			break;
		case GAMEPAGE_ePLAYPAGE:
			GameManager::GetInstance()->ColliderCheck(Point, hWnd);
			//InvalidateRect(hWnd, NULL, false);
			return 0;
			break;
		/*case GAMEPAGE_eRESULTPAGE :
			break;*/
		default :
			return 0;
		}
	case WM_PAINT:
	{
		HDC hdc = BeginPaint(hWnd, &ps);
		GameManager::GetInstance()->DrawBackGroundImage();
		switch (GameManager::GetInstance()->GetCurrentPage())
		{
		case GAMEPAGE_eSTARTPAGE:
			GameManager::GetInstance()->DrawStartButton();
			break;
		case GAMEPAGE_ePLAYPAGE:
			GameManager::GetInstance()->DrawAllCard();
			GameManager::GetInstance()->ShowTimer();
			break;
		/*case GAMEPAGE_eRESULTPAGE:
			break;*/
		}
		//card.Draw(hdc);
		EndPaint(hWnd, &ps);
	}
		return 0;
	case WM_DESTROY:
		GameManager::GetInstance()->Release(hWnd);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}