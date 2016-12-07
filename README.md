# Intermediate C++: Function Pointers

Function pointers are another way to solve the problem that functors solve.
While fuctors only exist in C++, function pointers exist in C, and are frequently used for callbacks.
This example covers the basics of declaring/using function pointers and their syntax.
It also shows usage of function pointers for member functions.

# Setup

You will need to have CMake installed on your computer, and properly added to your path.
In order to setup, run the following in a shell, then open the project in your preferred editor.
Windows setup has been configured for use with Visual Studio.

Windows:
```
cd path/to/folder
setup.cmd
```
Linux:
```
cd path/to/folder
./setup
```