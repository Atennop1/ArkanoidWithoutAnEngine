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

#ifndef B2_CIRCLE_SHAPE_HPP
#define B2_CIRCLE_SHAPE_HPP

#include <Collision/Shapes/Shape.hpp>

namespace box2d
{

/// A circle m_shape_.
class CircleShape : public Shape
{
public:
	CircleShape();

	/// Implement box2d::Shape.
	Shape* Clone(BlockAllocator* allocator) const;

	/// @see box2d::Shape::GetChildCount
	Int32 GetChildCount() const;

	/// Implement box2d::Shape.
	bool TestPoint(const Transform& transform, const Vector2& p) const;

	/// Implement box2d::Shape.
	bool RayCast(RayCastOutput* output, const RayCastInput& input,
                 const Transform& transform, Int32 childIndex) const;

	/// @see box2d::Shape::ComputeAABB
	void ComputeAABB(AABB* aabb, const Transform& transform, Int32 childIndex) const;

	/// @see box2d::Shape::ComputeMass
	void ComputeMass(MassData* massData, Float32 density) const;

	/// Get the supporting vertex index in the given direction.
	Int32 GetSupport(const Vector2& d) const;

	/// Get the supporting vertex in the given direction.
	const Vector2& GetSupportVertex(const Vector2& d) const;

	/// Get the vertex m_count_.
	Int32 GetVertexCount() const { return 1; }

	/// Get m_a_ vertex by index. Used by box2d::Distance.
	const Vector2& GetVertex(Int32 index) const;

	/// Position
	Vector2 m_position_;
};

inline CircleShape::CircleShape()
{
    m_type_ = e_circle;
    m_radius_ = 0.0f;
	m_position_.SetZero();
}

inline Int32 CircleShape::GetSupport(const Vector2 &d) const
{
	B2_NOT_USED(d);
	return 0;
}

inline const Vector2& CircleShape::GetSupportVertex(const Vector2 &d) const
{
	B2_NOT_USED(d);
	return m_position_;
}

inline const Vector2& CircleShape::GetVertex(Int32 index) const
{
	B2_NOT_USED(index);
	assert(index == 0);
	return m_position_;
}

} // namespace box2d

#endif // B2_CIRCLE_SHAPE_HPP
