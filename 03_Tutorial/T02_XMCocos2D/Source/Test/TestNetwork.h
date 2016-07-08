/* --------------------------------------------------------------------------
 *
 *      File            TestNetwork.h
 *      Author          Young-Hwan Mun
 * 
 * --------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2013 cocos2d-x.org
 *
 *         http://www.cocos2d-x.org      
 *
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. All rights reserved.
 * 
 *      Contact Email: xmsoft77@gmail.com 
 * 
 * --------------------------------------------------------------------------
 * 
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
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

#ifndef __TestNetwork_h__
#define __TestNetwork_h__

#include "../TestBasic.h"

class TestNetwork : public TestBasic
{
	public :

		CREATE_FUNC ( TestNetwork );

	protected :		

		virtual	KDvoid		onEnter ( KDvoid );
		virtual	KDvoid		onExit  ( KDvoid );

		KDvoid				onMenuGetTestClicked		( CCObject* pSender );
		KDvoid				onMenuPostTestClicked		( CCObject* pSender );
		KDvoid				onMenuPostBinaryTestClicked	( CCObject* pSender );
	    
		KDvoid				onHttpRequestCompleted	    ( CCNode* pSender, KDvoid* pData );

	protected :

		CCLabelTTF*			m_pLabel;
};

#endif	// TestNetwork
