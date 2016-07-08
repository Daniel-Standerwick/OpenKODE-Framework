/* --------------------------------------------------------------------------
 *
 *      File            ex_11.cpp
 *      Description     11. Time functions
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

KDvoid xmExample_11 ( KDvoid )
{	
	KDust        ust;
	KDtime       time;	
	KDTm         tm;
	
	kdLogMessage ( "Example 11. Time functions\n\n" );

	//
	//	���� : Unadjust System Time �������� (�ý����� ������ ������ ī��Ʈ �Ȱ�)
	//  ��ȯ : 64��Ʈ ����
	//
	ust = kdGetTimeUST ( );

	kdLogMessagefKHR ( "kdGetTimeUST  : %u ns", ust );

	//
	// ���� : ���� �ð��� ���Ѵ�. ( Epoch ���� )
	// ���� : ����� �ð�
	// ��ȯ : ���� �ð�
	//
	time = kdTime ( KD_NULL );
	kdTime ( &time );

	kdLogMessagefKHR ( "kdTime        : %u", time );
	//
	// ���� : 64��Ʈ ������ �ð��� �ð� ����ü�� ��ȯ�Ѵ�.
	// ���� : �Է� �ð�, ��ȯ�� �ð� ����ü
	// ��ȯ : ��ȯ�� �ð� ����ü �ּ�
	//
	kdGmtime_r ( &time, &tm );

	kdLogMessagefKHR ( "kdGmtime_r    : %04d/%02d/%02d %02d:%02d:%02d", 
		1900 + tm.tm_year, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec );

	//
	// ���� : 64��Ʈ ������ �ð��� ���� �ð� ����ü�� ��ȯ�Ѵ�.
	// ���� : �Է� �ð�, ��ȯ�� �ð� ����ü
	// ��ȯ : ��ȯ�� �ð� ����ü �ּ�
	//
	kdLocaltime_r ( &time, &tm );		

	kdLogMessagefKHR ( "kdLocaltime_r : %04d/%02d/%02d %02d:%02d:%02d", 
		1900 + tm.tm_year, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec );

	// 
	// ���� : Epoch(KDTime = 0)�� ���� �Ǵ� UST ���� �����´�.
	// ��ȯ : 64��Ʈ ����
	// 
	ust = kdUSTAtEpoch();	
	kdLogMessagefKHR ( "kdUSTAtEpoch  : %u ns", ust );
}
