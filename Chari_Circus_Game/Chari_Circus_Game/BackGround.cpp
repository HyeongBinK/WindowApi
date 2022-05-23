#include "BackGround.h"

BackGround::BackGround() : GameObject(IMAGE::IMAGE_BACK1, BACKGROUND_IMAGE::BACKGROUND_IMAGE_END),
Image(BACKGROUND_IMAGE_REDFLOWER)
{
	m_iy = SCREEN_HEIGHT * 0.22f;
	m_IBackgroundImage_X_Internal = m_BitMap[Image].GetSize().cx;
	m_IBackgroundImage_Y_Internal = m_BitMap[Image].GetSize().cy;
	m_fDistance = 0;

	m_iImageCount = (int)(SCREEN_WIDTH / m_IBackgroundImage_X_Internal);
	m_iFullImageWid = m_iImageCount * m_IBackgroundImage_X_Internal;

	m_iFirst_X = 0;
	m_ISecond_X = m_iFullImageWid;
	m_iMemoFirst_X = m_iFirst_X;
	m_iMemoSecond_X = m_ISecond_X;
	m_fMemoDeltaTime = 0;
	m_bShowApplause = false;
}

BackGround::~BackGround()
{

}

void BackGround::Update(float DeltaTime)
{
	if (m_fDistance - m_iFirst_X > m_iFullImageWid)
	{
		m_iMemoFirst_X = m_iFirst_X;
		m_iFirst_X += 2 * m_iFullImageWid;
	}
	if (m_fDistance - m_iMemoFirst_X < m_iFullImageWid)
	{
		m_iFirst_X -= 2 * m_iFullImageWid;
		m_iMemoFirst_X = m_iFirst_X;
	}

	if (m_fDistance - m_ISecond_X >  m_iFullImageWid)
	{
		m_iMemoSecond_X = m_ISecond_X;
		m_ISecond_X += 2 * m_iFullImageWid;
	}
	if (m_fDistance - m_iMemoSecond_X <  m_iFullImageWid)
	{
		m_ISecond_X -= 2 * m_iFullImageWid;
		m_iMemoSecond_X = m_ISecond_X;
	}
}

void BackGround::Draw(HDC hdc)
{
	for (int i = 0; m_ix + (m_IBackgroundImage_X_Internal * i) < SCREEN_WIDTH; i++)
	{
		m_BitMap[BACKGROUND_IMAGE_FIELD].Draw(hdc, (m_IBackgroundImage_X_Internal * i), m_iy + m_IBackgroundImage_Y_Internal);
		
		
		if (i == m_iImageCount/2 || i == m_iImageCount-1)
		{
			Image = BACKGROUND_IMAGE_ELEPHANT;
		}
		else
		{
			if(m_bShowApplause == true)
				Image = BACKGROUND_IMAGE_WHITEFLOWER;
			else
				Image = BACKGROUND_IMAGE_REDFLOWER;
		}

		m_BitMap[Image].Draw(hdc, (m_IBackgroundImage_X_Internal * i) + m_iFirst_X  - m_fDistance, m_iy);
		m_BitMap[Image].Draw(hdc, (m_IBackgroundImage_X_Internal * i) + m_ISecond_X - m_fDistance, m_iy);
	}
}

void BackGround::SetDistance(float NewDistance)
{
	m_fDistance = NewDistance;
}

void BackGround::FinishEffect(float DeltaTime)
{
	m_fMemoDeltaTime += DeltaTime;

	if (m_fMemoDeltaTime > IMAGE_CHANGE_DELTA_TICK)
	{
		m_bShowApplause = true;

		if (m_fMemoDeltaTime > IMAGE_CHANGE_DELTA_TICK * 2)
		{
			m_bShowApplause = false;
			m_fMemoDeltaTime = 0;
		}
	}
}



