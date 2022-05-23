#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_parrBitMap = new BitMap[IMAGE_END + 1];
}


void BitMapManager::Init(HDC hdc)
{
	char buf[256];
	for (int i = IMAGE_START; i <= IMAGE_END; i++)
	{
		sprintf(buf, "RES//0%d.bmp", i);
		m_parrBitMap[i].Init(hdc, buf);
	}
}

BitMapManager::~BitMapManager()
{
	delete[] m_parrBitMap;
}