#ifndef TAROT_CHARACTER
#define TAROT_CHARACTER

#include <string>



class Character {
public:

    Character() : r(255), g(255), b(255), a(255), ID(0)
    {

    }

    Character(int id, std::string n, uint8_t R, uint8_t G, uint8_t B)
        : ID(id), name(n), r(R), g(G), b(B)
    {

    }

    Character(int id, std::string n, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
        : ID(id), name(n), r(R), g(G), b(B), a(A)
    {

    }

    int ID;

    std::string name; // name of the character

    // colour of their character text
    // WILL BE UPDATED TO CONFORM TO GRAPHICS ENGINE
    // Range: 0-255
    // a is Alpha (opacity)
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

};

#endif
