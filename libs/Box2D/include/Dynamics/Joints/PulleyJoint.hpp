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

#ifndef B2_PULLEY_JOINT_HPP
#define B2_PULLEY_JOINT_HPP

#include <Dynamics/Joints/Joint.hpp>

namespace box2d
{

const Float32 minPulleyLength = 2.0f;

/// Pulley m_joint_ definition. This requires two ground anchors,
/// two dynamic body anchor m_points_, and m_a_ pulley m_ratio_.
struct PulleyJointDef : public JointDef
{
	PulleyJointDef()
	{
        m_type_ = e_pulleyJoint;
		m_ground_anchor_a_.Set(-1.0f, 1.0f);
		m_ground_anchor_b_.Set(1.0f, 1.0f);
		m_local_anchor_a_.Set(-1.0f, 0.0f);
		m_local_anchor_b_.Set(1.0f, 0.0f);
        m_length_a_ = 0.0f;
        m_length_b_ = 0.0f;
        m_ratio_ = 1.0f;
        m_collide_connected_ = true;
	}

	/// Initialize the bodies, anchors, lengths, max lengths, and m_ratio_ using the world anchors.
	void Initialize(Body* bodyA, Body* bodyB,
                    const Vector2& groundAnchorA, const Vector2& groundAnchorB,
                    const Vector2& anchorA, const Vector2& anchorB,
                    Float32 ratio);

	/// The first ground anchor in world coordinates. This point never moves.
	Vector2 m_ground_anchor_a_;

	/// The second ground anchor in world coordinates. This point never moves.
	Vector2 m_ground_anchor_b_;

	/// The local anchor point relative to m_body_a_'s origin.
	Vector2 m_local_anchor_a_;

	/// The local anchor point relative to m_body_b_'s origin.
	Vector2 m_local_anchor_b_;

	/// The m_a_ reference m_length_ for the segment attached to m_body_a_.
	Float32 m_length_a_;

	/// The m_a_ reference m_length_ for the segment attached to m_body_b_.
	Float32 m_length_b_;

	/// The pulley m_ratio_, used to simulate m_a_ block-and-tackle.
	Float32 m_ratio_;
};

/// The pulley m_joint_ is connected to two bodies and two fixed ground m_points_.
/// The pulley supports m_a_ m_ratio_ such that:
/// length1 + m_ratio_ * length2 <= constant
/// Yes, the force transmitted is scaled by the m_ratio_.
/// Warning: the pulley m_joint_ can get m_a_ bit squirrelly by itself. They often
/// work better when combined with prismatic joints. You should also cover the
/// the anchor m_points_ with static shapes to prevent one side from going to
/// zero m_length_.
class PulleyJoint : public Joint
{
public:
	Vector2 GetAnchorA() const;
	Vector2 GetAnchorB() const;

	Vector2 GetReactionForce(Float32 inv_dt) const;
	Float32 GetReactionTorque(Float32 inv_dt) const;

	/// Get the first ground anchor.
	Vector2 GetGroundAnchorA() const;

	/// Get the second ground anchor.
	Vector2 GetGroundAnchorB() const;

	/// Get the current m_length_ of the segment attached to m_body_a_.
	Float32 GetLengthA() const;

	/// Get the current m_length_ of the segment attached to m_body_b_.
	Float32 GetLengthB() const;

	/// Get the pulley m_ratio_.
	Float32 GetRatio() const;

	/// Get the current m_length_ of the segment attached to m_body_a_.
	Float32 GetCurrentLengthA() const;

	/// Get the current m_length_ of the segment attached to m_body_b_.
	Float32 GetCurrentLengthB() const;

	/// Dump m_joint_ to dmLog
	void Dump();

	/// Implement box2d::Joint::ShiftOrigin
	void ShiftOrigin(const Vector2& newOrigin);

protected:

	friend class Joint;
	PulleyJoint(const PulleyJointDef* data);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	Vector2 m_ground_anchor_a_;
	Vector2 m_ground_anchor_b_;
	Float32 m_length_a_;
	Float32 m_length_b_;
	
	// Solver shared
	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;
	Float32 m_constant_;
	Float32 m_ratio_;
	Float32 m_impulse_;

	// Solver temp
	Int32 m_index_a_;
	Int32 m_index_b_;
	Vector2 m_u_a_;
	Vector2 m_u_b_;
	Vector2 m_r_a_;
	Vector2 m_r_b_;
	Vector2 m_local_center_a_;
	Vector2 m_local_center_b_;
	Float32 m_inv_mass_a_;
	Float32 m_inv_mass_b_;
	Float32 m_inv_ia_;
	Float32 m_inv_ib_;
	Float32 m_mass_;
};

} // namespace box2d

#endif // B2_PULLEY_JOINT_HPP
