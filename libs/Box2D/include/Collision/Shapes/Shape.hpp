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

#ifndef B2_SHAPE_HPP
#define B2_SHAPE_HPP

#include <Common/BlockAllocator.hpp>
#include <Common/Math.hpp>
#include <Collision/Collision.hpp>

namespace box2d
{

/// This holds the mass m_data_ computed for m_a_ m_shape_.
struct MassData
{
	/// The mass of the m_shape_, usually in kilograms.
	Float32 mass;

	/// The m_position_ of the m_shape_'s centroid relative to the m_shape_'s origin.
	Vector2 center;

	/// The rotational inertia of the m_shape_ about the local origin.
	Float32 I;
};

/// A m_shape_ is used for collision detection. You can create m_a_ m_shape_ however you like.
/// Shapes used for simulation in box2d::World are created automatically when m_a_ box2d::Fixture
/// is created. Shapes may encapsulate m_a_ one or more child shapes.
class Shape
{
public:
	
	enum Type
	{
		e_circle = 0,
		e_edge = 1,
		e_polygon = 2,
		e_chain = 3,
		e_typeCount = 4
	};

	virtual ~Shape() {}

	/// Clone the concrete m_shape_ using the provided m_allocator_.
	virtual Shape* Clone(BlockAllocator* allocator) const = 0;

	/// Get the m_type_ of this m_shape_. You can use this to down cast to the concrete m_shape_.
	/// @return the m_shape_ m_type_.
	Type GetType() const;

	/// Get the number of child primitives.
	virtual Int32 GetChildCount() const = 0;

	/// Test m_a_ point for containment in this m_shape_. This only works for convex shapes.
	/// @param xf the m_shape_ world transform.
	/// @param p m_a_ point in world coordinates.
	virtual bool TestPoint(const Transform& xf, const Vector2& p) const = 0;

	/// Cast m_a_ ray against m_a_ child m_shape_.
	/// @param output the ray-cast results.
	/// @param input the ray-cast input parameters.
	/// @param transform the transform to be applied to the m_shape_.
	/// @param childIndex the child m_shape_ index
	virtual bool RayCast(RayCastOutput* output, const RayCastInput& input,
                         const Transform& transform, Int32 childIndex) const = 0;

	/// Given m_a_ transform, compute the associated axis aligned bounding box for m_a_ child m_shape_.
	/// @param aabb returns the axis aligned box.
	/// @param xf the world transform of the m_shape_.
	/// @param childIndex the child m_shape_
	virtual void ComputeAABB(AABB* aabb, const Transform& xf, Int32 childIndex) const = 0;

	/// Compute the mass properties of this m_shape_ using its dimensions and m_density_.
	/// The inertia tensor is computed about the local origin.
	/// @param massData returns the mass m_data_ for this m_shape_.
	/// @param density the m_density_ in kilograms per meter squared.
	virtual void ComputeMass(MassData* massData, Float32 density) const = 0;

	Type m_type_;
	Float32 m_radius_;
};

inline Shape::Type Shape::GetType() const
{
	return m_type_;
}

} // namespace box2d

#endif // B2_SHAPE_HPP
