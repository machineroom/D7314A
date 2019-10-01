/* Copyright INMOS Limited 1988,1990 */

/* CMSIDENTIFIER */
/* PRODUCT:ITEM.VARIANT-TYPE;0(DATE) */

#ifndef _NOHOST_H_

#define _NOHOST_H_

#define SWITCH_CHAR '-'

/* exit status  */
#define TERMINATE_OK_EXIT     (0)
#define TERMINATE_FAIL_EXIT   (255)
#define USER_EXIT             (254)
#define ERROR_FLAG_EXIT       (253)
#define MISC_EXIT             (252)

#define ERROUT stderr

/* fopen modes */
#define BINARY_1 "rb"
#define BINARY_2 "wb"
#define BINARY_3 "ab"
#define BINARY_4 "r+b"
#define BINARY_5 "w+b"
#define BINARY_6 "a+b"
#define TEXT_1 "r"
#define TEXT_2 "w"
#define TEXT_3 "a"
#define TEXT_4 "r+"
#define TEXT_5 "w+"
#define TEXT_6 "a+"

#endif /* _NOHOST_H_ */
