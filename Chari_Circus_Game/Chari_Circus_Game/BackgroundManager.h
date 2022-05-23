#pragma once
#include "BackGround.h"

class BackgroundManager
{
private :
	static BackgroundManager* m_this;
	float m_fDistance; //�÷��̾� �̵��Ÿ�
	BackGround* m_bg; //���
	//FireObstacle* m_FO; //�Ҳ���ֹ�(���������ؾ��ϴ�ģ��)
protected :
public :
	static BackgroundManager* GetInstance()
	{
		if (NULL == m_this)
		{
			m_this = new BackgroundManager;
		}

		return m_this;
	}
	void Init();
	void Realese();
	void Update(float DeltaTIme, float NewPlusDistance);
	void Draw(HDC hdc, float DeltaTime);
	void SetDistance(float NewDistance); //���ӿ����ÿ� ĳ���͸� ���� �ڷ� �̵���Ű�����ѿ뵵

	inline float GetDistance()
	{
		return m_fDistance;
	}
	
};

