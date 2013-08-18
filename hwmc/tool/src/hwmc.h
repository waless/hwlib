#ifndef HWG_MODEL_CONVERTER_H_
#define HWG_MODEL_CONVERTER_H_

#include <hw/types.h>
#include "reader.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    HWMC_PATH_MAX = 256,
};

typedef struct hwmc_state_t {
    char input_path[HWMC_PATH_MAX];
    char output_path[HWMC_PATH_MAX];
} hwmc_state_t;

extern hwbool hwmc_initialize(hwmc_state_t* state, int argc, const char* argv[]);
extern void hwmc_finalize(hwmc_state_t* state);
extern void hwmc_run(hwmc_state_t* state);

#ifdef __cplusplus
}
#endif

#endif

