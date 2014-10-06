//
//  Keyboard.cpp
//  test07
//
//  Created by Tianyi on 2/25/14.
//  Copyright (c) 2014 tianyi. All rights reserved.
//

#include "Keyboard.h"

using namespace std;
bool Keyboard::key[256];

void Keyboard::keyDown(unsigned char k, int x, int y)
{
    key[k] = true;
}
void Keyboard::keyUp(unsigned char k, int x, int y)
{
    key[k] = false;
}