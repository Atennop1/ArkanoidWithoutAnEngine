/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B2_MATH_HPP
#define B2_MATH_HPP

#include <Box2D/Common/Settings.hpp>
#include <cmath>

namespace Box2D
{

/// This function is used to ensure that a floating point number is not a NaN or infinity.
inline bool IsValid(float32 x)
{
	int32 ix = *reinterpret_cast<int32*>(&x);
	return (ix & 0x7f800000) != 0x7f800000;
}

/// This is a approximate yet fast inverse square-root.
inline float32 InvSqrt(float32 x)
{
	union
	{
		float32 x;
		int32 i;
	} convert;

	convert.x = x;
	float32 xhalf = 0.5f * x;
	convert.i = 0x5f3759df - (convert.i >> 1);
	x = convert.x;
	x = x * (1.5f - xhalf * x * x);
	return x;
}

/// A 2D column vector.
struct Vec2
{
	/// Default constructor does nothing (for performance).
	Vec2() {}

	/// Construct using coordinates.
	Vec2(float32 x, float32 y) : x(x), y(y) {}

	/// Set this vector to all zeros.
	void SetZero() { x = 0.0f; y = 0.0f; }

	/// Set this vector to some specified coordinates.
	void Set(float32 x_, float32 y_) { x = x_; y = y_; }

	/// Negate this vector.
	Vec2 operator -() const { Vec2 v; v.Set(-x, -y); return v; }
	
	/// Read from and indexed element.
	float32 operator () (int32 i) const
	{
		return (&x)[i];
	}

	/// Write to an indexed element.
	float32& operator () (int32 i)
	{
		return (&x)[i];
	}

	/// Add a vector to this vector.
	void operator += (const Vec2& v)
	{
		x += v.x; y += v.y;
	}
	
	/// Subtract a vector from this vector.
	void operator -= (const Vec2& v)
	{
		x -= v.x; y -= v.y;
	}

	/// Multiply this vector by a scalar.
	void operator *= (float32 a)
	{
		x *= a; y *= a;
	}

	/// Get the length of this vector (the norm).
	float32 Length() const
	{
		return std::sqrt(x * x + y * y);
	}

	/// Get the length squared. For performance, use this instead of
	/// Box2D::Vec2::Length (if possible).
	float32 LengthSquared() const
	{
		return x * x + y * y;
	}

	/// Convert this vector into a unit vector. Returns the length.
	float32 Normalize()
	{
		float32 length = Length();
		if (length < epsilon)
		{
			return 0.0f;
		}
		float32 invLength = 1.0f / length;
		x *= invLength;
		y *= invLength;

		return length;
	}

	/// Does this vector contain finite coordinates?
	bool IsValid() const
	{
		return Box2D::IsValid(x) && Box2D::IsValid(y);
	}

	/// Get the skew vector such that dot(skew_vec, other) == cross(vec, other)
	Vec2 Skew() const
	{
		return Vec2(-y, x);
	}

	float32 x, y;
};

/// A 2D column vector with 3 elements.
struct Vec3
{
	/// Default constructor does nothing (for performance).
	Vec3() {}

	/// Construct using coordinates.
	Vec3(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {}

	/// Set this vector to all zeros.
	void SetZero() { x = 0.0f; y = 0.0f; z = 0.0f; }

	/// Set this vector to some specified coordinates.
	void Set(float32 x_, float32 y_, float32 z_) { x = x_; y = y_; z = z_; }

	/// Negate this vector.
	Vec3 operator -() const { Vec3 v; v.Set(-x, -y, -z); return v; }

	/// Add a vector to this vector.
	void operator += (const Vec3& v)
	{
		x += v.x; y += v.y; z += v.z;
	}

	/// Subtract a vector from this vector.
	void operator -= (const Vec3& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
	}

	/// Multiply this vector by a scalar.
	void operator *= (float32 s)
	{
		x *= s; y *= s; z *= s;
	}

	float32 x, y, z;
};

/// A 2-by-2 matrix. Stored in column-major order.
struct Mat22
{
	/// The default constructor does nothing (for performance).
	Mat22() {}

	/// Construct this matrix using columns.
	Mat22(const Vec2& c1, const Vec2& c2)
	{
		ex = c1;
		ey = c2;
	}

	/// Construct this matrix using scalars.
	Mat22(float32 a11, float32 a12, float32 a21, float32 a22)
	{
		ex.x = a11; ex.y = a21;
		ey.x = a12; ey.y = a22;
	}

	/// Initialize this matrix using columns.
	void Set(const Vec2& c1, const Vec2& c2)
	{
		ex = c1;
		ey = c2;
	}

	/// Set this to the identity matrix.
	void SetIdentity()
	{
		ex.x = 1.0f; ey.x = 0.0f;
		ex.y = 0.0f; ey.y = 1.0f;
	}

