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

#ifndef B2_MATH_HPP
#define B2_MATH_HPP

#include <Common/Settings.hpp>
#include <cmath>

namespace box2d
{

/// This function is used to ensure that m_a_ floating point number is not m_a_ NaN or infinity.
inline bool IsValid(Float32 x)
{
	Int32 ix = *reinterpret_cast<Int32*>(&x);
	return (ix & 0x7f800000) != 0x7f800000;
}

/// This is m_a_ approximate yet fast inverse square-root.
inline Float32 InverseSqrt(Float32 x)
{
	union
	{
		Float32 m_x_;
		Int32 m_i_;
	} convert;

	convert.m_x_ = x;
	Float32 xhalf = 0.5f * x;
	convert.m_i_ = 0x5f3759df - (convert.m_i_ >> 1);
	x = convert.m_x_;
	x = x * (1.5f - xhalf * x * x);
	return x;
}

/// A 2D column vector.
struct Vector2
{
	/// Default constructor does nothing (for performance).
	Vector2() {}

	/// Construct using coordinates.
	Vector2(Float32 x, Float32 y) : m_x_(x), m_y_(y) {}

	/// Set this vector to all zeros.
	void SetZero() { m_x_ = 0.0f; m_y_ = 0.0f; }

	/// Set this vector to some specified coordinates.
	void Set(Float32 x_, Float32 y_) { m_x_ = x_; m_y_ = y_; }

	/// Negate this vector.
	Vector2 operator -() const { Vector2 v; v.Set(-m_x_, -m_y_); return v; }
	
	/// Read from and indexed element.
	Float32 operator () (Int32 i) const
	{
		return (&m_x_)[i];
	}

	/// Write to an indexed element.
	Float32& operator () (Int32 i)
	{
		return (&m_x_)[i];
	}

	/// Add m_a_ vector to this vector.
	void operator += (const Vector2& v)
	{
        m_x_ += v.m_x_; m_y_ += v.m_y_;
	}
	
	/// Subtract m_a_ vector from this vector.
	void operator -= (const Vector2& v)
	{
        m_x_ -= v.m_x_; m_y_ -= v.m_y_;
	}

	/// Multiply this vector by m_a_ scalar.
	void operator *= (Float32 a)
	{
        m_x_ *= a; m_y_ *= a;
	}

	/// Get the m_length_ of this vector (the norm).
	Float32 Length() const
	{
		return std::sqrt(m_x_ * m_x_ + m_y_ * m_y_);
	}

	/// Get the m_length_ squared. For performance, use this instead of
	/// box2d::Vector2::Length (if possible).
	Float32 LengthSquared() const
	{
		return m_x_ * m_x_ + m_y_ * m_y_;
	}

	/// Convert this vector into m_a_ unit vector. Returns the m_length_.
	Float32 Normalize()
	{
		Float32 length = Length();
		if (length < epsilon)
		{
			return 0.0f;
		}
		Float32 invLength = 1.0f / length;
        m_x_ *= invLength;
        m_y_ *= invLength;

		return length;
	}

	/// Does this vector contain finite coordinates?
	bool IsValid() const
	{
		return box2d::IsValid(m_x_) && box2d::IsValid(m_y_);
	}

	/// Get the skew vector such that dot(skew_vec, m_other_) == cross(vec, m_other_)
	Vector2 Skew() const
	{
		return Vector2(-m_y_, m_x_);
	}

	Float32 m_x_, m_y_;
};

/// A 2D column vector with 3 elements.
struct Vector3
{
	/// Default constructor does nothing (for performance).
	Vector3() {}

	/// Construct using coordinates.
	Vector3(Float32 x, Float32 y, Float32 z) : m_x_(x), m_y_(y), m_z_(z) {}

	/// Set this vector to all zeros.
	void SetZero() { m_x_ = 0.0f; m_y_ = 0.0f; m_z_ = 0.0f; }

	/// Set this vector to some specified coordinates.
	void Set(Float32 x_, Float32 y_, Float32 z_) { m_x_ = x_; m_y_ = y_; m_z_ = z_; }

