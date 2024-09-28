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

#ifndef B2_REVOLUTE_JOINT_HPP
#define B2_REVOLUTE_JOINT_HPP

#include <Dynamics/Joints/Joint.hpp>

namespace box2d
{

/// Revolute m_joint_ definition. This requires defining an
/// anchor point where the bodies are joined. The definition
/// uses local anchor m_points_ so that the initial configuration
/// can violate the constraint slightly. You also need to
/// specify the initial relative m_angle_ for m_joint_ limits. This
/// helps when saving and loading m_a_ game.
/// The local anchor m_points_ are measured from the body's origin
/// rather than the center of mass because:
/// 1. you might not know where the center of mass will be.
/// 2. if you add/remove shapes from m_a_ body and recompute the mass,
///    the joints will be broken.
struct RevoluteJointDef : public JointDef
{
	RevoluteJointDef()
	{
        m_type_ = e_revoluteJoint;
		m_local_anchor_a_.Set(0.0f, 0.0f);
		m_local_anchor_b_.Set(0.0f, 0.0f);
        m_reference_angle_ = 0.0f;
        m_lower_angle_ = 0.0f;
        m_upper_angle_ = 0.0f;
        m_max_motor_torque_ = 0.0f;
        m_motor_speed_ = 0.0f;
        m_enable_limit_ = false;
        m_enable_motor_ = false;
	}

	/// Initialize the bodies, anchors, and reference m_angle_ using m_a_ world
	/// anchor point.
	void Initialize(Body* bodyA, Body* bodyB, const Vector2& anchor);

	/// The local anchor point relative to m_body_a_'s origin.
	Vector2 m_local_anchor_a_;

	/// The local anchor point relative to m_body_b_'s origin.
	Vector2 m_local_anchor_b_;

	/// The m_body_b_ m_angle_ minus m_body_a_ m_angle_ in the reference state (radians).
	Float32 m_reference_angle_;

	/// A flag to enable m_joint_ limits.
	bool m_enable_limit_;

	/// The lower m_angle_ for the m_joint_ limit (radians).
	Float32 m_lower_angle_;

	/// The upper m_angle_ for the m_joint_ limit (radians).
	Float32 m_upper_angle_;

	/// A flag to enable the m_joint_ motor.
	bool m_enable_motor_;

	/// The desired motor speed. Usually in radians per second.
	Float32 m_motor_speed_;

	/// The maximum motor torque used to achieve the desired motor speed.
	/// Usually in N-m.
	Float32 m_max_motor_torque_;
};

/// A revolute m_joint_ constrains two bodies to share m_a_ common point while they
/// are free to rotate about the point. The relative rotation about the shared
/// point is the m_joint_ m_angle_. You can limit the relative rotation with
/// m_a_ m_joint_ limit that specifies m_a_ lower and upper m_angle_. You can use m_a_ motor
/// to drive the relative rotation about the shared point. A maximum motor torque
/// is provided so that infinite forces are not generated.
class RevoluteJoint : public Joint
{
public:
	Vector2 GetAnchorA() const;
	Vector2 GetAnchorB() const;

	/// The local anchor point relative to m_body_a_'s origin.
	const Vector2& GetLocalAnchorA() const { return m_local_anchor_a_; }

	/// The local anchor point relative to m_body_b_'s origin.
	const Vector2& GetLocalAnchorB() const  { return m_local_anchor_b_; }

	/// Get the reference m_angle_.
	Float32 GetReferenceAngle() const { return m_reference_angle_; }

	/// Get the current m_joint_ m_angle_ in radians.
	Float32 GetJointAngle() const;

	/// Get the current m_joint_ m_angle_ speed in radians per second.
	Float32 GetJointSpeed() const;

	/// Is the m_joint_ limit enabled?
	bool IsLimitEnabled() const;

	/// Enable/disable the m_joint_ limit.
	void EnableLimit(bool flag);

	/// Get the lower m_joint_ limit in radians.
	Float32 GetLowerLimit() const;

	/// Get the upper m_joint_ limit in radians.
	Float32 GetUpperLimit() const;

	/// Set the m_joint_ limits in radians.
	void SetLimits(Float32 lower, Float32 upper);

	/// Is the m_joint_ motor enabled?
	bool IsMotorEnabled() const;

	/// Enable/disable the m_joint_ motor.
	void EnableMotor(bool flag);

	/// Set the motor speed in radians per second.
	void SetMotorSpeed(Float32 speed);

	/// Get the motor speed in radians per second.
	Float32 GetMotorSpeed() const;

	/// Set the maximum motor torque, usually in N-m.
	void SetMaxMotorTorque(Float32 torque);
	Float32 GetMaxMotorTorque() const { return m_max_motor_torque_; }

	/// Get the reaction force given the inverse time m_step_.
	/// Unit is N.
	Vector2 GetReactionForce(Float32 inv_dt) const;

	/// Get the reaction torque due to the m_joint_ limit given the inverse time m_step_.
	/// Unit is N*m.
	Float32 GetReactionTorque(Float32 inv_dt) const;

	/// Get the current motor torque given the inverse time m_step_.
	/// Unit is N*m.
	Float32 GetMotorTorque(Float32 inv_dt) const;

	/// Dump to box2d::Log.
	void Dump();

protected:
	
	friend class Joint;
	friend class GearJoint;

	RevoluteJoint(const RevoluteJointDef* def);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	// Solver shared
	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;
	Vector3 m_impulse_;
	Float32 m_motor_impulse_;

	bool m_enable_motor_;
	Float32 m_max_motor_torque_;
	Float32 m_motor_speed_;

	bool m_enable_limit_;
	Float32 m_reference_angle_;
	Float32 m_lower_angle_;
	Float32 m_upper_angle_;

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
	Mat33 m_mass_;			// effective mass for point-to-point constraint.
	Float32 m_motor_mass_;	// effective mass for motor/limit angular constraint.
	LimitState m_limit_state_;
};

inline Float32 RevoluteJoint::GetMotorSpeed() const
{
	return m_motor_speed_;
}

} // namespace box2d

#endif // B2_REVOLUTE_JOINT_HPP
