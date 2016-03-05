#ifndef SUBMENU_H
#define SUBMENU_H

#include <vector>

#include "menuentry.h"

using namespace std;

class SubMenu: public MenuEntry
{
	private:
		vector<MenuEntry*> items;

	public:
		SubMenu();
		SubMenu(const string& name, const string& description, const vector<MenuEntry*>& items);
		SubMenu(const string& name, const string& description);
		SubMenu(const vector<MenuEntry*>& items);
		SubMenu(const string& name, const string& description, int menuLength, ...);

		//returns by reference, I hope it works
		vector<MenuEntry*>& getItems();

		int size() const;
		void addEntry(MenuEntry* entry);
		void removeEntry(int position);
		MenuEntry* getEntry(int position);
		void setEntry(int position, MenuEntry* entry);

		//overriden functions
		bool isMenuEntry() const;
		virtual string getEntryLine() const;
};

#endif
