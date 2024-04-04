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

#ifndef BOX2D_HPP
#define BOX2D_HPP

/**
\mainpage Box2D API Documentation

\section intro_sec Getting Started

For documentation please see http://box2d.org/documentation.html

For discussion please visit http://box2d.org/forum
*/

// These include files constitute the main Box2D API

#include <Common/Settings.hpp>
#include <Common/Draw.hpp>
#include <Common/Timer.hpp>

#include <Collision/Shapes/CircleShape.hpp>
#include <Collision/Shapes/EdgeShape.hpp>
#include <Collision/Shapes/ChainShape.hpp>
#include <Collision/Shapes/PolygonShape.hpp>

#include <Collision/BroadPhase.hpp>
#include <Collision/Distance.hpp>
#include <Collision/DynamicTree.hpp>
#include <Collision/TimeOfImpact.hpp>

#include <Dynamics/Body.hpp>
#include <Dynamics/Fixture.hpp>
#include <Dynamics/WorldCallbacks.hpp>
#include <Dynamics/TimeStep.hpp>
#include <Dynamics/World.hpp>

#include <Dynamics/Contacts/Contact.hpp>

#include <Dynamics/Joints/DistanceJoint.hpp>
#include <Dynamics/Joints/FrictionJoint.hpp>
#include <Dynamics/Joints/GearJoint.hpp>
#include <Dynamics/Joints/MotorJoint.hpp>
#include <Dynamics/Joints/MouseJoint.hpp>
#include <Dynamics/Joints/PrismaticJoint.hpp>
#include <Dynamics/Joints/PulleyJoint.hpp>
#include <Dynamics/Joints/RevoluteJoint.hpp>
#include <Dynamics/Joints/RopeJoint.hpp>
#include <Dynamics/Joints/WeldJoint.hpp>
#include <Dynamics/Joints/WheelJoint.hpp>

#endif // BOX2D_HPP
