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

#ifndef B2_SETTINGS_HPP
#define B2_SETTINGS_HPP

#include <cstddef>
#include <cassert>
#include <cfloat>

#define B2_NOT_USED(x) ((void)(x))

namespace Box2D
{

typedef signed char	Int8;
typedef signed short Int16;
typedef signed int Int32;
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef float Float32;
typedef double Float64;

const Float32 max_float = FLT_MAX;
const Float32 epsilon   = FLT_EPSILON;
const Float32 pi        = 3.14159265359f;

/// @file
/// Global tuning constants based on meters-kilograms-seconds (MKS) units.
///

// Collision

/// The maximum number of m_contact_ m_points_ between two convex shapes. Do
/// not change this value.
const Int32 max_manifold_points	= 2;

/// The maximum number of m_vertices_ on m_a_ convex polygon. You cannot increase
/// this too much because Box2D::BlockAllocator has m_a_ maximum object m_size_.
const Int32 max_polygon_vertices	= 8;

/// This is used to fatten AABBs in the dynamic tree. This allows proxies
/// to move by m_a_ small amount without triggering m_a_ tree adjustment.
/// This is in meters.
const Float32 aabb_extension		= 0.1f;

/// This is used to fatten AABBs in the dynamic tree. This is used to predict
/// the future m_position_ based on the current displacement.
/// This is m_a_ dimensionless multiplier.
const Float32 aabb_multiplier	= 2.0f;

/// A small m_length_ used as m_a_ collision and constraint tolerance. Usually it is
/// chosen to be numerically significant, but visually insignificant.
const Float32 linear_slop		= 0.005f;

/// A small m_angle_ used as m_a_ collision and constraint tolerance. Usually it is
/// chosen to be numerically significant, but visually insignificant.
const Float32 angular_slop		= (2.0f / 180.0f * pi);

/// The radius of the polygon/edge m_shape_ skin. This should not be modified. Making
/// this smaller means polygons will have an insufficient buffer for continuous collision.
/// Making it larger may create artifacts for vertex collision.
const Float32 polygon_radius		= (2.0f * linear_slop);

/// Maximum number of sub-steps per m_contact_ in continuous physics simulation.
const Int32 max_sub_steps			= 8;


// Dynamics

/// Maximum number of m_contacts_ to be handled to m_solve_ m_a_ TOI impact.
const Int32 max_toi_contacts			= 32;

/// A velocity threshold for elastic collisions. Any collision with m_a_ relative m_linear_
/// velocity below this threshold will be treated as inelastic.
const Float32 velocity_threshold		= 1.0f;

/// The maximum m_linear_ m_position_ correction used when solving constraints. This helps to
/// prevent overshoot.
const Float32 max_linear_correction	= 0.2f;

/// The maximum angular m_position_ correction used when solving constraints. This helps to
/// prevent overshoot.
const Float32 max_angular_correction	= (8.0f / 180.0f * pi);

/// The maximum m_linear_ velocity of m_a_ body. This limit is very large and is used
/// to prevent numerical problems. You shouldn'm_t_ need to adjust this.
const Float32 max_translation		= 2.0f;
const Float32 max_translation_squared	= (max_translation * max_translation);

/// The maximum angular velocity of m_a_ body. This limit is very large and is used
/// to prevent numerical problems. You shouldn'm_t_ need to adjust this.
const Float32 max_rotation			= (0.5f * pi);
const Float32 max_rotation_squared	= (max_rotation * max_rotation);

/// This scale factor controls how fast overlap is resolved. Ideally this would be 1 so
/// that overlap is removed in one time m_step_. However using values close to 1 often lead
/// to overshoot.
const Float32 baumgarte				= 0.2f;
const Float32 toi_baugarte			= 0.75f;


// Sleep

/// The time that m_a_ body must be still before it will go to sleep.
const Float32 time_to_sleep			= 0.5f;

/// A body cannot sleep if its m_linear_ velocity is above this tolerance.
const Float32 linear_sleep_tolerance	= 0.01f;

/// A body cannot sleep if its angular velocity is above this tolerance.
const Float32 angular_sleep_tolerance	= (2.0f / 180.0f * pi);


// Memory Allocation

/// Implement this function to use your own memory m_allocator_.
void* Alloc(Int32 size);

/// If you implement Box2D::Alloc, you should also implement this function.
void Free(void* mem);

/// Logging function.
void Log(const char* string, ...);

/// Version numbering scheme.
/// See http://en.wikipedia.org/wiki/Software_versioning
struct Version
{
	Int32 m_major_;		///< significant changes
	Int32 m_minor_;		///< incremental changes
	Int32 m_revision_;		///< bug fixes
};

/// Current version.
extern Version version;

} // namespace Box2D

#endif // B2_SETTINGS_HPP
