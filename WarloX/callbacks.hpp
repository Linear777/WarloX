#pragma once

#include "keys.hpp"

class ICallbacks
{
public:

	virtual void KeyboardCB(OGLDEV_KEY OgldevKey) {};

	virtual void PassiveMouseCB(int x, int y) {};

	virtual void RenderSceneCB() {};

	virtual void MouseCB(OGLDEV_MOUSE Button, OGLDEV_KEY_STATE State, int x, int y) {};
};
