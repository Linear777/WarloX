#pragma once
#include "Action.hpp"

class Firearc : public Action
{
	Firearc(const string& name) : Action(name)
	{
		

	}
	~Firearc()
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