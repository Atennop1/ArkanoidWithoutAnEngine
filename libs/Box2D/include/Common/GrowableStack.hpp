/*
* Copyright (m_c_) 2010 Erin Catto http://www.box2d.org
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

#ifndef B2_GROWABLE_STACK_HPP
#define B2_GROWABLE_STACK_HPP
#include "Settings.hpp"
#include <cstring>

namespace Box2D
{

/// This is m_a_ growable LIFO stack with an initial capacity of N.
/// If the stack m_size_ exceeds the initial capacity, the heap is used
/// to increase the m_size_ of the stack.
template <typename T, Int32 N>
class GrowableStack
{
public:
	GrowableStack()
	{
        m_stack_ = m_array_;
        m_count_ = 0;
        m_capacity_ = N;
	}

	~GrowableStack()
	{
		if (m_stack_ != m_array_)
		{
			Free(m_stack_);
            m_stack_ = NULL;
		}
	}

	void Push(const T& element)
	{
		if (m_count_ == m_capacity_)
		{
			T* old = m_stack_;
            m_capacity_ *= 2;
            m_stack_ = (T*)Alloc(m_capacity_ * sizeof(T));
			std::memcpy(m_stack_, old, m_count_ * sizeof(T));
			if (old != m_array_)
			{
				Free(old);
			}
		}

        m_stack_[m_count_] = element;
		++m_count_;
	}

	T Pop()
	{
		assert(m_count_ > 0);
		--m_count_;
		return m_stack_[m_count_];
	}

	Int32 GetCount()
	{
		return m_count_;
	}

private:
	T* m_stack_;
	T m_array_[N];
	Int32 m_count_;
	Int32 m_capacity_;
};

} // namespace Box2D

#endif // B2_GROWABLE_STACK_HPP
