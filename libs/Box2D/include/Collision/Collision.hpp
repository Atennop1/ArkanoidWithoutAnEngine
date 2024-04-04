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

#ifndef B2_COLLISION_HPP
#define B2_COLLISION_HPP

#include "Common/Math.hpp"
#include <climits>

namespace Box2D
{

/// @file
/// Structures and functions used for computing m_contact_ m_points_, m_distance_
/// queries, and TOI queries.

class Shape;
class CircleShape;
class EdgeShape;
class PolygonShape;

const UInt8 null_feature = UCHAR_MAX;

/// The features that intersect to form the m_contact_ point
/// This must be 4 bytes or less.
struct ContactFeature
{
	enum Type
	{
		e_vertex = 0,
		e_face = 1
	};

	UInt8 m_index_a_;		///< Feature index on shapeA
	UInt8 m_index_b_;		///< Feature index on shapeB
	UInt8 m_type_a_;		///< The feature m_type_ on shapeA
	UInt8 m_type_b_;		///< The feature m_type_ on shapeB
};

/// Contact ids to facilitate warm starting.
union ContactID
{
	ContactFeature m_cf_;
	UInt32 m_key_;					///< Used to quickly compare m_contact_ ids.
};

/// A manifold point is m_a_ m_contact_ point belonging to m_a_ m_contact_
/// manifold. It holds details related to the geometry and dynamics
/// of the m_contact_ m_points_.
/// The local point usage depends on the manifold m_type_:
/// -e_circles: the local center of circleB
/// -e_faceA: the local center of cirlceB or the clip point of polygonB
/// -e_faceB: the clip point of polygonA
/// This structure is stored across time steps, so we keep it small.
/// Note: the impulses are used for internal caching and may not
/// provide reliable m_contact_ forces, especially for high speed collisions.
struct ManifoldPoint
{
	Vector2 m_local_point_;		///< usage depends on manifold m_type_
	Float32 m_normal_impulse_;	///< the non-penetration impulse
	Float32 m_tangent_impulse_;	///< the m_friction_ impulse
	ContactID m_id_;			///< uniquely identifies m_a_ m_contact_ point between two shapes
};

/// A manifold for two touching convex shapes.
/// Box2D supports multiple types of m_contact_:
/// - clip point versus plane with radius
/// - point versus point with radius (circles)
/// The local point usage depends on the manifold m_type_:
/// -e_circles: the local center of circleA
/// -e_faceA: the center of faceA
/// -e_faceB: the center of faceB
/// Similarly the local m_normal_ usage:
/// -e_circles: not used
/// -e_faceA: the m_normal_ on polygonA
/// -e_faceB: the m_normal_ on polygonB
/// We store m_contacts_ in this way so that m_position_ correction can
/// account for movement, which is critical for continuous physics.
/// All m_contact_ scenarios must be expressed in one of these types.
/// This structure is stored across time steps, so we keep it small.
struct Manifold
{
	enum Type
	{
		e_circles,
		e_faceA,
		e_faceB
	};

	ManifoldPoint m_points_[max_manifold_points];	///< the m_points_ of m_contact_
	Vector2 m_local_normal_;								///< not use for Type::e_points
	Vector2 m_local_point_;								///< usage depends on manifold m_type_
	Type m_type_;
	Int32 m_point_count_;								///< the number of manifold m_points_
};

/// This is used to compute the current state of m_a_ m_contact_ manifold.
struct WorldManifold
{
	/// Evaluate the manifold with supplied transforms. This assumes
	/// modest motion from the original state. This does not change the
	/// point m_count_, impulses, etc. The radii must come from the shapes
	/// that generated the manifold.
	void Initialize(const Manifold* manifold,
                    const Transform& xfA, Float32 radiusA,
                    const Transform& xfB, Float32 radiusB);

	Vector2 m_normal_;								///< world vector pointing from A to B
	Vector2 m_points_[max_manifold_points];		///< world m_contact_ point (point of intersection)
	Float32 m_separations_[max_manifold_points];	///< m_a_ negative value indicates overlap, in meters
};

/// This is used for determining the state of m_contact_ m_points_.
enum PointState
{
	nullState,		///< point does not exist
	addState,		///< point was added in the update
	persistState,	///< point persisted across the update
	removeState		///< point was removed in the update
};

/// Compute the point states given two manifolds. The states pertain to the transition from manifold1
/// to manifold2. So state1 is either persist or remove while state2 is either add or persist.
void GetPointStates(PointState state1[max_manifold_points], PointState state2[max_manifold_points],
                    const Manifold* manifold1, const Manifold* manifold2);

/// Used for computing m_contact_ manifolds.
struct ClipVertex
{
	Vector2 m_v_;
	ContactID m_id_;
};

/// Ray-cast input m_data_. The ray extends from m_p1_ to m_p1_ + m_max_fraction_ * (m_p2_ - m_p1_).
struct RayCastInput
{
	Vector2 m_p1_, m_p2_;
	Float32 m_max_fraction_;
};

/// Ray-cast output m_data_. The ray hits at m_p1_ + m_fraction_ * (m_p2_ - m_p1_), where m_p1_ and m_p2_
/// come from Box2D::RayCastInput.
struct RayCastOutput
{
	Vector2 m_normal_;
	Float32 m_fraction_;
};

/// An axis aligned bounding box.
struct AABB
{
	/// Verify that the bounds are sorted.
	bool IsValid() const;

