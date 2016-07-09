/* --------------------------------------------------------------------------
 *
 *      File            Hull.cpp
 *      Description     Demo code to find contours in an image
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

KDvoid Hull ( KDint nIdx )
{
	Mat		tSrc;
	Mat		tDst;
	Mat		tGray;
	Mat		tThresh;
	KDint	nThresh;
	KDuint  i;
	RNG		tRng ( 12345 );

	std::vector <vector <Point> >  aContours;
	std::vector <Vec4i>	 aHierarchy;
	vector<vector<Point> >  tHull;

	nThresh = 34;

	// Load source image
	tSrc = imread ( "/res/image/hand.png" );

	// Convert image to gray and blur it
	cvtColor ( tSrc, tGray, CV_BGR2GRAY );
	blur ( tGray, tGray, Size ( 3, 3 ) );

	// Detect edges using Threshold
	threshold ( tGray, tThresh, nThresh, 255, THRESH_BINARY );

	// Find contours  
	findContours ( tThresh, aContours, aHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point ( 0, 0 ) );

	// Find the convex hull object for each contour
	tHull.resize ( aContours.size ( ) );
	for ( i = 0; i < aContours.size ( ); i++ )
	{ 
		convexHull ( Mat ( aContours [ i ] ), tHull [ i ], false ); 
	} 

	// Draw contours + hull results
	tDst = Mat::zeros ( tThresh.size ( ), CV_8UC3 );
	for ( i = 0; i< aContours.size ( ); i++ )
	{ 
		Scalar  tColor = Scalar ( tRng.uniform ( 0, 255 ), tRng.uniform ( 0, 255 ), tRng.uniform ( 0, 255 ) );

		drawContours ( tDst, aContours, i, tColor, 1, 8, vector<Vec4i> ( ), 0, Point ( ) ); 
		drawContours ( tDst, tHull, i, tColor, 1, 8, vector<Vec4i> ( ), 0, Point ( ) );       
	}

	g_pController->setFrame ( 1, tSrc );
	g_pController->setFrame ( 2, tDst );
}
