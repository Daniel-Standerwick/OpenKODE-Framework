/* -----------------------------------------------------------------------------------
 *
 *      File            CCGLProgram.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2013 XMSoft
 *      Copyright (c) 2010-2013 cocos2d-x.org
 *      Copyright (c) 2011 Jeff Lamarche
 *      Copyright (c) 2012 Goffredo Marocchi
 *      Copyright (c) 2012 Ricardo Quesada
 *
 *         http://www.cocos2d-x.org      
 *
 * -----------------------------------------------------------------------------------
 * 
 *     Permission is hereby granted, free of charge, to any person obtaining a copy
 *     of this software and associated documentation files (the "Software"), to deal
 *     in the Software without restriction, including without limitation the rights
 *     to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *     copies of the Software, and to permit persons to whom the Software is
 *     furnished to do so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included in
 *     all copies or substantial portions of the Software.
 *     
 *     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *     THE SOFTWARE.
 *
 * ----------------------------------------------------------------------------------- */ 

#ifndef __CCGLProgram_h__
#define __CCGLProgram_h__

#include "../cocoa/CCObject.h"
#include "../ccConfig.h"

NS_CC_BEGIN

/**
 * @addtogroup shaders
 * @{
 */

enum 
{
    kCCVertexAttrib_Position	,
    kCCVertexAttrib_Color		,
    kCCVertexAttrib_TexCoords	,
    kCCVertexAttrib_MAX			,
};

enum 
{
	kCCUniformPMatrix			,
	kCCUniformMVMatrix			,
	kCCUniformMVPMatrix			,
	kCCUniformTime				,
	kCCUniformSinTime			,
	kCCUniformCosTime			,
	kCCUniformRandom01			,
	kCCUniformSampler			,
    
	kCCUniform_MAX,
};

#define kCCShader_PositionTextureColor				"ShaderPositionTextureColor"
#define kCCShader_PositionTextureColorAlphaTest		"ShaderPositionTextureColorAlphaTest"
#define kCCShader_PositionColor						"ShaderPositionColor"
#define kCCShader_PositionTexture					"ShaderPositionTexture"
#define kCCShader_PositionTexture_uColor			"ShaderPositionTexture_uColor"
#define kCCShader_PositionTextureA8Color			"ShaderPositionTextureA8Color"
#define kCCShader_Position_uColor					"ShaderPosition_uColor"
#define kCCShader_PositionLengthTexureColor         "ShaderPositionLengthTextureColor"

// uniform names
#define kCCUniformPMatrix_s							"CC_PMatrix"
#define kCCUniformMVMatrix_s						"CC_MVMatrix"
#define kCCUniformMVPMatrix_s						"CC_MVPMatrix"
#define kCCUniformTime_s							"CC_Time"
#define kCCUniformSinTime_s							"CC_SinTime"
#define kCCUniformCosTime_s							"CC_CosTime"
#define kCCUniformRandom01_s						"CC_Random01"
#define kCCUniformSampler_s							"CC_Texture0"
#define kCCUniformAlphaTestValue					"CC_alpha_value"

// Attribute names
#define	kCCAttributeNameColor						"a_color"
#define	kCCAttributeNamePosition					"a_position"
#define	kCCAttributeNameTexCoord					"a_texCoord"

struct _hashUniformEntry;

typedef KDvoid (*GLInfoFunction) ( GLuint uProgram, GLenum uPname, GLint* pParams );
typedef KDvoid (*GLLogFunction ) ( GLuint uProgram, GLsizei uSize, GLsizei* pLength, GLchar* szInfoLog );

/** 
 *	CCGLProgram
 *	Class that implements a glProgram
 *	@since v2.0.0
 */
class CCGLProgram : public CCObject
{
	public :
				 CCGLProgram ( KDvoid );
		virtual ~CCGLProgram ( KDvoid );

	public :

		/** Initializes the CCGLProgram with a vertex and fragment with bytes array */
		virtual KDbool			initWithVertexShaderByteArray ( const GLchar* pVShaderByteArray, const GLchar* pFShaderByteArray );

	#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WINRT ) || ( CC_TARGET_PLATFORM == CC_PLATFORM_WP8 )
		/** Initializes the CCGLProgram with precompiled shader program */
		virtual KDbool			initWithPrecompiledProgramByteArray ( const GLchar* pShaderByteArray, GLint nLength );
	#endif

