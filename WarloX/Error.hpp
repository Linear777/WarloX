#pragma once
#include <iostream>

using namespace std;
class Error
{
public:
	static void Message(unsigned __int16 priority, const char * msg)
	{
		priority > 0 ? cout << "Success [" << priority << "] : " << msg << endl : cout << "Fail [" << priority << "] : " << msg << endl;
	}
};