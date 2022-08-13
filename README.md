# Direct Volume Renderer

This repository contains an implementation of a basic direct volume renderer using C++ and OpenGL. 
Currently supports only volumes in the same file format as the bonsai files found in `DVR/data`.

## Building

Officially supports Windows 10 and Visual Studio 2022. To build the project, do the following steps:

1. Clone the repository recursively with the command: `git clone --recursive https://github.com/daniisovich/volume_renderer`
2. Run `scripts/generate.bat`
3. Open `DVR.sln` and build the project in Visual Studio using your preferred configuration

## Running

You can also run the project without building by running the executable in the `run` folder.

## Controls

You can close the program by pressing `Escape`. With the `left mouse button`, the view is rotated. `R` resets the view, and you can change the smooth step start and end value with the `arrow keys`.
