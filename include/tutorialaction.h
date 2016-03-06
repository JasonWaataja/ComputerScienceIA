#ifndef TUTORIALACTION_H
#define TUTORIALACTION_H

#include <functional>
#include <string>

using namespace std;

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
