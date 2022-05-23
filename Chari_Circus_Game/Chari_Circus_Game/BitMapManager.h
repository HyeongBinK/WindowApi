#ifndef BITMAPMANAGER
#define BITMAPMANAGER

#include"BitMap.h"
#include <map>

enum IMAGE
{
	IMAGE_START,
	IMAGE_BACK1 = 0,  //�⺻ ��� �ʵ�
	IMAGE_BACK2, //�ڳ��� �׸�
	IMAGE_BACK3, //����1
	IMAGE_BACK4, //����2(�ڼ�¦)
	IMAGE_FIREOBSTACLE1, //�Ҳ���ֹ� �̱��̱�
	IMAGE_FIREOBSTACLE2, //�Ҳ���ֹ� ����Ʈ
	IMAGE_LITTLEFIRERING1, //�����Ҳɸ� ����
	IMAGE_LITTLEFIRERING2, //�����Ҳɸ� ������
	IMAGE_FIRERING1, //ū�Ҳɸ� ���� �̱��̱�
	IMAGE_FIRERING2, //ū�Ҳɸ� ������ �̱��̱�
	IMAGE_FIRERING3, //ū�Ҳɸ� ����
	IMAGE_FIRERING4, //ū�Ҳɸ� ������ 
	IMAGE_INTERFACE1, //��� ���ھ� ���ʽ����� ǥ�����ִ� ��
	IMAGE_INTERFACE2, //���������
	IMAGE_INTERFACE3, //�Ÿ�M ǥ�� �ڽ�
	IMAGE_PLAYER1, //�÷��̾� ����Ʈ(IDLE)
	IMAGE_PLAYER2, //�÷��̾�޸���(���ڴ޸��� �̹���)
	IMAGE_PLAYER3, //�÷��̾�����
	IMAGE_PLAYER4, //���� 1
	IMAGE_PLAYER5, //����2
	IMAGE_PLAYER6, //��ֹ��� �ε��� �ƿ�(DIE)
	IMAGE_MENU1, //�÷��̾� ����
	IMAGE_MENU2, //1�÷��̾� A 
	IMAGE_MENU3, //1�÷��̾� B
	IMAGE_MENU4, //2�÷��̾� A
	IMAGE_MENU5, //2�÷��̾� B
	IMAGE_POINT, //�÷��̾�� Ŀ�� ������
	IMAGE_TITLE1, //��������
	IMAGE_TITLE2, //���������ֺ� ���(�Ķ���)
	IMAGE_TITLE3,//���������ֺ� ���(������)
	IMAGE_TITLE4,//���������ֺ� ���(�����)
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