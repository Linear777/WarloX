#pragma once
#include "Objects.hpp"
#include "Camera.hpp"
#include "Error.hpp"
#include "Controls.hpp"

class ControlType
{
public:
	Object *obj;
	Character *character;
	CameraE *camera;
	Controls* controls;

	ControlType(){}
	~ControlType(){}

	virtual void ChangeBehavior() = 0;

protected:
};