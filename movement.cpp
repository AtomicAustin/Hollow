#include "movement.h"

Object_Mover::Object_Mover()
{
    //ctor
    std::cout << "Movement Component: Not constructed properly" << std::endl;
}
Object_Mover::Object_Mover(int speed, int gravity, sf::Vector2f startPosition, sf::FloatRect floor, sf::FloatRect objectDimensions)
: SPEED(speed), GRAVITY(gravity), oPosition(startPosition), oVelocity(sf::Vector2f(0,0)), oFloor(floor), oDimensions(objectDimensions)
{
    //ctor
}
void Object_Mover::moveLeft()
{
    oVelocity.x = -SPEED;
}
void Object_Mover::moveRight()
{
    oVelocity.x = SPEED;
}
void Object_Mover::jumpUp()
{
    oVelocity.y = -SPEED*2;
}
void Object_Mover::resetXvelocity()
{
    oVelocity.x = 0;
}
sf::Vector2f* Object_Mover::moveObject()
{
    oVelocity.y += GRAVITY;

    oPosition.x += oVelocity.x;
	oPosition.y += oVelocity.y;

	/*if(oPosition.y + oObjectHeight >= oFloor.top){
        oPosition.y = oFloor.top - oObjectHeight;
        oVelocity.y = 0;
	}*/

	return &oPosition;
}
void Object_Mover::isStructureColliding(collidedPackage package)
{
    switch(package.hit){
        case 1: { oPosition.y = package.bounds.top + oDimensions.height; oVelocity.y = 0; break;}
        case 2: { oPosition.y = package.bounds.top + package.bounds.height + 1; oVelocity.y = 0; break;}
        case 3: { oPosition.x = package.bounds.left + oDimensions.width; break;}
        case 4: { oPosition.x = package.bounds.left + package.bounds.width + 1; break;}
    }
}
sf::Vector2f* Object_Mover::getObjectPosition()
{
    return &oPosition;
}
Object_Mover::~Object_Mover()
{
    //dtor
}
