/* -----------------------------------------------------------------------------------
 *
 *      File            CCGLBufferedNode.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2014 XMSoft
 *      Copyright (c) 2010-2013 cocos2d-x.org
 *      Copyright (c) 2013      Zynga Inc.
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

#ifndef __CCGLBufferedNode_h__
#define __CCGLBufferedNode_h__

#include "../../ccMacros.h"
#include "../../platform/CCGL.h"

class GLBufferedNode
{
	public :

		/**
		 *	@js ctor
		 */
		GLBufferedNode ( KDvoid );

		/**
		 *	@js NA
		 *	@lua NA
		 */
		virtual ~GLBufferedNode ( KDvoid );

		/**
		 * Load the given data into this Node's GL Buffer. Needed for WebGL, as it does not support client-side arrays.
		 */
		KDvoid				setGLBufferData ( KDvoid* pBuf, GLuint uBufSize, KDint nSlot );
		KDvoid				setGLIndexData ( KDvoid* pBuf, GLuint uBufSize, KDint nSlot );

		// We allocate 4 buffer objs per node, and index into them as slots.
		#define BUFFER_SLOTS 4
		GLuint				m_aBufferObject			[ BUFFER_SLOTS ];
		GLuint				m_aBufferSize			[ BUFFER_SLOTS ];

		GLuint				m_aIndexBufferObject	[ BUFFER_SLOTS ];
		GLuint				m_aIndexBufferSize		[ BUFFER_SLOTS ];
};

#endif	// __CCGLBufferedNode_h__
