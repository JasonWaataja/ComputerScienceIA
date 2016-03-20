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

#include "btfunctions.h"

#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

bool btcd(const string& newDirectory)
{
	//int status = chdir(newDirectory.c_str());
	path p(newDirectory);
	if (!is_directory(p)) {
		return false;
	}
	try {
		boost::filesystem::current_path(newDirectory);
		return true;
	} catch (...) {
		return false;
	}
}

bool blankFunction()
{
	return false;
}

function<bool()> getBtFunction(const string& name, int argc, char** argv)
{
	function<bool()> btFunction;
	//checks if it's btcd
	if (name == "btcd") {
		if (argc >= 1) {
			//note, I try to have it copy it into a new string so the argument is still around
			string newDir = argv[0];
			btFunction = [newDir](){return btcd(newDir);};
		} else {
			cerr << "Error, btcd required at least one argument" << endl;
			btFunction = blankFunction;
		}
	} else {
		//return blank function
		btFunction = blankFunction;
	}
	return btFunction;
}
