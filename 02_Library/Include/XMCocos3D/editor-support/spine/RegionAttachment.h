/* -----------------------------------------------------------------------------------
 *
 *      File            RegionAttachment.h
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2014 XMSoft.
 *      Copyright (c) 2013      Esoteric Software. All rights reserved.
 *
 *         http://esotericsoftware.com/      
 *
 * -----------------------------------------------------------------------------------
 * 
 *     Redistribution and use in source and binary forms, with or without
 *     modification, are permitted provided that the following conditions are met:
 * 
 *     1. Redistributions of source code must retain the above copyright notice, this
 *        list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright notice,
 *        this list of conditions and the following disclaimer in the documentation
 *        and/or other materials provided with the distribution.
 * 
 *     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 *     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *     ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ----------------------------------------------------------------------------------- */ 

#ifndef __RegionAttachment_h__
#define __RegionAttachment_h__

#include "Attachment.h"
#include "Atlas.h"
#include "Slot.h"

namespace spine {

typedef enum 
{
	VERTEX_X1 = 0, VERTEX_Y1, VERTEX_X2, VERTEX_Y2, VERTEX_X3, VERTEX_Y3, VERTEX_X4, VERTEX_Y4
} VertexIndex;

typedef struct RegionAttachment RegionAttachment;
struct RegionAttachment 
{
	Attachment		super;
	KDfloat			x, y, scaleX, scaleY, rotation, width, height;

	KDvoid*			rendererObject;
	KDint			regionOffsetX, regionOffsetY;				/* Pixels stripped from the bottom left, unrotated. */
	KDint			regionWidth, regionHeight;					/* Unrotated, stripped pixel size. */
	KDint			regionOriginalWidth, regionOriginalHeight;	/* Unrotated, unstripped pixel size. */

	KDfloat			offset[8];
	KDfloat			uvs[8];
};

RegionAttachment*	RegionAttachment_create ( const KDchar* pName );
KDvoid				RegionAttachment_setUVs ( RegionAttachment* pSelf, KDfloat u, KDfloat v, KDfloat u2, KDfloat v2, KDint nRotate );
KDvoid				RegionAttachment_updateOffset ( RegionAttachment* pSelf );
KDvoid				RegionAttachment_computeVertices ( RegionAttachment* pSelf, KDfloat x, KDfloat y, Bone* pBone, KDfloat* pVertices );

} // namespace spine {

#endif	// __RegionAttachment_h__
