#pragma once
#include "Character.h"

struct Object_Attribs
{
	Vector3f position;
	Vector3f direction;
	Vector3f scale;
	Quaternion* rotation;

	Vector3f force;
	Vector3f speed;

	Vector3f perpendicular;

	Object_Attribs()
	{

	}
};

class Object
{
protected:
public:
	Character* character;
	Object_Attribs data;

	Object();
	~Object();

	virtual void Update(){};
};

