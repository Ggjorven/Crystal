---
title: Main page
layout: template
filename: README.md
--- 

# Crystal Game Engine

Crystal is an ambitious game engine that combines the power of OpenGL and Vulkan to provide a versatile platform for game development. It is currently in its early stages of development and is considered very bare-bones. However, it holds great promise and is under constant, heavy development, making it an exciting project for game developers looking to shape its future.

## Features

- **Graphics Rendering:** Crystal leverages both OpenGL and Vulkan, allowing developers to choose the rendering technology that best suits their needs. This flexibility is crucial for optimizing graphics performance.

- **User Interface Development:** The engine comes equipped with ImGui, a highly customizable, immediate mode graphical user interface library. ImGui makes it easy for developers to create in-game user interfaces and debug tools.

- **Window Management:** Crystal relies on GLFW for window management, providing cross-platform support for creating windows and handling user input.

- **Mathematics:** For vector and matrix mathematics, Crystal utilizes glm, a popular mathematics library that simplifies the development of graphics applications.

- **OpenGL Extension Wrangler (GLEW):** GLEW is integrated into Crystal to simplify the management of OpenGL extensions and ensure compatibility across different hardware and platforms.

## How to use

- **First of all:** Make sure you have the Vulkan SDK installed.

- **Visual Studio 2022:** Run the "Win-Gen-Projects.bat" in the scripts folder. There should now be a Crystal.sln file in the root of repository.

- **Other:** You can also use other compilers such as g++ or gcc. To do so you should compile all the src directories found in "Crystal" and all of the vendor src directories. Make sure to compile the Core and Physics and the vendor apps to a .lib file, Crystalizer can be compiled to a .exe, don't forget to link the .lib files to these.

- **Running/Compiling a project:** To run a project you can go to the Editor.hpp in Crystalizer and set the project path member variable to your project and just run Crystalizer.

## Development Status

As of [9/10/2023], Crystal is in active development. It's important to note that it is a work in progress and requires significant effort to reach its full potential. The development community around Crystal is highly encouraged to contribute, report issues, and help shape the future of this game engine.

## Contribution

If you are interested in contributing to the Crystal Game Engine project, please send me a message on [Discord](https://discord.com/) (ggjorven#0914) for more information on how to get involved.

## Copyright

© [2023] [Jorben van der Wal] (ggjorven)
