/* --------------------------------------------------------------------------
 *
 *      File            GameLayer.h
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

#ifndef __GameLayer_h__
#define __GameLayer_h__

class Board;
class Tetromino;

class GameLayer : public CCLayer
{
	public :

		GameLayer ( KDvoid );

		CREATE_FUNC ( GameLayer );

	public :

		virtual KDbool		init			( KDvoid );

		virtual KDvoid		onEnter			( KDvoid );								// ȭ�����Խ�

		virtual KDvoid		onEvent			( const KDEvent* pEvent );				// �̺�Ʈ���� (��Ŀ��)

		virtual KDvoid		ccTouchesBegan	( CCSet* pTouches, CCEvent* pEvent );	// ��ġ �Է� ����
		virtual KDvoid		ccTouchesEnded	( CCSet* pTouches, CCEvent* pEvent );	// ��ġ ���� ����

		virtual KDvoid		keyPressed		( KDint nId );							// Ű���� �Է� ����
		virtual KDvoid		keyReleased		( KDint nId );							// Ű���� ���� ����
		
		KDvoid				onMenuCallback	( CCObject* pSender );	// �޴� ��ġ�� �ݹ�
		KDvoid				onNextTetromino ( KDint nType );		// ������� ����
		KDvoid				onPressedButton	( KDfloat fDelta );		// �̵�Ű�� ��������
		KDvoid				onClearLine		( KDint nCount );		// ������ ���� �ݹ�
		KDvoid				onGameOver		( KDvoid );				// ���ӿ��� �ݹ�

		KDvoid				shakeScreen		( KDvoid );				// ȭ�� ����
		KDvoid				showLevelUpAni	( KDvoid );				// ������ �̹��� ����
		KDvoid				hideLevelUpAni	( KDfloat fDelta );		// ������ �̹��� ����

		KDint				getLevel		( KDvoid );				// ���ӷ��� ��ȯ

	protected:

		Board*				m_pBoard;			// ����
		Tetromino*			m_pNextTetromino;	// ������
		KDint				m_nTouchedTarget;	// ��ġ���δ��

		CCLabelTTF*			m_pLevel;			// ���� ���̺�
		CCLabelTTF*			m_pScore;			// ���� ���̺�
		CCLabelTTF*			m_pBlockLine;		// ���Ŷ��� ���̺�
		
		CCSprite*			m_pVibrateCursor;	// ���� ��� ��ư
		CCSprite*			m_pSoundCursor;		// �Ҹ� ��� ��ư

		CCSprite*			m_pLevelupSprite;	// ������ �̹���
		CCAnimation*		m_pLevelupAnimation;// ������ �ִϸ��̼�

		KDint				m_nLevelValue;		// ����
		KDint				m_nScoreValue;		// ����
		KDint				m_nBlockLineValue;	// ���Ŷ���

		KDbool				m_bIsSound;			// �Ҹ� ����
		KDbool				m_bIsVibrate;		// ���� ����
};

#endif	//__GameLayer_h__