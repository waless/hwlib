#ifndef HWM_FIXED16_H_
#define HWM_FIXED16_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef hws16 hwm_sfixed11_4_t;
typedef hwu16 hwm_ufixed12_4_t;
typedef hws16 hwm_sfixed1_14_t;
typedef hwu16 hwm_ufixed1_15_t;

extern hwm_sfixed11_4_t hwm_f32_to_sfixed11_4(hwf32 v);
extern hwf32            hwm_sfixed11_4_to_f32(hwm_sfixed11_4_t v);

extern hwm_ufixed12_4_t hwm_f32_to_ufixed12_4(hwf32 v);
extern hwf32            hwm_ufixed12_t_to_f32(hwm_ufixed12_4_t v);

#ifdef __cplusplus
}
#endif

#endif

