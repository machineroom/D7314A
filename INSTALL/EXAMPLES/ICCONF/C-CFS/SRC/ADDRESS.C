/*{{{  include files */
#include <stdio.h>
#include <stdlib.h>

#include <misc.h>
/*}}}*/

/*{{{  static constants */
#define L_Code   0
#define L_Stack  1
#define L_Vector 2
#define L_Static 3
#define L_Heap   4
/*}}}*/

/*{{{  static variables */
static int InvalidAddress = 0;
/*}}}*/

/*{{{  static procedures */
/*{{{  CheckMemorySegment */
static void CheckMemorySegment (int SegmentBase, int SegmentSize, const char *SegmentName, int Address, int Number)
{
    if (SegmentSize > 0)
    {
        /*{{{   */
        if ((Address >= SegmentBase) && ((Address - SegmentBase) < SegmentSize))
        {
            /*{{{   */
            if (sizeof(int) == 2)
                printf("%d, %-6.6s = #%04X -> #%04X : valid\n", Number, SegmentName, SegmentBase, (SegmentBase + SegmentSize) - 1);
            else
                printf("%d, %-6.6s = #%08X -> #%08X : valid\n", Number, SegmentName, SegmentBase, (SegmentBase + SegmentSize) - 1);
            /*}}}*/
        }
        else
        {
            /*{{{   */
            InvalidAddress = 1;
            
            if (sizeof(int) == 2)
                printf("%d, %-6.6s = #%04X -> #%04X : error (#%04X)\n", Number, SegmentName, SegmentBase, (SegmentBase + SegmentSize) - 1, Address);
            else
                printf("%d, %-6.6s = #%08X -> #%08X : error (#%08X)\n", Number, SegmentName, SegmentBase, (SegmentBase + SegmentSize) - 1, Address);
            /*}}}*/
        }
        /*}}}*/
    }
}
/*}}}*/

/*{{{  CheckCodeSegment */
static void CheckCodeSegment (int SegmentBase, int SegmentSize, int Number)
{
    if (SegmentSize > 0)
    {
        /*{{{   */
        int Address = (int) NULL;
        
        /*{{{  initialise code address */
        Address = (int) CheckCodeSegment;
        /*}}}*/
        
        CheckMemorySegment(SegmentBase, SegmentSize, "code", Address, Number);
        /*}}}*/
    }
}
/*}}}*/

/*{{{  CheckStackSegment */
static void CheckStackSegment (int SegmentBase, int SegmentSize, int Number)
{
    if (SegmentSize > 0)
    {
        /*{{{   */
        int Address = (int) NULL;
        
        /*{{{  initialise stack address */
        Address = (int) &Address;
        /*}}}*/
        
        CheckMemorySegment(SegmentBase, SegmentSize, "stack", Address, Number);
        /*}}}*/
    }
}
/*}}}*/

/*{{{  CheckVectorSegment */
static void CheckVectorSegment (int SegmentBase, int SegmentSize, int Number)
{
    if (SegmentSize > 0)
        abort();
}
/*}}}*/

/*{{{  CheckStaticSegment */
static void CheckStaticSegment (int SegmentBase, int SegmentSize, int Number)
{
    if (SegmentSize > 0)
    {
        /*{{{   */
        static int Address = (int) NULL;
        
        /*{{{  initialise static address */
        Address = (int) &Address;
        /*}}}*/
        
        CheckMemorySegment(SegmentBase, SegmentSize, "static", Address, Number);
        /*}}}*/
    }
}
/*}}}*/

/*{{{  CheckHeapSegment */
static void CheckHeapSegment (int SegmentBase, int SegmentSize, int Number)
{
    if (SegmentSize > 0)
    {
        /*{{{   */
        int Address = (int) NULL;
        
        /*{{{  initialise heap address */
        Address = (int) malloc(1);
        /*}}}*/
        
        CheckMemorySegment(SegmentBase, SegmentSize, "heap", Address, Number);
        /*}}}*/
    }
}
/*}}}*/
/*}}}*/

/*{{{  global procedures */
/*{{{  main */
int main (void)
{
    long int *SegmentBases = get_param(3);
    long int *SegmentSizes = get_param(4);
    int Number = (int) *((long int *) get_param(5));

    set_abort_action(ABORT_HALT);

    CheckCodeSegment((int) SegmentBases[L_Code], (int) SegmentSizes[L_Code], Number);
    CheckStackSegment((int) SegmentBases[L_Stack], (int) SegmentSizes[L_Stack], Number);
    CheckVectorSegment((int) SegmentBases[L_Vector], (int) SegmentSizes[L_Vector], Number);
    CheckStaticSegment((int) SegmentBases[L_Static], (int) SegmentSizes[L_Static], Number);
    CheckHeapSegment((int) SegmentBases[L_Heap], (int) SegmentSizes[L_Heap], Number);

    if (InvalidAddress)
        exit(EXIT_FAILURE);
    else
        exit(EXIT_SUCCESS);
}
/*}}}*/
/*}}}*/
