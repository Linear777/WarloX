#pragma once
#include "Action.hpp"

class MoveAction : public Action
{
public:
	MoveAction(const string& name) : Action(name)
	{

	}

	~MoveAction()
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
		object.character->AddDeltaPosition(data.directionFlow * data.speed * deltaTime);
	}
};