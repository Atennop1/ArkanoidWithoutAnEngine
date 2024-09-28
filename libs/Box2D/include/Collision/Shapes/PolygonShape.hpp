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

#ifndef B2_POLYGON_SHAPE_HPP
#define B2_POLYGON_SHAPE_HPP

#include <Collision/Shapes/Shape.hpp>

namespace box2d
{

/// A convex polygon. It is assumed that the interior of the polygon is to
/// the left of each edge.
/// Polygons have m_a_ maximum number of m_vertices_ equal to max_polygon_vertices.
/// In most cases you should not need many m_vertices_ for m_a_ convex polygon.
class PolygonShape : public Shape
{
public:
	PolygonShape();

	/// Implement box2d::Shape.
	Shape* Clone(BlockAllocator* allocator) const;

	/// @see box2d::Shape::GetChildCount
	Int32 GetChildCount() const;

	/// Create m_a_ convex hull from the given array of local m_points_.
	/// The m_count_ must be in the range [3, max_polygon_vertices].
	/// @warning the m_points_ may be re-ordered, even if they form m_a_ convex polygon
	/// @warning collinear m_points_ are handled but not removed. Collinear m_points_
	/// may lead to poor stacking behavior.
	void Set(const Vector2* points, Int32 count);

	/// Build m_vertices_ to represent an axis-aligned box centered on the local origin.
	/// @param hx the half-width.
	/// @param hy the half-m_height_.
	void SetAsBox(Float32 hx, Float32 hy);

	/// Build m_vertices_ to represent an oriented box.
	/// @param hx the half-width.
	/// @param hy the half-m_height_.
	/// @param center the center of the box in local coordinates.
	/// @param angle the rotation of the box in local coordinates.
	void SetAsBox(Float32 hx, Float32 hy, const Vector2& center, Float32 angle);

	/// @see box2d::Shape::TestPoint
	bool TestPoint(const Transform& transform, const Vector2& p) const;

	/// Implement box2d::Shape.
	bool RayCast(RayCastOutput* output, const RayCastInput& input,
                 const Transform& transform, Int32 childIndex) const;

	/// @see box2d::Shape::ComputeAABB
	void ComputeAABB(AABB* aabb, const Transform& transform, Int32 childIndex) const;

	/// @see box2d::Shape::ComputeMass
	void ComputeMass(MassData* massData, Float32 density) const;

	/// Get the vertex m_count_.
	Int32 GetVertexCount() const { return m_count_; }

	/// Get m_a_ vertex by index.
	const Vector2& GetVertex(Int32 index) const;

	/// Validate convexity. This is m_a_ very time consuming operation.
	/// @returns true if valid
	bool Validate() const;

	Vector2 m_centroid_;
	Vector2 m_vertices_[max_polygon_vertices];
	Vector2 m_normals_[max_polygon_vertices];
	Int32 m_count_;
};

inline PolygonShape::PolygonShape()
{
    m_type_ = e_polygon;
    m_radius_ = polygon_radius;
    m_count_ = 0;
	m_centroid_.SetZero();
}

inline const Vector2& PolygonShape::GetVertex(Int32 index) const
{
	assert(0 <= index && index < m_count_);
	return m_vertices_[index];
}

} // namespace box2d

#endif // B2_POLYGON_SHAPE_HPP
