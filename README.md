# Bomberman Group Project @42Born2code
[![Build Status](https://travis-ci.org/noxsnono/Bomberman_42.svg?branch=master)](https://travis-ci.org/noxsnono/Bomberman_42)

![Screen Shot](https://raw.githubusercontent.com/noxsnono/Bomberman_42/ia/screenshot.gif)

## Requierements, Install
### MacOsX (Supported & tested):
    - brew update && brew install sdl sdl2 sdl2_image sdl2_mixer sdl2_ttf
### Linux (Supported & tested)
    - You must install Drivers for use OpenGL 4.0 (open source libMesa
	only surpport OpenGL 3.2 at this moment), try to install owner's drivers,
	then install packages followings

    sudo apt-get update && sudo apt-get install glee-dev libglew-dev \
    libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev \
    libsdl2-ttf-dev freeglut3-dev libsdl1.2-dev

### Documentation -man-
How to add man game manuel to manpath.
```
git clone https://github.com/noxsnono/Bomberman_42.git bomberman
export MANPATH=$(manpath):bomberman/man
```

### Windows (Not Supported)

## How to Play (Binding)
Key | Joystick | Keyboard1 | Keyboard2
------------ | ------------- | ------------- | -------------
**UP** | UP | W | 8
**DOWN** | DOWN | S | 5
**LEFT** | LEFT | A | 4
**RIGHT** | RIGHT | D | 6
**Bomb normal** | Button 3 | C | +
**Bomb remote** | Button 2 | V | -
**Activate remote bombs** | Button 1 | B | *

## Developers
- Une fois une partie campaing lance, revenir au menu principal et appuyer sur '1' pour passer au niveau suivant
- Au lancement du jeux, au menu principal (sans partie en cours) appuyer sur '2' pour lancer la maps tests/test1.ntm
- Une fois une partie lancer en Multi, revenir au menu et appuyer sur '3' pour activer toutes les bombes, puissance max, et remote bomb illimtite


## Credits
Whois @42born2code | Jobs
------------ | -------------
rcargou  | 3D OpenGL engineer, assets 3D, textures
vjacquie | Game Logic, Game Design, input engineer
adjivas | IA engineer, Documentation wirter 'man'
nmohamed naki.md@gmail.com twitter@naki_md | Sound Design, input engineer
jmoiroux jjmoiroux@gmail.com twitter@jjmoiroux | Project Manager, Os Platform compatibility, Level Design, Game Design, textures
