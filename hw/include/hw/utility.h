#ifndef HW_UTILITY_H_
#define HW_UTILITY_H_

#define HW_CHECK_ALIGNMENT(address, alignment)    ((address) & ((alignment) - 1) == 0)
#define HW_ALIGNED_ROUND_UP(address, alignment)   (((address) + ((alignment) - 1)) & ~((alignment) - 1))
#define HW_ALIGNED_ROUND_DOWN(address, alignment) ((address) & ~((alignment) - 1))

#define HW_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define HW_MIN(a, b) (((a) < (b)) ? (a) : (b))

#define HW_SAFE_FREE(p)   if((p) != NULL) { hw_free((p)); (p) = NULL; }
#define HW_SAFE_DELETE(p) if((p) != NULL) { delete p; (p) = NULL; }

#endif

