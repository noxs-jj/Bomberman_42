# Bomberman Group Project @42Born2code
[![Build Status](https://travis-ci.org/noxsnono/Bomberman_42.svg?branch=master)](https://travis-ci.org/noxsnono/Bomberman_42)

![Screen Shot](https://raw.githubusercontent.com/noxsnono/Bomberman_42/ia/screenshot.gif)

## Requierements, Install
#### MacOsX (Supported & tested):
    - brew update && brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf
#### Linux (working on)
    - You ust install Drivers for use OpenGL 4.0 (open source libMesa only surpport OpenGL 3.2 at this moment), try to install owner's drivers, then install packages followings

    - sudo apt-get update && sudo apt-get install glee-dev libglew-dev libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

#### Windows (Not Supported)

## How to Play (Binding)
Key | Player 1 (Keyboard) | Player 2 (Keyboard)
------------ | ------------- | -------------
**UP** | S | 8
**DOWN** | W | 5
**LEFT** | A | 4
**RIGHT** | D | 6
**Bomb** | SPACE | 0

KEY | Player 3 (Joystick) | Player 4 (Keyboard)
------------ | ------------- | -------------
**UP** | Axis Y | S
**DOWN** | Axix Y | W
**LEFT** | Axix X | A
**RIGHT** | Axix X | D
**Bomb** | Button 1 | N

## Credits
Whois @42born2code | Jobs
------------ | -------------
rcargou  | 3D OpenGL engineer
vjacquie | Game Logic, Game Design
adjivas | IA engineer
nmohamed naki.md@gmail.com twitter@naki_md | Sound Design, input engineer
jmoiroux jjmoiroux@gmail.com twitter@jjmoiroux | Project Manager, Level Design, Game Design, Os Platform compatibility

#### Devs
event.class.cpp line 71

this->map = Mapparser::map_from_file(av[1]);

this->map = Mapparser::map_from_file(chemin_relatif);
