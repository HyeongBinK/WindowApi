#ifndef BITMAPMANAGER
#define BITMAPMANAGER

#include"BitMap.h"
#include <map>

enum IMAGE
{
	IMAGE_START,
	IMAGE_BACK1 = 0,  //기본 녹색 필드
	IMAGE_BACK2, //코끼리 그림
	IMAGE_BACK3, //관중1
	IMAGE_BACK4, //관중2(박수짝)
	IMAGE_FIREOBSTACLE1, //불꽃장애물 이글이글
	IMAGE_FIREOBSTACLE2, //불꽃장애물 디포트
	IMAGE_LITTLEFIRERING1, //작은불꽃링 왼쪽
	IMAGE_LITTLEFIRERING2, //작은불꽃링 오른쪽
	IMAGE_FIRERING1, //큰불꽃링 왼쪽 이글이글
	IMAGE_FIRERING2, //큰불꽃링 오른쪽 이글이글
	IMAGE_FIRERING3, //큰불꽃링 왼쪽
	IMAGE_FIRERING4, //큰불꽃링 오른쪽 
	IMAGE_INTERFACE1, //상단 스코어 보너스점수 표시해주는 바
	IMAGE_INTERFACE2, //목숨아이콘
	IMAGE_INTERFACE3, //거리M 표시 박스
	IMAGE_PLAYER1, //플레이어 디포트(IDLE)
	IMAGE_PLAYER2, //플레이어달리기(사자달리는 이미지)
	IMAGE_PLAYER3, //플레이어점프
	IMAGE_PLAYER4, //골도착 1
	IMAGE_PLAYER5, //골도착2
	IMAGE_PLAYER6, //장애물에 부딛혀 아웃(DIE)
	IMAGE_MENU1, //플레이어 선택
	IMAGE_MENU2, //1플레이어 A 
	IMAGE_MENU3, //1플레이어 B
	IMAGE_MENU4, //2플레이어 A
	IMAGE_MENU5, //2플레이어 B
	IMAGE_POINT, //플레이어선택 커서 아이콘
	IMAGE_TITLE1, //게임제목
	IMAGE_TITLE2, //게임제목주변 장식(파란별)
	IMAGE_TITLE3,//게임제목주변 장식(빨간별)
	IMAGE_TITLE4,//게임제목주변 장식(노란별)
	IMAGE_BLACK,
	IMAGE_CASH,
	IMAGE_GOAL,
	IMAGE_END
};


class BitMapManager
{
private:
	BitMap* m_parrBitMap;
	std::map<int, const char*> bitmapName;
	static BitMapManager* m_hThis;
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	BitMap* GetImage(IMAGE index)
	{
		return &m_parrBitMap[index];
	}
	BitMapManager();
	void Init(HDC hdc);
	~BitMapManager();

private:
	void SetBitmapName();
};

#endif