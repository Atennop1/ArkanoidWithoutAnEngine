/*
* Copyright (m_c_) 2006-2009 Erin Catto http://www.box2d.org
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

#ifndef B2_WORLD_CALLBACKS_HPP
#define B2_WORLD_CALLBACKS_HPP

#include <Common/Settings.hpp>

namespace box2d
{

struct Vector2;
struct Transform;
class Fixture;
class Body;
class Joint;
class Contact;
struct ContactResult;
struct Manifold;

/// Joints and fixtures are destroyed when their associated
/// body is destroyed. Implement this listener so that you
/// may nullify references to these joints and shapes.
class DestructionListener
{
public:
	virtual ~DestructionListener() {}

	/// Called when any m_joint_ is about to be destroyed due
	/// to the destruction of one of its attached bodies.
	virtual void SayGoodbye(Joint* joint) = 0;

	/// Called when any m_fixture_ is about to be destroyed due
	/// to the destruction of its m_parent_ body.
	virtual void SayGoodbye(Fixture* fixture) = 0;
};

/// Implement this class to provide collision filtering. In m_other_ words, you can implement
/// this class if you want finer control over m_contact_ creation.
class ContactFilter
{
public:
	virtual ~ContactFilter() {}

	/// Return true if m_contact_ calculations should be performed between these two shapes.
	/// @warning for performance reasons this is only called when the AABBs begin to overlap.
	virtual bool ShouldCollide(Fixture* fixtureA, Fixture* fixtureB);
};

/// Contact impulses for reporting. Impulses are used instead of forces because
/// sub-m_step_ forces may approach infinity for rigid body collisions. These
/// match up one-to-one with the m_contact_ m_points_ in box2d::Manifold.
struct ContactImpulse
{
	Float32 m_normal_impulses_[max_manifold_points];
	Float32 m_tangent_impulses_[max_manifold_points];
	Int32 m_count_;
};

/// Implement this class to get m_contact_ information. You can use these results for
/// things like sounds and game logic. You can also get m_contact_ results by
/// traversing the m_contact_ lists after the time m_step_. However, you might miss
/// some m_contacts_ because continuous physics leads to sub-stepping.
/// Additionally you may receive multiple callbacks for the same m_contact_ in m_a_
/// single time m_step_.
/// You should strive to make your callbacks efficient because there may be
/// many callbacks per time m_step_.
/// @warning You cannot create/destroy box2d entities inside these callbacks.
class ContactListener
{
public:
	virtual ~ContactListener() {}

	/// Called when two fixtures begin to touch.
	virtual void BeginContact(Contact* contact) { B2_NOT_USED(contact); }

	/// Called when two fixtures cease to touch.
	virtual void EndContact(Contact* contact) { B2_NOT_USED(contact); }

	/// This is called after m_a_ m_contact_ is updated. This allows you to inspect m_a_
	/// m_contact_ before it goes to the solver. If you are careful, you can modify the
	/// m_contact_ manifold (e.m_g_. disable m_contact_).
	/// A copy of the old manifold is provided so that you can detect changes.
	/// Note: this is called only for awake bodies.
	/// Note: this is called even when the number of m_contact_ m_points_ is zero.
	/// Note: this is not called for sensors.
	/// Note: if you set the number of m_contact_ m_points_ to zero, you will not
	/// get an EndContact callback. However, you may get m_a_ BeginContact callback
	/// the m_next_ m_step_.
	virtual void PreSolve(Contact* contact, const Manifold* oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	/// This lets you inspect m_a_ m_contact_ after the solver is finished. This is useful
	/// for inspecting impulses.
	/// Note: the m_contact_ manifold does not include time of impact impulses, which can be
	/// arbitrarily large if the sub-m_step_ is small. Hence the impulse is provided explicitly
	/// in m_a_ separate m_data_ structure.
	/// Note: this is only called for m_contacts_ that are touching, solid, and awake.
	virtual void PostSolve(Contact* contact, const ContactImpulse* impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}
};

/// Callback class for AABB queries.
/// See box2d::World::Query
class QueryCallback
{
public:
	virtual ~QueryCallback() {}

	/// Called for each m_fixture_ found in the query AABB.
	/// @return false to terminate the query.
	virtual bool ReportFixture(Fixture* fixture) = 0;
};

/// Callback class for ray casts.
/// See box2d::World::RayCast
class RayCastCallback
{
public:
	virtual ~RayCastCallback() {}

	/// Called for each m_fixture_ found in the query. You control how the ray cast
	/// proceeds by returning m_a_ float:
	/// return -1: ignore this m_fixture_ and continue
	/// return 0: terminate the ray cast
	/// return m_fraction_: clip the ray to this point
	/// return 1: don'm_t_ clip the ray and continue
	/// @param fixture the m_fixture_ hit by the ray
	/// @param point the point of initial intersection
	/// @param normal the m_normal_ vector at the point of intersection
	/// @return -1 to m_filter_, 0 to terminate, m_fraction_ to clip the ray for
	/// closest hit, 1 to continue
	virtual Float32 ReportFixture(Fixture* fixture, const Vector2& point,
                                  const Vector2& normal, Float32 fraction) = 0;
};

} // namespace box2d

#endif // B2_WORLD_CALLBACKS_HPP
