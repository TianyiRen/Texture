//
//  main.cpp
//  test07
//
//  Created by Tianyi on 2/25/14.
//  Copyright (c) 2014 tianyi. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdio>

#include <CoreGraphics/CoreGraphics.h>
#include <OpenGL/gl.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include "glm.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "Mouse.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Texture.h"
#include "vector3f.h"
#include "Viewport.h"
#include "Math.h"


using namespace std;

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;
const char* WINDOW_TITLE = "Glut";

const float MOUSE_SENSITIVITY = 1.0;
const float WALKING_SPEED = 1.1; //one meter
const float MAX_TILT = 85;

Texture* tex;

float LAST_TIME;
float CURRENT_TIME;
float DELTA_TIME;

void display();
void reshape (int w, int h);
void drawTriangles();
void inputActions();
void createSphere(int PointRows, int PointsPerRow);
void DrawCube(void);
void idle(void);
void setupLight();


void test();




int main(int argc, char ** argv)
{
    
    //Initilize GLUT and OpenGL
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    //Create Window
    glutCreateWindow(WINDOW_TITLE);
    
        //Reshape
    glutReshapeFunc(reshape);
    
    //Setup GLUT Callback Functions
    glutDisplayFunc(display);
    glutIdleFunc(display);
    
    glutKeyboardFunc(Keyboard::keyDown);
    glutKeyboardUpFunc(Keyboard::keyUp);
    
    glutMotionFunc(Mouse::move);
    glutPassiveMotionFunc(Mouse::move);
    
    glutMouseFunc(Mouse::click);
    
    //Enable Features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    //glDepthFunc(GL_LESS);
    
    
    //Setup Context
    
    CGSetLocalEventsSuppressionInterval(0);
    tex = Texture::loadBMP("ssand.bmp");
    if (!tex)
    {
        return 1;
    }
    
    
    Camera::position.y = 0.5;
    Camera::position.z = -2.0;
    
    
    //Enter Main Loop
    glutMainLoop();
    
    return 0;
}
void DrawCube()
{
	//Draws a cube with two shaded, two one-colored and two textured faces
  
    
	glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0);
    //front:
    
    glVertex3f(-0.5,-0.5,0.5);
    glVertex3f(-0.5,0.5,0.5);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,-0.5,0.5);
    
    //back:
    glColor3f(0.0,0.0,1.0);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(0.5,-0.5,-0.5);
    glVertex3f(0.5,0.5,-0.5);
    glVertex3f(-0.5,0.5,-0.5);
    
    //top:
    glColor3f(0.0,0.6,1.0);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(0.5,0.5,-0.5	);
    glColor3f(1.0,0.6,1.0);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(-0.5,0.5,0.5);
    
    //bottom:
    glColor3f(0.0,0.6,0.0);
    glVertex3f(-0.5,-0.5,-0.5);
    glColor3f(0.6,0.6,0.6);
    glVertex3f(-0.5,-0.5,0.5);
    glColor3f(1.0,1.0,0.3);
    glVertex3f(0.5,-0.5,0.5);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.5,-0.5,-0.5);
	glEnd();
    
    glPopMatrix();
    glPopAttrib();

    
    
}
void reshape (int w, int h)
{
    Viewport::width = w;
    Viewport::height = h;
    if(h ==0)
    {
        h=1;
    }
    float ratio = (float)w/h;
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    glViewport(0,0,w,h);
    
    gluPerspective(45, ratio, 0.01, 100);
    
    glMatrixMode(GL_MODELVIEW);
    
}

void inputActions()
{
    
    CURRENT_TIME = ((float)glutGet(GLUT_ELAPSED_TIME)) / 1000;
    DELTA_TIME = CURRENT_TIME - LAST_TIME;
    LAST_TIME = CURRENT_TIME;
    
    
    Mouse::update();
    
    //Process mouse
    Camera::rotation.y += (float)Mouse::deltaX * MOUSE_SENSITIVITY;
    Camera::rotation.x += (float)Mouse::deltaY * MOUSE_SENSITIVITY;
    
    if(Camera::rotation.x > MAX_TILT)
        Camera::rotation.x = MAX_TILT;
    if(Camera::rotation.x < - MAX_TILT)
        Camera::rotation.x = -MAX_TILT;
    
    
    
    //Process keys
    if (Keyboard::key['w'])
    {
        //move forward
        //CAMERA_POSITION.z += WALKING_SPEED * DELTA_TIME;
        Camera::position.x += (WALKING_SPEED * DELTA_TIME) * Math::dsin(Camera::rotation.y);
        Camera::position.z += (WALKING_SPEED * DELTA_TIME) * Math::dcos(Camera::rotation.y);
        
    }
    if (Keyboard::key['s'])
    {
        //move backward
        //CAMERA_POSITION.z -= WALKING_SPEED * DELTA_TIME;
        Camera::position.x += (WALKING_SPEED * DELTA_TIME) * Math::dsin(Camera::rotation.y + 180);
        Camera::position.z += (WALKING_SPEED * DELTA_TIME) * Math::dcos(Camera::rotation.y + 180);
    }
    if (Keyboard::key['a'])
    {
        //move left
        //CAMERA_POSITION.x -= WALKING_SPEED * DELTA_TIME;
        Camera::position.x += (WALKING_SPEED * DELTA_TIME) * Math::dsin(Camera::rotation.y + 270);
        Camera::position.z += (WALKING_SPEED * DELTA_TIME) * Math::dcos(Camera::rotation.y + 270);
    }
    if (Keyboard::key['d'])
    {
        //move right
        //CAMERA_POSITION.x += WALKING_SPEED * DELTA_TIME;
        Camera::position.x += (WALKING_SPEED * DELTA_TIME) * Math::dsin(Camera::rotation.y + 90);
        Camera::position.z += (WALKING_SPEED * DELTA_TIME) * Math::dcos(Camera::rotation.y + 90);
    }
    if (Keyboard::key[' '])
    {
        //jump
        //CAMERA_POSITION.z += 0.01;
        Viewport::setGrabbed();
        
    }
    if (Keyboard::key[27])
    {
        Viewport::setUnGrabbed();
    }
}

