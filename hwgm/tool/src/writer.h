#ifndef HWGM_WRITER_H_
#define HWGM_WRITER_H_

#include <hw/types.h>
#include <hwcp/type.h>
#include "hwgm/node.h"
#include "reader.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void writer_run(const reader_t* reader);

#ifdef __cplusplus
}
#endif

#endif

