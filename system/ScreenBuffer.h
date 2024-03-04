//
// Created by nava on 04/03/24.
//

#ifndef RETROBASIC_SCREENBUFFER_H
#define RETROBASIC_SCREENBUFFER_H

#include <SFML/Graphics.hpp>

#include "CharCell.h"

enum properties {
    CH_NORMAL = 0,
    CH_INVERTED,
    CH_BLINKING
};

class ScreenBuffer {
public:
    void Init();
    void ClearScreen();
    void PrintScreen();
    void SetString(int line, int column, std::string str,
                   int property = CH_NORMAL,
                   int fr=255, int fg=255, int fb=255,
                   int br=0, int bg=0, int bb=255);
    void SetString(std::string str, int property = CH_NORMAL,
                   int fr=255, int fg=255, int fb=255,
                   int br=0, int bg=0, int bb=255);
    void SetCharacter(int line, int column, std::string ch,
                   int property = CH_NORMAL,
                   int fr=255, int fg=255, int fb=255,
                   int br=0, int bg=0, int bb=255);
    void NewLine();
    sf::Vector2<int> GetCursorPosition() const;
    void SetCursorPosition(int line, int column);
    void CursorOn();
    void CursorOff();

    const std::string CCedil = "\xc3\x87"; // 199 Ç
    const std::string cCedil = "\xc3\xa7"; // 231 ç

    const std::string AGrave = "\xc3\x80"; // 192 À
    const std::string AAcute = "\xc3\x81"; // 193 Á
    const std::string ACirc = "\xc3\x82";  // 194 Â
    const std::string ATilde = "\xc3\x83"; // 195 Ã

    const std::string aGrave = "\xc3\xa0"; // 224 à
    const std::string aAcute = "\xc3\xa1"; // 225 á
    const std::string aCirc = "\xc3\xa2";  // 226 â
    const std::string aTilde = "\xc3\xa3"; // 227 ã

    const std::string EAcute = "\xc3\x89"; // 201 É
    const std::string ECirc = "\xc3\x8a";  // 202 Ê

    const std::string eAcute = "\xc3\xa9"; // 233 é
    const std::string eCirc = "\xc3\xaa";  // 234 ê

    const std::string IAcute = "\xc3\x8d"; // 205 Í

    const std::string iAcute = "\xc3\xad"; // 237 í

    const std::string OAcute = "\xc3\x93"; // 211 Ó
    const std::string OCirc = "\xc3\x94";  // 212 Ô
    const std::string OTilde = "\xc3\x95"; // 213 Õ

    const std::string oAcute = "\xc3\xb3"; // 243 ó
    const std::string oCirc = "\xc3\xb4";  // 244 ô
    const std::string oTilde = "\xc3\xb5"; // 245 õ

    const std::string UAcute = "\xc3\x9a"; // 218 Ú

    const std::string uAcute = "\xc3\xba"; // 250 ú

    sf::RenderWindow window;
    int frame = 0;
    bool show = true;
    bool showCursor = true;

private:
    void Scroll();
    void CheckLineColumn(int &line, int &column);

    CharCell screen[29][80];
    sf::Font font;
    sf::Text text;
    sf::Vector2<int> cursorPosition;
    sf::RectangleShape cursor;

    const int SCREEN_LINES = 29;
    const int SCREEN_COLUMNS = 80;
    const int FRAME_RATE = 60;
};


#endif //RETROBASIC_SCREENBUFFER_H
