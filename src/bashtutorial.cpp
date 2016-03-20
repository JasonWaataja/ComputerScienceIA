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

#include "bashtutorial.h"

//#include <iostream>
#include <cassert>
//#include <dirent.h>
//#include <sys/types.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <boost/filesystem.hpp>

#include "menu.h"
#include "tutorial.h"

using namespace std;
using namespace boost::filesystem;

bool getYesNo(const string& prompt)
{
	//print out the prompt
	cout << prompt;
	string line;
	getline(cin, line);
	//if Y or y, return true, N or n return false, asks again if neither.
	if (line.length() > 0) {
		char c = line[0];
		if (c == 'Y' || c == 'y')
			return true;
		else if (c == 'N' || c == 'n')
			return false;
		else {
			cout << "Enter yes or no." << endl;
			return getYesNo();
		}
	} else {
		return getYesNo();
	}
}

bool getYesNo()
{
	//uses empty prompt I guess.
	string prompt;
	return getYesNo(prompt);
}

SubMenu* getTutorialsInDirectory(const string& tutorialDirectory, SubMenu* parentMenu)
{
	//the current directory.
	path dir(tutorialDirectory);
	//menu to return.
	SubMenu* menu = new SubMenu(dir.filename().string(), "sub directory", parentMenu);
	//if it's a directory, load the stuff in the directory.
	if (is_directory(dir)) {
		//iterate over every entry in the directory.
		directory_iterator i(dir);
		directory_iterator end;
		for (; i != end; i++) {
			path p = i->path();
			//if it's not a directoy, see if it's a tutorial and add it, otherwise, add a new entry that is a submenu and load from that.
			if (is_regular_file(p)) {
				Tutorial* tut = new Tutorial();
				bool success = tut->loadFromFile(p.string());
				if (success) {
					menu->addEntry(tut);
				} else {
					delete tut;
				}
			} else {
				SubMenu* submenu = getTutorialsInDirectory(p.string(), menu);
				menu->addEntry(submenu);
				//submenu->setName(p.filename().string());
			}
		} 
		//order with order file
		path p = dir / ORDER_FILE_NAME;
		orderWithFile(menu, p.string());
	}
	return menu;
}

void deleteTutorialsInMenu(SubMenu* menu)
{
	//delete everything in each entry.
	for (int i = 0; i < menu->size(); i++) {
		MenuEntry* entry;
		entry = menu->getEntry(i);
		//if it's a submenu, recursively delete everything in the submenu.
		if (entry->isMenuEntry()) {
			SubMenu* asSubMenu = dynamic_cast<SubMenu*>(entry);
			if (asSubMenu) {
				deleteTutorialsInMenu(asSubMenu);
			}
		}
		//now delete the entry itself.
		delete entry;
	}
}

