#ifndef BASHTUTORIAL_H
#define BASHTUTORIAL_H

#include <vector>
#include <string>

#include "tutorial.h"
#include "menu.h"
#include "submenu.h"

using namespace std;


//allocates them with new delete with deleteTutorialsInMenu but also delete the menu itself afterwards
SubMenu* getTutorialsInDirectory(const string& tutorialDirectory, SubMenu* parentMenu=nullptr);
//deletes recursively, deletes everything, not just turials
void deleteTutorialsInMenu(SubMenu* menu);

class BashTutorial
{
	private:
		//list of all tutorials that are available
		//vector<Tutorial*> availableTutorials;
		Menu* menu;

	public:
		BashTutorial();
		BashTutorial(const string& tutorialDirectory);
		~BashTutorial();


		//scans all of the tutorial files in tutorialDirectory and loads them into availableTutorials
		//note, this deletes the old menu and makes a new one
		bool loadTutorialsFromDirectory(const string& tutorialDirectory);

		//method to have the user select a tutorial from a the current list
		Tutorial* selectTutorialMenu();
		//method to call to run the whole tutorial start to finish
		void startBashTutorial();


		//returns by reference
		//vector<Tutorial*>& getAvailableTutorials();
};

#endif
