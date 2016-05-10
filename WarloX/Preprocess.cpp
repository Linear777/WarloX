#include "Preprocess.hpp"
#include "Controls.hpp"
#include "Error.hpp"


Preprocess::Preprocess()
{
	Error::Message(1,"Starting Preprocess");
}


Preprocess::~Preprocess()
{
	Error::Message(1, "Delete preprocess");
}

void Preprocess::LoadDatas()
{}

void Preprocess::LoadAssets()
{}

void Preprocess::LoadObjects()
{}

void Preprocess::LoadControls(ControlSystem& control_system)
{
	Error::Message(1, "Loading Controls");

}

