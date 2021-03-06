/* -----------------------------------------------------------------------------------
 *
 *      File            SkeletonJson.h
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

#ifndef __SkeletonJson_h__
#define __SkeletonJson_h__

#include "Attachment.h"
#include "AttachmentLoader.h"
#include "SkeletonData.h"
#include "Atlas.h"
#include "Animation.h"

namespace spine {

typedef struct 
{
	KDfloat					scale;
	AttachmentLoader*		attachmentLoader;
	const KDchar* const		error;
} SkeletonJson;

SkeletonJson*	SkeletonJson_createWithLoader ( AttachmentLoader* pAttachmentLoader );
SkeletonJson*	SkeletonJson_create ( Atlas* pAtlas );
KDvoid			SkeletonJson_dispose ( SkeletonJson* pSelf );

SkeletonData*	SkeletonJson_readSkeletonData ( SkeletonJson* pSelf, const KDchar* pJson );
SkeletonData*	SkeletonJson_readSkeletonDataFile ( SkeletonJson* pSelf, const KDchar* pPath );

} // namespace spine {

#endif	// __SkeletonJson_h__
