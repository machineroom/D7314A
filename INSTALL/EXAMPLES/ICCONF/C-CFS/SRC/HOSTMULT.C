/*{{{  include files */
#include <stdlib.h>
#include <string.h>

#include <misc.h>
#include <process.h>
/*}}}*/

/*{{{  static constants */
#define SP_MIN_PACKET_DATA_SIZE 6
#define SP_MAX_PACKET_DATA_SIZE 510

#define SP_EXIT_TAG 35

#define SPR_OK 0

#define SPS_SUCCESS 999999999L
/*}}}*/

/*{{{  static procedures */
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

/*{{{  RotateChannels */
static void RotateChannels (Channel *Channels[], int ChannelsSize, int Count)
{
    while (Count-- > 0)
    {
        /*{{{   */
        int ChannelsIndex = 0;
        
        Channels[ChannelsSize] = Channels[ChannelsIndex]; /* NULL terminated */
        
        while (ChannelsIndex++ < ChannelsSize)
            Channels[ChannelsIndex - 1] = Channels[ChannelsIndex];
        
        Channels[ChannelsSize] = NULL;
        /*}}}*/
    }
}
/*}}}*/

/*{{{  SpExit */
static int SpExit (Channel *HostInput, Channel *HostOutput, long int Status)
{
    int Length = SP_MIN_PACKET_DATA_SIZE;
    char Buffer[SP_MIN_PACKET_DATA_SIZE];

    /*{{{  initialise packet buffer */
    memset(Buffer, 0, SP_MIN_PACKET_DATA_SIZE);
    
    Buffer[0] = SP_EXIT_TAG;
    
    memcpy(&Buffer[1], &Status, sizeof(Status)); /* Little endian */
    /*}}}*/

    ChanOut(HostOutput, &Length, 2);
    ChanOut(HostOutput, Buffer, Length);

    ChanIn(HostInput, &Length, 2);
    ChanIn(HostInput, Buffer, Length);

    return(Buffer[0] & 0XFF);
}
/*}}}*/
/*}}}*/

/*{{{  global procedures */
/*{{{  main */
int main (void)
{
    Channel *HostInput = get_param(1);
    Channel *HostOutput = get_param(2);
    int InputSize = (int) *((long int *) get_param(4));
    int OutputSize = (int) *((long int *) get_param(6));
    Channel **Input = CreateChannels(get_param(3), InputSize);
    Channel **Output = CreateChannels(get_param(5), OutputSize);

    set_abort_action(ABORT_HALT);

    if (InputSize == OutputSize)
    {
        /*{{{   */
        int ExitCount = InputSize;
        long int ExitStatus = SPS_SUCCESS;
        
        while (ExitCount > 0)
        {
            /*{{{   */
            char Buffer[SP_MAX_PACKET_DATA_SIZE];
            int Length = 0, Index = ProcAltList(Input);
            
            ChanIn(Input[Index], &Length, 2);
            ChanIn(Input[Index], Buffer, Length);
            
            if (Buffer[0] == SP_EXIT_TAG)
            {
                /*{{{   */
                long int Status = SPS_SUCCESS;
                
                /*{{{  determine exit status */
                memcpy(&Status, &Buffer[1], sizeof(Status)); /* Little endian */
                
                if (Status != SPS_SUCCESS)
                    ExitStatus = Status;
                /*}}}*/
                
                ExitCount--;
                
                Buffer[0] = SPR_OK; /* Successful exit */
                
                ChanOut(Output[Index], &Length, 2);
                ChanOut(Output[Index], Buffer, Length);
                /*}}}*/
            }
            else
            {
                /*{{{   */
                ChanOut(HostOutput, &Length, 2);
                ChanOut(HostOutput, Buffer, Length);
                
                ChanIn(HostInput, &Length, 2);
                ChanIn(HostInput, Buffer, Length);
                
                ChanOut(Output[Index], &Length, 2);
                ChanOut(Output[Index], Buffer, Length);
                /*}}}*/
            }
            
            RotateChannels(Input, InputSize, (Index + 1) % InputSize);
            RotateChannels(Output, OutputSize, (Index + 1) % InputSize);
            /*}}}*/
        }
        
        SpExit(HostInput, HostOutput, ExitStatus);
        /*}}}*/
    }
    else
        abort();
}
/*}}}*/
/*}}}*/
