/*
 * SolarSys.hpp
 *
 *  Created on: Aug 27, 2020
 *      Author: Family
 */

#ifndef SOLARSYS_HPP_
#define SOLARSYS_HPP_
#include <string>
#include <cmath>
#include <vector>
#include "Planet.hpp"
using namespace std;

class SolarSys
{
    public:
	    SolarSys();
	    SolarSys(string nm);
        virtual ~SolarSys();

        void updatePosition();
        string toString();
        void addSatellite(Planet body);
        Planet getSatellite(string planetName);
        void removeSatellite(string planetName);
        void setCentralBody(Planet newCentralBody);
        void setInterval(double interval);
        string name;
        string toCsv(bool outputTitleLine);
        string toCSV(bool outputTitleLine, string name);
        vector<Planet> Satellite;
        Planet Central;
        double centralForce;


    private:
        vector<double> accelG;
        double timeInterval;
        double currentTime;
        void getGravity();
};

#endif // SOLARSYS_HPP_

