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
        bool loadstructures();
        bool saveAllStructures();

        int showPausemenu();
        void selected();
        void resizing();
        void dragging();
        void deselected();
        void deleteRect();

        void printStates();
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

        GUI_designerPaused* pMenu;
        int menuChoice;

        sf::RenderWindow* designerWindow;
        sf::View* view;
        sf::RectangleShape background;

        float windowX_float;
        float windowY_float;
};

#endif // DESIGNER_H
