/* --------------------------------------------------------------------------
 *
 *      File            XMStageLoader.h
 *      Description     XMStageLoader
 *      Author          J.S Park
 *      Contact         pparkppark84@gmail.com
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (c) 2010-2013 XMSoft. All rights reserved.
 * 
 * --------------------------------------------------------------------------
 * 
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
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

#ifndef __XMStageLoader_h__
#define __XMStageLoader_h__

enum
{
	LOADERSTATE_NONE		= 0 ,
	LOADERSTATE_ROLL			,
	LOADERSTATE_WAIT
};

enum
{
	STAGESTATE_NONE			= 0 ,
	STAGESTATE_START			,
	STAGESTATE_WAIT				,
	STAGESTATE_ADDENEMY			,
	STAGESTATE_END				,
};

class XMStageLoader
{
	public :

				 XMStageLoader ( KDvoid );
		virtual ~XMStageLoader ( KDvoid );

		KDvoid				loadStage ( KDint nStage );
		KDvoid				update ( KDvoid );

		KDvoid				setSequence ( KDint nSequence );
		KDint				getSequence ( KDvoid );

		KDvoid				setLoaderState ( KDint nLoaderState );
		KDint				getLoaderState ( KDvoid );

		KDvoid				setStageState ( KDint nStageState );
		KDint				getStageState ( KDvoid );

		Object*				getObject ( KDvoid );

		Array*				m_pLoadArray;
	private :
		//Array*				m_pLoadArray;

		KDint				m_nSequence;
		KDint				m_nLoaderState;
		KDint				m_nStageState;

		Object*				m_pObject;
};

#endif  // __XMStageLoader_h__