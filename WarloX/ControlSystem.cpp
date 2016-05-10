#include "ControlSystem.hpp"
#include <iostream>

ControlSystem::ControlSystem(uint size)
{
	//controls.reserve(size);
}

ControlSystem::~ControlSystem()
{
	/*for (std::map<uint, Controls*>::iterator it = options.begin(); it != options.end();it++)
	{
		(*it).second->Destroy();
	}*/
	options.clear();
}

void ControlSystem::addControls(Controls* control)
{
	options[control->getID()] = control;
}


void ControlSystem::removeControls(uint control_ID)
{
	options[control_ID]->Destroy();
}

Controls& ControlSystem::getControls(uint control_ID)
{
	return *options[control_ID];
}

Controls& ControlSystem::getControls(string name)
{
	int i = 0;
	

	return *options[i];
}

void ControlSystem::Destroy()
{
	delete this;
}

void ControlSystem::CH_ControlBehavior()
{


}