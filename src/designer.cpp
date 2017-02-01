#include "designer.h"

/********************/
/**   DESIGNER     **/
/********************/
Designer::Designer() : mouseAction(UNCLICK), currentState(FREE), mouseOver(NOTHING),
    allShapesSize(0), selectedShape(NULL)
{}
/**ENVIRONMENT**/
int Designer::environmentDisplay(sf::RenderWindow* window)
{
    designerWindow = window;

	setUp();

    while (designerWindow->isOpen()){

		sf::Event event;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            mouseAction = L_HOLD;
            if(currentState != FREE){
                changeState(L_HOLD);

                if(currentState == DRAGGING && hoveringSelected() == OBJ_SELECTED){
                    dragging();
                }
                else if(currentState == RESIZING && hoveringSelected() == SIZE_HANDLE){
                    resizing();
                }
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            mouseAction = R_HOLD;
        }

        while (designerWindow->pollEvent(event)){

			if(event.type == sf::Event::Closed){
                if(SLobject != NULL){
                    saveMenu();
                }
                returnCode = -1;
            }
            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::A){
                    addRectangle();
                }
                else if(event.key.code == sf::Keyboard::Escape){
                    showPausemenu();
                }
            }
			else if(event.type == sf::Event::MouseButtonReleased){
                if(mouseAction == L_HOLD){
                    if(currentState == DRAGGING || currentState == RESIZING){
                        mouseAction = UNCLICK;
                        changeState(UNCLICK);
                    }
                    else{
                        mouseAction = LEFT_CLICK;
                        changeState(LEFT_CLICK);

                        if(currentState == SELECTED){
                            selected();
                        }
                    }
                }
                else if(mouseAction == R_HOLD){
                    if(hoveringSelected() == OBJ_SELECTED && currentState == SELECTED){
                        mouseAction = RIGHT_CLICK;
                        changeState(RIGHT_CLICK);
                        deleteRect();
                    }
                }

                mouseAction = UNCLICK;
			}
		}

		update();

        if(returnCode !=0){
            break;
        }

    }
	return returnCode;
}
void Designer::setUp()
{
    mChoice.pNum = 0;
    returnCode = 0;

    std::string fontName = "fonts/DesignFont.ttf";
	pFont = new sf::Font;
    if(!pFont->loadFromFile(fontName)){
        std::cout << "could not load font" << std::endl;
    }

    pMenu = new GUI_designerPaused(sf::Vector2f(300,650), sf::Vector2f(575,300), pFont);
    pGetString = new GUI_getString(sf::Vector2f(420,200), sf::Vector2f(575, 300), pFont);
    pGenericMenu = NULL;
    SLobject = NULL;

    windowX_float = static_cast <float>(designerWindow->getSize().x);
    windowY_float = static_cast <float>(designerWindow->getSize().y);

    background.setSize(sf::Vector2f(windowX_float, windowY_float));
    background.setFillColor(sf::Color::White);
    background.setPosition(0,0);

    designerWindow->setFramerateLimit(30);
}
/**STATE CHANGE**/
void Designer::changeState(Action mAction)
{
    mouseOver = hoveringSelected();

    if(mouseOver == NOTHING){
        mouseOver = mouseHovering();
    }

    if(currentState == FREE && mouseOver == OBJECT && mAction == LEFT_CLICK){
        mouseOver = OBJ_SELECTED;
    }

    switch(currentState){
        case FREE: {
            if (mAction == LEFT_CLICK && mouseOver == OBJ_SELECTED){
                currentState = SELECTED;
            }
            else{
                mouseAction = UNCLICK;
            }
            break;
        }
        case SELECTED: {
            if(mAction == L_HOLD || mAction == R_HOLD){
                if(mouseOver == SIZE_HANDLE){
                    currentState = RESIZING;
                }
                else if(mouseOver == OBJ_SELECTED){
                    currentState = DRAGGING;
                }
            }
            if(mAction == RIGHT_CLICK){
                if(mouseOver == OBJ_SELECTED || mouseOver == SIZE_HANDLE){
                    currentState = FREE;
                }
            }
            if(mAction == LEFT_CLICK){
                if(mouseOver == NOTHING){
                    currentState = FREE;
                }
            }
            break;
        }
        case RESIZING: {
            if(mAction == UNCLICK){
                currentState = SELECTED;
                mouseAction = UNCLICK;
            }
            break;
        }
        case DRAGGING: {
            if(mAction == UNCLICK){
                currentState = SELECTED;
                mouseAction = UNCLICK;
            }
            break;
        }
    }
    //printStates();
}
void Designer::printStates()
{
    switch(currentState){
        case FREE: { std::cout << "State: FREE "; break;}
        case SELECTED: { std::cout << "State: SELECTED "; break;}
        case DRAGGING: { std::cout << "State: DRAGGING "; break;}
        case RESIZING: { std::cout << "State: RESIZING "; break;}
    }
    switch(mouseAction){
        case LEFT_CLICK: { std::cout << "Mouse Action: LEFT_CLICK "; break;}
        case RIGHT_CLICK: { std::cout << "Mouse Action: RIGHT_CLICK "; break;}
        case L_HOLD: { std::cout << "Mouse Action: L_HOLD "; break;}
        case R_HOLD: { std::cout << "Mouse Action: R_HOLD "; break;}
        case UNCLICK: { std::cout << "Mouse Action: UNCLICK "; break;}
    }
    switch(mouseOver){
        case OBJECT: { std::cout << "Mouse Over: OBJECT"; break;}
        case SIZE_HANDLE: { std::cout << "Mouse Over: SIZE_HANDLE"; break;}
        case NOTHING: { std::cout << "Mouse Over: NOTHING"; break;}
        case OBJ_SELECTED: { std::cout << "Mouse Over: OBJECT SELECTED"; break;}
    }
    std::cout << std::endl;
}
void Designer::resetEnvironment()
{
    if(selectedShape != NULL){
        delete selectedShape;
        selectedShape = NULL;
    }
    if(pGenericMenu != NULL){
        delete pGenericMenu;
        pGenericMenu = NULL;
    }
    currentState = FREE;
    mouseAction = UNCLICK;
    mouseOver = mouseHovering();

    allShapes.clear();
    allShapesSize = 0;
    mChoice.pNum = 0;

}
/**PAUSE MENU**/
void Designer::showPausemenu()
{
    pMenu->makeVisible();

    while(pMenu->getVisible()){
        mChoice = pMenu->show(designerWindow);

        if(mChoice.pNum != 0){
            switch(mChoice.pNum){
                case 2: {saveMenu(); break;}
                case 3: {
                    if(loadstructures(getFileString())){
                        std::cout << "Loaded structures" << std::endl;
                    }
                    else{
                        pMenu->makeVisible();
                        std::cout << "Could not load structures" << std::endl;
                    }

                    break;
                }
                case 4: { returnCode = 1;}
            }
        }

        update();
    }
}
/**SAVE/LOAD STRUCTURES**/
std::string Designer::getFileString()
{
    pGetString->makeVisible();
    pGetString->resetPackage();

    mChoice.pNum = 0;
    mChoice.pString = "";

    while(pGetString->getVisible()){
        mChoice = pGetString->show(designerWindow);
        update();
    }

    std::cout << "Exiting File string loop" << "String =" << mChoice.pString << std::endl;

    if(mChoice.pString == ""){
        mChoice.pString = "NOSTRING";
    }

    return mChoice.pString;
}
bool Designer::loadstructures(std::string loadString)
{
    if(loadString == "NOSTRING"){
        std::cout << "No string given" << std::endl;
        return false;
    }
    if(loadString == "CANCEL"){
        std::cout << "Load canceled" << std::endl;
        return false;
    }

    SLobject = new SaveLoad(loadString);

    std::vector<sf::FloatRect> nStructures = SLobject->loadStructures();

    if(!nStructures.empty()){

        resetEnvironment();

        for(int i = 0; i < nStructures.size(); i++){

            sf::Vector2f nSize = sf::Vector2f(nStructures[i].width, nStructures[i].height);
            sf::Vector2f nPosition = sf::Vector2f(nStructures[i].left, nStructures[i].top);

            sf::RectangleShape nShape(nSize);
            nShape.setPosition(nPosition);
            nShape.setFillColor(sf::Color::Black);

            allShapes.push_back(nShape);
            allShapesSize++;
        }

        if(!allShapes.empty()){
            return true;
        }
        else{
            std::cout << "shapes did not add" << std::endl;
            return false;
        }
    }
    else{
        std::cout << "Empty file" << std::endl;
        return false;
    }

    return false;
}
void Designer::saveMenu()
{
    if(SLobject == NULL){
        saveAs();
    }
    else{
        //run save as / save current GUI
        pGenericMenu = new GUI_generic(sf::Vector2f(250, 75), sf::Vector2f(575, 300), pFont, false);
        pGenericMenu->addButton("Save");
        pGenericMenu->addButton("Save As");

        pGenericMenu->makeVisible();

        mChoice.pNum = 0;

        while(pGenericMenu->getVisible()){
            mChoice = pGenericMenu->show(designerWindow);
            update();
        }
        delete pGenericMenu;
        pGenericMenu = NULL;

        if(mChoice.pNum == 1){
            saveCurrent();
        }
        else if(mChoice.pNum == 2){
            saveAs();
        }
    }
}
void Designer::saveAs()
{
    if(SLobject != NULL){
        delete SLobject;
    }

    SLobject = new SaveLoad(getFileString());

    saveCurrent();
}
void Designer::saveCurrent()
{
    if(SLobject->getFileName() != ""){
        if(selectedShape != NULL){
            allShapes.push_back(*selectedShape);
        }

        SLobject->saveStructures(allShapes);

        if(selectedShape != NULL){
            allShapes.pop_back();
        }

        std::cout << "Saved structures to " << SLobject->getFileName() << std::endl;
        return;
    }

    std::cout << "Could not save structures. File name returned NULL" << std::endl;
}
/**STRUCTURE ADJUSTMENTS**/
void Designer::resizing()
{
    std::cout << "Resizing" << std::endl;

    mousePosition = sf::Mouse::getPosition(*designerWindow);

    for(int i = 0; i < 4; i++){
        if(handles[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))){
            if(handles[i].getFillColor() == sf::Color::Cyan){
                handleNumber = 1;
            }
            else if(handles[i].getFillColor() == sf::Color::Red){
                handleNumber = 2;
            }
            else if(handles[i].getFillColor() == sf::Color::Green){
            handleNumber = 3;
            }
            else{
                handleNumber = 4;
            }
        }
    }

    sf::FloatRect oldPos;
    sf::FloatRect newPos;

    while(mouseAction == L_HOLD){
        mousePosition = sf::Mouse::getPosition(*designerWindow);
        oldPos = selectedShape->getGlobalBounds();
        float newWidth, newHeight;

        switch(handleNumber){
            case 1: {
                selectedShape->setPosition(mousePosition.x, mousePosition.y);

                newWidth = (oldPos.left - mousePosition.x) + oldPos.width;
                newHeight = (oldPos.top - mousePosition.y) + oldPos.height;

                selectedShape->setSize(sf::Vector2f(newWidth, newHeight));

                break;
            }
            case 2:{
                selectedShape->setPosition(oldPos.left, mousePosition.y);

                newWidth = (mousePosition.x - (oldPos.left + oldPos.width)) + oldPos.width;
                newHeight = (oldPos.top - mousePosition.y) + oldPos.height;

                selectedShape->setSize(sf::Vector2f(newWidth, newHeight));

                break;
            }
            case 3:{
                newWidth = (mousePosition.x - (oldPos.left + oldPos.width)) + oldPos.width;
                newHeight = (mousePosition.y - (oldPos.top + oldPos.height)) + oldPos.height;

                selectedShape->setSize(sf::Vector2f(newWidth, newHeight));

                break;
            }
            case 4:{
                selectedShape->setPosition(mousePosition.x, oldPos.top);

                newWidth = (oldPos.left - mousePosition.x) + oldPos.width;
                newHeight = (mousePosition.y - (oldPos.top + oldPos.height)) + oldPos.height;

                selectedShape->setSize(sf::Vector2f(newWidth, newHeight));

                break;
            }
        }

        updateHandles();

        sf::Event resizeEvent;

        while (designerWindow->pollEvent(resizeEvent)){

			if(resizeEvent.type == sf::Event::MouseButtonReleased){
                mouseAction = UNCLICK;
                std::cout << "Mouse action: " << mouseAction << std::endl;
                changeState(UNCLICK);
			}
        }
        update();
    }
}
void Designer::dragging()
{
    std::cout << "Dragging" << std::endl;

    mousePosition = sf::Mouse::getPosition(*designerWindow);
    sf::FloatRect oldBounds = selectedShape->getGlobalBounds();
    float mouseXoffset = mousePosition.x - oldBounds.left;
    float mouseYoffset = mousePosition.y - oldBounds.top;
    float mouseXdifference, mouseYdifference;

    while(mouseAction == L_HOLD){
        mousePosition = sf::Mouse::getPosition(*designerWindow);
        oldBounds = selectedShape->getGlobalBounds();

        mouseXdifference = mousePosition.x - oldBounds.left;
        mouseYdifference = mousePosition.y - oldBounds.top;

        selectedShape->setPosition((oldBounds.left + mouseXdifference) - mouseXoffset, (oldBounds.top + mouseYdifference) - mouseYoffset);

        sf::Event dragEvent;

        while (designerWindow->pollEvent(dragEvent)){

			if(dragEvent.type == sf::Event::MouseButtonReleased){
                mouseAction = UNCLICK;
                std::cout << "Mouse action: " << mouseAction << std::endl;
                changeState(UNCLICK);
			}
/*			if(dragEvent.type == sf::Event::MouseMoved){
                sf::Vector2i newMousePos = sf::Mouse::getPosition(*designerWindow);
                selectedShape->move(newMousePos.x - mousePosition.x, newMousePos.y - mousePosition.y);
			}*/
		}

        updateHandles();

		update();
    }
}
void Designer::deleteRect()
{
    delete selectedShape;
    selectedShape = NULL;
}
/**CHECK MOUSE**/
void Designer::selected()
{
    if(findSelected()){
        if(handles.empty()){
            createHandles();
        }
        else{
            updateHandles();
        }
    }
}
Hovering Designer::mouseHovering()
{
    mousePosition = sf::Mouse::getPosition(*designerWindow);

    if(currentState == SELECTED){
        for(int i = 0; i < 4; i++){
            if(handles[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                return SIZE_HANDLE;
            }
        }
    }

    for(int i = 0; i < allShapesSize; i++){
        if(allShapes[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))){
            return OBJECT;
        }
    }

    return NOTHING;
}
Hovering Designer::hoveringSelected()
{
    mousePosition = sf::Mouse::getPosition(*designerWindow);

    if(selectedShape != NULL){

        for(int i = 0; i < 4; i++){
            if(handles[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                return SIZE_HANDLE;
            }
        }
        if(selectedShape->getGlobalBounds().contains(sf::Vector2f(mousePosition))){
            return OBJ_SELECTED;
        }
    }

    return NOTHING;
}
bool Designer::findSelected()
{
    mousePosition = sf::Mouse::getPosition(*designerWindow);

    if(selectedShape != NULL){
        if(selectedShape->getGlobalBounds().contains(sf::Vector2f(mousePosition))){
            return false;
        }

        for(int i = 0; i < allShapesSize; i++){
            if(allShapes[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                sf::RectangleShape putBack = *selectedShape;
                allShapes.push_back(putBack);
                selectedShape = new sf::RectangleShape(allShapes[i]);
                allShapes.erase(allShapes.begin()+i);

                updateHandles();
                return false;
            }
        }
    }

    for(int i = 0; i < allShapesSize; i++){
        if(allShapes[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))){
            selectedShape = new sf::RectangleShape(allShapes[i]);
            allShapes.erase(allShapes.begin()+i);
            allShapesSize --;
            std::cout << "found not selected" << std::endl;
            return true;
        }
    }

    selectedShape = NULL;
    return false;
}
/**ADD STRUCTURE**/
void Designer::addRectangle()
{
    sf::RectangleShape newRectangle(sf::Vector2f(100,100));
    newRectangle.setPosition(windowX_float/2, windowY_float/2);
    newRectangle.setFillColor(sf::Color::Black);

    allShapes.push_back(newRectangle);
    allShapesSize++;
    std::cout << "allShapesSize =" << allShapesSize << std::endl;
}
void Designer::createHandles()
{
    sf::FloatRect shapeRect = selectedShape->getGlobalBounds();

    sf::RectangleShape handle1(sf::Vector2f(10,10));
    sf::RectangleShape handle2(sf::Vector2f(10,10));
    sf::RectangleShape handle3(sf::Vector2f(10,10));
    sf::RectangleShape handle4(sf::Vector2f(10,10));

    handle1.setPosition(shapeRect.left-5, shapeRect.top-5);
    handle2.setPosition((shapeRect.left + shapeRect.width)-5, shapeRect.top-5);
    handle3.setPosition((shapeRect.left + shapeRect.width)-5, (shapeRect.top + shapeRect.height)-5);
    handle4.setPosition(shapeRect.left-5, (shapeRect.top + shapeRect.height)-5);

    handle1.setFillColor(sf::Color::Cyan);
    handle2.setFillColor(sf::Color::Red);
    handle3.setFillColor(sf::Color::Green);
    handle4.setFillColor(sf::Color::Blue);

    handles.push_back(handle1);
    handles.push_back(handle2);
    handles.push_back(handle3);
    handles.push_back(handle4);

}
void Designer::updateHandles()
{
    sf::FloatRect shapeRect = selectedShape->getGlobalBounds();

    handles[0].setPosition(shapeRect.left-5, shapeRect.top-5);
    handles[1].setPosition((shapeRect.left + shapeRect.width)-5, shapeRect.top-5);
    handles[2].setPosition((shapeRect.left + shapeRect.width)-5, (shapeRect.top + shapeRect.height)-5);
    handles[3].setPosition(shapeRect.left-5, (shapeRect.top + shapeRect.height)-5);
}
/**UPDATE DESIGNER**/
void Designer::update()
{
    //designerWindow->setView(*view);
	designerWindow->clear();

	designerWindow->draw(background);

	if(selectedShape != NULL){
        designerWindow->draw(*selectedShape);
	}

    for(int i = 0; i < allShapesSize; i ++){
        designerWindow->draw(allShapes[i]);
    }

    if(currentState != FREE){
        for(int i = 0; i < 4; i ++){
            designerWindow->draw(handles[i]);
        }
    }

    if(pMenu->getVisible()){
        designerWindow->draw(*pMenu);
    }
    if(pGetString->getVisible()){
        designerWindow->draw(*pGetString);
    }
    if(pGenericMenu != NULL){
        if(pGenericMenu->getVisible()){
            designerWindow->draw(*pGenericMenu);
        }
    }

	designerWindow->display();
}
Designer::~Designer()
{
    designerWindow = NULL;
}
