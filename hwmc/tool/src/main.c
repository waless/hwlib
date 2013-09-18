#include <stddef.h>
#include "hwmc.h"

#include <hw/memory/allocator.h>

int main(int argc, char* argv[])
{
    struct hwmc_state_t state;

    if(hwmc_initialize(&state, argc, argv)) {
        hwmc_run(&state);
        hwmc_finalize(&state);
    }

    return 0;
}

