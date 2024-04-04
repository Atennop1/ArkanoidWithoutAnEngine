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

#ifndef B2_WHEEL_JOINT_HPP
#define B2_WHEEL_JOINT_HPP

#include "Joint.hpp"

namespace Box2D
{

/// Wheel m_joint_ definition. This requires defining m_a_ line of
/// motion using an axis and an anchor point. The definition uses local
/// anchor m_points_ and m_a_ local axis so that the initial configuration
/// can violate the constraint slightly. The m_joint_ translation is zero
/// when the local anchor m_points_ coincide in world space. Using local
/// anchors and m_a_ local axis helps when saving and loading m_a_ game.
struct WheelJointDef : public JointDef
{
	WheelJointDef()
	{
        m_type_ = e_wheelJoint;
		m_local_anchor_a_.SetZero();
		m_local_anchor_b_.SetZero();
		m_local_axis_a_.Set(1.0f, 0.0f);
        m_enable_motor_ = false;
        m_max_motor_torque_ = 0.0f;
        m_motor_speed_ = 0.0f;
        m_frequency_hz_ = 2.0f;
        m_damping_ratio_ = 0.7f;
	}

	/// Initialize the bodies, anchors, axis, and reference m_angle_ using the world
	/// anchor and world axis.
	void Initialize(Body* bodyA, Body* bodyB, const Vector2& anchor, const Vector2& axis);

	/// The local anchor point relative to m_body_a_'s origin.
	Vector2 m_local_anchor_a_;

	/// The local anchor point relative to m_body_b_'s origin.
	Vector2 m_local_anchor_b_;

	/// The local translation axis in m_body_a_.
	Vector2 m_local_axis_a_;

	/// Enable/disable the m_joint_ motor.
	bool m_enable_motor_;

	/// The maximum motor torque, usually in N-m.
	Float32 m_max_motor_torque_;

	/// The desired motor speed in radians per second.
	Float32 m_motor_speed_;

	/// Suspension frequency, zero indicates no suspension
	Float32 m_frequency_hz_;

	/// Suspension m_damping_ m_ratio_, one indicates critical m_damping_
	Float32 m_damping_ratio_;
};

/// A wheel m_joint_. This m_joint_ provides two degrees of freedom: translation
/// along an axis fixed in m_body_a_ and rotation in the plane. In m_other_ words, it is m_a_ point to
/// line constraint with m_a_ rotational motor and m_a_ m_linear_ spring/damper.
/// This m_joint_ is designed for vehicle suspensions.
class WheelJoint : public Joint
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

	/// Get the current m_joint_ translation, usually in meters.
	Float32 GetJointTranslation() const;

	/// Get the current m_joint_ translation speed, usually in meters per second.
	Float32 GetJointSpeed() const;

	/// Is the m_joint_ motor enabled?
	bool IsMotorEnabled() const;

	/// Enable/disable the m_joint_ motor.
	void EnableMotor(bool flag);

	/// Set the motor speed, usually in radians per second.
	void SetMotorSpeed(Float32 speed);

	/// Get the motor speed, usually in radians per second.
	Float32 GetMotorSpeed() const;

	/// Set/Get the maximum motor force, usually in N-m.
	void SetMaxMotorTorque(Float32 torque);
	Float32 GetMaxMotorTorque() const;

	/// Get the current motor torque given the inverse time m_step_, usually in N-m.
	Float32 GetMotorTorque(Float32 inv_dt) const;

	/// Set/Get the spring frequency in hertz. Setting the frequency to zero disables the spring.
	void SetSpringFrequencyHz(Float32 hz);
	Float32 GetSpringFrequencyHz() const;

	/// Set/Get the spring m_damping_ m_ratio_
	void SetSpringDampingRatio(Float32 ratio);
	Float32 GetSpringDampingRatio() const;

	/// Dump to Box2D::Log
	void Dump();

protected:

	friend class Joint;
	WheelJoint(const WheelJointDef* def);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	Float32 m_frequency_hz_;
	Float32 m_damping_ratio_;

	// Solver shared
	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;
	Vector2 m_local_x_axis_a_;
	Vector2 m_local_y_axis_a_;

	Float32 m_impulse_;
	Float32 m_motor_impulse_;
	Float32 m_spring_impulse_;

	Float32 m_max_motor_torque_;
	Float32 m_motor_speed_;
	bool m_enable_motor_;

	// Solver temp
	Int32 m_index_a_;
	Int32 m_index_b_;
	Vector2 m_local_center_a_;
	Vector2 m_local_center_b_;
	Float32 m_inv_mass_a_;
	Float32 m_inv_mass_b_;
	Float32 m_inv_ia_;
	Float32 m_inv_ib_;

	Vector2 m_ax_, m_ay_;
	Float32 m_s_ax_, m_s_bx_;
	Float32 m_s_ay_, m_s_by_;

	Float32 m_mass_;
	Float32 m_motor_mass_;
	Float32 m_spring_mass_;

	Float32 m_bias_;
	Float32 m_gamma_;
};

inline Float32 WheelJoint::GetMotorSpeed() const
{
	return m_motor_speed_;
}

inline Float32 WheelJoint::GetMaxMotorTorque() const
{
	return m_max_motor_torque_;
}

inline void WheelJoint::SetSpringFrequencyHz(Float32 hz)
{
    m_frequency_hz_ = hz;
}

inline Float32 WheelJoint::GetSpringFrequencyHz() const
{
	return m_frequency_hz_;
}

inline void WheelJoint::SetSpringDampingRatio(Float32 ratio)
{
    m_damping_ratio_ = ratio;
}

inline Float32 WheelJoint::GetSpringDampingRatio() const
{
	return m_damping_ratio_;
}

} // namespace Box2D

#endif // B2_WHEEL_JOINT_HPP
