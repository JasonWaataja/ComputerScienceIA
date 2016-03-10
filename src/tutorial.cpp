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
	if (fileHasExtension(path, ".tut")) {

		ifstream reader;
		reader.open(path);
		if (reader.is_open()) {
			string line;
			//readds the first two lines and sets them to name and description, fails if can't be read.
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
