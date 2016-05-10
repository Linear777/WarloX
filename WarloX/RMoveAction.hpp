#pragma once
#include "wogsiw_utils.hpp"
#include "Action.hpp"
#include "wogsiw_math.hpp"

class RMoveAction : public Action
{
public:
	RMoveAction(const string& name) : Action(name)
	{

	}

	~RMoveAction()
	{
		Error::Message(1, "Deleted MoveAction");
	}

	void appendMainer(ActionAttribs v1)
	{
		this->data.mainer = v1.directionFlow;
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
		object.character->AddDeltaPosition(data.directionFlow.Cross(data.mainer) * data.speed * deltaTime);
	}
};