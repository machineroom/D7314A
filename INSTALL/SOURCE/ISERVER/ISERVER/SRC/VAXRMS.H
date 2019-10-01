/* Copyright INMOS Limited 1991 */

/* CMSIDENTIFIER */
/* PRODUCT:ITEM.VARIANT-TYPE;0(DATE) */

/* Macros */

/* Structure definitions */

/* External variables */

/* Functions */

#ifdef PROTOTYPES
#else
struct RAB *vmscreate();
struct RAB *vmsopen();
int vmsclose();
int vmsput();
int vmsget();
int vmsseek();
void freerab();
int vmssavepos();
RecInfo *newinfo();
#endif /* PROTOTYPES */
