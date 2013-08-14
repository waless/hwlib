#include "hwmc.h"

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
    if(argc < 2) {
        return HW_FALSE;
    }

    return HW_TRUE;
}

