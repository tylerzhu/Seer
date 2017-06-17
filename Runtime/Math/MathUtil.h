/*
 * Interface file for core components and functions.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

/**
 * @mainpage Cyclone Reference
 *
 * Cyclone is a general purpose and robust system for real-time
 * simulation of rigid bodies. The library was designed to be used in
 * computer games, but may be applicable to other areas of simulation
 * or research.
 *
 * @section docs About This Document
 *
 * This documentation contains detailed reference to every aspect of
 * the Cyclone library.
 *
 * @subsection contents Contents
 *
 * Use the navigation system on the left side of the page to view the
 * documentation. The navigation tool uses JavaScript, and requires a
 * version 4 browser or above.
 *
 * All the publically accessible functions and classes of Cyclone
 * are provided in a set of header files. These, and their contents,
 * can be browsed from the File List section.
 *
 * Cyclone is contained in a single namespace, cyclone. Its
 * contents can be viewed in the Compound List section. The Class
 * Hierarchy section provides an alternative way to navigate these
 * classes. The Graphical Class Hierarchy provides an overview of
 * class inheritance.
 *
 * The Compound List section gives an alphabetic list of all symbols
 * in the library, including method names and functions.
 *
 * @subsection graphs Graphs
 *
 * Most of the documentation contains detailed graphical
 * representations of the file and class dependencies. These diagrams
 * are clickable, and provide the fastest mechanism for browsing the
 * documentation. Each diagram is followed by a link to a help file
 * giving a legend.
 *
 * @section use Using Cyclone
 *
 * To set up:
 *
 * @li Create a set of instances of RigidBody.
 *
 * @li Set their mass, inertia tensor, and damping.
 *
 * @li Set their initial location, orientation, velocity and rotation.
 *
 * @li Apply any permanent forces (such as gravity).
 *
 * Then each frame:
 *
 * @li Apply any transient forces (such as springs or thrusts).
 *
 * @li Call eulerIntegrate on each body in turn.
 *
 * @li Fill an array of Contact instances with all contacts on all
 * bodies.
 *
 * @li Call ContactResolver::resolveContacts to resolve the
 * contacts.
 *
 * @li Call calculateInternals to update the bodies' internal
 * properties (such as the transform matrix).
 *
 * @li Render the bodies.
 *
 * @section legal Legal
 *
 * This documentation is distributed under license. Use of this
 * documentation implies agreement with all terms and conditions of
 * the accompanying software and documentation license.
 */

/**
 * @file
 *
 * The core contains utility functions, helpers and a basic set of
 * mathematical types.
 */
#ifndef CYCLONE_CORE_H
#define CYCLONE_CORE_H

#include "Precision.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <math.h>

/**
 * The cyclone namespace includes all cyclone functions and
 * classes. It is defined as a namespace to allow function and class
 * names to be simple without causing conflicts.
 */
namespace Seer {

    /**
     * Holds the value for energy under which a body will be put to
     * sleep. This is a global value for the whole solution.  By
     * default it is 0.1, which is fine for simulation when gravity is
     * about 20 units per second squared, masses are about one, and
     * other forces are around that of gravity. It may need tweaking
     * if your simulation is drastically different to this.
     */
    extern real sleepEpsilon;

    /**
     * Sets the current sleep epsilon value: the kinetic energy under
     * which a body may be put to sleep. Bodies are put to sleep if
     * they appear to have a stable kinetic energy less than this
     * value. For simulations that often have low values (such as slow
     * moving, or light objects), this may need reducing.
     *
     * The value is global; all bodies will use it.
     *
     * @see sleepEpsilon
     *
     * @see getSleepEpsilon
     *
     * @param value The sleep epsilon value to use from this point
     * on.
     */
    void setSleepEpsilon(real value);

    /**
     * Gets the current value of the sleep epsilon parameter.
     *
     * @see sleepEpsilon
     *
     * @see setSleepEpsilon
     *
     * @return The current value of the parameter.
     */
    real getSleepEpsilon();

	inline float InvSqrt(float p) { return 1.0F / sqrt(p); }
	inline float Sqrt(float p) { return sqrt(p); }

	inline real FloatMin(real a, real b)
	{
		return std::min(a, b);
	}

	inline real FloatMax(real a, real b)
	{
		return std::max(a, b);
	}

	inline real FloatClamp(real v, real mn, real mx)
	{
		return FloatMin(FloatMax(v, mn), mx);
	}

	inline unsigned int FloorfToIntPos(real f)
	{
		return (unsigned int)f;
	}

	inline unsigned int RoundfToIntPos(real f)
	{
		return FloorfToIntPos(f + 0.5F);
	}

	// Convert float [0...1] to word [0...65535]
	inline int NormalizedToWord(real f)
	{
		f = FloatClamp(f, 0.0f, 1.0f);
		return RoundfToIntPos(f * 65535.0f);
	}

	inline double Abs(real v)
	{
		return v < 0.0 ? -v : v;
	}

	inline int Abs(int v)
	{
		return v < 0 ? -v : v;
	}


	// Convert float [0...1] to byte [0...255]
	inline int NormalizedToByte(real f)
	{
		f = FloatClamp(f, 0.0f, 1.0f);
		return RoundfToIntPos(f * 255.0f);
	}

#ifndef kPI
#define kPI 3.14159265358979323846264338327950288419716939937510F
#endif
#define kDeg2Rad (2.0F * kPI / 360.0F)
#define kRad2Deg (1.F / kDeg2Rad)

	inline float Deg2Rad(float deg)
	{
		// TODO : should be deg * kDeg2Rad, but can't be changed,
		// because it changes the order of operations and that affects a replay in some RegressionTests
		return deg / 360.0F * 2.0F * kPI;
	}

	inline float Rad2Deg(float rad)
	{
		// TODO : should be rad * kRad2Deg, but can't be changed,
		// because it changes the order of operations and that affects a replay in some RegressionTests
		return rad / 2.0F / kPI * 360.0F;
	}

	inline float Radians(float deg)
	{
		return deg * kDeg2Rad;
	}

	inline float Degrees(float rad)
	{
		return rad * kRad2Deg;
	}
}

#endif // CYCLONE_CORE_H