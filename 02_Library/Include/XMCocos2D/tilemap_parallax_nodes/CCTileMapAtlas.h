/* -----------------------------------------------------------------------------------
 *
 *      File            CCTileMapAtlas.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2013 XMSoft
 *      Copyright (c) 2010-2013 cocos2d-x.org
 *      Copyright (c) 2008-2010 Ricardo Quesada
 *      Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCTileMapAtlas_h__
#define __CCTileMapAtlas_h__

#include "../base_nodes/CCAtlasNode.h"

#include <string>
#include <map>

NS_CC_BEGIN

class CCDictionary;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** 
 *	@brief CCTileMapAtlas is a subclass of CCAtlasNode.
 *
 *	It knows how to render a map based of tiles.
 *	The tiles must be in a .PNG format while the map must be a .TGA file.
 *
 *	For more information regarding the format, please see this post:
 *	http://www.cocos2d-iphone.org/archives/27
 *
 *	All features from CCAtlasNode are valid in CCTileMapAtlas
 *
 *	IMPORTANT:
 *	This class is deprecated. It is maintained for compatibility reasons only.
 *	You SHOULD not use this class.
 *	Instead, use the newer TMX file format: CCTMXTiledMap
 */
class CCTileMapAtlas : public CCAtlasNode 
{
	public :
		         CCTileMapAtlas ( KDvoid );
		virtual ~CCTileMapAtlas ( KDvoid );

		/** 
		 *	creates a CCTileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
		 *	The tile file will be loaded using the TextureMgr.
		 */
		static   CCTileMapAtlas*	create ( const KDchar* szTilePath, const KDchar* szMapPath, KDuint uTileWidth, KDuint uTileHeight );

	public :

		/** 
		 *	initializes a CCTileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
		 *	The file will be loaded using the TextureMgr.
		 */
		virtual KDbool				initWithTileFile ( const KDchar* szTilePath, const KDchar* szMapPath, KDuint uTileWidth, KDuint uTileHeight );

		/** 
		 *	returns a tile from position x,y.
		 *	For the moment only channel R is used
		 */
		ccColor3B					tileAt ( const CCPoint& tPos );

		/** 
		 *	sets a tile at position x,y.
		 *	For the moment only channel R is used
		 */
		KDvoid						setTile ( const ccColor3B& tColor, const CCPoint& tPos );

		/** dealloc the map from memory */
		KDvoid						releaseMap ( KDvoid );

	private :

		KDvoid						calculateItemsToRender ( KDvoid );

		KDvoid						updateAtlasValueAt ( const CCPoint& tPos, const ccColor3B& tColor, KDuint uIndex );
		KDvoid						updateAtlasValues ( KDvoid );

	protected :

		KDImageATX					m_pImage;
		KDuint						m_uWidth;
		KDuint						m_uHeight;
		ccColor3B*					m_pColors;
		
		//! x,y to atlas dictionary
		CCDictionary*				m_pPosToAtlasIndex;

		//! numbers of tiles to render
		KDint						m_nItemsToRender;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif // __CCTileMapAtlas_h__

