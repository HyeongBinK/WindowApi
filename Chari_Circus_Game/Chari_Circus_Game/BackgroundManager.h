#pragma once
#include "BackGround.h"

class BackgroundManager
{
private :
	static BackgroundManager* m_this;
	float m_fDistance; //플레이어 이동거리
	BackGround* m_bg; //배경
	//FireObstacle* m_FO; //불꽃장애물(점프로피해야하는친구)
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
	void SetDistance(float NewDistance); //게임오버시에 캐릭터를 조금 뒤로 이동시키기위한용도

	inline float GetDistance()
	{
		return m_fDistance;
	}
	
};

