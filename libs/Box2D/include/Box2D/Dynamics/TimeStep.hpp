/*
* Copyright (c) 2006-2011 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B2_TIME_STEP_HPP
#define B2_TIME_STEP_HPP

#include <Box2D/Common/Math.hpp>

namespace Box2D
{

/// Profiling data. Times are in milliseconds.
struct Profile
{
	float32 step;
	float32 collide;
	float32 solve;
	float32 solveInit;
	float32 solveVelocity;
	float32 solvePosition;
	float32 broadphase;
	float32 solveTOI;
};

/// This is an internal structure.
struct TimeStep
{
	float32 dt;			// time step
	float32 inv_dt;		// inverse time step (0 if dt == 0).
	float32 dtRatio;	// dt * inv_dt0
	int32 velocityIterations;
	int32 positionIterations;
	bool warmStarting;
};

/// This is an internal structure.
struct Position
{
	Vec2 c;
	float32 a;
};

/// This is an internal structure.
struct Velocity
{
	Vec2 v;
	float32 w;
};

/// Solver Data
struct SolverData
{
	TimeStep step;
	Position* positions;
	Velocity* velocities;
};

} // namespace Box2D

#endif // B2_TIME_STEP_HPP
