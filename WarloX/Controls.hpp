#pragma once

#include "wogsiw_utils.hpp"
#include "Action.hpp"
#include "Character.h"

class Controls
{
private:
	uint ID;
	string name;
	string content;

	bool keys[256];
	Action *controls[256];
	Object& object_to_control;

	void InitializeControls(const string& path)
	{
		ReadFile(path, this->content);
		cout << content.c_str() << endl;
	}

public:


	

	Controls(uint ID, Object& object_to_control) : object_to_control(object_to_control), ID(ID)
	{
		for (int i = 0; i < 256; i++)
		{
			keys[i] = false;
		}
		ClearControls();	
	}

	~Controls()
	{
		for (int i = 0; i < 256; i++)
		{
			if (controls[i] != NULL)
			{
				controls[i]->Destroy();
				controls[i] = NULL;
			}
		}
	}

	void Destroy()
	{
		delete this;
	}

	void ChangeCharacterSource(Object* object)
	{
		Error::Message(1, ("Player changed to " + object->character->name).c_str());
		this->object_to_control = *object;
	}

	void AddOption(Action* action, char key)
	{
		controls[key] = action;
	}
	string getRawOption()
	{
		return this->content;
	}

	string getName()
	{
		return this->name;
	}


	uint getID()
	{
		return this->ID;
	}

	void ClearControls()
	{
		for (int i = 0; i < 256; i++)
		{
			controls[i] = NULL;
		}
	}

	void Execute(char key)
	{
		if (controls[key] != NULL)
		controls[key]->Execute(object_to_control);
	}
};