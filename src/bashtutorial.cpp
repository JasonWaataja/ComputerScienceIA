#include "bashtutorial.h"

//#include <iostream>
#include <cassert>
//#include <dirent.h>
//#include <sys/types.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <boost/filesystem.hpp>

#include "menu.h"
#include "tutorial.h"

using namespace std;
using namespace boost::filesystem;

SubMenu* getTutorialsInDirectory(const string& tutorialDirectory, SubMenu* parentMenu)
{
	path dir(tutorialDirectory);
	SubMenu* menu = new SubMenu("Menu", dir.filename().string(), parentMenu);
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
	}
	return menu;
}

void deleteTutorialsInMenu(SubMenu* menu)
{
	for (int i = 0; i < menu->size(); i++) {
		MenuEntry* entry;
		entry = menu->getEntry(i);
		if (entry->isMenuEntry()) {
			SubMenu* asSubMenu = dynamic_cast<SubMenu*>(entry);
			if (asSubMenu) {
				deleteTutorialsInMenu(asSubMenu);
			}
		}
		delete entry;
	}
}

BashTutorial::BashTutorial()
{
	menu = new Menu("Bash Tutorial");
}

BashTutorial::BashTutorial(const string& tutorialDirectory) : BashTutorial()
{
	this->loadTutorialsFromDirectory(tutorialDirectory);
}

BashTutorial::~BashTutorial()
{
	deleteTutorialsInMenu(menu);
	delete menu;
}

Tutorial* BashTutorial::selectTutorialMenu()
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
	MenuEntry* userSeletion = menu->getUserSelection();
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
	delete menu;
	path dir(tutorialDirectory);
	menu = new Menu("Bash Tutorial");
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
	Tutorial* selectedTutorial = selectTutorialMenu();
	if (selectedTutorial != nullptr) {
		selectedTutorial->execute();
	}
}
