/*
* Copyright (m_c_) 2006-2010 Erin Catto http://www.box2d.org
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

#ifndef B2_EDGE_SHAPE_HPP
#define B2_EDGE_SHAPE_HPP

#include "Shape.hpp"

namespace Box2D
{

/// A line segment (edge) m_shape_. These can be connected in chains or loops
/// to m_other_ edge shapes. The connectivity information is used to ensure
/// correct m_contact_ normals.
class EdgeShape : public Shape
{
public:
	EdgeShape();

	/// Set this as an isolated edge.
	void Set(const Vector2& v1, const Vector2& v2);

	/// Implement Box2D::Shape.
	Shape* Clone(BlockAllocator* allocator) const;

	/// @see Box2D::Shape::GetChildCount
	Int32 GetChildCount() const;

	/// @see Box2D::Shape::TestPoint
	bool TestPoint(const Transform& transform, const Vector2& p) const;

	/// Implement Box2D::Shape.
	bool RayCast(RayCastOutput* output, const RayCastInput& input,
                 const Transform& transform, Int32 childIndex) const;

	/// @see Box2D::Shape::ComputeAABB
	void ComputeAABB(AABB* aabb, const Transform& transform, Int32 childIndex) const;

	/// @see Box2D::Shape::ComputeMass
	void ComputeMass(MassData* massData, Float32 density) const;
	
	/// These are the edge m_vertices_
	Vector2 m_vertex1_, m_vertex2_;

	/// Optional adjacent m_vertices_. These are used for smooth collision.
	Vector2 m_vertex0_, m_vertex3_;
	bool m_has_vertex0_, m_has_vertex3_;
};

inline EdgeShape::EdgeShape()
{
    m_type_ = e_edge;
    m_radius_ = polygon_radius;
    m_vertex0_.m_x_ = 0.0f;
    m_vertex0_.m_y_ = 0.0f;
    m_vertex3_.m_x_ = 0.0f;
    m_vertex3_.m_y_ = 0.0f;
    m_has_vertex0_ = false;
    m_has_vertex3_ = false;
}

} // namespace Box2D

#endif // B2_EDGE_SHAPE_HPP
