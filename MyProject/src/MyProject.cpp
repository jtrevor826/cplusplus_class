//============================================================================
// Name        : MyProject.cpp
// Author      : Trevor
// Version     :
// Copyright   :
// Description : Good description
//============================================================================

/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <chrono>
#include "Planet.hpp"
#include "SolarSys.hpp"


bool side[8];
SolarSys  SolSys;
double sunRadius =109;
Planet mercury,
       venus,
	   earth,
	   mars,
	   jupiter,
	   saturn,
	   uranus,
	   neptune;
double DISPLAY_WIDTH =31;
double const PI=3.14159265358979;
double centerX = 0;
double centerY = 0;
//struct Position pointsSun[20];
int planetDisplay = 0;


/* GLUT callback Handlers */
/*
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}
*/

void displayText( float x, float y, int r, int g, int b, const char *string ) {
    int j = strlen( string );

    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, string[i] );
    }
}


static void display(void)
{
	glutUseLayer(GLUT_NORMAL);
    Position grid[20];
    double deltaAngle = PI/10;

//    for(int i =0; i < 20; i++){
//        pointsSun[i].x= (SolSys.Central.getPositionX()+cos(i*deltaAngle)*sunRadius)/DISPLAY_WIDTH;
//        pointsSun[i].y= (SolSys.Central.getPositionY()+sin(i*deltaAngle)*sunRadius)/DISPLAY_WIDTH;
//    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    //gluLookAt(centerX,centerY,1.0,centerX,centerY,0,0.0,1.0,0.0);

    for(int r=0; r<20; r++){
        grid[r].x= cos(r*deltaAngle);
        grid[r].y= sin(r*deltaAngle);
    }
    //grid
    glPointSize(0.05f);
    glColor3f(0.2f, 0.2f,0.2f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f,0.f-centerY/DISPLAY_WIDTH);
        glVertex2f(1.0f,0.f-centerY/DISPLAY_WIDTH);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(0.f-centerX/DISPLAY_WIDTH,-1.0f);
        glVertex2f(0.f-centerX/DISPLAY_WIDTH,1.0f);
    glEnd();

    for(int t=1; t<36; t++){
        glBegin(GL_LINE_LOOP);
        for(int i =0; i <20; i++){
            glVertex2f((grid[i].x*t-centerX)/DISPLAY_WIDTH, (grid[i].y*t-centerY)/DISPLAY_WIDTH);
        }
        glEnd();
    }

    //glColor3f(1.0f,1.f,0.f);
    //central planet plot
    //glPointSize(0.50f);
//    glBegin(GL_POLYGON);
//    for (int i =0; i<20; i++){
//        glVertex2f(pointsSun[i].x-centerX/DISPLAY_WIDTH, pointsSun[i].y-centerY/DISPLAY_WIDTH);
//    }
//    glEnd();
/*
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i =0; i<20; i++){
        glVertex2f(pointsSun[i].x, pointsSun[i].y);
    }
    glEnd();
*/
    //satellite plots
    for (int i = 0; i < SolSys.Satellite.size(); i++){
        //SolSys.Satellite.at(i).addPoint();
        glPointSize(.2f);
        for(int j=0; j <SolSys.Satellite.at(i).getPathSize(); j++){
        glBegin(GL_POINTS);
            glColor3f(SolSys.Satellite.at(i).getRed(), SolSys.Satellite.at(i).getGreen(), SolSys.Satellite.at(i).getBlue());
            glVertex2f(((float)SolSys.Satellite.at(i).getPathAt(j).x-centerX)/DISPLAY_WIDTH, ((float)SolSys.Satellite.at(i).getPathAt(j).y-centerY)/DISPLAY_WIDTH);
        glEnd();
        }
        glPointSize(2.f);
        glBegin(GL_POINTS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(((float)SolSys.Satellite.at(i).getPositionX()-centerX)/DISPLAY_WIDTH, ((float)SolSys.Satellite.at(i).getPositionY()-centerY)/DISPLAY_WIDTH);
        glEnd();
    }

    glutUseLayer(GLUT_OVERLAY);

    glBegin(GL_LINE_LOOP);
    glColor3f(1.f,1.f,1.f);
    glVertex2f(0.95f,0.95f);
    glVertex2f(0.95f,0.55f);
    glVertex2f(0.65f,0.55f);
    glVertex2f(0.65f,0.95f);
    glEnd();

    // for (int i = 1; i < SolSys.Satellite.size(); i++){
    //	if ((SolSys.Satellite.at(i).getPositionX()-centerX)/LIMIT < 0.95 && (SolSys.Satellite.at(i).getPositionX()-centerX)/LIMIT > 0.65 && (SolSys.Satellite.at(i).getPositionY()-centerY)/LIMIT < 0.95 && (SolSys.Satellite.at(i).getPositionY()-centerY)/LIMIT > 0.55){
    //    	if ( i < planetDisplay ) {
    //            planetDisplay = i;
    //    	}
    //	}
    //}

   // if ( planetDisplay != NULL){
        char buffer[100];
        string name = SolSys.Satellite.at(planetDisplay).getName();
        sprintf (buffer, "%s \n", name.c_str());
        //sprintf(buffer, "%s", SolSys.Satellite.at(planetDisplay).getName());
        displayText(0.66f, 0.9f, 1, 1, 1, buffer);
        sprintf(buffer, "Mass: %g", SolSys.Satellite.at(planetDisplay).getMass());
        displayText(0.66f, 0.85f, 1, 1, 1, buffer);
        sprintf(buffer, "Position: (%g,", SolSys.Satellite.at(planetDisplay).getPositionX());
        displayText(0.66f, 0.8f, 1, 1, 1, buffer);
        sprintf(buffer, "%g)", SolSys.Satellite.at(planetDisplay).getPositionY());
        displayText(0.66f, 0.78f, 1, 1, 1, buffer);
        sprintf(buffer, "Velocity: (%g,", SolSys.Satellite.at(planetDisplay).getVelocityX());
        displayText(0.66f, 0.73f, 1, 1, 1, buffer);;
        sprintf(buffer, "%g)", SolSys.Satellite.at(planetDisplay).getVelocityY());
        displayText(0.66f, 0.71f, 1, 1, 1, buffer);
    //}

    glPopMatrix();
    glutSwapBuffers();
    SolSys.updatePosition();
    /*for (int i = 0; i < SolSys.Satellite.size(); i++){
    	if (side[i] == false && SolSys.Satellite.at(i).getPositionX() >= 0){
    		SolSys.Satellite.at(i).reset();
    	}
    	side[i] = (SolSys.Satellite.at(i).getPositionX() >= 0);
    }*/

}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+':
    	if (DISPLAY_WIDTH >=2){
    	    DISPLAY_WIDTH--;
    	}
        /*SolSys.Satellite.at(0).setVelocity(SolSys.Satellite.at(0).getVelocityX()*1.1,SolSys.Satellite.at(0).getVelocityY()*1.1);
        SolSys.Satellite.at(1).setVelocity(SolSys.Satellite.at(1).getVelocityX()*1.1,SolSys.Satellite.at(1).getVelocityY()*1.1);*/
        break;

    case '-':
    	if (DISPLAY_WIDTH <32){
            DISPLAY_WIDTH++;
        }
        /*SolSys.Satellite.at(0).setVelocity(SolSys.Satellite.at(0).getVelocityX()/1.1,SolSys.Satellite.at(0).getVelocityY()/1.1);
        SolSys.Satellite.at(1).setVelocity(SolSys.Satellite.at(1).getVelocityX()/1.1,SolSys.Satellite.at(1).getVelocityY()/1.1);*/
        break;
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'w':
        	centerY += 1.0;
            //SolSys.Central.setPosition(SolSys.Central.getPositionX(),SolSys.Central.getPositionY()+10000000);
            break;
        case 's':
        	centerY -= 1.0;
            //SolSys.Central.setPosition(SolSys.Central.getPositionX(),SolSys.Central.getPositionY()-10000000);
            break;
        case 'a':
        	centerX -= 1.0;
            //SolSys.Central.setPosition(SolSys.Central.getPositionX()-10000000,SolSys.Central.getPositionY());
            break;
        case 'd':
        	centerX += 1.0;
            //SolSys.Central.setPosition(SolSys.Central.getPositionX()+10000000,SolSys.Central.getPositionY());
            break;
    }

    glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
