/* -----------------------------------------------------------------------------------
 *
 *      File            aabb.h  
 *      Ported By       Young-Hwan Mun
 *      Contact         xmsoft77@gmail.com 
 * 
 * -----------------------------------------------------------------------------------
 *   
 *      Copyright (c) 2010-2013 XMSoft
 *      Copyright (c) 2008      Luke Benstead. All rights reserved.    
 *
 * -----------------------------------------------------------------------------------
 * 
 *      Redistribution and use in source and binary forms, with or without modification,
 *      are permitted provided that the following conditions are met:
 *      
 *       * Redistributions of source code must retain the above copyright notice,
 *         this list of conditions and the following disclaimer.
 *       * Redistributions in binary form must reproduce the above copyright notice,
 *         this list of conditions and the following disclaimer in the documentation
 *         and/or other materials provided with the distribution.
 *      
 *       THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *       ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *       WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *       DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 *       ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *       (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *       LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *       ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *       (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *       SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ----------------------------------------------------------------------------------- */ 

#ifndef __aabb_h__
#define __aabb_h__

#include "kode.h"
#include "vec3.h"
#include "utility.h"

/**
 * A structure that represents an axis-aligned
 * bounding box.
 */
typedef struct kmAABB 
{
    kmVec3 min; /** The max corner of the box */
    kmVec3 max; /** The min corner of the box */
} kmAABB;

const int     kmAABBContainsPoint ( const kmVec3* pPoint, const kmAABB* pBox );
kmAABB* const kmAABBAssign ( kmAABB* pOut, const kmAABB* pIn );
kmAABB* const kmAABBScale ( kmAABB* pOut, const kmAABB* pIn, kmScalar s );


#endif // __aabb_h__
