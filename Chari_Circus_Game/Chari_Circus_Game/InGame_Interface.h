#pragma once
#include "BItMapManager.h"
#include "BaseHeader.h"

#define MAX_BONNUS_SCORE 10000 //타임보너스점수최대치
#define MINUS_BONNUS_SCORE_TERM 10 //틱(델타타임)당 보너스점수 감소수치


enum INTERFACE_TOOL
{
	INTERFACE_TOOL_START,
	INTERFACE_TOOL_BAR = 0,
	INTERFACE_TOOL_LIFE,
	INTERFACE_TOOL_METER,
	INTERFACE_TOOL_END
};


class InGame_Interface 
{
private:
	static InGame_Interface* m_this;
	int m_iPlayerLife; //플레이어 생명갯수 플레이어생명아이콘그릴갯수결정
	float m_fDistance; // 전체 이동거리 
	int m_iPlayerScore; //플레이어 점수(기본0, 장애물넘으면 + 100, 돈주머니아이템먹으면 + 500)
	int m_iPlayerBonnusScore; // 클리어타임에따른 보너스 점수(1만에서 시간당 감소)
	bool m_bFixFlag; //플레이어가 골인지점에 도착해서 점수드 고정
	HFONT m_font;
public:
	static InGame_Interface* GetInstance()
	{
		if (NULL == m_this)
		{
			m_this = new InGame_Interface;
		}

		return m_this;
	}
public :
	void Init();
	void Release();
	void Clear();
	void EraseLifeIcon();
	void Update(float DeltaTime, float NewPlayerDistance, int NewPlayerScore, int NewPlayerLife);
	void Draw(HDC hdc);
	void ShowResult(float DeltaTime);
	void SetFixFlag();
	bool IsEnd()
	{
		return (0 == m_iPlayerBonnusScore);
	}
};

