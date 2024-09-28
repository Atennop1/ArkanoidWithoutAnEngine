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

#ifndef B2_GEAR_JOINT_HPP
#define B2_GEAR_JOINT_HPP

#include <Dynamics/Joints/Joint.hpp>

namespace box2d
{

/// Gear m_joint_ definition. This definition requires two existing
/// revolute or prismatic joints (any combination will work).
struct GearJointDef : public JointDef
{
	GearJointDef()
	{
        m_type_ = e_gearJoint;
        m_joint_1_ = NULL;
        m_joint_2_ = NULL;
        m_ratio_ = 1.0f;
	}

	/// The first revolute/prismatic m_joint_ attached to the gear m_joint_.
	Joint* m_joint_1_;

	/// The second revolute/prismatic m_joint_ attached to the gear m_joint_.
	Joint* m_joint_2_;

	/// The gear m_ratio_.
	/// @see box2d::GearJoint for explanation.
	Float32 m_ratio_;
};

/// A gear m_joint_ is used to connect two joints together. Either m_joint_
/// can be m_a_ revolute or prismatic m_joint_. You specify m_a_ gear m_ratio_
/// to bind the motions together:
/// coordinate1 + m_ratio_ * coordinate2 = constant
/// The m_ratio_ can be negative or positive. If one m_joint_ is m_a_ revolute m_joint_
/// and the m_other_ m_joint_ is m_a_ prismatic m_joint_, then the m_ratio_ will have units
/// of m_length_ or units of 1/m_length_.
/// @warning You have to manually destroy the gear m_joint_ if m_joint_1_ or m_joint_2_
/// is destroyed.
class GearJoint : public Joint
{
public:
	Vector2 GetAnchorA() const;
	Vector2 GetAnchorB() const;

	Vector2 GetReactionForce(Float32 inv_dt) const;
	Float32 GetReactionTorque(Float32 inv_dt) const;

	/// Get the first m_joint_.
	Joint* GetJoint1() { return m_joint_1_; }

	/// Get the second m_joint_.
	Joint* GetJoint2() { return m_joint_2_; }

	/// Set/Get the gear m_ratio_.
	void SetRatio(Float32 ratio);
	Float32 GetRatio() const;

	/// Dump m_joint_ to dmLog
	void Dump();

protected:

	friend class Joint;
	GearJoint(const GearJointDef* data);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	Joint* m_joint_1_;
	Joint* m_joint_2_;

	JointType m_type_a_;
	JointType m_type_b_;

	// Body A is connected to body C
	// Body B is connected to body D
	Body* m_body_c_;
	Body* m_body_d_;

	// Solver shared
	Vector2 m_local_anchor_a_;
	Vector2 m_local_anchor_b_;
	Vector2 m_local_anchor_c_;
	Vector2 m_local_anchor_d_;

	Vector2 m_local_axis_c_;
	Vector2 m_local_axis_d_;

	Float32 m_reference_angle_a_;
	Float32 m_reference_angle_b_;

	Float32 m_constant_;
	Float32 m_ratio_;

	Float32 m_impulse_;

	// Solver temp
	Int32 m_index_a_, m_index_b_, m_index_c_, m_index_d_;
	Vector2 m_lc_a_, m_lc_b_, m_lc_c_, m_lc_d_;
	Float32 m_m_a_, m_m_b_, m_m_c_, m_m_d_;
	Float32 m_i_a_, m_i_b_, m_i_c_, m_i_d_;
	Vector2 m_jv_ac_, m_jv_bd_;
	Float32 m_jw_a_, m_jw_b_, m_jw_c_, m_jw_d_;
	Float32 m_mass_;
};

} // namespace box2d

#endif // B2_GEAR_JOINT_HPP
