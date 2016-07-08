/* --------------------------------------------------------------------------
 *
 *      File            Main.cpp
 *      Description     Application Entrance.
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

#include "Precompiled.h"
#include "TestList.h"
#include "Test/TestTTS.h"

#define XM_EMULATOR_CX  768
#define XM_EMULATOR_CY	1024

#include "platform.h"

//COCOS2D_ENGINE_LAUNCH ( XM_SYS_LANDSCAPE | XM_SYS_ACCELEROMETER | XM_SYS_LOCATION | XM_SYS_STATUS_BAR | XM_SYS_LOG )
COCOS2D_ENGINE_LAUNCH ( XM_SYS_LANDSCAPE | XM_SYS_LOCATION | XM_SYS_STATUS_BAR | XM_SYS_LOG )

KDbool AppDelegate::applicationDidFinishLaunching ( KDvoid )
{
	/*
	CCSize            tDesignSize ( 800, 480 );
	ResolutionPolicy  eResolutionPolicy = kResolutionExactFit;

	eResolutionPolicy = kResolutionShowAll;
	eResolutionPolicy = kResolutionNoBorder;

	TestList::s_eResolutionPolicy = eResolutionPolicy;
	TestList::s_tDesignSize       = tDesignSize;

	// Initialize Resolution
	CCEGLView::sharedOpenGLView ( )->setDesignResolutionSize ( tDesignSize, eResolutionPolicy );

	// Initalize Frame rate and debug display
	CCDirector::sharedDirector ( )->setAnimationInterval ( 1 / 60.0 );
	CCDirector::sharedDirector ( )->setDisplayStats ( KD_TRUE );

	// Initialize Scene
	CCScene*   pScene = CCScene::create ( );
    pScene->addChild ( TestList::create ( ) );
    CCDirector::sharedDirector ( )->runWithScene ( pScene );
	*/

	return KD_TRUE;
}

KDvoid AppDelegate::applicationWillTerminate ( KDvoid )
{

}

KDvoid AppDelegate::applicationWillEnterForeground ( KDvoid )
{

}

KDvoid AppDelegate::applicationDidEnterBackground  ( KDvoid )
{

}