	/// Negate this vector.
	Vector3 operator -() const { Vector3 v; v.Set(-m_x_, -m_y_, -m_z_); return v; }

	/// Add m_a_ vector to this vector.
	void operator += (const Vector3& v)
	{
        m_x_ += v.m_x_; m_y_ += v.m_y_; m_z_ += v.m_z_;
	}

	/// Subtract m_a_ vector from this vector.
	void operator -= (const Vector3& v)
	{
        m_x_ -= v.m_x_; m_y_ -= v.m_y_; m_z_ -= v.m_z_;
	}

	/// Multiply this vector by m_a_ scalar.
	void operator *= (Float32 s)
	{
        m_x_ *= s; m_y_ *= s; m_z_ *= s;
	}

	Float32 m_x_, m_y_, m_z_;
};

/// A 2-by-2 matrix. Stored in column-m_major_ order.
struct Mat22
{
	/// The default constructor does nothing (for performance).
	Mat22() {}

	/// Construct this matrix using columns.
	Mat22(const Vector2& c1, const Vector2& c2)
	{
        m_ex_ = c1;
        m_ey_ = c2;
	}

	/// Construct this matrix using scalars.
	Mat22(Float32 a11, Float32 a12, Float32 a21, Float32 a22)
	{
        m_ex_.m_x_ = a11; m_ex_.m_y_ = a21;
        m_ey_.m_x_ = a12; m_ey_.m_y_ = a22;
	}

	/// Initialize this matrix using columns.
	void Set(const Vector2& c1, const Vector2& c2)
	{
        m_ex_ = c1;
        m_ey_ = c2;
	}

	/// Set this to the identity matrix.
	void SetIdentity()
	{
        m_ex_.m_x_ = 1.0f; m_ey_.m_x_ = 0.0f;
        m_ex_.m_y_ = 0.0f; m_ey_.m_y_ = 1.0f;
	}

	/// Set this matrix to all zeros.
	void SetZero()
	{
        m_ex_.m_x_ = 0.0f; m_ey_.m_x_ = 0.0f;
        m_ex_.m_y_ = 0.0f; m_ey_.m_y_ = 0.0f;
	}

	Mat22 GetInverse() const
	{
		Float32 a = m_ex_.m_x_, b = m_ey_.m_x_, c = m_ex_.m_y_, d = m_ey_.m_y_;
		Mat22 B;
		Float32 det = a * d - b * c;
		if (det != 0.0f)
		{
			det = 1.0f / det;
		}
		B.m_ex_.m_x_ = det * d; B.m_ey_.m_x_ = -det * b;
		B.m_ex_.m_y_ = -det * c; B.m_ey_.m_y_ = det * a;
		return B;
	}

	/// Solve A * m_x_ = m_b_, where m_b_ is m_a_ column vector. This is more efficient
	/// than computing the inverse in one-shot cases.
	Vector2 Solve(const Vector2& b) const
	{
		Float32 a11 = m_ex_.m_x_, a12 = m_ey_.m_x_, a21 = m_ex_.m_y_, a22 = m_ey_.m_y_;
		Float32 det = a11 * a22 - a12 * a21;
		if (det != 0.0f)
		{
			det = 1.0f / det;
		}
		Vector2 x;
		x.m_x_ = det * (a22 * b.m_x_ - a12 * b.m_y_);
		x.m_y_ = det * (a11 * b.m_y_ - a21 * b.m_x_);
		return x;
	}

	Vector2 m_ex_, m_ey_;
};

/// A 3-by-3 matrix. Stored in column-m_major_ order.
struct Mat33
{
	/// The default constructor does nothing (for performance).
	Mat33() {}

	/// Construct this matrix using columns.
	Mat33(const Vector3& c1, const Vector3& c2, const Vector3& c3)
	{
        m_ex_ = c1;
        m_ey_ = c2;
        m_ez_ = c3;
	}

