/*{{{  include files */
#include <stdio.h>
#include <stdlib.h>

#include <misc.h>
/*}}}*/

/*{{{  global procedures */
/*{{{  main */
int main (void)
{
    int Index = 0;

    char     *ByteVal = get_param(3),         *ByteVar = get_param(4);
    char     *ByteArrayVal = get_param(5),    *ByteArrayVar = get_param(6);
    long int *Int32Val = get_param(7),        *Int32Var = get_param(8);
    long int *Int32ArrayVal = get_param(9),   *Int32ArrayVar = get_param(10);
    float    *Real32Val = get_param(11),      *Real32Var = get_param(12);
    float    *Real32ArrayVal = get_param(13), *Real32ArrayVar = get_param(14);
    double   *Real64Val = get_param(15),      *Real64Var = get_param(16);
    double   *Real64ArrayVal = get_param(17), *Real64ArrayVar = get_param(18);

    /*{{{  BYTE */
    printf("%c : ByteVal\n", *ByteVal);
    
    printf("%c : ByteVar\n", *ByteVar);
    
    for (Index = 0; Index < 1; Index++)
        printf("%c ", ByteArrayVal[Index]);
    printf(": ByteArrayVal\n");
    
    for (Index = 0; Index < 1; Index++)
        printf("%c ", ByteArrayVar[Index]);
    printf(": ByteArrayVar\n");
    /*}}}*/

    /*{{{  INT32 */
    printf("%ld : Int32Val\n", *Int32Val);
    
    printf("%ld : Int32Var\n", *Int32Var);
    
    for (Index = 0; Index < 2; Index++)
        printf("%ld ", Int32ArrayVal[Index]);
    printf(": Int32ArrayVal\n");
    
    for (Index = 0; Index < 2; Index++)
        printf("%ld ", Int32ArrayVar[Index]);
    printf(": Int32ArrayVar\n");
    /*}}}*/

    /*{{{  REAL32 */
    printf("%g : Real32Val\n", *Real32Val);
    
    printf("%g : Real32Var\n", *Real32Var);
    
    for (Index = 0; Index < 3; Index++)
        printf("%g ", Real32ArrayVal[Index]);
    printf(": Real32ArrayVal\n");
    
    for (Index = 0; Index < 3; Index++)
        printf("%g ", Real32ArrayVar[Index]);
    printf(": Real32ArrayVar\n");
    /*}}}*/

    /*{{{  REAL64 */
    printf("%g : Real64Val\n", *Real64Val);
    
    printf("%g : Real64Var\n", *Real64Var);
    
    for (Index = 0; Index < 4; Index++)
        printf("%g ", Real64ArrayVal[Index]);
    printf(": Real64ArrayVal\n");
    
    for (Index = 0; Index < 4; Index++)
        printf("%g ", Real64ArrayVar[Index]);
    printf(": Real64ArrayVar\n");
    /*}}}*/

    exit(EXIT_SUCCESS);
}
/*}}}*/
/*}}}*/
