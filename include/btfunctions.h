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

#ifndef BTFUNCTIONS_H
#define BTFUNCTIONS_H

#include <string>
#include <functional>
#include <iostream>

/* This file contains all of the functions that are used in the BashTutorial language.
   Currently, "cd" is the only function replicated here that isn't in the TutorialAction file. */

using namespace std;

//bt cd function, calls glibc chdir internally
bool btcd(const string& newDirectory);

//blank function that always fails
bool blankFunction();

//returns pointer to the function corresponding to the string, returns null if could not be found
function<bool()> getBtFunction(const string& name, int argc, char** argv);

#endif
