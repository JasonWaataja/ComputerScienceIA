#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <string>

#include "menuentry.h"

using namespace std;

//This function is case senstive
bool fileHasExtension(const string& path, const string& extension);

class Tutorial: public MenuEntry
{
	private:
		//name of command that this tutorial teaches, can be blank or "none"
		string commandName;

	public:
		//basic constructor + destructor
		Tutorial();
		~Tutorial();

		bool loadFromFile(const string& path);
		bool loadFromFolder(const string& path);

		string getCommandName() const;
		void setCommandName(const string &commandName);


};

#endif
