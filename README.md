# Trinity

## Overview
Trinity is a game demo for in-house DirectX 11 engine called TrinityEngine and save files will be managed using rapidjson. This game will showcase the nature simulation and realistic animal behviours in different terrains and conditions.
This is work in progress and more will be updated weekly. 

## Project Status
Trinity is currently in early stage with some features such as level editor, creature editor and a short demo of simple procedural map generation in main game.

Known issues:
* Heap corruption which affects the .exe file functionality, but the debug demonstration in Visual Studio will not be affected
* Minor UI highlight overlap will be affected due to some input changes between keyboard and mouse
* UI in the Creature Editor and Map Editor levels will be locked to keyboard control only

## Requirements

1. Visual Studio 2019

## Setting up your game

1. Clone this repo: `git clone https://github.com/tieuchanlong/TrinityEngine` into some folder like TrinityDemo (name doesn't matter)
2. Clone this repo: `git clone https://github.com/tieuchanlong/Trinity` into the same folder as TrinityDemo
3. Navigate to folder `Trinity\Trinity\assets` and run BuildPC.bat file
4. Open project Trinity.sln in `Trinity` folder with Visual Studio 2019 and set it to configuration Debug-x64.
5. Set Trinity as start up project and starts debugging. Any error can be skipped using F5, future patches will fix those errors.

## Video Demo

You can also view a video of the game demo from [here](https://drive.google.com/file/d/1hTUAlbKLin6nEQldu-iRcRYgb9prxzKs/view?usp=sharing).
![](TrinityEngineDemo.gif)
