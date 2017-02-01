#include "GUI_Systems.h"

/************************/
/**    TEMPLATE GUI    **/
/************************/
GUI_Systems::GUI_Systems()
{}
/**UPDATES**/
int GUI_Systems::update()
{
    mousePosition = sf::Mouse::getPosition(*currentWindow);

    for(int i = 0; i < buttonReference; i++){
        if(buttons[i].checkHovering(sf::Vector2f(mousePosition))){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                std::cout << "Returning mouse choice " << i+1 << std::endl;
                return i+1;
            }
        }
    }
    return 0;
}
bool GUI_Systems::getVisible()
{
    return visible;
}
void GUI_Systems::makeVisible()
{
    visible = true;
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
void GUI_Systems::resetPackage()
{
    iPack.pNum = 0;
}
GUI_Systems::~GUI_Systems()
{}
/***********************/
/**    GENERIC GUI    **/
/***********************/
GUI_generic::GUI_generic()
{}
GUI_generic::GUI_generic(sf::Vector2f bDimensions, sf::Vector2f bPosition, sf::Font* font, bool vertical)
{
    this->bDimensions = bDimensions;
    this->bPosition = bPosition;

    background.setFillColor(sf::Color(139,198,174));
    background.setOutlineThickness(2);
	background.setOutlineColor(sf::Color(55,68,63));

    this->buttonColor = sf::Color(192,174,229);
    this->borderColor = sf::Color(81,75,94);
    this->textColor = sf::Color(200,199,201);
    this->font = font;
    this->vertical = vertical;
    buttonReference = 0;
}
void GUI_generic::addButton(const std::string text)
{
    float offSet = bDimensions.x / 8;

    if(buttonReference > 0){
        if(!vertical){
            bPosition.x += bDimensions.x + offSet;
        }
        else{
            bPosition.y += bDimensions.y + offSet;
        }
    }


    buttons.push_back(Button(bDimensions, bPosition, text, buttonColor, borderColor, textColor, font, 60));
    buttonReference ++;

    if(buttonReference == 1){
        totalBounds.width = bDimensions.x;
        totalBounds.height = bDimensions.y;
        totalBounds.left = bPosition.x - offSet;
        totalBounds.top = bPosition.y - offSet;

        sf::Vector2f position = sf::Vector2f(totalBounds.left, totalBounds.top);
        background.setPosition(position);
    }

    if(!vertical){
        totalBounds.width += (bDimensions.x + offSet) * (buttonReference - 1);
    }
    else{
        totalBounds.height += (bDimensions.y + offSet) * (buttonReference - 1);
    }

    sf::Vector2f dimensions = sf::Vector2f(totalBounds.width + 2 * offSet, totalBounds.height + 2 * offSet);

    background.setSize(dimensions);
}
inputPackage GUI_generic::show(sf::RenderWindow* currentWindow)
{
    this->currentWindow = currentWindow;

    sf::Event GUIevent;

    while (currentWindow->pollEvent(GUIevent)){

        if(GUIevent.type == sf::Event::KeyPressed){
            if(GUIevent.key.code == sf::Keyboard::Escape){
                    visible=false;
            }
        }
    }

    iPack.pNum = update();

    if(iPack.pNum != 0){
        visible = false;
    }

    return iPack;
}
/******************************/
/**   DESIGNER PAUSE MENU    **/
/******************************/
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

	sf::Color buttonColor = sf::Color(192,174,229);
	sf::Color borderColor = sf::Color(81,75,94);
	sf::Color textColor = sf::Color(200,199,201);

    sf::Vector2f bDimensions(280,130);

    sf::Vector2f bPosition1 = sf::Vector2f(position.x + 10, position.y + 26);
    sf::Vector2f bPosition2 = sf::Vector2f(position.x + 10, position.y + 182);
    sf::Vector2f bPosition3 = sf::Vector2f(position.x + 10, position.y + 338);
    sf::Vector2f bPosition4 = sf::Vector2f(position.x + 10, position.y + 494);

    buttons.push_back(Button(bDimensions, bPosition1, "Resume", buttonColor, borderColor, textColor, font, 72));
    buttons.push_back(Button(bDimensions, bPosition2, "Save", buttonColor, borderColor, textColor, font, 72));
    buttons.push_back(Button(bDimensions, bPosition3, "Load", buttonColor, borderColor, textColor, font, 72));
    buttons.push_back(Button(bDimensions, bPosition4, "Exit", buttonColor, borderColor, textColor, font, 72));
}
inputPackage GUI_designerPaused::show(sf::RenderWindow* currentWindow)
{
    this->currentWindow = currentWindow;

    sf::Event GUIevent;

    while (currentWindow->pollEvent(GUIevent)){

        if(GUIevent.type == sf::Event::KeyPressed){
            if(GUIevent.key.code == sf::Keyboard::Escape){
                    visible=false;
            }
        }
    }

    iPack.pNum = update();

    if(iPack.pNum != 0){
        visible = false;
    }

    return iPack;
}
/******************************/
/**   LOAD FILE INPUT MENU   **/
/******************************/
GUI_getString::GUI_getString()
{}
GUI_getString::GUI_getString(sf::Vector2f dimensions, sf::Vector2f position, sf::Font* font)
{
    visible = false;
    buttonReference = 2;

	background.setSize(dimensions);
	background.setFillColor(sf::Color(139,198,174));
	background.setOutlineThickness(2);
	background.setOutlineColor(sf::Color(55,68,63));
	background.setPosition(position);

	sf::Color buttonColor = sf::Color(192,174,229);
	sf::Color borderColor = sf::Color(81,75,94);
	sf::Color textColor = sf::Color(200,199,201);

    sf::Vector2f bDimensions(185, 75);

    sf::Vector2f bPosition1 = sf::Vector2f(position.x + 10, position.y + dimensions.y/2);
    sf::Vector2f bPosition2 = sf::Vector2f(position.x + bDimensions.x + 20, position.y + dimensions.y/2);

    sf::Vector2f tSize(300, 50);

    textBackground.setSize(tSize);
    textBackground.setPosition(position.x + 20, position.y + 10);
    textBackground.setFillColor(buttonColor);
    textBackground.setOutlineColor(borderColor);
    textBackground.setOutlineThickness(-1);

    currentText.setFont(*font);
    currentText.setPosition(sf::Vector2f(position.x + 23, position.y + 13));
    currentText.setFillColor(textColor);
    currentText.setCharacterSize(24);

    buttons.push_back(Button(bDimensions, bPosition1, "Okay", buttonColor, borderColor, textColor, font, 60));
    buttons.push_back(Button(bDimensions, bPosition2, "Cancel", buttonColor, borderColor, textColor, font, 60));
}
inputPackage GUI_getString::show(sf::RenderWindow* currentWindow)
{
    this->currentWindow = currentWindow;

    sf::Event GUIevent;

    while (currentWindow->pollEvent(GUIevent)){

        if(GUIevent.type == sf::Event::KeyPressed){
            if(GUIevent.key.code == sf::Keyboard::Escape){
                iPack.pNum = 2;
            }
            if(GUIevent.key.code == sf::Keyboard::BackSpace){
                if(inputString.size() != 0){
                    inputString.resize(inputString.size()-1);
                    currentText.setString(inputString);
                }
            }
            if(GUIevent.key.code == sf::Keyboard::Return){
                iPack.pNum = 1;
            }
        }
        else if (GUIevent.type == sf::Event::TextEntered){
            if (GUIevent.text.unicode < 127 && GUIevent.text.unicode > 31 && inputString.length() <= 32){
                inputString += static_cast<char>(GUIevent.text.unicode);
                currentText.setString(inputString);
            }
        }
    }

    if(iPack.pNum == 0){
        iPack.pNum = update();
    }
    else{
        if(iPack.pNum == 1){
            visible = false;
            iPack.pString = inputString;
        }
        if(iPack.pNum == 2){
            visible = false;
            iPack.pString = "CANCEL";
            iPack.pNum = 0;
        }
    }

    return iPack;
}
void GUI_getString::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(visible == false)
		return;

	states.transform *= getTransform();

	target.draw(background);

	for(int i = 0; i < buttonReference; i++){
		target.draw(buttons[i].getBackground());
		target.draw(buttons[i].getText());
	}

	target.draw(textBackground);

	if(!inputString.empty()){
        target.draw(currentText);
	}
}



/******************************/
/**          BUTTON          **/
/******************************/
Button::Button()
{}
//Dimensions, position, text, buttoncolor, bordercolor, text color, font
Button::Button(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor,
               sf::Color borderColor, sf::Color textColor, sf::Font* font, int characterSize)
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

	float textOffsetX = dimensions.x / 12;
	float textOffsetY = dimensions.y / 12;

	buttonText.setString(text);
	buttonText.setPosition(position.x + textOffsetX, position.y + textOffsetY);
	buttonText.setFillColor(textColor);
	buttonText.setFont(*font);
	buttonText.setCharacterSize(characterSize);
}
/**CHECK BUTTON STATES**/
bool Button::checkHovering(sf::Vector2f mousePosition)
{
	if(buttonBackground.getGlobalBounds().contains(mousePosition)){
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

    float textOffsetX = buttonBackground.getSize().x * (1/6);
	float textOffsetY = buttonBackground.getSize().y * (1/6);
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
