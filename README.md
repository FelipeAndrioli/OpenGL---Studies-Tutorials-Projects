# OpenGL / GLFW / GLEW

This repository is a set of tutorial's, exercises and small projects to study OpenGL, GLFW and GLEW. 

## Requirements

MinGW
GLFW
GLEW
Shell

## Directories

The directory "tutorial" was maded following the Sonar Systems tutorial. Inside the directory contains a subdirectory named open_window, the main.cpp file contain a explanation about the principal configuration functions used in all the tutorials.

## How to compile

To compile just execute the file 'scripts/compile_run.sh' in the same directory that contains the main.cpp flie.

## How to run it through MinGW

After tough hours of research I find out how to execute the whole code througth MinGW and not through Visual Studio Code as the majority of tutorials.

https://github.com/SonarSystems/OpenGL-Tutorials

We are going to need these files:

	- include/GLFW/glfw3
	- include/GLFW/glfw3native
	- include/GLEW/glew
	- GLFW/lib/libglfw3.a
	- GLEW/lib/Release/Win32/glew32.lib

Now we need to paste the files in the following directories:

	- C:/MinGW/include/GLFW/glfw3
	- C:/MinGW/include/GLFW/glfw3native
	- C:/MinGW/include/GL/glew
	- C:/MinGW/lib/libglfw3.a
	- C:/MinGW/lib/glew32.lib

After that we just need to compile our code with the correct links, this is what I am using to compile my code:

	g++ test.cpp -o test.exe -lglfw3 -lopengl32 -lgdi32 

You can give a look in the script I am using to compile and use it as base to create your own.

## TODO's

	- Transform the create window into a header