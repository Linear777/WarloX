
#pragma once
#include "wogsiw_math.hpp"

struct Character_attribs
{
	Matrix4f translation;
	Matrix4f rotation;
	Matrix4f scale;
	Matrix4f modelView;

	Character_attribs()
	{		
		translation = Matrix4f();
		rotation = Matrix4f();
		scale = Matrix4f();
		modelView = Matrix4f();

		InitIdentity();
	}

	void InitIdentity()
	{
		translation.InitIdentity();
		rotation.InitIdentity();
		scale.InitIdentity();
		modelView.InitIdentity();
	}
};

class Character
{
private:
	Vector3f position;
	Vector3f direction;
	Vector3f scale;

	Character_attribs data;

public:
	string name;
	
	Character(string name)
	{
		this->name = name;
		
		InitVectors();
	}

	void InitVectors()
	{
		position = Vector3f(0,0,0);
		direction = Vector3f(0, 0, 0);
		scale = Vector3f(0, 0, 0);
		data = Character_attribs();
	}
	void UpdateCharacter()
	{
		data.translation.InitTranslationTransform(position.x,position.y,position.z);

		this->CalculateMatrix();
	}

	void CalculateMatrix()
	{
		data.modelView = data.translation * data.rotation * data.scale;
	}


	void AddDeltaPosition(Vector3f pos)
	{
		position += pos;
		this->UpdateCharacter();
	}

	Vector3f getPosition()
	{
		return this->position;
	}

	Character_attribs& getAttribs()
	{
		return this->data;
	}
};