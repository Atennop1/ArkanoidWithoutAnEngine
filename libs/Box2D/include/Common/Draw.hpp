/*
* Copyright (m_c_) 2011 Erin Catto http://box2d.org
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

#ifndef B2_DRAW_HPP
#define B2_DRAW_HPP

#include <Common/Math.hpp>

namespace box2d
{

/// Color for debug drawing. Each value has the range [0,1].
    struct Color
    {
        Color()
        {}

        Color(Float32 r, Float32 g, Float32 b, Float32 a = 1.0f) : m_r_(r), m_g_(g), m_b_(b), m_a_(a)
        {}

        void Set(Float32 ri, Float32 gi, Float32 bi, Float32 ai = 1.0f)
        {
            m_r_ = ri;
            m_g_ = gi;
            m_b_ = bi;
            m_a_ = ai;
        }

        Float32 m_r_, m_g_, m_b_, m_a_;
    };

/// Implement and register this class with m_a_ box2d::World to provide debug drawing of physics
/// entities in your game.
    class Draw
    {
    public:
        Draw();

        virtual ~Draw()
        {}

        enum
        {
            e_shapeBit = 0x0001,    ///< draw shapes
            e_jointBit = 0x0002,    ///< draw m_joint_ connections
            e_aabbBit = 0x0004,    ///< draw axis aligned bounding boxes
            e_pairBit = 0x0008,    ///< draw broad-phase pairs
            e_centerOfMassBit = 0x0010    ///< draw center of mass frame
        };

        /// Set the drawing flags.
        void SetFlags(UInt32 flags);

        /// Get the drawing flags.
        UInt32 GetFlags() const;

        /// Append flags to the current flags.
        void AppendFlags(UInt32 flags);

        /// Clear flags from the current flags.
        void ClearFlags(UInt32 flags);

        /// Draw m_a_ closed polygon provided in CCW order.
        virtual void DrawPolygon(const Vector2 *vertices, Int32 vertexCount, const Color &color) = 0;

        /// Draw m_a_ solid closed polygon provided in CCW order.
        virtual void DrawSolidPolygon(const Vector2 *vertices, Int32 vertexCount, const Color &color) = 0;

        /// Draw m_a_ circle.
        virtual void DrawCircle(const Vector2 &center, Float32 radius, const Color &color) = 0;

        /// Draw m_a_ solid circle.
        virtual void DrawSolidCircle(const Vector2 &center, Float32 radius, const Vector2 &axis, const Color &color) = 0;

        /// Draw m_a_ line segment.
        virtual void DrawSegment(const Vector2 &p1, const Vector2 &p2, const Color &color) = 0;

        /// Draw m_a_ transform. Choose your own m_length_ scale.
        /// @param xf m_a_ transform.
        virtual void DrawTransform(const Transform &xf) = 0;

    protected:
        UInt32 m_draw_flags_;
    };

} // namespace box2d

#endif // B2_DRAW_HPP
