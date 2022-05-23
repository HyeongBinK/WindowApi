#include "GameObject.h"

GameObject::GameObject(IMAGE index, int size)
{
	m_ix = 0;
	m_iy = 0;
	m_BitMap = new BitMap[size];

	for (int i = index; (index + size) > i; i++)
	{
		m_BitMap[i - index] = *BitMapManager::GetInstance()->GetImage((IMAGE)i);
	}
}

