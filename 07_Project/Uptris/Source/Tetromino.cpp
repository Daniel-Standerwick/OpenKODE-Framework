/* --------------------------------------------------------------------------
 *
 *      File            Tetromino.cpp
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
#include "Tetromino.h"
#include "Block.h"

Tetromino::Tetromino ( KDvoid )
{
	m_nRowCnt = 0;
	m_nColumnCnt = 0;

	m_nBoardX = 0;
	m_nBoardY = 0;
}

Tetromino* Tetromino::create ( KDint nType )
{
	Tetromino*	pTetromino = new Tetromino ( );	
	if ( pTetromino && pTetromino->init ( nType ) )
	{
		pTetromino->autorelease ( );
	}
	else
	{
		CC_SAFE_DELETE ( pTetromino );
	}
	
	return pTetromino;
}; 

KDbool Tetromino::init ( KDint nType )
{
	if ( !CCNode::init ( ) )
	{
		return KD_FALSE;
	}

	m_nType = nType;

	// ��Ÿ�Կ� ���� ���迭 �ε�
	switch ( nType )
	{
		case BLOCK_TYPE_I :
		{
			KDint	aBlockI [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_I;
			kdMemcpy ( m_aBlockArray, aBlockI, sizeof ( aBlockI ) );
		}
		break;

		case BLOCK_TYPE_O :
		{
			KDint	aBlockO [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_O;
			kdMemcpy ( m_aBlockArray, aBlockO, sizeof ( aBlockO ) );
		}
		break;

		case BLOCK_TYPE_S :
		{
			KDint	aBlockS [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_S;
			kdMemcpy ( m_aBlockArray, aBlockS, sizeof ( aBlockS ) );
		}
		break;

		case BLOCK_TYPE_Z :
		{
			KDint	aBlockZ [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_Z;
			kdMemcpy ( m_aBlockArray, aBlockZ, sizeof( aBlockZ ) );
		}
		break;

		case BLOCK_TYPE_L :
		{
			KDint	aBlockL [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_L;
			kdMemcpy ( m_aBlockArray, aBlockL, sizeof ( aBlockL ) );
		}
		break;

		case BLOCK_TYPE_J :
		{
			KDint	aBlockJ [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_J;
			kdMemcpy ( m_aBlockArray, aBlockJ, sizeof ( aBlockJ ) );
		}
		break;

		case BLOCK_TYPE_T :
		{
			KDint	aBlockT [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_T;
			kdMemcpy ( m_aBlockArray, aBlockT, sizeof ( aBlockT ) );
		}
		break;

		case BLOCK_TYPE_P :
		{
			KDint	aBlockP [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_P;
			kdMemcpy ( m_aBlockArray, aBlockP, sizeof ( aBlockP ) );
		}
		break;

		case BLOCK_TYPE_Q :
		{
			KDint	aBlockQ [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_Q;
			kdMemcpy ( m_aBlockArray, aBlockQ, sizeof ( aBlockQ ) );
		}
		break;

		case BLOCK_TYPE_U :
		{
			KDint	aBlockU [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] = BLOCK_ARRAY_U;
			kdMemcpy ( m_aBlockArray, aBlockU, sizeof ( aBlockU ) );
		}
		break;
	}
	
	makeBlock ( );

	return KD_TRUE;
}

// Tetrimino ���� ���� ���ǵ� ����� ����
KDvoid Tetromino::makeBlock ( KDvoid )
{
	// �� ������ ����
	CCSize		tSize = this->getSize ( m_aBlockArray );
	m_nRowCnt = tSize.cy;
	m_nColumnCnt = tSize.cx;

	KDint		nBlockCnt = 0;	// �߰� �� ����
	for ( KDint y = 0; y < m_nRowCnt; y++ )
	{
		for ( KDint x = 0; x < m_nColumnCnt; x++ )
		{
			// �� �����
			if ( m_aBlockArray [ y ][ x ] == 1 )
			{
				// �� �����Ͽ� ��ġ����
				Block*		pBlock = Block::create ( m_nType );
				pBlock->setTetroPosition ( x, y, m_nRowCnt );
				this->addChild ( pBlock );

				nBlockCnt++;				// �� ���� ����
				if ( m_nRowCnt < y + 1 )	
				{
					m_nRowCnt = y + 1;		// �� ���� ����
				}

				if ( m_nColumnCnt < x + 1 )
				{
					m_nColumnCnt = x + 1;	// �� ���� ����
				}
			}

			if ( nBlockCnt == BLOCK_MAX_CNT )
			{
				break;
			}
		}

		if ( nBlockCnt == BLOCK_MAX_CNT )
		{
			break;
		}
	}
}

// �� ���� ȸ��
KDvoid Tetromino::rotateBlock ( KDvoid )
{
	// �迭 ȸ��
	KDint	aTemp [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ];
	for ( KDint y = 0; y < BLOCK_MATRIX_CNT; y++ )
	{
		// ȸ�� �� Y��ǥ
		KDint	nRotateY = m_nColumnCnt - y - 1;

		for ( KDint x = 0; x < BLOCK_MATRIX_CNT; x++ )
		{
			// ȸ�� �� ��ǥ�� ������ �迭���϶�
			if ( nRotateY >= 0 && nRotateY < BLOCK_MATRIX_CNT )
			{
				aTemp [ y ][ x ] = m_aBlockArray [ x ][ nRotateY ];
			}
			// ȸ�� �� ��ǥ�� ������ �迭���϶� 0���� �ʱ�ȭ
			else
			{
				aTemp [ y ][ x ] = 0;
			}
		}
	}
	kdMemcpy ( m_aBlockArray, aTemp, sizeof ( m_aBlockArray ) ); 

	// �� ���� �� ���� ����
	removeAllChildrenWithCleanup ( KD_TRUE );

	makeBlock ( );
}

// Tetromino �� ���� ũ�⸦ ��ȯ
CCSize Tetromino::getSize ( KDint aArray [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] )
{
	KDint	nMinX = 100, nMaxX = 0, nMinY = 100, nMaxY = 0;

	for ( KDint y = 0; y < BLOCK_MATRIX_CNT; y++ )
	{
		for ( KDint x = 0; x < BLOCK_MATRIX_CNT; x++ )
		{
			if( aArray [ y ][ x ] == 1 )
			{
				if ( nMinX > x )	nMinX = x;
				if ( nMaxX < x )	nMaxX = x;
				if ( nMinY > y )	nMinY = y;
				if ( nMaxY < y )	nMaxY = y;
			}
		}
	}
	return CCSizeMake ( nMaxX - nMinX + 1, nMaxY - nMinY + 1 );
}

// Tetromino �� ���� ���� ũ�⸦ ��ȯ
KDint Tetromino::getRowCnt ( KDvoid )
{
	return m_nRowCnt;
}

// Tetromino �� ���� ���� ũ�⸦ ��ȯ
KDint Tetromino::getColumnCnt ( KDvoid )
{
	return m_nColumnCnt;
}

// Board ���� Tetromino ���� ��ܱ��� ��ǥ���� (Board ���� ������ǥ)
KDvoid Tetromino::setBoardPosition ( KDint x, KDint y )
{
	CCLOG ( "Tetromino setBoardPosition: %d, %d", x, y );

	m_nBoardX = x;
	m_nBoardY = y;

	// ���� ���� ���� �������� �Ѿ���� ���� �������� ��ġ ����
	if ( m_nBoardX < 0 )
	{
		m_nBoardX = 0;
	}
	// ���� ���� ���� ���������� �Ѿ���� ���� �������� ��ġ ����
	else if ( m_nBoardX + getColumnCnt ( ) > BOARD_COLUMN_CNT )
	{
		m_nBoardX = BOARD_COLUMN_CNT - getColumnCnt ( );
	}

	// ��� ���� ���� �������� �Ѿ���� ���� �������� ��ġ ����
	if ( m_nBoardY < 0 )
	{
		m_nBoardY = 0;
	}
	// �ϴ� ���� ���� �Ʒ������� �Ѿ���� ���� �������� ��ġ ����
	else if ( m_nBoardY + getRowCnt ( ) > BOARD_ROW_CNT )
	{
		m_nBoardY = BOARD_ROW_CNT - getRowCnt ( );
	}

	// y�� ��ǥ�� �Ʒ����� 0, �������� �ö� ���� �����ϴ� ��ǥ�� ������Ű�� ���� ������
	KDint nReversePosition = BOARD_ROW_CNT - getRowCnt ( );

	setPosition 
	( 
		ccp 
		( 
			(					 m_nBoardX ) * BLOCK_SIZE, 
			( nReversePosition - m_nBoardY ) * BLOCK_SIZE
		) 
	);
}

// Board ���� ���� X��ǥ
KDint Tetromino::getBoardX ( KDvoid )
{
	return m_nBoardX;
}

// Board ���� ���� Y��ǥ
KDint Tetromino::getBoardY ( KDvoid )
{
	return m_nBoardY;
}
