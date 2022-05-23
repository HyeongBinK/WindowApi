#pragma once
#include "BItMapManager.h"
#include "BaseHeader.h"
	
#define GAROSTAR 16
#define SEROSTAR 6
#define CURSOR_Y_MOVELENGTH 30


class Select_Interface
{
private:
	static Select_Interface* m_this;
	POINT StarLocation[(GAROSTAR+ SEROSTAR)*2];
	POINT CursorLocation;
	int m_iCursor;
	bool m_bSelectScene; 
	int m_iStarValue;
	int DeltaTimeCount;

public:
	static Select_Interface* GetInstance()
	{
		if (NULL == m_this)
		{
			m_this = new Select_Interface;
		}

		return m_this;
	}
	void Init();
	void Release();
	void Clear();
	void SetStarLocation(int x, int y);
	void Update(float DeltaTime);
	void Draw(HDC hdc, float DeltaTime);
	inline bool GetSelectSceneFlag()
	{
		return m_bSelectScene;
	}
};

