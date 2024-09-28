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

#ifndef B2_FIXTURE_HPP
#define B2_FIXTURE_HPP

#include <Dynamics/Body.hpp>
#include <Collision/Collision.hpp>
#include <Collision/Shapes/Shape.hpp>

namespace box2d
{

class BlockAllocator;
class Body;
class BroadPhase;
class Fixture;

/// This holds m_contact_ filtering m_data_.
struct Filter
{
	Filter()
	{
        m_category_bits_ = 0x0001;
        m_mask_bits_ = 0xFFFF;
        m_group_index_ = 0;
	}

	/// The collision category bits. Normally you would just set one bit.
	UInt16 m_category_bits_;

	/// The collision mask bits. This states the categories that this
	/// m_shape_ would accept for collision.
	UInt16 m_mask_bits_;

	/// Collision groups allow m_a_ certain group of objects to never m_collide_ (negative)
	/// or always m_collide_ (positive). Zero means no collision group. Non-zero group
	/// filtering always wins against the mask bits.
	Int16 m_group_index_;
};

/// A m_fixture_ definition is used to create m_a_ m_fixture_. This class defines an
/// abstract m_fixture_ definition. You can reuse m_fixture_ definitions safely.
struct FixtureDef
{
	/// The constructor sets the default m_fixture_ definition values.
	FixtureDef()
	{
        m_shape_ = NULL;
        m_user_data_ = NULL;
        m_friction_ = 0.2f;
        m_restitution_ = 0.0f;
        m_density_ = 0.0f;
        m_is_sensor_ = false;
	}

	/// The m_shape_, this must be set. The m_shape_ will be cloned, so you
	/// can create the m_shape_ on the stack.
	const Shape* m_shape_;

	/// Use this to store application specific m_fixture_ m_data_.
	void* m_user_data_;

	/// The m_friction_ coefficient, usually in the range [0,1].
	Float32 m_friction_;

	/// The m_restitution_ (elasticity) usually in the range [0,1].
	Float32 m_restitution_;

	/// The m_density_, usually in kg/m^2.
	Float32 m_density_;

	/// A sensor m_shape_ collects m_contact_ information but never generates m_a_ collision
	/// response.
	bool m_is_sensor_;

	/// Contact filtering m_data_.
	Filter m_filter_;
};

/// This proxy is used internally to connect fixtures to the broad-phase.
struct FixtureProxy
{
	AABB m_aabb_;
	Fixture* m_fixture_;
	Int32 m_child_index_;
	Int32 m_proxy_id_;
};

/// A m_fixture_ is used to attach m_a_ m_shape_ to m_a_ body for collision detection. A m_fixture_
/// inherits its transform from its m_parent_. Fixtures hold additional non-geometric m_data_
/// such as m_friction_, collision filters, etc.
/// Fixtures are created via box2d::Body::CreateFixture.
/// @warning you cannot reuse fixtures.
class Fixture
{
public:
	/// Get the m_type_ of the child m_shape_. You can use this to down cast to the concrete m_shape_.
	/// @return the m_shape_ m_type_.
	Shape::Type GetType() const;

	/// Get the child m_shape_. You can modify the child m_shape_, however you should not change the
	/// number of m_vertices_ because this will crash some collision caching mechanisms.
	/// Manipulating the m_shape_ may lead to non-physical behavior.
	Shape* GetShape();
	const Shape* GetShape() const;

	/// Set if this m_fixture_ is m_a_ sensor.
	void SetSensor(bool sensor);

	/// Is this m_fixture_ m_a_ sensor (non-solid)?
	/// @return the true if the m_shape_ is m_a_ sensor.
	bool IsSensor() const;

	/// Set the m_contact_ filtering m_data_. This will not update m_contacts_ until the m_next_ time
	/// m_step_ when either m_parent_ body is m_active_ and awake.
	/// This automatically calls Refilter.
	void SetFilterData(const Filter& filter);

	/// Get the m_contact_ filtering m_data_.
	const Filter& GetFilterData() const;

	/// Call this if you want to establish collision that was previously disabled by box2d::ContactFilter::ShouldCollide.
	void Refilter();

	/// Get the m_parent_ body of this m_fixture_. This is NULL if the m_fixture_ is not attached.
	/// @return the m_parent_ body.
	Body* GetBody();
	const Body* GetBody() const;

	/// Get the m_next_ m_fixture_ in the m_parent_ body's m_fixture_ list.
	/// @return the m_next_ m_shape_.
	Fixture* GetNext();
	const Fixture* GetNext() const;

	/// Get the user m_data_ that was assigned in the m_fixture_ definition. Use this to
	/// store your application specific m_data_.
	void* GetUserData() const;

	/// Set the user m_data_. Use this to store your application specific m_data_.
	void SetUserData(void* data);

	/// Test m_a_ point for containment in this m_fixture_.
	/// @param p m_a_ point in world coordinates.
	bool TestPoint(const Vector2& p) const;

