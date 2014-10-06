//
//  Texture.h
//  test07
//
//  Created by Tianyi on 2/25/14.
//  Copyright (c) 2014 tianyi. All rights reserved.
//

#ifndef __test07__Texture__
#define __test07__Texture__

#include <iostream>
#include <OpenGL/gl.h>

class Texture
{
    unsigned int textureID;
public:
    Texture(void* data, int w, int h, int format);
    unsigned int getTextureID();
    static Texture* loadBMP(const char* filename);
    
};

#endif /* defined(__test07__Texture__) */
