/*
* Copyright (m_c_) 2006-2007 Erin Catto http://www.box2d.org
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

#ifndef B2_FRICTION_JOINT_HPP
#define B2_FRICTION_JOINT_HPP

#include "Joint.hpp"

namespace Box2D
{

/// Friction m_joint_ definition.
struct FrictionJointDef : public JointDef
{
	FrictionJointDef()
	{
        m_type_ = e_frictionJoint;
		m_local_anchor_a_.SetZero();
		m_local_anchor_b_.SetZero();
        m_max_force_ = 0.0f;
        m_max_torque_ = 0.0f;
	}

	/// Initialize the bodies, anchors, axis, and reference m_angle_ using the world
	/// anchor and world axis.
	void Initialize(Body* bodyA, Body* bodyB, const Vector2& anchor);

	/// The local anchor point relative to m_body_a_'s origin.
	Vector2 m_local_anchor_a_;

	/// The local anchor point relative to m_body_b_'s origin.
	Vector2 m_local_anchor_b_;

	/// The maximum m_friction_ force in N.
	Float32 m_max_force_;

	/// The maximum m_friction_ torque in N-m.
	Float32 m_max_torque_;
};

/// Friction m_joint_. This is used for top-down m_friction_.
/// It provides 2D translational m_friction_ and angular m_friction_.
class FrictionJoint : public Joint
{
public:
	Vector2 GetAnchorA() const;
	Vector2 GetAnchorB() const;

	Vector2 GetReactionForce(Float32 inv_dt) const;
	Float32 GetReactionTorque(Float32 inv_dt) const;

	/// The local anchor point relative to m_body_a_'s origin.
	const Vector2& GetLocalAnchorA() const { return m_local_anchor_a_; }

	/// The local anchor point relative to m_body_b_'s origin.
	const Vector2& GetLocalAnchorB() const  { return m_local_anchor_b_; }

	/// Set the maximum m_friction_ force in N.
	void SetMaxForce(Float32 force);

	/// Get the maximum m_friction_ force in N.
	Float32 GetMaxForce() const;

	/// Set the maximum m_friction_ torque in N*m.
	void SetMaxTorque(Float32 torque);

	/// Get the maximum m_friction_ torque in N*m.
	Float32 GetMaxTorque() const;

	/// Dump m_joint_ to dmLog
	void Dump();

protected:

	friend class Joint;

	FrictionJoint(const FrictionJointDef* def);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;

	// Solver shared
	Vector2 m_linear_impulse_;
	Float32 m_angular_impulse_;
	Float32 m_max_force_;
	Float32 m_max_torque_;

	// Solver temp
	Int32 m_index_a_;
	Int32 m_index_b_;
	Vector2 m_r_a_;
	Vector2 m_r_b_;
	Vector2 m_local_center_a_;
	Vector2 m_local_center_b_;
	Float32 m_inv_mass_a_;
	Float32 m_inv_mass_b_;
	Float32 m_inv_ia_;
	Float32 m_inv_ib_;
	Mat22 m_linear_mass_;
	Float32 m_angular_mass_;
};

} // namespace Box2D

#endif // B2_FRICTION_JOINT_HPP
