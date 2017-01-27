#ifndef STRUCTURE_COLLIDER_H
#define STRUCTURE_COLLIDER_H

#include <SFML/Graphics.hpp>
#include "types.h"

class Structure_Collider
{
    public:
        Structure_Collider();
        void addStructure(sf::FloatRect);
        bool axisCheck(float, float, float, float);
        collidedPackage checkCollision(sf::FloatRect);
        virtual ~Structure_Collider();

    protected:

    private:
        std::vector<sf::FloatRect> staticStructures;
        int structuresSize;
};

#endif // STRUCTURE_COLLIDER_H
