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

#ifndef B2_JOINT_HPP
#define B2_JOINT_HPP

#include "Common/Math.hpp"

namespace Box2D
{

class Body;
class Joint;
struct SolverData;
class BlockAllocator;

enum JointType
{
	e_unknownJoint,
	e_revoluteJoint,
	e_prismaticJoint,
	e_distanceJoint,
	e_pulleyJoint,
	e_mouseJoint,
	e_gearJoint,
	e_wheelJoint,
    e_weldJoint,
	e_frictionJoint,
	e_ropeJoint,
	e_motorJoint
};

enum LimitState
{
	e_inactiveLimit,
	e_atLowerLimit,
	e_atUpperLimit,
	e_equalLimits
};

struct Jacobian
{
    explicit Jacobian(Float32 angular_a);

    Vector2 m_linear_;
	Float32 m_angular_a_;
	Float32 m_angular_b_;
};

/// A m_joint_ edge is used to connect bodies and joints together
/// in m_a_ m_joint_ graph where each body is m_a_ node and each m_joint_
/// is an edge. A m_joint_ edge belongs to m_a_ doubly linked list
/// maintained in each attached body. Each m_joint_ has two m_joint_
/// nodes, one for each attached body.
struct JointEdge
{
	Body* m_other_;			///< provides quick access to the m_other_ body attached.
	Joint* m_joint_;			///< the m_joint_
	JointEdge* m_prev_;		///< the previous m_joint_ edge in the body's m_joint_ list
	JointEdge* m_next_;		///< the m_next_ m_joint_ edge in the body's m_joint_ list
};

/// Joint definitions are used to construct joints.
struct JointDef
{
	JointDef()
	{
        m_type_ = e_unknownJoint;
        m_user_data_ = NULL;
        m_body_a_ = NULL;
        m_body_b_ = NULL;
        m_collide_connected_ = false;
	}

	/// The m_joint_ m_type_ is set automatically for concrete m_joint_ types.
	JointType m_type_;

	/// Use this to attach application specific m_data_ to your joints.
	void* m_user_data_;

	/// The first attached body.
	Body* m_body_a_;

	/// The second attached body.
	Body* m_body_b_;

	/// Set this flag to true if the attached bodies should m_collide_.
	bool m_collide_connected_;
};

/// The base m_joint_ class. Joints are used to constraint two bodies together in
/// various fashions. Some joints also feature limits and motors.
class Joint
{
public:

	/// Get the m_type_ of the concrete m_joint_.
	JointType GetType() const;

	/// Get the first body attached to this m_joint_.
	Body* GetBodyA();

	/// Get the second body attached to this m_joint_.
	Body* GetBodyB();

	/// Get the anchor point on m_body_a_ in world coordinates.
	virtual Vector2 GetAnchorA() const = 0;

	/// Get the anchor point on m_body_b_ in world coordinates.
	virtual Vector2 GetAnchorB() const = 0;

	/// Get the reaction force on m_body_b_ at the m_joint_ anchor in Newtons.
	virtual Vector2 GetReactionForce(Float32 inv_dt) const = 0;

	/// Get the reaction torque on m_body_b_ in N*m.
	virtual Float32 GetReactionTorque(Float32 inv_dt) const = 0;

	/// Get the m_next_ m_joint_ the world m_joint_ list.
	Joint* GetNext();
	const Joint* GetNext() const;

	/// Get the user m_data_ pointer.
	void* GetUserData() const;

	/// Set the user m_data_ pointer.
	void SetUserData(void* data);

	/// Short-cut function to determine if either body is inactive.
	bool IsActive() const;

	/// Get m_collide_ connected.
	/// Note: modifying the m_collide_ connect flag won'm_t_ work correctly because
	/// the flag is only checked when m_fixture_ AABBs begin to overlap.
	bool GetCollideConnected() const;

	/// Dump this m_joint_ to the log file.
	virtual void Dump() { Log("// Dump is not supported for this m_joint_ m_type_.\n"); }

	/// Shift the origin for any m_points_ stored in world coordinates.
	virtual void ShiftOrigin(const Vector2& newOrigin) { B2_NOT_USED(newOrigin);  }

protected:
	friend class World;
	friend class Body;
	friend class Island;
	friend class GearJoint;

	static Joint* Create(const JointDef* def, BlockAllocator* allocator);
	static void Destroy(Joint* joint, BlockAllocator* allocator);

	Joint(const JointDef* def);
	virtual ~Joint() {}

	virtual void InitVelocityConstraints(const SolverData& data) = 0;
	virtual void SolveVelocityConstraints(const SolverData& data) = 0;

	// This returns true if the m_position_ errors are within tolerance.
	virtual bool SolvePositionConstraints(const SolverData& data) = 0;

	JointType m_type_;
	Joint* m_prev_;
	Joint* m_next_;
	JointEdge m_edge_a_;
	JointEdge m_edge_b_;
	Body* m_body_a_;
	Body* m_body_b_;

	Int32 m_index_;

	bool m_island_flag_;
	bool m_collide_connected_;

	void* m_user_data_;
};

inline JointType Joint::GetType() const
{
	return m_type_;
}

inline Body* Joint::GetBodyA()
{
	return m_body_a_;
}

inline Body* Joint::GetBodyB()
{
	return m_body_b_;
}

inline Joint* Joint::GetNext()
{
	return m_next_;
}

inline const Joint* Joint::GetNext() const
{
	return m_next_;
}

inline void* Joint::GetUserData() const
{
	return m_user_data_;
}

inline void Joint::SetUserData(void* data)
{
    m_user_data_ = data;
}

inline bool Joint::GetCollideConnected() const
{
	return m_collide_connected_;
}

} // namespace Box2D

#endif // B2_JOINT_HPP
