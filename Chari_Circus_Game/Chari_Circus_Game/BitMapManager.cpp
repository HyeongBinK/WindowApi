#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_parrBitMap = new BitMap[IMAGE_END];
}

void BitMapManager::SetBitmapName()
{
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_BACK1, "BackGround_Image//back_1"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_BACK2, "BackGround_Image//back_2"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_BACK3, "BackGround_Image//back_3"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_BACK4, "BackGround_Image//back_4"));

	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_FIREOBSTACLE1, "FireObstacle_Image//fire_1"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_FIREOBSTACLE2, "FireObstacle_Image//fire_2"));

	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_LITTLEFIRERING1, "FireRing_Image//littlering_1"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_LITTLEFIRERING2, "FireRing_Image//littlering_2"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_FIRERING1, "FireRing_Image//ring_1"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_FIRERING2, "FireRing_Image//ring_2"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_FIRERING3, "FireRing_Image//ring_3"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_FIRERING4, "FireRing_Image//ring_4"));

	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_INTERFACE1, "Interface_Image//interface_1"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_INTERFACE2, "Interface_Image//interface_2"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_INTERFACE3, "Interface_Image//interface_3"));

	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_PLAYER1, "Player_Image//player_1"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_PLAYER2, "Player_Image//player_2"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_PLAYER3, "Player_Image//player_3"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_PLAYER4, "Player_Image//player_4"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_PLAYER5, "Player_Image//player_5"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_PLAYER6, "Player_Image//player_6"));

	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_MENU1, "SelectScreen_Image//menu_1"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_MENU2, "SelectScreen_Image//menu_2"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_MENU3, "SelectScreen_Image//menu_3"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_MENU4, "SelectScreen_Image//menu_4"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_MENU5, "SelectScreen_Image//menu_5"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_POINT, "SelectScreen_Image//point"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_TITLE1, "SelectScreen_Image//title_1"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_TITLE2, "SelectScreen_Image//title_2"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_TITLE3, "SelectScreen_Image//title_3"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_TITLE4, "SelectScreen_Image//title_4"));

	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_BLACK, "black"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_CASH, "cash"));
	bitmapName.insert(std::pair<int, const char*>(IMAGE::IMAGE_GOAL, "goal"));
}

void BitMapManager::Init(HDC hdc)
{
	SetBitmapName();

	char buf[256];
	for (int i = IMAGE_START; i < IMAGE_END; i++)
	{
		sprintf(buf, "ImageFile//%s.bmp", bitmapName[i]);
		m_parrBitMap[i].Init(hdc, buf);
	}
	//for (int i = IMAGE_BACK1; i <= IMAGE_BACK4; i++)
	//{
	//	sprintf(buf, "ImageFile//BackGround_Image//%d.bmp", i + 1);
	//	m_parrBitMap[i].Init(hdc, buf);
	//}
	//for (int i = IMAGE_FIREOBSTACLE1; i <= IMAGE_FIREOBSTACLE2; i++)
	//{
	//	sprintf(buf, "ImageFile//FireObstacle_Image%d.bmp", (i + 1) - IMAGE_FIREOBSTACLE1);
	//	m_parrBitMap[i].Init(hdc, buf);
	//}
	//for (int i = IMAGE_LITTLEFIRERING1; i <= IMAGE_FIRERING4; i++)
	//{
	//	sprintf(buf, "ImageFile//FireRing_Image%d.bmp", (i + 1) - IMAGE_LITTLEFIRERING1);
	//	m_parrBitMap[i].Init(hdc, buf);
	//}
	//for (int i = IMAGE_INTERFACE1; i <= IMAGE_INTERFACE3; i++)
	//{
	//	sprintf(buf, "ImageFile//Interface_Image%d.bmp", (i + 1) - IMAGE_INTERFACE1);
	//	m_parrBitMap[i].Init(hdc, buf);
	//}
	//for (int i = IMAGE_PLAYER1; i <= IMAGE_PLAYER6; i++)
	//{
	//	sprintf(buf, "ImageFile//Player_Image%d.bmp", (i + 1) - IMAGE_PLAYER1);
	//	m_parrBitMap[i].Init(hdc, buf);
	//}
	//for (int i = IMAGE_MENU1; i <= IMAGE_TITLE4; i++)
	//{
	//	sprintf(buf, "ImageFile//SelectScreen_Image%d.bmp", (i + 1) - IMAGE_MENU1);
	//	m_parrBitMap[i].Init(hdc, buf);
	//}
	//for (int i = IMAGE_BLACK; i <= IMAGE_GOAL; i++)
	//{
	//	sprintf(buf, "ImageFile//%d.bmp", (i + 1) - IMAGE_BLACK);
	//	m_parrBitMap[i].Init(hdc, buf);
	//}

}

BitMapManager::~BitMapManager()
{
	delete[] m_parrBitMap;
}