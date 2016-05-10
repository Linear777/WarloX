#pragma once
#include "Action.hpp"
#include "wogsiw_utils.hpp"

class PerpMove : public Action
{
public:
	PerpMove(const string& name) : Action(name)
	{

	}

	~PerpMove()
	{
		Error::Message(1, "Deleted MoveAction");
	}

	virtual void Destroy()
	{
		delete this;
	}
	virtual void Update()
	{


	}
	virtual void Execute(Object& object)
	{
		object.data.position += object.data.perpendicular * data.speed * deltaTime;
	}
};