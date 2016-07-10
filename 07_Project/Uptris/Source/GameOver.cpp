/* --------------------------------------------------------------------------
 *
 *      File            GameOver.cpp
 *      Author          Project B team
 * 
 *      
 *      Copyright (c) 2013 XMsoft. All rights reserved.
 * 
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
#include "SoundManager.h"
#include "GameOver.h"
#include "MyRanking.h"
#include "XMSqlite/CppSQLite3.h"

KDbool GameOver::init ( KDvoid )
{
	if ( !CCLayer::initWithVisibleViewport ( ) )
	{
		return KD_FALSE;
	}

	const CCSize&		tLyrSize = this->getContentSize ( );

	// ���� ���
	SoundManager::getInstance ( )->gameOverBackgroundMusic ( );

	// ��� �߰�
	CCSprite*		pGameOverBG = CCSprite::create ( "Images/bg_gameover.jpg" );
	this->addChild ( pGameOverBG );
	pGameOverBG->setPositionWithParent ( kCCAlignmentCenter );

	// OTL �ִϸ��̼�
	CCSprite*		pGameOverOTL = CCSprite::create ( "Images/jolla1.png" );
	pGameOverOTL->setScale ( 0.5 );
    pGameOverOTL->setPosition ( ccp ( 225, 560 ) );							// width,height    
    this->addChild ( pGameOverOTL ); 
 
    CCAnimation*	pAnimation = CCAnimation::create();						// �ִϸ��̼� ����
    pAnimation->setDelayPerUnit ( 0.3f );									// �ݺ��� �ð�
    pAnimation->addSpriteFrameWithFileName ( "Images/jolla1.png" );
    pAnimation->addSpriteFrameWithFileName ( "Images/jolla2.png" );
 
    CCAnimate*		pAnimate = CCAnimate::create ( pAnimation );			// �ִϸ��̼��� �׼�ó�� �����Ű��
	CCAction*		pAction = CCRepeatForever::create ( pAnimate );			// ���� ����
    pGameOverOTL->runAction ( pAction );

	// ����
	m_pScoreField = CCLabelTTF::create ( "","Fonts/NanumGothicBold.ttf", 70 );
	m_pScoreField->setPosition ( ccp ( tLyrSize.cx / 2 , tLyrSize.cy / 2 - 160 ) );
	m_pScoreField->setColor ( ccRED );
	this->addChild ( m_pScoreField );

	// NickName �Էºκ� 
	m_pTextField = CCTextFieldTTF::create ( "< Click Here For Name Input >", "Fonts/NanumGothicBold.ttf", 27 );
	m_pTextField->setPosition ( ccp ( 240, 300) );
	m_pTextField->setColor ( ccGREEN );
	this->addChild ( m_pTextField );

	// �����ư �̹���
	CCMenuItemImage*  pMenuItem = CCMenuItemImage::create 
	(
		"Images/main_menu_button_bg_nomal.png", 
		"Images/main_menu_button_bg_press.png",
		this,
		menu_selector ( GameOver::onSaveClick )
	);

	// �����ư �ؽ�Ʈ
	CCLabelTTF*		pLabel = CCLabelTTF::create ( "Save", "Fonts/NanumGothicBold.ttf", 50 );
	pLabel->setPosition ( ccpMid ( pMenuItem->getContentSize ( ) ) );
	pLabel->setColor ( ccBLACK );

	// �����ư �޴�
	CCMenu*		pSaveMenu = CCMenu::create ( );
	pSaveMenu->setScale ( 0.5 );
	pSaveMenu->setPosition ( ccp ( 120, -30 ) );

	pMenuItem->addChild ( pLabel );
	pSaveMenu->addChild ( pMenuItem );
	this->addChild ( pSaveMenu );

	// �������� ��ƼŬ
	CCParticleSnow*		pEmitter = CCParticleSnow::create ( );
	
	ccColor4F	tStartColor = pEmitter->getStartColor ( );
	tStartColor.r = 0.9f;
	tStartColor.g = 0.9f;
	tStartColor.b = 0.9f;
	
	ccColor4F	tStartColorVar = pEmitter->getStartColorVar ( );
	tStartColorVar.b = 1.1f;

	pEmitter->setLife ( 3 );
	pEmitter->setLifeVar ( 1 );
	pEmitter->setGravity ( ccp ( 0, -10 ) );
	pEmitter->setSpeed ( 130 );
	pEmitter->setSpeedVar ( 30 );
	pEmitter->setStartColor ( tStartColor );
	pEmitter->setStartColorVar ( tStartColorVar );
	pEmitter->setEmissionRate ( pEmitter->getTotalParticles ( ) / pEmitter->getLife ( ) );
	pEmitter->setTexture ( CCTextureCache::sharedTextureCache ( )->addImage ( "Images/snow.png" ) );
	this->addChild ( pEmitter, 10 );

	// ���� �ε� �̹���
	m_pLoading = CCProgressTimer::create ( "Images/loding.png" );
	m_pLoading->setType ( kCCProgressTimerTypeRadial );
	m_pLoading->setPosition ( ccpMid ( tLyrSize ) );
	m_pLoading->runAction ( CCRepeatForever::create ( CCProgressTo::create ( 2, 100 ) ) );
	m_pLoading->setVisible ( KD_FALSE );
	this->addChild ( m_pLoading, 1000 );

	this->setTouchEnabled ( KD_TRUE );
    this->setTouchMode    ( kCCTouchesOneByOne );

	return KD_TRUE;
}

KDbool GameOver::ccTouchBegan ( CCTouch* pTouch, CCEvent* pEvent )
{
	CCRect		tRect = CCRect ( CCPointZero, m_pTextField->getContentSize ( ) );

	// NickName �Է½����̺�Ʈ 
	if ( tRect.containsPoint ( m_pTextField->convertToNodeSpace ( pTouch->getLocation ( ) ) ) )
	{
		m_pTextField->attachWithIME ( );
	}
	else
	{
		m_pTextField->detachWithIME ( );
	}
	
	return KD_TRUE;
}

// �����ư Ŭ��
KDvoid GameOver::onSaveClick ( CCObject* pSender )
{
	m_pLoading->setVisible ( KD_TRUE );
	scheduleOnce ( schedule_selector ( GameOver::insertData ) , 3 );
}

// �������� �Ϸ�
KDvoid GameOver::onHttpRequestCompleted ( CCNode* pSender, KDvoid* pData )
{
	m_pLoading->setVisible ( KD_FALSE );
	
	CCHttpResponse*		pResponse = (CCHttpResponse*) pData;
    if ( !pResponse )
    {
        return;
    }
    
    if ( 0 != kdStrlen ( pResponse->getHttpRequest ( )->getTag ( ) ) ) 
    {
        CCLOG ( "%s completed", pResponse->getHttpRequest ( )->getTag ( ) );
		
		SimpleAudioEngine::sharedEngine ( )->stopBackgroundMusic ( );
		
		CCScene*	pScene = CCScene::create ( );
		CCLayer*	pLayer = MyRanking::create ( );
		pScene->addChild ( pLayer );
		CCDirector::sharedDirector ( )->replaceScene ( pScene );
    }
}

// ���� �����Է�
KDvoid GameOver::insertData ( KDfloat fDelta )
{
	CCHttpClient*	pHttpClient = CCHttpClient::getInstance ( );
	CCHttpRequest*  pRequest = KD_NULL;
	const KDchar*   szPostData  = KD_NULL;
	std::string		sParam;

	pRequest = new CCHttpRequest ( );
	pRequest->setUrl ( "http://server1.ausoft.co.kr/uptris/write.php" );
	pRequest->setRequestType ( CCHttpRequest::kCCHttpPost );
	pRequest->setResponseCallback ( this, callfuncND_selector ( GameOver::onHttpRequestCompleted ) );

	sParam += "name=";
	sParam += m_pTextField->getString ( );
	sParam += "&score=";
	sParam += ccszf ( "%s", m_pScoreField->getString ( ) );

	// write the post data
	szPostData = sParam.c_str ( );
	pRequest->setRequestData ( szPostData, kdStrlen ( szPostData ) );
	pRequest->setTag  ( "insert" );
	pHttpClient->send ( pRequest );
	pRequest->release ( );
}

// ���� ����
KDvoid GameOver::setGameScore ( KDint nScore )
{
	m_pScoreField->setString ( ccszf ( "- %d -", nScore ) );
}