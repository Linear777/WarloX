#pragma once
#include "ControlType.hpp"



class BasicPlayerBehavior : public ControlType
{
private:

public:
	BasicPlayerBehavior()
	{

	}
	~BasicPlayerBehavior()
	{

	}

	virtual void ChangeBehavior()
	{
		Error::Message(1, "PlayerBehavior Changed");
		camera->ChangeMode(OBJECT_DEPEND);
		
	}

};


