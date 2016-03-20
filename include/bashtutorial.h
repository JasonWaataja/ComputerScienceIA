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

#ifndef BASHTUTORIAL_H
#define BASHTUTORIAL_H

#include <vector>
#include <string>

#include "tutorial.h"
#include "menu.h"
#include "submenu.h"

//where the tutorial files are located
#define TUTORIAL_DIRECTORY "tutorials"

//the name of the file that orders them.
#define ORDER_FILE_NAME ".tutorder"

using namespace std;

/*true for yes, false for no
note, any input that begins with y or n is a yes or no*/
bool getYesNo(const string& prompt);
bool getYesNo();

//allocates them with new delete with deleteTutorialsInMenu but also delete the menu itself afterwards
SubMenu* getTutorialsInDirectory(const string& tutorialDirectory, SubMenu* parentMenu=nullptr);
//deletes recursively, deletes everything, not just turials
void deleteTutorialsInMenu(SubMenu* menu);

//sets order in menu with the given order file, returns whether or not it succeded.
bool orderWithFile(SubMenu* menu, const string& orderfile);

/* main class for the BashTutorial program
   Contains the information for the tutorial, as well as the methods necessary for starting and managing it.
   startBashTutorial is called in BashTutorial's main function. */


class BashTutorial
{
	private:
		//list of all tutorials that are available
		//vector<Tutorial*> availableTutorials;
		Menu* menu;

	public:
		BashTutorial();
		//constructor accepting the root directory for all of the tutorial file, loads them.
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
