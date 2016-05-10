#pragma once
#include "Objects.hpp"
#include "wogsiw_math.hpp"
#include "Error.hpp"

struct ActionAttribs
{
	//Absolute settings
	string ActionName;
	Vector3f directionFlow;
	Vector3f forceFlow;

	float durationTime;
	float currentTime;
	float speed;
	float force;

	//Support
	Vector3f mainer;
	//Animation animation;
};


class Action
{
protected:
	ActionAttribs data;

public:

	Action(const string& actionName) 
	{
		this->data.ActionName = actionName;
	}

	void AppendData(ActionAttribs data)
	{
		this->data = data;
	}

	virtual ~Action() { Error::Message(1, "Deleted Action"); }
	virtual void Execute(Object& character) = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
};