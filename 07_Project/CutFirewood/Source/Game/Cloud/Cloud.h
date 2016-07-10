/* -----------------------------------------------------------------------------------
 *
 *      File            Cloud.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2013 XMSoft  
 *      Copyright (c) 2011      FOWCOM. All rights reserved.
 *
 * -----------------------------------------------------------------------------------
 * 
 *     Permission is hereby granted, free of charge, to any person obtaining a copy
 *     of this software and associated documentation files (the "Software"), to deal
 *     in the Software without restriction, including without limitation the rights
 *     to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *     copies of the Software, and to permit persons to whom the Software is
 *     furnished to do so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included in
 *     all copies or substantial portions of the Software.
 *     
 *     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *     THE SOFTWARE.
 *
 * ----------------------------------------------------------------------------------- */ 

#ifndef __Cloud_h__
#define __Cloud_h__

#include "Scene/JBase/JBaseScene.h"

class cSprite;

class cCloud : public Object
{
	private :

		// class
		struct sCloudObj
		{
			public :
				cSprite*		pSpr;
				Point			tPoint;
				Point			tPointAdd;
				KDdouble		dStartDelay;
				KDdouble		dTime;
				KDdouble		dLeftTime;
				KDfloat			fScale;
				KDfloat			fScaleAdd;
				KDfloat			fRotation;
				KDfloat			fRotationAdd;
		};
	
	public :

		// init
		cCloud ( JBaseScene* pScene );
		virtual ~cCloud ( KDvoid );
	
		// add
		KDvoid			add ( KDint z, KDdouble dStartDelay, Point tPoint, Point tPointAdd, KDdouble dLeftTime, KDfloat fScale, KDfloat fScaleAdd, KDfloat fRotation, KDfloat fRotationAdd, KDbool bIsFlipX );

		// get
		KDint			getCloudCount ( KDvoid );
	
		// update
		KDvoid			update ( KDdouble dLeftTime );

	private :

		// scene
		JBaseScene*					m_pScene;
	
		// sprite
		cSprite*					m_pSprCloudBackup;	
	
		// clouds
		std::vector<sCloudObj>		m_aClouds;
};

#endif	// __Cloud_h__