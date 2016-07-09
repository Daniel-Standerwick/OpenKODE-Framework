/* --------------------------------------------------------------------------
 *
 *      File            Helper.cpp
 *
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 *
 *      Created By      Steffen Itterheim on 10/09/20
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. 
 *      Copyright (c) 2010      Steffen Itterheim. All rights reserved.
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

#include "Precompiled.h"
#include "Helper.h"

// convenience method to convert a CCPoint to a b2Vec2
b2Vec2 Helper::toMeters ( const CCPoint& tPoint )
{
	return b2Vec2 ( tPoint.x / PTM_RATIO, tPoint.y / PTM_RATIO );
}

// convenience method to convert a b2Vec2 to a CCPoint
CCPoint Helper::toPixels ( const b2Vec2& tVec )
{
	return ccpMult ( ccp ( tVec.x, tVec.y ), PTM_RATIO );
}

CCPoint Helper::locationFromTouch ( CCTouch* pTouch )
{
	return pTouch->getLocation ( );
}

CCPoint Helper::locationFromTouches ( CCSet* pTouches )
{
	return Helper::locationFromTouch ( (CCTouch*) pTouches->anyObject ( ) );
}

CCPoint Helper::screenCenter ( KDvoid )
{
	return ccpMid ( CCDirector::sharedDirector ( )->getWinSize ( ) );
}

