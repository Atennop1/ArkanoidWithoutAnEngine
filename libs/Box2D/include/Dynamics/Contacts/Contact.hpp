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

#ifndef B2_CONTACT_HPP
#define B2_CONTACT_HPP

#include "Common/Math.hpp"
#include "Collision/Collision.hpp"
#include "Collision/Shapes/Shape.hpp"
#include "Dynamics/Fixture.hpp"

namespace Box2D
{

class Body;
class Contact;
class Fixture;
class World;
class BlockAllocator;
class StackAllocator;
class ContactListener;

/// Friction mixing law. The idea is to allow either m_fixture_ to drive the m_restitution_ to zero.
/// For example, anything slides on ice.
inline Float32 MixFriction(Float32 friction1, Float32 friction2)
{
	return sqrtf(friction1 * friction2);
}

/// Restitution mixing law. The idea is allow for anything to bounce off an inelastic surface.
/// For example, m_a_ superball bounces on anything.
inline Float32 MixRestitution(Float32 restitution1, Float32 restitution2)
{
	return restitution1 > restitution2 ? restitution1 : restitution2;
}

typedef Contact* ContactCreateFcn(Fixture* fixtureA, Int32 indexA,
                                  Fixture* fixtureB, Int32 indexB,
                                  BlockAllocator* allocator);
typedef void ContactDestroyFcn(Contact* contact, BlockAllocator* allocator);

struct ContactRegister
{
	ContactCreateFcn* m_create_fcn_;
	ContactDestroyFcn* m_destroy_fcn_;
	bool m_primary_;
};

/// A m_contact_ edge is used to connect bodies and m_contacts_ together
/// in m_a_ m_contact_ graph where each body is m_a_ node and each m_contact_
/// is an edge. A m_contact_ edge belongs to m_a_ doubly linked list
/// maintained in each attached body. Each m_contact_ has two m_contact_
/// nodes, one for each attached body.
struct ContactEdge
{
	Body* m_other_;			///< provides quick access to the m_other_ body attached.
	Contact* m_contact_;		///< the m_contact_
	ContactEdge* m_prev_;	///< the previous m_contact_ edge in the body's m_contact_ list
	ContactEdge* m_next_;	///< the m_next_ m_contact_ edge in the body's m_contact_ list
};

/// The class manages m_contact_ between two shapes. A m_contact_ exists for each overlapping
/// AABB in the broad-phase (except if filtered). Therefore m_a_ m_contact_ object may exist
/// that has no m_contact_ m_points_.
class Contact
{
public:

	/// Get the m_contact_ manifold. Do not modify the manifold unless you understand the
	/// internals of Box2D.
	Manifold* GetManifold();
	const Manifold* GetManifold() const;

	/// Get the world manifold.
	void GetWorldManifold(WorldManifold* worldManifold) const;

	/// Is this m_contact_ touching?
	bool IsTouching() const;

	/// Enable/disable this m_contact_. This can be used inside the pre-m_solve_
	/// m_contact_ listener. The m_contact_ is only disabled for the current
	/// time m_step_ (or sub-m_step_ in continuous collisions).
	void SetEnabled(bool flag);

	/// Has this m_contact_ been disabled?
	bool IsEnabled() const;

	/// Get the m_next_ m_contact_ in the world's m_contact_ list.
	Contact* GetNext();
	const Contact* GetNext() const;

	/// Get m_fixture_ A in this m_contact_.
	Fixture* GetFixtureA();
	const Fixture* GetFixtureA() const;

	/// Get the child primitive index for m_fixture_ A.
	Int32 GetChildIndexA() const;

	/// Get m_fixture_ B in this m_contact_.
	Fixture* GetFixtureB();
	const Fixture* GetFixtureB() const;

	/// Get the child primitive index for m_fixture_ B.
	Int32 GetChildIndexB() const;

	/// Override the default m_friction_ mixture. You can call this in Box2D::ContactListener::PreSolve.
	/// This value persists until set or reset.
	void SetFriction(Float32 friction);

	/// Get the m_friction_.
	Float32 GetFriction() const;

	/// Reset the m_friction_ mixture to the default value.
	void ResetFriction();

	/// Override the default m_restitution_ mixture. You can call this in Box2D::ContactListener::PreSolve.
	/// The value persists until you set or reset.
	void SetRestitution(Float32 restitution);

	/// Get the m_restitution_.
	Float32 GetRestitution() const;

	/// Reset the m_restitution_ to the default value.
	void ResetRestitution();

	/// Set the desired tangent speed for m_a_ conveyor belt behavior. In meters per second.
	void SetTangentSpeed(Float32 speed);

	/// Get the desired tangent speed. In meters per second.
	Float32 GetTangentSpeed() const;

	/// Evaluate this m_contact_ with your own manifold and transforms.
	virtual void Evaluate(Manifold* manifold, const Transform& xfA, const Transform& xfB) = 0;

protected:
	friend class ContactManager;
	friend class World;
	friend class ContactSolver;
	friend class Body;
	friend class Fixture;

	// Flags stored in m_flags_
	enum
	{
		// Used when crawling m_contact_ graph when forming islands.
		e_islandFlag		= 0x0001,

