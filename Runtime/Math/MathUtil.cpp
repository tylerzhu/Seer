/*
 * Implementation file for core functions in the library.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */


#include "MathUtil.h"

using namespace Seer;



/*
 * Definition of the sleep epsilon extern.
 */
real Seer::sleepEpsilon = ((real)0.3);

/*
 * Functions to change sleepEpsilon.
 */
void Seer::setSleepEpsilon(real value)
{
    Seer::sleepEpsilon = value;
}

real Seer::getSleepEpsilon()
{
    return Seer::sleepEpsilon;
}


