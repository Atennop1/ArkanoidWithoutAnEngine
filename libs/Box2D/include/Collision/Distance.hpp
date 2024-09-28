
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

#ifndef B2_DISTANCE_HPP
#define B2_DISTANCE_HPP

#include <Common/Math.hpp>

namespace box2d
{

class Shape;

/// A m_distance_ proxy is used by the GJK algorithm.
/// It encapsulates any m_shape_.
struct DistanceProxy
{
	DistanceProxy() : m_vertices_(NULL), m_count_(0), m_radius_(0.0f) {}

	/// Initialize the proxy using the given m_shape_. The m_shape_
	/// must remain in scope while the proxy is in use.
	void Set(const Shape* shape, Int32 index);

	/// Get the supporting vertex index in the given direction.
	Int32 GetSupport(const Vector2& d) const;

	/// Get the supporting vertex in the given direction.
	const Vector2& GetSupportVertex(const Vector2& d) const;

	/// Get the vertex m_count_.
	Int32 GetVertexCount() const;

	/// Get m_a_ vertex by index. Used by box2d::Distance.
	const Vector2& GetVertex(Int32 index) const;

	Vector2 m_buffer_[2];
	const Vector2* m_vertices_;
	Int32 m_count_;
	Float32 m_radius_;
};

/// Used to warm start box2d::Distance.
/// Set m_count_ to zero on first call.
struct SimplexCache
{
	Float32 m_metric_;		///< m_length_ or area
	UInt16 m_count_;
	UInt8 m_index_a_[3];	///< m_vertices_ on m_shape_ A
	UInt8 m_index_b_[3];	///< m_vertices_ on m_shape_ B
};

/// Input for box2d::Distance.
/// You have to option to use the m_shape_ radii
/// in the computation. Even 
struct DistanceInput
{
	DistanceProxy m_proxy_a_;
	DistanceProxy m_proxy_b_;
	Transform m_transform_a_;
	Transform m_transform_b_;
	bool m_use_radii_;
};

/// Output for box2d::Distance.
struct DistanceOutput
{
	Vector2 m_point_a_;		///< closest point on shapeA
	Vector2 m_point_b_;		///< closest point on shapeB
	Float32 m_distance_;
	Int32 m_iterations_;	///< number of GJK m_iterations_ used
};

/// Compute the closest m_points_ between two shapes. Supports any combination of:
/// box2d::CircleShape, box2d::PolygonShape, box2d::EdgeShape. The simplex cache is input/output.
/// On the first call set box2d::SimplexCache.m_count_ to zero.
void Distance(DistanceOutput* output,
				SimplexCache* cache, 
				const DistanceInput* input);


//////////////////////////////////////////////////////////////////////////

inline Int32 DistanceProxy::GetVertexCount() const
{
	return m_count_;
}

inline const Vector2& DistanceProxy::GetVertex(Int32 index) const
{
	assert(0 <= index && index < m_count_);
	return m_vertices_[index];
}

inline Int32 DistanceProxy::GetSupport(const Vector2& d) const
{
	Int32 bestIndex = 0;
	Float32 bestValue = Dot(m_vertices_[0], d);
	for (Int32 i = 1; i < m_count_; ++i)
	{
		Float32 value = Dot(m_vertices_[i], d);
		if (value > bestValue)
		{
			bestIndex = i;
			bestValue = value;
		}
	}

	return bestIndex;
}

inline const Vector2& DistanceProxy::GetSupportVertex(const Vector2& d) const
{
	Int32 bestIndex = 0;
	Float32 bestValue = Dot(m_vertices_[0], d);
	for (Int32 i = 1; i < m_count_; ++i)
	{
		Float32 value = Dot(m_vertices_[i], d);
		if (value > bestValue)
		{
			bestIndex = i;
			bestValue = value;
		}
	}

	return m_vertices_[bestIndex];
}

} // namespace box2d

#endif // B2_DISTANCE_HPP