	/// Set this matrix to all zeros.
	void SetZero()
	{
		ex.x = 0.0f; ey.x = 0.0f;
		ex.y = 0.0f; ey.y = 0.0f;
	}

	Mat22 GetInverse() const
	{
		float32 a = ex.x, b = ey.x, c = ex.y, d = ey.y;
		Mat22 B;
		float32 det = a * d - b * c;
		if (det != 0.0f)
		{
			det = 1.0f / det;
		}
		B.ex.x =  det * d;	B.ey.x = -det * b;
		B.ex.y = -det * c;	B.ey.y =  det * a;
		return B;
	}

	/// Solve A * x = b, where b is a column vector. This is more efficient
	/// than computing the inverse in one-shot cases.
	Vec2 Solve(const Vec2& b) const
	{
		float32 a11 = ex.x, a12 = ey.x, a21 = ex.y, a22 = ey.y;
		float32 det = a11 * a22 - a12 * a21;
		if (det != 0.0f)
		{
			det = 1.0f / det;
		}
		Vec2 x;
		x.x = det * (a22 * b.x - a12 * b.y);
		x.y = det * (a11 * b.y - a21 * b.x);
		return x;
	}

	Vec2 ex, ey;
};

/// A 3-by-3 matrix. Stored in column-major order.
struct Mat33
{
	/// The default constructor does nothing (for performance).
	Mat33() {}

	/// Construct this matrix using columns.
	Mat33(const Vec3& c1, const Vec3& c2, const Vec3& c3)
	{
		ex = c1;
		ey = c2;
		ez = c3;
	}

	/// Set this matrix to all zeros.
	void SetZero()
	{
		ex.SetZero();
		ey.SetZero();
		ez.SetZero();
	}

	/// Solve A * x = b, where b is a column vector. This is more efficient
	/// than computing the inverse in one-shot cases.
	Vec3 Solve33(const Vec3& b) const;

	/// Solve A * x = b, where b is a column vector. This is more efficient
	/// than computing the inverse in one-shot cases. Solve only the upper
	/// 2-by-2 matrix equation.
	Vec2 Solve22(const Vec2& b) const;

	/// Get the inverse of this matrix as a 2-by-2.
	/// Returns the zero matrix if singular.
	void GetInverse22(Mat33* M) const;

	/// Get the symmetric inverse of this matrix as a 3-by-3.
	/// Returns the zero matrix if singular.
	void GetSymInverse33(Mat33* M) const;

	Vec3 ex, ey, ez;
};

/// Rotation
struct Rot
{
	Rot() {}

	/// Initialize from an angle in radians
	explicit Rot(float32 angle)
	{
		/// TODO_ERIN optimize
		s = std::sin(angle);
		c = std::cos(angle);
	}

	/// Set using an angle in radians.
	void Set(float32 angle)
	{
		/// TODO_ERIN optimize
		s = std::sin(angle);
		c = std::cos(angle);
	}

	/// Set to the identity rotation
	void SetIdentity()
	{
		s = 0.0f;
		c = 1.0f;
	}

	/// Get the angle in radians
	float32 GetAngle() const
	{
		return std::atan2(s, c);
	}

	/// Get the x-axis
	Vec2 GetXAxis() const
	{
		return Vec2(c, s);
	}

	/// Get the u-axis
	Vec2 GetYAxis() const
	{
		return Vec2(-s, c);
	}

	/// Sine and cosine
	float32 s, c;
};

/// A transform contains translation and rotation. It is used to represent
/// the position and orientation of rigid frames.
struct Transform
{
	/// The default constructor does nothing.
	Transform() {}

	/// Initialize using a position vector and a rotation.
	Transform(const Vec2& position, const Rot& rotation) : p(position), q(rotation) {}

	/// Set this to the identity transform.
	void SetIdentity()
	{
		p.SetZero();
		q.SetIdentity();
	}

	/// Set this based on the position and angle.
	void Set(const Vec2& position, float32 angle)
	{
		p = position;
		q.Set(angle);
	}

	Vec2 p;
	Rot q;
};

/// This describes the motion of a body/shape for TOI computation.
/// Shapes are defined with respect to the body origin, which may
/// no coincide with the center of mass. However, to support dynamics
/// we must interpolate the center of mass position.
struct Sweep
{
	/// Get the interpolated transform at a specific time.
	/// @param beta is a factor in [0,1], where 0 indicates alpha0.
	void GetTransform(Transform* xfb, float32 beta) const;

	/// Advance the sweep forward, yielding a new initial state.
	/// @param alpha the new initial time.
	void Advance(float32 alpha);

	/// Normalize the angles.
	void Normalize();

	Vec2 localCenter;	///< local center of mass position
	Vec2 c0, c;		///< center world positions
	float32 a0, a;		///< world angles

