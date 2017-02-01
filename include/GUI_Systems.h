#ifndef GUI_SYSTEMS_H
#define GUI_SYSTEMS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "types.h"

class Button;

class GUI_Systems: public sf::Transformable, public sf::Drawable
{
    public:
        GUI_Systems();
        int update();

        virtual inputPackage show(sf::RenderWindow* currentWindow) =0;
        bool getVisible();
        void makeVisible();
        void resetPackage();

        virtual ~GUI_Systems();

    protected:
        sf::RenderWindow* currentWindow;
        bool visible;
        int buttonReference;
        sf::RectangleShape background;
        std::vector<Button> buttons;
        inputPackage iPack;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Vector2i mousePosition;
};
class GUI_generic : public GUI_Systems
{
    public:
        GUI_generic();
        GUI_generic(sf::Vector2f bDimensions, sf::Vector2f bPosition, sf::Font* font, bool vertical);
        void addButton(const std::string text);
        inputPackage show(sf::RenderWindow* currentWindow);

    private:
        sf::Vector2f bDimensions;
        sf::Vector2f bPosition;
        sf::FloatRect totalBounds;

        sf::Color buttonColor;
        sf::Color borderColor;
        sf::Color textColor;
        sf::Font* font;

        bool vertical;
};
class GUI_designerPaused : public GUI_Systems
{
    public:
        GUI_designerPaused();
        //dimensions, position, backgroundcolor, bordercolor
        GUI_designerPaused(sf::Vector2f dimensions, sf::Vector2f position, sf::Font* font);
        inputPackage show(sf::RenderWindow* currentWindow);
};
class GUI_getString : public GUI_Systems
{
    public:
        GUI_getString();
        //dimensions, position, backgroundcolor, bordercolor
        GUI_getString(sf::Vector2f dimensions, sf::Vector2f position, sf::Font* font);
        inputPackage show(sf::RenderWindow* currentWindow);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::string inputString;
        sf::Text currentText;
        sf::RectangleShape textBackground;
};
class Button
{
    public:
        Button();
        Button(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor,
               sf::Color borderColor, sf::Color textColor, sf::Font* font, int characterSize);

        bool checkHovering(sf::Vector2f);
        void hovering();
        void notHovering();
        sf::RectangleShape getBackground() const;
        sf::Text getText() const;

        void setPosition(sf::Vector2f);

    private:
        sf::RectangleShape buttonBackground;
        sf::Text buttonText;

        sf::Color backgroundColor;
        sf::Color backgroundHovering;
        sf::Color borderColor;
        sf::Color borderHovering;
        sf::Color textColor;
        sf::Color textHovering;
};
#endif // GUI_SYSTEMS_H
