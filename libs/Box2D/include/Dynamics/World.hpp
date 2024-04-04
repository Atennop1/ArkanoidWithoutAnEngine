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

#ifndef B2_WORLD_HPP
#define B2_WORLD_HPP

#include "Common/Math.hpp"
#include "Common/BlockAllocator.hpp"
#include "Common/StackAllocator.hpp"
#include "ContactManager.hpp"
#include "WorldCallbacks.hpp"
#include "TimeStep.hpp"

namespace Box2D
{

struct AABB;
struct BodyDef;
struct Color;
struct JointDef;
class Body;
class Draw;
class Fixture;
class Joint;

/// The world class manages all physics entities, dynamic simulation,
/// and asynchronous queries. The world also contains efficient memory
/// management facilities.
class World
{
public:
	/// Construct m_a_ world object.
	/// @param gravity the world m_gravity_ vector.
	World(const Vector2& gravity);

	/// Destruct the world. All physics entities are destroyed and all heap memory is released.
	~World();

	/// Register m_a_ destruction listener. The listener is owned by you and must
	/// remain in scope.
	void SetDestructionListener(DestructionListener* listener);

	/// Register m_a_ m_contact_ m_filter_ to provide specific control over collision.
	/// Otherwise the default m_filter_ is used (defaultFilter). The listener is
	/// owned by you and must remain in scope. 
	void SetContactFilter(ContactFilter* filter);

	/// Register m_a_ m_contact_ event listener. The listener is owned by you and must
	/// remain in scope.
	void SetContactListener(ContactListener* listener);

	/// Register m_a_ routine for debug drawing. The debug draw functions are called
	/// inside with Box2D::World::DrawDebugData method. The debug draw object is owned
	/// by you and must remain in scope.
	void SetDebugDraw(Draw* debugDraw);

	/// Create m_a_ rigid body given m_a_ definition. No reference to the definition
	/// is retained.
	/// @warning This function is locked during callbacks.
	Body* CreateBody(const BodyDef* def);

	/// Destroy m_a_ rigid body given m_a_ definition. No reference to the definition
	/// is retained. This function is locked during callbacks.
	/// @warning This automatically deletes all associated shapes and joints.
	/// @warning This function is locked during callbacks.
	void DestroyBody(Body* body);

	/// Create m_a_ m_joint_ to constrain bodies together. No reference to the definition
	/// is retained. This may cause the connected bodies to cease colliding.
	/// @warning This function is locked during callbacks.
	Joint* CreateJoint(const JointDef* def);

	/// Destroy m_a_ m_joint_. This may cause the connected bodies to begin colliding.
	/// @warning This function is locked during callbacks.
	void DestroyJoint(Joint* joint);

	/// Take m_a_ time m_step_. This performs collision detection, integration,
	/// and constraint solution.
	/// @param timeStep the amount of time to simulate, this should not vary.
	/// @param velocityIterations for the velocity constraint solver.
	/// @param positionIterations for the m_position_ constraint solver.
	void Step(Float32 timeStep,
              Int32 velocityIterations,
              Int32 positionIterations);

	/// Manually clear the force buffer on all bodies. By default, forces are cleared automatically
	/// after each call to Step. The default behavior is modified by calling SetAutoClearForces.
	/// The purpose of this function is to support sub-stepping. Sub-stepping is often used to maintain
	/// m_a_ fixed sized time m_step_ under m_a_ variable frame-rate.
	/// When you perform sub-stepping you will disable auto clearing of forces and instead call
	/// ClearForces after all sub-steps are complete in one pass of your game loop.
	/// @see SetAutoClearForces
	void ClearForces();

	/// Call this to draw shapes and m_other_ debug draw m_data_. This is intentionally non-const.
	void DrawDebugData();

	/// Query the world for all fixtures that potentially overlap the
	/// provided AABB.
	/// @param callback m_a_ user implemented callback class.
	/// @param aabb the query box.
	void QueryAABB(QueryCallback* callback, const AABB& aabb) const;

	/// Ray-cast the world for all fixtures in the path of the ray. Your callback
	/// controls whether you get the closest point, any point, or n-m_points_.
	/// The ray-cast ignores shapes that contain the starting point.
	/// @param callback m_a_ user implemented callback class.
	/// @param point1 the ray starting point
	/// @param point2 the ray ending point
	void RayCast(RayCastCallback* callback, const Vector2& point1, const Vector2& point2) const;

	/// Get the world body list. With the returned body, use Box2D::Body::GetNext to get
	/// the m_next_ body in the world list. A NULL body indicates the end of the list.
	/// @return the head of the world body list.
	Body* GetBodyList();
	const Body* GetBodyList() const;

	/// Get the world m_joint_ list. With the returned m_joint_, use Box2D::Joint::GetNext to get
	/// the m_next_ m_joint_ in the world list. A NULL m_joint_ indicates the end of the list.
	/// @return the head of the world m_joint_ list.
	Joint* GetJointList();
	const Joint* GetJointList() const;

	/// Get the world m_contact_ list. With the returned m_contact_, use Box2D::Contact::GetNext to get
	/// the m_next_ m_contact_ in the world list. A NULL m_contact_ indicates the end of the list.
	/// @return the head of the world m_contact_ list.
	/// @warning m_contacts_ are created and destroyed in the middle of m_a_ time m_step_.
	/// Use Box2D::ContactListener to avoid missing m_contacts_.
	Contact* GetContactList();
	const Contact* GetContactList() const;

