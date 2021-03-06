#pragma once

/*This class represents idea of basic movement system (Firmware options)*/

enum WOG_UPPER_KEYS_MOVEMENT
{
	WOG_KEY_FORWARD = 'A',
	WOG_KEY_BACKWARD = 'S',
	WOG_KEY_LEFT = 'A',
	WOG_KEY_RIGHT = 'D',

	WOG_UPPER_KEYS_MOVEMENT_SIZE = 4
};

enum WOG_LOWER_KEYS_MOVEMENT
{
	WOG_KEY_FORWARD = 'w',
	WOG_KEY_BACKWARD = 's',
	WOG_KEY_LEFT = 'a',
	WOG_KEY_RIGHT = 'd',

	WOG_LOWER_KEYS_MOVEMENT_SIZE = 4
};

enum WOG_ACTION_KEYS
{
	WOG_KEY_JUMP = ' ',
	WOG_KEY_BIND0 = 1,
	WOG_KEY_BIND1,
	WOG_KEY_BIND2,
	WOG_KEY_BIND3,
	WOG_KEY_BIND4,

	WOG_ACTION_KEYS_SIZE = 6
};