        // Set when the shapes are touching.
		e_touchingFlag		= 0x0002,

		// This m_contact_ can be disabled (by user)
		e_enabledFlag		= 0x0004,

		// This m_contact_ needs filtering because m_a_ m_fixture_ m_filter_ was changed.
		e_filterFlag		= 0x0008,

		// This m_bullet_ m_contact_ had m_a_ TOI event
		e_bulletHitFlag		= 0x0010,

		// This m_contact_ has m_a_ valid TOI in m_toi_
		e_toiFlag			= 0x0020
	};

	/// Flag this m_contact_ for filtering. Filtering will occur the m_next_ time m_step_.
	void FlagForFiltering();

	static void AddType(ContactCreateFcn* createFcn, ContactDestroyFcn* destroyFcn,
						Shape::Type typeA, Shape::Type typeB);
	static void InitializeRegisters();
	static Contact* Create(Fixture* fixtureA, Int32 indexA, Fixture* fixtureB, Int32 indexB, BlockAllocator* allocator);
	static void Destroy(Contact* contact, Shape::Type typeA, Shape::Type typeB, BlockAllocator* allocator);
	static void Destroy(Contact* contact, BlockAllocator* allocator);

	Contact() : m_fixture_a_(NULL), m_fixture_b_(NULL) {}
	Contact(Fixture* fixtureA, Int32 indexA, Fixture* fixtureB, Int32 indexB);
	virtual ~Contact() {}

	void Update(ContactListener* listener);

	static ContactRegister s_registers[Shape::e_typeCount][Shape::e_typeCount];
	static bool s_initialized;

	UInt32 m_flags_;

	// World pool and list pointers.
	Contact* m_prev_;
	Contact* m_next_;

	// Nodes for connecting bodies.
	ContactEdge m_node_a_;
	ContactEdge m_node_b_;

	Fixture* m_fixture_a_;
	Fixture* m_fixture_b_;

	Int32 m_index_a_;
	Int32 m_index_b_;

	Manifold m_manifold_;

	Int32 m_toi_count_;
	Float32 m_toi_;

	Float32 m_friction_;
	Float32 m_restitution_;

	Float32 m_tangent_speed_;
};

inline Manifold* Contact::GetManifold()
{
	return &m_manifold_;
}

inline const Manifold* Contact::GetManifold() const
{
	return &m_manifold_;
}

inline void Contact::GetWorldManifold(WorldManifold* worldManifold) const
{
	const Body* bodyA = m_fixture_a_->GetBody();
	const Body* bodyB = m_fixture_b_->GetBody();
	const Shape* shapeA = m_fixture_a_->GetShape();
	const Shape* shapeB = m_fixture_b_->GetShape();

	worldManifold->Initialize(&m_manifold_, bodyA->GetTransform(), shapeA->m_radius_, bodyB->GetTransform(), shapeB->m_radius_);
}

inline void Contact::SetEnabled(bool flag)
{
	if (flag)
	{
        m_flags_ |= e_enabledFlag;
	}
	else
	{
        m_flags_ &= ~e_enabledFlag;
	}
}

inline bool Contact::IsEnabled() const
{
	return (m_flags_ & e_enabledFlag) == e_enabledFlag;
}

inline bool Contact::IsTouching() const
{
	return (m_flags_ & e_touchingFlag) == e_touchingFlag;
}

inline Contact* Contact::GetNext()
{
	return m_next_;
}

inline const Contact* Contact::GetNext() const
{
	return m_next_;
}

inline Fixture* Contact::GetFixtureA()
{
	return m_fixture_a_;
}

inline const Fixture* Contact::GetFixtureA() const
{
	return m_fixture_a_;
}

inline Fixture* Contact::GetFixtureB()
{
	return m_fixture_b_;
}

inline Int32 Contact::GetChildIndexA() const
{
	return m_index_a_;
}

inline const Fixture* Contact::GetFixtureB() const
{
	return m_fixture_b_;
}

inline Int32 Contact::GetChildIndexB() const
{
	return m_index_b_;
}

inline void Contact::FlagForFiltering()
{
    m_flags_ |= e_filterFlag;
}

inline void Contact::SetFriction(Float32 friction)
{
    m_friction_ = friction;
}

inline Float32 Contact::GetFriction() const
{
	return m_friction_;
}

inline void Contact::ResetFriction()
{
    m_friction_ = MixFriction(m_fixture_a_->m_friction_, m_fixture_b_->m_friction_);
}

inline void Contact::SetRestitution(Float32 restitution)
{
    m_restitution_ = restitution;
}

inline Float32 Contact::GetRestitution() const
{
	return m_restitution_;
}

inline void Contact::ResetRestitution()
{
    m_restitution_ = MixRestitution(m_fixture_a_->m_restitution_, m_fixture_b_->m_restitution_);
}

inline void Contact::SetTangentSpeed(Float32 speed)
{
    m_tangent_speed_ = speed;
}

inline Float32 Contact::GetTangentSpeed() const
{
	return m_tangent_speed_;
}

} // namespace Box2D

#endif // B2_CONTACT_HPP
