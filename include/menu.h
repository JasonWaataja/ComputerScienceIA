#ifndef MENU_H
#define MENU_H

#include "submenu.h"
#include "menuentry.h"

class Menu : public SubMenu
{
	private:

	public:
		Menu(const string& name);

		void printMenuSelection(SubMenu* submenu);
		MenuEntry* getUserSelection(SubMenu* submenu);
		MenuEntry* getUserSelection();
};

#endif
