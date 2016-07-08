/* -----------------------------------------------------------------------------------
 *
 *      File            Animation.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2014 XMSoft
 *      Copyright (c) 2010-2013 cocos2d-x.org
 *      Copyright (c) 2008-2010 Ricardo Quesada
 *      Copyright (c) 2011      Zynga Inc.
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

#ifndef __Animation_h__
#define __Animation_h__

#include "../../base/CCArray.h"
#include "../../base/CCDictionary.h"
#include "../../base/CCGeometry.h"
#include "../sprite_nodes/CCSpriteFrame.h"

NS_CC_BEGIN

class Texture2D;
class SpriteFrame;

/**
 *	@addtogroup sprite_nodes
 *	@{
 */

/** 
 *	AnimationFrame
 *	A frame of the animation. It contains information like:
 *	   - sprite frame name
 *	   - # of delay units.
 *	   - offset
 *
 *	@since v2.0
 */
class CC_DLL AnimationFrame : public Object, public Clonable
{
	public :

		/**
		 *	@js ctor
		 */
		AnimationFrame ( KDvoid );

		/**
		 *	@js NA
		 *	@lua NA
		 */
		virtual ~AnimationFrame ( KDvoid );

		/** initializes the animation frame with a spriteframe, number of delay units and a notification user info */
		KDbool						initWithSpriteFrame ( SpriteFrame* pSpriteFrame, KDfloat fDelayUnits, Dictionary* pUserInfo );

		SpriteFrame*				getSpriteFrame ( KDvoid ) const { return m_pSpriteFrame; }
    
		KDvoid						setSpriteFrame ( SpriteFrame* pFrame )
		{
			CC_SAFE_RETAIN ( pFrame );
			CC_SAFE_RELEASE ( m_pSpriteFrame );
			m_pSpriteFrame = pFrame;
		}

		/** Gets the units of time the frame takes */
		KDfloat						getDelayUnits ( KDvoid ) const { return m_fDelayUnits; }
    
		/** Sets the units of time the frame takes */ 
		KDvoid						setDelayUnits ( KDfloat fDelayUnits ) { m_fDelayUnits = fDelayUnits; }
    
		/**
		 *	@brief Gets user infomation
		 *	A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcast.
		 */
		Dictionary*					getUserInfo ( KDvoid ) const { return m_pUserInfo; }
    
		/** Sets user infomation */
		KDvoid						setUserInfo ( Dictionary* pUserInfo )
		{
			CC_SAFE_RETAIN ( pUserInfo );
			CC_SAFE_RELEASE ( m_pUserInfo );
			m_pUserInfo = pUserInfo;
		}
    
		// Overrides
		virtual AnimationFrame*		clone ( KDvoid ) const override;

	protected :

		/** SpriteFrameName to be used */
		SpriteFrame*				m_pSpriteFrame;

		/**  how many units of time the frame takes */
		KDfloat						m_fDelayUnits;

		/**  A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcast. */
		Dictionary*					m_pUserInfo;
};

/** 
 *	A Animation object is used to perform animations on the Sprite objects.
 *
 *	The Animation object contains AnimationFrame objects, and a possible delay between the frames.
 *	You can animate a Animation object by using the Animate action. Example:
 *
 *	@code
 *	    sprite->runAction(Animate::create(animation));
 *	@endcode
 *
 */
class CC_DLL Animation : public Object, public Clonable
{
	public :

		/** 
		 *	Creates an animation
		 *	@since v0.99.5
		 */
		static Animation*			create ( KDvoid );

		/** 
		 *	Creates an animation with an array of SpriteFrame and a delay between frames in seconds.
		 *	The frames will be added with one "delay unit".
		 *	@since v0.99.5
		 */
		static Animation*			createWithSpriteFrames ( Array* pArrayOfSpriteFrameNames, KDfloat fDelay = 0.0f );

		/**
		 *	Creates an animation with an array of AnimationFrame, the delay per units in seconds and and how many times it should be executed.
		 *	@since v2.0
		 *	@js NA
		 */
		static Animation*			create ( Array* pArrayOfAnimationFrameNames, KDfloat fDelayPerUnit, KDuint uLoops = 1 );
		
