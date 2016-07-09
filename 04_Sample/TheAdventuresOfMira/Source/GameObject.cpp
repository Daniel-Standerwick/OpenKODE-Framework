/* --------------------------------------------------------------------------
 *
 *      File            GameObject.cpp
 *
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 *
 *      Created By      Craig Newton on 2012/10/04
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. All rights reserved. 
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
#include "GameObject.h"

KDbool GameObject::init ( KDvoid )
{    
    if ( !CCSprite::init ( ) )
    {
		return KD_FALSE;
	}

	m_tScreenSize		= SCREEN_SIZE;
	m_bIsActive			= KD_TRUE;
	m_eGameObjectType	= kObjectTypeNone;
    
    return KD_TRUE;
}

KDvoid GameObject::changeState ( CharacterState eNewState )
{
    CCLOG ( "GameObject->changeState method should be overridden" );
}

CCRect GameObject::adjustedBoundingBox ( KDvoid )
{
    CCLOG ( "GameObject->adjustedBoundingBox should be overridden" );
    return this->boundingBox ( );
}
