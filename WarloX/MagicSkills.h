#pragma once
#include "Action.hpp"

class MagicSkills : public Action
{
protected:
	

public:

	MagicSkills(const string& name) : Action(name)
	{
		
	}

	~MagicSkills()
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