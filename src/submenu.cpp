#include "submenu.h"

#include <vector>
#include <cstdarg>
#include <iostream>

using namespace std;

using namespace std;

SubMenu::SubMenu() : MenuEntry("Submenu", "a submenu")
{
}

SubMenu::SubMenu(const string& name, const string& description, const vector<MenuEntry*>& items) : MenuEntry(name, description), items(items)
{
}

SubMenu::SubMenu(const string& name, const string& description) : MenuEntry(name, description)
{
}

SubMenu::SubMenu(const vector<MenuEntry*>& menuEntries) : SubMenu("Submenu", "a submenu", menuEntries)
{
}

SubMenu::SubMenu(const string& name, const string& description, int menuLength, ...) : SubMenu(name, description)
{
	va_list args;
	va_start(args, menuLength);

	for (int i = 0; i < menuLength; i++) {
		MenuEntry* nextEntry = va_arg(args, MenuEntry*);
		if (nextEntry != NULL)
		{
			items.push_back(nextEntry);
		}
	}

	va_end(args);
}

vector<MenuEntry*>& SubMenu::getItems()
{
	return items;
}

int SubMenu::size() const
{
	return items.size();
}

void SubMenu::addEntry(MenuEntry* entry)
{
	cout << "Adding Entry" << endl;
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

string SubMenu::getEntryLine() const
{
	string entryLine;
	entryLine = "submenu " + MenuEntry::getEntryLine();
	return entryLine;
}