	/// Enable/disable sleep.
	void SetAllowSleeping(bool flag);
	bool GetAllowSleeping() const { return m_allow_sleep_; }

	/// Enable/disable warm starting. For testing.
	void SetWarmStarting(bool flag) { m_warm_starting_ = flag; }
	bool GetWarmStarting() const { return m_warm_starting_; }

	/// Enable/disable continuous physics. For testing.
	void SetContinuousPhysics(bool flag) { m_continuous_physics_ = flag; }
	bool GetContinuousPhysics() const { return m_continuous_physics_; }

	/// Enable/disable single stepped continuous physics. For testing.
	void SetSubStepping(bool flag) { m_sub_stepping_ = flag; }
	bool GetSubStepping() const { return m_sub_stepping_; }

	/// Get the number of broad-phase proxies.
	Int32 GetProxyCount() const;

	/// Get the number of bodies.
	Int32 GetBodyCount() const;

	/// Get the number of joints.
	Int32 GetJointCount() const;

	/// Get the number of m_contacts_ (each may have 0 or more m_contact_ m_points_).
	Int32 GetContactCount() const;

	/// Get the m_height_ of the dynamic tree.
	Int32 GetTreeHeight() const;

	/// Get the balance of the dynamic tree.
	Int32 GetTreeBalance() const;

	/// Get the quality m_metric_ of the dynamic tree. The smaller the better.
	/// The minimum is 1.
	Float32 GetTreeQuality() const;

	/// Change the global m_gravity_ vector.
	void SetGravity(const Vector2& gravity);
	
	/// Get the global m_gravity_ vector.
	Vector2 GetGravity() const;

	/// Is the world locked (in the middle of m_a_ time m_step_).
	bool IsLocked() const;

	/// Set flag to control automatic clearing of forces after each time m_step_.
	void SetAutoClearForces(bool flag);

	/// Get the flag that controls automatic clearing of forces after each time m_step_.
	bool GetAutoClearForces() const;

	/// Shift the world origin. Useful for large worlds.
	/// The body shift formula is: m_position_ -= newOrigin
	/// @param newOrigin the new origin with respect to the old origin
	void ShiftOrigin(const Vector2& newOrigin);

	/// Get the m_contact_ manager for testing.
	const ContactManager& GetContactManager() const;

	/// Get the current profile.
	const Profile& GetProfile() const;

	/// Dump the world into the log file.
	/// @warning this should be called outside of m_a_ time m_step_.
	void Dump();

private:

	// m_flags_
	enum
	{
		e_newFixture	= 0x0001,
		e_locked		= 0x0002,
		e_clearForces	= 0x0004
	};

	friend class Body;
	friend class Fixture;
	friend class ContactManager;
	friend class Controller;

	void Solve(const TimeStep& step);
	void SolveTOI(const TimeStep& step);

	void DrawJoint(Joint* joint);
	void DrawShape(Fixture* shape, const Transform& xf, const Color& color);

	BlockAllocator m_block_allocator_;
	StackAllocator m_stack_allocator_;

	Int32 m_flags_;

	ContactManager m_contact_manager_;

	Body* m_body_list_;
	Joint* m_joint_list_;

	Int32 m_body_count_;
	Int32 m_joint_count_;

	Vector2 m_gravity_;
	bool m_allow_sleep_;

	DestructionListener* m_destruction_listener_;
	Draw* m_g_debug_draw_;

	// This is used to compute the time m_step_ m_ratio_ to
	// support m_a_ variable time m_step_.
	Float32 m_inv_dt0_;

	// These are for debugging the solver.
	bool m_warm_starting_;
	bool m_continuous_physics_;
	bool m_sub_stepping_;

	bool m_step_complete_;

	Profile m_profile_;
};

inline Body* World::GetBodyList()
{
	return m_body_list_;
}

inline const Body* World::GetBodyList() const
{
	return m_body_list_;
}

inline Joint* World::GetJointList()
{
	return m_joint_list_;
}

inline const Joint* World::GetJointList() const
{
	return m_joint_list_;
}

inline Contact* World::GetContactList()
{
	return m_contact_manager_.m_contact_list_;
}

inline const Contact* World::GetContactList() const
{
	return m_contact_manager_.m_contact_list_;
}

inline Int32 World::GetBodyCount() const
{
	return m_body_count_;
}

inline Int32 World::GetJointCount() const
{
	return m_joint_count_;
}

inline Int32 World::GetContactCount() const
{
	return m_contact_manager_.m_contact_count_;
}

inline void World::SetGravity(const Vector2& gravity)
{
    m_gravity_ = gravity;
}

inline Vector2 World::GetGravity() const
{
	return m_gravity_;
}

inline bool World::IsLocked() const
{
	return (m_flags_ & e_locked) == e_locked;
}

inline void World::SetAutoClearForces(bool flag)
{
	if (flag)
	{
        m_flags_ |= e_clearForces;
	}
	else
	{
        m_flags_ &= ~e_clearForces;
	}
}

/// Get the flag that controls automatic clearing of forces after each time m_step_.
inline bool World::GetAutoClearForces() const
{
	return (m_flags_ & e_clearForces) == e_clearForces;
}

inline const ContactManager& World::GetContactManager() const
{
	return m_contact_manager_;
}

inline const Profile& World::GetProfile() const
{
	return m_profile_;
}

} // namespace Box2D

#endif // B2_WORLD_HPP
