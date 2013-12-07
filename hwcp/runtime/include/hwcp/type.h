#ifndef HWCP_TYPE_H_
#define HWCP_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwcp_reference_t { hwu32 count;
    hwu32 offsets[1];
} hwcp_reference_t;

#ifdef __cplusplus
}
#endif

#endif

