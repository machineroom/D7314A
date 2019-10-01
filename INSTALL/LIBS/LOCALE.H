/* @(#)locale.h	1.4 6/5/92 */

/* locale.h: ANSI X3.159 1989 library header, section 4.4 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __locale_h
#define __locale_h

#define LC_COLLATE  1
#define LC_CTYPE    2
#define LC_MONETARY 4
#define LC_NUMERIC  8
#define LC_TIME    16
#define LC_ALL     31

extern char *setlocale(int /*category*/, const char * /*locale*/);

struct lconv {
  char *decimal_point;
  char *thousands_sep;
  char *grouping;
  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
};

#ifdef __SIGNED_CHAR__
#pragma IMS_translate(localeconv, "_IMS_localeconv_signed")
#else
#pragma IMS_translate(localeconv, "_IMS_localeconv_unsigned")
#endif

extern struct lconv *localeconv(void);

#pragma IMS_nosideeffects(localeconv)

#ifndef NULL
#  define NULL (void *)0
#endif

#endif

/* end of locale.h */
