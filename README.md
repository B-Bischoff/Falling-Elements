# Falling-Elements

This is an interactive simulation game where you can create and manipulate different types of particles on a virtual grid.

## Features
* Multiple particles types: Each particle have custom behavior and interactions.
* Velocity and temperature simulation: The particles in the game will react to the velocity and temperature of the environment.
* Property filters: The game allows player to clearly see the impact of the velocity and temperature on the particles by using color coding.

https://user-images.githubusercontent.com/79707661/215260173-3cbe5893-092e-43ed-9df8-e04c1b8ab73c.mp4

## Documentation

You can find the project documentation (in french) with the link below :

https://b-bischoff.github.io/web/falling-elements.html

## Installation

### Linux
Make sure CMake, Git and GCC are installed by typing ```sudo apt-get install cmake git g++```

You may also need to install the required packages : 
```sudo apt-get install libsoil-dev libglm-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev libxi-dev libfreetype-dev libgl1-mesa-dev xorg-dev freeglut3-dev```

To install, build and start the application, type the following commands:

```git clone git@github.com:B-Bischoff/Falling-Elements.git && cd Falling-Elements```

```mkdir build```

```cmake -S . -B build```

```make -C build```

```./build/Falling-Elements```


### Windows
Using Visual Studio you can execute the "CMakeLists.txt" script to build and start the application.
