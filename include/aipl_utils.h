/* Copyright (C) 2022-2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/******************************************************************************
 * @file    aipl_utils.h
 * @brief   Utility types and functions
 *
******************************************************************************/

#ifndef AIPL_UTILS_H
#define AIPL_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include "aipl_error.h"

/*********************
 *      DEFINES
 *********************/
#define INLINE inline __attribute__((always_inline))

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
} aipl_argb8888_px_t;

typedef struct {
    union {
        struct {
            uint8_t b : 4;
            uint8_t g : 4;
        };
        uint8_t gb;
    };
    union {
        struct {
            uint8_t r : 4;
            uint8_t a : 4;
        };
        uint8_t ar;
    };
} aipl_argb4444_px_t;

typedef struct {
    union {
        struct {
            uint8_t b;
            uint8_t t;
        };
        uint16_t h;
    };
} aipl_argb1555_px_t;

typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t g;
    uint8_t r;
} aipl_rgba8888_px_t;

typedef struct {
    union {
        struct {
            uint8_t a : 4;
            uint8_t b : 4;
        };
        uint8_t ba;
    };
    union {
        struct {
            uint8_t g : 4;
            uint8_t r : 4;
        };
        uint8_t rg;
    };
} aipl_rgba4444_px_t;

typedef struct {
    union {
        struct {
            uint8_t b;
            uint8_t t;
        };
        uint16_t h;
    };
} aipl_rgba5551_px_t;

typedef struct {
    union {
        struct {
            uint8_t b;
            uint8_t t;
        };
        uint16_t h;
    };
} aipl_rgb565_px_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * Pack ARGB8888 pixel into ARGB4444
 *
 * @param dst desitnation pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_packa_argb4444_px(aipl_argb4444_px_t* dst,
                                   const aipl_argb8888_px_t* src)
{
    dst->ar = (src->a & 0xf0) | (src->r >> 4);
    dst->gb = (src->g & 0xf0) | (src->b >> 4);
}

/**
 * Pack ARGB8888 pixel into ARGB1555
 *
 * @param dst desitnation pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_packa_argb1555_px(aipl_argb1555_px_t* dst,
                                   const aipl_argb8888_px_t* src)
{
    dst->h = ((uint16_t)(src->a & 0x80) << 8)
             | ((uint16_t)(src->r & 0xf8) << 7)
             | ((uint16_t)(src->g & 0xf8) << 2)
             | (src->b >> 3);
}

/**
 * Pack ARGB8888 pixel into RGBA4444
 *
 * @param dst desitnation pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_packa_rgba4444_px(aipl_rgba4444_px_t* dst,
                                   const aipl_argb8888_px_t* src)
{
    dst->rg = (src->r & 0xf0) | (src->g >> 4);
    dst->ba = (src->b & 0xf0) | (src->a >> 4);
}

/**
 * Pack ARGB8888 pixel into RGBA5551
 *
 * @param dst desitnation pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_packa_rgba5551_px(aipl_rgba5551_px_t* dst,
                                   const aipl_argb8888_px_t* src)
{
    dst->h = ((uint16_t)(src->r & 0xf8) << 8)
             | ((uint16_t)(src->g & 0xf8) << 3)
             | ((src->b & 0xf8) >> 2)
             | (src->a >> 7);
}

/**
 * Pack ARGB8888 pixel into RGB565
 *
 * @param dst desitnation pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_packa_rgb565_px(aipl_rgb565_px_t* dst,
                                 const aipl_argb8888_px_t* src)
{
    dst->h = ((uint16_t)(src->r & 0xf8) << 8)
             | ((uint16_t)(src->g & 0xfc) << 3)
             | (src->b >> 3);
}

/**
 * Pack ARGB8888 pixel into Y channel
 *
 * @param dst destination pointer
 * @param src source pixel pointer
 */
INLINE void aipl_packa_yuv_y(uint8_t* dst,
                             const aipl_argb8888_px_t* src)
{
    *dst = ((66 * src->r + 129 * src->g + 25 * src->b + 128) >> 8) + 16;
}

/**
 * Pack ARGB8888 pixel into U channel
 *
 * @param dst destination pointer
 * @param src source pixel pointer
 */
INLINE void aipl_packa_yuv_u(uint8_t* dst,
                             const aipl_argb8888_px_t* src)
{
    *dst = ((-38 * src->r - 74 * src->g + 112 * src->b + 128) >> 8) + 128;
}

/**
 * Pack ARGB8888 pixel into V channel
 *
 * @param dst destination pointer
 * @param src source pixel pointer
 */
INLINE void aipl_packa_yuv_v(uint8_t* dst,
                             const aipl_argb8888_px_t* src)
{
    *dst = ((112 * src->r - 94 * src->g - 18 * src->b + 128) >> 8) + 128;
}

