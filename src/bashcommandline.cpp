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
	stringstream promptStream;

	promptStream << "[" << this->username << "@" << this->computerName << " ";

	path currentDir = current_path();
	char* home;
	home = getenv("HOME");
	bool inHome = false;
	if (home) {
		if (currentDir == path(home)) {
			inHome = true;
		}
	}
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
	char* line = readline(prompt.c_str());
	string input = line;
	free(line);
	return input;
}

string BashCommandLine::getBashInputExpected(const string& expected, const string& incorrectMessage)
{
	string userInput;
	userInput = this->getBashInput();
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
	while (userInput != expected)
	{
		cout << incorrectMessage << endl;
		tries++;
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
