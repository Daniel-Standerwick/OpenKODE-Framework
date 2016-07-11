/*
 *
 *      File            main.cpp
 *      Description     XMGraphics : Camera demo application
 *      Version         0.20.0801, 2011-08-01
 *      Author          Y.H Mun
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (C) 2010-2011 XMSoft. All rights reserved.
 * 
 *      Contact Email: chris@xmsoft.co.kr 
 *                     xmsoft77@gmail.com	
 * 
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
 */

#include "main.h"
#include "platform.h"

XM_APP_MAIN_BEGIN
	XM_APP_WND_REALIZE(XM_SYS_DEFAULT)
XM_APP_MAIN_END

KDvoid xmEventCreate ( KDvoid )
{	
	KD_SET_TLS ( KDTLS );
	KD_GET_TLS ( KDTLS, tls );

	XMGRectF     rect;
	XMGVector2F  size;

	tls->xmg_canvas  = new XMGCanvas ( );	
	tls->xmg_view[0] = new XMGView ( );
	tls->xmg_view[1] = new XMGView ( );
	tls->xmg_font[0] = new XMGFont ( "/res/font/COOPBL.TTF" );
	tls->xmg_font[1] = new XMGFont ( "/res/font/BrushScriptStd.otf" );
	tls->xmg_tex     = new XMGTexture ( "/res/image/combinedtextures.jpg" );
	tls->xmg_text    = new XMGText ( 2 );
	tls->xmg_wall    = new XMGQuad ( 1, XMG_GEO_BWALL );
	
	tls->xmg_text->SetFont ( tls->xmg_font[ 0 ], 0 );
	tls->xmg_text->SetText ( "XMGraphics : Camera demo", 0 );

	tls->xmg_text->SetFont ( tls->xmg_font[ 1 ], 1 );
	tls->xmg_text->SetLineAlign ( XMG_ALIGN_CENTER, 1 );				
	tls->xmg_text->SetColor ( XMGColorF ( 1.0f, 0.6f, 0.3f, 1.0f ), 1 );
	
	tls->xmg_tex->GetImageSize ( size );
	
	size.m_x *= 0.5f;
	size.m_y *= 0.5f;

	rect = XMGRectF ( -1.0f, -0.5f, 2.0f, 2.0f, 1.0f );

	tls->xmg_wall->SetCull ( XMG_CULL_FRONT );
	tls->xmg_wall->SetVertexArray ( &rect );

	tls->xmg_wall->SetTexture ( tls->xmg_tex, XMGRectF ( size.m_x, size.m_y, size.m_x, size.m_y ), XMG_TEX_UNIT_0, 0, 0 );	
	tls->xmg_wall->SetTexture ( tls->xmg_tex, XMGRectF (        0,        0, size.m_x, size.m_y ), XMG_TEX_UNIT_0, 0, 1 );	
	tls->xmg_wall->SetTexture ( tls->xmg_tex, XMGRectF (        0, size.m_y, size.m_x, size.m_y ), XMG_TEX_UNIT_0, 0, 2 );	
	tls->xmg_wall->SetTexture ( tls->xmg_tex, XMGRectF ( size.m_x,        0, size.m_x, size.m_y ), XMG_TEX_UNIT_0, 0, 3 );	
}

KDvoid xmEventDestroy ( KDvoid )
{
	KD_GET_TLS ( KDTLS, tls );
	
	delete tls->xmg_wall;
	delete tls->xmg_text;
	delete tls->xmg_tex;
	delete tls->xmg_font[0];
	delete tls->xmg_font[1];
	delete tls->xmg_view[0];
	delete tls->xmg_view[1];
	delete tls->xmg_canvas;
}