	/// Cast m_a_ ray against this m_shape_.
	/// @param output the ray-cast results.
	/// @param input the ray-cast input parameters.
	bool RayCast(RayCastOutput* output, const RayCastInput& input, Int32 childIndex) const;

	/// Get the mass m_data_ for this m_fixture_. The mass m_data_ is based on the m_density_ and
	/// the m_shape_. The rotational inertia is about the m_shape_'s origin. This operation
	/// may be expensive.
	void GetMassData(MassData* massData) const;

	/// Set the m_density_ of this m_fixture_. This will _not_ automatically adjust the mass
	/// of the body. You must call box2d::Body::ResetMassData to update the body's mass.
	void SetDensity(Float32 density);

	/// Get the m_density_ of this m_fixture_.
	Float32 GetDensity() const;

	/// Get the coefficient of m_friction_.
	Float32 GetFriction() const;

	/// Set the coefficient of m_friction_. This will _not_ change the m_friction_ of
	/// existing m_contacts_.
	void SetFriction(Float32 friction);

	/// Get the coefficient of m_restitution_.
	Float32 GetRestitution() const;

	/// Set the coefficient of m_restitution_. This will _not_ change the m_restitution_ of
	/// existing m_contacts_.
	void SetRestitution(Float32 restitution);

	/// Get the m_fixture_'s AABB. This AABB may be enlarge and/or stale.
	/// If you need m_a_ more accurate AABB, compute it using the m_shape_ and
	/// the body transform.
	const AABB& GetAABB(Int32 childIndex) const;

	/// Dump this m_fixture_ to the log file.
	void Dump(Int32 bodyIndex);

protected:

	friend class Body;
	friend class World;
	friend class Contact;
	friend class ContactManager;

	Fixture();

	// We need separation create/destroy functions from the constructor/destructor because
	// the destructor cannot access the m_allocator_ (no destructor arguments allowed by C++).
	void Create(BlockAllocator* allocator, Body* body, const FixtureDef* def);
	void Destroy(BlockAllocator* allocator);

	// These support body activation/deactivation.
	void CreateProxies(BroadPhase* broadPhase, const Transform& xf);
	void DestroyProxies(BroadPhase* broadPhase);

	void Synchronize(BroadPhase* broadPhase, const Transform& xf1, const Transform& xf2);

	Float32 m_density_;

	Fixture* m_next_;
	Body* m_body_;

	Shape* m_shape_;

	Float32 m_friction_;
	Float32 m_restitution_;

	FixtureProxy* m_proxies_;
	Int32 m_proxy_count_;

	Filter m_filter_;

	bool m_is_sensor_;

	void* m_user_data_;
};

inline Shape::Type Fixture::GetType() const
{
	return m_shape_->GetType();
}

inline Shape* Fixture::GetShape()
{
	return m_shape_;
}

inline const Shape* Fixture::GetShape() const
{
	return m_shape_;
}

inline bool Fixture::IsSensor() const
{
	return m_is_sensor_;
}

inline const Filter& Fixture::GetFilterData() const
{
	return m_filter_;
}

inline void* Fixture::GetUserData() const
{
	return m_user_data_;
}

inline void Fixture::SetUserData(void* data)
{
    m_user_data_ = data;
}

inline Body* Fixture::GetBody()
{
	return m_body_;
}

inline const Body* Fixture::GetBody() const
{
	return m_body_;
}

inline Fixture* Fixture::GetNext()
{
	return m_next_;
}

inline const Fixture* Fixture::GetNext() const
{
	return m_next_;
}

inline void Fixture::SetDensity(Float32 density)
{
	assert(IsValid(density) && density >= 0.0f);
    m_density_ = density;
}

inline Float32 Fixture::GetDensity() const
{
	return m_density_;
}

inline Float32 Fixture::GetFriction() const
{
	return m_friction_;
}

inline void Fixture::SetFriction(Float32 friction)
{
    m_friction_ = friction;
}

inline Float32 Fixture::GetRestitution() const
{
	return m_restitution_;
}

inline void Fixture::SetRestitution(Float32 restitution)
{
    m_restitution_ = restitution;
}

inline bool Fixture::TestPoint(const Vector2& p) const
{
	return m_shape_->TestPoint(m_body_->GetTransform(), p);
}

inline bool Fixture::RayCast(RayCastOutput* output, const RayCastInput& input, Int32 childIndex) const
{
	return m_shape_->RayCast(output, input, m_body_->GetTransform(), childIndex);
}

inline void Fixture::GetMassData(MassData* massData) const
{
	m_shape_->ComputeMass(massData, m_density_);
}

inline const AABB& Fixture::GetAABB(Int32 childIndex) const
{
	assert(0 <= childIndex && childIndex < m_proxy_count_);
	return m_proxies_[childIndex].m_aabb_;
}

} // namespace box2d

#endif // B2_FIXTURE_HPP
