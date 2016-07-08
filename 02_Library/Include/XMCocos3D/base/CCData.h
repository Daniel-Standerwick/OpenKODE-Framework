/* -----------------------------------------------------------------------------------
 *
 *      File            CCData.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2014 XMSoft
 *      Copyright (c) 2010-2013 cocos2d-x.org
 *
 *         http://www.cocos2d-x.org   
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
 * --------------------------------------------------------------------------------- */ 

#ifndef __CCData_h__
#define __CCData_h__

#include "../platform/CCPlatformMacros.h"
#include "CCObject.h"

NS_CC_BEGIN

class CC_DLL Data : public Object
{
	public :

		/**
		 *	@js NA
		 *	@lua NA
		 */
		Data ( KDubyte* pBytes, const KDsize uSize );

		/**
		 *	@js NA
		 *	@lua NA
		 */
		Data ( Data* pData );

		/**
		 *	@js NA
		 *	@lua NA
		 */
		~Data ( KDvoid );

		/**
		 *	@js NA
		 *	@lua NA
		 */
		static Data*		create ( KDubyte* pBytes, const KDsize uSize )
		{
			Data*	pRet = new Data ( pBytes, uSize );
			if ( pRet )
			{
				pRet->autorelease ( );
			}
			return pRet;
		}    

		/**
		 *	@js NA
		 *	@lua NA
		 */
		KDubyte*			getBytes ( KDvoid ) const;

		/**
		 *	@js NA
		 *	@lua NA
		 */
		KDsize				getSize ( KDvoid ) const;
    
		/** 
		 *	override functions
		 *	@js NA
		 *	@lua NA
		 */
		virtual KDvoid		acceptVisitor ( DataVisitor& tVisitor ) { tVisitor.visit ( this ); }

	private :

		KDubyte*			m_pBytes;
		KDsize				m_uSize;
};

NS_CC_END

#endif	// __CCData_h__
