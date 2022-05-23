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
	float m_fDistance; //�÷��̾� x��ġ(�Ÿ�)
	int m_iFirst_X; //ù��° ȭ���� ��ǥ
	int m_ISecond_X; //�ι��� ȭ���� ��ǥ
	int m_iMemoFirst_X; //ȭ��ΰ��� �����ϸ鼭 �ٲ�±����̱⿡ ù���� x ��ġ��ǥ ���
	int m_iMemoSecond_X; // �ι��� x ��ǥ��ġ ���
	int m_iImageCount; //ȭ���� ũ�⿡ ���缭 �̹����� ����� ���� ���� ī��Ʈ
	int m_iFullImageWid; //�ܼ�â�� ���̿� �̹����� ���������� �̻ڰ� ���̱�����Ƿ� �ִ��� �ֿ������� �̹������� ���α��� ����
	float m_fMemoDeltaTime; //UPdate ���� DeltaTime ���� �ð����ݿ����� ���������� ����ϱ����� ���
	bool m_bShowApplause; //true ���Ǹ� ����� ���ߵ��� �ڼ��� ġ�Բ�
	BACKGROUND_IMAGE Image;
	int m_IBackgroundImage_X_Internal; //����̹����� x ����
	int m_IBackgroundImage_Y_Internal; //����̹����� y ����,
	
public:
	BackGround();
	~BackGround();
	void Update(float DeltaTime);
	void Draw(HDC hdc);
	void SetDistance(float NewDistance);
	void FinishEffect(float DeltaTime);
};

