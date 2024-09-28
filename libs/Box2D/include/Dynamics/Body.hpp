/*
* Copyright (m_c_) 2006-2011 Erin Catto http://www.box2d.org
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

#ifndef B2_BODY_HPP
#define B2_BODY_HPP

#include <Common/Math.hpp>
#include <Collision/Shapes/Shape.hpp>
#include <memory>

namespace box2d
{

class Fixture;
class Joint;
class Contact;
class Controller;
class World;
struct FixtureDef;
struct JointEdge;
struct ContactEdge;

/// The body m_type_.
/// static: zero mass, zero velocity, may be manually moved
/// kinematic: zero mass, non-zero velocity set by user, moved by solver
/// dynamic: positive mass, non-zero velocity determined by forces, moved by solver
enum BodyType
{
	staticBody = 0,
	kinematicBody,
	dynamicBody

	// TODO_ERIN
	//bulletBody,
};

/// A body definition holds all the m_data_ needed to construct m_a_ rigid body.
/// You can safely re-use body definitions. Shapes are added to m_a_ body after construction.
struct BodyDef
{
	/// This constructor sets the body definition default values.
	BodyDef()
	{
        m_user_data_ = NULL;
		m_position_.Set(0.0f, 0.0f);
        m_angle_ = 0.0f;
		m_linear_velocity_.Set(0.0f, 0.0f);
        m_angular_velocity_ = 0.0f;
        m_linear_damping_ = 0.0f;
        m_angular_damping_ = 0.0f;
        m_allow_sleep_ = true;
        m_awake_ = true;
        m_fixed_rotation_ = false;
        m_bullet_ = false;
        m_type_ = staticBody;
        m_active_ = true;
        m_gravity_scale_ = 1.0f;
	}

	/// The body m_type_: static, kinematic, or dynamic.
	/// Note: if m_a_ dynamic body would have zero mass, the mass is set to one.
	BodyType m_type_;

	/// The world m_position_ of the body. Avoid creating bodies at the origin
	/// since this can lead to many overlapping shapes.
	Vector2 m_position_;

	/// The world m_angle_ of the body in radians.
	Float32 m_angle_;

	/// The m_linear_ velocity of the body's origin in world co-ordinates.
	Vector2 m_linear_velocity_;

	/// The angular velocity of the body.
	Float32 m_angular_velocity_;

	/// Linear m_damping_ is use to reduce the m_linear_ velocity. The m_damping_ parameter
	/// can be larger than 1.0f but the m_damping_ effect becomes sensitive to the
	/// time m_step_ when the m_damping_ parameter is large.
	Float32 m_linear_damping_;

	/// Angular m_damping_ is use to reduce the angular velocity. The m_damping_ parameter
	/// can be larger than 1.0f but the m_damping_ effect becomes sensitive to the
	/// time m_step_ when the m_damping_ parameter is large.
	Float32 m_angular_damping_;

	/// Set this flag to false if this body should never fall asleep. Note that
	/// this increases CPU usage.
	bool m_allow_sleep_;

	/// Is this body initially awake or sleeping?
	bool m_awake_;

	/// Should this body be prevented from rotating? Useful for characters.
	bool m_fixed_rotation_;

	/// Is this m_a_ fast moving body that should be prevented from tunneling through
	/// m_other_ moving bodies? Note that all bodies are prevented from tunneling through
	/// kinematic and static bodies. This setting is only considered on dynamic bodies.
	/// @warning You should use this flag sparingly since it increases processing time.
	bool m_bullet_;

	/// Does this body start out m_active_?
	bool m_active_;

	/// Use this to store application specific body m_data_.
	void* m_user_data_;

	/// Scale the m_gravity_ applied to this body.
	Float32 m_gravity_scale_;
};

/// A rigid body. These are created via box2d::World::CreateBody.
class Body
{
public:
	/// Creates m_a_ m_fixture_ and attach it to this body. Use this function if you need
	/// to set some m_fixture_ parameters, like m_friction_. Otherwise you can create the
	/// m_fixture_ directly from m_a_ m_shape_.
	/// If the m_density_ is non-zero, this function automatically updates the mass of the body.
	/// Contacts are not created until the m_next_ time m_step_.
	/// @param def the m_fixture_ definition.
	/// @warning This function is locked during callbacks.
	Fixture* CreateFixture(const FixtureDef* def);

	/// Creates m_a_ m_fixture_ from m_a_ m_shape_ and attach it to this body.
	/// This is m_a_ convenience function. Use box2d::FixtureDef if you need to set parameters
	/// like m_friction_, m_restitution_, user m_data_, or filtering.
	/// If the m_density_ is non-zero, this function automatically updates the mass of the body.
	/// @param shape the m_shape_ to be cloned.
	/// @param density the m_shape_ m_density_ (set to zero for static bodies).
	/// @warning This function is locked during callbacks.
	Fixture* CreateFixture(const Shape* shape, Float32 density);

	/// Destroy m_a_ m_fixture_. This removes the m_fixture_ from the broad-phase and
	/// destroys all m_contacts_ associated with this m_fixture_. This will
	/// automatically adjust the mass of the body if the body is dynamic and the
	/// m_fixture_ has positive m_density_.
	/// All fixtures attached to m_a_ body are implicitly destroyed when the body is destroyed.
	/// @param fixture the m_fixture_ to be removed.
	/// @warning This function is locked during callbacks.
	void DestroyFixture(Fixture* fixture);

	/// Set the m_position_ of the body's origin and rotation.
	/// Manipulating m_a_ body's transform may cause non-physical behavior.
	/// Note: m_contacts_ are updated on the m_next_ call to box2d::World::Step.
	/// @param position the world m_position_ of the body's local origin.
	/// @param angle the world rotation in radians.
	void SetTransform(const Vector2& position, Float32 angle);

	/// Get the body transform for the body's origin.
	/// @return the world transform of the body's origin.
	const Transform& GetTransform() const;

	/// Get the world body origin m_position_.
	/// @return the world m_position_ of the body's origin.
	const Vector2& GetPosition() const;

	/// Get the m_angle_ in radians.
	/// @return the current world rotation m_angle_ in radians.
	Float32 GetAngle() const;

	/// Get the world m_position_ of the center of mass.
	const Vector2& GetWorldCenter() const;

	/// Get the local m_position_ of the center of mass.
	const Vector2& GetLocalCenter() const;

	/// Set the m_linear_ velocity of the center of mass.
	/// @param v the new m_linear_ velocity of the center of mass.
	void SetLinearVelocity(const Vector2& v);

	/// Get the m_linear_ velocity of the center of mass.
	/// @return the m_linear_ velocity of the center of mass.
	const Vector2& GetLinearVelocity() const;

	/// Set the angular velocity.
	/// @param omega the new angular velocity in radians/second.
	void SetAngularVelocity(Float32 omega);

	/// Get the angular velocity.
	/// @return the angular velocity in radians/second.
	Float32 GetAngularVelocity() const;

	/// Apply m_a_ force at m_a_ world point. If the force is not
	/// applied at the center of mass, it will generate m_a_ torque and
	/// affect the angular velocity. This wakes up the body.
	/// @param force the world force vector, usually in Newtons (N).
	/// @param point the world m_position_ of the point of application.
	/// @param wake also wake up the body
	void ApplyForce(const Vector2& force, const Vector2& point, bool wake);

	/// Apply m_a_ force to the center of mass. This wakes up the body.
	/// @param force the world force vector, usually in Newtons (N).
	/// @param wake also wake up the body
	void ApplyForceToCenter(const Vector2& force, bool wake);

	/// Apply m_a_ torque. This affects the angular velocity
	/// without affecting the m_linear_ velocity of the center of mass.
	/// This wakes up the body.
	/// @param torque about the z-axis (out of the screen), usually in N-m.
	/// @param wake also wake up the body
	void ApplyTorque(Float32 torque, bool wake);

	/// Apply an impulse at m_a_ point. This immediately modifies the velocity.
	/// It also modifies the angular velocity if the point of application
	/// is not at the center of mass. This wakes up the body.
	/// @param impulse the world impulse vector, usually in N-seconds or kg-m/s.
	/// @param point the world m_position_ of the point of application.
	/// @param wake also wake up the body
	void ApplyLinearImpulse(const Vector2& impulse, const Vector2& point, bool wake);

	/// Apply an angular impulse.
	/// @param impulse the angular impulse in units of kg*m*m/s
	/// @param wake also wake up the body
	void ApplyAngularImpulse(Float32 impulse, bool wake);

	/// Get the total mass of the body.
	/// @return the mass, usually in kilograms (kg).
	Float32 GetMass() const;

	/// Get the rotational inertia of the body about the local origin.
	/// @return the rotational inertia, usually in kg-m^2.
	Float32 GetInertia() const;

	/// Get the mass m_data_ of the body.
	/// @return m_a_ struct containing the mass, inertia and center of the body.
	void GetMassData(MassData* data) const;

	/// Set the mass properties to override the mass properties of the fixtures.
	/// Note that this changes the center of mass m_position_.
	/// Note that creating or destroying fixtures can also alter the mass.
	/// This function has no effect if the body isn'm_t_ dynamic.
	/// @param massData the mass properties.
	void SetMassData(const MassData* data);

	/// This resets the mass properties to the sum of the mass properties of the fixtures.
	/// This normally does not need to be called unless you called SetMassData to override
	/// the mass and you later want to reset the mass.
	void ResetMassData();

	/// Get the world coordinates of m_a_ point given the local coordinates.
	/// @param localPoint m_a_ point on the body measured relative the the body's origin.
	/// @return the same point expressed in world coordinates.
	Vector2 GetWorldPoint(const Vector2& localPoint) const;

	/// Get the world coordinates of m_a_ vector given the local coordinates.
	/// @param localVector m_a_ vector fixed in the body.
	/// @return the same vector expressed in world coordinates.
	Vector2 GetWorldVector(const Vector2& localVector) const;

	/// Gets m_a_ local point relative to the body's origin given m_a_ world point.
	/// @param a point in world coordinates.
	/// @return the corresponding local point relative to the body's origin.
	Vector2 GetLocalPoint(const Vector2& worldPoint) const;

	/// Gets m_a_ local vector given m_a_ world vector.
	/// @param a vector in world coordinates.
	/// @return the corresponding local vector.
	Vector2 GetLocalVector(const Vector2& worldVector) const;

	/// Get the world m_linear_ velocity of m_a_ world point attached to this body.
	/// @param a point in world coordinates.
	/// @return the world velocity of m_a_ point.
	Vector2 GetLinearVelocityFromWorldPoint(const Vector2& worldPoint) const;

	/// Get the world velocity of m_a_ local point.
	/// @param a point in local coordinates.
	/// @return the world velocity of m_a_ point.
	Vector2 GetLinearVelocityFromLocalPoint(const Vector2& localPoint) const;

	/// Get the m_linear_ m_damping_ of the body.
	Float32 GetLinearDamping() const;

	/// Set the m_linear_ m_damping_ of the body.
	void SetLinearDamping(Float32 linearDamping);

	/// Get the angular m_damping_ of the body.
	Float32 GetAngularDamping() const;

	/// Set the angular m_damping_ of the body.
	void SetAngularDamping(Float32 angularDamping);

	/// Get the m_gravity_ scale of the body.
	Float32 GetGravityScale() const;

	/// Set the m_gravity_ scale of the body.
	void SetGravityScale(Float32 scale);

	/// Set the m_type_ of this body. This may alter the mass and velocity.
	void SetType(BodyType type);

	/// Get the m_type_ of this body.
	BodyType GetType() const;

	/// Should this body be treated like m_a_ m_bullet_ for continuous collision detection?
	void SetBullet(bool flag);

	/// Is this body treated like m_a_ m_bullet_ for continuous collision detection?
	bool IsBullet() const;

	/// You can disable sleeping on this body. If you disable sleeping, the
	/// body will be woken.
	void SetSleepingAllowed(bool flag);

	/// Is this body allowed to sleep
	bool IsSleepingAllowed() const;

	/// Set the sleep state of the body. A sleeping body has very
	/// low CPU cost.
	/// @param flag set to true to wake the body, false to put it to sleep.
	void SetAwake(bool flag);

	/// Get the sleeping state of this body.
	/// @return true if the body is awake.
	bool IsAwake() const;

	/// Set the m_active_ state of the body. An inactive body is not
	/// simulated and cannot be collided with or woken up.
	/// If you pass m_a_ flag of true, all fixtures will be added to the
	/// broad-phase.
	/// If you pass m_a_ flag of false, all fixtures will be removed from
	/// the broad-phase and all m_contacts_ will be destroyed.
	/// Fixtures and joints are otherwise unaffected. You may continue
	/// to create/destroy fixtures and joints on inactive bodies.
	/// Fixtures on an inactive body are implicitly inactive and will
	/// not participate in collisions, ray-casts, or queries.
	/// Joints connected to an inactive body are implicitly inactive.
	/// An inactive body is still owned by m_a_ box2d::World object and remains
	/// in the body list.
	void SetActive(bool flag);

	/// Get the m_active_ state of the body.
	bool IsActive() const;

	/// Set this body to have fixed rotation. This causes the mass
	/// to be reset.
	void SetFixedRotation(bool flag);

	/// Does this body have fixed rotation?
	bool IsFixedRotation() const;

	/// Get the list of all fixtures attached to this body.
	Fixture* GetFixtureList();
	const Fixture* GetFixtureList() const;

	/// Get the list of all joints attached to this body.
	JointEdge* GetJointList();
	const JointEdge* GetJointList() const;

	/// Get the list of all m_contacts_ attached to this body.
	/// @warning this list changes during the time m_step_ and you may
	/// miss some collisions if you don'm_t_ use box2d::ContactListener.
	ContactEdge* GetContactList();
	const ContactEdge* GetContactList() const;

	/// Get the m_next_ body in the world's body list.
	Body* GetNext();
	const Body* GetNext() const;

	/// Get the user m_data_ pointer that was provided in the body definition.
	void* GetUserData() const;

	/// Set the user m_data_. Use this to store your application specific m_data_.
	void SetUserData(void* data);

	/// Get the m_parent_ world of this body.
	World* GetWorld();
	const World* GetWorld() const;

	/// Dump this body to m_a_ log file
	void Dump();

private:

	friend class World;
	friend class Island;
	friend class ContactManager;
	friend class ContactSolver;
	friend class Contact;
	
	friend class DistanceJoint;
	friend class FrictionJoint;
	friend class GearJoint;
	friend class MotorJoint;
	friend class MouseJoint;
	friend class PrismaticJoint;
	friend class PulleyJoint;
	friend class RevoluteJoint;
	friend class RopeJoint;
	friend class WeldJoint;
	friend class WheelJoint;

	// m_flags_
	enum
	{
		e_islandFlag		= 0x0001,
		e_awakeFlag			= 0x0002,
		e_autoSleepFlag		= 0x0004,
		e_bulletFlag		= 0x0008,
		e_fixedRotationFlag	= 0x0010,
		e_activeFlag		= 0x0020,
		e_toiFlag			= 0x0040
	};

	Body(const BodyDef* bd, World* world);
	~Body();

	void SynchronizeFixtures();
	void SynchronizeTransform();

	// This is used to prevent connected bodies from colliding.
	// It may lie, depending on the m_collide_connected_ flag.
	bool ShouldCollide(const Body* other) const;

	void Advance(Float32 t);

	BodyType m_type_;

	UInt16 m_flags_;

	Int32 m_island_index_;

	Transform m_xf_;		// the body origin transform
	Sweep m_sweep_;		// the swept motion for CCD

	Vector2 m_linear_velocity_;
	Float32 m_angular_velocity_;

	Vector2 m_force_;
	Float32 m_torque_;

	World* m_world_;
	Body* m_prev_;
	Body* m_next_;

	Fixture* m_fixture_list_;
	Int32 m_fixture_count_;

	JointEdge* m_joint_list_;
	ContactEdge* m_contact_list_;

	Float32 m_mass_, m_inv_mass_;

	// Rotational inertia about the center of mass.
	Float32 m_i_, m_inv_i_;

	Float32 m_linear_damping_;
	Float32 m_angular_damping_;
	Float32 m_gravity_scale_;

	Float32 m_sleep_time_;

	void* m_user_data_;
};

inline BodyType Body::GetType() const
{
	return m_type_;
}

inline const Transform& Body::GetTransform() const
{
	return m_xf_;
}

inline const Vector2& Body::GetPosition() const
{
	return m_xf_.m_p_;
}

inline Float32 Body::GetAngle() const
{
	return m_sweep_.m_a_;
}

inline const Vector2& Body::GetWorldCenter() const
{
	return m_sweep_.m_c_;
}

inline const Vector2& Body::GetLocalCenter() const
{
	return m_sweep_.m_local_center_;
}

inline void Body::SetLinearVelocity(const Vector2& v)
{
	if (m_type_ == staticBody)
	{
		return;
	}

	if (Dot(v,v) > 0.0f)
	{
		SetAwake(true);
	}

    m_linear_velocity_ = v;
}

inline const Vector2& Body::GetLinearVelocity() const
{
	return m_linear_velocity_;
}

inline void Body::SetAngularVelocity(Float32 w)
{
	if (m_type_ == staticBody)
	{
		return;
	}

	if (w * w > 0.0f)
	{
		SetAwake(true);
	}

    m_angular_velocity_ = w;
}

inline Float32 Body::GetAngularVelocity() const
{
	return m_angular_velocity_;
}

inline Float32 Body::GetMass() const
{
	return m_mass_;
}

inline Float32 Body::GetInertia() const
{
	return m_i_ + m_mass_ * Dot(m_sweep_.m_local_center_, m_sweep_.m_local_center_);
}

inline void Body::GetMassData(MassData* data) const
{
	data->mass = m_mass_;
	data->I = m_i_ + m_mass_ * Dot(m_sweep_.m_local_center_, m_sweep_.m_local_center_);
	data->center = m_sweep_.m_local_center_;
}

inline Vector2 Body::GetWorldPoint(const Vector2& localPoint) const
{
	return Mul(m_xf_, localPoint);
}

inline Vector2 Body::GetWorldVector(const Vector2& localVector) const
{
	return Mul(m_xf_.m_q_, localVector);
}

inline Vector2 Body::GetLocalPoint(const Vector2& worldPoint) const
{
	return MulT(m_xf_, worldPoint);
}

inline Vector2 Body::GetLocalVector(const Vector2& worldVector) const
{
	return MulT(m_xf_.m_q_, worldVector);
}

inline Vector2 Body::GetLinearVelocityFromWorldPoint(const Vector2& worldPoint) const
{
	return m_linear_velocity_ + Cross(m_angular_velocity_, worldPoint - m_sweep_.m_c_);
}

inline Vector2 Body::GetLinearVelocityFromLocalPoint(const Vector2& localPoint) const
{
	return GetLinearVelocityFromWorldPoint(GetWorldPoint(localPoint));
}

inline Float32 Body::GetLinearDamping() const
{
	return m_linear_damping_;
}

inline void Body::SetLinearDamping(Float32 linearDamping)
{
    m_linear_damping_ = linearDamping;
}

inline Float32 Body::GetAngularDamping() const
{
	return m_angular_damping_;
}

inline void Body::SetAngularDamping(Float32 angularDamping)
{
    m_angular_damping_ = angularDamping;
}

inline Float32 Body::GetGravityScale() const
{
	return m_gravity_scale_;
}

inline void Body::SetGravityScale(Float32 scale)
{
    m_gravity_scale_ = scale;
}

inline void Body::SetBullet(bool flag)
{
	if (flag)
	{
        m_flags_ |= e_bulletFlag;
	}
	else
	{
        m_flags_ &= ~e_bulletFlag;
	}
}

inline bool Body::IsBullet() const
{
	return (m_flags_ & e_bulletFlag) == e_bulletFlag;
}

inline void Body::SetAwake(bool flag)
{
	if (flag)
	{
		if ((m_flags_ & e_awakeFlag) == 0)
		{
            m_flags_ |= e_awakeFlag;
            m_sleep_time_ = 0.0f;
		}
	}
	else
	{
        m_flags_ &= ~e_awakeFlag;
        m_sleep_time_ = 0.0f;
		m_linear_velocity_.SetZero();
        m_angular_velocity_ = 0.0f;
		m_force_.SetZero();
        m_torque_ = 0.0f;
	}
}

inline bool Body::IsAwake() const
{
	return (m_flags_ & e_awakeFlag) == e_awakeFlag;
}

inline bool Body::IsActive() const
{
	return (m_flags_ & e_activeFlag) == e_activeFlag;
}

inline bool Body::IsFixedRotation() const
{
	return (m_flags_ & e_fixedRotationFlag) == e_fixedRotationFlag;
}

inline void Body::SetSleepingAllowed(bool flag)
{
	if (flag)
	{
        m_flags_ |= e_autoSleepFlag;
	}
	else
	{
        m_flags_ &= ~e_autoSleepFlag;
		SetAwake(true);
	}
}

inline bool Body::IsSleepingAllowed() const
{
	return (m_flags_ & e_autoSleepFlag) == e_autoSleepFlag;
}

inline Fixture* Body::GetFixtureList()
{
	return m_fixture_list_;
}

inline const Fixture* Body::GetFixtureList() const
{
	return m_fixture_list_;
}

inline JointEdge* Body::GetJointList()
{
	return m_joint_list_;
}

inline const JointEdge* Body::GetJointList() const
{
	return m_joint_list_;
}

inline ContactEdge* Body::GetContactList()
{
	return m_contact_list_;
}

inline const ContactEdge* Body::GetContactList() const
{
	return m_contact_list_;
}

inline Body* Body::GetNext()
{
	return m_next_;
}

inline const Body* Body::GetNext() const
{
	return m_next_;
}

inline void Body::SetUserData(void* data)
{
    m_user_data_ = data;
}

inline void* Body::GetUserData() const
{
	return m_user_data_;
}

inline void Body::ApplyForce(const Vector2& force, const Vector2& point, bool wake)
{
	if (m_type_ != dynamicBody)
	{
		return;
	}

	if (wake && (m_flags_ & e_awakeFlag) == 0)
	{
		SetAwake(true);
	}

	// Don'm_t_ accumulate m_a_ force if the body is sleeping.
	if (m_flags_ & e_awakeFlag)
	{
        m_force_ += force;
        m_torque_ += Cross(point - m_sweep_.m_c_, force);
	}
}

inline void Body::ApplyForceToCenter(const Vector2& force, bool wake)
{
	if (m_type_ != dynamicBody)
	{
		return;
	}

	if (wake && (m_flags_ & e_awakeFlag) == 0)
	{
		SetAwake(true);
	}

	// Don'm_t_ accumulate m_a_ force if the body is sleeping
	if (m_flags_ & e_awakeFlag)
	{
        m_force_ += force;
	}
}

inline void Body::ApplyTorque(Float32 torque, bool wake)
{
	if (m_type_ != dynamicBody)
	{
		return;
	}

	if (wake && (m_flags_ & e_awakeFlag) == 0)
	{
		SetAwake(true);
	}

	// Don'm_t_ accumulate m_a_ force if the body is sleeping
	if (m_flags_ & e_awakeFlag)
	{
        m_torque_ += torque;
	}
}

inline void Body::ApplyLinearImpulse(const Vector2& impulse, const Vector2& point, bool wake)
{
	if (m_type_ != dynamicBody)
	{
		return;
	}

	if (wake && (m_flags_ & e_awakeFlag) == 0)
	{
		SetAwake(true);
	}

	// Don'm_t_ accumulate velocity if the body is sleeping
	if (m_flags_ & e_awakeFlag)
	{
        m_linear_velocity_ += m_inv_mass_ * impulse;
        m_angular_velocity_ += m_inv_i_ * Cross(point - m_sweep_.m_c_, impulse);
	}
}

inline void Body::ApplyAngularImpulse(Float32 impulse, bool wake)
{
	if (m_type_ != dynamicBody)
	{
		return;
	}

	if (wake && (m_flags_ & e_awakeFlag) == 0)
	{
		SetAwake(true);
	}

	// Don'm_t_ accumulate velocity if the body is sleeping
	if (m_flags_ & e_awakeFlag)
	{
        m_angular_velocity_ += m_inv_i_ * impulse;
	}
}

inline void Body::SynchronizeTransform()
{
	m_xf_.m_q_.Set(m_sweep_.m_a_);
    m_xf_.m_p_ = m_sweep_.m_c_ - Mul(m_xf_.m_q_, m_sweep_.m_local_center_);
}

inline void Body::Advance(Float32 alpha)
{
	// Advance to the new safe time. This doesn'm_t_ sync the broad-phase.
	m_sweep_.Advance(alpha);
    m_sweep_.m_c_ = m_sweep_.m_c0_;
    m_sweep_.m_a_ = m_sweep_.m_a0_;
	m_xf_.m_q_.Set(m_sweep_.m_a_);
    m_xf_.m_p_ = m_sweep_.m_c_ - Mul(m_xf_.m_q_, m_sweep_.m_local_center_);
}

inline World* Body::GetWorld()
{
	return m_world_;
}

inline const World* Body::GetWorld() const
{
	return m_world_;
}

} // namespace box2d

#endif // B2_BODY_HPP