	/// Set this matrix to all zeros.
	void SetZero()
	{
		m_ex_.SetZero();
		m_ey_.SetZero();
		m_ez_.SetZero();
	}

	/// Solve A * m_x_ = m_b_, where m_b_ is m_a_ column vector. This is more efficient
	/// than computing the inverse in one-shot cases.
	Vector3 Solve33(const Vector3& b) const;

	/// Solve A * m_x_ = m_b_, where m_b_ is m_a_ column vector. This is more efficient
	/// than computing the inverse in one-shot cases. Solve only the upper
	/// 2-by-2 matrix equation.
	Vector2 Solve22(const Vector2& b) const;

	/// Get the inverse of this matrix as m_a_ 2-by-2.
	/// Returns the zero matrix if singular.
	void GetInverse22(Mat33* M) const;

	/// Get the symmetric inverse of this matrix as m_a_ 3-by-3.
	/// Returns the zero matrix if singular.
	void GetSymInverse33(Mat33* M) const;

	Vector3 m_ex_, m_ey_, m_ez_;
};

/// Rotation
struct Rot
{
	Rot() {}

	/// Initialize from an m_angle_ in radians
	explicit Rot(Float32 angle)
	{
		/// TODO_ERIN optimize
		m_s_ = std::sin(angle);
        m_c_ = std::cos(angle);
	}

	/// Set using an m_angle_ in radians.
	void Set(Float32 angle)
	{
		/// TODO_ERIN optimize
		m_s_ = std::sin(angle);
        m_c_ = std::cos(angle);
	}

	/// Set to the identity rotation
	void SetIdentity()
	{
        m_s_ = 0.0f;
        m_c_ = 1.0f;
	}

	/// Get the m_angle_ in radians
	Float32 GetAngle() const
	{
		return std::atan2(m_s_, m_c_);
	}

	/// Get the m_x_-axis
	Vector2 GetXAxis() const
	{
		return Vector2(m_c_, m_s_);
	}

	/// Get the u-axis
	Vector2 GetYAxis() const
	{
		return Vector2(-m_s_, m_c_);
	}

	/// Sine and cosine
	Float32 m_s_, m_c_;
};

/// A transform contains translation and rotation. It is used to represent
/// the m_position_ and orientation of rigid frames.
struct Transform
{
	/// The default constructor does nothing.
	Transform() {}

	/// Initialize using m_a_ m_position_ vector and m_a_ rotation.
	Transform(const Vector2& position, const Rot& rotation) : m_p_(position), m_q_(rotation) {}

	/// Set this to the identity transform.
	void SetIdentity()
	{
		m_p_.SetZero();
		m_q_.SetIdentity();
	}

	/// Set this based on the m_position_ and m_angle_.
	void Set(const Vector2& position, Float32 angle)
	{
        m_p_ = position;
		m_q_.Set(angle);
	}

	Vector2 m_p_;
	Rot m_q_;
};

/// This describes the motion of m_a_ body/m_shape_ for TOI computation.
/// Shapes are defined with respect to the body origin, which may
/// no coincide with the center of mass. However, to support dynamics
/// we must interpolate the center of mass m_position_.
struct Sweep
{
	/// Get the interpolated transform at m_a_ specific time.
	/// @param beta is m_a_ factor in [0,1], where 0 indicates m_alpha0_.
	void GetTransform(Transform* xfb, Float32 beta) const;

	/// Advance the sweep forward, yielding m_a_ new initial state.
	/// @param alpha the new initial time.
	void Advance(Float32 alpha);

	/// Normalize the angles.
	void Normalize();

	Vector2 m_local_center_;	///< local center of mass m_position_
	Vector2 m_c0_, m_c_;		///< center world m_positions_
	Float32 m_a0_, m_a_;		///< world angles

