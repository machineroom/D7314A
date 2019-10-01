/*{{{  include files */
#include <stdio.h>
#include <stdlib.h>

#include <misc.h>
/*}}}*/

/*{{{  static constants */
#define WorkspaceSize 5

#define AltStatus   0
#define LowWptr     1
#define HighIptr    2
#define HighWptr    3
#define SyncChannel 4
/*}}}*/

/*{{{  static variables */
static int LowPriority = 0;
/*}}}*/

/*{{{  static procedures */
/*{{{  PrintStatus */
static void PrintStatus (int LowPriority, int Number)
{
    int Priority = 0, Descriptor = 0;

    /*{{{  get process attributes */
    __asm {ldpri; st Priority; ldlp 0; st Descriptor;}
    /*}}}*/

    if (LowPriority)
    {
        /*{{{   */
        if (sizeof(int) == 2)
            printf("%d (L), Priority : %d, Wptr : #%04X\n", Number, Priority, Descriptor);
        else
            printf("%d (L), Priority : %d, Wptr : #%08X\n", Number, Priority, Descriptor);
        /*}}}*/
    }
    else
    {
        /*{{{   */
        if (sizeof(int) == 2)
            printf("%d (H), Priority : %d, Wptr : #%04X\n", Number, Priority, Descriptor);
        else
            printf("%d (H), Priority : %d, Wptr : #%08X\n", Number, Priority, Descriptor);
        /*}}}*/
    }
}
/*}}}*/

/*{{{  LowProcess */
static void LowProcess (void)
{
    __asm
    {
        /*{{{   */
        /* Check low priority */
        ldpri;
        eqc 0;
        cj SkipLow;
        
        /* Start low priority */
        ldlp 0;
        adc 1;
        runp;
        
        /* Stop high priority */
        stopp;
        
        SkipLow:;
        /*}}}*/
    }
}
/*}}}*/

/*{{{  HighProcess */
static void HighProcess (void)
{
    int Workspace[WorkspaceSize];

    __asm
    {
        /*{{{   */
        /* Check high priority */
        ldpri;
        cj SkipHigh;
        
        /* Initialise channel */
        mint;
        st Workspace[SyncChannel];
        
        /* Store low priority Wptr */
        ldlp 0;
        st Workspace[LowWptr];
        
        /* Store high priority Iptr */
        ldlabeldiff StopLow - StartHigh;
        ldpi;
        
        StartHigh:
        
        st Workspace[HighIptr];
        
        /* Start high priority */
        ld &Workspace[HighWptr];
        runp;
        
        /* Stop low priority, part 1 */
        ldabc 1, &Workspace[SyncChannel], &Workspace;
        out;
        
        StopLow:
        
        /* Stop low priority, part 2 */
        alt;
        ldlp SyncChannel - HighWptr;
        ldc 1;
        enbc;
        altwt;
        
        /* Restore low priority Wptr */
        ldl LowWptr - HighWptr;
        gajw;
        
        SkipHigh:;
        /*}}}*/
    }
}
/*}}}*/
/*}}}*/

/*{{{  global procedures */
/*{{{  main */
int main (void)
{
    int Count = (int) *((long int *) get_param(3));
    int Number = (int) *((long int *) get_param(4));

    /*{{{  evaluate initial priority */
    __asm {ldpri; st LowPriority;}
    /*}}}*/

    PrintStatus(LowPriority, Number);

    while (Count-- > 0)
    {
        /*{{{   */
        /*{{{  flip process priority */
        if (LowPriority)
            HighProcess();
        else
            LowProcess();
        /*}}}*/
        
        PrintStatus(LowPriority, Number);
        
        /*{{{  flip process priority */
        if (LowPriority)
            LowProcess();
        else
            HighProcess();
        /*}}}*/
        
        PrintStatus(LowPriority, Number);
        /*}}}*/
    }
    exit(EXIT_SUCCESS);
}
/*}}}*/
/*}}}*/
