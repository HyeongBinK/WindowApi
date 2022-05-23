#pragma once
#include "GameObject.h"

#define IMAGE_CHANGE_DELTA_TICK 0.2f

enum BACKGROUND_IMAGE
{
	BACKGROUND_IMAGE_START,
	BACKGROUND_IMAGE_FIELD = 0,
	BACKGROUND_IMAGE_ELEPHANT, 
	BACKGROUND_IMAGE_REDFLOWER,
	BACKGROUND_IMAGE_WHITEFLOWER,
	BACKGROUND_IMAGE_END
};

class BackGround : public GameObject
{
private :
	float m_fDistance; //플레이어 x위치(거리)
	int m_iFirst_X; //첫번째 화면의 좌표
	int m_ISecond_X; //두번쨰 화면의 좌표
	int m_iMemoFirst_X; //화면두개가 셔플하면서 바뀌는구조이기에 첫번쨰 x 위치좌표 기억
	int m_iMemoSecond_X; // 두번쨰 x 좌표위치 기억
	int m_iImageCount; //화면의 크기에 맞춰서 이미지가 몇개들어가는 가에 대한 카운트
	int m_iFullImageWid; //콘솔창의 길이에 이미지를 정수형으로 이쁘게 붙이긴힘드므로 최대한 최웠을떄의 이미지들의 가로길이 총합
	float m_fMemoDeltaTime; //UPdate 에서 DeltaTime 과의 시간간격에따라 게임진행을 재어하기위해 사용
	bool m_bShowApplause; //true 가되면 배경의 관중들이 박수를 치게끔
	BACKGROUND_IMAGE Image;
	int m_IBackgroundImage_X_Internal; //배경이미지의 x 간격
	int m_IBackgroundImage_Y_Internal; //배경이미지의 y 간격,
	
public:
	BackGround();
	~BackGround();
	void Update(float DeltaTime);
	void Draw(HDC hdc);
	void SetDistance(float NewDistance);
	void FinishEffect(float DeltaTime);
};

