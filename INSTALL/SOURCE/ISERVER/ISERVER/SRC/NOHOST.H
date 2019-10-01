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
#define BINARY_1 "r"
#define BINARY_2 "w"
#define BINARY_3 "a"
#define BINARY_4 "r+"
#define BINARY_5 "w+"
#define BINARY_6 "a+"
#define TEXT_1 BINARY_1
#define TEXT_2 BINARY_2
#define TEXT_3 BINARY_3
#define TEXT_4 BINARY_4
#define TEXT_5 BINARY_5
#define TEXT_6 BINARY_6

#endif /* _NOHOST_H_ */
