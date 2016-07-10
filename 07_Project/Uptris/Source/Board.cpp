/* --------------------------------------------------------------------------
 *
 *      File            Board.cpp
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
#include "Board.h"
#include "Block.h"
#include "Tetromino.h"
#include "GameLayer.h"
#include "SoundManager.h"

Board::Board ( KDvoid )
{
	kdMemset ( m_aBoards, 0, sizeof ( m_aBoards ) );

	m_pTetromino	 = KD_NULL;
	m_nNextTetroType = -1;
	m_nGameSpeed	 = 1;
}

KDbool Board::init ( KDvoid )
{
	if ( !CCLayer::initWithVisibleViewport ( ) ) 
	{
		return KD_FALSE;
	}

	return KD_TRUE;
}

KDvoid Board::onEnter ( KDvoid )
{
	CCLayer::onEnter ( );

    CCLOG ( "%d", kdRand ( ) );
    
//	kdSrand ( kdTime ( 0 ) );

	// ù��° ������
	this->createTetromino ( );

	// �����ٷ� ����
	this->schedule ( schedule_selector ( Board::goTetromino ), m_nGameSpeed );
}

// ���Ӽӵ� ����
KDvoid Board::setGameSpeed ( KDfloat fSec )
{
	m_nGameSpeed = fSec;

	// �����췯 �簡��
	this->unschedule ( schedule_selector ( Board::goTetromino ) );
	this->schedule   ( schedule_selector ( Board::goTetromino ), fSec );

	CCLOG ( "setGameSpeed: %f", fSec );
}

// ���� ��Ÿ���� ��ȯ
KDint Board::newTetroType ( KDvoid )
{
	KDint		nBlockTypeCnt;
	GameLayer*	pGameLayer = (GameLayer*) this->getParent ( );

	// �������� ���� ������ �ٸ��� ��
	if		( pGameLayer->getLevel ( ) > 10 )	{ nBlockTypeCnt = BLOCK_TYPE_COUNT;     }
	else if ( pGameLayer->getLevel ( ) >  5 )	{ nBlockTypeCnt = BLOCK_TYPE_COUNT - 1; }
	else										{ nBlockTypeCnt = BLOCK_TYPE_COUNT - 3; }

	KDint		nType = kdRand ( ) % nBlockTypeCnt;

	// ���� �� �ݹ� �۽�
	pGameLayer->onNextTetromino ( nType );

	return nType;
}

// ������
KDvoid Board::createTetromino ( KDvoid )
{
	// ���� ���� ���ǵ��� �ʾ�����
	if ( m_nNextTetroType == -1 )
	{
		m_nNextTetroType = newTetroType ( );
	}

	// ������
	m_pTetromino = Tetromino::create ( m_nNextTetroType );
	m_pTetromino->setAnchorPoint ( ccpz );
	this->addChild ( m_pTetromino );

	// �� ��ġ�� �ϴ��� �߾����� ����
	KDint nCenterX = ( BOARD_COLUMN_CNT - m_pTetromino->getColumnCnt ( ) ) / 2;
	KDint nBottomY = BOARD_ROW_CNT - m_pTetromino->getRowCnt ( );
	m_pTetromino->setBoardPosition ( nCenterX, nBottomY );

	// ���� ���� �̸� ����
	m_nNextTetroType = newTetroType ( );
	CCLOG ( "createTetro: %d, %d", nCenterX, nBottomY );
}

// �� �̵�
KDbool Board::moveTetromino ( KDint offsetX, KDint offsetY )
{
	if ( m_pTetromino == KD_NULL )
	{
		return KD_FALSE;
	}

	KDint	nMoveTop	 = m_pTetromino->getBoardY ( ) + offsetY;		// �̵� �� �� ��� ��ǥ (������ġ + �̵���)
	KDint	nMoveLeft	 = m_pTetromino->getBoardX ( ) + offsetX;		// �̵� �� �� ���� ��ǥ (������ġ + �̵���)
	KDint	nMoveRight	 = nMoveLeft + m_pTetromino->getColumnCnt ( );	// �̵� �� �� ���� ��ǥ (������ġ + ��ũ��)

	KDbool	bIsStuck	 = KD_FALSE;
	KDbool	bIsCollision = KD_FALSE;

	// ���� �̵��� ���ʺ� �Ǵ� �ٸ� ���� �浹üũ 
	if ( offsetX == 0 && ( nMoveTop < 0 || isCollision ( offsetX, offsetY ) ) )
	{
		CCLOG ( "is Stuck" );
		bIsStuck = KD_TRUE;
	}

	// ����,������,�� �浹üũ
	else if ( nMoveLeft < 0 || nMoveRight > BOARD_COLUMN_CNT || isCollision ( offsetX, offsetY ) )
	{
		CCLOG ( "is Collision" );
		bIsCollision = KD_TRUE;
	}

	// �浹 �������� �̵�
	if ( ! bIsCollision && ! bIsStuck )
	{
		CCLOG ( "moveTetro: %d, %d", nMoveLeft, nMoveTop );
		m_pTetromino->setBoardPosition ( nMoveLeft, nMoveTop );
	}

	// �̵������
	if ( bIsStuck )
	{
		// �̵����� ������ �浹�� �ƴҶ�
		if ( !isCollision ( 0, 0 ) )
		{
			// �� �̵��Ϸ�
			stuckTetromino ( );

			// �� �� ����
			createTetromino ( );
		}

		// �̵����� �ʾƵ� �̹� �浹�϶�, ���� ���� �������ٿ� ������
		else if ( m_pTetromino->getBoardY ( ) + m_pTetromino->getRowCnt ( ) >= BOARD_ROW_CNT )
		{
			// ���ӿ���
			gameOver ( );
		}

		return KD_FALSE;
	}

	return KD_TRUE;
}

// ��ȸ��
KDvoid Board::rotateTetromino ( KDvoid )
{
	if ( m_pTetromino == KD_NULL )
	{
		return;
	}

	// ȸ���� ����� �ٸ���ϰ� �浹�Ǿ����� �� �����ֱ� ���� ī����
	KDint	nRotateCount = 4;

	do 
	{
		// ȸ�� �� ����
		KDint	nBeforeColumnCnt = m_pTetromino->getColumnCnt ( );

		m_pTetromino->rotateBlock ( );
		
		// ȸ�� �� ����
		KDint nAfterColumnCnt = nBeforeColumnCnt - m_pTetromino->getColumnCnt ( );

		// �� ��ġ�� �߰����� ����
		m_pTetromino->setBoardPosition ( m_pTetromino->getBoardX ( ) + nAfterColumnCnt / 2, m_pTetromino->getBoardY ( ) );

		nRotateCount--;

	} while ( isCollision ( 0, 0 ) && nRotateCount > 0 ); // ȸ���� ����� �ٸ���ϰ� �浹�Ǿ����� �ִ� 4������ �ݺ�

	SoundManager::getInstance ( )->playRotateEffect ( );
}

// �� �����ȱ�
KDvoid Board::shootTetromino ( KDvoid )
{
	if ( m_pTetromino == KD_NULL )
	{
		return;
	}

	// ��ƼŬ ȿ��. ������ ��
	/*
	CCParticleSystem*	pEmitter = CCParticleExplosion::create ( 100 );
	pEmitter->setTexture ( CCTextureCache::sharedTextureCache ( )->addImage ( "Images/star.png" ) );
	pEmitter->setLife ( 0.1f );
	pEmitter->setLifeVar ( 0.1f );
	pEmitter->setSpeed ( 300 );
	pEmitter->setSpeedVar ( 300 );
	pEmitter->setStartSize ( 15 );
	pEmitter->setZOrder ( 0 );
	pEmitter->setAutoRemoveOnFinish ( KD_TRUE );
	pEmitter->setPosition ( ccp ( m_pTetromino->getPositionX ( ) + m_pTetromino->getColumnCnt ( ) * BLOCK_SIZE / 2, m_pTetromino->getPositionY ( ) + m_pTetromino->getRowCnt ( ) * BLOCK_SIZE / 2 ) );
	this->addChild ( pEmitter );	
	*/

	// ���̵��� ����ɶ� ���� �ݺ�
	while ( moveTetromino ( 0, -1 ) );
}