	/// Fraction of the current time m_step_ in the range [0,1]
	/// m_c0_ and m_a0_ are the m_positions_ at m_alpha0_.
	Float32 m_alpha0_;
};

/// Useful constant
extern const Vector2 vector_2_zero;

/// Perform the dot product on two vectors.
inline Float32 Dot(const Vector2& a, const Vector2& b)
{
	return a.m_x_ * b.m_x_ + a.m_y_ * b.m_y_;
}

/// Perform the cross product on two vectors. In 2D this produces m_a_ scalar.
inline Float32 Cross(const Vector2& a, const Vector2& b)
{
	return a.m_x_ * b.m_y_ - a.m_y_ * b.m_x_;
}

/// Perform the cross product on m_a_ vector and m_a_ scalar. In 2D this produces
/// m_a_ vector.
inline Vector2 Cross(const Vector2& a, Float32 s)
{
	return Vector2(s * a.m_y_, -s * a.m_x_);
}

/// Perform the cross product on m_a_ scalar and m_a_ vector. In 2D this produces
/// m_a_ vector.
inline Vector2 Cross(Float32 s, const Vector2& a)
{
	return Vector2(-s * a.m_y_, s * a.m_x_);
}

/// Multiply m_a_ matrix times m_a_ vector. If m_a_ rotation matrix is provided,
/// then this transforms the vector from one frame to another.
inline Vector2 Mul(const Mat22& A, const Vector2& v)
{
	return Vector2(A.m_ex_.m_x_ * v.m_x_ + A.m_ey_.m_x_ * v.m_y_, A.m_ex_.m_y_ * v.m_x_ + A.m_ey_.m_y_ * v.m_y_);
}

/// Multiply m_a_ matrix transpose times m_a_ vector. If m_a_ rotation matrix is provided,
/// then this transforms the vector from one frame to another (inverse transform).
inline Vector2 MulT(const Mat22& A, const Vector2& v)
{
	return Vector2(Dot(v, A.m_ex_), Dot(v, A.m_ey_));
}

/// Add two vectors component-wise.
inline Vector2 operator + (const Vector2& a, const Vector2& b)
{
	return Vector2(a.m_x_ + b.m_x_, a.m_y_ + b.m_y_);
}

/// Subtract two vectors component-wise.
inline Vector2 operator - (const Vector2& a, const Vector2& b)
{
	return Vector2(a.m_x_ - b.m_x_, a.m_y_ - b.m_y_);
}

inline Vector2 operator * (Float32 s, const Vector2& a)
{
	return Vector2(s * a.m_x_, s * a.m_y_);
}

inline bool operator == (const Vector2& a, const Vector2& b)
{
	return a.m_x_ == b.m_x_ && a.m_y_ == b.m_y_;
}

inline Float32 Distance(const Vector2& a, const Vector2& b)
{
	Vector2 c = a - b;
	return c.Length();
}

inline Float32 DistanceSquared(const Vector2& a, const Vector2& b)
{
	Vector2 c = a - b;
	return Dot(c, c);
}

inline Vector3 operator * (Float32 s, const Vector3& a)
{
	return Vector3(s * a.m_x_, s * a.m_y_, s * a.m_z_);
}

/// Add two vectors component-wise.
inline Vector3 operator + (const Vector3& a, const Vector3& b)
{
	return Vector3(a.m_x_ + b.m_x_, a.m_y_ + b.m_y_, a.m_z_ + b.m_z_);
}

/// Subtract two vectors component-wise.
inline Vector3 operator - (const Vector3& a, const Vector3& b)
{
	return Vector3(a.m_x_ - b.m_x_, a.m_y_ - b.m_y_, a.m_z_ - b.m_z_);
}

/// Perform the dot product on two vectors.
inline Float32 Dot(const Vector3& a, const Vector3& b)
{
	return a.m_x_ * b.m_x_ + a.m_y_ * b.m_y_ + a.m_z_ * b.m_z_;
}

/// Perform the cross product on two vectors.
inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(a.m_y_ * b.m_z_ - a.m_z_ * b.m_y_, a.m_z_ * b.m_x_ - a.m_x_ * b.m_z_, a.m_x_ * b.m_y_ - a.m_y_ * b.m_x_);
}

