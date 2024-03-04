#include <iostream>
#include "system/ScreenBuffer.h"

int main() {

    ScreenBuffer screenBuffer;
    screenBuffer.Init();
    screenBuffer.CursorOff();
    screenBuffer.SetString(0,0,"RetroBasic 0.1");
    screenBuffer.SetString(1, 0, "Ready!");
    screenBuffer.SetString(2, 0, ">");
    screenBuffer.NewLine();
    screenBuffer.SetString("Testing other color", CH_NORMAL, 50,47,12,100,200,190);
    screenBuffer.SetString(10, 30, "Inverted", CH_INVERTED);
    screenBuffer.SetString(12, 10, "This irritates too much!", CH_BLINKING);

    while(screenBuffer.window.isOpen())
    {
        sf::Event event;
        while(screenBuffer.window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                screenBuffer.window.close();
            }
        }
        screenBuffer.PrintScreen();
    }

    return 0;
}

