/* --------------------------------------------------------------------------
 *
 *      File            MyRanking.h
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

#ifndef __MyRanking_h__
#define __MyRanking_h__

class MyRanking : public CCLayer
{
	public :

		CREATE_FUNC ( MyRanking );

	protected :

		virtual KDbool		init						( KDvoid );

		KDvoid				onButtonClick				( CCObject*	pSender );				// �ڷΰ��� ��ư
		KDvoid				onHttpRequestCompleted	    ( CCNode* pSender, KDvoid* pData );	// ���� ���ſϷ�

		KDvoid				selectData					( KDfloat fDelta );					// ���� ��û
		KDvoid				decoding					( std::string sData );				// ���� ���º�ȯ

	protected :

		CCProgressTimer*	m_pLoading;		// �ε��̹���
};

#endif	//__MyRanking_h__