/* -----------------------------------------------------------------------------------
 *
 *      File            TestBlade.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2013 XMSoft.
 *      Copyright (c) 2011      Ngo Duc Hiep. All rights reserved.
 *
 *         http://precognitiveresearch.com      
 *
 * -----------------------------------------------------------------------------------
 * 
 *      Permission is hereby granted, free of charge, to any person obtaining a copy
 *      of this software and associated documentation files (the "Software"), to deal
 *      in the Software without restriction, including without limitation the rights
 *      to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *      copies of the Software, and to permit persons to whom the Software is
 *      furnished to do so, subject to the following conditions:
 * 
 *      The above copyright notice and this permission notice shall be included in
 *      all copies or substantial portions of the Software.
 * 
 *      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *      AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *      LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *      OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *      THE SOFTWARE.
 *
 * ----------------------------------------------------------------------------------- */ 

#ifndef __TestBlade_h__
#define __TestBlade_h__

#include "../TestBasic.h"

class TestBlade : public TestBasic
{
	public :
				 TestBlade ( KDvoid );
		virtual ~TestBlade ( KDvoid );

		CREATE_FUNC ( TestBlade );

	protected :		

		virtual KDbool			init ( KDvoid );
		virtual const KDchar*	subtitle ( KDvoid );

		virtual KDvoid			ccTouchesBegan ( CCSet* pTouches, CCEvent* pEvent );
		virtual KDvoid			ccTouchesMoved ( CCSet* pTouches, CCEvent* pEvent );
		virtual KDvoid			ccTouchesEnded ( CCSet* pTouches, CCEvent* pEvent );

	private :

		CCDictionary*			m_pDictionary;
};

#endif	// __TestBlade_h__
