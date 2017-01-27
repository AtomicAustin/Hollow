#include "collision.h"

Structure_Collider::Structure_Collider()
: structuresSize(0)
{
    //ctor
}
void Structure_Collider::addStructure(sf::FloatRect structure)
{
    staticStructures.push_back(structure);
    structuresSize++;
}
bool Structure_Collider::axisCheck(float x1, float y1, float x2, float y2)
{
	if((x1 - x2) >= (y1 - y2))
		return true;
	else
		return false;
}
collidedPackage Structure_Collider::checkCollision(sf::FloatRect p)
{
    collidedPackage newPackage;

    for(int i = 0; i < structuresSize; i++){

        float x1 = p.left;
        float y1 = p.top;
        float w1 = p.width;
        float h1 = p.height;

        float x2 = staticStructures[i].left;
        float y2 = staticStructures[i].top;
        float w2 = staticStructures[i].width;
        float h2 = staticStructures[i].height;

        if(x1 > x2 &&  x1 < x2+w2){
            if(y1 > y2 && y1 < y2+h2){
                if(axisCheck(x2+w2,y2+h2,x1,y1))
                {
                    newPackage.hit = 2;
                    newPackage.bounds = staticStructures[i];
                    return newPackage; //bottom
                }
                else{
                    newPackage.hit = 4;
                    newPackage.bounds = staticStructures[i];
                    return newPackage; //right
                }
            }
            if(y1+h1 > y2 && y1+h1 < y2+h2){
                if(axisCheck(x2+w2,y1+h1,x1,y2)){
                    newPackage.hit = 1;
                    newPackage.bounds = staticStructures[i];
                    return newPackage; //top
                }
                else{
                    newPackage.hit = 4;
                    newPackage.bounds = staticStructures[i];
                    return newPackage; //right
                }
            }
        }
        if(x1+w1 > x2 && x1+w1 < x2+w2){
            if(y1 > y2 && y1 < y2+h2){
                if(axisCheck(x1+w1,y2+h2,x2,y1)){
                    newPackage.hit = 2;
                    newPackage.bounds = staticStructures[i];
                    return newPackage; //bottom
                }
                else{
                    newPackage.hit = 3;
                    newPackage.bounds = staticStructures[i];
                    return newPackage; //left
                }
            }
            if(y1+h1 > y2 && y1+h1 < y2+h2){
                if(axisCheck(x1+w1,y1+h1,x2,y2)){
                    newPackage.hit = 1;
                    newPackage.bounds = staticStructures[i];
                    return newPackage; //top
                }
                else{
                    newPackage.hit = 3;
                    newPackage.bounds = staticStructures[i];
                    return newPackage; //left
                }
            }
        }
    }

	return newPackage;
}
Structure_Collider::~Structure_Collider()
{
    //dtor
}
