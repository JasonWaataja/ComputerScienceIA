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

#include "submenu.h"

#include <vector>
#include <cstdarg>
#include <iostream>

using namespace std;

using namespace std;

SubMenu::SubMenu(SubMenu* parentMenu) : SubMenu("Menu", "a submenu", parentMenu)
{
}

SubMenu::SubMenu(const string& name, const string& description, SubMenu* parentMenu) : MenuEntry(name, description), parentMenu(parentMenu)
{
}

vector<MenuEntry*>& SubMenu::getItems()
{
	return items;
}

void SubMenu::setItems(vector<MenuEntry*>& items)
{
	this->items = items;
}

int SubMenu::size() const
{
	return items.size();
}

void SubMenu::addEntry(MenuEntry* entry)
{
	this->items.push_back(entry);
}

void SubMenu::removeEntry(int position)
{
	items.erase(items.begin() + position);
}

MenuEntry* SubMenu::getEntry(int position)
{
	return items[position];
}

void SubMenu::setEntry(int position, MenuEntry* entry)
{
	items[position] = entry;
}

bool SubMenu::isMenuEntry() const
{
	return true;
}

/*string SubMenu::getEntryLine() const
{
	string entryLine;
	entryLine = "submenu " + MenuEntry::getEntryLine();
	return entryLine;
}*/

SubMenu* SubMenu::getParentMenu()
{
	return this->parentMenu;
}