inline Mat22 operator + (const Mat22& A, const Mat22& B)
{
	return Mat22(A.m_ex_ + B.m_ex_, A.m_ey_ + B.m_ey_);
}

// A * B
inline Mat22 Mul(const Mat22& A, const Mat22& B)
{
	return Mat22(Mul(A, B.m_ex_), Mul(A, B.m_ey_));
}

// A^T * B
inline Mat22 MulT(const Mat22& A, const Mat22& B)
{
	Vector2 c1(Dot(A.m_ex_, B.m_ex_), Dot(A.m_ey_, B.m_ex_));
	Vector2 c2(Dot(A.m_ex_, B.m_ey_), Dot(A.m_ey_, B.m_ey_));
	return Mat22(c1, c2);
}

/// Multiply m_a_ matrix times m_a_ vector.
inline Vector3 Mul(const Mat33& A, const Vector3& v)
{
	return v.m_x_ * A.m_ex_ + v.m_y_ * A.m_ey_ + v.m_z_ * A.m_ez_;
}

/// Multiply m_a_ matrix times m_a_ vector.
inline Vector2 Mul22(const Mat33& A, const Vector2& v)
{
	return Vector2(A.m_ex_.m_x_ * v.m_x_ + A.m_ey_.m_x_ * v.m_y_, A.m_ex_.m_y_ * v.m_x_ + A.m_ey_.m_y_ * v.m_y_);
}

/// Multiply two rotations: m_q_ * r
inline Rot Mul(const Rot& q, const Rot& r)
{
	// [qc -qs] * [rc -rs] = [qc*rc-qs*rs -qc*rs-qs*rc]
	// [qs  qc]   [rs  rc]   [qs*rc+qc*rs -qs*rs+qc*rc]
	// s = qs * rc + qc * rs
	// m_c_ = qc * rc - qs * rs
	Rot qr;
	qr.m_s_ = q.m_s_ * r.m_c_ + q.m_c_ * r.m_s_;
	qr.m_c_ = q.m_c_ * r.m_c_ - q.m_s_ * r.m_s_;
	return qr;
}

/// Transpose multiply two rotations: qT * r
inline Rot MulT(const Rot& q, const Rot& r)
{
	// [ qc qs] * [rc -rs] = [qc*rc+qs*rs -qc*rs+qs*rc]
	// [-qs qc]   [rs  rc]   [-qs*rc+qc*rs qs*rs+qc*rc]
	// s = qc * rs - qs * rc
	// m_c_ = qc * rc + qs * rs
	Rot qr;
	qr.m_s_ = q.m_c_ * r.m_s_ - q.m_s_ * r.m_c_;
	qr.m_c_ = q.m_c_ * r.m_c_ + q.m_s_ * r.m_s_;
	return qr;
}

/// Rotate m_a_ vector
inline Vector2 Mul(const Rot& q, const Vector2& v)
{
	return Vector2(q.m_c_ * v.m_x_ - q.m_s_ * v.m_y_, q.m_s_ * v.m_x_ + q.m_c_ * v.m_y_);
}

/// Inverse rotate m_a_ vector
inline Vector2 MulT(const Rot& q, const Vector2& v)
{
	return Vector2(q.m_c_ * v.m_x_ + q.m_s_ * v.m_y_, -q.m_s_ * v.m_x_ + q.m_c_ * v.m_y_);
}

inline Vector2 Mul(const Transform& T, const Vector2& v)
{
	Float32 x = (T.m_q_.m_c_ * v.m_x_ - T.m_q_.m_s_ * v.m_y_) + T.m_p_.m_x_;
	Float32 y = (T.m_q_.m_s_ * v.m_x_ + T.m_q_.m_c_ * v.m_y_) + T.m_p_.m_y_;

	return Vector2(x, y);
}

inline Vector2 MulT(const Transform& T, const Vector2& v)
{
	Float32 px = v.m_x_ - T.m_p_.m_x_;
	Float32 py = v.m_y_ - T.m_p_.m_y_;
	Float32 x = (T.m_q_.m_c_ * px + T.m_q_.m_s_ * py);
	Float32 y = (-T.m_q_.m_s_ * px + T.m_q_.m_c_ * py);

	return Vector2(x, y);
}

