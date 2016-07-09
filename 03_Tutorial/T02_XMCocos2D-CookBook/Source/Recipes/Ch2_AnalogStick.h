/* --------------------------------------------------------------------------
 *
 *      File            Ch2_AnalogStick.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 *
 *      Created By      Nate Burba
 *      Contact         Cocos2dCookbook@gmail.com
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. 
 *      Copyright (c) 2011      COCOS2D COOKBOOK. All rights reserved. 
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

#ifndef __Ch2_AnalogStick_h__
#define __Ch2_AnalogStick_h__

class AnalogStick;
class SimpleAnimObject;

class Ch2_AnalogStick : public Recipe
{
	public :

		SCENE_FUNC ( Ch2_AnalogStick );

	protected :		

		virtual KDbool			init ( KDvoid );

		virtual KDvoid			ccTouchesBegan ( CCSet* pTouches, CCEvent* pEvent );
		virtual KDvoid			ccTouchesMoved ( CCSet* pTouches, CCEvent* pEvent );
		virtual KDvoid			ccTouchesEnded ( CCSet* pTouches, CCEvent* pEvent );

		KDvoid					step ( KDfloat fDelta );

		KDvoid					animateGunman ( KDvoid );

	private :

		AnalogStick*			m_pAnalogStick;
		SimpleAnimObject*		m_pGunman;
		KDint					m_nGunmanDirection;
};

#endif	// __Ch2_AnalogStick_h__
