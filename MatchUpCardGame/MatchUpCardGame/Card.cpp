#include "Card.h"

Card::Card()
{
	m_eCardState = CARD_REAR;
}

void Card::Init(IMAGE Index, int x, int y)
{
	m_pBitMap[CARD_FRONT] = BitMapManager::GetInstance()->GetImage(Index);
	m_pBitMap[CARD_REAR] = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK);
	m_ix = x;
	m_iy = y;
	m_BitMapRect.left = m_DestMapRect.left = x;
	m_BitMapRect.top = m_DestMapRect.top = y;
	m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[CARD_FRONT]->GetSize().cx;
	m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[CARD_FRONT]->GetSize().cy;

	m_DestMapRect.right = m_DestMapRect.left + 120;
	m_DestMapRect.bottom = m_DestMapRect.top + 180;
}

void Card::Draw(HDC hdc)
{
	m_pBitMap[m_eCardState]->Draw(hdc, m_ix, m_iy);
}

void Card::DrawV2(HDC hdc, int w, int h)
{
	m_pBitMap[m_eCardState]->Draw(hdc, m_ix, m_iy , 120, 180);
}

void Card::CardFrontBackChange()
{
	if (CARD_FRONT == m_eCardState)
		return;

	m_eCardState = CARD_FRONT;
}

bool Card::ColliderCheck(POINT point)
{
	if (PtInRect(&m_DestMapRect, point))
	{
		CardFrontBackChange();
		return true;
	}
	return false;
}

void Card::SetCardREAR()
{
	m_eCardState = CARD_REAR;
}

bool Card::IsFront()
{
	return (CARD_FRONT == m_eCardState);
}

Card::~Card()
{
}