/* --------------------------------------------------------------------------
 *
 *      File            Block.h
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

#ifndef __Block_h__
#define __Block_h__

class Block : public CCLayerGradient
{
	public :

		Block ( KDvoid );

		static  Block*	create ( KDint nType );

		virtual KDbool	init   ( KDint nType );

	public :

		KDvoid			setTetroPosition	( KDint x, KDint y, KDint nTetroRow );	// Tetromino ���� ���� ��ġ�� ����
		KDint			getTetroX			( KDvoid );								// Tetromino ���� ���� X��ǥ ��ȯ
		KDint			getTetroY			( KDvoid );								// Tetromino ���� ���� Y��ǥ ��ȯ

		KDvoid			setBoardPosition	( KDint x, KDint y );					// Board ���� ���� ��ġ�� ����
		KDint			getBoardX			( KDvoid );								// Board ���� X��ǥ ��ȯ
		KDint			getBoardY			( KDvoid );								// Board ���� Y��ǥ ��ȯ

	protected :
	
		KDint			m_nTetroX;	// Tetromino ���� X��ǥ
		KDint 			m_nTetroY;	// Tetromino ���� Y��ǥ
	
		KDint 			m_nBoardX;	// Board ���� X��ǥ
		KDint 			m_nBoardY;	// Board ���� Y��ǥ
};

#endif	//__Block_h__