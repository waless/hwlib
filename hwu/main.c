#include <stdio.h>
#include "hwu/platform.h"
#include "hwu/debug/assert.h"

int main(int argc, char** argv)
{
	HWU_ASSERT_MESSAGE(0, "foocc");
    return 0;
}

