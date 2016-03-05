#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <string>

#include "menuentry.h"

using namespace std;

class Tutorial: public MenuEntry
{
	private:
		//name of command that this tutorial teaches, can be blank or "none"
		string commandName;

	public:
		//basic constructor + destructor
		Tutorial();
		~Tutorial();

		string getCommandName() const;
		void setCommandName(const string &commandName);


};

#endif
