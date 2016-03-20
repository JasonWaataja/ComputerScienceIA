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

#ifndef SUBMENU_H
#define SUBMENU_H

#include <vector>

#include "menuentry.h"

using namespace std;

/* MenuEntry that can contain other menu entries.
   Acts as a way to branch out different options in menus. */
class SubMenu: public MenuEntry
{
	private:
		//The list of menuentries that this submenu has and displays.
		vector<MenuEntry*> items;
		//parent menu, nullptr if no parent
		SubMenu* parentMenu;

	public:
		SubMenu(SubMenu* parentMenu=nullptr);
		//note, use of this function may result in not all entires being deleted properly, this is meant to use when reordering or modifying.
		SubMenu(const string& name, const string& description, SubMenu* parentMenu=nullptr);

		//returns by reference, I hope it works
		vector<MenuEntry*>& getItems();
		void setItems(vector<MenuEntry*>& items);

		//amount of entries, calls vector.size()
		int size() const;
		//adds a menu entry at the end, calls vector.push_back().
		void addEntry(MenuEntry* entry);
		//removes entry at given index, calls vector.erase().
		void removeEntry(int position);
		//returns menu entry at given index, must be cast before use. Calls vector.operator[].
		MenuEntry* getEntry(int position);
		//sets the menu entry at given index to entry, calls vector.operator[].
		void setEntry(int position, MenuEntry* entry);

		//overriden functions
		bool isMenuEntry() const;
		//virtual string getEntryLine() const;

		//returns parentMenu, nullptr if none exists
		SubMenu* getParentMenu();
};

#endif
