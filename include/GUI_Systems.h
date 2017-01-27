#ifndef GUI_SYSTEMS_H
#define GUI_SYSTEMS_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Button;

class GUI_Systems: public sf::Transformable, public sf::Drawable
{
    public:
        GUI_Systems();

        //Dimensions, position, text, buttoncolor, bordercolor, text color, font
        int addButton(sf::Vector2f dimensions, sf::Vector2f position,
                      const std::string& text, sf::Color buttonColor,
                      sf::Color borderColor, sf::Color textColor, sf::Font* font);
        int update();

        void show();
        void hide();
        bool getVisible();

        virtual ~GUI_Systems();

    protected:
        bool visible;
        int buttonReference;
        sf::RectangleShape background;
        std::vector<Button> buttons;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Vector2i mousePosition;
};

class Button
{
    public:
        Button();
        Button(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor,
               sf::Color borderColor, sf::Color textColor, sf::Font* font);

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

class GUI_designerPaused : public GUI_Systems
{
public:
    GUI_designerPaused();
    //dimensions, position, backgroundcolor, bordercolor
    GUI_designerPaused(sf::Vector2f dimensions, sf::Vector2f position, sf::Font* font);

    private:
};

#endif // GUI_SYSTEMS_H
