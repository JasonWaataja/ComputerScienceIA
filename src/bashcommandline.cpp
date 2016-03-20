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

#include "bashcommandline.h"

#include <readline/readline.h>
#include <boost/filesystem.hpp>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace boost::filesystem;
using namespace std;


BashCommandLine::BashCommandLine() : username("user"), computerName("computer")
{
	//rl_readline_name = "BashCommandLine";
	//more stuff here
}

BashCommandLine::BashCommandLine(const string& username, const string& computerName) : username(username), computerName(computerName)
{
}

BashCommandLine::~BashCommandLine()
{
}

string BashCommandLine::getPrompt()
{
	//stream to add all of the elements on
	stringstream promptStream;

	//puts on username and computer name.
	promptStream << "[" << this->username << "@" << this->computerName << " ";

	//put on name of current directory.
	path currentDir = current_path();
	char* home;
	home = getenv("HOME");
	bool inHome = false;
	if (home) {
		if (currentDir == path(home)) {
			inHome = true;
		}
	}
	//if we're in the home directory, use "~"
	if (inHome)
		promptStream << "~";
	else
		promptStream << currentDir.filename().string();

	promptStream << "]$ ";
	return promptStream.str();
}

string BashCommandLine::getBashInput()
{
	string prompt = this->getPrompt();
	//calls the GNU Readline function readline with the given prompt.
	char* line = readline(prompt.c_str());
	string input = line;
	free(line);
	return input;
}

string BashCommandLine::getBashInputExpected(const string& expected, const string& incorrectMessage)
{
	string userInput;
	userInput = this->getBashInput();
	//loop until the user enters the correct one, no hint.
	while (userInput != expected)
	{
		cout << incorrectMessage << endl;
		userInput = this->getBashInput();
	}
	return userInput;
}

string BashCommandLine::getBashInputExpected(const string& expected, const string& incorrectMessage, const string& hintMessage)
{
	string userInput;
	userInput = this->getBashInput();
	int tries = 0;
	//loop until the user enters the correct input.
	while (userInput != expected)
	{
		cout << incorrectMessage << endl;
		tries++;
		//if the amount of tries is too high, print out the hint message.
		if (tries >= MISTAKE_COUNT_HINT) {
			cout << hintMessage << endl;
		}
		userInput = this->getBashInput();
	}
	return userInput;
}

string BashCommandLine::getUsername() const
{
	return this->username;
}

void BashCommandLine::setUsername(const string& username)
{
	this->username = username;
}

string BashCommandLine::getComputerName() const
{
	return this->computerName;
}

void BashCommandLine::setComputerName(const string& computerName)
{
	this->computerName = computerName;
}
