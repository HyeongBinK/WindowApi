#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "BaseHeader.h"
#include "BitMap.h"
#include "BitMapManager.h"

class GameObject
{
protected :
	BitMap* m_BitMap;
	int m_ix;
	int m_iy;
public :
	GameObject(IMAGE index, int size);
	virtual ~GameObject() { delete[] m_BitMap; }
	virtual void Update(float DeltaTime) = 0;
	virtual void Draw(HDC hdc) = 0;
};


#endif