#pragma once
#include <iostream>
#include <map>

using namespace std;

class Widget
{
public:
	virtual void onSelect(int position) = 0;
	virtual void onClick(int x, int y) = 0;
	virtual void onHover(int x, int y) = 0;

	virtual void show() = 0;
};



struct MenuParam
{
private:
	string menu_title;
	void (*val_ptr)();
	int selection_key;

public:
	MenuParam(){}
	MenuParam(string title,int selection,void (*ptr)()):menu_title(title),selection_key(selection),val_ptr(ptr){}
	void msg() { val_ptr(); }
};

class Menu : public Widget
{
public:

	void appendMenuParam(string title,int selection,void (*ptr)())
	{
		menu_params[selection] = MenuParam(title,selection,ptr);
	}

	void onSelect(int key)
	{
		menu_params[key].msg();
	}

	void onClick(int x, int y)
	{


	}

	void onHover(int x, int y)
	{



	}

	void show()
	{
		for (map<int, MenuParam>::iterator it = menu_params.begin(); it != menu_params.end();it++)
		{
			it->second.msg();
		}
	}
private:

	map<int,MenuParam> menu_params;
};