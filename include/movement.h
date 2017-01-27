#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "types.h"

class Object_Mover
{
    public:
        Object_Mover();
        Object_Mover(int speed, int gravity, sf::Vector2f startPosition, sf::FloatRect floor, sf::FloatRect objectDimensions);
        void moveLeft();
        void moveRight();
        void jumpUp();
        void resetXvelocity();
        sf::Vector2f* moveObject();
        void isStructureColliding(collidedPackage);
        sf::Vector2f* getObjectPosition();
        virtual ~Object_Mover();

    protected:

    private:
        int SPEED;
        int GRAVITY;
        sf::FloatRect oDimensions;
        sf::Vector2f oPosition;
        sf::Vector2f oVelocity;
        sf::FloatRect oFloor;
};

#endif // MOVEMENT_H
