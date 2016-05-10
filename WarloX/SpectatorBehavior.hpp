#pragma once
#include "ControlType.hpp"



class BasicSpectatorBehavior : public ControlType
{
private:

public:
	BasicSpectatorBehavior()
	{

	}
	~BasicSpectatorBehavior()
	{

	}

	virtual void ChangeBehavior()
	{
		Error::Message(1, "PlayerBehavior Changed");
		camera->ChangeMode(FREE_MODE);

	}

};


