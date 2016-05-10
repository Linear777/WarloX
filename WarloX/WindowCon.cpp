#include "WindowCon.hpp"
#include "WindowInit.hpp"


WindowCon::WindowCon()
{


}

WindowCon::~WindowCon()
{
	
}


WindowInit* WindowCon::getWindowContext(unsigned short key)
{
	return Window_context[key];
}

void WindowCon::setWindowContext(WindowInit* window)
{
	Window_context.push_back(window);
}