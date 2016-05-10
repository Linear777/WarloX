#include <iostream>
#include <map>
#include "Controls.hpp"

using namespace std;

static map<string, unsigned int> commands;

namespace BlockParser
{
	void InitializeCommands(string content)
	{
		bool end = false;
		string copy = content;

		
		while (!end)
		{
			parseCommand(copy);
			parseValue(copy);

		}
	
	}
	void parseCommand(string k)
	{
		
	}

	void parseValue(string k)
	{

	}
}