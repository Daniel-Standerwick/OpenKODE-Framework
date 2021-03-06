/* -----------------------------------------------------------------------------------
 *
 *      File            CCControlLoader.h
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

#ifndef __CCControlLoader_h__
#define __CCControlLoader_h__

#include "CCNodeLoader.h"
#include "../../extensions/GUI/CCControlExtension/CCControl.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class ControlLoader : public NodeLoader
{
	public :

		/**
		 *	@js NA
		 *	@lua NA
		 */
		virtual ~ControlLoader ( KDvoid ) { }

	protected :

		CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD ( cocos2d::extension::Control );

		virtual KDvoid		onHandlePropTypeBlockControl ( cocos2d::Node* pNode, cocos2d::Node* pParent, const KDchar* pPropertyName, BlockControlData * pBlockControlData, CCBReader* ccbReader );
		virtual KDvoid		onHandlePropTypeCheck		 ( cocos2d::Node* pNode, cocos2d::Node* pParent, const KDchar* pPropertyName, KDbool pCheck, CCBReader* ccbReader );
};

}

#endif	// __CCControlLoader_h__
