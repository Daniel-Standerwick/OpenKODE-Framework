/* --------------------------------------------------------------------------
 *
 *      File            GameLayer.cpp
 *      Created By      Project B team
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2013 XMsoft. All rights reserved.
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
#include "GameLayer.h"
#include "GameOver.h"
#include "Board.h"
#include "Tetromino.h"
#include "SoundManager.h"

#define LEVELUP_COUNT		6

enum 
{
	kTagSound		,
	kTagVibeRate	,
};

GameLayer::GameLayer ( KDvoid )
{
	m_nTouchedTarget	= TOUCH_NONE;
	m_pNextTetromino	= KD_NULL;
	
	m_bIsSound			= KD_TRUE;
	m_bIsVibrate		= KD_TRUE;

	m_nLevelValue		= 1;
	m_nScoreValue		= 0;
	m_nBlockLineValue	= 0;
}

KDbool GameLayer::init ( KDvoid )
{
	if ( !CCLayer::initWithVisibleViewport ( ) ) 
	{
		return KD_FALSE;
	}

	const CCSize&	tLyrSize = this->getContentSize ( );

	// ��� ����
	CCSprite*	pBgSprite = CCSprite::create ( "Images/tetrisbghdpi.jpg" );
	pBgSprite->setPosition ( ccpMid ( tLyrSize ) );
	this->addChild ( pBgSprite );

	// ���� ����
	m_pBoard = Board::create ( );
	m_pBoard->setAnchorPoint ( ccpz );
	m_pBoard->setPosition ( 0, tLyrSize.cy - BOARD_ROW_CNT * BLOCK_SIZE );
	this->addChild ( m_pBoard );

	// ���ھ�
	m_pScore = CCLabelTTF::create ( "0", "Fonts/NanumGothicBold.ttf", 22 );
	m_pScore->setPosition ( ccp ( 420, 645 ) );
	m_pScore->setColor ( ccc3 ( 255, 0, 0 ) );
	this->addChild ( m_pScore );

	// ���� �ټ�
	m_pBlockLine = CCLabelTTF::create ( "0", "Fonts/NanumGothicBold.ttf", 22 );
	m_pBlockLine->setPosition ( ccp ( 420, 580 ) );
	m_pBlockLine->setColor ( ccc3 ( 0, 0, 255 ) );
	this->addChild ( m_pBlockLine );

	// ����
	m_pLevel = CCLabelTTF::create ( "1", "Fonts/NanumGothicBold.ttf", 22 );
	m_pLevel->setPosition ( ccp ( 420, 520 ) );
	m_pLevel->setColor ( ccc3 ( 0, 255, 0 ) );
	this->addChild ( m_pLevel );

	// �Ҹ�
	CCMenuItemToggle*  pTogleSound = CCMenuItemToggle::createWithTarget 
	(
		this, 
		menu_selector ( GameLayer::onMenuCallback ), 
		CCMenuItemImage::create ( "Images/soundon.png" ,"Images/soundon.png" ),
		CCMenuItemImage::create ( "Images/soundoff.png" ,"Images/soundoff.png" ),
		KD_NULL 
	);
	pTogleSound->setTag ( kTagSound );	

	// ����
	CCMenuItemToggle*  pTogleViberate = CCMenuItemToggle::createWithTarget 
	(
		this, 
		menu_selector ( GameLayer::onMenuCallback ), 
		CCMenuItemImage::create ( "Images/vibe_on.png" ,"Images/vibe_on.png" ),
		CCMenuItemImage::create ( "Images/vibe_off.png" ,"Images/vibe_off.png" ),
		KD_NULL 
	);
	pTogleViberate->setTag ( kTagVibeRate );

	CCMenu*		pMenu = CCMenu::create
	(
		pTogleSound,
		pTogleViberate,
		KD_NULL
	);
	pMenu->setPosition ( ccp ( 420, 320 ) );
	pMenu->alignItemsInColumns ( 1, 1, KD_NULL );
	pMenu->alignItemsVerticallyWithPadding ( 20 );
	this->addChild ( pMenu );

	// levelup �ִ�
	m_pLevelupSprite = CCSprite::create ( "Images/levelup/levelup_f50.jpg" );
	m_pLevelupSprite->setPosition ( ccpMid ( tLyrSize ) );
	m_pLevelupSprite->setVisible ( KD_FALSE );
	this->addChild ( m_pLevelupSprite );

	m_pLevelupAnimation = CCAnimation::create ( );
	m_pLevelupAnimation->retain ( );
	for ( KDint i = 0; i < 51; i++ )
    {
        KDchar  szName [100] = { 0 };
        kdSprintf ( szName, "Images/levelup/levelup_f%02d.jpg", i );
        m_pLevelupAnimation->addSpriteFrameWithFileName ( szName );
    }
    
    m_pLevelupAnimation->setDelayPerUnit ( 2.8f / 50.0f );
    m_pLevelupAnimation->setRestoreOriginalFrame ( KD_TRUE );

	this->setTouchEnabled  ( KD_TRUE );
	this->setKeypadEnabled ( KD_TRUE );
	this->setEventEnabled  ( KD_TRUE );
	return KD_TRUE;
}

KDvoid GameLayer::onEnter ( KDvoid )
{
	CCLayer::onEnter ( );

	SoundManager::getInstance ( )->playBackgroundMusic ( );
}

KDvoid GameLayer::onEvent ( const KDEvent* pEvent )
{
	if ( pEvent->type == KD_EVENT_FOCUS )
	{
		// ��Ŀ�� �޾����� ���
		if ( pEvent->data.value.i == 1 )
		{
			CCDirector::sharedDirector ( )->resume ( );
		}
		// ��Ŀ�� �Ҿ����� �Ͻ�����
		else
		{
			CCDirector::sharedDirector ( )->pause ( );
		}
	}
}

KDvoid GameLayer::ccTouchesBegan ( CCSet* pTouches, CCEvent* pEvent )
{
	CCTouch*	pTouch    = (CCTouch*) pTouches->anyObject ( );
	CCPoint		tLocation = this->convertTouchToNodeSpace ( pTouch );
	
	KDint		x = tLocation.x;
	KDint		y = tLocation.y;

	// LEFT
	if ( x > 0 && x < 130 && y > 0 && y < 130 )
	{
		keyPressed ( KD_INPUT_GAMEKEYS_LEFT );
	}
	// ROTATE
	else if ( x > 170 && x < 310 && y > 0 && y < 130 )
	{
		keyPressed ( KD_INPUT_GAMEKEYS_DOWN );
	}
	// RIGHT
	else if ( x > 360 && x < 470 && y > 0 && y < 130 )
	{
		keyPressed ( KD_INPUT_GAMEKEYS_RIGHT );
	}
	// SHOOT
	else if ( x > 370 && x < 470 && y > 150 && y < 240 )
	{
		keyPressed ( KD_INPUT_GAMEKEYS_UP );
	}
}

KDvoid GameLayer::ccTouchesEnded ( CCSet* pTouches, CCEvent* pEvent )
{
	CCTouch*	pTouch    = (CCTouch*) pTouches->anyObject ( );
	CCPoint		tLocation = this->convertTouchToNodeSpace ( pTouch );
	
	KDint		x = tLocation.x;
	KDint		y = tLocation.y;

	// LEFT
	if ( x > 0 && x < 130 && y > 0 && y < 130 )
	{
		keyReleased ( KD_INPUT_GAMEKEYS_LEFT );
	}
	// RIGHT
	else if ( x > 360 && x < 470 && y > 0 && y < 130 )
	{
		keyReleased ( KD_INPUT_GAMEKEYS_RIGHT );
	}
}

KDvoid GameLayer::keyPressed ( KDint nId )
{
	switch ( nId )
	{
		// LEFT
		case KD_INPUT_GAMEKEYS_LEFT :
			m_nTouchedTarget = TOUCH_LEFT;
			m_pBoard->moveTetromino ( -1, 0 );

			// �����ٷ� ����
			this->unschedule ( schedule_selector ( GameLayer::onPressedButton ) );
			this->schedule   ( schedule_selector ( GameLayer::onPressedButton ), 0.05f, kCCRepeatForever, 0.4f );
			break;

		// RIGHT
		case KD_INPUT_GAMEKEYS_RIGHT :
			m_nTouchedTarget = TOUCH_RIGHT;
			m_pBoard->moveTetromino ( 1, 0 );

			// �����ٷ� ����
			this->unschedule ( schedule_selector ( GameLayer::onPressedButton ) );
			this->schedule   ( schedule_selector ( GameLayer::onPressedButton ), 0.05f, kCCRepeatForever, 0.4f );
			break;

		// UP
		case KD_INPUT_GAMEKEYS_UP :
			m_nTouchedTarget = TOUCH_SHOOT;
			m_pBoard->shootTetromino ( );
			break;

		// DOWN
		case KD_INPUT_GAMEKEYS_DOWN :
			m_nTouchedTarget = TOUCH_ROTATE;
			m_pBoard->rotateTetromino ( );
			break;
	}
}

KDvoid GameLayer::keyReleased ( KDint nId )
{
	switch ( nId )
	{
		// LEFT
		case KD_INPUT_GAMEKEYS_LEFT :
			if ( m_nTouchedTarget == TOUCH_LEFT )
			{
				m_nTouchedTarget = TOUCH_NONE;
				this->unschedule ( schedule_selector ( GameLayer::onPressedButton ) );
			}
			break;

		// RIGHT
		case KD_INPUT_GAMEKEYS_RIGHT :
			if ( m_nTouchedTarget == TOUCH_RIGHT )
			{
				m_nTouchedTarget = TOUCH_NONE;
				this->unschedule ( schedule_selector ( GameLayer::onPressedButton ) );
			}
			break;
	}
}

// �޴� ��ġ�� �ݹ�
KDvoid GameLayer::onMenuCallback ( CCObject* pSender )
{
	CCMenuItemToggle*	pToggle = (CCMenuItemToggle*) pSender;
	switch ( pToggle->getTag ( ) )
	{
		case kTagSound :			
			if ( pToggle->getSelectedIndex ( ) == 1 )
			{
				SimpleAudioEngine::sharedEngine ( )->pauseBackgroundMusic ( );
				m_bIsSound = KD_FALSE;
			}
			else
			{
				SimpleAudioEngine::sharedEngine ( )->resumeBackgroundMusic ( );			
				m_bIsSound = KD_TRUE;
			}
			break;

		case kTagVibeRate :
			if ( pToggle->getSelectedIndex ( ) == 1 )
			{
				m_bIsVibrate = KD_FALSE;
			}
			else
			{
				m_bIsVibrate = KD_TRUE;
			}
			break;
	}
}

// ������� ����
KDvoid GameLayer::onNextTetromino ( KDint nType )
{
	if ( m_pNextTetromino != KD_NULL )
	{
		m_pNextTetromino->removeFromParent ( );
	}

	m_pNextTetromino = Tetromino::create ( nType );
	m_pNextTetromino->setPosition ( ccp ( 400, 415 ) );
	m_pNextTetromino->setScale ( 0.4f );
	this->addChild ( m_pNextTetromino );
}

// �̵�Ű�� ��������
KDvoid GameLayer::onPressedButton ( KDfloat fDelta )
{
	if ( m_nTouchedTarget == TOUCH_LEFT )
	{
		m_pBoard->moveTetromino ( -1, 0 );
	}
	else if ( m_nTouchedTarget == TOUCH_RIGHT )
	{
		m_pBoard->moveTetromino ( 1, 0 );
	}
}

// ������ ���� �ݹ�
KDvoid GameLayer::onClearLine ( KDint nCount )
{
	m_nBlockLineValue	+= nCount;
	m_nScoreValue		+= nCount * 10 * ( 1 + ( nCount - 1 ) * 0.3f ); // 10��, 26��, 48��, 76��

	m_pScore->setString ( ccszf ( "%d", m_nScoreValue ) );
	m_pBlockLine->setString ( ccszf ( "%d", m_nBlockLineValue ) );

	KDint nLevelValue = m_nBlockLineValue / LEVELUP_COUNT + 1;
	if ( m_nLevelValue != nLevelValue )
	{		
		m_nLevelValue = nLevelValue;
		m_pLevel->setString ( ccszf ( "%d", m_nLevelValue ) );

		// ���� ����� �ӵ� ��ȭ
		KDfloat		fSec = 1 - ( ( m_nLevelValue - 1 ) * 0.05f );

		// �ְ�ӵ� Ȧ������ 0.1, ¦������ 0.2
		if ( fSec < 0.1f )
		{
			fSec = m_nLevelValue % 2 == 1 ? 0.1f : 0.2f;
		}

		m_pBoard->setGameSpeed ( fSec );

		// �ִϸ��̼� ����
		showLevelUpAni ( );

		SoundManager::getInstance ( )->playLevelupEffect ( );		
	}
	
	if ( nCount >= 2 )
	{
		shakeScreen ( );
		SoundManager::getInstance ( )->playLineClearEffect ( );
	}
}

// ���ӿ��� �ݹ�
KDvoid GameLayer::onGameOver ( KDvoid )
{
	const CCSize&	tLyrSize = this->getContentSize ( );

	CCSprite*		pSprite = CCSprite::create ( );
	pSprite->setTextureRect ( CCRect ( 0, 0, tLyrSize.cx, tLyrSize.cy ) );
	pSprite->setAnchorPoint ( ccpz );
	pSprite->setColor ( ccc3 ( 0, 0, 0 ) );
	pSprite->setOpacity ( 150 );
	pSprite->setPositionY ( tLyrSize.cy );
	this->addChild ( pSprite );

	GameOver*		pGameOver =	GameOver::create ( );
	pGameOver->setGameScore ( m_nScoreValue );
	this->addChild ( pGameOver );

	CCAction*		pActions = CCSequence::create 
	(
		CCScaleTo::create ( 0, 0, 0 ),
		CCScaleTo::create ( 0.3f, 1, 1 ),
		KD_NULL
	);
	pGameOver->runAction ( pActions );
}

// ȭ���� ���� �ݴϵ�~
KDvoid GameLayer::shakeScreen ( KDvoid )
{
	xmVibrate ( 1000 );

	CCArray*	pActions = CCArray::create ( );

	for ( KDint i = 0; i < 60; ++i )
	{
		CCFiniteTimeAction*		pMove = CCMoveTo::create ( 1.f / 60, ccp ( 30 - kdRand ( ) % 60, 15 - kdRand ( ) % 60 ) );
		pActions->addObject ( pMove );
	}
	
	CCFiniteTimeAction*		pReset = CCMoveTo::create ( 1.f / 60, ccp ( 0, 0 ) );
	pActions->addObject ( pReset );

	this->runAction ( CCSequence::create ( pActions ) );
}

// ������ �̹��� ����
KDvoid GameLayer::showLevelUpAni ( KDvoid )
{
    CCAnimate*		pAction = CCAnimate::create ( m_pLevelupAnimation );
	m_pLevelupSprite->setVisible ( KD_TRUE );
	m_pLevelupSprite->runAction ( CCSequence::create ( pAction, KD_NULL ) );
	scheduleOnce ( schedule_selector ( GameLayer::hideLevelUpAni ), 3.5f );
}

// ������ �̹��� ����
KDvoid	GameLayer::hideLevelUpAni ( KDfloat dt )
{
	m_pLevelupSprite->setVisible ( KD_FALSE );
}

// ���ӷ��� ��ȯ
KDint GameLayer::getLevel ( KDvoid )
{
	return m_nLevelValue;
}
