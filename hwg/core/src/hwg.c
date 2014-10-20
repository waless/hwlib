#include "hwg.h"
#include <hw/types.h>
#include <hw/error.h>
#include "hwg/dx.h"

hwbool hwg_initialize(const hwg_parameter_t* param)
{
    HRESULT result = S_OK;
    RECT rc;

    HW_ASSERT(param->hwnd != NULL);
}

hwbool hwg_finalize()
{
}