switch(key)
{
break;
case GLUT_KEY_LEFT:
	planetDisplay = (planetDisplay+7)%8;
break;
case GLUT_KEY_RIGHT:
	planetDisplay = (planetDisplay+1)%8;
break;
}
}

static void idle(void)
{
    glutPostRedisplay();
}
/*
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
*/
/* Program entry point */

int main(int argc, char *argv[])
{

	SolSys = SolarSys("Sol Simulation");
	SolSys.setCentralBody(Planet(0.0, 0.0, 3.3295e5, 0.0, 0.0, "Sol", Planet::WHITE));
    SolSys.addSatellite(Planet(.387, 0.0, 5.52729e-2, 0.0, 0.0276, "Mercury", Planet::GREY));
    SolSys.addSatellite(Planet(.723332, 0.0, .815, 0.0, 2.02257e-2, "Venus", Planet::BEIGE));
    SolSys.addSatellite(Planet(1., 0.0, 1., 0.0, 0.017199, "Earth", Planet::BLUE));
    SolSys.addSatellite(Planet(1.52368, 0.0, .107446, 0.0, 0.0138652, "Mars", Planet::RED));
    SolSys.addSatellite(Planet(5.2044, 0.0, 317.83, 0.0, 0.00754856, "Jupiter", Planet::BROWN));
    SolSys.addSatellite(Planet(9.5826, 0.0, 95.1616, 0.0, 0.00559067, "Saturn", Planet::YELLOW));
    SolSys.addSatellite(Planet(19.184, 0.0, 14.5353, 0.0, 0.00392733, "Uranus", Planet::SKY));
    SolSys.addSatellite(Planet(30.33, 0.0, 17.1456, 0.0, 0.0031361, "Neptune", Planet::PURPLE));
    //high_resolution_clock::time_point t0 = high_resolution_clock::now();
    for (int i = 0; i < SolSys.Satellite.size(); i++){
    	side[i]=true;
    }


    glutInit(&argc, argv);
    glutInitWindowSize(1400,1400);

    //glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Solar System");
    glutEstablishOverlay();

    //glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(SpecialInput);
    glutIdleFunc(idle);
/*
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
*/
    glutMainLoop();

    return EXIT_SUCCESS;
}
