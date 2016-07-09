/* --------------------------------------------------------------------------
 *
 *      File            Ch4_Forces.h
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

#ifndef __Ch4_Forces_h__
#define __Ch4_Forces_h__

#include "Libraries/GameArea2D.h"

enum 
{
	// Collision bits for filtering
	CB_PLANET	= 1 << 0,
	CB_NONE		= 1 << 2,
};

class Ch4_Forces : public GameArea2D
{
	public :

		SCENE_FUNC ( Ch4_Forces );

	protected :		

		virtual KDbool		init ( KDvoid );

		virtual KDvoid		onExit ( KDvoid );

		virtual KDvoid		step ( KDfloat fDelta );

		KDvoid				addPlanetWithSpriteFrameName ( const KDchar* szFrameName, const CCPoint& tPosition );

	private :

		CCDictionary*		m_pPlanets;
};

#endif	// __Ch4_Forces_h__
