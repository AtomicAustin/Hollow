#include "GUI_Systems.h"

/*****************************
**    GENERIC PAUSE MENU    **
******************************/
GUI_Systems::GUI_Systems()
{}
/**ADD BUTTON**/
int GUI_Systems::addButton(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor,
                           sf::Color borderColor, sf::Color textColor, sf::Font* font)
{
	buttons.push_back(Button(dimensions, position, text, buttonColor, borderColor, textColor, font));
	buttonReference++;
	return buttonReference;
}
/**UPDATES**/
int GUI_Systems::update()
{
    mousePosition = sf::Mouse::getPosition();

    for(int i = 0; i < buttonReference; i++){
        if(buttons[i].checkHovering(sf::Vector2f(mousePosition))){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                std::cout << "Returning " << i+1 << std::endl;
                return i+1;
            }
        }
    }
    return 0;
}
void GUI_Systems::show()
{
	visible = true;
}
void GUI_Systems::hide()
{
	visible = false;
}
bool GUI_Systems::getVisible()
{
    return visible;
}
void GUI_Systems::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(visible == false)
		return;

	states.transform *= getTransform();

	target.draw(background);

	for(int i = 0; i < buttonReference; i++)
	{
		target.draw(buttons[i].getBackground());
		target.draw(buttons[i].getText());
	}
}
GUI_Systems::~GUI_Systems()
{}
/*****************************
**   DESIGNER PAUSE MENU    **
******************************/
GUI_designerPaused::GUI_designerPaused()
{}
GUI_designerPaused::GUI_designerPaused(sf::Vector2f dimensions, sf::Vector2f position, sf::Font* font)
{
    visible = false;
    buttonReference = 4;

	background.setSize(dimensions);
	background.setFillColor(sf::Color(139,198,174));
	background.setOutlineThickness(2);
	background.setOutlineColor(sf::Color(55,68,63));
	background.setPosition(position);

	float yChunk = dimensions.y/4;
	float xChunk = dimensions.x;

	float buttonHeight = yChunk * (3/5);
	float buttonYspacing = yChunk * (1/5);

	float buttonWidth = xChunk * (6/10);
	float buttonXspacing = xChunk * (2/10);

	sf::Vector2f bDimensions(buttonWidth, buttonHeight);

	sf::Color buttonColor = sf::Color(192,174,229);
	sf::Color borderColor = sf::Color(81,75,94);
	sf::Color textColor = sf::Color(200,199,201);

    sf::Vector2f bPosition1 = sf::Vector2f(position.x + buttonXspacing, position.y + buttonYspacing);
    sf::Vector2f bPosition2 = sf::Vector2f(position.x + buttonXspacing, position.y + buttonYspacing + yChunk * 1);
    sf::Vector2f bPosition3 = sf::Vector2f(position.x + buttonXspacing, position.y + buttonYspacing + yChunk * 2);
    sf::Vector2f bPosition4 = sf::Vector2f(position.x + buttonXspacing, position.y + buttonYspacing + yChunk * 3);

    buttons.push_back(Button(bDimensions, bPosition1, "Resume", buttonColor, borderColor, textColor, font));
    buttons.push_back(Button(bDimensions, bPosition2, "Save", buttonColor, borderColor, textColor, font));
    buttons.push_back(Button(bDimensions, bPosition3, "Load", buttonColor, borderColor, textColor, font));
    buttons.push_back(Button(bDimensions, bPosition4, "Exit", buttonColor, borderColor, textColor, font));

    buttonReference = 4;
}
/*****************************
**          BUTTON          **
******************************/
Button::Button()
{}
//Dimensions, position, text, buttoncolor, bordercolor, text color, font
Button::Button(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor,
               sf::Color borderColor, sf::Color textColor, sf::Font* font)
{
    int hoverOffset = 10;
    backgroundColor = buttonColor;
    this->borderColor = borderColor;
    this->textColor = textColor;

    backgroundHovering = sf::Color(backgroundColor.r - hoverOffset, backgroundColor.b - hoverOffset, backgroundColor.g - hoverOffset);
    borderHovering = sf::Color(this->borderColor.r - hoverOffset, this->borderColor.b - hoverOffset, this->borderColor.g - hoverOffset);
    textHovering = sf::Color(this->textColor.r - hoverOffset, this->textColor.b - hoverOffset, this->textColor.g - hoverOffset);

	buttonBackground.setSize(dimensions);
	buttonBackground.setPosition(position);
	buttonBackground.setFillColor(buttonColor);
	buttonBackground.setOutlineColor(borderColor);
	buttonBackground.setOutlineThickness(-1);

	float textOffsetX = dimensions.x * 1/6;
	float textOffsetY = dimensions.y * 1/4;

	buttonText.setString(text);
	buttonText.setPosition(position.x + textOffsetX, position.y + textOffsetY);
	buttonText.setFillColor(textColor);
	buttonText.setFont(*font);
	buttonText.setCharacterSize(48);
}
/**CHECK BUTTON STATES**/
bool Button::checkHovering(sf::Vector2f mousePosition)
{
	if(buttonBackground.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
		hovering();
		return true;
	}

	notHovering();
	return false;
}
void Button::hovering()
{
	//background (0x00, 0x66, 0xff), background outline (0x00, 0x1f, 0x4d), text color (0xcc, 0xe0, 0xff)
	buttonBackground.setFillColor(backgroundHovering);
	buttonBackground.setOutlineColor(borderHovering);
	buttonText.setFillColor(textHovering);
}
void Button::notHovering()
{
	buttonBackground.setFillColor(backgroundColor);
	buttonBackground.setOutlineColor(borderColor);
	buttonText.setFillColor(textColor);
}
/**SETTER/GETTERS**/
void Button::setPosition(sf::Vector2f position)
{
	buttonBackground.setPosition(position);

    float textOffsetX = buttonBackground.getSize().x * 1/6;
	float textOffsetY = buttonBackground.getScale().y * 1/4;
	buttonText.setPosition(position.x + textOffsetX, position.y + textOffsetY);
}
sf::RectangleShape Button::getBackground() const
{
    return buttonBackground;
}
sf::Text Button::getText() const
{
    return buttonText;
}
