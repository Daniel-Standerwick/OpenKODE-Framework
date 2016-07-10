/* --------------------------------------------------------------------------
 *
 *      File            Tetromino.h
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

#ifndef __Tetromino_h__
#define __Tetromino_h__

class Tetromino : public CCNode
{
	public :

		Tetromino ( KDvoid );

		static  Tetromino*	create ( KDint nType );

		virtual KDbool		init ( KDint nType );

	private :		

		KDvoid		makeBlock ( KDvoid );												// Tetromino ���� �� ����

		CCSize		getSize ( KDint aArray [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ] );	// Tetromino �� ���� ũ�⸦ ��ȯ

	public :

		KDvoid		rotateBlock			( KDvoid );				// �� ���� ȸ��

		KDint		getRowCnt			( KDvoid );				// Tetromino �� ���� ���� ũ�⸦ ��ȯ
		KDint		getColumnCnt		( KDvoid );				// Tetromino �� ���� ���� ũ�⸦ ��ȯ

		KDvoid		setBoardPosition	( KDint x, KDint y );	// Board ���� Tetromino ���� ��ܱ��� ��ǥ����
		KDint		getBoardX			( KDvoid );				// Board ���� X��ǥ ��ȯ
		KDint		getBoardY			( KDvoid );				// Board ���� Y��ǥ ��ȯ

	protected :

		KDint		m_aBlockArray [ BLOCK_MATRIX_CNT ][ BLOCK_MATRIX_CNT ]; // �� �迭
		KDint		m_nType;		// ��Ÿ��

		KDint		m_nRowCnt;		// Tetromino �� ���� ���� ũ��
		KDint		m_nColumnCnt;	// Tetromino �� ���� ���� ũ��
		KDint		m_nBoardX;		// Board ���� X��ǥ
		KDint		m_nBoardY; 		// Board ���� Y��ǥ
};

#endif  // __Tetromino_h__