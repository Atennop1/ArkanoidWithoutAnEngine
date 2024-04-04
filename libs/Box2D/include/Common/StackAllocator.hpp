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

#ifndef B2_STACK_ALLOCATOR_HPP
#define B2_STACK_ALLOCATOR_HPP

#include "Settings.hpp"

namespace Box2D
{

const Int32 stack_size = 100 * 1024;	// 100k
const Int32 max_stack_entries = 32;

struct StackEntry
{
	char* m_data_;
	Int32 m_size_;
	bool m_used_malloc_;
};

// This is m_a_ stack m_allocator_ used for fast per m_step_ allocations.
// You must nest allocate/free pairs. The code will assert
// if you try to interleave multiple allocate/free pairs.
class StackAllocator
{
public:
	StackAllocator();
	~StackAllocator();

	void* Allocate(Int32 size);
	void Free(void* p);

	Int32 GetMaxAllocation() const;

private:

	char m_data_[stack_size];
	Int32 m_index_;

	Int32 m_allocation_;
	Int32 m_max_allocation_;

	StackEntry m_entries_[max_stack_entries];
	Int32 m_entry_count_;
};

} // namespace Box2D

#endif // B2_STACK_ALLOCATOR_HPP