bool orderWithFile(SubMenu* menu, const string& orderfile)
{
	if (menu != nullptr) {
		//the order file to find.
		path p(orderfile);
		if (exists(p)) {
			std::ifstream reader(p.string());
			//read the order file and order it.
			if (reader.is_open()) {
				vector<string> lines;
				string line;
				while (getline(reader, line))
				{
					lines.push_back(line);
				}
				reader.close();
				vector<MenuEntry*> newEntries;
				vector<MenuEntry*> entries = menu->getItems();
				//for each line, put the entry named that nex.
				for (int i = 0; i < lines.size(); i++) {
					string name = lines[i];
					int j = 0;
					//if it finds name at index, put it in new entries.
					while (j < entries.size()) {
						if (entries[j]->getName() == name) {
							newEntries.push_back(entries[j]);
							entries.erase(entries.begin() + j);
						} else {
							j++;
						}
					}
				}
				//copy over all items that weren't found in the order file.
				while (entries.size() > 0) {
					newEntries.push_back(entries[0]);
					entries.erase(entries.begin());
				}
				//set menu to the new list we made.
				menu->setItems(newEntries);
				//for (int i = 0; i < newEntries.size(); i++) {
					//cout << newEntries[i]->getName() << endl;
					//entries.push_back(newEntries[i]);
				//}
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

BashTutorial::BashTutorial()
{
	menu = new Menu("Bash Tutorial");
	loadTutorialsFromDirectory(TUTORIAL_DIRECTORY);
}

BashTutorial::BashTutorial(const string& tutorialDirectory) : BashTutorial()
{
	menu = new Menu("Bash Tutorial");
	this->loadTutorialsFromDirectory(tutorialDirectory);
}

BashTutorial::~BashTutorial()
{
	deleteTutorialsInMenu(menu);
	delete menu;
}

Tutorial* BashTutorial::selectTutorialMenu(SubMenu*& parentMenuToSet)
{
	//Menu selectionMenu("Tutorial Selection Menu");
	//for (int i = 0; i < availableTutorials.size(); i++) {
		//Tutorial* currentTutorial = availableTutorials[i];
		//if (currentTutorial != nullptr)
		//{
			//selectionMenu.addEntry(currentTutorial);
		//}
	//}
	//MenuEntry* userSelection = selectionMenu.getUserSelection();
	//Tutorial* selectedTutorial = dynamic_cast<Tutorial*>(userSelection);
	//assert(selectedTutorial != nullptr);
	//return selectedTutorial;
	MenuEntry* userSeletion = menu->getUserSelection(parentMenuToSet);
	Tutorial* asTutorial = dynamic_cast<Tutorial*>(userSeletion);
	//could be null
	//assert(asTutorial != nullptr);
	return asTutorial;
}

//vector<Tutorial*>& BashTutorial::getAvailableTutorials()
//{
	//return this->availableTutorials;
//}

bool BashTutorial::loadTutorialsFromDirectory(const string& tutorialDirectory)
{
	if (menu != nullptr) {
		deleteTutorialsInMenu(menu);
	}
	//delete menu;
	path dir(tutorialDirectory);
	if (menu == nullptr) {
		menu = new Menu("Bash Tutorial");
	}
	if (is_directory(dir)) {
		directory_iterator i(dir);
		directory_iterator end;
		for (; i != end; i++) {
			path p = i->path();
			if (is_regular_file(p)) {
				Tutorial* tut = new Tutorial();
				bool success = tut->loadFromFile(p.string());
				if (success) {
					menu->addEntry(tut);
				} else {
					delete tut;
				}
			} else {
				SubMenu* submenu = getTutorialsInDirectory(p.string(), menu);
				menu->addEntry(submenu);
			}
		} 
		//order with order file
		path p = dir / ORDER_FILE_NAME;
		orderWithFile(menu, p.string());
		return true;
	} else {
		return false;
	}

	//DIR* rootDir = opendir(tutorialDirectory.c_str());
	//if (rootDir != NULL) {
		//dirent* currentEntry;
		//while ((currentEntry = readdir(rootDir))) {
			//if (currentEntry->d_type == DT_REG) {
				//Tutorial* tutorial = new Tutorial();
				//int pathLength = tutorialDirectory.length() + strlen("/") + strlen(currentEntry->d_name);
				//char* path = new char[pathLength + 1];
				//strcpy(path, tutorialDirectory.c_str());
				//strcat(path, "/");
				//strcat(path, currentEntry->d_name);
				//cout << path << endl;
				//bool success;
				//success = tutorial->loadFromFile(path);
				//delete[] path;
				//if (success) {
					//availableTutorials.push_back(tutorial);
				//} else {
					////return false;
					////cout << "Error, couldn't load tutorial file " << path << endl;
					////
					////actually, I've decided that it will just ignore it and not throw any errors for now
				//}
			//}
		//}
		//closedir(rootDir);
	//}
	//return true;
}

void BashTutorial::startBashTutorial()
{
	//null parent menu, there isn't one.
	SubMenu* parentMenu;
	//get selected tutorial.
	Tutorial* selectedTutorial = selectTutorialMenu(parentMenu);
	if (selectedTutorial != nullptr) {
		//selectedTutorial->execute();
		this->executeTutorialFromEntry(selectedTutorial, parentMenu);
	}
}

bool BashTutorial::executeTutorialFromEntry(MenuEntry* startEntry, SubMenu* parent)
{
	//if there's no start entry, go up to parent directory.
	if (startEntry == nullptr) {
		if (parent) {
			if (parent->size() > 0) {
				startEntry = parent->getEntry(0);
			}
		}
	}
	//whether or not we went into a directoy and we have to print "done" at the end.
	bool wentIntoDirectory = false;
	if (startEntry != nullptr) {
		//if it's a normal tutorial entry, execute it.
		if (startEntry->isItemEntry()) {
			Tutorial* asTutorial = dynamic_cast<Tutorial*>(startEntry);
			if (asTutorial) {
				cout << "Would you like to start tutorial " << asTutorial->getName() << "? [y/n] ";
				bool answer = getYesNo();
				if (answer) {
					asTutorial->execute();
				}
			}
		//if it's not on, presumably a submenu, ask if they want to go into it and execute from first entry.
		} else {
			SubMenu* asSubMenu = dynamic_cast<SubMenu*>(startEntry);
			if (asSubMenu) {
				cout << "Would you like to go through tutorials in " << asSubMenu->getName() << "? [y/n] ";
				bool answer = getYesNo();
				if (answer) {
					if (asSubMenu->size() > 0) {
						executeTutorialFromEntry(asSubMenu->getEntry(0), asSubMenu);
					} else {
						executeTutorialFromEntry(nullptr, asSubMenu);
					}
					wentIntoDirectory = true;
				}

			}
		}
	}
	//now, iterate to the next entry and start from there, this is recursion.
	if ((parent != nullptr) && !wentIntoDirectory) {
		vector<MenuEntry*> entries = parent->getItems();
		auto i = std::find(entries.begin(), entries.end(), startEntry);
		//find it in parent
		if (i != entries.end()) {
			//get next entry
			i++;
			//if it's the last entry, execute from next entry, else, do a complicated thing to go up to parent directory.
			if (i != entries.end()) {
				executeTutorialFromEntry(*i, parent);
			} else {
				cout << "No more entries in " << parent->getName() << endl;
				//if the parent menu is null, that means we've gone through everything and need to end the program.
				if (parent->getParentMenu()) {
					cout << "Would you like to go up to " << parent->getParentMenu()->getName() << "? [y/n] " << endl;
					bool answer = getYesNo();
					if (answer) {
						executeTutorialFromEntry(parent, parent->getParentMenu());
					}
				} else {
					cout << "No parent menu, ending." << endl;
				}
			}
		}
	} else {
		cout << "No parent menu, ending." << endl;
	}
	return true;
}

Menu* BashTutorial::getMenu()
{
	return this->menu;
}
