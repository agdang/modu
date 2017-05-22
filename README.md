# modu
A WIP rogulike made for Windows and Linux

# Repository Index
* /bin - Contains executables
* /src - modu source

# Building (Windows)

You can build modu on Windows with a compiler of your choice.

You will have to point whatever compiler you use to where your SDL /include and /lib folder is located. 

# Building (Linux)

## Dependancies (Linux)
* libsdl2-dev

To build modu on linux you can use this command:
* g++ -o bin/linux/x86_64/modu src/*.cpp -lSDL2

And then to run modu:
* ./bin/linux/x86_64/modu
