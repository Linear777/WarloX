#pragma once
#include "Action.hpp"
#include "wogsiw_utils.hpp"

class DirectionMove : public Action
{
public:
	DirectionMove(const string& name) : Action(name)
	{

	}

	~DirectionMove()
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
		object.data.position += object.data.direction * data.speed * deltaTime;
	}
};