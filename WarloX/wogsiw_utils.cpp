#include "wogsiw_utils.hpp"



float calcDeltaTime()
{	
	return deltaTime;
}

float calcGameTime()
{
	return 0.f;
}



bool ReadFile(const string& path,string& source)
{
	FILE* file = fopen(path.c_str(), "r");

	char key;

	if (!file) return false;

	while ((key = fgetc(file)) != EOF)
	{
		source += key;
	}

	return true;
}
