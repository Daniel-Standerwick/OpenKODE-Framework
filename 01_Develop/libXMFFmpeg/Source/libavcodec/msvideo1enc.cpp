/*
 * Microsoft Video-1 Encoder
 * Copyright (c) 2009 Konstantin Shishkov
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * Microsoft Video-1 encoder
 */

#include "internal.h"
#include "bytestream.h"
#include "XMFFmpeg/libavutil/lfg.h"
#include "elbg.h"
#include "XMFFmpeg/libavutil/imgutils.h"
/**
 * Encoder context
 */
typedef struct Msvideo1EncContext {
    AVCodecContext *avctx;
    AVFrame pic;
    AVLFG rnd;
    uint8_t *prev;

    int block[16*3];
    int block2[16*3];
    int codebook[8*3];
    int codebook2[8*3];
    int output[16*3];
    int output2[16*3];
    int avg[3];
    int bestpos;
    int keyint;
} Msvideo1EncContext;

enum MSV1Mode{
    MODE_SKIP = 0,
    MODE_FILL,
    MODE_2COL,
    MODE_8COL,
};

#define SKIP_PREFIX 0x8400
#define SKIPS_MAX 0x0FFF
#define MKRGB555(in, off) ((in[off] << 10) | (in[off + 1] << 5) | (in[off + 2]))

static const int remap[16] = { 0, 1, 4, 5, 2, 3, 6, 7, 8, 9, 12, 13, 10, 11, 14, 15 };

static int encode_frame(AVCodecContext *avctx, uint8_t *buf, int buf_size, void *data)
{
    Msvideo1EncContext * const c = (Msvideo1EncContext *const)avctx->priv_data;
    AVFrame *pict = (AVFrame *)data;
    AVFrame * const p = &c->pic;
    uint16_t *src;
    uint8_t *prevptr;
    uint8_t *dst = buf;
    int keyframe = 1;
    int no_skips = 1;
    int i, j, k, x, y;
    int skips = 0;

    *p = *pict;
    if(!c->prev)
        c->prev = (uint8_t *)av_malloc(avctx->width * 3 * (avctx->height + 3));
    prevptr = c->prev + avctx->width * 3 * (FFALIGN(avctx->height, 4) - 1);
    src = (uint16_t*)(p->data[0] + p->linesize[0]*(FFALIGN(avctx->height, 4) - 1));
    if(c->keyint >= avctx->keyint_min)
        keyframe = 1;

    p->quality = 24;

    for(y = 0; y < avctx->height; y += 4){
        for(x = 0; x < avctx->width; x += 4){
            int bestmode = MODE_SKIP;
            int bestscore = INT_MAX;
            int flags = 0;
            int score;

            for(j = 0; j < 4; j++){
                for(i = 0; i < 4; i++){
                    uint16_t val = src[x + i - j*p->linesize[0]/2];
                    for(k = 0; k < 3; k++){
                        c->block[(i + j*4)*3 + k] =
                        c->block2[remap[i + j*4]*3 + k] = (val >> (10-k*5)) & 0x1F;
                    }
                }
            }
            if(!keyframe){
                bestscore = 0;
                for(j = 0; j < 4; j++){
                    for(i = 0; i < 4*3; i++){
                        int t = prevptr[x*3 + i + j*p->linesize[0]] - c->block[i + j*4*3];
                        bestscore += t*t;
                    }
                }
                bestscore /= p->quality;
            }
            // try to find optimal value to fill whole 4x4 block
            score = 0;
            ff_init_elbg(c->block, 3, 16, c->avg, 1, 1, c->output, &c->rnd);
            ff_do_elbg  (c->block, 3, 16, c->avg, 1, 1, c->output, &c->rnd);
            if(c->avg[0] == 1) // red component = 1 will be written as skip code
                c->avg[0] = 0;
            for(j = 0; j < 4; j++){
                for(i = 0; i < 4; i++){
                    for(k = 0; k < 3; k++){
                        int t = c->avg[k] - c->block[(i+j*4)*3+k];
                        score += t*t;
                    }
                }
            }
            score /= p->quality;
            score += 2;
            if(score < bestscore){
                bestscore = score;
                bestmode = MODE_FILL;
            }
            // search for optimal filling of 2-color block
            score = 0;
            ff_init_elbg(c->block, 3, 16, c->codebook, 2, 1, c->output, &c->rnd);
            ff_do_elbg  (c->block, 3, 16, c->codebook, 2, 1, c->output, &c->rnd);
            // last output value should be always 1, swap codebooks if needed
            if(!c->output[15]){
                for(i = 0; i < 3; i++)
                    FFSWAP(uint8_t, c->codebook[i], c->codebook[i+3]);
                for(i = 0; i < 16; i++)
                    c->output[i] ^= 1;
            }
            for(j = 0; j < 4; j++){
                for(i = 0; i < 4; i++){
                    for(k = 0; k < 3; k++){
                        int t = c->codebook[c->output[i+j*4]*3 + k] - c->block[i*3+k+j*4*3];
                        score += t*t;
                    }
                }
            }
            score /= p->quality;
            score += 6;
            if(score < bestscore){
                bestscore = score;
                bestmode = MODE_2COL;
            }
            // search for optimal filling of 2-color 2x2 subblocks
            score = 0;
            for(i = 0; i < 4; i++){
                ff_init_elbg(c->block2 + i*4*3, 3, 4, c->codebook2 + i*2*3, 2, 1, c->output2 + i*4, &c->rnd);
                ff_do_elbg  (c->block2 + i*4*3, 3, 4, c->codebook2 + i*2*3, 2, 1, c->output2 + i*4, &c->rnd);
            }
            // last value should be always 1, swap codebooks if needed
            if(!c->output2[15]){
                for(i = 0; i < 3; i++)
                    FFSWAP(uint8_t, c->codebook2[i+18], c->codebook2[i+21]);
                for(i = 12; i < 16; i++)
                    c->output2[i] ^= 1;
            }
            for(j = 0; j < 4; j++){
                for(i = 0; i < 4; i++){
                    for(k = 0; k < 3; k++){
                        int t = c->codebook2[(c->output2[remap[i+j*4]] + (i&2) + (j&2)*2)*3+k] - c->block[i*3+k + j*4*3];
                        score += t*t;
                    }
                }
            }
            score /= p->quality;
            score += 18;
            if(score < bestscore){
                bestscore = score;
                bestmode = MODE_8COL;
            }

            if(bestmode == MODE_SKIP){
                skips++;
                no_skips = 0;
            }
            if((bestmode != MODE_SKIP && skips) || skips == SKIPS_MAX){
                bytestream_put_le16(&dst, skips | SKIP_PREFIX);
                skips = 0;
            }

            switch(bestmode){
            case MODE_FILL:
                bytestream_put_le16(&dst, MKRGB555(c->avg,0) | 0x8000);
                for(j = 0; j < 4; j++)
                    for(i = 0; i < 4; i++)
                        for(k = 0; k < 3; k++)
                            prevptr[i*3 + k - j*3*avctx->width] = c->avg[k];
                break;
            case MODE_2COL:
                for(j = 0; j < 4; j++){
                    for(i = 0; i < 4; i++){
                        flags |= (c->output[i + j*4]^1) << (i + j*4);
                        for(k = 0; k < 3; k++)
                            prevptr[i*3 + k - j*3*avctx->width] = c->codebook[c->output[i + j*4]*3 + k];
                    }
                }
                bytestream_put_le16(&dst, flags);
                bytestream_put_le16(&dst, MKRGB555(c->codebook, 0));
                bytestream_put_le16(&dst, MKRGB555(c->codebook, 3));
                break;
            case MODE_8COL:
                for(j = 0; j < 4; j++){
                    for(i = 0; i < 4; i++){
                        flags |= (c->output2[remap[i + j*4]]^1) << (i + j*4);
                        for(k = 0; k < 3; k++)
                            prevptr[i*3 + k - j*3*avctx->width] = c->codebook2[(c->output2[remap[i+j*4]] + (i&2) + (j&2)*2)*3 + k];
                    }
                }
                bytestream_put_le16(&dst, flags);
                bytestream_put_le16(&dst, MKRGB555(c->codebook2, 0) | 0x8000);
                for(i = 3; i < 24; i += 3)
                    bytestream_put_le16(&dst, MKRGB555(c->codebook2, i));
                break;
            }
        }
        src     -= p->linesize[0] << 1;
        prevptr -= avctx->width * 3 * 4;
    }
    if(skips)
        bytestream_put_le16(&dst, skips | SKIP_PREFIX);
    //EOF
    bytestream_put_byte(&dst, 0);
    bytestream_put_byte(&dst, 0);

    if(no_skips)
        keyframe = 1;
    if(keyframe)
        c->keyint = 0;
    else
        c->keyint++;
    p->pict_type= keyframe ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;
    p->key_frame= keyframe;

    return dst - buf;
}


