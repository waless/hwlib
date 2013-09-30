#ifndef HWGM_H_
#define HWGM_H_

#include <hw/types.h>
#include "reader.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    HWGM_PATH_MAX = 256,
};

typedef struct hwgm_state_t {
    char input_path[HWGM_PATH_MAX];
    char output_path[HWGM_PATH_MAX];
} hwgm_state_t;

extern hwbool hwgm_initialize(hwgm_state_t* state, int argc, const char* argv[]);
extern void hwgm_finalize(hwgm_state_t* state);
extern void hwgm_run(hwgm_state_t* state);

#ifdef __cplusplus
}
#endif

#endif

