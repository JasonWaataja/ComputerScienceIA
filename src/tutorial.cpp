#include "tutorial.h"

#include <fstream>
#include <iostream>

#include "tutorialaction.h"

using namespace std;

bool fileHasExtension(const string& path, const string& extension)
{
	size_t extensionPos = path.find_last_of(".") + 1;
	//if there's not dot
	if (extensionPos == string::npos) {
		return false;
	} else {
		string fileExtension = path.substr(extensionPos, path.length() - extensionPos);
		if (fileExtension == extension) {
			return true;
		} else {
			return false;
		}
	}
}

Tutorial::Tutorial() : MenuEntry("Tutorial", "a tutorial")
{
}

Tutorial::~Tutorial()
{
	cout << "Running tutorial destructor" << endl;
	for (int i = 0; i < actionList.size(); i++) {
		delete actionList[i];
	}
	cout << "About to finish running destructor in tutorial" << endl;
}

bool Tutorial::loadFromFile(const string& path)
{
	if (fileHasExtension(path, "tut")) {

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
				TutorialAction* action = new TutorialAction(line);
				bool success = action->loadFromString(line);
				if (!success) {
					return false;
				}
				actionList.push_back(action);
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
		bool success;
		success = actionList[i]->execute();
		if (!success)
			return false;
	}
	return true;
}
