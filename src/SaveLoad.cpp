#include "SaveLoad.h"

/*********************
 **    SAVE/LOAD    **
 *********************/
SaveLoad::SaveLoad()
{
    //ctor
}
SaveLoad::SaveLoad(const std::string nameOfFile)
{
    changeFileName(nameOfFile);
}
void SaveLoad::changeFileName(std::string nameOfFile)
{
    if(nameOfFile == "NOSTRING"){
        std::cout << "No string for file name" << std::endl;
    }
    else{
        if(nameOfFile.length() > 4){
            if(nameOfFile.substr(nameOfFile.length() - 4) != ".txt"){
                nameOfFile += ".txt";
            }
        }
        else{
            nameOfFile += ".txt";
        }

        fileName = "saves/" + nameOfFile;
    }
}
std::string SaveLoad::getFileName()
{
    return fileName;
}
void SaveLoad::makeFile()
{
    std::ofstream outfile(fileName.c_str());
    outfile << "" << std::endl;
    outfile.close();
}
void SaveLoad::saveStructures(std::vector<sf::RectangleShape> allShapes)
{
    writeFile.open(fileName.c_str());

    if(!allShapes.empty()){
        for(int i = 0; i < allShapes.size(); i++){

            sf::FloatRect toSave = allShapes[i].getGlobalBounds();

            writeFile << toSave.left << "%" << toSave.top << "%" << toSave.width << "%" << toSave.height << "% \n";
        }
    }

    writeFile.close();
}
std::vector<sf::FloatRect> SaveLoad::loadStructures()
{
    std::string line;
    std::string token;

    loadFile.open(fileName.c_str());

    if(!loadFile.is_open()){
        std::cout << "Couldn't open file - invalid string or can't locate file." << std::endl;
    }
    else{
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
