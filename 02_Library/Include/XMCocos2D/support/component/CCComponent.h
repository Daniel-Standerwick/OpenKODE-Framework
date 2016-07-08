/* -----------------------------------------------------------------------------------
 *
 *      File            CCComponent.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2013 XMSoft
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
 * ----------------------------------------------------------------------------------- */ 

#ifndef __CCComponent_h__
#define __CCComponent_h__

#include "../../cocoa/CCObject.h"
#include <string>

NS_CC_BEGIN

class CCComponent : public CCObject
{
	protected :

		CCComponent ( KDvoid );

	public :

		/**
		 *  @js NA
		 *  @lua NA
		 */
		virtual ~CCComponent ( KDvoid );

		static CCComponent*		create ( KDvoid );

	public :

		virtual KDbool		init ( KDvoid );
		/**
		 *  @js NA
		 *  @lua NA
		 */
		virtual KDvoid		onEnter ( KDvoid );

		/**
		 *  @js NA
		 *  @lua NA
		 */
		virtual KDvoid		onExit ( KDvoid );
		
		virtual KDvoid		update ( KDfloat fDelta );

		virtual KDvoid		serialize ( KDvoid* r );
		
		virtual KDbool		 isEnabled ( KDvoid ) const;
		virtual KDvoid		setEnabled ( KDbool bEnable );

		virtual CCNode*		getNode ( KDvoid );
		virtual KDvoid		setNode ( CCNode* pNode );
		
	    
		const KDchar*		getName ( KDvoid ) const;
		KDvoid				setName ( const KDchar* szName );
	    
		KDvoid				setOwner ( CCNode* pOwner );
		CCNode*				getOwner ( KDvoid ) const;
	    
	protected :

		CCNode*				m_pOwner;
		std::string			m_sName;
		KDbool				m_bEnabled;
};

NS_CC_END

#endif	// __CCComponent_h__