		/**
		 *	@js ctor
		 */
		Animation ( KDvoid );

		/**
		 *	@js NA
		 *	@lua NA
		 */
		virtual ~Animation ( KDvoid );

		KDbool						init ( KDvoid );

		/** 
		 *	Initializes a Animation with frames and a delay between frames
		 *	@since v0.99.5
		 */
		KDbool						initWithSpriteFrames ( Array* pFrames, KDfloat fDelay = 0.0f );

		/**
		 *	Initializes a Animation with AnimationFrame
		 *	@since v2.0
		 */
		KDbool						initWithAnimationFrames ( Array* pArrayOfAnimationFrames, KDfloat fDelayPerUnit, KDuint uLoops );

		/** 
		 *	Adds a SpriteFrame to a Animation.
		 *	The frame will be added with one "delay unit".
		 */
		KDvoid						addSpriteFrame ( SpriteFrame* pFrame );

		/**
		 *	Adds a frame with an image filename. Internally it will create a SpriteFrame and it will add it.
		 *	The frame will be added with one "delay unit".
		 *	Added to facilitate the migration from v0.8 to v0.9.
		 */
		KDvoid						addSpriteFrameWithFile ( const KDchar* pFilename );

		/** 
		 *	Adds a frame with a texture and a rect. Internally it will create a SpriteFrame and it will add it.
		 *	The frame will be added with one "delay unit".
		 *	Added to facilitate the migration from v0.8 to v0.9.
		 */
		KDvoid						addSpriteFrameWithTexture ( Texture2D* pTexture, const Rect& tRect );

		/** Gets the total Delay units of the Animation. */
		KDfloat						getTotalDelayUnits ( KDvoid ) const { return m_fTotalDelayUnits; }
    
		/** Sets the delay in seconds of the "delay unit" */
		KDvoid						setDelayPerUnit ( KDfloat fDelayPerUnit ) { m_fDelayPerUnit = fDelayPerUnit; }
    
		/** Gets the delay in seconds of the "delay unit" */
		KDfloat						getDelayPerUnit ( KDvoid ) const { return m_fDelayPerUnit; }
    
		/** Gets the duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit */
		KDfloat						getDuration ( KDvoid ) const;
    
		/** Gets the array of AnimationFrames */
		Array*						getFrames ( KDvoid ) const { return m_pFrames; }
    
		/** Sets the array of AnimationFrames */
		KDvoid						setFrames ( Array* pFrames )
		{
			CC_SAFE_RETAIN ( pFrames );
			CC_SAFE_RELEASE ( m_pFrames );
			m_pFrames = pFrames;
		}
    
		/** Checks whether to restore the original frame when animation finishes. */
		KDbool						getRestoreOriginalFrame ( KDvoid ) const { return m_bRestoreOriginalFrame; }
    
		/** Sets whether to restore the original frame when animation finishes */
		KDvoid						setRestoreOriginalFrame ( KDbool bRestoreOriginalFrame ) { m_bRestoreOriginalFrame = bRestoreOriginalFrame; }
    
		/** Gets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... */
		KDuint						getLoops ( KDvoid ) const { return m_uLoops; }
    
		/** Sets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... */
		KDvoid						setLoops ( KDuint uLoops ) { m_uLoops = uLoops; }
    
		// overrides
		virtual Animation*			clone ( KDvoid ) const override;

	protected :

		/** total Delay units of the Animation. */
		KDfloat						m_fTotalDelayUnits;

		/** Delay in seconds of the "delay unit" */
		KDfloat						m_fDelayPerUnit;

		/** duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit */
		KDfloat						m_fDuration;

		/** array of AnimationFrames */
		Array*						m_pFrames;

		/** whether or not it shall restore the original frame when the animation finishes */
		KDbool						m_bRestoreOriginalFrame;

		/** how many times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... */
		KDuint						m_uLoops;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif	// __Animation_h__
