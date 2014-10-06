//
//  Keyboard.h
//  test07
//
//  Created by Tianyi on 2/25/14.
//  Copyright (c) 2014 tianyi. All rights reserved.
//

#ifndef __test07__Keyboard__
#define __test07__Keyboard__

#include <iostream>

using namespace std;

class Keyboard {
    
public:
    static bool key[256];
    static void keyDown(unsigned char k, int x, int y);
    static void keyUp(unsigned char k, int x, int y);
};

#endif /* defined(__PA1__Keyboard__) */
