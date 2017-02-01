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

    float left1 = p.left;
    float top1 = p.top;
    float right1 = p.left + p.width;
    float bottom1 = p.top + p.height;

    float left2, top2, right2, bottom2;

    for(int i = 0; i < structuresSize; i++){

        left2 = staticStructures[i].left;
        top2 = staticStructures[i].top;
        right2 = left2 + staticStructures[i].width;
        bottom2 = top2 + staticStructures[i].height;

        if(right1 > left2 && right1 < right2){
            if(bottom1 > top2 && bottom1 < bottom2){
                if(axisCheck(right1, bottom1, left2, top2)){
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
            if(top1 > top2 && top1 < bottom2){
                if(axisCheck(right1, bottom2, left2, top1)){
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
        }
        if(left1 > left2 &&  left1 < right2){
            if(top1 > top2 && top1 < bottom2){
                if(axisCheck(right2, bottom2, left1, top1))
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
            if(bottom1 > top2 && bottom1 < bottom2){
                if(axisCheck(right2, bottom1, left1, top2)){
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
    }

	return newPackage;
}
Structure_Collider::~Structure_Collider()
{
    //dtor
}
