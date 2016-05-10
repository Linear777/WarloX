#pragma once
#include "ControlSystem.hpp"

class Preprocess
{
private:

public:
	Preprocess();
	~Preprocess();

	void LoadObjects();
	void LoadAssets();
	void LoadControls(ControlSystem& controlSystem);
	void LoadDatas();

};