// 1�ʸ��� �� �����̵�
KDvoid Board::goTetromino ( KDfloat fDelta )
{
	moveTetromino ( 0, -1 );
}

// �� �̵��Ϸ�
KDvoid Board::stuckTetromino ( KDvoid )
{
	// �����췯 �簡��
	setGameSpeed ( m_nGameSpeed );

	// Tetromino ���� ���� ���忡 ����
	saveTetromino ( );

	// �ϼ��� ���� ����
	clearLine ( );

	SoundManager::getInstance ( )->playStuckEffect ( );
}

// Tetromino ���� ���� ���忡 ����
KDvoid Board::saveTetromino ( KDvoid )
{
	// ������ �� �迭
	CCArray*	pBlockArray = m_pTetromino->getChildren ( );
	KDint nCount = pBlockArray->count ( );

	// ������ �� �迭 ����
	CCArray*	pCopyArray = CCArray::create ( );
	pCopyArray->addObjectsFromArray ( pBlockArray );
	
	// ���� �� ��� ����
	m_pTetromino->removeAllChildren ( );

	CCLOG ( "saveParticle" );

	// �浹 ��ƼŬ ȿ���� ������ �� ����
	CCObject*	pObject;
	CCArray*	pParticleArray = CCArray::create ( );
	CCARRAY_FOREACH ( pCopyArray, pObject )
	{
		Block*		pBlock = (Block*) pObject;

		KDint x = m_pTetromino->getBoardX ( ) + pBlock->getTetroX ( );
		KDint y = m_pTetromino->getBoardY ( ) + pBlock->getTetroY ( );

		// ���� �����̰ų� ���ʿ� ���� ������
		if ( y == 0 || m_aBoards [ x ] [ y - 1 ] != KD_NULL )
		{
			pParticleArray->addObject ( pBlock );
		}
	}

	CCLOG ( "saveTetro" );

	// ������ ���� ���忡 ����
	for ( KDint i = 0; i < nCount; i++ )
	{
		Block*		pBlock = (Block*) pCopyArray->objectAtIndex ( i );

		KDint x = m_pTetromino->getBoardX ( ) + pBlock->getTetroX ( );
		KDint y = m_pTetromino->getBoardY ( ) + pBlock->getTetroY ( );
		pBlock->setBoardPosition ( x, y );
		this->addChild ( pBlock );

		m_aBoards [ x ] [ y ] = pBlock;
	}

	CCLOG ( "showParticle" );

	CCARRAY_FOREACH ( pParticleArray, pObject )
	{
		Block*		pBlock = (Block*) pObject;

		// �浹 ��ƼŬ ȿ��
		CCParticleSystem*	pEmitter = CCParticleSun::create ( 100 );
		pEmitter->setLife ( 1 );
		pEmitter->setSpeedVar ( 1 );
		pEmitter->setDuration ( 0.1f );
		pEmitter->setStartSize ( 50 );
		pEmitter->setZOrder ( 0 );
		pEmitter->setAutoRemoveOnFinish ( KD_TRUE );
		pEmitter->setPosition ( ccp ( pBlock->getPositionX ( ) + BLOCK_SIZE / 2, pBlock->getPositionY ( ) + BLOCK_SIZE ) );
		this->addChild ( pEmitter );
	}
}

