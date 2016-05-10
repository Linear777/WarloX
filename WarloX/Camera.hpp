#pragma once
#include "wogsiw_math.hpp"
#include "Objects.hpp"
#include <map>
#include <iostream>

#define	FREE_MODE  1
#define	OBJECT_DEPEND  2
#define	OBJECT_DEPEND_AND_FREE 3

#define DEFAULT_MODE FREE_MODE

class CameraE : public Object
{
private:

	Object* follow_object;

	Vector3f position;
	Vector3f right;
	Vector3f up;
	Vector3f direction;

	
	float pitch;
	float yaw;

	map<uint, void(CameraE::*)()> update_by_mode;

	void(CameraE::*ptr)();
	uint camera_mode;

	char keys[256];


public:
	CameraE() : up(Vector3f(0, 1, 0)), direction(Vector3f(0, 0, -1)), position(Vector3f(0, 0, 3))
	{
		pitch = -22.5f;
		yaw = 90;

		camera_mode = DEFAULT_MODE;
		update_by_mode[FREE_MODE] = &CameraE::UpdateFreeMode;
		update_by_mode[OBJECT_DEPEND] = &CameraE::UpdateDependMode;
	}

	~CameraE()
	{


	}


	inline Vector3f& getPosition()
	{
		return data.position;
	}

	inline Vector3f& getUp()
	{
		return this->up;
	}

	inline Vector3f& getRight()
	{
		return this->right;
	}

	inline Vector3f& getDirection()
	{
		return data.direction;
	}

	inline void setEulerAngles(float offs[])
	{
		yaw += -offs[0];
		pitch += offs[1];

		if (pitch > 89) pitch = 89;
		if (pitch < -89) pitch = -89;

	}


	virtual void Update()
	{
		(this->*update_by_mode[camera_mode])();
	}

	inline void UpdateDependMode()
	{
		this->AttachAt(Vector3f(0, 20, -20));
	}

	inline void UpdateFreeMode()
	{
		
	}

	void setDependency(Object* object)
	{
		this->follow_object = object;
	}

	inline void ChangeMode(uint mode)
	{
		camera_mode = mode;
	}

	inline void calculateDirection()
	{

		direction.x = cos(ToRadian(yaw))*cos(ToRadian(pitch));
		direction.y = sin(ToRadian(pitch));
		direction.z = cos(ToRadian(pitch))*sin(ToRadian(yaw));

		right = direction.Cross(up);

		data.direction = direction;
		data.perpendicular = right;

	}

	void LookAt()
	{
		direction = (follow_object->data.position - position).Normalize();
	}

	void AttachAt(Vector3f offset)
	{
		data.position = character->getPosition() + offset;
	}
};




