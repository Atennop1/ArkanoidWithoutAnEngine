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

#ifndef B2_PRISMATIC_JOINT_HPP
#define B2_PRISMATIC_JOINT_HPP

#include "Joint.hpp"

namespace Box2D
{

/// Prismatic m_joint_ definition. This requires defining m_a_ line of
/// motion using an axis and an anchor point. The definition uses local
/// anchor m_points_ and m_a_ local axis so that the initial configuration
/// can violate the constraint slightly. The m_joint_ translation is zero
/// when the local anchor m_points_ coincide in world space. Using local
/// anchors and m_a_ local axis helps when saving and loading m_a_ game.
struct PrismaticJointDef : public JointDef
{
	PrismaticJointDef()
	{
        m_type_ = e_prismaticJoint;
		m_local_anchor_a_.SetZero();
		m_local_anchor_b_.SetZero();
		m_local_axis_a_.Set(1.0f, 0.0f);
        m_reference_angle_ = 0.0f;
        m_enable_limit_ = false;
        m_lower_translation_ = 0.0f;
        m_upper_translation_ = 0.0f;
        m_enable_motor_ = false;
        m_max_motor_force_ = 0.0f;
        m_motor_speed_ = 0.0f;
	}

	/// Initialize the bodies, anchors, axis, and reference m_angle_ using the world
	/// anchor and unit world axis.
	void Initialize(Body* bodyA, Body* bodyB, const Vector2& anchor, const Vector2& axis);

	/// The local anchor point relative to m_body_a_'s origin.
	Vector2 m_local_anchor_a_;

	/// The local anchor point relative to m_body_b_'s origin.
	Vector2 m_local_anchor_b_;

	/// The local translation unit axis in m_body_a_.
	Vector2 m_local_axis_a_;

	/// The constrained m_angle_ between the bodies: bodyB_angle - bodyA_angle.
	Float32 m_reference_angle_;

	/// Enable/disable the m_joint_ limit.
	bool m_enable_limit_;

	/// The lower translation limit, usually in meters.
	Float32 m_lower_translation_;

	/// The upper translation limit, usually in meters.
	Float32 m_upper_translation_;

	/// Enable/disable the m_joint_ motor.
	bool m_enable_motor_;

	/// The maximum motor torque, usually in N-m.
	Float32 m_max_motor_force_;

	/// The desired motor speed in radians per second.
	Float32 m_motor_speed_;
};

/// A prismatic m_joint_. This m_joint_ provides one degree of freedom: translation
/// along an axis fixed in m_body_a_. Relative rotation is prevented. You can
/// use m_a_ m_joint_ limit to restrict the range of motion and m_a_ m_joint_ motor to
/// drive the motion or to model m_joint_ m_friction_.
class PrismaticJoint : public Joint
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

	/// The local m_joint_ axis relative to m_body_a_.
	const Vector2& GetLocalAxisA() const { return m_local_x_axis_a_; }

	/// Get the reference m_angle_.
	Float32 GetReferenceAngle() const { return m_reference_angle_; }

	/// Get the current m_joint_ translation, usually in meters.
	Float32 GetJointTranslation() const;

	/// Get the current m_joint_ translation speed, usually in meters per second.
	Float32 GetJointSpeed() const;

	/// Is the m_joint_ limit enabled?
	bool IsLimitEnabled() const;

	/// Enable/disable the m_joint_ limit.
	void EnableLimit(bool flag);

	/// Get the lower m_joint_ limit, usually in meters.
	Float32 GetLowerLimit() const;

	/// Get the upper m_joint_ limit, usually in meters.
	Float32 GetUpperLimit() const;

	/// Set the m_joint_ limits, usually in meters.
	void SetLimits(Float32 lower, Float32 upper);

	/// Is the m_joint_ motor enabled?
	bool IsMotorEnabled() const;

	/// Enable/disable the m_joint_ motor.
	void EnableMotor(bool flag);

	/// Set the motor speed, usually in meters per second.
	void SetMotorSpeed(Float32 speed);

	/// Get the motor speed, usually in meters per second.
	Float32 GetMotorSpeed() const;

	/// Set the maximum motor force, usually in N.
	void SetMaxMotorForce(Float32 force);
	Float32 GetMaxMotorForce() const { return m_max_motor_force_; }

	/// Get the current motor force given the inverse time m_step_, usually in N.
	Float32 GetMotorForce(Float32 inv_dt) const;

	/// Dump to Box2D::Log
	void Dump();

protected:
	friend class Joint;
	friend class GearJoint;
	PrismaticJoint(const PrismaticJointDef* def);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	// Solver shared
	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;
	Vector2 m_local_x_axis_a_;
	Vector2 m_local_y_axis_a_;
	Float32 m_reference_angle_;
	Vector3 m_impulse_;
	Float32 m_motor_impulse_;
	Float32 m_lower_translation_;
	Float32 m_upper_translation_;
	Float32 m_max_motor_force_;
	Float32 m_motor_speed_;
	bool m_enable_limit_;
	bool m_enable_motor_;
	LimitState m_limit_state_;

	// Solver temp
	Int32 m_index_a_;
	Int32 m_index_b_;
	Vector2 m_local_center_a_;
	Vector2 m_local_center_b_;
	Float32 m_inv_mass_a_;
	Float32 m_inv_mass_b_;
	Float32 m_inv_ia_;
	Float32 m_inv_ib_;
	Vector2 m_axis_, m_perp_;
	Float32 m_s_1_, m_s_2_;
	Float32 m_a_1_, m_a_2_;
	Mat33 m_k_;
	Float32 m_motor_mass_;
};

inline Float32 PrismaticJoint::GetMotorSpeed() const
{
	return m_motor_speed_;
}

} // namespace Box2D

#endif // B2_PRISMATIC_JOINT_HPP
