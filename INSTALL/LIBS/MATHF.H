/* @(#)mathf.h	1.2 5/15/92 */

/* mathf.h */
/* Copyright (C) Inmos Ltd. 1990 */

#ifndef __mathf_h
#define __mathf_h

#define HUGE_VAL_F 3.40282347e+38F /* FLT_MAX */

extern float acosf(float /*x*/);
extern float asinf(float /*x*/);
extern float atanf(float /*x*/);
extern float atan2f(float /*y*/, float /*x*/);
extern float cosf(float /*x*/);
extern float sinf(float /*x*/);
extern float tanf(float /*x*/);
extern float coshf(float /*x*/);
extern float sinhf(float /*x*/);
extern float tanhf(float /*x*/);
extern float expf(float /*x*/);
extern float frexpf(float /*value*/, int * /*exp*/);
extern float ldexpf(float /*x*/, int /*exp*/);
extern float logf(float /*x*/);
extern float log10f(float /*x*/);
extern float modff(float /*value*/, float * /*iptr*/);
extern float powf(float /*x*/, float /*y*/);
extern float sqrtf(float /*x*/);
extern float ceilf(float /*x*/);
extern float fabsf(float /*x*/);
extern float floorf(float /*d*/);
extern float fmodf(float /*x*/, float /*y*/);

#pragma IMS_nosideeffects(ceilf)
#pragma IMS_nosideeffects(fabsf)
#pragma IMS_nosideeffects(floorf)

#endif

/* end of mathf.h */
