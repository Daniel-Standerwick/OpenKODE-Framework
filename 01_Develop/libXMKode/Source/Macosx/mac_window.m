/* --------------------------------------------------------------------------
 *
 *      File            ios_window.m
 *      Description     Windowing
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
#include "mac_window.h"

/*
#define KFPS                                60.0
extern KDfloat          g_scale;
static KDmode           l_mode              = 0;
static KDbool           l_use_retina        = KD_TRUE;
static XMDelegate*      l_delegate          = KD_NULL;
//static NSString*      l_lastPushMessage   = KD_NULL;
static CAEAGLLayer*     l_egllayer          = KD_NULL;
// --------------------------------------------------------------------------
//
//  Location Delegate
//
// --------------------------------------------------------------------------

@implementation XMLocation
- (id) init
{
    id  ret = [super init];
    
    [self setDelegate:self];
    [self setDesiredAccuracy:kCLLocationAccuracyBestForNavigation];
    [self setDistanceFilter:kCLDistanceFilterNone];
    [self setHeadingFilter:kCLHeadingFilterNone];
    [self startUpdatingLocation];
    
    return ret;
}

- (void) dealloc
{
    [self stopUpdatingLocation];
    [super dealloc];
}

- (void) locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation;
{
    KDchar     out [ 1024 ] = "";
    KDchar     msg [ 128 ];
    
    KDchar     checksum;
    KDfloat64  tmp;
    KDint      i;
    
    KDchar     ns = 'N';
    KDchar     ew = 'E';
    KDchar     valid = 'A';
    
    KDfloat64  longitude = newLocation.coordinate.longitude;
    KDfloat64  latitude  = newLocation.coordinate.latitude;
    KDfloat64  speed     = newLocation.speed * 1.15077945;
    KDfloat64  course    = newLocation.course;
    KDfloat64  altitude  = newLocation.altitude;
    
    NSDateFormatter* formater = [[NSDateFormatter alloc] init];
    KDTm       tm;
    
    [formater setTimeZone:[NSTimeZone timeZoneWithAbbreviation:@"GMT"]];
    
    [formater setDateFormat:@"yyyy"];
    tm.tm_year  = [[formater stringFromDate:newLocation.timestamp] intValue];
    
    [formater setDateFormat:@"MM"];
    tm.tm_mon   = [[formater stringFromDate:newLocation.timestamp] intValue];
    
    [formater setDateFormat:@"dd"];
    tm.tm_mday  = [[formater stringFromDate:newLocation.timestamp] intValue];
    
    [formater setDateFormat:@"HH"];
    tm.tm_hour  = [[formater stringFromDate:newLocation.timestamp] intValue];
    
    [formater setDateFormat:@"mm"];
    tm.tm_min   = [[formater stringFromDate:newLocation.timestamp] intValue];
    
    [formater setDateFormat:@"ss"];
    tm.tm_sec   = [[formater stringFromDate:newLocation.timestamp] intValue];
    
    [formater release];
    
    if ( newLocation.horizontalAccuracy < 0 )
    {
        valid = 'V';
    }
    
    if ( speed < 0 )
    {
        speed = 0;
    }
    
    if ( course < 0 )
    {
        course = 0;
    }
    
    if ( latitude < 0 )
    {
        ew = 'S';
    }
    tmp = kdFloorKHR ( latitude );
    latitude = tmp * 100 + ( latitude - tmp ) * 60;
    
    if ( longitude < 0 )
    {
        ew = 'W';
    }
    tmp = kdFloorKHR ( longitude );
    longitude = tmp * 100 + ( longitude - tmp ) * 60;
    
    //
    // GPGGA
    //
    kdSprintfKHR ( msg, "$GPGGA,%02d%02d%02d.000,%.4f,%c,%.4f,%c,%d,%02d,%.1f,%.1f,M,%.1f,M,,0000"
                  , tm.tm_hour, tm.tm_min, tm.tm_sec                                        // UTC
                  , latitude, ns 															// Latitude
                  , longitude, ew															// Longitude
                  , 0																		// Fix Quality
                  , 0  																		// Number of Satellites
                  , 1.0 																	// Horizontal Dilution of Precision (HDOP)
                  , altitude                                                                // Altitude
                  , 0.0																		// Height of geoid above WGS84 ellipsoid
                  //, 0.0																	// Time since last DGPS update
                  //, 0																		// DGPS reference station id
                  );
    kdStrcat ( out, msg );
    
    checksum = 0;
    for ( i = 1; i < kdStrlen ( msg ); i++ )
    {
        checksum ^= msg [ i ];
    }
    kdSprintfKHR ( msg, "*%2X\n", checksum );
    kdStrcat ( out, msg );
    
    //
    // GPRMC
    //
    kdSprintfKHR ( msg, "$GPRMC,%02d%02d%02d.000,%c,%.4f,%c,%.4f,%c,%.2f,%.2f,%02d%02d%02d,,,A"
                  , tm.tm_hour, tm.tm_min, tm.tm_sec                                        // UTC
                  , valid																	// Data status (A=Valid position, V=navigation receiver warning)
                  , latitude, ns 															// Latitude
                  , longitude, ew															// Longitude
                  , speed                                                                   // Speed over ground in knots
                  , course                                                                  // Track made good in degrees True
                  , tm.tm_mday, tm.tm_mon, tm.tm_year % 100                                 // UTC Date of fix
                  //, 0.0																	// Magnetic variation
                  //,
                  );
    kdStrcat ( out, msg );
    
    checksum = 0;
    for ( i = 1; i < kdStrlen ( msg ); i++ )
    {
        checksum ^= msg [ i ];
    }
    kdSprintfKHR ( msg, "*%2X\n", checksum );
    kdStrcat ( out, msg );
    
    xmParseNMEA ( KD_TRUE, out, kdStrlen ( out ) );
}

- (void) locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    NSLog(@"Error: %@", [error description]);
}
@end


// --------------------------------------------------------------------------
//
//  Magnetometer Delegate
//
// --------------------------------------------------------------------------

@implementation XMMagnetometer
- (id)init
{
    id  ret = [super init];

    [self setDelegate:self];
    [self setDesiredAccuracy:kCLLocationAccuracyBest];
    [self setDistanceFilter:kCLDistanceFilterNone];
    [self setHeadingFilter:kCLHeadingFilterNone];
    [self startUpdatingHeading];
    
    return ret;
}

- (void)dealloc 
{
    [self stopUpdatingHeading];
    [super dealloc];
}

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)heading 
{
    KDEventMagnetometer magnetometer;
    
    magnetometer.azimuth = heading.magneticHeading;
    magnetometer.pitch   = 0;
    magnetometer.roll    = 0;
    magnetometer.x       = heading.x;
    magnetometer.y       = heading.y;
    magnetometer.z       = heading.z;
    
    _xmEventMagnetometer ( magnetometer );
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error 
{
    
}
@end

// --------------------------------------------------------------------------
//
//  Accelerometer Delegate
//
// --------------------------------------------------------------------------

@implementation XMAccelerometer
- (id)init
{
    id  ret = [super init];
    
    [[UIAccelerometer sharedAccelerometer] setDelegate:self];
    
    return ret;
}

- (void)dealloc 
{
    [[UIAccelerometer sharedAccelerometer] setDelegate:nil];
    [super dealloc];
}

- (void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    KDfloat  val[3];
	
	val[0] = acceleration.x;
	val[1] = acceleration.y;
	val[2] = acceleration.z;
    
	_xmEventAccelerometer ( val[0], val[1], val[2] );
}
@end

// --------------------------------------------------------------------------
//
//  EGL View with Touch and Virtual Keypad Delegates
//
// --------------------------------------------------------------------------

@implementation XMEGLView

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

- (id) initWithFrame:(CGRect)frame
			   scale:(KDfloat)scale
{
    if ( !( self = [super initWithFrame:frame] ) )
    {
        return nil;
    }
        
    CAEAGLLayer*  eaglLayer = (CAEAGLLayer *) self.layer;
    eaglLayer.opaque = TRUE;
    eaglLayer.contentsScale = scale;
    eaglLayer.drawableProperties = [ NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:FALSE],
                                     kEAGLDrawablePropertyRetainedBacking,
                                     l_mode & XM_SYS_RGB565 ? kEAGLColorFormatRGB565 : kEAGLColorFormatRGBA8,
                                     kEAGLDrawablePropertyColorFormat,
                                     nil ];        
    
    l_egllayer = eaglLayer;
    m_cx = frame.size.width  * scale;
    m_cy = frame.size.height * scale;
    
    if ( ( l_mode & XM_SYS_GLES_V1 ) || ( l_mode & XM_SYS_GLES_V2 ) )
    {    
        m_context = l_mode & XM_SYS_GLES_V2 ? [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] :
                                          [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1] ;
        if ( !m_context || ![EAGLContext setCurrentContext:m_context] )
        {
            [self release];
            kdLogMessage ( "Allocate EAGL Context failed." );
            kdExit ( 3 );
            return nil;
        }
	   
        m_depth = 0;
        m_msaa_color = 0;
    
        glGenFramebuffers ( 1, &m_frame );
        NSAssert ( m_frame, @"Can't create frame buffer" );
    
        glGenRenderbuffers ( 1, &m_color );
        NSAssert ( m_color, @"Can't create render buffer" );
    
        glBindFramebuffer  ( GL_FRAMEBUFFER , m_frame );
        glBindRenderbuffer ( GL_RENDERBUFFER, m_color );
        glFramebufferRenderbuffer ( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_color );

        [EAGLContext setCurrentContext:m_context];
    
    }
    
    [self setMultipleTouchEnabled:YES];

    g_scale   = scale;
    m_scale   = scale;
    m_live    = KD_FALSE;
    m_visible = KD_FALSE;
    
    kdMemset ( m_touches, 0, sizeof ( m_touches ) );
    
    return self;
}

- (void) dealloc
{
    if ( ( l_mode & XM_SYS_GLES_V1 ) || ( l_mode & XM_SYS_GLES_V2 ) )
    {
        EAGLContext*  context;

        context = [EAGLContext currentContext];
        if ( context != m_context )
        {
            [EAGLContext setCurrentContext:m_context];
        }
	
        if ( m_depth )
        {
            glDeleteRenderbuffers ( 1, &m_depth );
            m_depth = 0;
        }
	
        if ( m_color )
        {
            glDeleteRenderbuffers ( 1, &m_color );
            m_color = 0;
        }
	
        if ( m_frame )
        {
            glDeleteFramebuffers ( 1, &m_frame );
            m_frame = 0;
        }
    
        if ( m_msaa_color )
        {
            glDeleteRenderbuffers ( 1, &m_msaa_color );
            m_msaa_color = 0;
        }
    
        if ( m_msaa_frame )
        {
            glDeleteRenderbuffers ( 1, &m_msaa_frame );
            m_msaa_frame = 0;
        }
	
        if ( context != m_context )
        {
            [EAGLContext setCurrentContext:context];
        }
	
        [m_context release];
        m_context = nil;	
	
    }

    [super dealloc];
}

- (void) layoutSubviews
{
    CAEAGLLayer*  eaglLayer = (CAEAGLLayer *) self.layer;
    
    GLint   cx = m_cx;
	GLint   cy = m_cy;
    
    if ( ( l_mode & XM_SYS_GLES_V1 ) || ( l_mode & XM_SYS_GLES_V2 ) )
    {
        glBindRenderbuffer ( GL_RENDERBUFFER, m_color );
    
        if ( ![m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer] )
        {
            NSLog ( @"failed to call context" );
        }
    
        GLenum  error;    
    
        glGetRenderbufferParameteriv ( GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH , &cx );
        glGetRenderbufferParameteriv ( GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &cy );

        if ( !m_depth )
        {
            glGenRenderbuffers ( 1, &m_depth );
            NSAssert ( m_depth, @"Can't create depth buffer" );
        }
    
        glBindRenderbuffer ( GL_RENDERBUFFER, m_depth );

            glRenderbufferStorage ( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, cx, cy );
    
        glFramebufferRenderbuffer ( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT  , GL_RENDERBUFFER, m_depth );
        glFramebufferRenderbuffer ( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth );
    
        glBindRenderbuffer ( GL_RENDERBUFFER, m_color );
    
        if ( ( error = glCheckFramebufferStatus ( GL_FRAMEBUFFER ) ) != GL_FRAMEBUFFER_COMPLETE )
        {
            NSLog ( @"Failed to make complete framebuffer object 0x%X", error );        
        }
    }
    else
    {
        if ( l_mode & XM_SYS_LANDSCAPE )
        {
            KD_SWAP ( cx, cy, KDint );
        }
    }
    
    static KDbool  bOnce = KD_FALSE;
    
    if ( !bOnce )
    {
        bOnce = KD_TRUE;
        
        _xmEventCreate ( (XMWindow) l_delegate->m_root );                
    }
    
    _xmEventResize ( cx, cy );
}

- (void) renderScene
{
    if ( m_live == KD_FALSE || m_visible == KD_FALSE )
	{
		return;
	}

    static KDuint    old_msec = 0;
    KDuint           new_msec = KD_GET_UST2MSEC;
    
	if ( g_interval == 0 || ( new_msec - old_msec ) > ( g_interval - 1 ) || new_msec < old_msec )
	{
		old_msec = new_msec;    
        
		_xmEventRedraw ( );
		
        if ( ( l_mode & XM_SYS_GLES_V1 ) || ( l_mode & XM_SYS_GLES_V2 ) )
        {
    
            if ( ![m_context presentRenderbuffer:GL_RENDERBUFFER] )
            {
                kdLogMessage ( "Failed to swap renderbuffer." );
            }		
        }
        
        _xmEventUpdate ( );
	}
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint	 point;
    KDuint   i = 0;
    
	for ( UITouch *touch in touches )
	{		
		point = [touch locationInView:self];
		
        m_touches [ i ].id = (KDvoid*) touch;
        m_touches [ i ].x  = point.x * m_scale;
        m_touches [ i ].y  = point.y * m_scale;
        i++;
	}
    
    if ( i > 0 )
    {
        _xmEventTouchBegan ( m_touches, i );
    }
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint	 point;
    KDuint   i = 0;
	
	for ( UITouch *touch in touches )
	{		
		point = [touch locationInView:self];
		
        m_touches [ i ].id = (KDvoid*) touch;
        m_touches [ i ].x  = point.x * m_scale;
        m_touches [ i ].y  = point.y * m_scale;
        i++;
	}
    
    if ( i > 0 )
    {
        _xmEventTouchMoved ( m_touches, i );
    }
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint	 point;
    KDuint   i = 0;
	
	for ( UITouch *touch in touches )
	{		
		point = [touch locationInView:self];
		
        m_touches [ i ].id = (KDvoid*) touch;
        m_touches [ i ].x  = point.x * m_scale;
        m_touches [ i ].y  = point.y * m_scale;
        i++;
	}
    
    if ( i > 0 )
    {
        _xmEventTouchEnded  ( m_touches, i );
    }
}

- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint	 point;
    KDuint   i = 0;
    
    for ( UITouch *touch in touches )
    {
        point = [touch locationInView:self];
        
        m_touches [ i ].id = (KDvoid*) touch;
        m_touches [ i ].x  = point.x;
        m_touches [ i ].y  = point.y;
        i++;
    }
    
    if ( i > 0 )
    {    
        _xmEventTouchCancelled ( m_touches, i );
    }
}

- (void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration 
{
	KDfloat    val[3];
	
	val[0] = acceleration.x; // -9.81f;
	val[1] = acceleration.y; // -9.81f;
	val[2] = acceleration.z; // -9.81f;
    
	_xmEventAccelerometer ( val[0], val[1], val[2] );
}

- (void)didMoveToWindow;
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardWillShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardDidShowNotification object:nil];
	
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardWillHideNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardDidHideNotification object:nil];
}

- (BOOL)canBecomeFirstResponder
{
	if ( nil != m_markedText )
	{
		[m_markedText release];
	}
    m_markedText = nil;
    return YES;
}

- (BOOL)hasText
{
    return NO;
}

- (void)insertText:(NSString *)text
{
	if ( nil != m_markedText ) 
	{
		[m_markedText release];
		m_markedText = nil;
	}
	
    const char* pszText = [text cStringUsingEncoding:NSUTF8StringEncoding];	
	_xmEventInsertText ( pszText, strlen ( pszText ) );
}

- (void)deleteBackward
{
	if ( nil != m_markedText )
	{
		[m_markedText release];
		m_markedText = nil;
	}
	
	_xmEventKeyPressed ( KD_INPUT_XMSOFT_BACKSPACE );
}

#pragma mark -
#pragma mark UITextInputTrait protocol
-(UITextAutocapitalizationType) autocapitalizationType
{
    return UITextAutocapitalizationTypeNone;
}

#pragma mark -
#pragma mark UITextInput protocol
#pragma mark UITextInput - properties

@synthesize beginningOfDocument;
@synthesize endOfDocument;
@synthesize inputDelegate;
@synthesize markedTextRange;
@synthesize markedTextStyle;
// @synthesize selectedTextRange;       // must implement
@synthesize tokenizer;

- (void) setSelectedTextRange:(UITextRange *)aSelectedTextRange;
{
 
}

- (UITextRange *)selectedTextRange;
{
	return [[[UITextRange alloc] init] autorelease];
}

#pragma mark UITextInput - Replacing and Returning Text

- (NSString *)textInRange:(UITextRange *)range;
{
	return @"";
}

- (void)replaceRange:(UITextRange *)range withText:(NSString *)theText;
{
   
}

#pragma mark UITextInput - Working with Marked and Selected Text

- (void)setMarkedTextRange:(UITextRange *)markedTextRange;
{

}

- (UITextRange *) markedTextRange;
{
	return nil; 
}

- (void)setMarkedTextStyle:(NSDictionary *)markedTextStyle;
{
    
}
 
- (NSDictionary *) markedTextStyle;
{
	return nil;
}

- (void)setMarkedText:(NSString *)markedText selectedRange:(NSRange)selectedRange;
{
	if ( markedText == m_markedText ) 
	{
		return;
	}
	if ( nil != m_markedText ) 
	{
		[m_markedText release];
	}
    m_markedText = markedText;
	[m_markedText retain];
}

- (NSArray *) selectionRectsForRange:(UITextRange *)range
{
    return nil;
}

- (void) unmarkText;
{ 
    if ( nil == m_markedText )
    {
        return;
    }
	
    const char*  pszText = [m_markedText cStringUsingEncoding:NSUTF8StringEncoding];
	
    _xmEventInsertText ( pszText, strlen ( pszText ) );
    
	[m_markedText release];
    m_markedText = nil;
}

#pragma mark Methods for creating ranges and positions.
- (UITextRange *) textRangeFromPosition:(UITextPosition *)fromPosition toPosition:(UITextPosition *)toPosition;
{
	return nil;
}

- (UITextPosition *) positionFromPosition:(UITextPosition *)position offset:(NSInteger)offset;
{
	return nil;
}

- (UITextPosition *) positionFromPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset;
{
	return nil;
}

- (NSComparisonResult) comparePosition:(UITextPosition *)position toPosition:(UITextPosition *)other;
{
	return 0;
}

- (NSInteger) offsetFromPosition:(UITextPosition *)from toPosition:(UITextPosition *)toPosition;
{
	return 0;
}

- (UITextPosition *) positionWithinRange:(UITextRange *)range farthestInDirection:(UITextLayoutDirection)direction;
{
	return nil;
}

- (UITextRange *)characterRangeByExtendingPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction;
{
	return nil;
}

#pragma mark Writing direction

- (UITextWritingDirection) baseWritingDirectionForPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;
{
	return UITextWritingDirectionNatural;
}

- (void) setBaseWritingDirection:(UITextWritingDirection) writingDirection forRange:(UITextRange *)range;
{
  
}

#pragma mark Geometry

- (CGRect) firstRectForRange:(UITextRange *)range;
{
	return CGRectNull;
}

- (CGRect) caretRectForPosition:(UITextPosition *)position;
{
	return m_caretRect;
}

#pragma mark Hit testing

- (UITextPosition *)closestPositionToPoint:(CGPoint)point;
{
	return nil;
}

- (UITextPosition *) closestPositionToPoint:(CGPoint)point withinRange:(UITextRange *)range;
{
	return nil;
}

- (UITextRange *) characterRangeAtPoint:(CGPoint)point;
{
	return nil;
}

#pragma mark -
#pragma mark UIKeyboard notification

- (void) onUIKeyboardNotification:(NSNotification *)notif;
{

}
@end

@implementation XMRootView

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ( l_mode & XM_SYS_LANDSCAPE )
    {
        return UIInterfaceOrientationIsLandscape ( interfaceOrientation );
    }
    else
    {
        return UIInterfaceOrientationIsPortrait ( interfaceOrientation );
    }
}

- (NSUInteger) supportedInterfaceOrientations
{
#ifdef __IPHONE_6_0
    if ( l_mode & XM_SYS_LANDSCAPE )
    {
        return UIInterfaceOrientationMaskLandscape;
    }
    else
    {
        return ( UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskPortraitUpsideDown );
    }
#endif
}

- (BOOL) shouldAutorotate
{
    return YES;
}

- (void) didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void) viewDidUnload
{
    [super viewDidUnload];
}

- (void)dealloc
{
    [super dealloc];
}
@end


// --------------------------------------------------------------------------
//
//  Application Delegate
//
// --------------------------------------------------------------------------

@implementation XMDelegate

- (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{           
    l_delegate      = self;
    m_magnetometer  = nil;
    m_accelerometer = nil;
    
    if ( l_mode & XM_SYS_STATUS_BAR )
    {
        [[UIApplication sharedApplication] setStatusBarHidden: NO];
    }
    else
    {
        [[UIApplication sharedApplication] setStatusBarHidden: YES];
    }
    
    KDfloat  scale = 1;
    if ( l_use_retina && ( [[UIScreen mainScreen] respondsToSelector:@selector(scale)] ) )
    {
        scale = [[UIScreen mainScreen] scale];
    }
    
    // Add the view controller's view to the window and display.
	m_window = [[UIWindow  alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    m_view   = [[XMEGLView alloc] initWithFrame:[m_window bounds] scale:scale];
        
    // Use RootViewController manage EAGLView
    m_root = [[XMRootView alloc] initWithNibName:nil bundle:nil];
    m_root.wantsFullScreenLayout = NO;
    m_root.view = m_view;
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0 )
    {
        [m_window addSubview: m_root.view];                
    }
    else
    {
        [m_window setRootViewController:m_root];
    }        
    
	[m_window makeKeyAndVisible];    
	
	m_view->m_live    = KD_TRUE;
	m_view->m_visible = KD_TRUE;
	
	[UIApplication sharedApplication].idleTimerDisabled = YES;
	m_timer = [NSTimer scheduledTimerWithTimeInterval:(1.0 / KFPS) target:m_view selector:@selector(renderScene) userInfo:nil repeats:YES];
    
    m_brightness = [UIScreen mainScreen].brightness;
 
	//-----------------------------------------------------------------
	// PushNotification handler..
	//-----------------------------------------------------------------

    return YES;
}

- (void) applicationWillTerminate:(UIApplication *)application;
{
	kdExit ( 0 );
}

- (void) applicationWillEnterForeground:(UIApplication *)application;
{
	m_view->m_visible = KD_TRUE;
	
	_xmEventVisible ( 1 );
}

- (void) applicationDidEnterBackground:(UIApplication *)application;
{
	m_view->m_visible = KD_FALSE;
	
	_xmEventVisible ( 0 );
}

- (void) applicationDidBecomeActive:(UIApplication *)application;
{
	_xmEventFocus ( 1 );
}

- (void) applicationWillResignActive:(UIApplication *)application;
{
	_xmEventFocus ( 0 );
}

- (void) applicationDidReceiveMemoryWarning:(UIApplication *)application
{
	_xmEventMemoryWarning ( );
}

- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
	NSLog ( @"deviceToken : %@", deviceToken );
    
	//
	// Notify to xmcocos2d
	//
	NSUInteger len = [deviceToken length];
	//
	KDEvent*  event = kdCreateEvent ( );
	if ( event )
	{
		event->type = KD_APNS_DEVIDREG_OK;
		event->userptr = (KDvoid*) [deviceToken bytes];
		event->data.user.value1.i32pair.a = len;
        _xmEventSend ( event );
	}
}

- (void) application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
	NSLog ( @"deviceToken error : %@", error );
	
	NSString* str = [error localizedDescription];
	const KDchar* szStr = [str UTF8String];
	NSUInteger len = kdStrlen ( szStr );
    
	//
	// Notify to xmcocos2d
	//
	KDEvent*  event = kdCreateEvent ( );
	if ( event )
	{
		event->type = KD_APNS_DEVIDREG_FAIL;
		event->userptr = (KDvoid*) szStr;
		event->data.user.value1.i32pair.a = len;
		event->data.user.value1.i32pair.b = [ error code ];
		_xmEventSend ( event );
	}
}

- (void) application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
	NSDictionary* aps = [userInfo valueForKey:@"aps"];
	
	NSString* str = [aps valueForKey:@"customvalue1"];
	const KDchar* szStr = [str UTF8String];
	
	// UTF8String
	NSLog ( @"userInfo Alert : %@", str );
	
	//
	// Notify to xmcocos2d
	//
	NSUInteger  len = kdStrlen ( szStr );
	KDEvent*  event = kdCreateEvent ( );
	if ( event )
	{
		event->type = KD_APNS_NOTIFY_RECEIVED;
		event->userptr = (KDvoid*) szStr;
		event->data.user.value1.i32pair.a = len;
		_xmEventSend ( event );
	}
}

- (void) dealloc
{
    [[UIScreen mainScreen] setBrightness:m_brightness];
    
    l_delegate = nil;
    
   	[m_view    release];
	[m_window  release];
    
    [super dealloc];
}

@end

*/
// --------------------------------------------------------------------------
//
//  Window Functions
//
// --------------------------------------------------------------------------

