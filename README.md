# modu
A WIP rogulike made for Windows and Linux

# Repository Index
* /bin - Contains executables
* /build - Intermediate directory for visual studio
* /include - Included files from SDL
* /lib - Library files from SDL
* /src - modu source
* /vs - Visual studio project folder

# Dependancies (Linux)
* libsdl2-dev

# Building

You can build modu on Windows using the Visual Studio 2017 project file provided in /vs .

If you use another compiler, you will have to point it to the SDL source and libraries located in /include and /lib .  

To build modu on linux you can use this command:
* g++ -o bin/linux/x86_64/modu src/*.cpp -lSDL2

And then to run modu:
* ./bin/linux/x86_64/modu
