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

#include "menuentry.h"

MenuEntry::MenuEntry(const string& name, const string& description) : name(name), description(description)
{
}

MenuEntry::MenuEntry() : MenuEntry("Menu Entry", "a menu entry")
{
}

string MenuEntry::getEntryLine() const
{
	string entryLine;
	entryLine = name + " - " + description;
	return entryLine; 
}

bool MenuEntry::isMenuEntry() const
{
	return false;
}

bool MenuEntry::isItemEntry() const
{
	return !isMenuEntry();
}

string MenuEntry::getName() const
{
	return this->name;
}

void MenuEntry::setName(const string& name)
{
	this->name = name;
}

string MenuEntry::getDescription() const
{
	return this->description;
}

void MenuEntry::setDescription(const string& description)
{
	this->description = description;
}