		/** Initializes the CCGLProgram with a vertex and fragment with contents of filenames */
		virtual KDbool			initWithVertexShaderFilename ( const KDchar* szVShaderFilename, const KDchar* szFShaderFilename );

		/**  It will add a new attribute to the shader */
		KDvoid					addAttribute ( const KDchar* szAttributeName, GLuint uIndex );

		/** links the glProgram */
		KDbool					link ( KDvoid );

		/** it will call glUseProgram() */
		KDvoid					use ( KDvoid );

		/** It will create 4 uniforms:
		 *		- kCCUniformPMatrix
		 *		- kCCUniformMVMatrix
		 *		- kCCUniformMVPMatrix
		 *		- kCCUniformSampler
		 *
		 *	And it will bind "kCCUniformSampler" to 0
		 *
		 */
		KDvoid					updateUniforms ( KDvoid );

		/** calls retrieves the named uniform location for this shader program. */
		GLint					getUniformLocationForName ( const KDchar* szName );

		/** calls glUniform1i only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith1i ( GLint nLocation, GLint i1 );

		/** calls glUniform2i only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith2i ( GLint nLocation, GLint i1, GLint i2 );
	    
		/** calls glUniform3i only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith3i ( GLint nLocation, GLint i1, GLint i2, GLint i3 );
	    
		/** calls glUniform4i only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith4i ( GLint nLocation, GLint i1, GLint i2, GLint i3, GLint i4 );
	    
		/** calls glUniform2iv only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith2iv ( GLint nLocation, GLint* ints, GLuint uNumberOfArrays );
	    
		/** calls glUniform3iv only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith3iv ( GLint nLocation, GLint* ints, GLuint uNumberOfArrays );
	    
		/** calls glUniform4iv only if the values are different than the previous call for this same shader program. */
	    
		KDvoid					setUniformLocationWith4iv ( GLint nLocation, GLint* ints, GLuint uNumberOfArrays );

		/** calls glUniform1f only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith1f ( GLint nLocation, GLfloat f1 );

		/** calls glUniform2f only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith2f ( GLint nLocation, GLfloat f1, GLfloat f2 );

		/** calls glUniform3f only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith3f ( GLint nLocation, GLfloat f1, GLfloat f2, GLfloat f3 );

		/** calls glUniform4f only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith4f ( GLint nLocation, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4 );

		/** calls glUniform2fv only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith2fv ( GLint nLocation, GLfloat* pFloats, GLuint uNumberOfArrays );

		/** calls glUniform3fv only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith3fv ( GLint nLocation, GLfloat* pFloats, GLuint uNumberOfArrays );

		/** calls glUniform4fv only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWith4fv ( GLint nLocation, GLfloat* pFloats, GLuint uNumberOfArrays );

		/** calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program. */
		KDvoid					setUniformLocationWithMatrix4fv ( GLint nLocation, GLfloat* pMatrixArray, GLuint uNmberOfMatrices );

		/** will update the		builtin uniforms if they are different than the previous call for this same shader program. */
		KDvoid					setUniformsForBuiltins ( KDvoid );

		/** returns the vertexShader error log */
		const KDchar*			vertexShaderLog ( KDvoid );
		
		/** returns the fragmentShader error log */
		const KDchar*			fragmentShaderLog ( KDvoid );

		/** returns the program error log */
		const KDchar*			programLog ( KDvoid );
	    
		// reload all shaders, this function is designed for android
		// when opengl context lost, so don't call it.
		KDvoid					reset ( KDvoid );
	    
		inline const GLuint		getProgram ( KDvoid ) { return m_uProgram; }

	private :

		KDbool					updateUniformLocation ( GLint nLocation, GLvoid* pData, GLuint uBytes );
		
		const KDchar*			description ( KDvoid );

		KDbool					compileShader ( GLuint* pShader, GLenum uType, const GLchar* pSource );

		const KDchar*			logForOpenGLObject ( GLuint uObject, GLInfoFunction pInfoFunc, GLLogFunction pLogFunc );

	private :

		GLuint						m_uProgram;
		GLuint						m_uVertShader;
		GLuint						m_uFragShader;
		GLint						m_aUniforms[kCCUniform_MAX];
		struct _hashUniformEntry*	m_pHashForUniforms;
		KDbool						m_bUsesTime;
};

// end of shaders group
/// @}

NS_CC_END

#endif // __CCGLProgram_h__
