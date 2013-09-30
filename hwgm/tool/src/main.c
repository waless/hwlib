#include <stddef.h>
#include "hwgm.h"

#include <hw/memory/allocator.h>

int main(int argc, char* argv[])
{
    struct hwgm_state_t state;

    if(hwgm_initialize(&state, argc, argv)) {
        hwgm_run(&state);
        hwgm_finalize(&state);
    }

    return 0;
}

