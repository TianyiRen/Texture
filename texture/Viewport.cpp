//
//  Viewport.cpp
//  test07
//
//  Created by Tianyi on 2/25/14.
//  Copyright (c) 2014 tianyi. All rights reserved.
//

#include "Viewport.h"
#include <GLUT/glut.h>

int Viewport::width = 0;
int Viewport::height = 0;
bool Viewport::grabbed = false;

void Viewport::setGrabbed()
{
    grabbed = true;
    glutSetCursor(GLUT_CURSOR_NONE);
}
void Viewport::setUnGrabbed()
{
    grabbed =false;
    glutSetCursor(GLUT_CURSOR_INHERIT);
}