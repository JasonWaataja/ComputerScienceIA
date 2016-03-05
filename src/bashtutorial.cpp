#include "bashtutorial.h"

//#include <iostream>
#include <cassert>

#include "menu.h"
#include "tutorial.h"

BashTutorial::BashTutorial()
{
}

BashTutorial::BashTutorial(const char* tutorialDirectory)
{
}

BashTutorial::~BashTutorial()
{
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
