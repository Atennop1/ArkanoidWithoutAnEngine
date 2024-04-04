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

#ifndef B2_CHAIN_SHAPE_HPP
#define B2_CHAIN_SHAPE_HPP

#include "Shape.hpp"

namespace Box2D
{

class EdgeShape;

/// A chain m_shape_ is m_a_ free form sequence of line segments.
/// The chain has two-sided collision, so you can use inside and outside collision.
/// Therefore, you may use any winding order.
/// Since there may be many m_vertices_, they are allocated using Box2D::Alloc.
/// Connectivity information is used to create smooth collisions.
/// WARNING: The chain will not m_collide_ properly if there are self-intersections.
class ChainShape : public Shape
{
public:
	ChainShape();

	/// The destructor frees the m_vertices_ using Box2D::Free.
	~ChainShape();

	/// Clear all m_data_.
	void Clear();

	/// Create m_a_ loop. This automatically adjusts connectivity.
	/// @param vertices an array of m_vertices_, these are copied
	/// @param count the vertex m_count_
	void CreateLoop(const Vector2* vertices, Int32 count);

	/// Create m_a_ chain with isolated end m_vertices_.
	/// @param vertices an array of m_vertices_, these are copied
	/// @param count the vertex m_count_
	void CreateChain(const Vector2* vertices, Int32 count);

	/// Establish connectivity to m_a_ vertex that precedes the first vertex.
	/// Don'm_t_ call this for loops.
	void SetPrevVertex(const Vector2& prevVertex);

	/// Establish connectivity to m_a_ vertex that follows the last vertex.
	/// Don'm_t_ call this for loops.
	void SetNextVertex(const Vector2& nextVertex);

	/// Implement Box2D::Shape. Vertices are cloned using Box2D::Alloc.
	Shape* Clone(BlockAllocator* allocator) const;

	/// @see Box2D::Shape::GetChildCount
	Int32 GetChildCount() const;

	/// Get m_a_ child edge.
	void GetChildEdge(EdgeShape* edge, Int32 index) const;

	/// This always return false.
	/// @see Box2D::Shape::TestPoint
	bool TestPoint(const Transform& transform, const Vector2& p) const;

	/// Implement Box2D::Shape.
	bool RayCast(RayCastOutput* output, const RayCastInput& input,
                 const Transform& transform, Int32 childIndex) const;

	/// @see Box2D::Shape::ComputeAABB
	void ComputeAABB(AABB* aabb, const Transform& transform, Int32 childIndex) const;

	/// Chains have zero mass.
	/// @see Box2D::Shape::ComputeMass
	void ComputeMass(MassData* massData, Float32 density) const;

	/// The m_vertices_. Owned by this class.
	Vector2* m_vertices_;

	/// The vertex m_count_.
	Int32 m_count_;

	Vector2 m_prev_vertex_, m_next_vertex_;
	bool m_has_prev_vertex_, m_has_next_vertex_;
};

inline ChainShape::ChainShape()
{
    m_type_ = e_chain;
    m_radius_ = polygon_radius;
    m_vertices_ = NULL;
    m_count_ = 0;
    m_has_prev_vertex_ = false;
    m_has_next_vertex_ = false;
}

} // namespace Box2D

#endif // B2_CHAIN_SHAPE_HPP
