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

#ifndef B2_BROAD_PHASE_HPP
#define B2_BROAD_PHASE_HPP

#include "Common/Settings.hpp"
#include "Collision.hpp"
#include "DynamicTree.hpp"
#include <algorithm>

namespace Box2D
{

struct Pair
{
    explicit Pair(Int32 proxy_id_a);

    Int32 m_proxy_id_a_;
	Int32 m_proxy_id_b_;
};

/// The broad-phase is used for computing pairs and performing volume queries and ray casts.
/// This broad-phase does not persist pairs. Instead, this reports potentially new pairs.
/// It is up to the client to consume the new pairs and to track subsequent overlap.
class BroadPhase
{
public:

	enum
	{
		e_nullProxy = -1
	};

	BroadPhase();
	~BroadPhase();

	/// Create m_a_ proxy with an initial AABB. Pairs are not reported until
	/// UpdatePairs is called.
	Int32 CreateProxy(const AABB& aabb, void* userData);

	/// Destroy m_a_ proxy. It is up to the client to remove any pairs.
	void DestroyProxy(Int32 proxyId);

	/// Call MoveProxy as many times as you like, then when you are done
	/// call UpdatePairs to finalized the proxy pairs (for your time m_step_).
	void MoveProxy(Int32 proxyId, const AABB& aabb, const Vector2& displacement);

	/// Call to trigger m_a_ re-processing of it's pairs on the m_next_ call to UpdatePairs.
	void TouchProxy(Int32 proxyId);

	/// Get the fat AABB for m_a_ proxy.
	const AABB& GetFatAABB(Int32 proxyId) const;

	/// Get user m_data_ from m_a_ proxy. Returns NULL if the m_id_ is invalid.
	void* GetUserData(Int32 proxyId) const;

	/// Test overlap of fat AABBs.
	bool TestOverlap(Int32 proxyIdA, Int32 proxyIdB) const;

	/// Get the number of proxies.
	Int32 GetProxyCount() const;

	/// Update the pairs. This results in pair callbacks. This can only add pairs.
	template <typename T>
	void UpdatePairs(T* callback);

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

	/// Get the m_height_ of the embedded tree.
	Int32 GetTreeHeight() const;

	/// Get the balance of the embedded tree.
	Int32 GetTreeBalance() const;

	/// Get the quality m_metric_ of the embedded tree.
	Float32 GetTreeQuality() const;

	/// Shift the world origin. Useful for large worlds.
	/// The shift formula is: m_position_ -= newOrigin
	/// @param newOrigin the new origin with respect to the old origin
	void ShiftOrigin(const Vector2& newOrigin);

private:

	friend class DynamicTree;

	void BufferMove(Int32 proxyId);
	void UnBufferMove(Int32 proxyId);

	bool QueryCallback(Int32 proxyId);

	DynamicTree m_tree_;

	Int32 m_proxy_count_;

	Int32* m_move_buffer_;
	Int32 m_move_capacity_;
	Int32 m_move_count_;

	Pair* m_pair_buffer_;
	Int32 m_pair_capacity_;
	Int32 m_pair_count_;

	Int32 m_query_proxy_id_;
};

/// This is used to sort pairs.
inline bool PairLessThan(const Pair& pair1, const Pair& pair2)
{
	if (pair1.m_proxy_id_a_ < pair2.m_proxy_id_a_)
	{
		return true;
	}

	if (pair1.m_proxy_id_a_ == pair2.m_proxy_id_a_)
	{
		return pair1.m_proxy_id_b_ < pair2.m_proxy_id_b_;
	}

	return false;
}

inline void* BroadPhase::GetUserData(Int32 proxyId) const
{
	return m_tree_.GetUserData(proxyId);
}

inline bool BroadPhase::TestOverlap(Int32 proxyIdA, Int32 proxyIdB) const
{
	const AABB& aabbA = m_tree_.GetFatAABB(proxyIdA);
	const AABB& aabbB = m_tree_.GetFatAABB(proxyIdB);
	return Box2D::TestOverlap(aabbA, aabbB);
}

inline const AABB& BroadPhase::GetFatAABB(Int32 proxyId) const
{
	return m_tree_.GetFatAABB(proxyId);
}

inline Int32 BroadPhase::GetProxyCount() const
{
	return m_proxy_count_;
}

inline Int32 BroadPhase::GetTreeHeight() const
{
	return m_tree_.GetHeight();
}

inline Int32 BroadPhase::GetTreeBalance() const
{
	return m_tree_.GetMaxBalance();
}

inline Float32 BroadPhase::GetTreeQuality() const
{
	return m_tree_.GetAreaRatio();
}

template <typename T>
void BroadPhase::UpdatePairs(T* callback)
{
	// Reset pair buffer
	m_pair_count_ = 0;

	// Perform tree queries for all moving proxies.
	for (Int32 i = 0; i < m_move_count_; ++i)
	{
        m_query_proxy_id_ = m_move_buffer_[i];
		if (m_query_proxy_id_ == e_nullProxy)
		{
			continue;
		}

		// We have to query the tree with the fat AABB so that
		// we don'm_t_ fail to create m_a_ pair that may touch later.
		const AABB& fatAABB = m_tree_.GetFatAABB(m_query_proxy_id_);

		// Query tree, create pairs and add them pair buffer.
		m_tree_.Query(this, fatAABB);
	}

	// Reset move buffer
	m_move_count_ = 0;

	// Sort the pair buffer to expose duplicates.
	std::sort(m_pair_buffer_, m_pair_buffer_ + m_pair_count_, PairLessThan);

	// Send the pairs back to the client.
	Int32 i = 0;
	while (i < m_pair_count_)
	{
		Pair* primaryPair = m_pair_buffer_ + i;
		void* userDataA = m_tree_.GetUserData(primaryPair->m_proxy_id_a_);
		void* userDataB = m_tree_.GetUserData(primaryPair->m_proxy_id_b_);

		callback->AddPair(userDataA, userDataB);
		++i;

		// Skip any duplicate pairs.
		while (i < m_pair_count_)
		{
			Pair* pair = m_pair_buffer_ + i;
			if (pair->m_proxy_id_a_ != primaryPair->m_proxy_id_a_ || pair->m_proxy_id_b_ != primaryPair->m_proxy_id_b_)
			{
				break;
			}
			++i;
		}
	}

	// Try to keep the tree balanced.
	//m_tree_.Rebalance(4);
}

template <typename T>
inline void BroadPhase::Query(T* callback, const AABB& aabb) const
{
	m_tree_.Query(callback, aabb);
}

template <typename T>
inline void BroadPhase::RayCast(T* callback, const RayCastInput& input) const
{
	m_tree_.RayCast(callback, input);
}

inline void BroadPhase::ShiftOrigin(const Vector2& newOrigin)
{
	m_tree_.ShiftOrigin(newOrigin);
}

} // namespace Box2D

#endif // B2_BROAD_PHASE_HPP
