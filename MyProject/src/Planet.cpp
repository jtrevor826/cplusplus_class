/*
 * Planet.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: Family
 */

#include <string>
#include <cstdio>
#include "Planet.hpp"
using namespace std;

void Planet::translateColor(PlanetColor code){
switch (code){
        case WHITE:
            r=1.;
            g=1.0;
            b=1.0;
            break;
        case GREY:
            r=0.5;
            g=0.5;
            b=0.5;
            break;
        case RED:
            r=1.;
            g=0.;
            b=0.;
            break;
        case GREEN:
            r=0.;
            g=1.;
            b=0.;
            break;
        case BLUE:
            r=0.0;
            g=0.0;
            b=1.0;
            break;
        case YELLOW:
            r=1.0;
            g=1.0;
            b=0.0;
            break;
        case BROWN:
            r=0.60;
            g=0.20;
            b=0.20;
            break;
        case BEIGE:
            r=0.8;
            g=0.8;
            b=0.6;
            break;
        case PURPLE:
            r=0.70;
            g=0.0;
            b=0.70;
            break;
        case SKY:
            r=.5;
            g=0.5;
            b=1.;
            break;
        default:
            r=1.;
            g=1.0;
            b=1.0;
            break;
        }


}

Planet::Planet(double positionx,double positiony,double kg,double velocityx,double velocityy, string nm, PlanetColor code):
    mass{kg},posx{positionx},posy{positiony},velx{velocityx},vely{velocityy},name{nm}{
        translateColor(code);
}

Planet::Planet(): mass{0.},posx{0.0},posy{0.0},velx{0.0},vely{0.0},name{"unknown"}{
    pathNext=0;
    pathSize=0;

}


string Planet::getName(){
	return name;
}

void Planet::setName(string name){
	this->name=name;
}

double Planet::getRed(){
    return r;
}

double Planet::getGreen(){
    return g;
}

double Planet::getBlue(){
    return b;
}

void Planet::setPathPoint(Position point){

    path[pathNext].x= point.x;
    path[pathNext].y=point.y;

    pathNext = (pathNext+1) % PATH_LENGTH;
    if(pathSize < PATH_LENGTH){
        pathSize++;
    }

}

double Planet::getPositionX(){
	return posx;
}

double Planet::getPositionY(){
	return posy;
}

void Planet::setPosition(double newPosX, double newPosY){
    Position hold;

	posx = newPosX;
	posy = newPosY;
	hold.x = posx;
	hold.y = posy;
	setPathPoint(hold);
}

double Planet::getMass(){
	return mass;
}

void Planet::setMass(double newMass){
	mass=newMass;
}

double Planet::getVelocityX(){
	return velx;
}

double Planet::getVelocityY(){
	return vely;
}

void Planet::setVelocity(double newVelX, double newVelY){
	velx=newVelX;
	vely=newVelY;
}

int Planet::getPathSize(){
    return pathSize;
}

Position Planet::getPathAt(int offset){
    Position val;
    if(offset >= PATH_LENGTH  || offset >= pathSize){
        val=path[0];
    }else{
        val = path[offset];
    }
    return val;
}

string Planet::toString(){
    string result;
    char buffer[100];

    result = name + "\n  ";
    sprintf(buffer,"Position: ( %g, %g )\n  ",getPositionX(),getPositionY());
    result += buffer;
    sprintf(buffer,"Velocity: ( %g, %g )\n  ",velx, vely);
    result += buffer;
    sprintf(buffer,"Mass: %g\n",mass);
    result += buffer;

    return result;
}

string Planet::toCsv(){
	string result;
	    char buffer[100];

	    result = "\"" + name + "\",";
	    sprintf(buffer,"%g,%g,",getPositionX(),getPositionY());
	    result += buffer;
	    sprintf(buffer,"%g,%g,",velx, vely);
	    result += buffer;
	    sprintf(buffer,"%g\n",mass);
	    result += buffer;

	    return result;
}
