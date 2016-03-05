#ifndef BASHTUTORIAL_H
#define BASHTUTORIAL_H

#include <vector>

#include "tutorial.h"

using namespace std;

class BashTutorial
{
	private:
		//list of all tutorials that are available
		vector<Tutorial*> availableTutorials;

		//scans all of the tutorial files in tutorialDirectory and loads them into availableTutorials
		void loadTutorialsFromDirectory(const char *tutorialDirectory);
	public:
		BashTutorial();
		BashTutorial(const char *tutorialDirectory);
		~BashTutorial();

		//method to have the user select a tutorial from a the current list
		Tutorial* selectTutorialMenu();
		//method to call to run the whole tutorial start to finish
		void startBashTutorial();

		//returns by reference
		vector<Tutorial*>& getAvailableTutorials();
};

#endif
