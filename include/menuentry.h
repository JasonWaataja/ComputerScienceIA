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

#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <string>

using namespace std;

/* Class that represents an entry in a menu, subclasses of which can represent items or more submenus */
class MenuEntry
{
	private:
		//the name of the menuentry
		string name;
		//the description of the menuentry
		string description;

	public:
		MenuEntry(const string& name, const string& description);
		MenuEntry();

		virtual string getEntryLine() const;

		//getters and setters for main variables
		string getName() const;
		void setName(const string& name);
		string getDescription() const;
		void setDescription(const string &description);

		//Returns whether or not this entry is a menu, such as a SubMenu or Menu
		virtual bool isMenuEntry() const;
		//returns opposite of above for convenience, isn't meant to be overridden
		bool isItemEntry() const;
};

#endif