/**
 * init encoder
 */
static av_cold int encode_init(AVCodecContext *avctx)
{
    Msvideo1EncContext * const c = (Msvideo1EncContext *const)avctx->priv_data;

    c->avctx = avctx;
    if (av_image_check_size(avctx->width, avctx->height, 0, avctx) < 0) {
        return -1;
    }
    if((avctx->width&3) || (avctx->height&3)){
        av_log(avctx, AV_LOG_ERROR, "width and height must be multiplies of 4\n");
        return -1;
    }

    avcodec_get_frame_defaults(&c->pic);
    avctx->coded_frame = (AVFrame*)&c->pic;

    c->keyint = avctx->keyint_min;
    av_lfg_init(&c->rnd, 1);

    return 0;
}



/**
 * Uninit encoder
 */
static av_cold int encode_end(AVCodecContext *avctx)
{
    Msvideo1EncContext * const c = (Msvideo1EncContext *const)avctx->priv_data;

    av_freep(&c->prev);

    return 0;
}

static const enum PixelFormat _ff_msvideo1_encoder[] = {PIX_FMT_RGB555, PIX_FMT_NONE};
AVCodec ff_msvideo1_encoder = {
    /*.name					= */	"msvideo1",
    /*.type					= */	AVMEDIA_TYPE_VIDEO,
    /*.id					= */	CODEC_ID_MSVIDEO1,
    /*.priv_data_size		= */	sizeof(Msvideo1EncContext),
    /*.init					= */	encode_init,
    /*.encode				= */	encode_frame,
    /*.close				= */	encode_end,
    /*.decode				= */	0,
    /*.capabilities			= */	0,
	/*.next					= */	0,
	/*.flush				= */	0,
	/*.supported_framerates	= */	0,
	/*.pix_fmts				= */	_ff_msvideo1_encoder,
    /*.long_name			= */	NULL_IF_CONFIG_SMALL("Microsoft Video-1"),
};