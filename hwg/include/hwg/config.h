#ifndef HWG_CONFIG_H_
#define HWG_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* OpenGL platform */
/* #define HWG_CONFIG_GL_4_0    */
/* #define HWG_CONFIG_GL_ES_1_1 */
/* #define HWG_CONFIG_GL_ES_2_0 */
/* #define HWG_CONFIG_GL_ES_3_0 */

/* DirectX platform */
#define HWG_CONFIG_DX11

/* AMD Mantle API Platform */
/* #define HWG_CONFIG_MANTLE */

/* API kind define */
#if defined(HWG_CONFIG_GL_4_0) || defined(HWG_CONFIG_GL_ES_1_1) || defined(HWG_CONFIG_GL_ES_2_0) || defined(HWG_CONFIG_GL_ES_3_0)
#   define HWG_GL
#elif defined(HWG_CONFIG_DX9) || defined(HWG_CONFIG_DX11)
#   define HWG_DX
#elif defined(HWG_CONFIG_MANTLE)
#   define HWG_MANTLE
#endif

#ifdef __cplusplus
}
#endif

#endif

