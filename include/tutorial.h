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

#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <string>
#include <vector>

#include "menuentry.h"
#include "tutorialaction.h"

using namespace std;

//This function is case senstive
bool fileHasExtension(const string& path, const string& extension);

/* A MenuEntry that represents a tutorial.
   Contains a list of commands to execute and can be loaded from file. */
class Tutorial: public MenuEntry
{
	private:
		//name of command that this tutorial teaches, can be blank or "none"
		string commandName;
		
		//list of commands to execute
		vector<TutorialAction*> actionList;

	public:
		//basic constructor + destructor
		Tutorial();
		~Tutorial();

		//note, this doesn't delete the current tutorials loaded, each call appends to existing.
		bool loadFromFile(const string& path);

		//getters and setters for commandName
		string getCommandName() const;
		void setCommandName(const string &commandName);

		/*runs all of the actions in actionList in sequence.
		returns false if any tutorial actions return false.*/
		bool execute();


};

#endif
