/* --------------------------------------------------------------------------
 *
 *      File            KWScene.cpp
 *      Description     
 *      Ported By       Young-Hwan Mun
 *      Created By      giginet - 11/03/05 
 *      Contact         xmsoft77@gmail.com
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. 
 *      Copyright (c) 2011-2013 Kawaz. All rights reserved.                             
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
#include "KWScene.h"

KWScene::KWScene ( KDvoid )
{
	m_tBackgroundColor = ccc4 ( 0, 0, 0, 0 );
}

KDbool KWScene::init ( KDvoid )
{
	if ( !CCLayer::initWithVisibleViewport ( ) )
	{
		return KD_FALSE;
	}

	const CCSize&	tLyrSize = this->getContentSize ( );

	m_tLyrSize = tLyrSize;

	CCLayerColor*	pBG = CCLayerColor::create ( m_tBackgroundColor, tLyrSize );
	this->addChild ( pBG );
	
	this->scheduleUpdate ( );

	this->setTouchMode ( kCCTouchesOneByOne );
	
	return KD_TRUE;
}

KDvoid KWScene::update ( KDfloat fDelta )
{
	
}
