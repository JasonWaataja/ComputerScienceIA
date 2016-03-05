#include "menu.h"

#include <iostream>
#include <string>

using namespace std;

Menu::Menu(const string& name) : SubMenu(name, "Menu - " + name)
{

}

void Menu::printMenuSelection(SubMenu* submenu)
{
	cout << submenu->getName() << endl;
	for (int i = 0; i < submenu->size(); i++)
	{
		MenuEntry* currentEntry = submenu->getEntry(i);
		cout << "\t" << i+1 << ": " << currentEntry->getEntryLine() << endl;
	}
}

MenuEntry* Menu::getUserSelection(SubMenu* submenu)
{
	printMenuSelection(submenu);

	int length = submenu->size();
	if (length > 0)
	{
		int selection = 0;
		do {
			//note, this assumes there's at least 1 entry, will produce a weird result of no-entries
			//also, accepts answer on the same line
			cout << "Please enter a selection 1-" << length << ": ";
			string userInput;
			cin >> userInput;
			try {
				selection = std::stoi(userInput);
				if (selection < 1 || selection > length) {
					cout << "You have to enter a number from 1 to " << length << ". Try again" << endl;
				}
			} catch (...) {
				cout << "There was an error with your input, make user you enter an integer." << endl;
				selection = 0;
			}
		} while (selection < 1 || selection > length);
		MenuEntry* selectedEntry = submenu->getEntry(selection);
		return selectedEntry;
	} else {
		cerr << "Error, trying to print a menu with no entries" << endl;
		return NULL;
	}
}

MenuEntry* Menu::getUserSelection()
{
	return getUserSelection(this);
}
