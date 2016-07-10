/* --------------------------------------------------------------------------
 *
 *      File            Board.h
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

#ifndef __Board_h__
#define __Board_h__

class Block;
class Tetromino;

class Board : public CCLayer
{
	public :

		Board ( KDvoid );

		CREATE_FUNC ( Board );

	public :

		virtual KDbool	init ( KDvoid );

		virtual KDvoid	onEnter ( KDvoid );

		KDvoid			setGameSpeed		( KDfloat fSec );		// ���Ӽӵ� ����
		KDint			newTetroType		( KDvoid );				// ���� ��Ÿ�� ����

		KDvoid			createTetromino		( KDvoid );				// �� ����
		KDbool			moveTetromino		( KDint x, KDint y );	// �� �̵�
		KDvoid			rotateTetromino		( KDvoid );				// �� ȸ��
		KDvoid			shootTetromino		( KDvoid );				// �� �����ȱ�

		KDvoid			goTetromino			( KDfloat fDelta );		// ������ �ð����� �� �����̵�
		KDvoid			stuckTetromino		( KDvoid );				// �� �̵��Ϸ�
		KDvoid			saveTetromino		( KDvoid );				// Tetromino ���� ���� ���忡 ����

		KDbool			isCollision			( KDint x, KDint y );	// Tetromino ���� ���� ���忡 �ִ� �� �浹üũ
		KDvoid			clearLine			( KDvoid );				// �ϼ��� ���� ����
		KDvoid			clearBlock			( CCObject* pSender );	// �ϼ��� ���� ���� �ִϸ��̼� �� ���� �� ����
		KDvoid			gameOver			( KDvoid );				// ���ӿ���

	protected :

		Block*			m_aBoards [ BOARD_COLUMN_CNT ] [ BOARD_ROW_CNT ]; // �׿��ִ� ������
		Tetromino*		m_pTetromino;		// �̵���� ��

		KDint			m_nNextTetroType;	// ������ Ÿ��
		KDfloat			m_nGameSpeed;		// ���Ӽӵ�
};

#endif	//__Board_h__