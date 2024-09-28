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

#ifndef B2_ISLAND_HPP
#define B2_ISLAND_HPP

#include <Common/Math.hpp>
#include <Dynamics/Body.hpp>
#include <Dynamics/TimeStep.hpp>

namespace box2d
{

class Contact;
class Joint;
class StackAllocator;
class ContactListener;
struct ContactVelocityConstraint;
struct Profile;

/// This is an internal class.
class Island
{
public:
	Island(Int32 bodyCapacity, Int32 contactCapacity, Int32 jointCapacity,
           StackAllocator* allocator, ContactListener* listener);
	~Island();

	void Clear()
	{
        m_body_count_ = 0;
        m_contact_count_ = 0;
        m_joint_count_ = 0;
	}

	void Solve(Profile* profile, const TimeStep& step, const Vector2& gravity, bool allowSleep);

	void SolveTOI(const TimeStep& subStep, Int32 toiIndexA, Int32 toiIndexB);

	void Add(Body* body)
	{
		assert(m_body_count_ < m_body_capacity_);
		body->m_island_index_ = m_body_count_;
        m_bodies_[m_body_count_] = body;
		++m_body_count_;
	}

	void Add(Contact* contact)
	{
		assert(m_contact_count_ < m_contact_capacity_);
        m_contacts_[m_contact_count_++] = contact;
	}

	void Add(Joint* joint)
	{
		assert(m_joint_count_ < m_joint_capacity_);
        m_joints_[m_joint_count_++] = joint;
	}

	void Report(const ContactVelocityConstraint* constraints);

	StackAllocator* m_allocator_;
	ContactListener* m_listener_;

	Body** m_bodies_;
	Contact** m_contacts_;
	Joint** m_joints_;

	Position* m_positions_;
	Velocity* m_velocities_;

	Int32 m_body_count_;
	Int32 m_joint_count_;
	Int32 m_contact_count_;

	Int32 m_body_capacity_;
	Int32 m_contact_capacity_;
	Int32 m_joint_capacity_;
};

} // namespace box2d

#endif // B2_ISLAND_HPP
