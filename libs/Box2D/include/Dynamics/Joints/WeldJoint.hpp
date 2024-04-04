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

#ifndef B2_WELD_JOINT_HPP
#define B2_WELD_JOINT_HPP

#include "Joint.hpp"

namespace Box2D
{

/// Weld m_joint_ definition. You need to specify local anchor m_points_
/// where they are attached and the relative body m_angle_. The m_position_
/// of the anchor m_points_ is important for computing the reaction torque.
struct WeldJointDef : public JointDef
{
	WeldJointDef()
	{
        m_type_ = e_weldJoint;
		m_local_anchor_a_.Set(0.0f, 0.0f);
		m_local_anchor_b_.Set(0.0f, 0.0f);
        m_reference_angle_ = 0.0f;
        m_frequency_hz_ = 0.0f;
        m_damping_ratio_ = 0.0f;
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
	
	/// The mass-spring-damper frequency in Hertz. Rotation only.
	/// Disable softness with m_a_ value of 0.
	Float32 m_frequency_hz_;

	/// The m_damping_ m_ratio_. 0 = no m_damping_, 1 = critical m_damping_.
	Float32 m_damping_ratio_;
};

/// A weld m_joint_ essentially glues two bodies together. A weld m_joint_ may
/// distort somewhat because the island constraint solver is approximate.
class WeldJoint : public Joint
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

	/// Get the reference m_angle_.
	Float32 GetReferenceAngle() const { return m_reference_angle_; }

	/// Set/get frequency in Hz.
	void SetFrequency(Float32 hz) { m_frequency_hz_ = hz; }
	Float32 GetFrequency() const { return m_frequency_hz_; }

	/// Set/get m_damping_ m_ratio_.
	void SetDampingRatio(Float32 ratio) { m_damping_ratio_ = ratio; }
	Float32 GetDampingRatio() const { return m_damping_ratio_; }

	/// Dump to Box2D::Log
	void Dump();

protected:

	friend class Joint;

	WeldJoint(const WeldJointDef* def);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	Float32 m_frequency_hz_;
	Float32 m_damping_ratio_;
	Float32 m_bias_;

	// Solver shared
	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;
	Float32 m_reference_angle_;
	Float32 m_gamma_;
	Vector3 m_impulse_;

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
	Mat33 m_mass_;
};

} // namespace Box2D

#endif // B2_WELD_JOINT_HPP
