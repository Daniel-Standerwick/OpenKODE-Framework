/* --------------------------------------------------------------------------
 *
 *      File            CannyDetector.cpp
 *      Description     Sample code showing how to detect edges using 
 *                      the Canny Detector
 *      Author          OpenCV team, Y.H Mun
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (C) 2010-2012 XMSoft. All rights reserved.
 * 
 *      Contact Email: xmsoft77@gmail.com 
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

#include "Precompiled.h"
#include "../Controller.h"

KDvoid CannyDetector ( KDint nIdx )
{
	Mat		tSrc;
	Mat		tDst;
	Mat		tGray;
	Mat     tEdge;

	KDint	nThreshold;
	KDint	nRatio;
	KDint	nSize;

	nThreshold	= 100;	
	nRatio		= 3;
	nSize		= 3;

	// Load the source image
	tSrc = imread ( "/res/image/building.png" ); 
	tDst.create ( tSrc.size ( ), tSrc.type ( ) );

	// Convert it to gray
	cvtColor ( tSrc, tGray, CV_RGB2GRAY );

    // Reduce noise with a kernel 3x3
    blur ( tGray, tEdge, Size ( 3, 3 ) );

    // Canny detector
    Canny ( tEdge, tEdge, nThreshold, nThreshold * nRatio, nSize );

    /// Using Canny's output as a mask, we display our result
    tDst = Scalar::all ( 0 );
	tSrc.copyTo ( tDst, tEdge );

	g_pController->setFrame ( 1, tSrc );
	g_pController->setFrame ( 2, tDst );
}

