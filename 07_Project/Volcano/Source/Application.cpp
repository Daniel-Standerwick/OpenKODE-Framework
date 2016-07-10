/* --------------------------------------------------------------------------
 *
 *      File            Application.cpp
 *      Description     
 *      Author          Kyoung-Cheol Kim
 *      Contact         redfreek2c@gmail.com
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
#include "platform.h"
#include "SplashLayer.h"

COCOS2D_ENGINE_LAUNCH ( XM_SYS_LOG )

KDbool AppDelegate::applicationDidFinishLaunching ( KDvoid )
{
	// ���ϴ� �ػ󵵷� ����
	CCEGLView::sharedOpenGLView ( )->setDesignResolutionSize ( 480, 800, kResolutionExactFit );

	// ����� ���� ǥ�� (�� �ϴ�)
//	CCDirector::sharedDirector ( )->setDisplayStats ( KD_TRUE );

	// ó�� ȭ�� ǥ��
    CCScene*	pScene = CCScene::create ( );
    CCLayer*	pLayer = SplashLayer::create ( );
    pScene->addChild ( pLayer );
	CCDirector::sharedDirector ( )->runWithScene ( pScene );

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
