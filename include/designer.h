#ifndef DESIGNER_H
#define DESIGNER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SaveLoad.h"
#include "GUI_Systems.h"

enum State { FREE, SELECTED, DRAGGING, RESIZING };
enum Action { LEFT_CLICK, RIGHT_CLICK, L_HOLD, R_HOLD, UNCLICK};
enum Hovering { OBJECT, SIZE_HANDLE, NOTHING, OBJ_SELECTED};

class Designer
{
    public:
        Designer();
        int environmentDisplay(sf::RenderWindow* window);
        void setUp();

        std::string getFileString();
        bool loadstructures(std::string loadString);
        void saveMenu();
        void saveAs();
        void saveCurrent();

        void showPausemenu();
        void selected();
        void resizing();
        void dragging();
        void deselected();
        void deleteRect();

        void printStates();
        void resetEnvironment();
        void changeState(Action mAction);

        Hovering mouseHovering();
        Hovering hoveringSelected();
        bool findSelected();

        void addRectangle();
        void createHandles();
        void updateHandles();

        void update();

        virtual ~Designer();

    protected:

    private:
        int returnCode;

        SaveLoad* SLobject;

        Action mouseAction;

        State currentState;
        State previousState;

        Hovering mouseOver;
        sf::Vector2i mousePosition;

        std::vector<sf::RectangleShape> allShapes;
        int allShapesSize;

        std::vector<sf::RectangleShape> handles;
        int handleNumber;

        sf::RectangleShape* selectedShape;

        sf::Font* pFont;
        GUI_designerPaused* pMenu;
        GUI_getString* pGetString;
        GUI_generic* pGenericMenu;
        inputPackage mChoice;

        sf::RenderWindow* designerWindow;
        sf::View* view;
        sf::RectangleShape background;

        float windowX_float;
        float windowY_float;
};

#endif // DESIGNER_H