	/// Get the center of the AABB.
	Vector2 GetCenter() const
	{
		return 0.5f * (m_lower_bound_ + m_upper_bound_);
	}

	/// Get the extents of the AABB (half-widths).
	Vector2 GetExtents() const
	{
		return 0.5f * (m_upper_bound_ - m_lower_bound_);
	}

	/// Get the perimeter m_length_
	Float32 GetPerimeter() const
	{
		Float32 wx = m_upper_bound_.m_x_ - m_lower_bound_.m_x_;
		Float32 wy = m_upper_bound_.m_y_ - m_lower_bound_.m_y_;
		return 2.0f * (wx + wy);
	}

	/// Combine an AABB into this one.
	void Combine(const AABB& aabb)
	{
        m_lower_bound_ = Min(m_lower_bound_, aabb.m_lower_bound_);
        m_upper_bound_ = Max(m_upper_bound_, aabb.m_upper_bound_);
	}

	/// Combine two AABBs into this one.
	void Combine(const AABB& aabb1, const AABB& aabb2)
	{
        m_lower_bound_ = Min(aabb1.m_lower_bound_, aabb2.m_lower_bound_);
        m_upper_bound_ = Max(aabb1.m_upper_bound_, aabb2.m_upper_bound_);
	}

	/// Does this m_aabb_ contain the provided AABB.
	bool Contains(const AABB& aabb) const
	{
		bool result = true;
		result = result && m_lower_bound_.m_x_ <= aabb.m_lower_bound_.m_x_;
		result = result && m_lower_bound_.m_y_ <= aabb.m_lower_bound_.m_y_;
		result = result && aabb.m_upper_bound_.m_x_ <= m_upper_bound_.m_x_;
		result = result && aabb.m_upper_bound_.m_y_ <= m_upper_bound_.m_y_;
		return result;
	}

	bool RayCast(RayCastOutput* output, const RayCastInput& input) const;

	Vector2 m_lower_bound_;	///< the lower vertex
	Vector2 m_upper_bound_;	///< the upper vertex
};

/// Compute the collision manifold between two circles.
void CollideCircles(Manifold* manifold,
					const CircleShape* circleA, const Transform& xfA,
					const CircleShape* circleB, const Transform& xfB);

/// Compute the collision manifold between m_a_ polygon and m_a_ circle.
void CollidePolygonAndCircle(Manifold* manifold,
							 const PolygonShape* polygonA, const Transform& xfA,
							 const CircleShape* circleB, const Transform& xfB);

/// Compute the collision manifold between two polygons.
void CollidePolygons(Manifold* manifold,
					 const PolygonShape* polygonA, const Transform& xfA,
					 const PolygonShape* polygonB, const Transform& xfB);

/// Compute the collision manifold between an edge and m_a_ circle.
void CollideEdgeAndCircle(Manifold* manifold,
						  const EdgeShape* polygonA, const Transform& xfA,
						  const CircleShape* circleB, const Transform& xfB);

/// Compute the collision manifold between an edge and m_a_ circle.
void CollideEdgeAndPolygon(Manifold* manifold,
						   const EdgeShape* edgeA, const Transform& xfA,
						   const PolygonShape* circleB, const Transform& xfB);

/// Clipping for m_contact_ manifolds.
Int32 ClipSegmentToLine(ClipVertex vOut[2], const ClipVertex vIn[2],
                        const Vector2& normal, Float32 offset, Int32 vertexIndexA);

/// Determine if two generic shapes overlap.
bool TestOverlap(const Shape* shapeA, Int32 indexA,
                 const Shape* shapeB, Int32 indexB,
                 const Transform& xfA, const Transform& xfB);

// ---------------- Inline Functions ------------------------------------------

inline bool AABB::IsValid() const
{
	Vector2 d = m_upper_bound_ - m_lower_bound_;
	bool valid = d.m_x_ >= 0.0f && d.m_y_ >= 0.0f;
	valid = valid && m_lower_bound_.IsValid() && m_upper_bound_.IsValid();
	return valid;
}

inline bool TestOverlap(const AABB& a, const AABB& b)
{
	Vector2 d1, d2;
	d1 = b.m_lower_bound_ - a.m_upper_bound_;
	d2 = a.m_lower_bound_ - b.m_upper_bound_;

	if (d1.m_x_ > 0.0f || d1.m_y_ > 0.0f)
		return false;

	if (d2.m_x_ > 0.0f || d2.m_y_ > 0.0f)
		return false;

	return true;
}

} // namespace Box2D

#endif // B2_COLLISION_HPP
