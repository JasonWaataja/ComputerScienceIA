#ifndef SUBMENU_H
#define SUBMENU_H

#include <vector>

#include "menuentry.h"

using namespace std;

class SubMenu: public MenuEntry
{
	private:
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

		int size() const;
		void addEntry(MenuEntry* entry);
		void removeEntry(int position);
		MenuEntry* getEntry(int position);
		void setEntry(int position, MenuEntry* entry);

		//overriden functions
		bool isMenuEntry() const;
		//virtual string getEntryLine() const;

		//returns parentMenu, nullptr if none exists
		SubMenu* getParentMenu();
};

#endif