KDvoid xmEventRedraw ( KDvoid )
{	
	KD_GET_TLS ( KDTLS, tls );

	tls->xmg_canvas->Clear ( );

	tls->xmg_view[ 0 ]->Update ( );
	for ( GLuint idx = 0; idx < 5; idx++ )
	{		
		tls->xmg_canvas->Translate ( XMGVector3F ( 0.0f, 0.0f, -2.0f ) );
		tls->xmg_wall->Render ( );
	}

	tls->xmg_view[ 1 ]->Update ( );
	tls->xmg_text->Render ( );

	tls->xmg_canvas->Flush ( );
}

KDvoid xmEventUpdate ( KDuint msec )
{	
	KD_GET_TLS ( KDTLS, tls );

	switch ( tls->app_index )
	{
		case 0 :

			if ( tls->app_count == 0 )
			{
				tls->xmg_text->SetText ( "WALK ( + )", 1 );
			}
			else if ( tls->app_count < 100 )
			{
				tls->xmg_view[ 0 ]->Walk ( 0.02f );
			}
			else if ( tls->app_count == 100 )
			{
				tls->xmg_text->SetText ( "WALK ( - )", 1 );
			}
			else if ( tls->app_count < 200 )
			{
				tls->xmg_view[ 0 ]->Walk ( -0.02f );
			}
			else
			{
				tls->app_index++;
				tls->app_count = 0;
				return;
			}

			break;

		case 1 :

			if ( tls->app_count == 0 )
			{
				tls->xmg_text->SetText ( "FLY ( + )", 1 );
			}
			else if ( tls->app_count < 100 )
			{
				tls->xmg_view[ 0 ]->Fly ( 0.003f );
			}
			else if ( tls->app_count == 100 )
			{
				tls->xmg_text->SetText ( "FLY ( - )", 1 );
			}
			else if ( tls->app_count < 200 )
			{
				tls->xmg_view[ 0 ]->Fly ( -0.003f );
			}
			else
			{
				tls->app_index++;
				tls->app_count = 0;
				return;
			}

			break;

		case 2 :

			if ( tls->app_count == 0 )
			{
				tls->xmg_text->SetText ( "STRAFE ( + )", 1 );
			}
			else if ( tls->app_count < 100 )
			{
				tls->xmg_view[ 0 ]->Strafe ( 0.008f );
			}
			else if ( tls->app_count == 100 )
			{
				tls->xmg_text->SetText ( "STRAFE ( - )", 1 );
			}
			else if ( tls->app_count < 200 )
			{
				tls->xmg_view[ 0 ]->Strafe ( -0.008f );
			}
			else
			{
				tls->app_index++;
				tls->app_count = 0;
				return;
			}

			break;

		case 3 :

			if ( tls->app_count == 0 )
			{
				tls->xmg_text->SetText ( "ROTATE ( + )", 1 );
			}
			else if ( tls->app_count < 100 )
			{
				tls->xmg_view[ 0 ]->RotateY ( 0.5f );
			}
			else if ( tls->app_count == 100 )
			{
				tls->xmg_text->SetText ( "ROTATE ( - )", 1 );
			}
			else if ( tls->app_count < 200 )
			{
				tls->xmg_view[ 0 ]->RotateY ( -0.5f );
			}
			else
			{
				tls->app_index++;
				tls->app_count = 0;
				return;
			}

			break;

		case 4 :

			if ( tls->app_count == 0 )
			{
				tls->xmg_text->SetText ( "TILT ( + )", 1 );
			}
			else if ( tls->app_count < 100 )
			{
				tls->xmg_view[ 0 ]->Tilt ( 0.4f );
			}
			else if ( tls->app_count == 100 )
			{
				tls->xmg_text->SetText ( "TILT ( - )", 1 );
			}
			else if ( tls->app_count < 200 )
			{
				tls->xmg_view[ 0 ]->Tilt ( -0.4f );
			}
			else
			{
				tls->app_index = 0;
				tls->app_count = 0;
				return;
			}

			break;
	}

	tls->app_count++;
}

