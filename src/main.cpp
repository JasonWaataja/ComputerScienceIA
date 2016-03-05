#include <iostream>
#include <readline/readline.h>
#include "bashtutorial.h"
#include "tutorial.h"
#include "menuentry.h"
#include "menu.h"

using namespace std;

int main(int argc, char **argv)
{
	cout << "Hello BashTutorial" << endl;
	BashTutorial bashTutorial;
	Tutorial testTutorial;
	bashTutorial.getAvailableTutorials().push_back(&testTutorial);
	Tutorial* selectedTutorial = bashTutorial.selectTutorialMenu();
	cout << selectedTutorial->getName() << endl;
}