// Tetromino ���� ���� ���忡 �ִ� �� �浹üũ
KDbool Board::isCollision ( KDint offsetX, KDint offsetY )
{
	CCObject*	pObject;
	CCARRAY_FOREACH ( m_pTetromino->getChildren ( ), pObject )
	{
		Block*		pBlock = (Block*) pObject;

		KDint x = m_pTetromino->getBoardX ( ) + pBlock->getTetroX ( ) + offsetX;
		KDint y = m_pTetromino->getBoardY ( ) + pBlock->getTetroY ( ) + offsetY;

		if ( m_aBoards [ x ] [ y ] != KD_NULL )
		{
			CCLOG ( "%d, %d", m_pTetromino->getBoardX ( ), pBlock->getTetroX ( ), offsetX );
			return KD_TRUE;
		}
	}
	return KD_FALSE;
}

// �ϼ��� ���� ����
KDvoid Board::clearLine ( KDvoid )
{
	KDint	nClearCnt = 0;

	for ( KDint y = BOARD_ROW_CNT - 1; y >= 0; y-- )
	{
		KDbool	bIsFull = KD_TRUE;

		// ���� �ϼ����� Ȯ��
		for ( KDint x = 0; x < BOARD_COLUMN_CNT; x++ )
		{
			if ( m_aBoards [ x ] [ y ] == KD_NULL )
			{
				bIsFull = KD_FALSE;
			}
		}

		// �ϼ��� �����϶�
		if ( bIsFull )
		{
			nClearCnt++;
		}
		// �ϼ��� ������ �ƴҶ�
		else
		{
			continue;
		}

		for ( KDint targetY = y; targetY < BOARD_ROW_CNT; targetY++ )
		{
			for ( KDint targetX = 0; targetX < BOARD_COLUMN_CNT; targetX++ )
			{
				Block*&		pBlock = m_aBoards [ targetX ] [ targetY ];

				// ���� ���� �����϶�
				if ( targetY == y )
				{
					KDfloat		fDelay = kdRand ( ) % 8 / 10.f;
					KDint		nPostionx = ( kdRand ( ) % ( BOARD_WIDTH * 3 ) ) - BOARD_WIDTH;

					// ������ �ִϸ��̼� ����
					CCAction*	pActions = CCSequence::create 
					(
						CCEaseOut::create																// ���ӵ��� �־�
						( 
							CCSpawn::create 
							(
								CCFadeOut ::create ( 1 ),												// �����������
								CCRotateBy::create ( 0.5f, 360 * 5 ),									// ȸ����Ű��
								CCMoveTo  ::create ( fDelay, ccp ( nPostionx, -300 ) ),					// �����ӵ�, ������ġ�� �̵�
								CCScaleBy ::create ( fDelay, 3 ),
								KD_NULL
							),
							0.8f
						),
						CCCallFuncO::create ( this, callfuncO_selector ( Board::clearBlock ), pBlock ),	// ���� ���忡�� �� ����
						KD_NULL
					);

					pBlock->setZOrder ( 0 );
					pBlock->setAnchorPoint ( ccp ( 0.5f, 0.5f ) );
					pBlock->runAction ( pActions );

					// ������ ��ƼŬ ȿ��
					CCParticleSystem*	pEmitter = CCParticleFlower::create ( 100 );
					pEmitter->setLife ( 0.5f );
					pEmitter->setSpeedVar ( 0.5f );
					pEmitter->setDuration ( 0.5f );
					pEmitter->setStartSize ( 50 );
					pEmitter->setZOrder ( 0 );
					pEmitter->setAutoRemoveOnFinish ( KD_TRUE );
					pEmitter->setPosition ( ccp ( pBlock->getPositionX ( ) + BLOCK_SIZE / 2, pBlock->getPositionY ( ) + BLOCK_SIZE / 2 ) );
					this->addChild ( pEmitter );
				}
				// ���������� ���� �� ��ĭ�� ���� �̵�
				else if ( targetY < BOARD_ROW_CNT - 1 && pBlock != KD_NULL)
				{
					pBlock->setBoardPosition ( pBlock->getBoardX ( ), pBlock->getBoardY ( ) - 1 );
				}

				// ���������� ���� �迭���� ��ĭ�� ���� �̵�
				if ( targetY < BOARD_ROW_CNT - 1 )
				{
					pBlock = m_aBoards [ targetX ] [ targetY + 1 ];
				}
				// ������ ������ null
				else
				{
					pBlock = KD_NULL;
				}
			}
		}
	}

	if ( nClearCnt > 0 )
	{
		// ���� ���� �ݹ� �۽�
		GameLayer*		pGameLayer = (GameLayer*) this->getParent ( );
		pGameLayer->onClearLine ( nClearCnt );

		SoundManager::getInstance ( )->playBoomEffect ( );
	}
}

// �ϼ��� ���� ���� �ִϸ��̼� �� ���� �� ����
KDvoid Board::clearBlock ( CCObject* pSender )
{
	Block*		pBlock = (Block*) pSender;
	pBlock->removeFromParent ( );
}

// ���ӿ���
KDvoid Board::gameOver ( KDvoid )
{
	this->unschedule ( schedule_selector ( Board::goTetromino ) );

	// ���� ���� �ݹ� �۽�
	GameLayer*	pGameLayer = (GameLayer*) this->getParent ( );
	pGameLayer->onGameOver ( );
}