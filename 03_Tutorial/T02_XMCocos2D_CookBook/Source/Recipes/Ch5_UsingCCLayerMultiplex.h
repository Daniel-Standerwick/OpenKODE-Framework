/* --------------------------------------------------------------------------
 *
 *      File            Ch5_UsingCCLayerMultiplex.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 *
 *      Created By      Nate Burba
 *      Contact         Cocos2dCookbook@gmail.com
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. 
 *      Copyright (c) 2011      COCOS2D COOKBOOK. All rights reserved. 
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

#ifndef __Ch5_UsingCCLayerMultiplex_h__
#define __Ch5_UsingCCLayerMultiplex_h__

class Ch5_UsingCCLayerMultiplex : public Recipe
{
	public :

		SCENE_FUNC ( Ch5_UsingCCLayerMultiplex );

	protected :		

		virtual KDbool		init ( KDvoid );
};

// MultiplexLayerMenu
// Our switchable layer class
class MultiplexLayerMenu : public CCLayer 
{
	public :

		static MultiplexLayerMenu*		createWithLayerNumber ( KDint nLayerNumber );

	public :

		virtual KDbool		initWithLayerNumber ( KDint nLayerNumber );

		KDvoid				goToLayer ( CCObject* pSender );
};

#endif	// __Ch5_UsingCCLayerMultiplex_h__
