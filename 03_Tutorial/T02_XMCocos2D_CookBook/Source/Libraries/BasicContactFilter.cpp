/* --------------------------------------------------------------------------
 *
 *      File            BasicContactFilter.cpp
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

#include "Precompiled.h"
#include "BasicContactFilter.h"

KDbool BasicContactFilter::ShouldCollide ( b2Fixture* pFixtureA, b2Fixture* pFixtureB )
{
	const b2Filter&		tFilterA = pFixtureA->GetFilterData ( );
	const b2Filter&		tFilterB = pFixtureB->GetFilterData ( );

	if ( tFilterA.groupIndex == tFilterB.groupIndex && tFilterA.groupIndex != 0 )
	{
		return tFilterA.groupIndex > 0;
	}

	KDbool	bCollide = ( tFilterA.maskBits & tFilterB.categoryBits ) != 0 && ( tFilterA.categoryBits & tFilterB.maskBits ) != 0;

	return bCollide;
}

