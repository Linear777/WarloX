#pragma once
#include <map>
#include "wogsiw_types.hpp"
#include "Controls.hpp"
#include "ControlType.hpp"


class ControlSystem
{
private:
	map<uint, Controls*> options;
	uint control_system_ID;
	ControlType* controlTYPE;

public:

	Controls* current_controls;
	ControlSystem(uint control_size);
	~ControlSystem();


	void addControls(Controls* control);
	Controls& getControls(uint controlID);
	Controls& getControls(string name);
	void removeControls(uint control_ID);

	void CH_ControlBehavior();


	void Destroy();
};