void drawObstaclesX(float x, float y, float z)
{
    
        glBegin(GL_QUADS);
        
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(x, y, z);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(x, y, z-1);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x, y+1, z);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x, y+1, z-1);
    
        
        glEnd();
        
    
    
    
}

void drawObstaclesY(float x, float y, float z)
{
    
    glBegin(GL_QUADS);
    
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x, y, z);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(x, y, z-1);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x+1, y, z);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x+1, y, z-1);
    
    
    glEnd();
    
    
    
    
}

void drawObstaclesZ(float x, float y, float z)
{
    
    glBegin(GL_QUADS);
    
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x, y+1, z);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(x, y, z);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x+1, y, z);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x+1, y+1, z);
    
    
    glEnd();
    
    
    
    
}
void display()
{
    inputActions();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    
    Texture* sphereTex = Texture::loadBMP("tex1.bmp");
    glBindTexture( GL_TEXTURE_2D, sphereTex->getTextureID());
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    
    glutSolidSphere(0.5, 20, 20);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    

    //Camera transformations
    glRotatef(Camera::rotation.x, 1, 0, 0);
    glRotatef(Camera::rotation.y, 0, 1, 0);
    glRotatef(Camera::rotation.z, 0, 0, 1);
    glTranslatef(-Camera::position.x, -Camera::position.y, Camera::position.z);
    
    
    drawObstaclesX(1, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(1, 0, -6);
    
    drawObstaclesX(2, 0, -4);
    //drawObstaclesX(2, 0, -5);
    drawObstaclesX(2, 0, -6);
    
    drawObstaclesX(3, 0, -4);
    //drawObstaclesX(3, 0, -5);
    drawObstaclesX(3, 0, -6);
    
    drawObstaclesX(4, 0, -4);
    //drawObstaclesX(4, 0, -5);
    drawObstaclesX(4, 0, -6);
    
    drawObstaclesX(5, 0, -4);
    //drawObstaclesX(5, 0, -5);
    drawObstaclesX(5, 0, -6);
    
    drawObstaclesX(6, 0, -4);
    //drawObstaclesX(6, 0, -5);
    drawObstaclesX(6, 0, -6);
    
    drawObstaclesX(7, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(7, 0, -6);

    drawObstaclesX(8, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(8, 0, -6);
    
    drawObstaclesX(9, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(9, 0, -6);

    
    drawObstaclesX(10, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(10, 0, -6);

    drawObstaclesX(11, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(11, 0, -6);

    drawObstaclesX(12, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(12, 0, -6);

    drawObstaclesX(13, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(13, 0, -6);

    drawObstaclesX(14, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(14, 0, -6);

    drawObstaclesX(15, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(15, 0, -6);

    drawObstaclesX(16, 0, -4);
    //drawObstaclesX(1, 0, -5);
    drawObstaclesX(16, 0, -6);
    
    drawObstaclesZ(16, 0, -6);
    drawObstaclesZ(18, 0, -5);
    
    
    drawObstaclesZ(16, 0, -6);
    drawObstaclesZ(18, 0, -6);
    
    drawObstaclesZ(16, 0, -5);
    drawObstaclesZ(18, 0, -5);
    
    drawObstaclesZ(16, 0, -4);
    drawObstaclesZ(18, 0, -4);
    
    drawObstaclesZ(16, 0, -3);
    drawObstaclesZ(18, 0, -3);
    


    GLMmodel* model;
    model = glmReadOBJ("SideTable2.obj");
    glmDraw(model, GL_SMOOTH | GL_TEXTURE);





    
    

    Texture* sphereTex2 = Texture::loadBMP("tex2.bmp");
    glBindTexture( GL_TEXTURE_2D, sphereTex2->getTextureID());
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    
    glutSolidSphere(0.1, 20, 20);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    DrawCube();
    
    test();
    
    
    
    glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(100,100);
    glVertex3f(100, 0, 100);
    
    glTexCoord2f(-100, 100);
    glVertex3f(-100, 0, 100);
    
    glTexCoord2f(-100, -100);
    glVertex3f(-100, 0, -100);
    
    glTexCoord2f(100, -100);
    glVertex3f(100, 0, -100);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    glutSwapBuffers();
}
void setupLight()
{
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	//Put one light above each of the four corners
	int index = 0;
	for(float z = 0; z < 2; z += 1) {
		for(float x = 0; x < 2; x += 1) {
			glEnable(GL_LIGHT0 + index);
			GLfloat lightColor[] = {0.5f, 0.5f, 1.0f, 1};
			GLfloat lightPos[] = {x, 1.5f, z, 1};
			glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, lightColor);
			glLightfv(GL_LIGHT0 + index, GL_SPECULAR, lightColor);
			glLightfv(GL_LIGHT0 + index, GL_POSITION, lightPos);
			index++;
		}
	}
}
void test()
{
    if(Camera::position.x == -3)
    {
        std::cout<< " is x=1?" <<std::endl;
        Texture* temp1 = Texture::loadBMP("ssand.bmp");
        glBindTexture( GL_TEXTURE_2D, temp1->getTextureID());
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glutSolidSphere(0.5, 20, 20);
        glBindTexture(GL_TEXTURE_2D, 0);
        
    }
    else std::cout<< "not!" <<std::endl;
}

void idle(void)
{
    Camera::rotation.y += 0.4;
	display();
}
