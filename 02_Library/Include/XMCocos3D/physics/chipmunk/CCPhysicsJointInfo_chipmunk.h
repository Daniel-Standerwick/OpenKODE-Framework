/* --------------------------------------------------------------------------
 *
 *      File            CCPhysicsJointInfo_chipmunk.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com
 * 
 * --------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2014 XMSoft.
 *      Copyright (c) 2013      cocos2d-x.org
 *
 *         http://www.cocos2d-x.org      
 *
 * --------------------------------------------------------------------------
 * 
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or ( at your option ) any later version.
 * 
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 * 
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 *
 * -------------------------------------------------------------------------- */

#ifndef __CCPhysicsJointInfo_chipmunk_h__
#define __CCPhysicsJointInfo_chipmunk_h__

#include "../CCPhysicsSetting.h"
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include "../../platform/CCPlatformMacros.h"
#include "XMChipmunk/chipmunk.h"
#include <vector>
#include <map>
NS_CC_BEGIN

class PhysicsJoint;

class PhysicsJointInfo
{
	public :

		KDvoid							add ( cpConstraint* pShape );
		KDvoid							remove ( cpConstraint* pShape );
		KDvoid							removeAll ( KDvoid );
    
		PhysicsJoint*					getJoint ( KDvoid ) const { return m_pJoint; }
		std::vector<cpConstraint*>&		getJoints ( KDvoid ) { return m_aJoints; }

		static std::map<cpConstraint*, PhysicsJointInfo*>&	getMap ( KDvoid ) { return m_aMap; }
    
	private :

		 PhysicsJointInfo ( PhysicsJoint* pJoint );
		~PhysicsJointInfo ( KDvoid );
    
	private :

		std::vector<cpConstraint*>							m_aJoints;
		PhysicsJoint*										m_pJoint;
		static std::map<cpConstraint*, PhysicsJointInfo*>	m_aMap;
    
		friend class PhysicsJoint;
};

NS_CC_END

#endif	// CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK
#endif	// __CCPhysicsJointInfo_chipmunk_h__
