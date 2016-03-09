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
		//gets a user selected entry. If parentMenu is nullptr, then the option "quit" will be available instead of "parent"
		MenuEntry* getUserSelection(SubMenu* submenu);
		//returns a user selected item, returns null if not item was selected
		MenuEntry* getUserSelection();
};

#endif
