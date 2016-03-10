#ifndef TUTORIALACTION_H
#define TUTORIALACTION_H

#include <functional>
#include <string>

using namespace std;

//might change on OS, for now on linux, it just calls "system()"
bool executeWithBash(const string& command);

//gets whether or not the current character is escaped with "\"
bool isEscaped(const string& s, int i);

//-1 if none found, stores it in "quote", else it returns the position after the second quote
int findQuoted(const string& parameter, string& quote, int start = 0);

//the parameter is the line after "ge " supposedly
function<bool()> getGeFunction(const string& parameter);

//same as above, except executes the thing as well
function<bool()> getGeeFunction(const string& parameter);


class TutorialAction
{
	public:
		//returns false if failed
		function<bool()> action;

		TutorialAction();
		TutorialAction(const function<bool()>& action);
		//loads from string
		TutorialAction(const string& line);

		//returns false if failed
		bool loadFromString(const string& line);

		//returns false if failed
		bool execute();
};

#endif
