/* --------------------------------------------------------------------------
 *
 *      File            Block.cpp
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
#include "Block.h"

Block::Block ( KDvoid )
{
	m_nTetroX = 0;
	m_nTetroY = 0;
	m_nBoardX = 0;
	m_nBoardY = 0;
}

Block* Block::create ( KDint nType )
{
	Block*		pBlock = new Block ( );	

	if ( pBlock && pBlock->init ( nType ) )
	{
		pBlock->autorelease ( );
	}
	else
	{
		CC_SAFE_DELETE ( pBlock );
	}
	
	return pBlock;
}; 

KDbool Block::init ( KDint nType )
{
	if ( ! CCLayerGradient::init ( ) ) 
	{
		return KD_FALSE;
	}
	
	ccColor4B	tBlockColor1;
	ccColor4B	tBlockColor2;

	// ��Ÿ�Կ� ���� ���迭 �ε�
	switch ( nType )
	{
		case BLOCK_TYPE_I :		
			tBlockColor1 = ccc4 ( 255,   0,   0, 255 );	// ��
			tBlockColor2 = ccc4 ( 255,  92,  92, 255 );	// ��		
			break;

		case BLOCK_TYPE_O :		
			tBlockColor1 = ccc4 ( 255, 136,   0, 255 );	// ��
			tBlockColor2 = ccc4 ( 255, 178,  46, 255 );	// ��		
			break;

		case BLOCK_TYPE_S :
			tBlockColor1 = ccc4 ( 255, 213,   0, 255 );	// ��
			tBlockColor2 = ccc4 ( 255, 255,  46, 255 );	// ��		
			break;

		case BLOCK_TYPE_Z :
			tBlockColor1 = ccc4 (   0, 128,   0, 255 );	// ��
			tBlockColor2 = ccc4 (  46, 171,  46, 255 );	// ��		
			break;

		case BLOCK_TYPE_L :
			tBlockColor1 = ccc4 (   0,   0, 255, 255 ); // ��
			tBlockColor2 = ccc4 (  92,  92, 255, 255 ); // ��		
			break;

		case BLOCK_TYPE_J :
			tBlockColor1 = ccc4 (   6,  12,  86, 255 ); // ��
			tBlockColor2 = ccc4 (  96, 102, 171, 255 ); // ��
			break;

		case BLOCK_TYPE_T :
			tBlockColor1 = ccc4 ( 128,   0, 128, 255 ); // ��
			tBlockColor2 = ccc4 ( 214,  92, 214, 255 ); // ��		
			break;

		case BLOCK_TYPE_P :
			tBlockColor1 = ccc4 ( 255, 105, 180, 255 ); // ��ũ
			tBlockColor2 = ccc4 ( 255, 153, 226, 255 ); // ��ũ		
			break;

		case BLOCK_TYPE_Q :
			tBlockColor1 = ccc4 ( 189, 183, 107, 255 ); // īŰ
			tBlockColor2 = ccc4 ( 232, 224, 153, 255 ); // īŰ		
			break;

		case BLOCK_TYPE_U :
			tBlockColor1 = ccc4 ( 111, 127, 143, 255 ); // ���Ǿ�ȸ��
			tBlockColor2 = ccc4 ( 155, 170, 186, 255 ); // ���Ǿ�ȸ��		
			break;
	}

	ccColor3B	tColor = ccc3 ( 100, 100, 100 );

	// �� ���� �׸���
	CCSprite*	pRightSprite = CCSprite::create ( );
	pRightSprite->setTextureRect ( CCRect ( 0, 0, 1, BLOCK_SIZE ) );
	pRightSprite->setAnchorPoint ( ccpz );
	pRightSprite->setColor ( tColor );
	pRightSprite->setPositionX ( BLOCK_SIZE - 1 );

	// �� �ϴ� �׸���
	CCSprite*	pBottomSprite = CCSprite::create ( );
	pBottomSprite->setTextureRect ( CCRect ( 0, 0, BLOCK_SIZE, 1 ) );
	pBottomSprite->setAnchorPoint ( ccpz );
	pBottomSprite->setColor ( tColor );

	// �׶��̼� ��
	this->initWithColor
	( 
		tBlockColor1, 
		tBlockColor2, 
		ccp ( 0.5f, 0.5f ) 
	);
	this->setContentSize ( ccs ( BLOCK_SIZE, BLOCK_SIZE ) );
	this->setAnchorPoint ( ccpz );

	this->addChild ( pRightSprite );
	this->addChild ( pBottomSprite );

	return KD_TRUE;
}

// �ش� ���� ���� Tetromino�� �����ǥ ����
KDvoid Block::setTetroPosition ( KDint x, KDint y, KDint nTetroRow )
{
	m_nTetroX = x;
	m_nTetroY = y;

	// y�� ��ǥ�� �Ʒ����� 0, �������� �ö� ���� �����ϴ� ��ǥ�� ������Ű�� ���� ������
	KDint	nReversePosition = nTetroRow - 1;

	this->setPosition 
	( 
		ccp 
		( 
			(					 m_nTetroX ) * BLOCK_SIZE, 
			( nReversePosition - m_nTetroY ) * BLOCK_SIZE 
		) 
	);
}

// �ش� ���� ���� Tetromino�� ��� x ��ǥ ��ȯ
KDint Block::getTetroX ( KDvoid )
{
	return m_nTetroX;
}

// �ش� ���� ���� Tetromino�� ��� y ��ǥ ��ȯ
KDint Block::getTetroY ( KDvoid )
{
	return m_nTetroY;
}

// �ش� ���� ���� Board�� �����ǥ ����
KDvoid Block::setBoardPosition ( KDint x, KDint y )
{
	m_nBoardX = x;
	m_nBoardY = y;

	// y�� ��ǥ�� �Ʒ����� 0, �������� �ö� ���� �����ϴ� ��ǥ�� ������Ű�� ���� ������
	KDint	nReversePosition = BOARD_ROW_CNT - 1;

	this->setPosition 
	( 
		ccp 
		(
			(					 m_nBoardX ) * BLOCK_SIZE, 
			( nReversePosition - m_nBoardY ) * BLOCK_SIZE
		)
	);
}

// �ش� ���� ���� Board�� ��� x ��ǥ ��ȯ
KDint Block::getBoardX ( KDvoid )
{
	return m_nBoardX;
}

// �ش� ���� ���� Board�� ��� y ��ǥ ��ȯ
KDint Block::getBoardY ( KDvoid )
{
	return m_nBoardY;
}