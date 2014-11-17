#ifndef HWG_H_
#define HWG_H_

#include <hw/platform.h>
#include <hw/types.h>
#include "hwg/config.h"
#include <windows.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct hwg_parameter_t {
    HWND   hwnd;
    hwuint frame_width;
    hwuint frame_height;
    hwuint frame_rate;
    hwbool is_windowed;
} hwg_parameter_t;

extern hwbool hwg_initialize(const hwg_parameter_t* param);
extern hwbool hwg_begin();
extern hwbool hwg_end();
extern hwbool hwg_finalize();

#if defined(__cplusplus)
}
#endif

#endif

