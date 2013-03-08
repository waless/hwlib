#ifndef HWU_UTILITY_H_
#define HWU_UTILITY_H_

#define HWU_CHECK_ALIGNMENT(address, alignment)    ((address) & ((alignment) - 1) == 0)
#define HWU_ALIGNED_ROUND_UP(address, alignment)   (((address) + ((alignment) - 1)) & ~((alignment) - 1))
#define HWU_ALIGNED_ROUND_DOWN(address, alignment) ((address) & ~((alignment) - 1))

#define HWU_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define HWU_MIN(a, b) (((a) < (b)) ? (b) : (b))

#define HWU_SAFE_FREE(p)   if((p) != NULL) { hwu_free((p)); (p) = NULL; }
#define HWU_SAFE_DELETE(p) if((p) != NULL) { delete p; (p) = NULL; }

#endif	/* HWU_UTILITY_H */

