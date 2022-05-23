#pragma once
#include "BItMapManager.h"
#include "BaseHeader.h"

#define MAX_BONNUS_SCORE 10000 //Ÿ�Ӻ��ʽ������ִ�ġ
#define MINUS_BONNUS_SCORE_TERM 10 //ƽ(��ŸŸ��)�� ���ʽ����� ���Ҽ�ġ


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
	int m_iPlayerLife; //�÷��̾� ������ �÷��̾��������ܱ׸���������
	float m_fDistance; // ��ü �̵��Ÿ� 
	int m_iPlayerScore; //�÷��̾� ����(�⺻0, ��ֹ������� + 100, ���ָӴϾ����۸����� + 500)
	int m_iPlayerBonnusScore; // Ŭ����Ÿ�ӿ����� ���ʽ� ����(1������ �ð��� ����)
	bool m_bFixFlag; //�÷��̾ ���������� �����ؼ� ������ ����
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

