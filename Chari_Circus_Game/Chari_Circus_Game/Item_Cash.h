#pragma once
#include "GameObject.h"

#define X_CORRECT_POINT 12 

class Item_Cash : public GameObject
{
private :
	int m_iXPoint; //�ܺο��� �޾ƿÿ���
	int m_iImage_X;
	int m_iImage_Y;
public :
	Item_Cash();
	~Item_Cash();
	void Update(float DeltaTime);
	void Draw(HDC hdc);
	void GetXPoint(int NewX);
};

