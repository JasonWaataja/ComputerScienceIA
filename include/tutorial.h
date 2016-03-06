#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <string>
#include <vector>

#include "menuentry.h"
#include "tutorialaction.h"

using namespace std;

//This function is case senstive
bool fileHasExtension(const string& path, const string& extension);

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

		string getCommandName() const;
		void setCommandName(const string &commandName);

		bool execute();


};

#endif
