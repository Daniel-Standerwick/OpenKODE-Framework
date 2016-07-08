/* --------------------------------------------------------------------------
 *
 *      File            ios_locale.m
 *      Description     Locale specific functions
 *      Author          Y.H Mun
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

#include "../kd_library.h"

#import  <Foundation/Foundation.h>

static KDchar      l_locale[64] = "";

const KDchar* xmPlatformGetLocale ( KDvoid )
{
	id           pool   = [[NSAutoreleasePool alloc] init];	
	NSString*    locale = [[NSLocale currentLocale] localeIdentifier];	
		
	if ( [locale length] )
	{
		strcpy ( l_locale, [locale UTF8String] );	
	}
	else
	{
		strcpy ( l_locale, "unknown" );
	}
	 	
	[pool release];
	
	return l_locale;
}

