#pragma once
#include <iostream>

#define MAX_KEY_PRESSED 10

class KeyEvent
{
	public:
		int keyLsize = 0;
		int keyStart = 0;

		char keys[256];

		char keyL[MAX_KEY_PRESSED];
		char keyP[256];

		float offsets[2];

		KeyEvent::KeyEvent()
		{
			for (int i = 0; i < 256; i++) keys[i] = 0;
			//Error::Message(1, "Key event created");
		}

		KeyEvent::~KeyEvent()
		{
			//Error::Message(1, "Key event destroyed");
		}

		inline void KeyEvent::press(char code)
		{
			keyL[++keyLsize - 1] = code;
			keyP[code] = keyLsize - 1;
		}

		inline void KeyEvent::unpress(char code)
		{
			for (int i = keyP[code]; i < keyLsize - 1; i++)	{ keyP[keyL[i+1]]--; keyL[i] = keyL[i + 1]; }
			keyL[--keyLsize] = '\0';
		}


		inline void KeyEvent::WIP()
		{
			for (int i = 0; i < keyLsize; i++)
			{
				std::cout << keyL[i] << ",";
			}
			std::cout << std::endl;
		}

		inline void KeyEvent::mouse_offsets(float oX, float oY)
		{
			this->offsets[0] = oX;
			this->offsets[1] = oY;
		}
};

