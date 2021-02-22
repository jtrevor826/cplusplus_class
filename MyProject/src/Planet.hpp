/*
 * Planet.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: Family
 */

#ifndef PLANET_HPP_
#define PLANET_HPP_
#include <string>
#include <vector>
using namespace std;

struct Position{
    double x;
    double y;
};

class Planet{
    public:
    static const int PATH_LENGTH= 880;
    enum PlanetColor{WHITE, GREY, RED, GREEN, BLUE, YELLOW, BROWN, PURPLE, SKY, BEIGE};


	private:
    double mass;
	double posx;
	double posy;
	double velx;
	double vely;
	string name;
	Position path[PATH_LENGTH];
	int pathNext=0;
	int pathSize=0;
	double r,
	       g,
	       b;

	public:
	Planet();
	Planet(double positionx,double positiony,double kg,double velocityx,double velocityy, std::string nm, PlanetColor c);

	~Planet(){}

	string getName();
	void setName(std::string name);
	void setPathPoint(Position point);
	Position getPathPoint(unsigned offset);
	double getPositionX();
	double getPositionY();
	void setPosition(double newPosX, double newPosY);
	double getMass();
	double getRed();
	double getGreen();
	double getBlue();
	void setMass(double newMass);
	double getVelocityX();
	double getVelocityY();
	void setVelocity(double newVelX, double newVelY);
	int getPathSize();
	Position getPathAt(int offset);
	void translateColor(PlanetColor code);

	std::string toString();
	std::string toCsv();
};

#endif /* PLANET_HPP_ */
