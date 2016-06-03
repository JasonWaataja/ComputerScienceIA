# BashTutorial

A program for Linux/Unix which teaches the user how to use a command line interface, specifically BASH, or the Bourne Again SHell. By the end of these tutorials, the user should have a basic understanding of the commands for operating a Unix-like system. The program also supports writing your own tutorials which can be for any command.

## Installation

BashTutorial is installed and run from the command line. Start by opening a terminal. Try searching for "terminal" in your OS or starting your favorite terminal emulator.

You might not have git installed, so do that. On Arch Linux, run `sudo pacman -S git` and on Ubuntu, run `sudo apt-get install git`. Then, clone this repository. If you don't know how to do this, follow these instructions. Type `mkdir git`, `cd git`, `git clone https://github.com/JasonWaataja/ComputerScienceIA.git`. Then, navigate into the directory with `cd ComputerScienceIA`.

The dependencies are Boost, GNU Readline and CMake.

On Arch Linux, run

`sudo pacman -S base-devel cmake boost boost-libs readline`

On Debian, Ubuntu, or other derivative, run

`sudo apt-get install build-essential cmake libboost-all-dev libreadline-dev`

Once you have the dependencies installed, you can build the program.

Create a folder to build in, the current directory is fine but it is recommended to make a directory called "build" in the project folder and build it there. To do this, run `mkdir build` and `cd build`.

Once you've navigated into the directory you want to build in, run cmake. To do this in build, run `cmake ..`. This should generate the build files for your system. To build it on most systems, just type `make`. There shouldn't be any errors, so let me know if there are.

This should create an executable called runbashtutorial. To run it, type `./runbashtutorial`. You're ready!

## Usage

Running the program, you should be greeted with a menu. You can navigate it by typing the number of the item you want to select. It is recommended if the user has no experience with the command line that they start the first tutorial firse. If the user wishes to be reminded of a specific tutorial, they can navigate into one of the directories and start it. Finishing any tutorial automatically prompts the user as to if they would like to do the next one. All of the tutorials can be done in sequence this way.

### Writing Tutorials

The program automatically searches the "tutorials" directory, so you can add or change the tutorials by modifying this folder. Tutorial files end in ".tut" and placing one in a directory will make the program see it when run.

The first line of the tutorial file is the name of the tutorial and the second line is the description. After that, any lines are interpreted as commands for the tutorial.

The most commands are "p", "w", and "pw" which print the rest of the line, wait until the user presses enter, and both of those respectively.

"g" gets the use input. "ge" gets user input with an expected value. The first argument is the expected input in quotes. The second is the message if the user gives the wrong input. This is also quoted. The optional last argument is the hint to be printed if the user gets it wrong too many times.

"gee" will be the most common, though, and is the same as "ge" with the exception that it also executes the command afterwards. This is useful for showing the output of a command.

There are also "bt" functins which manipulate the tutorial program itself. For now, the only one is "btcd" which allows you to change directories as if you're using "cd". This is useful for making sure commands dependent on the current directory work correctly as even it you call a cd command with "gee" which doesn't change the current directory for the program.

To run an arbitrary command, use "e" which executes the command contained in the rest of the line.

If you want to make sure that the tutorials are ordered correctly in the menus, every directory may contain a ".tutorder" file which is read and used to order the items in the menu. The tutorials and directories are ordered according to the order their names appear in the file on individual lines. You can also include directory names.
