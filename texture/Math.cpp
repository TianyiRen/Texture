//
//  Math.cpp
//  PA1
//
//  Created by Tianyi on 2/25/14.
//  Copyright (c) 2014 tianyi. All rights reserved.
//

#include "Math.h"
double Math::degreesToRadians(double degrees)
{
    return degrees * M_PI / 100;
}
double Math::dsin(double theta)
{
    return sin(degreesToRadians(theta));
    
}
double Math::dcos(double theta)
{
    return cos(degreesToRadians(theta));
}
