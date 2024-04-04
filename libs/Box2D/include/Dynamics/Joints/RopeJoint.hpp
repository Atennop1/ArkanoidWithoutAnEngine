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

#ifndef B2_ROPE_JOINT_HPP
#define B2_ROPE_JOINT_HPP

#include "Joint.hpp"

namespace Box2D
{

/// Rope m_joint_ definition. This requires two body anchor m_points_ and
/// m_a_ maximum lengths.
/// Note: by default the connected objects will not m_collide_.
/// see m_collide_connected_ in Box2D::JointDef.
struct RopeJointDef : public JointDef
{
	RopeJointDef()
	{
        m_type_ = e_ropeJoint;
		m_local_anchor_a_.Set(-1.0f, 0.0f);
		m_local_anchor_b_.Set(1.0f, 0.0f);
        m_max_length_ = 0.0f;
	}

	/// The local anchor point relative to m_body_a_'s origin.
	Vector2 m_local_anchor_a_;

	/// The local anchor point relative to m_body_b_'s origin.
	Vector2 m_local_anchor_b_;

	/// The maximum m_length_ of the rope.
	/// Warning: this must be larger than linear_slop or
	/// the m_joint_ will have no effect.
	Float32 m_max_length_;
};

/// A rope m_joint_ enforces m_a_ maximum m_distance_ between two m_points_
/// on two bodies. It has no m_other_ effect.
/// Warning: if you attempt to change the maximum m_length_ during
/// the simulation you will get some non-physical behavior.
/// A model that would allow you to dynamically modify the m_length_
/// would have some sponginess, so I chose not to implement it
/// that way. See Box2D::DistanceJoint if you want to dynamically
/// control m_length_.
class RopeJoint : public Joint
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

	/// Set/Get the maximum m_length_ of the rope.
	void SetMaxLength(Float32 length) { m_max_length_ = length; }
	Float32 GetMaxLength() const;

	LimitState GetLimitState() const;

	/// Dump m_joint_ to dmLog
	void Dump();

protected:

	friend class Joint;
	RopeJoint(const RopeJointDef* data);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	// Solver shared
	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;
	Float32 m_max_length_;
	Float32 m_length_;
	Float32 m_impulse_;

	// Solver temp
	Int32 m_index_a_;
	Int32 m_index_b_;
	Vector2 m_u_;
	Vector2 m_r_a_;
	Vector2 m_r_b_;
	Vector2 m_local_center_a_;
	Vector2 m_local_center_b_;
	Float32 m_inv_mass_a_;
	Float32 m_inv_mass_b_;
	Float32 m_inv_ia_;
	Float32 m_inv_ib_;
	Float32 m_mass_;
	LimitState m_state_;
};

} // namespace Box2D

#endif // B2_ROPE_JOINT_HPP
