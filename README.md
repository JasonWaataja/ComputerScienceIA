# ComputerScienceIA

## Installation

The dependencies are Boost, GNU Readline and CMake.

On arch, run

`sudo pacman -S base-devel cmake boost boost-libs readline`

On Debian, Ubuntu, or other derivative, run

`sudo apt-get install build-essential cmake libboost-all-dev libreadline-dev`

Once you have the dependencies installed, you can build the program.

Create a folder to build in, the current directory is fine but it is recommended to make a directory called "build" in the project folder and build it there. To do this, run `mkdir build` and `cd build`.

Once you've navigated into the directory you want to build in, run cmake. To do this in build, run `cmake ..`. This should generate the build files for your system. To build it on most systems, just type `make`. There shouldn't be any errors, so let me know if there are.

This should create an executable called runbashtutorial. To run it, type `./runbashtutorial`. You're ready!