/**
 * Pack 24bit pixel into ARGB4444
 *
 * @param dst       desitnation pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_pack_argb4444_px(aipl_argb4444_px_t* dst,
                                  const uint8_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst->ar = 0xf0 | (src[r_offset] >> 4);
    dst->gb = (src[g_offset] & 0xf0) | (src[b_offset] >> 4);
}

/**
 * Pack 24bit pixel into ARGB1555
 *
 * @param dst       desitnation pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_pack_argb1555_px(aipl_argb1555_px_t* dst,
                                  const uint8_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst->h = 0x8000 | ((uint16_t)(src[r_offset] & 0xf8) << 7)
             | ((uint16_t)(src[g_offset] & 0xf8) << 2)
             | (src[b_offset] >> 3);
}

/**
 * Pack 24bit pixel into RGBA4444
 *
 * @param dst       desitnation pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_pack_rgba4444_px(aipl_rgba4444_px_t* dst,
                                  const uint8_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst->rg = (src[r_offset] & 0xf0) | (src[g_offset] >> 4);
    dst->ba = (src[b_offset] & 0xf0) | 0x0f;
}

/**
 * Pack 24bit pixel into RGBA5551
 *
 * @param dst       desitnation pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_pack_rgba5551_px(aipl_rgba5551_px_t* dst,
                                  const uint8_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst->h = ((uint16_t)(src[r_offset] & 0xf8) << 8)
             | ((uint16_t)(src[g_offset] & 0xf8) << 3)
             | ((src[b_offset] & 0xf8) >> 2)
             | 0x01;
}

/**
 * Pack 24bit pixel into RGB565
 *
 * @param dst       desitnation pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_pack_rgb565_px(aipl_rgb565_px_t* dst,
                                const uint8_t* src,
                                uint8_t r_offset,
                                uint8_t g_offset,
                                uint8_t b_offset)
{
    dst->h = ((uint16_t)(src[r_offset] & 0xf8) << 8)
             | ((uint16_t)(src[g_offset] & 0xfc) << 3)
             | (src[b_offset] >> 3);
}

/**
 * Pack 24bit pixel into Y channel
 *
 * @param dst       destination pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_pack_yuv_y(uint8_t* dst,
                            const uint8_t* src,
                            uint8_t r_offset,
                            uint8_t g_offset,
                            uint8_t b_offset)
{
    *dst = ((66 * src[r_offset] + 129 * src[g_offset] + 25 * src[b_offset] + 128) >> 8) + 16;
}

/**
 * Pack 24bit pixel into U channel
 *
 * @param dst       destination pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_pack_yuv_u(uint8_t* dst,
                            const uint8_t* src,
                            uint8_t r_offset,
                            uint8_t g_offset,
                            uint8_t b_offset)
{
    *dst = ((-38 * src[r_offset] - 74 * src[g_offset] + 112 * src[b_offset] + 128) >> 8) + 128;
}

/**
 * Pack 24bit pixel into V channel
 *
 * @param dst       destination pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_pack_yuv_v(uint8_t* dst,
                            const uint8_t* src,
                            uint8_t r_offset,
                            uint8_t g_offset,
                            uint8_t b_offset)
{
    *dst = ((112 * src[r_offset] - 94 * src[g_offset] - 18 * src[b_offset] + 128) >> 8) + 128;
}

/**
 * Load RGBA8888 pixel into 24bit
 *
 * @param dst       destination pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_load_rgba8888_px(uint8_t* dst,
                                  const aipl_rgba8888_px_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst[r_offset] = src->r;
    dst[g_offset] = src->g;
    dst[b_offset] = src->b;
}


/**
 * Load ARGB4444 pixel into 24bit
 *
 * @param dst       destination pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_load_argb4444_px(uint8_t* dst,
                                  const aipl_argb4444_px_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst[r_offset] = src->r << 4;
    dst[g_offset] = src->gb & 0xf0;
    dst[b_offset] = src->b << 4;
}

/**
 * Load RGBA4444 pixel into 24bit
 *
 * @param dst       destination pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_load_rgba4444_px(uint8_t* dst,
                                  const aipl_rgba4444_px_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst[r_offset] = src->rg & 0xf0;
    dst[g_offset] = src->g << 4;
    dst[b_offset] = src->ba & 0xf0;
}

/**
 * Load ARGB1555 pixel into 24bit
 *
 * @param dst       destination pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_load_argb1555_px(uint8_t* dst,
                                  const aipl_argb1555_px_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst[r_offset] = (src->t << 1) & 0xf8;
    dst[g_offset] = (src->h & 0x03e0) >> 2;
    dst[b_offset] = (src->b & 0x1f) << 3;
}

/**
 * Load RGBA5551 pixel into 24bit
 *
 * @param dst       destination pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_load_rgba5551_px(uint8_t* dst,
                                  const aipl_rgba5551_px_t* src,
                                  uint8_t r_offset,
                                  uint8_t g_offset,
                                  uint8_t b_offset)
{
    dst[r_offset] = src->t & 0xf8;
    dst[g_offset] = (src->h & 0x07c0) >> 3;
    dst[b_offset] = (src->b & 0x3e) << 2;
}

/**
 * Load RGB565 pixel into 24bit
 *
 * @param dst       destination pixel pointer
 * @param src       source pixel pointer
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_load_rgb565_px(uint8_t* dst,
                                const aipl_rgb565_px_t* src,
                                uint8_t r_offset,
                                uint8_t g_offset,
                                uint8_t b_offset)
{
    dst[r_offset] = src->t & 0xf8;
    dst[g_offset] = (src->h & 0x07e0) >> 3;
    dst[b_offset] = (src->b & 0x1f) << 3;
}

/**
 * Load RGBA8888 pixel into ARGB888
 *
 * @param dst destination pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_loada_rgba8888_px(aipl_argb8888_px_t* dst,
                                   const aipl_rgba8888_px_t* src)
{
    dst->a = src->a;
    dst->r = src->r;
    dst->g = src->g;
    dst->b = src->b;
}

/**
 * Load ARGB4444 pixel into ARGB8888
 *
 * @param dst destination pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_loada_argb4444_px(aipl_argb8888_px_t* dst,
                                   const aipl_argb4444_px_t* src)
{
    dst->a = src->ar & 0xf0;
    dst->r = src->r << 4;
    dst->g = src->gb & 0xf0;
    dst->b = src->b << 4;
}

/**
 * Load ARGB1555 pixel into ARGB8888
 *
 * @param dst destination pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_loada_argb1555_px(aipl_argb8888_px_t* dst,
                                   const aipl_argb1555_px_t* src)
{
    dst->a = (src->t >> 7) * 0xff;
    dst->r = (src->t << 1) & 0xf8;
    dst->g = (src->h & 0x03e0) >> 2;
    dst->b = (src->b & 0x1f) << 3;
}

/**
 * Load RGBA4444 pixel into ARGB888
 *
 * @param dst destination pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_loada_rgba4444_px(aipl_argb8888_px_t* dst,
                                   const aipl_rgba4444_px_t* src)
{
    dst->r = src->rg & 0xf0;
    dst->g = src->g << 4;
    dst->b = src->ba & 0xf0;
    dst->a = src->a << 4;
}

/**
 * Load RGBA5551 pixel into ARGB888
 *
 * @param dst destination pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_loada_rgba5551_px(aipl_argb8888_px_t* dst,
                                   const aipl_rgba5551_px_t* src)
{
    dst->r = src->t & 0xf8;
    dst->g = (src->h & 0x07c0) >> 3;
    dst->b = (src->b & 0x3e) << 2;
    dst->a = (src->b & 0x01) * 0xff;
}

/**
 * Load RGB565 pixel into ARGB888
 *
 * @param dst destination pixel pointer
 * @param src source pixel pointer
 */
