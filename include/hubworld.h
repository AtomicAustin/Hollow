#ifndef HUBWORLD_H
#define HUBWORLD_H

#include "player.h"
#include "collision.h"

class Hubworld
{
    public:
        Hubworld();
        int worldDisplay(sf::RenderWindow* window);
        void setUp();
        void createStructures();
        void updateWindow();
        void updateView();
        void update();
        virtual ~Hubworld();

    protected:

    private:
        sf::RenderWindow* gameWindow;
        sf::View* view;
        sf::Texture hTextureMap;
        sf::Sprite hMap;
        sf::RectangleShape background;
        Player* player;
        sf::Vector2f PLAYER_POSITION;
        sf::Vector2i PLAYER_DIMENSIONS;
        sf::RectangleShape floor;
        Structure_Collider* hSCollider;
};

#endif // HUBWORLD_H
