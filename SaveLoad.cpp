#include "SaveLoad.h"

SaveLoad::SaveLoad()
{
    //ctor
}
SaveLoad::SaveLoad(const std::string nameOfFile) : fileName(nameOfFile)
{

}
void SaveLoad::saveStructures(std::vector<sf::RectangleShape> allShapes)
{
    writeFile.open(fileName.c_str());

    for(int i = 0; i < allShapes.size(); i++){

        sf::FloatRect toSave = allShapes[i].getGlobalBounds();

        writeFile << toSave.left << "%" << toSave.top << "%" << toSave.width << "%" << toSave.height << "% \n";
    }

    writeFile.close();
}
void SaveLoad::changeFileName(const std::string newFilename)
{
    fileName = newFilename;
}
std::string SaveLoad::getFileName()
{
    return fileName;
}
std::vector<sf::FloatRect> SaveLoad::loadStructures()
{
    std::string line;
    std::string token;

    loadFile.open(fileName.c_str());

    if(loadFile.is_open()){
        while(std::getline(loadFile, line)){
            sf::FloatRect newRect;

            newRect.left = returnToken(line);
            newRect.top = returnToken(line);
            newRect.width = returnToken(line);
            newRect.height = returnToken(line);

            loadedStructures.push_back(newRect);
        }
    }

    return loadedStructures;

}
int SaveLoad::returnToken(std::string& newLine)
{
    std::string token;

    size_t position = newLine.find("%");

    token = newLine.substr(0, position);

    newLine.erase(0, token.length()+1);

    return atoi(token.c_str());
}
SaveLoad::~SaveLoad()
{
    //dtor
}