	/// Fraction of the current time step in the range [0,1]
	/// c0 and a0 are the positions at alpha0.
	float32 alpha0;
};

/// Useful constant
extern const Vec2 Vec2_zero;

/// Perform the dot product on two vectors.
inline float32 Dot(const Vec2& a, const Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

/// Perform the cross product on two vectors. In 2D this produces a scalar.
inline float32 Cross(const Vec2& a, const Vec2& b)
{
	return a.x * b.y - a.y * b.x;
}

/// Perform the cross product on a vector and a scalar. In 2D this produces
/// a vector.
inline Vec2 Cross(const Vec2& a, float32 s)
{
	return Vec2(s * a.y, -s * a.x);
}

/// Perform the cross product on a scalar and a vector. In 2D this produces
/// a vector.
inline Vec2 Cross(float32 s, const Vec2& a)
{
	return Vec2(-s * a.y, s * a.x);
}

/// Multiply a matrix times a vector. If a rotation matrix is provided,
/// then this transforms the vector from one frame to another.
inline Vec2 Mul(const Mat22& A, const Vec2& v)
{
	return Vec2(A.ex.x * v.x + A.ey.x * v.y, A.ex.y * v.x + A.ey.y * v.y);
}

/// Multiply a matrix transpose times a vector. If a rotation matrix is provided,
/// then this transforms the vector from one frame to another (inverse transform).
inline Vec2 MulT(const Mat22& A, const Vec2& v)
{
	return Vec2(Dot(v, A.ex), Dot(v, A.ey));
}

/// Add two vectors component-wise.
inline Vec2 operator + (const Vec2& a, const Vec2& b)
{
	return Vec2(a.x + b.x, a.y + b.y);
}

/// Subtract two vectors component-wise.
inline Vec2 operator - (const Vec2& a, const Vec2& b)
{
	return Vec2(a.x - b.x, a.y - b.y);
}

inline Vec2 operator * (float32 s, const Vec2& a)
{
	return Vec2(s * a.x, s * a.y);
}

inline bool operator == (const Vec2& a, const Vec2& b)
{
	return a.x == b.x && a.y == b.y;
}

inline float32 Distance(const Vec2& a, const Vec2& b)
{
	Vec2 c = a - b;
	return c.Length();
}

inline float32 DistanceSquared(const Vec2& a, const Vec2& b)
{
	Vec2 c = a - b;
	return Dot(c, c);
}

inline Vec3 operator * (float32 s, const Vec3& a)
{
	return Vec3(s * a.x, s * a.y, s * a.z);
}

/// Add two vectors component-wise.
inline Vec3 operator + (const Vec3& a, const Vec3& b)
{
	return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

/// Subtract two vectors component-wise.
inline Vec3 operator - (const Vec3& a, const Vec3& b)
{
	return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

/// Perform the dot product on two vectors.
inline float32 Dot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/// Perform the cross product on two vectors.
inline Vec3 Cross(const Vec3& a, const Vec3& b)
{
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline Mat22 operator + (const Mat22& A, const Mat22& B)
{
	return Mat22(A.ex + B.ex, A.ey + B.ey);
}

// A * B
inline Mat22 Mul(const Mat22& A, const Mat22& B)
{
	return Mat22(Mul(A, B.ex), Mul(A, B.ey));
}

// A^T * B
inline Mat22 MulT(const Mat22& A, const Mat22& B)
{
	Vec2 c1(Dot(A.ex, B.ex), Dot(A.ey, B.ex));
	Vec2 c2(Dot(A.ex, B.ey), Dot(A.ey, B.ey));
	return Mat22(c1, c2);
}

/// Multiply a matrix times a vector.
inline Vec3 Mul(const Mat33& A, const Vec3& v)
{
	return v.x * A.ex + v.y * A.ey + v.z * A.ez;
}

/// Multiply a matrix times a vector.
inline Vec2 Mul22(const Mat33& A, const Vec2& v)
{
	return Vec2(A.ex.x * v.x + A.ey.x * v.y, A.ex.y * v.x + A.ey.y * v.y);
}

/// Multiply two rotations: q * r
inline Rot Mul(const Rot& q, const Rot& r)
{
	// [qc -qs] * [rc -rs] = [qc*rc-qs*rs -qc*rs-qs*rc]
	// [qs  qc]   [rs  rc]   [qs*rc+qc*rs -qs*rs+qc*rc]
	// s = qs * rc + qc * rs
	// c = qc * rc - qs * rs
	Rot qr;
	qr.s = q.s * r.c + q.c * r.s;
	qr.c = q.c * r.c - q.s * r.s;
	return qr;
}

/// Transpose multiply two rotations: qT * r
inline Rot MulT(const Rot& q, const Rot& r)
{
	// [ qc qs] * [rc -rs] = [qc*rc+qs*rs -qc*rs+qs*rc]
	// [-qs qc]   [rs  rc]   [-qs*rc+qc*rs qs*rs+qc*rc]
	// s = qc * rs - qs * rc
	// c = qc * rc + qs * rs
	Rot qr;
	qr.s = q.c * r.s - q.s * r.c;
	qr.c = q.c * r.c + q.s * r.s;
	return qr;
}

/// Rotate a vector
inline Vec2 Mul(const Rot& q, const Vec2& v)
{
	return Vec2(q.c * v.x - q.s * v.y, q.s * v.x + q.c * v.y);
}

/// Inverse rotate a vector
inline Vec2 MulT(const Rot& q, const Vec2& v)
{
	return Vec2(q.c * v.x + q.s * v.y, -q.s * v.x + q.c * v.y);
}

inline Vec2 Mul(const Transform& T, const Vec2& v)
{
	float32 x = (T.q.c * v.x - T.q.s * v.y) + T.p.x;
	float32 y = (T.q.s * v.x + T.q.c * v.y) + T.p.y;

	return Vec2(x, y);
}

inline Vec2 MulT(const Transform& T, const Vec2& v)
{
	float32 px = v.x - T.p.x;
	float32 py = v.y - T.p.y;
	float32 x = (T.q.c * px + T.q.s * py);
	float32 y = (-T.q.s * px + T.q.c * py);

	return Vec2(x, y);
}

// v2 = A.q.Rot(B.q.Rot(v1) + B.p) + A.p
//    = (A.q * B.q).Rot(v1) + A.q.Rot(B.p) + A.p
inline Transform Mul(const Transform& A, const Transform& B)
{
	Transform C;
	C.q = Mul(A.q, B.q);
	C.p = Mul(A.q, B.p) + A.p;
	return C;
}

// v2 = A.q' * (B.q * v1 + B.p - A.p)
//    = A.q' * B.q * v1 + A.q' * (B.p - A.p)
inline Transform MulT(const Transform& A, const Transform& B)
{
	Transform C;
	C.q = MulT(A.q, B.q);
	C.p = MulT(A.q, B.p - A.p);
	return C;
}

template <typename T>
inline T Abs(T a)
{
	return a > T(0) ? a : -a;
}

inline Vec2 Abs(const Vec2& a)
{
	return Vec2(Abs(a.x), Abs(a.y));
}

inline Mat22 Abs(const Mat22& A)
{
	return Mat22(Abs(A.ex), Abs(A.ey));
}

template <typename T>
inline T Min(T a, T b)
{
	return a < b ? a : b;
}

inline Vec2 Min(const Vec2& a, const Vec2& b)
{
	return Vec2(Min(a.x, b.x), Min(a.y, b.y));
}

template <typename T>
inline T Max(T a, T b)
{
	return a > b ? a : b;
}

inline Vec2 Max(const Vec2& a, const Vec2& b)
{
	return Vec2(Max(a.x, b.x), Max(a.y, b.y));
}

template <typename T>
inline T Clamp(T a, T low, T high)
{
	return Max(low, Min(a, high));
}

inline Vec2 Clamp(const Vec2& a, const Vec2& low, const Vec2& high)
{
	return Max(low, Min(a, high));
}

template<typename T> inline void Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

/// "Next Largest Power of 2
/// Given a binary integer value x, the next largest power of 2 can be computed by a SWAR algorithm
/// that recursively "folds" the upper bits into the lower bits. This process yields a bit vector with
/// the same most significant 1 as x, but all 1's below it. Adding 1 to that value yields the next
/// largest power of 2. For a 32-bit value:"
inline uint32 NextPowerOfTwo(uint32 x)
{
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x + 1;
}

inline bool IsPowerOfTwo(uint32 x)
{
	bool result = x > 0 && (x & (x - 1)) == 0;
	return result;
}

inline void Sweep::GetTransform(Transform* xf, float32 beta) const
{
	xf->p = (1.0f - beta) * c0 + beta * c;
	float32 angle = (1.0f - beta) * a0 + beta * a;
	xf->q.Set(angle);

	// Shift to origin
	xf->p -= Mul(xf->q, localCenter);
}

inline void Sweep::Advance(float32 alpha)
{
	assert(alpha0 < 1.0f);
	float32 beta = (alpha - alpha0) / (1.0f - alpha0);
	c0 += beta * (c - c0);
	a0 += beta * (a - a0);
	alpha0 = alpha;
}

/// Normalize an angle in radians to be between -pi and pi
inline void Sweep::Normalize()
{
	float32 twoPi = 2.0f * pi;
	float32 d =  twoPi * floorf(a0 / twoPi);
	a0 -= d;
	a -= d;
}

} // namespace Box2D

#endif // B2_MATH_HPP
