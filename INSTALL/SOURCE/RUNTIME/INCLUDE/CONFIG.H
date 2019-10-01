 /* @(#)config.h	1.3 8/26/92 */

/* config.h */
/* Copyright (C) Inmos Ltd, 1990, 1991, 1992 */

#ifndef __config_h
#define __config_h

/*****************************************************************************
 * Define the data structures used by the INMOS configuration system.        *
 * INMOS do not guarantee that the details of these structures will remain   *
 * the same in the future.                                                   *
 *****************************************************************************/

typedef struct Conf_Process Conf_Process;
typedef struct Processor Processor;

struct Conf_Process
       {
         int                  ProcessId;
         int                  ProcessMode;
         unsigned int         CodeSize;
         char                *CodeAddr;
         char                *CodeEntryAddr;
         unsigned int         StackSize;
         unsigned int         StackParamSize;
         char                *StackAddr;
         unsigned int         VectorSize;
         char                *VectorAddr;
         unsigned int         StaticSize;
         char                *StaticAddr;
         unsigned int         HeapSize;
         char                *HeapAddr;
         struct Conf_Process *NextProcessAddr;
         struct Processor    *ProcessorAddr;
         unsigned int         NoParameters;
         unsigned int         NoValues;
       };

/*****************************************************************************
 * The parameters and data arrays follow the process structure directly      *
 *****************************************************************************/

struct Processor
       {
         int                  ProcessorId;
         int                  ProcessorMode;
         unsigned int         ProcessorSize;
         char                *CodeLoadAddr;
         char                *DataLoadAddr;
         char                *ExternalAddress;
         char                *InputAddr;
         char                *OutputAddr;
         char                *FreeAddr;
         struct Conf_Process *UserProcessAddr;
         struct Conf_Process *InitProcessAddr;
         void                *VirtualDataAddr;
         unsigned int         NoChannels;
       };

struct param_info
{
  int simple;
  int complete;
  union t
  {
    int v_value;
    int **v_ptr;
  } value;
};

#define DATA 1
#define DATA_PTR 2  
#define INTERNAL_CHANNEL 3  
#define EXTERNAL_CHANNEL 4  
#define CHANNEL_PTR 5  

#define INPUT 15
#define OUTPUT 16

#define CONFIGURED_BIT 2

#endif

