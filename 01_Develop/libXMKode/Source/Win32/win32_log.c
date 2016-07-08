/* --------------------------------------------------------------------------
 *
 *      File            win32_log.c
 *      Description     Output a log message.
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

// xmPlatformLogMessage : Output a log message in platform specific.
KDvoid xmPlatformLogMessage ( const KDchar* msg )
{
	TCHAR*      tmsg = 0;
	KDchar*     msg2 = 0;
	KDuint      len  = 0;
	KDuint	    tlen = 0;
	
	if ( ( len = strlen ( msg ) ) > 0 )
	{
		if ( strcmp ( &msg[ len - 1 ], "\n" ) )
		{
			msg2 = malloc ( len + 2 );
			strcpy ( msg2, msg );
			strcat ( msg2, "\n" );
		}
		else
		{
			msg2 = (KDchar *) msg;
		}

		if ( XM_SET_TSTR ( tmsg, (KDchar *) msg2 ) )
		{
			OutputDebugString ( tmsg );
			KD_FREE_TSTR ( tmsg );		
		}

		if ( strcmp ( msg2, msg ) )
		{
			free ( msg2 );
		}
	}
}