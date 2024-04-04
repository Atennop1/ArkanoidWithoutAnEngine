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

#ifndef B2_BLOCK_ALLOCATOR_HPP
#define B2_BLOCK_ALLOCATOR_HPP

#include "Settings.hpp"

namespace Box2D
{

const Int32 chunk_size = 16 * 1024;
const Int32 max_block_size = 640;
const Int32 block_sizes = 14;
const Int32 chunk_array_increment = 128;

struct Block;
struct Chunk;

/// This is m_a_ small object m_allocator_ used for allocating small
/// objects that persist for more than one time m_step_.
/// See: http://www.codeproject.com/useritems/Small_Block_Allocator.asp
class BlockAllocator
{
public:
	BlockAllocator();
	~BlockAllocator();

	/// Allocate memory. This will use Box2D::Alloc if the m_size_ is larger than maxBlockSize.
	void* Allocate(Int32 size);

	/// Free memory. This will use Box2D::Free if the m_size_ is larger than maxBlockSize.
	void Free(void* p, Int32 size);

	void Clear();

private:

	Chunk* m_chunks_;
	Int32 m_chunk_count_;
	Int32 m_chunk_space_;

	Block* m_free_lists_[block_sizes];

	static Int32 m_s_block_sizes_[block_sizes];
	static UInt8 m_s_block_size_lookup_[max_block_size + 1];
	static bool m_s_block_size_lookup_initialized_;
};

} // namespace Box2D

#endif // B2_BLOCK_ALLOCATOR_HPP
