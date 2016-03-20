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


#ifndef BASHCOMMANDLINE_H
#define BASHCOMMANDLINE_H

#include <string>

#define MISTAKE_COUNT_HINT 5

using namespace std;

/* BashCommandLine is a class that gets basic input from the command line using cin and cout.
   It also supports expected inputs and errors until the user inputs the correct one. */
class BashCommandLine
{
	private:
		//the name to be displayed on command line.
		string username;
		//the name of the computer to be displayed on the command line
		string computerName;

	public:
		BashCommandLine();
		//constructor that sets the username and computer name
		BashCommandLine(const string& username, const string& computerName);
		~BashCommandLine();

		//returns the prompt to be used at the beginning of the line in the form [username@computerName currentDirectory]
		string getPrompt();


		//gets the user input with a bash-like command line
		string getBashInput();
		//errors until the user enters the correct input, gives a hint after MISTAKE_COUNT_HINT incorrect guessed
		string getBashInputExpected(const string& expected, const string& incorrectMessage = "Incorrect, try again");
		//after MISTAKE_COUNT_HINT mistakes, starts printing the error message and the hint message
		string getBashInputExpected(const string& expected, const string& incorrectMessage, const string& hintMessage);

		//getters and setters for username and computerName
		string getUsername() const;
		void setUsername(const string& username);
		string getComputerName() const;
		void setComputerName(const string& computerName);
};

#endif
