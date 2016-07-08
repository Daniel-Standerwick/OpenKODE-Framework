/* --------------------------------------------------------------------------
 *
 *      File            ex_06.cpp
 *      Description     06. String and memory functions
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

KDvoid xmEx_kdMemchr ( KDvoid )
{
	KDchar*    pch   = 0;
	KDchar     str[] = "Hello";

	// �־��� ����Ʈ�� (0~255)�� �޸� �������� ã�� �ּҰ��� ��ȯ�Ѵ�.
	pch = (KDchar *) kdMemchr ( str, 'l', kdStrlen ( str ) );

	kdAssert ( pch != KD_NULL );
	kdLogMessagefKHR ( "kdMemchr    : 'l' found at position %d.", pch - str + 1 );
}

KDvoid xmEx_kdMemcmp ( KDvoid )
{
	KDchar     str1[] = "Hi";
	KDchar     str2[] = "Hello";
	KDsize     len1	  = kdStrlen ( str1 );
	KDsize     len2	  = kdStrlen ( str2 );
	KDint      retval = 0;

	// �־��� �޸� ������ŭ ó������ KDuint8�� �񱳸� �Ѵ�. 
	// ��ȯ���� ����� ��� : �ҽ� 1 > �ҽ� 2 
	// ��ȯ���� ������ ��� : �ҽ� 1 < �ҽ� 2
	// ��ȯ����    0�� ��� : �ҽ� 1 = �ҽ� 2
	retval = kdMemcmp ( str1, str2, ( len1 > len2 ) ? len1 : len2 );

	kdAssert ( retval > 0 );
	kdLogMessagefKHR ( "kdMemcmp    : '%s' is greater than '%s'.", str1, str2 );
}

KDvoid xmEx_kdMemcpy ( KDvoid )
{
	KDchar     str1[]   = "Hello world";
	KDchar     str2[20] = "";

	// �־��� �޸� ������ŭ �ҽ� 2�� �ҽ� 1�� �����Ѵ�.
	kdMemcpy ( str2, str1, 5 );

	kdAssert ( kdMemcmp ( str2, "Hello", 5 ) == 0 );
	kdLogMessagefKHR ( "kdMemcpy    : '%s' correctly copied.", str2 );
}

KDvoid xmEx_kdMemmove ( KDvoid )
{
	KDchar     str[] = "Hello world .....";
	 
	// �������� ���� �޸� ���縦 �Ѵ�. (kdMemcpy�� �������� ������ �ʴ´�.)
	// 'world' �κ��� �ҽ��� ��� �ּ��� ������ �����̴�.
	kdMemmove ( str + 6, str, 11 );

	kdAssert ( kdMemcmp ( str, "Hello Hello world", 17 ) == 0 );
	kdLogMessagefKHR ( "kdMemmove   : '%s' correctly overlapped.", str );
}

KDvoid xmEx_kdMemset ( KDvoid )
{
	KDchar     str[] = "Hello world";
	 
	// �������� ���� �޸� ���縦 �Ѵ�. (kdMemcpy�� �������� ������ �ʴ´�.)
	// 'world' �κ��� �ҽ��� ��� �ּ��� ������ �����̴�.
	kdMemset ( str + 6, '.', 5 );

	kdAssert ( kdMemcmp ( str, "Hello .....", 11 ) == 0 );
	kdLogMessagefKHR ( "kdMemset    : '%s' correctly set bytes.", str );
}

KDvoid xmEx_kdStrchr ( KDvoid )
{
	KDchar*    pch   = 0;
	KDchar     str[] = "Hello";

	// �־��� ����Ʈ�� (0~255)�� ���ڿ����� ã�� �ּҰ��� ��ȯ�Ѵ�.
	pch = kdStrchr ( str, 'e' );

	kdAssert ( pch );
	kdLogMessagefKHR ( "kdStrchr    : 'e' found at position %d.", pch - str + 1 );
}

KDvoid xmEx_kdStrcmp ( KDvoid )
{
	KDchar     str1[] = "Hello";
	KDchar     str2[] = "Hi";
	KDint      retval = 0;

	// �־��� ���ڿ����� ���ʴ�� KDuint8 ���ڰ� �񱳸� �Ѵ�. 
	// ��ȯ���� ����� ��� : ���ڿ� 1 > ���ڿ� 2 
	// ��ȯ���� ������ ��� : ���ڿ� 1 < ���ڿ� 2
	// ��ȯ����    0�� ��� : ���ڿ� 1 = ���ڿ� 2
	retval = kdStrcmp ( str1, str2 );

	kdAssert ( retval < 0 );
	kdLogMessagefKHR ( "kdStrcmp    : '%s' is smaller than '%s'.", str1, str2 );
}

KDvoid xmEx_kdStrlen ( KDvoid )
{
	KDchar     str[]  = "Hello";
	KDsize     retval = 0;
	
	// ���ڿ��� ���̸� ���Ѵ�. ��, �ִ� ����� �����ȴ�.
	retval = kdStrlen ( str );

	kdAssert ( retval == 5 );
	kdLogMessagefKHR ( "kdStrlen    : '%s' string length is %d.", str, retval );
}

KDvoid xmEx_kdStrnlen ( KDvoid ) 
{
	KDchar     str[]  = "Hello world";
	KDsize     maxlen = 5;
	KDsize     retval = 0;
	
	// ���ڿ��� ���̸� ���Ѵ�.
	retval = kdStrnlen ( str, maxlen );

	kdAssert ( retval == 5 );
	kdLogMessagefKHR ( "kdStrnlen   : '%s' string length is %d. max length is %d", str, retval, maxlen );
}

KDvoid xmEx_kdStrncat_s ( KDvoid )
{
	KDchar     str[20] = "";

	// �� ���ڿ��� ���� �����Ѵ�.
	// ��� ���ڿ��� �ִ� ����� ���ؾ� �Ѵ�.
	// �ҽ� ���ڿ��� �ִ� ����� ���ؾ� �Ѵ�. 
	// �� �ִ� ������� Null terminated ���ڿ��� ���� ������ üũ�� �ִ�.
	kdStrncat_s ( str, sizeof ( str ), "Hello World", 5 );
	kdStrncat_s ( str, sizeof ( str ), " World...", 6 );

	kdAssert ( kdStrcmp ( str, "Hello World" ) == 0 );
	kdLogMessagefKHR ( "kdStrncat_s : '%s' correctly concatenated.", str );
}

KDvoid xmEx_kdStrncmp ( KDvoid )
{
	KDchar     str1[] = "Hello world";
	KDchar     str2[] = "Hello";
	KDint      retval = 0;

	// �־��� �� ���ڿ����� ���ʴ�� KDuint8 ���ڰ� �񱳸� �Ѵ�. 
	// ��ȯ���� ����� ��� : ���ڿ� 1 > ���ڿ� 2 
	// ��ȯ���� ������ ��� : ���ڿ� 1 < ���ڿ� 2
	// ��ȯ����    0�� ��� : ���ڿ� 1 = ���ڿ� 2
	// �� ���ڿ��� �ִ� ����� ���ؾ� �Ѵ�.
	retval = kdStrncmp ( str1, str2, 5 );

	kdAssert ( retval == 0 );
	kdLogMessagefKHR ( "kdStrncmp   : '%s' is same length as '%s'. compare max length is %d", str1, str2, 5 );
}

KDvoid xmEx_kdStrcpy_s ( KDvoid )
{
	KDchar     str1[]   = "Hello";
	KDchar     str2[20] = "";

	// ���ڿ� ���縦 �Ѵ�.
	// ��� ���ڿ��� �ִ� ������� �ҽ� ũ�Ⱑ �۾ƾ� �Ѵ�.
	// PS. ���� ������ �߸��Ȱ� ����. kdStrncpy �Լ����� �´°� ����. _s�� �ҽ� �ִ� ����� �ǹ� �ϴµ�.
	kdStrcpy_s ( str2, 11, str1 );

	kdAssert ( kdStrcmp ( str2, "Hello" ) == 0 );
	kdLogMessagefKHR ( "kdStrcpy_s  : '%s' correctly copied.", str2 );
}

KDvoid xmEx_kdStrncpy_s ( KDvoid )
{
	KDchar     str1[]   = "Hello";
	KDchar     str2[20] = "";

	// ���ڿ� ���縦 �Ѵ�.
	// ��� ���ڿ��� �ִ� ����� ���ؾ� �Ѵ�.
	// �ҽ� ���ڿ��� �ִ� ����� ���ؾ� �Ѵ�. 
	// �� �ִ� ������� Null terminated ���ڿ��� ���� ������ üũ�� �ִ�.
	kdStrncpy_s ( str2, 11, str1, 5 );

	kdAssert ( kdStrcmp ( str2, "Hello" ) == 0 );
	kdLogMessagefKHR ( "kdStrncpy_s : '%s' correctly copied.", str2 );
}

KDvoid xmExample_06 ( KDvoid )
{	
	kdLogMessage ( "Example 06. String and memory functions\n\n" );

	xmEx_kdMemchr  ( );
	xmEx_kdMemcmp  ( );
	xmEx_kdMemcpy  ( );
	xmEx_kdMemmove ( );
	xmEx_kdMemset  ( );

	xmEx_kdStrchr    ( );
	xmEx_kdStrcmp    ( );
	xmEx_kdStrlen    ( );
	xmEx_kdStrnlen   ( );
	xmEx_kdStrncat_s ( );
	xmEx_kdStrncmp   ( );
	xmEx_kdStrcpy_s  ( );
	xmEx_kdStrncpy_s ( );
}
