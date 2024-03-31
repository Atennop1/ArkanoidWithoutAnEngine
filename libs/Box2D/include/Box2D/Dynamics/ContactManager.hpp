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

#ifndef B2_CONTACT_MANAGER_HPP
#define B2_CONTACT_MANAGER_HPP

#include <Box2D/Collision/BroadPhase.hpp>

namespace Box2D
{

class Contact;
class ContactFilter;
class ContactListener;
class BlockAllocator;

// Delegate of Box2D::World.
class ContactManager
{
public:
	ContactManager();

	// Broad-phase callback.
	void AddPair(void* proxyUserDataA, void* proxyUserDataB);

	void FindNewContacts();

	void Destroy(Contact* c);

	void Collide();
            
	BroadPhase m_broadPhase;
	Contact* m_contactList;
	int32 m_contactCount;
	ContactFilter* m_contactFilter;
	ContactListener* m_contactListener;
	BlockAllocator* m_allocator;
};

} // namespace Box2D

#endif // B2_CONTACT_MANAGER_HPP
