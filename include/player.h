#ifndef PLAYER_H
#define PLAYER_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include "movement.h"
#include "collision.h"
//#include "collision.h"

class Player: public sf::Drawable, public sf::Transformable
{
    public:
        Player(const std::string& name, sf::Vector2i dimensions,
                sf::Vector2u size, sf::Vector2f mPosition,
                sf::FloatRect floor);
        //virtual ~Player();
        void jump();
        void duck();
        void moveLeft();
        void moveRight();
        void keyReleased(sf::Event);
        void movePlayer();
        void setStructureCollider(Structure_Collider* sCollider);
        sf::Vector2f getPosition();

    protected:

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        //int SPEED;
        //int GRAVITY;
        sf::Vector2u pSize;
        //sf::Vector2f mPosition;
        //sf::Vector2f mVelocity;
        sf::Sprite pSprite;
        sf::Texture pTexture;
        Object_Mover* pMover;
        Structure_Collider* pStructureCollider;
};

#endif // PLAYER_H
