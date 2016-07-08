/* -----------------------------------------------------------------------------------
 *
 *      File            CCEventDispatcher.cpp
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

#include "Precompiled.h"
#include "event_dispatcher/CCEventDispatcher.h"

NS_CC_BEGIN

//------------------------------------------------------------------
//
// CCEventDispatcher
//
//------------------------------------------------------------------
CCEventDispatcher::CCEventDispatcher ( KDvoid )
{
    m_bLocked    = KD_FALSE;
    m_bToAdd     = KD_FALSE;
    m_bToRemove  = KD_FALSE;

    m_pDelegates = CCArray::create ( );
    m_pDelegates->retain ( );
   
    m_pHandlersToAdd    = ccCArrayNew ( 8 );
    m_pHandlersToRemove = ccCArrayNew ( 8 );
}

CCEventDispatcher::~CCEventDispatcher ( KDvoid )
{
	CC_SAFE_RELEASE ( m_pDelegates );

	if ( m_pHandlersToAdd )
	{
		ccCArrayFree ( m_pHandlersToAdd );
	}

	if ( m_pHandlersToRemove )
	{
		ccCArrayFree ( m_pHandlersToRemove );
	}
}

KDvoid CCEventDispatcher::removeDelegate ( CCEventDelegate* pDelegate )
{
    if ( !pDelegate )
    {
        return;
    }

    if ( !m_bLocked )
    {
        forceRemoveDelegate ( pDelegate );
    }
    else
    {
        ccCArrayAppendValue ( m_pHandlersToRemove, pDelegate );
        m_bToRemove = KD_TRUE;
    }
}

KDvoid CCEventDispatcher::addDelegate ( CCEventDelegate* pDelegate )
{
    if ( !pDelegate )
    {
        return;
    }

    if ( !m_bLocked )
    {
        forceAddDelegate ( pDelegate );
    }
    else
    {
        ccCArrayAppendValue ( m_pHandlersToAdd, pDelegate );
        m_bToAdd = KD_TRUE;
    }
}

KDvoid CCEventDispatcher::forceAddDelegate ( CCEventDelegate* pDelegate )
{
    CCEventHandler*  pHandler = CCEventHandler::create ( pDelegate );

    if ( pHandler )
    {
        m_pDelegates->addObject ( pHandler );
    }
}

KDvoid CCEventDispatcher::forceRemoveDelegate ( CCEventDelegate* pDelegate )
{
    CCObject*  pObject  = KD_NULL;
    CCARRAY_FOREACH ( m_pDelegates, pObject )
    {
        CCEventHandler*  pHandler = (CCEventHandler*) pObject;
        if ( pHandler && pHandler->getDelegate ( ) == pDelegate )
        {
            m_pDelegates->removeObject ( pHandler );
            break;
        }
    }
}

KDbool CCEventDispatcher::dispatchEvent ( const KDEvent* pEvent )
{
    m_bLocked = KD_TRUE;

    if ( m_pDelegates->count ( ) > 0 )
    {
		CCEventHandler*    pHandler  = KD_NULL;
		CCEventDelegate*   pDelegate = KD_NULL;
        CCObject*          pObject   = KD_NULL;

        CCARRAY_FOREACH ( m_pDelegates, pObject )
        {
            CC_BREAK_IF ( !pObject );

            pHandler  = (CCEventHandler*) pObject;
            pDelegate = pHandler->getDelegate ( );

			pDelegate->onEvent ( pEvent ); 		
        }
    }

    m_bLocked = KD_FALSE;
    if ( m_bToRemove )
    {
        m_bToRemove = KD_FALSE;
        for ( KDuint i = 0; i < m_pHandlersToRemove->num; ++i )
        {
            forceRemoveDelegate ( (CCEventDelegate*) m_pHandlersToRemove->arr[ i ] );
        }
        ccCArrayRemoveAllValues ( m_pHandlersToRemove );
    }

    if ( m_bToAdd )
    {
        m_bToAdd = KD_FALSE;
        for ( KDuint i = 0; i < m_pHandlersToAdd->num; ++i )
        {
            forceAddDelegate ( (CCEventDelegate*) m_pHandlersToAdd->arr[ i ] );
        }
        ccCArrayRemoveAllValues ( m_pHandlersToAdd );
    }

    return KD_TRUE;
}
    
NS_CC_END