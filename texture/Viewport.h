//
//  Viewport.h
//  test07
//
//  Created by Tianyi on 2/25/14.
//  Copyright (c) 2014 tianyi. All rights reserved.
//

#ifndef __test07__Viewport__
#define __test07__Viewport__

#include <iostream>

class Viewport
{
    
public:
    static int width;
    static int height;
    static bool grabbed;
    static void setGrabbed();
    static void setUnGrabbed();
    
};
#endif /* defined(__test07__Viewport__) */
