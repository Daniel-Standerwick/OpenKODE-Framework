/* --------------------------------------------------------------------------
 *
 *      File            ex_10.cpp
 *      Description     10. Events
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

#define XM_FOR_PUMP_EVENT        1000
#define XM_FOR_WAIT_EVENT        2000

KDvoid xmRegularCallback ( const KDEvent *event )
{
	kdLogMessagefKHR ( "regular_callback   : event = 0x%08x, type = %04d, userptr = 0x%08x", event, event->type, event->userptr );
}

KDvoid xmRecursiveCallback ( const KDEvent *event )
{
	kdLogMessagefKHR ( "recursive_callback : event = 0x%08x, type = %04d, userptr = 0x%08x", event, event->type, event->userptr );

	if ( event->userptr == 0 )
	{
		const KDEvent* wait;
		
		KDEvent*	event[3];
		KDint		i = 0;

		event[i] = kdCreateEvent ();	
		event[i]->type = XM_FOR_PUMP_EVENT;	
		event[i]->userptr = (KDvoid *) xmRecursiveCallback;
		kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
		
		kdPostEvent ( event[i] );
		kdLogMessagefKHR ( "kdPostEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );

		i++;

		kdLogMessagefKHR ( "kdWaitEvent        : waiting message." );	
		wait = kdWaitEvent ( 0 );	
		kdLogMessagefKHR ( "kdWaitEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", wait, wait->type, wait->userptr );

		kdDefaultEvent( wait );	
		kdLogMessagefKHR ( "kdDefaultEvent     : event = 0x%08x", wait );

		event[i] = kdCreateEvent ();	
		event[i]->type = XM_FOR_PUMP_EVENT;	
		event[i]->userptr = (KDvoid *) xmRecursiveCallback;
		kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );

		kdPostEvent ( event[i] );
		kdLogMessagefKHR ( "kdPostEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );

		i++;

		event[i] = kdCreateEvent ();	
		event[i]->type = XM_FOR_WAIT_EVENT;	
		event[i]->userptr = (KDvoid *) xmRecursiveCallback;
		kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );		

		kdPostEvent ( event[i] );
		kdLogMessagefKHR ( "kdPostEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
	}
}

KDvoid xmEx_Regular ( KDvoid )
{
	const KDEvent* wait;

	KDEvent*	event[4];	
	KDint		ret = 0;
	KDint		i   = 0;
	
	kdLogMessage ( "* Case Regular\n\n" );

	//
	// ���� : �̺�Ʈ ����
	// ��ȯ : �̺�Ʈ 
	//
	event[i] = kdCreateEvent ();
	kdAssert ( ( event[i] ) );

	event[i]->type = XM_FOR_PUMP_EVENT;	// ���� �׽�Ʈ ��
	kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
	i++;

	event[i] = kdCreateEvent ();	
	event[i]->type = XM_FOR_WAIT_EVENT;	// �޼��� ��� �׽�Ʈ ��
	kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
	i++;

	event[i] = kdCreateEvent ();
	event[i]->type = XM_FOR_PUMP_EVENT;	// �̺�Ʈ ���� �׽�Ʈ ��
	kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
	i++;

	event[i] = kdCreateEvent ();	
	event[i]->type = XM_FOR_PUMP_EVENT;	// �޼��� ���� ���� �׽�Ʈ ��
	kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );

	i = 0;
	//
	// ���� : �̺�Ʈ ����
	// ���� : �̺�Ʈ
	// ��ȯ : ���� = 0, ���� = -1
	//
	ret = kdPostEvent ( event[i] );
	kdAssert ( !ret );

	kdLogMessagefKHR ( "kdPostEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
	i++;

	//
	// ���� : �̺�Ʈ ���� ( �ش� ������� �̺�Ʈ ���� )
	// ���� : �̺�Ʈ, ������ �ڵ� 
	// ��ȯ : ���� = 0, ���� = -1
	//	
	ret = kdPostThreadEvent ( event[i], kdThreadSelf() );			// ���� ������ ���� �ȵ�. 	
	kdAssert ( !ret );

	kdLogMessagefKHR ( "kdPostThreadEvent  : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
	i++;

	// 
	// ���� : �̺�Ʈ ���� ( �̹� ������ �Ǵ� ���Ÿ� �� ��쿡�� ����ġ ���� ���� �߻� ���� )
	// ���� : �̺�Ʈ
	//
	kdFreeEvent ( event[i] );

	kdLogMessagefKHR ( "kdFreeEvent        : event = 0x%08x", event[i] );
	i++;

	//
	// ���� : �ݹ� �Լ� ��� ( �̺�Ʈ �� ����� �����͸� �������� ��� ���� )
	// ���� : �ݹ� �Լ�, �̺�Ʈ ����, ����� ������
	// ��ȯ : ���� = 0, ���� = -1
	//	
	ret = kdInstallCallback ( xmRegularCallback, XM_FOR_PUMP_EVENT, KD_NULL );	
	kdAssert ( !ret );

	kdLogMessagefKHR ( "kdInstallCallback  : func  = 0x%08x, type = %04d, userptr = 0x%08x", xmRegularCallback, XM_FOR_PUMP_EVENT, KD_NULL );

	//
	// ���� : �̺�Ʈ ����( ��ϵ� �ݹ� �Լ� ���ǿ� ������ �޼������� ť���� ���� ���� �ݹ� �Լ��� ȣ���Ѵ� )
	// ��ȯ : ���� = 0, ���� = -1
	//
	kdLogMessagefKHR ( "kdPumpEvents       : pumping messages." );

	ret = kdPumpEvents ( );
	
	kdAssert ( !ret );

	//
	// ���� : �޼��� ���
	// ���� : �ð����� ( -1�� ���� )
	// ��ȯ : �̺�Ʈ
	//		
	i = 3;
	kdPostEvent ( event[i] );
	kdLogMessagefKHR ( "kdPostEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
	kdLogMessagefKHR ( "kdWaitEvent        : waiting message." );	
	
	wait = kdWaitEvent ( -1 );	
	kdAssert ( wait->type == XM_FOR_WAIT_EVENT );

	kdLogMessagefKHR ( "kdWaitEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", wait, wait->type, wait->userptr );

	//
	// ���� : ����Ʈ ó�� ( ���޵� �̺�Ʈ�� ���� �� )
	// ���� : �̺�Ʈ
	// 
	kdDefaultEvent ( wait );	

	kdLogMessagefKHR ( "kdDefaultEvent     : event = 0x%08x", wait );
}

KDvoid xmEx_Recursive ( KDvoid )
{
	const KDEvent*    wait;

	KDEvent*     event[2];		
	KDint        i = 0;

	kdLogMessage ( "\n* Case Recursive\n\n" );

	event[i] = kdCreateEvent ();	
	event[i]->type = XM_FOR_PUMP_EVENT;	
	kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );

	kdPostEvent ( event[i] );
	kdLogMessagefKHR ( "kdPostEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );

	i++;

	event[i] = kdCreateEvent ();	
	event[i]->type = XM_FOR_WAIT_EVENT;	
	kdLogMessagefKHR ( "kdCreateEvent      : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );
	
	kdPostEvent ( event[i] );
	kdLogMessagefKHR ( "kdPostEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", event[i], event[i]->type, event[i]->userptr );

	kdInstallCallback ( xmRecursiveCallback, XM_FOR_PUMP_EVENT, KD_NULL );
	kdLogMessagefKHR ( "kdInstallCallback  : func  = 0x%08x, type = %04d, userptr = 0x%08x", xmRecursiveCallback, XM_FOR_PUMP_EVENT, KD_NULL );

	kdLogMessagefKHR ( "kdWaitEvent        : waiting message." );	
	wait = kdWaitEvent ( -1 );	
	kdLogMessagefKHR ( "kdWaitEvent        : event = 0x%08x, type = %04d, userptr = 0x%08x", wait, wait->type, wait->userptr );

	kdDefaultEvent( wait );	
	kdLogMessagefKHR ( "kdDefaultEvent     : event = 0x%08x", wait );
}

KDvoid xmEx_RemoveCallback ( KDvoid )
{
	kdLogMessage ( "\n* Case RemoveCallback\n\n" );

	//
	// �ݹ� ��� ����
	//
	kdLogMessagefKHR ( "kdInstallCallback  : uninstall all callbacks." );
	kdInstallCallback ( KD_NULL, (KDint) KD_NULL, KD_NULL );	
}

KDvoid xmExample_10 ( KDvoid )
{	
	kdLogMessage ( "Example 10. Events\n\n" );

	xmEx_Regular ( );
	xmEx_Recursive ( );
	xmEx_RemoveCallback ( );	
}
