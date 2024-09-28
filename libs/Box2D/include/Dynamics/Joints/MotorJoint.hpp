/*
* Copyright (m_c_) 2006-2012 Erin Catto http://www.box2d.org
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

#ifndef B2_MOTOR_JOINT_HPP
#define B2_MOTOR_JOINT_HPP

#include <Dynamics/Joints/Joint.hpp>

namespace box2d
{

/// Motor m_joint_ definition.
struct MotorJointDef : public JointDef
{
	MotorJointDef()
	{
        m_type_ = e_motorJoint;
		m_linear_offset_.SetZero();
        m_angular_offset_ = 0.0f;
        m_max_force_ = 1.0f;
        m_max_torque_ = 1.0f;
        m_correction_factor_ = 0.3f;
	}

	/// Initialize the bodies and offsets using the current transforms.
	void Initialize(Body* bodyA, Body* bodyB);

	/// Position of m_body_b_ minus the m_position_ of m_body_a_, in m_body_a_'s frame, in meters.
	Vector2 m_linear_offset_;

	/// The m_body_b_ m_angle_ minus m_body_a_ m_angle_ in radians.
	Float32 m_angular_offset_;
	
	/// The maximum motor force in N.
	Float32 m_max_force_;

	/// The maximum motor torque in N-m.
	Float32 m_max_torque_;

	/// Position correction factor in the range [0,1].
	Float32 m_correction_factor_;
};

/// A motor m_joint_ is used to control the relative motion
/// between two bodies. A typical usage is to control the movement
/// of m_a_ dynamic body with respect to the ground.
class MotorJoint : public Joint
{
public:
	Vector2 GetAnchorA() const;
	Vector2 GetAnchorB() const;

	Vector2 GetReactionForce(Float32 inv_dt) const;
	Float32 GetReactionTorque(Float32 inv_dt) const;

	/// Set/get the m_target_ m_linear_ offset, in frame A, in meters.
	void SetLinearOffset(const Vector2& linearOffset);
	const Vector2& GetLinearOffset() const;

	/// Set/get the m_target_ angular offset, in radians.
	void SetAngularOffset(Float32 angularOffset);
	Float32 GetAngularOffset() const;

	/// Set the maximum m_friction_ force in N.
	void SetMaxForce(Float32 force);

	/// Get the maximum m_friction_ force in N.
	Float32 GetMaxForce() const;

	/// Set the maximum m_friction_ torque in N*m.
	void SetMaxTorque(Float32 torque);

	/// Get the maximum m_friction_ torque in N*m.
	Float32 GetMaxTorque() const;

	/// Set the m_position_ correction factor in the range [0,1].
	void SetCorrectionFactor(Float32 factor);

	/// Get the m_position_ correction factor in the range [0,1].
	Float32 GetCorrectionFactor() const;

	/// Dump to box2d::Log
	void Dump();

protected:

	friend class Joint;

	MotorJoint(const MotorJointDef* def);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	// Solver shared
	Vector2 m_linear_offset_;
	Float32 m_angular_offset_;
	Vector2 m_linear_impulse_;
	Float32 m_angular_impulse_;
	Float32 m_max_force_;
	Float32 m_max_torque_;
	Float32 m_correction_factor_;

	// Solver temp
	Int32 m_index_a_;
	Int32 m_index_b_;
	Vector2 m_r_a_;
	Vector2 m_r_b_;
	Vector2 m_local_center_a_;
	Vector2 m_local_center_b_;
	Vector2 m_linear_error_;
	Float32 m_angular_error_;
	Float32 m_inv_mass_a_;
	Float32 m_inv_mass_b_;
	Float32 m_inv_ia_;
	Float32 m_inv_ib_;
	Mat22 m_linear_mass_;
	Float32 m_angular_mass_;
};

} // namespace box2d

#endif // B2_MOTOR_JOINT_HPP
