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

#ifndef B2_CONTACT_SOLVER_HPP
#define B2_CONTACT_SOLVER_HPP

#include "Common/Math.hpp"
#include "Collision/Collision.hpp"
#include "Dynamics/TimeStep.hpp"

namespace Box2D
{

class Contact;
class Body;
class StackAllocator;
struct ContactPositionConstraint;

struct VelocityConstraintPoint
{
	Vector2 m_r_a_;
	Vector2 m_r_b_;
	Float32 m_normal_impulse_;
	Float32 m_tangent_impulse_;
	Float32 m_normal_mass_;
	Float32 m_tangent_mass_;
	Float32 m_velocity_bias_;
};

struct ContactVelocityConstraint
{
	VelocityConstraintPoint m_points_[max_manifold_points];
	Vector2 m_normal_;
	Mat22 m_normal_mass_;
	Mat22 m_k_;
	Int32 m_index_a_;
	Int32 m_index_b_;
	Float32 m_inv_mass_a_, m_inv_mass_b_;
	Float32 m_inv_ia_, m_inv_ib_;
	Float32 m_friction_;
	Float32 m_restitution_;
	Float32 m_tangent_speed_;
	Int32 m_point_count_;
	Int32 m_contact_index_;
};

struct ContactSolverDef
{
    TimeStep m_step_;
	Contact** m_contacts_;
	Int32 m_count_;
	Position* m_positions_;
	Velocity* m_velocities_;
	StackAllocator* m_allocator_;
};

class ContactSolver
{
public:
	ContactSolver(ContactSolverDef* def);
	~ContactSolver();

	void InitializeVelocityConstraints();

	void WarmStart();
	void SolveVelocityConstraints();
	void StoreImpulses();

	bool SolvePositionConstraints();
	bool SolveTOIPositionConstraints(Int32 toiIndexA, Int32 toiIndexB);

	TimeStep m_step_;
	Position* m_positions_;
	Velocity* m_velocities_;
	StackAllocator* m_allocator_;
	ContactPositionConstraint* m_position_constraints_;
	ContactVelocityConstraint* m_velocity_constraints_;
	Contact** m_contacts_;
	int m_count_;
};

} // namespace Box2D

#endif // B2_CONTACT_SOLVER_HPP
