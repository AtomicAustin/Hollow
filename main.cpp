/* Hollow
 * A bare-bones dungeon crawler
 * Author: Austin Herman
 * Started: 1/12/17
 * Last Update: 1/12/17
 * Progress: Designing
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "hubworld.h"
#include "designer.h"

int handleChoice(int, sf::RenderWindow*);

int main()
{
	const int WIDTH = GetSystemMetrics(SM_CXSCREEN) - 100;
	const int HEIGHT = GetSystemMetrics(SM_CYSCREEN) - 100;

    std::cout << WIDTH << " " << HEIGHT << std::endl;

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Hollow");
	window->setPosition(sf::Vector2i(0,0));

	sf::IntRect menu1(0,0,120,78);
	sf::IntRect menu2(120,0,120,78);
	sf::IntRect menu3(240,0,120,78);
	sf::IntRect menu4(360,0,120,78);

	sf::IntRect selectArray[] = {menu1, menu2, menu3, menu4};

	sf::Texture sTexture;
	sf::Sprite sSprite;
	sTexture.loadFromFile("png/splashscreentest480x78.png");
	sSprite.setTexture(sTexture);
	sSprite.setTextureRect(menu1);
	sSprite.setPosition(0, 0);
	sSprite.setScale(16, 12.8);

	int choice = 0;

	while(window->isOpen()){

		sf::Event sEvent;

		while (window->pollEvent(sEvent)){

			if(sEvent.type == sf::Event::Closed)
				window->close();

			if(sEvent.type == sf::Event::KeyPressed){

				if(sEvent.key.code == sf::Keyboard::W){

					choice--;

					if(choice < 0)
						choice = 3;
				}

				if(sEvent.key.code == sf::Keyboard::S){

					choice++;

					if(choice > 3)
						choice = 0;
				}
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            int rCode = handleChoice(choice, window);
            if(rCode == -1){
                window->close();
            }
		}

		sSprite.setTextureRect(selectArray[choice]);

		window->clear();
		window->draw(sSprite);
		window->display();
	}
}
//RETURN CODES:
//-1 = exit game
//1 = return to main menu
int handleChoice(int choice, sf::RenderWindow* window)
{
    int returnCode;

    switch(choice){
        case 0:{
			Hubworld* level = new Hubworld();
			returnCode = level->worldDisplay(window);
			delete level;
			break;
		}
        case 1:{
			Hubworld* level = new Hubworld();
			returnCode = level->worldDisplay(window);
			delete level;
			break;
		}
        case 2:{
            Designer* designer = new Designer();
            returnCode = designer->environmentDisplay(window);
            delete designer;
            break;
        }
        case 3:{returnCode = -1; break;}

	}

    return returnCode;
}
