#pragma once
#include "wogsiw_math.hpp"

class Movement
{
protected:
	Vector3f direction;

	float durationTime;
	float currentTime;
	float speed;

	//Animation animation;

public:
	virtual void Execute() = 0;
	virtual void Update() = 0;
};

