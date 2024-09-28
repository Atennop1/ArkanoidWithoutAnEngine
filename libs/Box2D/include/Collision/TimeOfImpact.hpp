/*
* Copyright (m_c_) 2006-2009 Erin Catto http://www.box2d.org
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

#ifndef B2_TIME_OF_IMPACT_HPP
#define B2_TIME_OF_IMPACT_HPP

#include <Common/Math.hpp>
#include <Collision/Distance.hpp>

namespace box2d
{

/// Input parameters for box2d::TimeOfImpact
struct TOIInput
{
	DistanceProxy m_proxy_a_;
	DistanceProxy m_proxy_b_;
	Sweep m_sweep_a_;
	Sweep m_sweep_b_;
	Float32 m_t_max_;		// defines sweep interval [0, tMax]
};

// Output parameters for box2d::TimeOfImpact.
struct TOIOutput
{
	enum State
	{
		e_unknown,
		e_failed,
		e_overlapped,
		e_touching,
		e_separated
	};

	State m_state_;
	Float32 m_t_;
};

/// Compute the upper bound on time before two shapes penetrate. Time is represented as
/// m_a_ m_fraction_ between [0,tMax]. This uses m_a_ swept separating axis and may miss some intermediate,
/// non-tunneling collision. If you change the time interval, you should call this function
/// again.
/// Note: use box2d::Distance to compute the m_contact_ point and m_normal_ at the time of impact.
void TimeOfImpact(TOIOutput* output, const TOIInput* input);

} // namespace box2d

#endif // B2_TIME_OF_IMPACT_HPP
