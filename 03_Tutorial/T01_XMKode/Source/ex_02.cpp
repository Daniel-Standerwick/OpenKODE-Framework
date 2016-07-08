/* --------------------------------------------------------------------------
 *
 *      File            ex_02.cpp
 *      Description     02. Versioning and attribute queries
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

#include "main.h"

KDvoid xmExample_02 ( KDvoid )
{			
	const KDchar*     attrbcv[3];
	      KDint       value;

	kdLogMessage ( "Example 02. Versioning and attribute queries\n\n" );

	//
	// Case 1 : kdQueryAttribcv
	//

	// ������ ������ �����´�.
	if ( ( attrbcv[ 0 ] = kdQueryAttribcv ( KD_ATTRIB_VENDOR ) ) != KD_NULL )
	{
		kdLogMessagefKHR ( "Case 1-1 : VENDOR   = %s", attrbcv[ 0 ] );
	}

	// ���� ������ �����´�.
	if ( ( attrbcv[ 1 ] = kdQueryAttribcv ( KD_ATTRIB_VERSION ) ) != KD_NULL )
	{
		kdLogMessagefKHR ( "Case 1-2 : VERSION  = %s", attrbcv[ 1 ] );
	}

	// �÷��� ������ �����´�.
	if ( ( attrbcv[ 2 ] = kdQueryAttribcv ( KD_ATTRIB_PLATFORM ) ) != KD_NULL )
	{
		kdLogMessagefKHR ( "Case 1-3 : PLATFORM = %s", attrbcv[ 2 ] );
	}

	// ���� ���� �ʴ� ������ ���� �Ͽ��� ���, KD_EINVAL ���� �޼����� �߻��Ѵ�.
	kdSetError ( 0 );

	if ( kdQueryAttribcv ( 0 ) == KD_NULL )
	{
		if ( kdGetError ( ) == KD_EINVAL )
		{
			kdLogMessage ( "Case 1-4 : Correct error value returned. ( KD_EINVAL )" );
		}
		else
		{
			kdLogMessage ( "Case 1-4 : Incorrect error value returned. " );
		}
	}
	
	//
	// Case 2 : kdQueryAttribi 
	//

	kdSetError ( 0 );

	if ( kdQueryAttribi ( 0, &value ) == 0 )
	{
		// ���� ��ȿ�� ATTRIBUTE ���� ���� ����
	}
	else
	{
		if( kdGetError ( ) == KD_EINVAL )
		{
			// ���� ���忡�� �׻� KD_EINVAL ���� ���´�.
			kdLogMessage ( "Case 2   : Correct error value returned. ( KD_EINVAL )" );
		}
		else
		{
			kdLogMessage ( "Case 2   : Incorrect error value returned. " );
		}
	}

	//
	// Case 3 : kdQueryIndexedAttribcv
	//

	kdSetError ( 0 );

	if ( kdQueryIndexedAttribcv ( 0, 0 ) != KD_NULL )
	{
		// ���� ��ȿ�� ATTRIBUTE ���� ���� ����
	}
	else
	{
		if ( kdGetError ( ) == KD_EINVAL )
		{
			// ���� ���忡�� �׻� KD_EINVAL ���� ���´�.
			kdLogMessage ( "Case 3   : Correct error value returned. ( KD_EINVAL )" );
		}
		else
		{
			kdLogMessage ( "Case 3   : Incorrect error value returned. " );
		}
	}
}
