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
