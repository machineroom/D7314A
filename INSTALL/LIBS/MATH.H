/* @(#)math.h	1.3 6/5/92 */

/* math.h: ANSI X3.159 1989 library header, section 4.5 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __math_h
#define __math_h

#define HUGE_VAL _IMS_huge_val
extern double HUGE_VAL;

extern double acos(double /*x*/);
extern double asin(double /*x*/);
extern double atan(double /*x*/);
extern double atan2(double /*y*/, double /*x*/);
extern double cos(double /*x*/);
extern double sin(double /*x*/);
extern double tan(double /*x*/);
extern double cosh(double /*x*/);
extern double sinh(double /*x*/);
extern double tanh(double /*x*/);
extern double exp(double /*x*/);
extern double frexp(double /*value*/, int * /*exp*/);
extern double ldexp(double /*x*/, int /*exp*/);
extern double log(double /*x*/);
extern double log10(double /*x*/);
extern double modf(double /*value*/, double * /*iptr*/);
extern double pow(double /*x*/, double /*y*/);
extern double sqrt(double /*x*/);
extern double ceil(double /*x*/);
extern double fabs(double /*x*/);
extern double floor(double /*d*/);
extern double fmod(double /*x*/, double /*y*/);

#pragma IMS_nosideeffects(ceil)
#pragma IMS_nosideeffects(fabs)
#pragma IMS_nosideeffects(floor)

#endif

/* end of math.h */
