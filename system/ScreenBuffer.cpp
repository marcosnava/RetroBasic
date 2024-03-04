//
// Created by nava on 04/03/24.
//

#include "ScreenBuffer.h"
#include <iostream>

void ScreenBuffer::Init() {
    sf::VideoMode dimension(800, 600);
    window.create(dimension, "RetroBasic 0.1");
    window.setFramerateLimit(FRAME_RATE);
    frame = 0;
    show = true;

    if(!font.loadFromFile("./assets/ConsolaMono-Book.ttf"))
    {
        std::cerr << "Error loading fonts!" << std::endl;
        exit(EXIT_FAILURE);
    }

    text.setFont(font);
    text.setCharacterSize(17);
    text.setFillColor(sf::Color::White);

    cursor.setSize(sf::Vector2f(10,20));
    cursor.setFillColor(sf::Color(255, 255, 255, 200));

    ClearScreen();
}


void ScreenBuffer::ClearScreen() {
    cursorPosition.x = 0;
    cursorPosition.y = 0;
    for(int line = 0; line < SCREEN_LINES; line++)
    {
        for(int column = 0; column < SCREEN_COLUMNS; column++)
        {
            screen[line][column].bgColor = sf::Color::Blue;
            screen[line][column].fgColor = sf::Color::White;
            screen[line][column].ch = " ";
            screen[line][column].property = CH_NORMAL;
        }
    }
}

void ScreenBuffer::PrintScreen() {
    frame++;
    if(frame>(FRAME_RATE / 2))
    {
        frame = 0;
        show = !show;
    }
    std::string str;
    sf::Color fgColor;
    sf::Color bgColor;
    int property;
    sf::RectangleShape recSp(sf::Vector2f(10, 20));

    window.clear(sf::Color::Blue);
    for(int line = 0; line < SCREEN_LINES; line++)
    {
        for(int column = 0; column < SCREEN_COLUMNS; column++)
        {
            str = screen[line][column].ch;
            fgColor = screen[line][column].fgColor;
            bgColor = screen[line][column].bgColor;
            property = screen[line][column].property;

            if(property == CH_NORMAL)
            {
                text.setString(sf::String::fromUtf8(str.begin(), str.end()));
                text.setFillColor(fgColor);
                recSp.setFillColor(bgColor);
                text.setPosition(column * 10, line * 20);
                recSp.setPosition(column * 10, line * 20);
            }
            else if(property == CH_INVERTED)
            {
                text.setString(sf::String::fromUtf8(str.begin(), str.end()));
                text.setFillColor(bgColor);
                recSp.setFillColor(fgColor);
                text.setPosition(column * 10, line * 20);
                recSp.setPosition(column * 10, line * 20);
            }
            else if(property == CH_BLINKING)
            {
                if(show)
                {
                    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
                    text.setFillColor(fgColor);
                    text.setPosition(column * 10, line * 20);
                }
                recSp.setFillColor(bgColor);
                recSp.setPosition(column * 10, line * 20);
            }

            window.draw(recSp);
            window.draw(text);
        }
    }
    if(showCursor && show)
    {
        cursor.setPosition(cursorPosition.x * 10, cursorPosition.y * 20);
        window.draw(cursor);
    }
    window.display();
}

void
ScreenBuffer::SetCharacter(int line, int column, std::string ch, int property, int fr, int fg, int fb, int br, int bg,
                           int bb) {
    sf::Color fgColor = sf::Color(fr, fg, fb);
    sf::Color bgColor = sf::Color(br, bg, bb);

    screen[line][column].ch = ch;
    screen[line][column].fgColor = fgColor;
    screen[line][column].bgColor = bgColor;
    screen[line][column].property = property;
    column++;
    CheckLineColumn(line, column);

    cursorPosition.x = column;
    cursorPosition.y = line;
}

void
ScreenBuffer::SetString(int line, int column, std::string str, int property, int fr, int fg, int fb, int br, int bg,
                        int bb) {
    sf::Color fgColor = sf::Color(fr, fg, fb);
    sf::Color bgColor = sf::Color(br, bg, bb);

    if(line >= SCREEN_LINES)
    {
        Scroll();
        line = SCREEN_LINES - 1;
    }
    bool escape = false;
    for(auto ch: str)
    {
        if(!escape)
        {
            screen[line][column].ch = ch;
            screen[line][column].fgColor = fgColor;
            screen[line][column].bgColor = bgColor;
            screen[line][column].property = property;
        }
        else
        {
            screen[line][column].ch += ch;
            escape = false;
        }

        if(ch == '\xc3')
        {
            escape = true;
        }
        if(!escape)
        {
            column++;
            CheckLineColumn(line, column);
        }
    }
    column++;
    CheckLineColumn(line, column);

    cursorPosition.x = column-1;
    cursorPosition.y = line;
}

void ScreenBuffer::SetString(std::string str, int property, int fr, int fg, int fb, int br, int bg, int bb) {
    sf::Color fgColor = sf::Color(fr, fg, fb);
    sf::Color bgColor = sf::Color(br, bg, bb);

    int line = cursorPosition.y;

    if(line >= SCREEN_LINES)
    {
        Scroll();
        line = SCREEN_LINES - 1;
    }
    int column = cursorPosition.x;
    bool escape = false;
    for(auto ch: str)
    {
        if(!escape)
        {
            screen[line][column].ch = ch;
            screen[line][column].fgColor = fgColor;
            screen[line][column].bgColor = bgColor;
            screen[line][column].property = property;
        }
        else
        {
            screen[line][column].ch += ch;
            escape = false;
        }

        if(ch == '\xc3')
        {
            escape = true;
        }
        if(!escape)
        {
            column++;
            CheckLineColumn(line, column);
        }
    }
    column++;
    CheckLineColumn(line, column);

    cursorPosition.x = column-1;
    cursorPosition.y = line;
}

sf::Vector2<int> ScreenBuffer::GetCursorPosition() const {
    return cursorPosition;
}

void ScreenBuffer::Scroll() {
    for(int line = 0; line < (SCREEN_LINES - 1); line++)
    {
        for(int column = 0; column < SCREEN_COLUMNS; column++)
        {
            screen[line][column] = screen[line + 1][column];
        }
    }
    for(int column = 0; column < SCREEN_COLUMNS; column++)
    {
        screen[SCREEN_LINES-1][column].ch = " ";
        screen[SCREEN_LINES-1][column].fgColor = sf::Color::White;
        screen[SCREEN_LINES-1][column].bgColor = sf::Color::Blue;
        screen[SCREEN_LINES-1][column].property = CH_NORMAL;
    }
}

void ScreenBuffer::CheckLineColumn(int &line, int &column) {
    if(column == SCREEN_COLUMNS)
    {
        line++;
        column = 0;
        if(line == SCREEN_LINES)
        {
            Scroll();
            line = SCREEN_LINES - 1;
        }
    }
}

void ScreenBuffer::NewLine() {
    cursorPosition.x = 0;
    cursorPosition.y++;
    CheckLineColumn(cursorPosition.y, cursorPosition.x);
}

void ScreenBuffer::SetCursorPosition(int line, int column) {
    cursorPosition.x = column;
    cursorPosition.y = line;
    CheckLineColumn(cursorPosition.y, cursorPosition.x);
}

void ScreenBuffer::CursorOn() {
    showCursor = true;
}

void ScreenBuffer::CursorOff() {
    showCursor = false;
}
