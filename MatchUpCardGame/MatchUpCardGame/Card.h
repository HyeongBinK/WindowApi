#pragma once
#include"BaseHeader.h"
#include"BitMap.h"
#include"BitMapManager.h"

enum CARD
{
	CARD_FRONT,
	CARD_REAR,
	CARD_END
};

class Card
{
private:
	CARD m_eCardState;
	BitMap* m_pBitMap[CARD_END];
	int m_ix;
	int m_iy;
	RECT m_BitMapRect, m_DestMapRect;
public:
	Card();
	void Init(IMAGE Index, int x, int y);
	void Draw(HDC hdc);
	void DrawV2(HDC hdc, int w, int h);
	void CardFrontBackChange();
	bool ColliderCheck(POINT point);
	bool IsFront();
	void SetCardREAR();
	void CardLocalization(int w, int h);


	CARD inline GetCardState()
	{
		return m_eCardState;
	}
	int inline GetXLocation()
	{
		return m_ix;
	}
	int inline GetYLocation()
	{
		return m_iy;
	}
	~Card();
};

