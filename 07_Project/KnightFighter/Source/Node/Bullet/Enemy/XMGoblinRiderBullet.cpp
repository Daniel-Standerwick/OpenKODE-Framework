/* --------------------------------------------------------------------------
 *
 *      File            XMGoblinRiderBullet.cpp
 *      Description     XMGoblinRiderBullet
 *      Author          J.S Park
 *      Contact         pparkppark84@gmail.com
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
#include "XMGoblinRiderBullet.h"
#include "Node/Effect/Slash/XMSlashEffect.h"
#include "Manager/XMGlobalManager.h"
#include "Node/Character/Player/XMPlayer.h"

XMGoblinRiderBullet::XMGoblinRiderBullet ( b2World* pWorld )
{
	m_pParentWorld = pWorld;
}

XMGoblinRiderBullet::~XMGoblinRiderBullet ( KDvoid )
{

}

XMGoblinRiderBullet* XMGoblinRiderBullet::create ( b2World* pWorld )
{
	XMGoblinRiderBullet* pRet = new XMGoblinRiderBullet ( pWorld );
	
	if ( pRet && pRet->init ( ) )
	{
		pRet->autorelease ( );
	}
	else
	{
		CC_SAFE_DELETE ( pRet );
	}

	return pRet;
}

KDbool XMGoblinRiderBullet::init ( KDvoid )
{
	if ( !XMEnemyBullet::initWithFile ( "GoblinRiderBullet.png" ) )
	{
		return KD_FALSE;
	}

	this->initVariable ( );

	this->setScale ( 1.5 );
	
	return KD_TRUE;
}

KDvoid XMGoblinRiderBullet::initVariable ( )
{

}

KDvoid XMGoblinRiderBullet::setVisible ( KDbool bVisible )
{
	XMEnemyBullet::setVisible ( bVisible );
	
	if ( bVisible == KD_FALSE )
	{
//		XMSlashEffect*		pEffect = XMSlashEffect::create ( "Knight" );

//		pEffect->setPosition ( this->getPosition ( ) );
//		this->getParent ( )->addChild ( pEffect, ZORDER_EFFECT );
	}
}