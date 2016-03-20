/*Copyright 2016 Jason Waataja

  This file is part of BashTutorial.

  BashTutorial is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  BashTutorial is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with BashTutorial.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef MENU_H
#define MENU_H

#include "submenu.h"
#include "menuentry.h"

/* Menu class which is used by the BashTutorial class.
   It's a normal submenu except with the exception that it
   has an interactive selection process and get get a user selection. */
class Menu : public SubMenu
{
	private:

	public:
		//constructs a menu with the given name.
		Menu(const string& name);

		void printMenuSelection(SubMenu* submenu);
		//gets a user selected entry. If parentMenu is nullptr, then the option "quit" will be available instead of "parent". Stores its parentMenu in parentMenu.
		MenuEntry* getUserSelection(SubMenu* submenu, SubMenu*& parentMenuToSet);
		//returns a user selected item, returns null if not item was selected, stores parent menu in parent
		MenuEntry* getUserSelection(SubMenu*& parentMenuToSet);
};

#endif
