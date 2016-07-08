/* --------------------------------------------------------------------------
 *
 *      File            ex_05.cpp
 *      Description     05. Memory allocation
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

KDvoid xmExample_05 ( KDvoid )
{	
	const KDsize size[3] = { 1000, 100, 10000 };

	KDvoid*	    buf;
	KDint       i;
	
	kdLogMessage ( "Example 05. Memory allocation\n\n" );

	//
	// Case 1 : kdMalloc 
	//

	// �޸� ���� �Ҵ��Ѵ�.
	buf = kdMalloc ( size[ 0 ] );

	// �޸� �� �Ҵ��� ���������� Ȯ���Ѵ�.
	if ( buf != KD_NULL )
	{
		kdLogMessage ( "Case 1 : Memory block is allocated." );
	}
	else
	{
		// �޸� �� �Ҵ� ������ �������� Ȯ���Ѵ�.
		if ( kdGetError ( ) == KD_ENOMEM )
		{
			kdLogMessage ( "Case 1 : Not enough space." );
		}
		else
		{
			kdHandleAssertion ( "kdMalloc", __FILE__, __LINE__ );
		}
	}

	//
	// Case 2 : kdRealloc 
	//

	// �Ҵ�� �޸� �� ����� �ٿ��ٰ� �ٽ� ũ���Ѵ�.
	for ( i = 1; i < 3; i++ )
	{
		// �޸� ���� ���������մϴ�.
		buf = kdRealloc ( buf, size[i] );

		// �޸� �� ������� �������� Ȯ���Ѵ�.
		if ( buf != KD_NULL )
		{
			kdLogMessage ( "Case 2 : Memory block is resized." );
		}
		else
		{
			// �޸� �� �������� ������ �������� Ȯ���Ѵ�.
			if ( kdGetError ( ) == KD_ENOMEM )
			{
				kdLogMessage ( "Case 2 : Not enough space." );
			}
			else
			{
				kdHandleAssertion ( "kdRealloc", __FILE__, __LINE__);
			}
		}
	}

	//
	// Case 3 : kdFree 
	//

	// �޸� �� �����Ѵ�.
	kdFree ( buf );
	kdLogMessage ( "Case 3 : Allocated memory block is freed." );
}
