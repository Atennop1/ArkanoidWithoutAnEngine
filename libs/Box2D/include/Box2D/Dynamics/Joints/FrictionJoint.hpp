/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B2_FRICTION_JOINT_HPP
#define B2_FRICTION_JOINT_HPP

#include <Box2D/Dynamics/Joints/Joint.hpp>

namespace Box2D
{

/// Friction joint definition.
struct FrictionJointDef : public JointDef
{
	FrictionJointDef()
	{
		type = e_frictionJoint;
		localAnchorA.SetZero();
		localAnchorB.SetZero();
		maxForce = 0.0f;
		maxTorque = 0.0f;
	}

	/// Initialize the bodies, anchors, axis, and reference angle using the world
	/// anchor and world axis.
	void Initialize(Body* bodyA, Body* bodyB, const Vec2& anchor);

	/// The local anchor point relative to bodyA's origin.
	Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin.
	Vec2 localAnchorB;

	/// The maximum friction force in N.
	float32 maxForce;

	/// The maximum friction torque in N-m.
	float32 maxTorque;
};

/// Friction joint. This is used for top-down friction.
/// It provides 2D translational friction and angular friction.
class FrictionJoint : public Joint
{
public:
	Vec2 GetAnchorA() const;
	Vec2 GetAnchorB() const;

	Vec2 GetReactionForce(float32 inv_dt) const;
	float32 GetReactionTorque(float32 inv_dt) const;

	/// The local anchor point relative to bodyA's origin.
	const Vec2& GetLocalAnchorA() const { return m_localAnchorA; }

	/// The local anchor point relative to bodyB's origin.
	const Vec2& GetLocalAnchorB() const  { return m_localAnchorB; }

	/// Set the maximum friction force in N.
	void SetMaxForce(float32 force);

	/// Get the maximum friction force in N.
	float32 GetMaxForce() const;

	/// Set the maximum friction torque in N*m.
	void SetMaxTorque(float32 torque);

	/// Get the maximum friction torque in N*m.
	float32 GetMaxTorque() const;

	/// Dump joint to dmLog
	void Dump();

protected:

	friend class Joint;

	FrictionJoint(const FrictionJointDef* def);

	void InitVelocityConstraints(const SolverData& data);
	void SolveVelocityConstraints(const SolverData& data);
	bool SolvePositionConstraints(const SolverData& data);

	Vec2 m_localAnchorA;
	Vec2 m_localAnchorB;

	// Solver shared
	Vec2 m_linearImpulse;
	float32 m_angularImpulse;
	float32 m_maxForce;
	float32 m_maxTorque;

	// Solver temp
	int32 m_indexA;
	int32 m_indexB;
	Vec2 m_rA;
	Vec2 m_rB;
	Vec2 m_localCenterA;
	Vec2 m_localCenterB;
	float32 m_invMassA;
	float32 m_invMassB;
	float32 m_invIA;
	float32 m_invIB;
	Mat22 m_linearMass;
	float32 m_angularMass;
};

} // namespace Box2D

#endif // B2_FRICTION_JOINT_HPP