INLINE void aipl_loada_rgb565_px(aipl_argb8888_px_t* dst,
                                 const aipl_rgb565_px_t* src)
{
    dst->a = 0xff;
    dst->r = src->t & 0xf8;
    dst->g = (src->h & 0x07e0) >> 3;
    dst->b = (src->b & 0x1f) << 3;
}


/**
 * Convert singed channel value to unsigned
 * and cap the value to range [0;255]
 *
 * @param val uncapped channel value
 * @return capped channel value
 */
INLINE uint8_t aipl_channel_cap(int16_t val)
{
    if (val & 0x8000) return 0;
    else if (val & 0xff00) return 0xff;
    else return val;
}

/**
 * Get 24bit from YUV
 *
 * @param dst       destination 24bit pixel pointer
 * @param y         Y channel value
 * @param u         U channel value
 * @param v         V channel value
 * @param r_offset  red channel offset
 * @param g_offset  green channel offset
 * @param b_offset  blue channel offset
 */
INLINE void aipl_yuv_to_24bit(uint8_t* dst,
                              uint8_t y, uint8_t u, uint8_t v,
                              uint8_t r_offset,
                              uint8_t g_offset,
                              uint8_t b_offset)
{
    int16_t c = y - 16;
    int16_t d = u - 128;
    int16_t e = v - 128;

    dst[r_offset] = aipl_channel_cap((298 * c + 409 * e + 128) >> 8);
    dst[g_offset] = aipl_channel_cap((298 * c - 100 * d - 208 * e + 128) >> 8);
    dst[b_offset] = aipl_channel_cap((298 * c + 516 * d + 128) >> 8);
}

/**
 * Get 24bit from ALPHA8
 *
 * @param dst   destination 24bit pixel pointer
 * @param alpha aplha channel value
 */
INLINE void aipl_alpha_to_24bit(uint8_t* dst,
                                uint8_t alpha)
{
    dst[0] = alpha;
    dst[1] = alpha;
    dst[2] = alpha;
}

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*AIPL_UTILS_H*/
