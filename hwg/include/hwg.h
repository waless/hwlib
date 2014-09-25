#ifndef HWG_H_
#define HWG_H_

#include <hw/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern hwbool hwg_initialize();
extern hwbool hwg_begin();
extern hwbool hwg_end();
extern hwbool hwg_finalize();

#if defined(__cplusplus)
}
#endif

#endif

