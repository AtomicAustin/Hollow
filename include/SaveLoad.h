#ifndef SAVELOAD_H
#define SAVELOAD_H

#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

class SaveLoad
{
    public:
        SaveLoad();
        SaveLoad(const std::string);
        void changeFileName(const std::string);
        std::string getFileName();
        void saveStructures(std::vector<sf::RectangleShape>);
        std::vector<sf::FloatRect> loadStructures();
        int returnToken(std::string&);
        virtual ~SaveLoad();

    protected:

    private:
        std::ofstream writeFile;
        std::ifstream loadFile;
        std::string fileName;
        std::vector<sf::FloatRect> loadedStructures;
};

#endif // SAVELOAD_H
