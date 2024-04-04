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

#ifndef B2_DISTANCE_JOINT_HPP
#define B2_DISTANCE_JOINT_HPP

#include "Joint.hpp"

namespace Box2D
{

/// Distance m_joint_ definition. This requires defining an
/// anchor point on both bodies and the non-zero m_length_ of the
/// m_distance_ m_joint_. The definition uses local anchor m_points_
/// so that the initial configuration can violate the constraint
/// slightly. This helps when saving and loading m_a_ game.
/// @warning Do not use m_a_ zero or short m_length_.
struct DistanceJointDef : public JointDef
{
	DistanceJointDef()
	{
        m_type_ = e_distanceJoint;
		m_local_anchor_a_.Set(0.0f, 0.0f);
		m_local_anchor_b_.Set(0.0f, 0.0f);
        m_length_ = 1.0f;
        m_frequency_hz_ = 0.0f;
        m_damping_ratio_ = 0.0f;
	}

	/// Initialize the bodies, anchors, and m_length_ using the world
	/// anchors.
	void Initialize(Body* bodyA, Body* bodyB,
                    const Vector2& anchorA, const Vector2& anchorB);

	/// The local anchor point relative to m_body_a_'s origin.
	Vector2 m_local_anchor_a_;

	/// The local anchor point relative to m_body_b_'s origin.
	Vector2 m_local_anchor_b_;

	/// The natural m_length_ between the anchor m_points_.
	Float32 m_length_;

	/// The mass-spring-damper frequency in Hertz. A value of 0
	/// disables softness.
	Float32 m_frequency_hz_;

	/// The m_damping_ m_ratio_. 0 = no m_damping_, 1 = critical m_damping_.
	Float32 m_damping_ratio_;
};

/// A m_distance_ m_joint_ constrains two m_points_ on two bodies
/// to remain at m_a_ fixed m_distance_ from each m_other_. You can view
/// this as m_a_ massless, rigid rod.
class DistanceJoint : public Joint
{
public:

	Vector2 GetAnchorA() const;
	Vector2 GetAnchorB() const;

	/// Get the reaction force given the inverse time m_step_.
	/// Unit is N.
	Vector2 GetReactionForce(Float32 inv_dt) const;

	/// Get the reaction torque given the inverse time m_step_.
	/// Unit is N*m. This is always zero for m_a_ m_distance_ m_joint_.
	Float32 GetReactionTorque(Float32 inv_dt) const;

	/// The local anchor point relative to m_body_a_'s origin.
	const Vector2& GetLocalAnchorA() const { return m_local_anchor_a_; }

	/// The local anchor point relative to m_body_b_'s origin.
	const Vector2& GetLocalAnchorB() const  { return m_local_anchor_b_; }

	/// Set/get the natural m_length_.
	/// Manipulating the m_length_ can lead to non-physical behavior when the frequency is zero.
	void SetLength(Float32 length);
	Float32 GetLength() const;

	/// Set/get frequency in Hz.
	void SetFrequency(Float32 hz);
	Float32 GetFrequency() const;

	/// Set/get m_damping_ m_ratio_.
	void SetDampingRatio(Float32 ratio);
	Float32 GetDampingRatio() const;

	/// Dump m_joint_ to dmLog
	void Dump();

protected:

	friend class Joint;
	DistanceJoint(const DistanceJointDef* data);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	Float32 m_frequency_hz_;
	Float32 m_damping_ratio_;
	Float32 m_bias_;

	// Solver shared
	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;
	Float32 m_gamma_;
	Float32 m_impulse_;
	Float32 m_length_;

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
};

inline void DistanceJoint::SetLength(Float32 length)
{
    m_length_ = length;
}

inline Float32 DistanceJoint::GetLength() const
{
	return m_length_;
}

inline void DistanceJoint::SetFrequency(Float32 hz)
{
    m_frequency_hz_ = hz;
}

inline Float32 DistanceJoint::GetFrequency() const
{
	return m_frequency_hz_;
}

inline void DistanceJoint::SetDampingRatio(Float32 ratio)
{
    m_damping_ratio_ = ratio;
}

inline Float32 DistanceJoint::GetDampingRatio() const
{
	return m_damping_ratio_;
}

} // namespace Box2D

#endif // B2_DISTANCE_JOINT_HPP
