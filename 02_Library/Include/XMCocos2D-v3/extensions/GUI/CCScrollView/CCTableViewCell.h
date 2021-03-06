/* -----------------------------------------------------------------------------------
 *
 *      File            CCTableViewCell.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2014 XMSoft.
 *      Copyright (c) 2012      cocos2d-x.org.
 *      Copyright (c) 2010      Sangwoo Im.
 *
 *          http://www.cocos2d-x.org
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
 *       all copies or substantial portions of the Software.
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

#ifndef __CCTableViewCell_h__
#define __CCTableViewCell_h__

#include "../../../2d/base_nodes/CCNode.h"
#include "CCSorting.h"

NS_CC_EXT_BEGIN

/**
 *	Abstract class for SWTableView cell node
 */
class TableViewCell: public Node, public SortableObject
{
	public :

		TableViewCell ( KDvoid ) { }

		/**
		 *	The index used internally by SWTableView and its subclasses
		 */
		KDint32				getIdx ( KDvoid );
		KDvoid				setIdx ( KDint32 nIdx );

		/**
		 *	Cleans up any resources linked to this cell and resets <code>idx</code> property.
		 */
		KDvoid				reset ( KDvoid );

		KDvoid				setObjectID ( KDint32 nIdx );
		KDint32				getObjectID ( KDvoid );

	private :

		KDint32				m_nIdx;
};

NS_CC_EXT_END

#endif	// __CCTableViewCell_h__
