﻿#ifndef HWGM_WRITER_H_
#define HWGM_WRITER_H_

#include <hw/types.h>
#include <hwcp/type.h>
#include "hwgm/node.h"
#include "reader.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct writer_t {
} writer_t;

extern void writer_initialize(writer_t* writer);
extern void writer_finalize(writer_t* writer);
extern void writer_run(writer_t* writer, const reader_t* reader);

#ifdef __cplusplus
}
#endif

#endif

