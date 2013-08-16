#include "hwmc.h"
#include <string.h>
#include "hw/string/string.h"

static hwbool parse_args(hwmc_state_t* state, int argc, const char* argv[]);

hwbool hwmc_initialize(hwmc_state_t* state, int argc, const char* argv[])
{
    if(parse_args(state, argc, argv) == HW_FALSE) {
        return HW_FALSE;
    }

    return HW_TRUE;
}

void hwmc_finalize(hwmc_state_t* state)
{
}

void hwmc_run(hwmc_state_t* state)
{
}

hwbool parse_args(hwmc_state_t* state, int argc, const char* argv[])
{
    int i;
    hw_string_t input;
    hw_string_t output;

    if(argc < 2) {
        return HW_FALSE;
    }

    hw_string_initialize(&input, state->input_path, sizeof(state->input_path));
    hw_string_initialize(&input, state->output_path, sizeof(state->output_path));

    hw_string_copy_cstring(&input, argv[1]);
    if(argc > 2) {
        for(i = 2; i < argc; ++i) {
            const char* arg = argv[i];

            if(strcmp(arg, "-o") == 0) {
                if(argc > i) {
                    hw_string_copy_cstring(&output, argv[i + 1]);
                    ++i;
                }
            }
        }
    }
    else {
    }

    return HW_TRUE;
}

