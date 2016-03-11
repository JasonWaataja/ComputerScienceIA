#ifndef BASHTUTORIAL_H
#define BASHTUTORIAL_H

#include <vector>
#include <string>

#include "tutorial.h"
#include "menu.h"
#include "submenu.h"

//where the tutorial files are located
#define TUTORIAL_DIRECTORY "tutorials"

using namespace std;

//true for yes, false for no
//note, any input that begins with y or n is a yes or no
bool getYesNo(const string& prompt);
bool getYesNo();

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

		//method to have the user select a tutorial from a the current list, stores the parent menu in parentMenu;
		Tutorial* selectTutorialMenu(SubMenu*& parentMenuToSet);
		//method to call to run the whole tutorial start to finish
		void startBashTutorial();

		//uses parent directories and std::find to loop over all of the entries in the directory
		//note, this fails if the same pointer is in the list twice.
		bool executeTutorialFromEntry(MenuEntry* startEntry, SubMenu* parent);

		Menu* getMenu();


		//returns by reference
		//vector<Tutorial*>& getAvailableTutorials();
};

#endif
