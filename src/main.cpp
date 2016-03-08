#include <iostream>
#include <functional>
#include <cstdlib>
//#include <unistd.h>
#include <readline/readline.h>



#include "bashtutorial.h"
#include "tutorial.h"
#include "menuentry.h"
#include "menu.h"
#include "tutorialaction.h"
#include "btfunctions.h"

using namespace std;

int main(int argc, char **argv)
{
	cout << "Hello BashTutorial" << endl;

	/*TutorialAction action("e echo hello > testfile.txt");
	char* currentDir = (char*) malloc(100);
	cout << getcwd(currentDir, 100) << endl;
	action.execute();
	cout << getcwd(currentDir, 100) << endl;
	free(currentDir);*/


	//Tutorial tut;
	//cout << tut.loadFromFile("tutorial.tut") << endl;
	//cout << tut.execute() << endl;

	BashTutorial tut("/home/jason/git/ComputerScienceIA/build");
	cout << "Constructed bash tutorial" << endl;
	Tutorial* st = tut.selectTutorialMenu();
	cout << "Finished selecting tutorial" << endl;
	cout << st << endl;



	/*BashTutorial bashTutorial;
	Tutorial testTutorial;
	bashTutorial.getAvailableTutorials().push_back(&testTutorial);
	Tutorial* selectedTutorial = bashTutorial.selectTutorialMenu();
	cout << selectedTutorial->getName() << endl;*/
}
