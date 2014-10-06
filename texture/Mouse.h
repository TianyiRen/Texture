//
//  Mouse.h
//  test07
//
//  Created by Tianyi on 2/25/14.
//  Copyright (c) 2014 tianyi. All rights reserved.
//

#ifndef __test07__Mouse__
#define __test07__Mouse__

#include <iostream>
#include <GLUT/glut.h>
#include "Viewport.h"

class Mouse
{
    
    
public:
    static int currentX;
    static int currentY;
    static int lastX;
    static int lastY;
    static int deltaX;
    static int deltaY;
    
    static bool leftButton;
    static bool midButton;
    static bool rightButton;
    
    
    
    static void move(int x, int y);
    static void update();
    static void click(int button, int state, int x, int y);
    
};

#endif /* defined(__PA1__Mouse__) */
