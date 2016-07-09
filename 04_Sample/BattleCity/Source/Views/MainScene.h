/* --------------------------------------------------------------------------
 *
 *      File            MainScene.h
 *      Description     
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. 
 *      Copyright (c) 2012      喆 肖 (12/08/10). All rights reserved.
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

#ifndef __MainScene_h__
#define __MainScene_h__

#include "MapLayer.h"
//#import "InputLayer.h"

class MainScene : public CCLayer, public MapLayerDelegate
{    
	public :

		static CCScene*		scene ( KDint nLevel, KDint nStatus, KDint nLife );

	protected :

				 MainScene ( KDvoid );
		virtual ~MainScene ( KDvoid );

		virtual KDbool		initWithMapInformation ( KDint nLevel, KDint nStatus, KDint nLife );

	public :

		//
		// MapLayerDelegate
		//

		virtual KDvoid		gameOver ( KDvoid );

		virtual KDvoid		bornEnmey ( KDvoid );

		virtual KDvoid		changeTankLife ( KDint nLife );

	private :

		KDvoid				iconTank ( KDvoid );

		KDvoid				showLife ( KDint nLife );

		KDvoid				showLevel ( KDint nLevel );

	private :

		CCArray*			m_pIconArray;
};

#endif	// __MainScene_h__