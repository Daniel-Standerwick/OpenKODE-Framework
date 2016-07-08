/* --------------------------------------------------------------------------
 *
 *      File            ex_04.cpp
 *      Description     04. Assertions and logging
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

KDvoid xmExample_04 ( KDvoid )
{	
	kdLogMessage ( "Example 04. Assertions and logging\n\n" );

	// IDE���� Release���� ������ ���, Case 3�� ���۵ȴ�.
	
	//
	// Case 1 : kdLogMessage 
	//

	kdLogMessage ( "Case 1 : Log message is printed." );

	//
	// Case 2 : kdAssert 
	//

	// Condition�� KD_TRUE ��, ��ũ�� ���� ������ �������� ġȯ�ȴ�.
	// KD_FALSE�̸� kdHandleAssertion ��ũ�� ġȯ�ȴ�.
	kdAssert ( KD_TRUE );
	kdLogMessage ( "Case 2 : Assert condition is KD_TRUE." ); 

	//
	// Case 3 : kdHandleAssertion 
	//

	// ����� Assert ����� ������. 
	//kdHandleAssertion ( "Case 3", __FILE__, __LINE__);
	
	// ���� �α� �޼����� ��µǸ� ����� Assert�� ���е��� �� �� �ִ�.
	//kdLogMessage ( "Case 3 : Application is not terminated by kdHandleAssertion" ); 
}
