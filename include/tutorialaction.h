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

/* Class that represents one action that a tutorial can do.
   Something like print or get input. */
class TutorialAction
{
	public:
		//returns false if failed
		function<bool()> action;

		//default constructor that uses a dummy action.
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
