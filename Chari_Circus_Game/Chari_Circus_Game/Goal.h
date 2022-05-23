#pragma once
#include "GameObject.h"

class Goal : public GameObject
{
private :

public :
	Goal();
	~Goal();
	void Update(float DeltaTime);
	void Draw(HDC hdc);
};

