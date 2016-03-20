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

#include "menu.h"

#include <iostream>
#include <string>

using namespace std;

Menu::Menu(const string& name) : SubMenu(name, "Menu - " + name)
{

}

void Menu::printMenuSelection(SubMenu* submenu)
{
	//print out menu name at top.
	cout << submenu->getName() << endl;
	//loops over and prints the line for each entry.
	for (int i = 0; i < submenu->size(); i++)
	{
		MenuEntry* currentEntry = submenu->getEntry(i);
		cout << "\t" << i+1 << ": " << currentEntry->getEntryLine() << endl;
	}
	SubMenu* parent = submenu->getParentMenu();
	//if it's null, present quit option, otherwise allow parent
	if (parent != nullptr) {
		cout << "\t" << submenu->size()+1 << ": " << "Parent directory - " << parent->getName() << endl;
	} else {
		cout << "\t" << submenu->size()+1 << ": Quit" << endl;
	}
}

MenuEntry* Menu::getUserSelection(SubMenu* submenu, SubMenu*& parentMenuToSet)
{
	//first, print out the selection so the user can see the options.
	printMenuSelection(submenu);
	parentMenuToSet = submenu;

	int length = submenu->size();
	/*if (length > 0)
	  {*/
	int selection = 0;
	do {
		//note, this assumes there's at least 1 entry, will produce a weird result of no-entries
		//also, accepts answer on the same line
		cout << "Please enter a selection 1-" << length+1 << ": ";
		string userInput;
		cin >> userInput;
		try {
			//string to int = stoi
			selection = std::stoi(userInput);
			if (selection < 1 || selection > length+1) {
				cout << "You have to enter a number from 1 to " << length+1 << ". Try again" << endl;
			}
		} catch (...) {
			cout << "There was an error with your input, make user you enter an integer." << endl;
			selection = 0;
		}
	} while (selection < 1 || selection > length+1);
	//if it's the last entry;
	if (selection == length+1) {
		cout << "last entry in menu was selected" << endl;
		SubMenu* parent = submenu->getParentMenu();
		if (parent != nullptr) {
			return getUserSelection(parent, parentMenuToSet);
		} else {
			//the "quit" was used and we're returning null
			parentMenuToSet = nullptr;
			return nullptr;
		}
	}
	MenuEntry* selectedEntry = submenu->getEntry(selection-1);
	if (selectedEntry->isMenuEntry()) {
		SubMenu* asSubMenu = dynamic_cast<SubMenu*>(selectedEntry);
		if (asSubMenu) {
			return getUserSelection(asSubMenu, parentMenuToSet);
		} else {
			//as of now, fails if it's anything other than a submenu object.
			return nullptr;
		}
	}
	return selectedEntry;
	/*} else {
	  cerr << "Error, trying to print a menu with no entries" << endl;
	  return nullptr;
	  }*/
}

MenuEntry* Menu::getUserSelection(SubMenu*& parentMenuToSet)
{
	//return getUserSelection(this, parentMenu);
	MenuEntry* selection = getUserSelection(this, parentMenuToSet);
	return selection;
}
