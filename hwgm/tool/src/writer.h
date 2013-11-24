#ifndef HWGM_WRITER_H_
#define HWGM_WRITER_H_

#include <hw/types.h>
#include <hwcp/type.h>
#include "reader.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void writer_initialize(reader_t* reader);
extern void writer_finalize(writer_t* writer);
extern void writer_run(writer_t* writer);

#ifdef __cplusplus
}
#endif

#endif

