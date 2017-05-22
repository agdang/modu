# modu
A WIP rogulike made for Windows and Linux

# Repository Index
* /bin - Contains executables
* /build - Intermediate directory for visual studio
* /src - modu source
* /vs - Visual studio project folder

# Dependancies (Linux)
* libsdl2-dev

# Building

You can build modu on Windows a compiler of your choice. A Visual Studio 2017 project file is provided in /vs .

You will have to point whatever compiler you use to where your SDL /include and /lib folder is located. 

To build modu on linux you can use this command:
* g++ -o bin/linux/x86_64/modu src/*.cpp -lSDL2

And then to run modu:
* ./bin/linux/x86_64/modu