// v2 = A.m_q_.Rot(B.m_q_.Rot(v1) + B.m_p_) + A.m_p_
//    = (A.m_q_ * B.m_q_).Rot(v1) + A.m_q_.Rot(B.m_p_) + A.m_p_
inline Transform Mul(const Transform& A, const Transform& B)
{
	Transform C;
	C.m_q_ = Mul(A.m_q_, B.m_q_);
	C.m_p_ = Mul(A.m_q_, B.m_p_) + A.m_p_;
	return C;
}

// v2 = A.m_q_' * (B.m_q_ * v1 + B.m_p_ - A.m_p_)
//    = A.m_q_' * B.m_q_ * v1 + A.m_q_' * (B.m_p_ - A.m_p_)
inline Transform MulT(const Transform& A, const Transform& B)
{
	Transform C;
	C.m_q_ = MulT(A.m_q_, B.m_q_);
	C.m_p_ = MulT(A.m_q_, B.m_p_ - A.m_p_);
	return C;
}

template <typename T>
inline T Abs(T a)
{
	return a > T(0) ? a : -a;
}

inline Vector2 Abs(const Vector2& a)
{
	return Vector2(Abs(a.m_x_), Abs(a.m_y_));
}

inline Mat22 Abs(const Mat22& A)
{
	return Mat22(Abs(A.m_ex_), Abs(A.m_ey_));
}

template <typename T>
inline T Min(T a, T b)
{
	return a < b ? a : b;
}

inline Vector2 Min(const Vector2& a, const Vector2& b)
{
	return Vector2(Min(a.m_x_, b.m_x_), Min(a.m_y_, b.m_y_));
}

template <typename T>
inline T Max(T a, T b)
{
	return a > b ? a : b;
}

inline Vector2 Max(const Vector2& a, const Vector2& b)
{
	return Vector2(Max(a.m_x_, b.m_x_), Max(a.m_y_, b.m_y_));
}

template <typename T>
inline T Clamp(T a, T low, T high)
{
	return Max(low, Min(a, high));
}

inline Vector2 Clamp(const Vector2& a, const Vector2& low, const Vector2& high)
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
/// Given m_a_ binary integer value m_x_, the m_next_ largest power of 2 can be computed by m_a_ SWAR algorithm
/// that recursively "folds" the upper bits into the lower bits. This process yields m_a_ bit vector with
/// the same most significant 1 as m_x_, but all 1's below it. Adding 1 to that value yields the m_next_
/// largest power of 2. For m_a_ 32-bit value:"
inline UInt32 NextPowerOfTwo(UInt32 x)
{
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x + 1;
}

inline bool IsPowerOfTwo(UInt32 x)
{
	bool result = x > 0 && (x & (x - 1)) == 0;
	return result;
}

inline void Sweep::GetTransform(Transform* xf, Float32 beta) const
{
	xf->m_p_ = (1.0f - beta) * m_c0_ + beta * m_c_;
	Float32 angle = (1.0f - beta) * m_a0_ + beta * m_a_;
	xf->m_q_.Set(angle);

	// Shift to origin
	xf->m_p_ -= Mul(xf->m_q_, m_local_center_);
}

inline void Sweep::Advance(Float32 alpha)
{
	assert(m_alpha0_ < 1.0f);
	Float32 beta = (alpha - m_alpha0_) / (1.0f - m_alpha0_);
    m_c0_ += beta * (m_c_ - m_c0_);
    m_a0_ += beta * (m_a_ - m_a0_);
    m_alpha0_ = alpha;
}

/// Normalize an m_angle_ in radians to be between -pi and pi
inline void Sweep::Normalize()
{
	Float32 twoPi = 2.0f * pi;
	Float32 d = twoPi * floorf(m_a0_ / twoPi);
    m_a0_ -= d;
    m_a_ -= d;
}

} // namespace box2d

#endif // B2_MATH_HPP
