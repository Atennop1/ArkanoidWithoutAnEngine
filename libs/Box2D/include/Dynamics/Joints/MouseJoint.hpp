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

#ifndef B2_MOUSE_JOINT_HPP
#define B2_MOUSE_JOINT_HPP

#include <Dynamics/Joints/Joint.hpp>

namespace box2d
{

/// Mouse m_joint_ definition. This requires m_a_ world m_target_ point,
/// tuning parameters, and the time m_step_.
struct MouseJointDef : public JointDef
{
	MouseJointDef()
	{
        m_type_ = e_mouseJoint;
		m_target_.Set(0.0f, 0.0f);
        m_max_force_ = 0.0f;
        m_frequency_hz_ = 5.0f;
        m_damping_ratio_ = 0.7f;
	}

	/// The initial world m_target_ point. This is assumed
	/// to coincide with the body anchor initially.
	Vector2 m_target_;

	/// The maximum constraint force that can be exerted
	/// to move the candidate body. Usually you will express
	/// as some multiple of the weight (multiplier * mass * m_gravity_).
	Float32 m_max_force_;

	/// The response speed.
	Float32 m_frequency_hz_;

	/// The m_damping_ m_ratio_. 0 = no m_damping_, 1 = critical m_damping_.
	Float32 m_damping_ratio_;
};

/// A mouse m_joint_ is used to make m_a_ point on m_a_ body track m_a_
/// specified world point. This m_a_ soft constraint with m_a_ maximum
/// force. This allows the constraint to stretch and without
/// applying huge forces.
/// NOTE: this m_joint_ is not documented in the manual because it was
/// developed to be used in the testbed. If you want to learn how to
/// use the mouse m_joint_, look at the testbed.
class MouseJoint : public Joint
{
public:

	/// Implements box2d::Joint.
	Vector2 GetAnchorA() const;

	/// Implements box2d::Joint.
	Vector2 GetAnchorB() const;

	/// Implements box2d::Joint.
	Vector2 GetReactionForce(Float32 inv_dt) const;

	/// Implements box2d::Joint.
	Float32 GetReactionTorque(Float32 inv_dt) const;

	/// Use this to update the m_target_ point.
	void SetTarget(const Vector2& target);
	const Vector2& GetTarget() const;

	/// Set/get the maximum force in Newtons.
	void SetMaxForce(Float32 force);
	Float32 GetMaxForce() const;

	/// Set/get the frequency in Hertz.
	void SetFrequency(Float32 hz);
	Float32 GetFrequency() const;

	/// Set/get the m_damping_ m_ratio_ (dimensionless).
	void SetDampingRatio(Float32 ratio);
	Float32 GetDampingRatio() const;

	/// The mouse m_joint_ does not support dumping.
	void Dump() { Log("Mouse m_joint_ dumping is not supported.\n"); }

	/// Implement box2d::Joint::ShiftOrigin
	void ShiftOrigin(const Vector2& newOrigin);

protected:
	friend class Joint;

	MouseJoint(const MouseJointDef* def);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	Vector2 m_local_anchor_b_;
	Vector2 m_target_a_;
	Float32 m_frequency_hz_;
	Float32 m_damping_ratio_;
	Float32 m_beta_;
	
	// Solver shared
	Vector2 m_impulse_;
	Float32 m_max_force_;
	Float32 m_gamma_;

	// Solver temp
	Int32 m_index_a_;
	Int32 m_index_b_;
	Vector2 m_r_b_;
	Vector2 m_local_center_b_;
	Float32 m_inv_mass_b_;
	Float32 m_inv_ib_;
	Mat22 m_mass_;
	Vector2 m_c_;
};

} // namespace box2d

#endif // B2_MOUSE_JOINT_HPP