KDvoid xmEventResize ( KDint width, KDint height )
{
	KD_GET_TLS ( KDTLS, tls );
	
	XMGRectF  wnd = XMGRectF ( 0, 0, 0, XMG_I2F ( width ), XMG_I2F ( height ) );
	GLfloat   aspect = aspect = height > width ? wnd.m_h / wnd.m_w : wnd.m_w / wnd.m_h;

	XMGMatrix4F  mat[2];
	GLuint       idx;	

	tls->xmg_canvas->Perspective ( width, height );

	mat[ 0 ].Perspective ( 45.0f, aspect, 0.1f, 500.0f );	
	mat[ 1 ].Ortho ( 0.0f, wnd.m_w, 0.0f, wnd.m_h, -1.0f, 100.0f );	

	for ( idx = 0; idx < 2; idx++ )
	{
		tls->xmg_view[ idx ]->SetViewport ( wnd );	
		tls->xmg_view[ idx ]->SetProject ( mat[ idx ] );
	}

	tls->xmg_text->SetPosition ( XMGVector3F ( 5.0f, wnd.m_h - 20.0f ), 0 );
	tls->xmg_text->SetPosition ( XMGVector3F ( 5.0f, wnd.m_h / 5.0f - 20.0f ), 1 );
	tls->xmg_text->SetLineLength ( wnd.m_w - 5.0f );	
}

KD_API KDvoid KD_APIENTRY xmEventProc(const KDEvent* event)
{
	switch (event->type)
	{
		case KD_EVENT_NATIVE:
		{
			//#if !defined ( SHP ) && defined ( _WIN32 ) 
			//KDEventNativeWin32*  proc = (KDEventNativeWin32*) event->data.native.p;
			//KDEventNativeLinux*  proc = (KDEventNativeLinux*) event->data.native.p;
			//#endif
		}	break;

		case KD_EVENT_CREATE:
		{
			// event->data.size.width;
			// event->data.size.height;
			xmEventCreate();
			xmEventResize(event->data.size.width, event->data.size.height);
		}	break;

		case KD_EVENT_DESTROY:
		{
			xmEventDestroy();
		}	break;

		case KD_EVENT_RESIZE:
		{
			// event->data.size.width;
			// event->data.size.height;	
			xmEventResize(event->data.size.width, event->data.size.height);
		}	break;

		case KD_EVENT_FOCUS:
		{
			// event->data.value.i;
			// 1 : focus
		}	break;

		case KD_EVENT_VISIBLE:
		{
			// event->data.value.i;
			// 1 : visible
		}	break;

		case KD_EVENT_REDRAW:
		{
			xmEventRedraw();
		}	break;

		case KD_EVENT_UPDATE:
		{
			// event->data.update.msec;
			xmEventUpdate(event->data.update.msec);
		}	break;

		case KD_EVENT_TOUCH_BEGAN:
		{
			// event->data.touch.touches;
			// event->data.touch.count;
		}	break;

		case KD_EVENT_TOUCH_MOVED:
		{

		}	break;

		case KD_EVENT_TOUCH_ENDED:
		{

		}	break;

		case KD_EVENT_TOUCH_CANCELLED:
		{

		}	break;

		case KD_EVENT_KEY_RELEASED:
		{
			// event->data.keypad.code;		
		}	break;

		case KD_EVENT_KEY_PRESSED:
		{

		}	break;

		case KD_EVENT_ACCELEROMETER:
		{
			// event->data.accelerometer.x;
			// event->data.accelerometer.y;
			// event->data.accelerometer.z;
		}	break;

		case KD_EVENT_LOCATION:
		{
			// event->data.value.i;
			// KD_NMEA_UPDATED_GPS, KD_NMEA_UPDATED_USER
		}	break;

		case KD_EVENT_INSERT_TEXT:
		{
			// event->data.insert.utf8;
		}	break;

		case KD_EVENT_SERIALIZE:
		{
			// event->data.serialize.type;
			// event->data.serialize.data;
			// event->data.serialize.size;
		}	break;
	}
}