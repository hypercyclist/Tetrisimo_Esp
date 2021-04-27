# Tetrisimo ESP
## Physical Tetris clone with online game mechanics
Development of a Tetris clone game for a miniature physical copy of the Super Brick Game console with multiplayer and color graphics support.
The game can be played alone or together with friends.
The maximum number of players in a match is two, the limits are set based on the size of the screen.
## Features
- A flexible level of difficulty of the game allowing everyone to play at their own pace.
- The possibility to play online both nearby and in different places.
- The table of records of other players.
- Variety of game settings, including setting the basic color tones of the game, figures.

## Code compilation
The source code writen for ESP-12E, ESP8266 board with TFT display.
ESP8266 firmware upload over USB.
ESP-12E firmware upload scheme can be viewed in the repository named #Boards#.
The code uses the features of C++14 and needs to update standart tools kind of Arduino IDE.
Now there is no task to write graphics for all sizes of displays, but I try to build a graphics subsystem like in Qt.
The layout of the console board based on ESP-12E can be viewed in the repository named #Boards#.

## Demonstration
The first prototype based on Arduino Nano board.
The layout of the console board based on Arduino can be viewed in the repository named #Boards#.

[![Video](https://i9.ytimg.com/vi_webp/la7uFopkpTI/mqdefault.webp?time=1619546400000&sqp=CKCioYQG&rs=AOn4CLDpB5J-U1GuBkFMUynAI8gDJYxp3A)](https://youtu.be/la7uFopkpTI)