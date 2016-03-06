#include <iostream>
#include <functional>
#include <cstdlib>
#include <unistd.h>
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

	TutorialAction action("print hello world");
	char* currentDir = (char*) malloc(100);
	cout << getcwd(currentDir, 100) << endl;
	action.execute();
	cout << getcwd(currentDir, 100) << endl;
	free(currentDir);
	


	/*BashTutorial bashTutorial;
	Tutorial testTutorial;
	bashTutorial.getAvailableTutorials().push_back(&testTutorial);
	Tutorial* selectedTutorial = bashTutorial.selectTutorialMenu();
	cout << selectedTutorial->getName() << endl;*/
}
