#include "bashtutorial.h"

//#include <iostream>
#include <cassert>
#include <dirent.h>
#include <sys/types.h>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "menu.h"
#include "tutorial.h"

using namespace std;

BashTutorial::BashTutorial()
{
}

BashTutorial::BashTutorial(const string& tutorialDirectory)
{
	this->loadTutorialsFromDirectory(tutorialDirectory);
}

BashTutorial::~BashTutorial()
{
	for (int i = 0; i < availableTutorials.size(); i++) {
		delete availableTutorials[i];
	}
}

Tutorial* BashTutorial::selectTutorialMenu()
{
	Menu selectionMenu("Tutorial Selection Menu");
	for (int i = 0; i < availableTutorials.size(); i++) {
		Tutorial* currentTutorial = availableTutorials[i];
		if (currentTutorial != nullptr)
		{
			selectionMenu.addEntry(currentTutorial);
		}
	}
	MenuEntry* userSelection = selectionMenu.getUserSelection();
	Tutorial* selectedTutorial = dynamic_cast<Tutorial*>(userSelection);
	assert(selectedTutorial != nullptr);
	return selectedTutorial;
}

vector<Tutorial*>& BashTutorial::getAvailableTutorials()
{
	return this->availableTutorials;
}

bool BashTutorial::loadTutorialsFromDirectory(const string& tutorialDirectory)
{
	DIR* rootDir = opendir(tutorialDirectory.c_str());
	if (rootDir != NULL) {
		dirent* currentEntry;
		while ((currentEntry = readdir(rootDir))) {
			if (currentEntry->d_type == DT_REG) {
				Tutorial* tutorial = new Tutorial();
				int pathLength = tutorialDirectory.length() + strlen("/") + strlen(currentEntry->d_name);
				char* path = new char[pathLength + 1];
				strcpy(path, tutorialDirectory.c_str());
				strcat(path, "/");
				strcat(path, currentEntry->d_name);
				cout << path << endl;
				bool success;
				success = tutorial->loadFromFile(path);
				delete[] path;
				if (success) {
					availableTutorials.push_back(tutorial);
				} else {
					//return false;
					//cout << "Error, couldn't load tutorial file " << path << endl;
					//
					//actually, I've decided that it will just ignore it and not throw any errors for now
				}
			}
		}
		closedir(rootDir);
	}
	return true;
}

void BashTutorial::startBashTutorial()
{
	Tutorial* selectedTutorial = selectTutorialMenu();
	if (selectedTutorial != nullptr) {
		selectedTutorial->execute();
	}
}
