#include "SFML/Graphics.hpp"

#ifndef COLLIDED_PACKAGE
#define COLLIDED_PACKAGE
struct collidedPackage{
    int hit;
    sf::FloatRect bounds;
};
#endif // COLLIDED_PACKAGE

#ifndef INPUT_PACKAGE
#define INPUT_PACKAGE
struct inputPackage{
    int pNum;
    std::string pString;
};
#endif // INPUT_PACKAGE
