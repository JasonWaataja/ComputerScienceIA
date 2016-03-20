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

#include "tutorial.h"

#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>

#include "tutorialaction.h"

using namespace std;

bool fileHasExtension(const string& path, const string& e)
{
	return boost::filesystem::extension(path) == e;
}

Tutorial::Tutorial() : MenuEntry("Tutorial", "a tutorial")
{
}

Tutorial::~Tutorial()
{
	for (int i = 0; i < actionList.size(); i++) {
		delete actionList[i];
	}
}

bool Tutorial::loadFromFile(const string& path)
{
	//if it's a .tut file, load it.
	if (fileHasExtension(path, ".tut")) {

		ifstream reader;
		reader.open(path);
		if (reader.is_open()) {
			string line;
			//reads the first two lines and sets them to name and description, fails if can't be read.
			if (getline(reader, line)) {
				this->setName(line);
				if (getline(reader, line)) {
					this->setDescription(line);
				} else {
					return false;
				}
			} else {
				return false;
			}
			while (getline(reader, line)) {
				//uses default constructor so it can check for errors
				//TutorialAction* action = new TutorialAction(line);
				TutorialAction* action = new TutorialAction();
				bool success = action->loadFromString(line);
				if (!success) {
					delete action;
					//return false;
				} else {
					actionList.push_back(action);
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

string Tutorial::getCommandName() const
{
	return this->commandName;
}

void Tutorial::setCommandName(const string& commandName)
{
	this->commandName = commandName;
}

bool Tutorial::execute() {
	//for each ection, execute it.
	for (int i = 0; i < actionList.size(); i++) {
		//cout << i << endl;
		bool success;
		success = actionList[i]->execute();
		//cout << success << endl;
		if (!success)
			return false;
	}
	return true;
}
