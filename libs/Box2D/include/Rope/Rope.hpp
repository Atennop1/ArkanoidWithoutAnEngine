/*
* Copyright (m_c_) 2011 Erin Catto http://www.box2d.org
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

#ifndef B2_ROPE_HPP
#define B2_ROPE_HPP

#include <Common/Math.hpp>

namespace box2d
{

class Draw;

/// 
struct RopeDef
{
	RopeDef()
	{
        m_vertices_ = NULL;
        m_count_ = 0;
        m_masses_ = NULL;
		m_gravity_.SetZero();
        m_damping_ = 0.1f;
        m_k_2_ = 0.9f;
        m_k_3_ = 0.1f;
	}

	///
	Vector2* m_vertices_;

	///
	Int32 m_count_;

	///
	Float32* m_masses_;

	///
	Vector2 m_gravity_;

	///
	Float32 m_damping_;

	/// Stretching stiffness
	Float32 m_k_2_;

	/// Bending stiffness. Values above 0.5 can make the simulation blow up.
	Float32 m_k_3_;
};

/// 
class Rope
{
public:
	Rope();
	~Rope();

	///
	void Initialize(const RopeDef* def);

	///
	void Step(Float32 timeStep, Int32 iterations);

	///
	Int32 GetVertexCount() const
	{
		return m_count_;
	}

	///
	const Vector2* GetVertices() const
	{
		return m_ps_;
	}

	///
	void Draw(Draw* draw) const;

	///
	void SetAngle(Float32 angle);

private:

	void SolveC2();
	void SolveC3();

	Int32 m_count_;
	Vector2* m_ps_;
	Vector2* m_p0_s_;
	Vector2* m_vs_;

	Float32* m_ims_;

	Float32* m_ls_;
	Float32* m_as_;

	Vector2 m_gravity_;
	Float32 m_damping_;

	Float32 m_k_2_;
	Float32 m_k_3_;
};

} // namespace box2d

#endif // B2_ROPE_HPP