// xmPlatformRealizeWindow : Realize window and ready event loop in platform specific.
KDvoid xmPlatformRealizeWindow ( KDmode mode )
{
    NSApplicationMain(argc, (const char **)argv);
}

// xmPlatformFreeWindow : Release window resources in platform specific.
KDvoid xmPlatformFreeWindow ( KDvoid )
{

}
/*
KDvoid  xmPlatformEventAttach ( KDenum mode )
{
    if ( mode & XM_SYS_LOCATION )
    {
        if ( l_delegate->m_location == nil )
        {
             l_delegate->m_location = [[XMLocation alloc] init];
        }
    }
    
    if ( mode & XM_SYS_MAGNETOMETER )
    {
        if ( l_delegate->m_magnetometer == nil )
        {
             l_delegate->m_magnetometer = [[XMMagnetometer alloc] init];
        }
    }
    
    if ( mode & XM_SYS_ACCELEROMETER )
    {
        if ( l_delegate->m_accelerometer == nil )
        {  
             l_delegate->m_accelerometer = [[XMAccelerometer alloc] init];
        }
    }
}

KDvoid  xmPlatformEventDetach ( KDenum mode )
{
    if ( mode & XM_SYS_LOCATION )
    {
        if ( l_delegate->m_location != nil )
        {
            [l_delegate->m_location release];
             l_delegate->m_location = nil;
        }
    }
    
    if ( mode & XM_SYS_MAGNETOMETER )
    {
        if ( l_delegate->m_magnetometer != nil )
        {
            [l_delegate->m_magnetometer release];
             l_delegate->m_magnetometer = nil;
        }
    }    
    
    if ( mode & XM_SYS_ACCELEROMETER )
    {
        if ( l_delegate->m_accelerometer != nil )
        {
            [l_delegate->m_accelerometer release];
             l_delegate->m_accelerometer = nil;
        }
    }        
}

// xmPlatformSetFPS : Set FPS. 
// It's not exactly same interval timing.
// If input value is 0 then no interval timing. 
KDvoid xmPlatformSetFPS ( KDuint fps )
{   
	if ( l_delegate )
	{
		if ( l_delegate->m_timer != nil )
		{
			[l_delegate->m_timer invalidate];
		}
		
        KDfloat  inteval = ( g_interval == 0 ? 1.0 / KFPS : g_interval * 0.001 );
		l_delegate->m_timer = [NSTimer scheduledTimerWithTimeInterval:inteval
                                       target:l_delegate->m_view selector:@selector(renderScene)
                                       userInfo:nil repeats:YES];
	}
}

KDvoid xmPlatformSetIMEKeyboardState ( KDbool show )
{
    if ( show )
    {
        [l_delegate->m_view becomeFirstResponder];
    }
    else
    {
        [l_delegate->m_view resignFirstResponder];
    }	
}

KDvoid xmWinSetProperty ( KDbool use_retina )
{
    l_use_retina  = use_retina;
}

KDvoid xmPlatformSetBrightness ( KDfloat value )
{
    if ( value == -1.0f )
    {
        value = l_delegate->m_brightness;
    }
    else if ( value < 0 )
    {
        value = 0;
    }
    else if ( value > 1 )
    {
        value = 1;
    }
    
    [[UIScreen mainScreen] setBrightness:value];
}

KDvoid xmPlatformSetFullScreen ( KDbool enable )
{
    [[UIApplication sharedApplication] setStatusBarHidden: enable ? YES : NO];
}

// For AREM Engine.
KD_API XMAREM KD_APIENTRY xmGetAREM ( KDvoid )
{
    return (XMAREM) l_egllayer;
}
*/