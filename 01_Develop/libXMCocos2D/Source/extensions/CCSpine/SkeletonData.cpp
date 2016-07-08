/* -----------------------------------------------------------------------------------
 *
 *      File            SkeletonData.cpp
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2013 XMSoft.
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
 *     ( INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION ) HOWEVER CAUSED AND
 *     ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *     ( INCLUDING NEGLIGENCE OR OTHERWISE ) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ----------------------------------------------------------------------------------- */ 

#include "Precompiled.h"
#include "extensions/CCSpine/SkeletonData.h"
#include "extensions/CCSpine/Extension.h"

NS_CC_BEGIN


SkeletonData* SkeletonData_create ( KDvoid )
{
	return NEW ( SkeletonData );
}

KDvoid SkeletonData_dispose ( SkeletonData* self )
{
	KDint  i;
	for ( i = 0; i < self->boneCount; ++i )
	{
		BoneData_dispose ( self->bones[i] );
	}
	FREE ( self->bones );

	for ( i = 0; i < self->slotCount; ++i )
	{
		SlotData_dispose ( self->slots[i] );
	}
	FREE ( self->slots );

	for ( i = 0; i < self->skinCount; ++i )
	{
		Skin_dispose ( self->skins[i] );
	}
	FREE ( self->skins );

	for ( i = 0; i < self->animationCount; ++i )
	{
		Animation_dispose ( self->animations[i] );
	}
	FREE ( self->animations );

	FREE ( self );
}

BoneData* SkeletonData_findBone ( const SkeletonData* self, const KDchar* boneName ) 
{
	for ( KDint i = 0; i < self->boneCount; ++i )
	{
		if ( kdStrcmp ( self->bones[i]->name, boneName ) == 0 ) 
		{
			return self->bones[i];
		}
	}
	return 0;
}

KDint SkeletonData_findBoneIndex ( const SkeletonData* self, const KDchar* boneName )
{
	for ( KDint i = 0; i < self->boneCount; ++i )
	{
		if ( kdStrcmp ( self->bones[i]->name, boneName ) == 0 ) 
		{
			return i;
		}
	}
	return 0;
}

SlotData* SkeletonData_findSlot ( const SkeletonData* self, const KDchar* slotName )
{
	for ( KDint i = 0; i < self->slotCount; ++i )
	{
		if ( kdStrcmp ( self->slots[i]->name, slotName ) == 0 )
		{
			return self->slots[i];
		}
	}
	return 0;
}

KDint SkeletonData_findSlotIndex ( const SkeletonData* self, const KDchar* slotName ) 
{
	for ( KDint i = 0; i < self->slotCount; ++i )
	{
		if ( kdStrcmp ( self->slots[i]->name, slotName ) == 0 ) 
		{
			return i;
		}
	}
	return 0;
}

Skin* SkeletonData_findSkin ( const SkeletonData* self, const KDchar* skinName )
{	
	for ( KDint i = 0; i < self->skinCount; ++i )
	{
		if ( kdStrcmp ( self->skins[i]->name, skinName ) == 0 )
		{
			return self->skins[i];
		}
	}
	return 0;
}

Animation* SkeletonData_findAnimation ( const SkeletonData* self, const KDchar* animationName )
{
	for ( KDint i = 0; i < self->animationCount; ++i )
	{
		if ( kdStrcmp ( self->animations[i]->name, animationName ) == 0 )
		{
			return self->animations[i];
		}
	}
	return 0;
}


NS_CC_END
