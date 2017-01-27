#include "hubworld.h"

Hubworld::Hubworld() : PLAYER_POSITION(sf::Vector2f(100,100)), PLAYER_DIMENSIONS(sf::Vector2i(20,32))
{
/*  if(!textureMap.loadFromFile("png/level1/level1.png")){
        std::cout << "Could not load file" << std::endl;
    }
	smap.setTexture(textureMap);
	smap.setPosition(0,0);*/
}
int Hubworld::worldDisplay(sf::RenderWindow* window)
{
    gameWindow = window;

	setUp();

    while (gameWindow->isOpen()){

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			player->jump();
		/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player->duck();
        */
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player->moveLeft();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player->moveRight();
		/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			//call action
        */
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			gameWindow->close();

		sf::Event event;

        while (gameWindow->pollEvent(event)){

			if(event.type == sf::Event::Closed)
				gameWindow->close();
			if(event.type == sf::Event::KeyReleased)
				player->keyReleased(event);
		}

		update();

    }
	return -1;
}
void Hubworld::setUp()
{
    view = new sf::View();
	view->reset(sf::FloatRect(0,0,400,300));
	view->setCenter(PLAYER_POSITION);

    float windowX_float = static_cast < float >(gameWindow->getSize().x);
    float windowY_float = static_cast < float >(gameWindow->getSize().y);

    floor.setSize(sf::Vector2f(windowX_float, 5));
    floor.setFillColor(sf::Color::Black);
    floor.setPosition(sf::Vector2f(0,200));

    player = new Player("png/playertest20x32.png", PLAYER_DIMENSIONS,  gameWindow->getSize(), PLAYER_POSITION, floor.getGlobalBounds());

    background.setSize(sf::Vector2f(windowX_float, windowY_float));
    background.setFillColor(sf::Color::White);
    background.setPosition(0,0);

	gameWindow->setFramerateLimit(30);
}
void Hubworld::createStructures()
{
    /*get structure info from file
    sf::Vector2i structurePositions;
    sf::Vector2i structureDimensions;
    hSCollider = new Structure_Collider(sf::Vector2u(structurePositions, structureDimensions));
    player->setStructureCollider(hSCollider);
    send homeworld structure collider to enemies / moveable objects*/
}
void Hubworld::updateWindow()
{
    gameWindow->setView(*view);
	gameWindow->clear();
	//gameWindow->draw(smap);
	gameWindow->draw(background);
	gameWindow->draw(*player);
    gameWindow->draw(floor);

	gameWindow->display();
}
void Hubworld::updateView()
{
    if(player->getPosition().x > view->getCenter().x+75){
        view->move(3,0);
        //floor->move(1,0);
    }
	if(player->getPosition().x < view->getCenter().x-75){
        view->move(-3,0);
        //floor->move(-1,0);
	}
	if(player->getPosition().y > view->getCenter().y+50){
        view->move(0,3);
        //floor->move(0,1);
	}
	if(player->getPosition().y < view->getCenter().y-50){
        view->move(0,-3);
        //floor->move(0,-1);
	}

    //player->setFloor(floor->getGlobalBounds());

}
void Hubworld::update()
{
	player->movePlayer();

	updateView();
	updateWindow();
}
Hubworld::~Hubworld()
{
    gameWindow = NULL;
    delete player;

}
