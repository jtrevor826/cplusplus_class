#include <cmath>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "SolarSys.hpp"
using namespace std;
#define PI 3.14159265358979323846  /* pi */

SolarSys::SolarSys(): name{"unknown"},Central{}, Satellite{}, accelG{}, timeInterval{.01}, currentTime{0.}
{

}

SolarSys::SolarSys(string nm): name{nm},Central{}, Satellite{}, accelG{}, timeInterval{.01}, currentTime{0.}
{


}

SolarSys::~SolarSys()
{
    //dtor
}

void SolarSys::getGravity(){
    double bigGM = Central.getMass()*(double)(8.88799e-10);
    double dx, dy, dist2;
    accelG.clear();
    //cout << "in SolarSys::getGravity" <<endl;
    for (unsigned int i=0; i < Satellite.size(); i++){
    	dx=Satellite.at(i).getPositionX()-Central.getPositionX();
        dy=Satellite.at(i).getPositionY()-Central.getPositionY();
        dist2=dx*dx+dy*dy;
        if (!(std::abs(dist2)<0.000001)){
            accelG.push_back(bigGM/dist2); //We are actually calculating the acceleration, not the force.
        }
        else{
        	accelG.push_back(0);
        }
        centralForce+= bigGM/dist2*Satellite.at(i).getMass();
    }
}

void SolarSys::updatePosition(){
	double angle;
	double acceleration;

	centralForce=0;
	getGravity();

	for (unsigned int i=0; i < Satellite.size(); i++){
        if (!(std::abs(Satellite.at(i).getPositionX()-Central.getPositionX())<0.001)){
            angle = atan((Satellite.at(i).getPositionY()-Central.getPositionY())/(Satellite.at(i).getPositionX()-Central.getPositionX()));
            if ((Satellite.at(i).getPositionX()-Central.getPositionX())<0){
                angle += PI;
            }
        }else{
            if ((Satellite.at(i).getPositionY()-Central.getPositionY())>0){
                angle=PI/2.0;
            }else{
                angle=-PI/2.0;
            }
        }

        acceleration=accelG.at(i);
        Satellite.at(i).setVelocity((Satellite.at(i)).getVelocityX()-acceleration*cos(angle)*timeInterval,(Satellite.at(i)).getVelocityY()-acceleration*sin(angle)*timeInterval);
        Satellite.at(i).setPosition((Satellite.at(i)).getPositionX()+(Satellite.at(i)).getVelocityX()*timeInterval,(Satellite.at(i)).getPositionY()+Satellite.at(i).getVelocityY()*timeInterval);
	}
	currentTime+=timeInterval;
}

void SolarSys::addSatellite(Planet body){
    int sz =Satellite.size();
	Satellite.push_back(body);
	cout << Satellite.size()<<" "<< Satellite.at(sz).getName()<<endl;
}

void SolarSys::removeSatellite(string planetName){
	for (unsigned int i=0; i<Satellite.size(); i++){
	    if (Satellite.at(i).getName()==planetName){
	    	Satellite.erase(Satellite.begin()+i);
	    	break;
	    }
	}
}

void SolarSys::setCentralBody(Planet newCentralBody){
	Central = newCentralBody;
}

void SolarSys::setInterval(double interval){
	timeInterval=interval;
}

string SolarSys::toString(){
	string output="Solar System: " + name + "  at Time: ";
	output +="\n";
	output += Central.toString();
	for (unsigned int i = 0; i < Satellite.size(); i++){
		output += "  " + Satellite.at(i).toString();
	}
	return output;
}

Planet SolarSys::getSatellite(string planetName){

	Planet result = Planet();
	result.setName(planetName + " not found");
	for (unsigned int i=0; i<Satellite.size(); i++){
		if (Satellite.at(i).getName()==planetName){
			result = Satellite.at(i);
			break;
        }
	}
	return result;
}

string SolarSys::toCsv(bool outputTitleLine){
	string output;
	if (outputTitleLine){
		output="\"Planet\",\"X\",\"Y\",\"VelocityX\",\"VelocityY\",\"Mass\"\n";
	}
	else{
		output="";
	}
    output += Central.toCsv();
    for (unsigned int i = 0; i < Satellite.size(); i++){
		output += Satellite.at(i).toCsv();
	}
	return output;
}

string SolarSys::toCSV(bool outputTitleLine, string name){
    string output;
    char buffer[100];
    Planet tmp;
	if (outputTitleLine){
		output=name+"\n\"Time\",\"X\",\"Y\",\"VelocityX\",\"VelocityY\"\n";
	}
	else{
		output="";
	}
    tmp = getSatellite(name);
    sprintf(buffer,"%g,%g,%g,%g,%g\n",currentTime,tmp.getPositionX(),tmp.getPositionY(),tmp.getVelocityX(),tmp.getVelocityY());
    output+=buffer;
	return output;
}
