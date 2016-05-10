#pragma once
#include "Action.hpp"


class Frostarc : public Action
{
	Frostarc(const string& name) : Action(name)
	{

	}

	~Frostarc()
	{

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

	}

};