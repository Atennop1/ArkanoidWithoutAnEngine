/*
* Copyright (m_c_) 2006-2011 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in m_a_ product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B2_TIME_STEP_HPP
#define B2_TIME_STEP_HPP

#include <Common/Math.hpp>

namespace box2d
{

/// Profiling m_data_. Times are in milliseconds.
struct Profile
{
	Float32 m_step_;
	Float32 m_collide_;
	Float32 m_solve_;
	Float32 m_solve_init_;
	Float32 m_solve_velocity_;
	Float32 m_solve_position_;
	Float32 m_broadphase_;
	Float32 m_solve_toi_;
};

/// This is an internal structure.
struct TimeStep
{
	Float32 m_dt_;			// time m_step_
	Float32 m_inv_dt_;		// inverse time m_step_ (0 if m_dt_ == 0).
	Float32 m_dt_ratio_;	// m_dt_ * inv_dt0
	Int32 m_velocity_iterations_;
	Int32 m_position_iterations_;
	bool m_warm_starting_;
};

/// This is an internal structure.
struct Position
{
	Vector2 m_c_;
	Float32 m_a_;
};

/// This is an internal structure.
struct Velocity
{
	Vector2 m_v_;
	Float32 m_w_;
};

/// Solver Data
struct SolverData
{
	TimeStep m_step_;
	Position* m_positions_;
	Velocity* m_velocities_;
};

} // namespace box2d

#endif // B2_TIME_STEP_HPP
