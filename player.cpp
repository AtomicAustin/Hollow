#include "player.h"

Player::Player(const std::string& name, sf::Vector2i dimensions, sf::Vector2u playerSize, sf::Vector2f position, sf::FloatRect floor)
 : pSize(playerSize)
{
	pTexture.loadFromFile(name);
	pSprite.setTexture(pTexture);

	pMover = new Object_Mover(3, 1, position, floor, pSprite.getGlobalBounds());
}
void Player::jump()
{
    pMover->jumpUp();
}
void Player::duck()
{
    //duck
}
void Player::moveLeft()
{
    pMover->moveLeft();
}
void Player::moveRight()
{
    pMover->moveRight();
}
void Player::keyReleased(sf::Event event)
{
    switch(event.key.code){
		//case sf::Keyboard::W: mVelocity.y = 0; break;
		//case sf::Keyboard::S: un-duck; break;
		case sf::Keyboard::A: pMover->resetXvelocity(); break;
		case sf::Keyboard::D: pMover->resetXvelocity(); break;
		default: break;
	}
}
void Player::movePlayer()
{
    collidedPackage newPackage = pStructureCollider->checkCollision(pSprite.getGlobalBounds());

    if(newPackage.hit != 0){
        pMover->isStructureColliding(newPackage);
    }

    pSprite.setPosition(*pMover->moveObject());
}
void Player::setStructureCollider(Structure_Collider* sCollider)
{
    pStructureCollider = sCollider;
}
sf::Vector2f Player::getPosition()
{
    return *pMover->getObjectPosition();
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(pSprite, states);
}
/*Player::~Player()
{
    //dtor
}*/
