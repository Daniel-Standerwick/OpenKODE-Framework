/* --------------------------------------------------------------------------
 *
 *      File            APSGraphic.h
 *      Author          Young-Hwan Mun
 * 
 * --------------------------------------------------------------------------
 *   
 *      Copyright (c) 2012 ArtPig Software LLC
 *
 *         http://www.artpigsoft.com  
 *
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. All rights reserved.
 * 
 *      Contact Email: xmsoft77@gmail.com
 * 
 * --------------------------------------------------------------------------
 * 
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or ( at your option ) any later version.
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

#ifndef __APSGraphic_h__
#define __APSGraphic_h__

#include "APSResource.h"
#include "../../cocoa/CCAffineTransform.h"

NS_APS_BEGIN

class APSGraphicAction;
class APSAction;
class APSResourceProvider;
class APSLinkerAction;
class APSGraphicGroup;

extern const KDuint  kAPSGraphic_defaultTouchOption;

/**
 *	@brief	APSGraphic has graphic information and creates CCNode object.
 */
class  APSGraphic : public APSResource
{ 
	public :

		/** 
		 *	Constructor of APSGraphic. If 'properties' parameter is not NULL, the 
		 *	instance is initialized by the properties.
		 */
		APSGraphic ( APSDictionary* pProperties = KD_NULL );
		virtual ~APSGraphic ( KDvoid );

		APS_CLASS_NAME ( APSGraphic );
	    
	public :

		/** Initializes this APSGraphic object with given properties. */
		virtual KDbool   initWithProperties ( APSDictionary* pProperties );
	        
		/** 
		 *	Resets properties of CCNode object to initial state. resetNode ( ) is just
		 *	an alias of initNode ( ).
		 */
		KDbool  resetNode ( KDvoid ) { return this->initNode ( ); }
	    
		/** 
		 *	Initializes CCNode objects in APSGraphic. initNode ( ) can be called 
		 *	multiple times to reset CCNode objects' states back to original.
		 */
		virtual KDbool  initNode ( KDvoid );

		/** Returns CCNode generated by this APSGraphic. */
		virtual CCNode*  getNode ( KDvoid );
	    
		/** 
		 *	Returns parent graphic group that contains this graphic.
		 *	This must be called after setting parentIndex property.
		 */
		virtual APSGraphic*  getParent ( KDvoid );
	        
		/** 
		 *	Updates accOpacity, accOpacity value propagates to the all descendant
		 *	graphics. Opacities are multiplied from parent to children thoughout 
		 *	graphics hierarchy. For performance reason, updateAccOpacity ( ) should
		 *	be called as minimum times as possible.
		 */
		virtual KDvoid  updateAccOpacity ( KDvoid );

		/** Returns origin ( left, bottom ) position relative to parent coordinations */
		CCPoint  getOriginPosition ( KDvoid ) const;
	        
		virtual CCAffineTransform  getNodeToSymbolTransform ( KDvoid );
		virtual CCAffineTransform  getSymbolToNodeTransform ( KDvoid );
	    
		APSResourceArray*  getLinkersForEvent ( APSEventType uType ) const;
		APSResourceArray*  getLinkersForEventWithCreation ( APSEventType uType );
	    
		/** 
		 *	Compres this graphic with a given graphic. Returns true if this graphic
		 *	is displayed above the compared graphic. 
		 */
		KDbool   isAbove ( APSGraphic* pGraphic ) { return m_fLevel < pGraphic->getLevel ( ); }
	    
		KDbool   isNodeVisible ( KDvoid );
	    
		CCPoint  convertPositionFromParentNode ( const CCPoint& tPosition );	   
	    
		/** If retainsTouch is true, graphic receives all following touch events ( touch moved, touch ended, and touch cancelled ) once touch begin event is on this graphic. */
		KDbool   getRetainsTouch ( KDvoid ) const;
		KDvoid   setRetainsTouch ( KDbool bRetainsTouch );
	    
		/** If acceptsTouchMoveEnter is true, this graphic receives 'touch moved', 'touch ended', and 'touch cancelled' events that have begun in external position. */
		KDbool   getAcceptsTouchMoveEnter ( KDvoid ) const;
		KDvoid   setAcceptsTouchMoveEnter ( KDbool bAcceptsMoveEnter );
	    
		/** If acceptsTouchOnlyVisible is true, graphic receives touch events only when it is visible in the screen. */
		KDbool   getAcceptsTouchOnlyVisible ( KDvoid ) const;
		KDvoid   setAcceptsTouchOnlyVisible ( KDbool bAcceptsTouchOnlyVisible );

	protected :

		virtual CCNode*  createNode ( KDvoid );

		/** An index of parent graphic group that contains this graphic. */
		APS_SYNTHESIZE_WITH_KEY ( APSIndex, m_uParentIndex, ParentIndex );
		APS_SYNTHESIZE_WITH_KEY ( KDfloat , m_fLevel, Level );
	        
		APS_SYNTHESIZE_WITH_KEY ( CCPoint, m_tPosition	 , Position    );
		APS_SYNTHESIZE_WITH_KEY ( CCSize , m_tSize		 , Size		   );
		APS_SYNTHESIZE_WITH_KEY ( CCPoint, m_tAnchor	 , Anchor  	   );
		APS_SYNTHESIZE_WITH_KEY ( CCPoint, m_tScale		 , Scale	   );
		APS_SYNTHESIZE_WITH_KEY ( KDfloat, m_fRotation	 , Rotation    );
		APS_SYNTHESIZE_WITH_KEY ( KDuint , m_uOpacity	 , Opacity	   );
		APS_SYNTHESIZE_WITH_KEY ( KDbool , m_bVisible	 , Visible	   );
		APS_SYNTHESIZE_WITH_KEY ( KDuint , m_uTouchOption, TouchOption );
	    
		/** 
		 *	runningOpacity is changed by APSCCFadeChildrenTo during fade action is
		 *	performed. After runningOpacity property is changed, updateAccOpacity ( )
		 *	should be called to eventually set accOpacity property.
		 */
		APS_SYNTHESIZE ( KDuint, m_uRunningOpacity, RunningOpacity );
		APS_SYNTHESIZE ( KDuint, m_uAccOpacity, AccOpacity );
	    
		APS_PROPERTY_KEY ( TouchBeginEventLinkers );
		APS_PROPERTY_KEY ( TouchMovedEventLinkers );
		APS_PROPERTY_KEY ( TouchEndEventLinkers   );

	protected :

		CCNode*							m_pNode;
		APSGraphic*						m_pParent;
		std::vector<APSResourceArray*>*	m_pTouchEventLinkers;

		friend class APSGraphicGroup;
};

NS_APS_END

#endif	// __APSGraphic_h__
