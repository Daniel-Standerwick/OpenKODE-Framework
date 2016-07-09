/* --------------------------------------------------------------------------
 *
 *      File            TBGameState.h
 *
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 *
 *      Created By      Rana Hammad Hussain on 04/22/11
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft.
 *      Copyright (c) 2011      Azosh & Co. All rights reserved.
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

#ifndef __TBGameState_h__
#define __TBGameState_h__

#define GameState			TBGameState::sharedGameState ( )

class TBGameState : public CCObject 
{
	public :

		static TBGameState*		sharedGameState ( KDvoid );

		static KDvoid			purgedGameState ( KDvoid );

	public :

		KDbool					init ( KDvoid );

		KDvoid					loadState ( KDvoid );

		KDvoid					saveState ( KDvoid );

		KDvoid					playGamemusic ( KDvoid );

		KDvoid					stopGamemusic ( KDvoid );
		
		KDvoid					playClick ( KDvoid );
		
		KDvoid					playBallHit ( KDvoid );

	public :

		CC_SYNTHESIZE_PASS_BY_REF ( CCSize , m_tScreenSize  , ScreenSize );
		CC_SYNTHESIZE_PASS_BY_REF ( CCPoint, m_tScreenCenter, ScreenCenter );		

		CC_SYNTHESIZE_BOOL ( m_bFirstTimeRunning, FirstTimeRunning );

		CC_SYNTHESIZE_BOOL ( m_bGameSceneRunning, GameSceneRunning );

		CC_SYNTHESIZE ( KDint, m_nSelectedCharacterIndex, SelectedCharacterIndex );
};

#endif	// __TBGameState_h__
