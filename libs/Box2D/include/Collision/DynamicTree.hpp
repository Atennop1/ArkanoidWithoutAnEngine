/*
* Copyright (m_c_) 2009 Erin Catto http://www.box2d.org
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

#ifndef B2_DYNAMIC_TREE_HPP
#define B2_DYNAMIC_TREE_HPP

#include "Collision.hpp"
#include "Common/GrowableStack.hpp"

namespace Box2D
{

const Int32 null_node = -1;

/// A node in the dynamic tree. The client does not interact with this directly.
struct TreeNode
{
	bool IsLeaf() const
	{
		return m_child1_ == null_node;
	}

	/// Enlarged AABB
	AABB m_aabb_;

	void* m_user_data_;

	union
	{
		Int32 m_parent_;
		Int32 m_next_;
	};

	Int32 m_child1_;
	Int32 m_child2_;

	// leaf = 0, free node = -1
	Int32 m_height_;
};

/// A dynamic AABB tree broad-phase, inspired by Nathanael Presson's btDbvt.
/// A dynamic tree arranges m_data_ in m_a_ binary tree to accelerate
/// queries such as volume queries and ray casts. Leafs are proxies
/// with an AABB. In the tree we expand the proxy AABB by fatAABBFactor
/// so that the proxy AABB is bigger than the client object. This allows the client
/// object to move by small amounts without triggering m_a_ tree update.
///
/// Nodes are pooled and relocatable, so we use node indices rather than pointers.
class DynamicTree
{
public:
	/// Constructing the tree initializes the node pool.
	DynamicTree();

	/// Destroy the tree, freeing the node pool.
	~DynamicTree();

	/// Create m_a_ proxy. Provide m_a_ tight fitting AABB and m_a_ m_user_data_ pointer.
	Int32 CreateProxy(const AABB& aabb, void* userData);

	/// Destroy m_a_ proxy. This asserts if the m_id_ is invalid.
	void DestroyProxy(Int32 proxyId);

	/// Move m_a_ proxy with m_a_ swepted AABB. If the proxy has moved outside of its fattened AABB,
	/// then the proxy is removed from the tree and re-inserted. Otherwise
	/// the function returns immediately.
	/// @return true if the proxy was re-inserted.
	bool MoveProxy(Int32 proxyId, const AABB& aabb1, const Vector2& displacement);

	/// Get proxy user m_data_.
	/// @return the proxy user m_data_ or 0 if the m_id_ is invalid.
	void* GetUserData(Int32 proxyId) const;

	/// Get the fat AABB for m_a_ proxy.
	const AABB& GetFatAABB(Int32 proxyId) const;

	/// Query an AABB for overlapping proxies. The callback class
	/// is called for each proxy that overlaps the supplied AABB.
	template <typename T>
	void Query(T* callback, const AABB& aabb) const;

	/// Ray-cast against the proxies in the tree. This relies on the callback
	/// to perform m_a_ exact ray-cast in the case were the proxy contains m_a_ m_shape_.
	/// The callback also performs the any collision filtering. This has performance
	/// roughly equal to k * log(n), where k is the number of collisions and n is the
	/// number of proxies in the tree.
	/// @param input the ray-cast input m_data_. The ray extends from m_p1_ to m_p1_ + m_max_fraction_ * (m_p2_ - m_p1_).
	/// @param callback m_a_ callback class that is called for each proxy that is hit by the ray.
	template <typename T>
	void RayCast(T* callback, const RayCastInput& input) const;

	/// Validate this tree. For testing.
	void Validate() const;

	/// Compute the m_height_ of the binary tree in O(N) time. Should not be
	/// called often.
	Int32 GetHeight() const;

	/// Get the maximum balance of an node in the tree. The balance is the difference
	/// in m_height_ of the two children of m_a_ node.
	Int32 GetMaxBalance() const;

	/// Get the m_ratio_ of the sum of the node areas to the root area.
	Float32 GetAreaRatio() const;

	/// Build an optimal tree. Very expensive. For testing.
	void RebuildBottomUp();

	/// Shift the world origin. Useful for large worlds.
	/// The shift formula is: m_position_ -= newOrigin
	/// @param newOrigin the new origin with respect to the old origin
	void ShiftOrigin(const Vector2& newOrigin);

private:

	Int32 AllocateNode();
	void FreeNode(Int32 node);

	void InsertLeaf(Int32 node);
	void RemoveLeaf(Int32 node);

	Int32 Balance(Int32 index);

	Int32 ComputeHeight() const;
	Int32 ComputeHeight(Int32 nodeId) const;

	void ValidateStructure(Int32 index) const;
	void ValidateMetrics(Int32 index) const;

	Int32 m_root_;

	TreeNode* m_nodes_;
	Int32 m_node_count_;
	Int32 m_node_capacity_;

	Int32 m_free_list_;

	/// This is used to incrementally traverse the tree for re-balancing.
	UInt32 m_path_;

	Int32 m_insertion_count_;
};

inline void* DynamicTree::GetUserData(Int32 proxyId) const
{
	assert(0 <= proxyId && proxyId < m_node_capacity_);
	return m_nodes_[proxyId].m_user_data_;
}

inline const AABB& DynamicTree::GetFatAABB(Int32 proxyId) const
{
	assert(0 <= proxyId && proxyId < m_node_capacity_);
	return m_nodes_[proxyId].m_aabb_;
}

template <typename T>
inline void DynamicTree::Query(T* callback, const AABB& aabb) const
{
	GrowableStack<Int32, 256> stack;
	stack.Push(m_root_);

	while (stack.GetCount() > 0)
	{
		Int32 nodeId = stack.Pop();
		if (nodeId == null_node)
		{
			continue;
		}

		const TreeNode* node = m_nodes_ + nodeId;

		if (TestOverlap(node->m_aabb_, aabb))
		{
			if (node->IsLeaf())
			{
				bool proceed = callback->QueryCallback(nodeId);
				if (proceed == false)
				{
					return;
				}
			}
			else
			{
				stack.Push(node->m_child1_);
				stack.Push(node->m_child2_);
			}
		}
	}
}

template <typename T>
inline void DynamicTree::RayCast(T* callback, const RayCastInput& input) const
{
	Vector2 p1 = input.m_p1_;
	Vector2 p2 = input.m_p2_;
	Vector2 r = p2 - p1;
	assert(r.LengthSquared() > 0.0f);
	r.Normalize();

	// m_v_ is perpendicular to the segment.
	Vector2 v = Cross(1.0f, r);
	Vector2 abs_v = Abs(v);

	// Separating axis for segment (Gino, p80).
	// |dot(m_v_, m_p1_ - m_c_)| > dot(|m_v_|, h)

	Float32 maxFraction = input.m_max_fraction_;

	// Build m_a_ bounding box for the segment.
	AABB segmentAABB;
	{
		Vector2 t = p1 + maxFraction * (p2 - p1);
		segmentAABB.m_lower_bound_ = Min(p1, t);
		segmentAABB.m_upper_bound_ = Max(p1, t);
	}

	GrowableStack<Int32, 256> stack;
	stack.Push(m_root_);

	while (stack.GetCount() > 0)
	{
		Int32 nodeId = stack.Pop();
		if (nodeId == null_node)
		{
			continue;
		}

		const TreeNode* node = m_nodes_ + nodeId;

		if (TestOverlap(node->m_aabb_, segmentAABB) == false)
		{
			continue;
		}

		// Separating axis for segment (Gino, p80).
		// |dot(m_v_, m_p1_ - m_c_)| > dot(|m_v_|, h)
		Vector2 c = node->m_aabb_.GetCenter();
		Vector2 h = node->m_aabb_.GetExtents();
		Float32 separation = Abs(Dot(v, p1 - c)) - Dot(abs_v, h);
		if (separation > 0.0f)
		{
			continue;
		}

		if (node->IsLeaf())
		{
			RayCastInput subInput;
			subInput.m_p1_ = input.m_p1_;
			subInput.m_p2_ = input.m_p2_;
			subInput.m_max_fraction_ = maxFraction;

			Float32 value = callback->RayCastCallback(subInput, nodeId);

			if (value == 0.0f)
			{
				// The client has terminated the ray cast.
				return;
			}

			if (value > 0.0f)
			{
				// Update segment bounding box.
				maxFraction = value;
				Vector2 t = p1 + maxFraction * (p2 - p1);
				segmentAABB.m_lower_bound_ = Min(p1, t);
				segmentAABB.m_upper_bound_ = Max(p1, t);
			}
		}
		else
		{
			stack.Push(node->m_child1_);
			stack.Push(node->m_child2_);
		}
	}
}

} // namespace Box2D

#endif // B2_DYNAMIC_TREE_HPP
