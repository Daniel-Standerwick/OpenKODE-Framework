/* --------------------------------------------------------------------------
 *
 *      File            ex_24.cpp
 *      Description     24. XM_Queue
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

typedef struct XMData 
{
	KDint       index;
	KDchar      name[128];
} XMData;

static XMQueue*	    g_queue1 = 0;
static XMQueue*	    g_queue2 = 0;

static KDint xmFindQueue ( KDvoid* data, KDvoid* find )
{
	return ( (XMData *) data )->index >= *( (KDint *) find ) ? 0 : -1;
}

static KDvoid xmFreeQueue ( KDvoid* data )
{
	XMData*    _data = (XMData *) data;

	_data->index = 0;
	kdMemset ( _data->name, 0, 128 );

	kdFree ( data );
}

static KDvoid xmEx_Create ( KDvoid )
{
	//
	// ���� : ť�� �����Ѵ�.
	// ��ȯ : ť �ڵ�
	//
	g_queue1 = xmQueueCreate ( );
	g_queue2 = xmQueueCreate ( );

	kdAssert ( g_queue1 );
	kdAssert ( g_queue2 );

	kdLogMessagefKHR ( "xmQueueCreate      : queue = 0x%08x", g_queue1 );
	kdLogMessagefKHR ( "xmQueueCreate      : queue = 0x%08x", g_queue2 );
}

static KDvoid xmEx_Push ( KDvoid )
{
	XMData*    data1  = 0;
	XMData*	   data2  = 0;
	KDint      i;
	KDint      ret;

	for ( i = 0; i < 7; i++ )
	{
		data1 = (XMData *) kdMalloc ( sizeof ( XMData ) );
		data2 = (XMData *) kdMalloc ( sizeof ( XMData ) );

		data1->index = i;
		data2->index = i;

		kdSprintfKHR ( data1->name, "data = 0x%08x, index = %d", data1, data1->index );
		kdSprintfKHR ( data2->name, "data = 0x%08x, index = %d", data2, data2->index );

		//
		// ���� : ť�� �պκп� ����Ÿ�� �ִ´�. 
		// ���� : ť �ڵ�, ����Ÿ
		// ��ȯ : ���� = 0, ���� = -1
		//
		ret = xmQueuePushFront ( g_queue1, ( KDvoid * ) data1 );

		kdAssert ( ret == 0 );
		kdLogMessagefKHR ( "xmQueuePushFront   : queue = 0x%08x, %s", g_queue1, data1->name );

		//
		// ���� : ť�� �޺κп� ����Ÿ�� �ִ´�. 
		// ���� : ť �ڵ�, ����Ÿ
		// ��ȯ : ���� = 0, ���� = -1
		//
		ret = xmQueuePushRear ( g_queue2, ( KDvoid * ) data2 );
		
		kdAssert ( ret == 0 );		
		kdLogMessagefKHR ( "xmQueuePushRear    : queue = 0x%08x, %s", g_queue2, data2->name );
	}
}

KDvoid xmEx_Pop ( KDvoid )
{
	XMData*    data1 = 0;
	XMData*    data2 = 0;
	KDint      find  = 3;

	//
	// ���� : ť�� �պκп� ����Ÿ�� ������.
	// ���� : ť �ڵ�
	// ��ȯ : ����Ÿ
	//
	data1 = (XMData *) xmQueuePopFront ( g_queue1 );
	data2 = (XMData *) xmQueuePopFront ( g_queue2 );

	kdAssert ( data1 && data2 );
	kdLogMessagefKHR ( "xmQueuePopFront    : queue = 0x%08x, %s", g_queue1, data1->name );
	kdLogMessagefKHR ( "xmQueuePopFront    : queue = 0x%08x, %s", g_queue2, data2->name );

	//
	// ���� : ť�� �޺κп� ����Ÿ�� ������.
	// ���� : ť �ڵ�
	// ��ȯ : ����Ÿ
	//
	data1 = (XMData *) xmQueuePopRear ( g_queue1 );
	data2 = (XMData *) xmQueuePopRear ( g_queue2 );

	kdAssert ( data1 && data2 );
	kdLogMessagefKHR ( "xmQueuePopRear     : queue = 0x%08x, %s", g_queue1, data1->name );
	kdLogMessagefKHR ( "xmQueuePopRear     : queue = 0x%08x, %s", g_queue2, data2->name );

	//
	// ���� : ť�� ���ǿ� ���� ����Ÿ�� ������.
	// ���� : ť �ڵ�, ���� �Լ�, ���� ����
	// ��ȯ : ����Ÿ
	//
	data1 = (XMData *) xmQueuePopFind ( g_queue1, xmFindQueue, &find );
	data2 = (XMData *) xmQueuePopFind ( g_queue2, xmFindQueue, &find );

	kdAssert ( data1 && data2 );
	kdLogMessagefKHR ( "xmQueuePopFind     : queue = 0x%08x, %s", g_queue1, data1->name );
	kdLogMessagefKHR ( "xmQueuePopFind     : queue = 0x%08x, %s", g_queue2, data2->name );
}

static KDvoid xmEx_Free ( KDvoid )
{
	//
	// ���� : ť�� �����Ѵ�.
	// ���� : ť �ڵ�, ť ���� �Լ� ( �ΰ��̸� �ڵ����� ����Ÿ�� �ִ��� �Ǵ��ؼ� ����Ÿ�� ���� �Ѵ�. )
	//
	xmQueueFree ( g_queue1, xmFreeQueue );
	xmQueueFree ( g_queue2, 0 );

	kdLogMessagefKHR ( "xmQueueFree        : queue = 0x%08x", g_queue1 );
	kdLogMessagefKHR ( "xmQueueFree        : queue = 0x%08x", g_queue2 );
}

static KDvoid xmEx_Size ( KDvoid )
{
	KDsize    size1;
	KDsize    size2;

	//
	// ���� : ť ����� ���Ѵ�.
	// ���� : ť �ڵ�
	// ��ȯ : ť ������
	//
	size1 = xmQueueSize ( g_queue1 );
	size2 = xmQueueSize ( g_queue2 );

	kdAssert ( size1 && size2 );
	kdLogMessagefKHR ( "xmQueueSize        : queue = 0x%08x, size = %d", g_queue1, size1 );
	kdLogMessagefKHR ( "xmQueueSize        : queue = 0x%08x, size = %d", g_queue2, size2 );
}

static KDvoid xmEx_Get ( KDvoid )
{
	XMData*    data1 = 0;
	XMData*    data2 = 0;

	//
	// ���� : ť���� ����Ÿ�� ���� �´�. ( ť���� ����Ÿ�� �����Ѵ�. )
	// ���� : ť �ڵ�, �ε���
	// ��ȯ : ����Ÿ
	//
	data1 = (XMData *) xmQueueGet ( g_queue1, 1 );
	data2 = (XMData *) xmQueueGet ( g_queue2, 1 );

	kdAssert ( data1 && data2 );
	kdLogMessagefKHR ( "xmQueueGet         : queue = 0x%08x, %s", g_queue1, data1->name );
	kdLogMessagefKHR ( "xmQueueGet         : queue = 0x%08x, %s", g_queue2, data2->name );
}

static KDvoid xmEx_Erase ( KDvoid )
{
	XMData*    data1 = 0;
	XMData*    data2 = 0;

	//
	// ���� : ť �ش� �ε����� ��带 �����Ѵ�.
	// ���� : ť �ڵ�, �ε���
	// ��ȯ : ����Ÿ
	//
	data1 = (XMData *) xmQueueErase ( g_queue1, 1 );
	data2 = (XMData *) xmQueueErase ( g_queue2, 1 );

	kdAssert ( data1 && data2 );
	kdLogMessagefKHR ( "xmQueueErase       : queue = 0x%08x, %s", g_queue1, data1->name );
	kdLogMessagefKHR ( "xmQueueErase       : queue = 0x%08x, %s", g_queue2, data2->name );

	kdFree ( data1 );
	kdFree ( data2 );
}

static KDvoid xmEx_Find ( KDvoid )
{
	XMData*    data1 = 0;
	XMData*    data2 = 0;
	KDint      find  = 1;

	//
	// ���� : ť�� �պκ� ���� ���ǿ� ���� ����Ÿ�� ã�´�. ( �� ���� �Լ��� ������, ù��° ����Ÿ�� ��ȯ�Ѵ�. )
	// ���� : ť �ڵ�, ���� �Լ�, ���� ����
	// ��ȯ : ����Ÿ
	//
	data1 = (XMData *) xmQueueFind ( g_queue1, xmFindQueue, &find );

	//
	// ���� : ť�� �޺κ� ���� ���ǿ� ���� ����Ÿ�� ã�´�. ( �� ���� �Լ��� ������, ù��° ����Ÿ�� ��ȯ�Ѵ�. )
	// ���� : ť �ڵ�, ���� �Լ�, ���� ����
	// ��ȯ : ����Ÿ
	//
	data2 = (XMData *) xmQueueReverseFind ( g_queue2, xmFindQueue, &find );

	kdAssert ( data1 && data2 );
	kdLogMessagefKHR ( "xmQueueFind        : queue = 0x%08x, %s", g_queue1, data1->name );
	kdLogMessagefKHR ( "xmQueueReverseFind : queue = 0x%08x, %s", g_queue2, data2->name );	
}

/*
static KDvoid xmEx_FindNext ( KDvoid )
{
	XMData*    data1 = 0;
	XMData*    data2 = 0;

	//
	// ���� : Find�� ã�� ����Ÿ�� ������, �� ���� ������ �´� ����Ÿ�� ã�´�. 
	// ���� : ť �ڵ�
	// ��ȯ : ����Ÿ 
	//
	data1 = (XMData *) xmQueueFindNext ( g_queue1 );
	data2 = (XMData *) xmQueueFindNext ( g_queue2 );

	kdAssert ( data1 && data2 );
	kdLogMessagefKHR ( "xmQueueFindNext    : queue = 0x%08x, %s", g_queue1, data1->name );
	kdLogMessagefKHR ( "xmQueueFindNext    : queue = 0x%08x, %s", g_queue2, data2->name );	
}

static KDvoid xmEx_EraseFound ( KDvoid )
{
	XMData*    data1 = 0;
	XMData*    data2 = 0;

	//
	// ���� : Find�� ã�� ����Ÿ�� ������, �� ���� ������ �´� ����Ÿ�� ã�´�. 
	// ���� : ť �ڵ�
	// ��ȯ : ����Ÿ 
	//
	data1 = (XMData *) xmQueueEraseFound ( g_queue1 );
	data2 = (XMData *) xmQueueEraseFound ( g_queue2 );

	kdAssert ( data1 && data2 );
	kdLogMessagefKHR ( "Example xmQueueEraseFound()  : queue = 0x%08x, %s", g_queue1, data1->name );
	kdLogMessagefKHR ( "Example xmQueueEraseFound()  : queue = 0x%08x, %s", g_queue2, data2->name );	

	kdFree ( data1 );
	kdFree ( data2 );
}
*/

KDvoid xmExample_24 ( KDvoid )
{	
	kdLogMessage ( "Example 24. XM_Queue\n\n" );

	//
	// * ��� ���� ����
	//
	//   - ť�� �⺻������ ���� ��ȣ ������ ���� �ֽ��ϴ�.
	//   - ����, �ϳ��� ť�� ���� ������ �ϴ� ��� DeadLock�� �߻� �� �� �ֽ��ϴ�.
	//   - ������ �Լ� �̿�� ���� �ٶ��ϴ�.
	//

	xmEx_Create ( );
	xmEx_Push   ( );
	xmEx_Pop    ( );
	xmEx_Size   ( );
	xmEx_Get    ( );
	xmEx_Erase  ( );
	xmEx_Find   ( );
	//xmEx_FindNext   ( );
	//xmEx_EraseFound ( );
	xmEx_Free   ( );
}