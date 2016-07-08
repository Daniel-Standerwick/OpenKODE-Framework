/* --------------------------------------------------------------------------
 *
 *      File            ex_21.cpp
 *      Description     21. KD_KHR_formatted
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

static KDchar    l_fmt[256] = "Hello, c = %c, d = %03d, e = %e, f = %0.2f, g = %0.2g, o = %o, s = %s, x = %x";
static KDchar    l_str[256] = "a 99 0.111 0.222 0.333 Hi ff";

KDvoid xmEx_Sprintf ( KDvoid )
{
	KDchar        buf[256];
	KDint         len;

	//
	// ���� : ���˵� ����� ���ۿ� �����Ѵ�.
	// ���� : ����, ���� ������, ���� ���ڿ�, ���� ���ڵ�
	// ��� : ����� ���� ��ȯ
	//
	len = kdSnprintfKHR ( buf, 256, l_fmt, 'a', 99, 0.111f, 0.222f, 0.333f, 9, "Hi", 0xFF );
	kdLogMessagefKHR ( "kdSnprintfKHR    : buffer = '%s', length = %d", buf, len );

	//
	// ���� : ���˵� ����� ���ۿ� �����Ѵ�.
	// ���� : ����, ���� ���ڿ�, ���� ���ڵ�
	// ��� : ����� ���� ��ȯ
	//
	len = kdSprintfKHR ( buf, l_fmt, 'a', 99, 0.111f, 0.222f, 0.333f, 9, "Hi", 0xFF );
	kdLogMessagefKHR ( "kdSprintfKHR     : buffer = '%s', length = %d", buf, len );
}

KDvoid xmEx_Vsnprintf ( KDchar * format, ... )
{ 
	KDchar        buf[256];
	KDint         len;
	KDVaListKHR   ap;

	KD_VA_START_KHR ( ap, format );

	//
	// ���� : ���˵� ����� ���ۿ� �����Ѵ�.
	// ���� : ����, ���� ������, ���� ���ڿ�, ���� ���� ����Ʈ
	// ��� : ����� ���� ��ȯ
	//
	len = kdVsnprintfKHR ( buf, 256, format, ap );
	kdLogMessagefKHR ( "kdVsnprintfKHR   : buffer = '%s', length = %d", buf, len );
	
	KD_VA_END_KHR ( ap );
}

KDvoid xmEx_Vsprintf ( KDchar * format, ... )
{
	KDchar        buf[256];
	KDint         len;
	KDVaListKHR   ap;

	KD_VA_START_KHR ( ap, format );

	//
	// ���� : ���˵� ����� ���ۿ� �����Ѵ�.
	// ���� : ����, ���� ���ڿ�, ���� ���� ����Ʈ
	// ��� : ����� ���� ��ȯ
	//
	len = kdVsprintfKHR ( buf, format, ap );
	kdLogMessagefKHR ( "kdVsprintfKHR    : buffer = '%s', length = %d", buf, len );

	KD_VA_END_KHR ( ap );
}

KDvoid xmEx_LogMessage ( KDvoid )
{
	KDchar        buf[256];

	kdStrncpy_s ( buf, 256, "kdLogMessagefKHR : buffer = '", 256 );
	kdStrncat_s ( buf, 256, l_fmt, 256 );
	kdStrncat_s ( buf, 256, "'", 256 );

	//
	// ���� : ���˵� ���ڿ��� �α� �޼����� ����Ѵ�. (�ִ� ����� 256 �����̴�)
	// ���� : ���� ���ڿ�, ���� ���ڵ�
	// ��� : ��µ� ���ڿ� ���� ��ȯ
	//
	kdLogMessagefKHR ( buf, 'a', 99, 0.111f, 0.222f, 0.333f, 9, "Hi", 0xFF );
}

KDvoid xmEx_Scanf ( KDFile* file )
{
	KDchar        c;
	KDint         d;
	KDfloat32     e;
	KDfloat32     f;
	KDfloat32     g;	
	KDchar        s[256];
	KDint         x;
	KDint         len;
	KDchar        buf[256];

	kdFseek ( file, 0, KD_SEEK_SET );

	kdStrncpy_s ( buf, 256, "kdSscanfKHR      : buffer = '", 256 );
	kdStrncat_s ( buf, 256, l_fmt, 256 );
	kdStrncat_s ( buf, 256, "', count = %d", 256 );

	//
	// ���� : ���ڿ����� ���˵� �Է°��� �д´�.
	// ���� : ���ڿ�, ���� ���ڿ�, ���� ���ڵ�
	// ��� : ���� ���� ����
	//
	len = kdSscanfKHR ( l_str, "%c %d %e %f %g %s %x", &c, &d, &e, &f, &g, s, &x );
	kdLogMessagefKHR  ( buf, c, d, e, f, g, 9, s, x, len );	

	kdStrncpy_s ( buf, 256, "kdFscanfKHR      : buffer = '", 256 );
	kdStrncat_s ( buf, 256, l_fmt, 256 );
	kdStrncat_s ( buf, 256, "', count = %d", 256 );

	//
	// ���� : ���Ͽ��� ���˵� �Է°��� �д´�.
	// ���� : ����, ���� ���ڿ�, ���� ���ڵ�
	// ��� : ���� ���� ����
	//
	len = kdFscanfKHR ( file, "%c %d %e %f %g %s %x", &c, &d, &e, &f, &g, s, &x );
	kdLogMessagefKHR ( buf, c, d, e, f, g, 9, s, x, len );	
}

static KDint xmVscanf ( KDchar * format, ... )
{	
	KDint         len;
	KDVaListKHR   ap;

	KD_VA_START_KHR( ap, format );

	//
	// ���� : ���ڿ����� ���˵� �Է°��� �д´�.
	// ���� : ���ڿ�, ���� ���ڿ�, ���� ���ڵ�
	// ��� : ���� ���� ����
	//
	len = kdVsscanfKHR ( l_str, format, ap );

	KD_VA_END_KHR ( ap );
	
	return len;
}

static KDint xmVfscanf ( KDFile* file, KDchar * format, ... )
{
	KDint         len;
	KDVaListKHR   ap;
	
	KD_VA_START_KHR ( ap, format );

	//
	// ���� : ���Ͽ��� ���˵� �Է°��� �д´�.
	// ���� : ����, ���� ���ڿ�, ���� ���� ����Ʈ
	// ��� : ���� ���� ����
	//
	len = kdVfscanfKHR ( file, format, ap );

	KD_VA_END_KHR ( ap );
	
	return len;
}

KDvoid xmEx_Vscanf ( KDFile* file )
{
	KDchar        c;
	KDint         d;
	KDfloat32     e;
	KDfloat32     f;
	KDfloat32     g;	
	KDchar        s[256];
	KDint         x;
	KDint         len;
	KDchar        buf[256];

	kdStrncpy_s ( buf, 256, "kdVsscanfKHR     : buffer = '", 256 );
	kdStrncat_s ( buf, 256, l_fmt, 256 );
	kdStrncat_s ( buf, 256, "', count = %d", 256 );

	len = xmVscanf ( (KDchar *) "%c %d %e %f %g %s %x", &c, &d, &e, &f, &g, s, &x );
	kdLogMessagefKHR ( buf, c, d, e, f, g, 9, s, x, len );	

	kdFseek ( file, 0, KD_SEEK_SET );

	kdStrncpy_s ( buf, 256, "kdVfscanfKHR     : buffer = '", 256 );
	kdStrncat_s ( buf, 256, l_fmt, 256 );
	kdStrncat_s ( buf, 256, "', count = %d", 256 );

	len = xmVfscanf ( file, (KDchar *) "%c %d %e %f %g %s %x", &c, &d, &e, &f, &g, s, &x );
	kdLogMessagefKHR ( buf, c, d, e, f, g, 9, s, x, len );
}

KDvoid xmExample_21 ( KDvoid )
{	
	KDFile*      file;

	kdLogMessage ( "Example 21. KD_KHR_formatted\n\n" );

	file = kdFopen ( "/tmp/KD_KHR_formatted.txt", "w+" );
	kdFwrite ( l_str, kdStrlen ( l_str ), 1, file );

	xmEx_Sprintf    ( );
	xmEx_Vsnprintf  ( l_fmt, 'a', 99, 0.111f, 0.222f, 0.333f, 9, "Hi", 0xFF );
	xmEx_Vsprintf   ( l_fmt, 'a', 99, 0.111f, 0.222f, 0.333f, 9, "Hi", 0xFF );
	xmEx_LogMessage ( );	

	xmEx_Scanf      ( file );
	xmEx_Vscanf     ( file );

	kdFclose ( file );
}
