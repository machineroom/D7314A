/*{{{  include files */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include <misc.h>
#include <process.h>
/*}}}*/

/*{{{  static procedures */
/*{{{  ChanInInt32 */
static long int ChanInInt32 (Channel *Input)
{
    long int Value = 0;

    ChanIn(Input, &Value, sizeof(Value));

    return(Value);
}
/*}}}*/

/*{{{  ChanOutInt32 */
static void ChanOutInt32 (Channel *Output, long int Value)
{
    ChanOut(Output, &Value, sizeof(Value));
}
/*}}}*/

/*{{{  CreateChannels */
static Channel **CreateChannels (Channel *Channels[], int ChannelsSize)
{
    Channel **CopyChannels = NULL;

    if ((CopyChannels = malloc((ChannelsSize + 1) * sizeof(Channel *))) == NULL)
        abort();
    else
    {
        /*{{{   */
        int ChannelsIndex = 0;
        
        while (ChannelsIndex++ < ChannelsSize)
            CopyChannels[ChannelsIndex - 1] = Channels[ChannelsIndex - 1];
        
        CopyChannels[ChannelsSize] = NULL;
        /*}}}*/
    }
    return(CopyChannels);
}
/*}}}*/

/*{{{  InputProcess */
static void InputProcess (Process *InputP, Channel *Input[], int InputSize, long int *Value)
{
    int InputIndex = 0;

    InputP = InputP; /* Prevent warnings */

    while (InputIndex++ < InputSize)
    {
        /*{{{   */
        long int InputValue = ChanInInt32(Input[ProcAltList(Input)]);
        
        if (InputValue < (LONG_MAX - *Value))
            *Value += InputValue;
        else
            abort(); /* Overflow error */
        /*}}}*/
    }
}
/*}}}*/

/*{{{  OutputProcess */
static void OutputProcess (Process *OutputP, Channel *Output[], int OutputSize, long int Value)
{
    int OutputIndex = 0;

    OutputP = OutputP; /* Prevent warnings */

    /*{{{  checked increment addition */
    if (Value < LONG_MAX)
        Value++;
    else
        abort(); /* Overflow error */
    /*}}}*/

    while (OutputIndex < OutputSize)
        ChanOutInt32(Output[OutputIndex++], Value);
}
/*}}}*/

/*{{{  IOProcesses */
static long int IOProcesses (Channel *Input[], int InputSize, Channel *Output[], int OutputSize, long int Value)
{
    Process *InputP = NULL;

    if ((InputP = ProcAlloc(InputProcess, 1024, 3, Input, InputSize, &Value)) == NULL)
        abort();
    else
    {
        /*{{{   */
        Process *OutputP = NULL;
        
        if ((OutputP = ProcAlloc(OutputProcess, 1024, 2 + (sizeof(long int) / sizeof(int)), Output, OutputSize, Value)) == NULL)
            abort();    
        else
        {
            /*{{{   */
            ProcPar(InputP, OutputP, NULL);
            
            ProcAllocClean(InputP);
            ProcAllocClean(OutputP);
            /*}}}*/
        }
        /*}}}*/
    }
    return(Value);
}
/*}}}*/
/*}}}*/

/*{{{  global procedures */
/*{{{  main */
int main (void)
{
    int InputSize = (int) *((long int *) get_param(4));
    int OutputSize = (int) *((long int *) get_param(6));
    Channel **Input = CreateChannels(get_param(3), InputSize);
    Channel **Output = CreateChannels(get_param(5), OutputSize);

    set_abort_action(ABORT_HALT);

    if (InputSize == OutputSize)
    {
        /*{{{   */
        long int Value = 0;
        
        while (1)
            printf("%ld\n", Value = IOProcesses(Input, InputSize, Output, OutputSize, Value));
        /*}}}*/
    }
    else
        abort();
}
/*}}}*/
/*}}}*/
