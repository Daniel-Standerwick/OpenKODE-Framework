/* --------------------------------------------------------------------------
 *
 *      File            TBCredits.h
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

#ifndef __TBCredits_h__
#define __TBCredits_h__

class TBCredits : public CCLayer
{
	public :

		SCENE_FUNC ( TBCredits );

	public :

		virtual KDbool		init ( KDvoid );

		KDvoid				backClicked ( CCObject* pSender );
		
		KDvoid				crowdsClicked ( CCObject* pSender );
};

#endif	// __TBCredits_h__
