//
// Created by nava on 04/03/24.
//

#ifndef RETROBASIC_CHARCELL_H
#define RETROBASIC_CHARCELL_H

#include <iostream>
#include <SFML/Graphics.hpp>

class CharCell
{
public:
    std::string ch;
    sf::Color fgColor;
    sf::Color bgColor;
    int property;
};

#endif //RETROBASIC_CHARCELL_H
