-- -----
--
--     (c) Copyright INMOS Limited 1989.
--
-- Generic assembler module for the initialisation code used in the
-- boot from EPROM run from EPROM case, this is the primary bootstrap
-- code, and performs the following functions :-
--
--     1/ Allocate workspace for this module, the network loader,
--        and the run time system initialisation code, also calculate
--        memstart which is defined as the chips MEMSTART + allocated
--        workspace. This means memstart points to free memory after
--        the allocated workspace.
--
--     2/ Reset the High and Low priority process queues.
--
--     3/ Clear the error flag and initialise the halt-on-error flag. 
--
--     4/ Initialise the hardware, link and event, channels, 
--        and the timer pointer queues.
--
--     5/ Start the low and high priority timers. 
--
--     6/ Initialise the parameters for, and call, the network loader.
--
--     7/ Initialise the parameters for, and transfer control to,
--        the run time system initialisation code. 
--
--
--    The workspace used by this procedure is mapped as follows
--
--        offset       Variable
--
--          0            Return addess for the called routines.
--          1-8          Parameters to routines.
--          9-12         The variable parameters to the network loader.
--          13           Stored value of memstart.
--          14           Loop control variable used in memory initialisation.
--          15           Loop counter used in memory initialisation.
--          16           Network loader entry point.
--          17           Start of network commands.
--
-- -----

#define T426_PROCESSOR_LOWER    30
#define T426_PROCESSOR_UPPER    39

#define PARITY_ERROR_REGISTER   2147483492      -- 7FFFFF64

--

#define    return_address                 0
#define    routine_param_1                1
#define    routine_param_2                2
#define    routine_param_3                3
#define    routine_param_4                4
#define    routine_param_5                5
#define    routine_param_6                6
#define    routine_param_7                7
#define    routine_param_8                8
#define    loader_var_param_1             9
#define    loader_var_param_2             10
#define    loader_var_param_3             11
#define    loader_var_param_4             12
#define    memstart                       13
#define    loop_control                   14
#define    loop_count                     15
#define    loader_entry_point             16
#define    start_of_network_commands      17
#define    free_memory                    18

--

#define    subroutine_workspace           32
#define    channel_words_to_clear         11
#define    loader_buffer_size             120

--

    align
Machine_initialisation_runrom:
    global Machine_initialisation_runrom

-- -----
--
--    1/ Allocate workspace, for the called routines. 
--
--    The actual workspace used is this plus the thirteen words
--    detailed above, This restricts the workspace available
--    to the network loader and system initialisation code, and
--    this must be changed if they need increased workspace.
--
--    This piece of code actually gets and stores the value of 
--    memstart as well.
--
-- -----

    ajw         subroutine_workspace    -- Allow some workspace

    ldlp        free_memory             -- Address of first free word.
    stl         memstart                -- store memstart

-- -----
--
--    2/ Reset High and Low priority process queues.
--
-- -----

    mint                                -- NotProcess.p
    sthf
    mint                                -- NotProcess.p
    stlf

-- -----
--
--    3/ Clear the error flag and initialise halt on error flag.
--
--    Note this is for halt on error but it could be for continue
--    on error by changing sethalterr to clrhalterr.
--
--    Note this has the T8 fpu error initialisation also.
--
--    Also clear parity regs for the T426
--
-- -----

    testerr                            -- Clear error flag
    fptesterr                         -- Clear floating point error flag

    sethalterr                           -- Set or clear halt on error.

--

#ifdef PARITY_CHECKING

    lddevid                            -- can do this since this is safe on all processors
    ldc    T426_PROCESSOR_LOWER-1
    gt                                 -- Only on T426s at present
    cj     Noparityregs
    ldc    T426_PROCESSOR_UPPER+1
    lddevid
    gt
    cj     Noparityregs
    ldc    PARITY_ERROR_REGISTER       -- Clear parity register by reading it
    ldnl   0

Noparityregs:

#endif

-- -----
--
--    4/ Initialise hardware channels and timer queues.
--       This is done by setting the bottom eleven words of memory
--       to NotProcess.p.
--
-- -----

                                       -- Setup loop control variables
    ldc         0                      -- Word number
    stl         loop_control
    ldc         channel_words_to_clear -- Number of times to loop
    stl         loop_count

loop:
    mint                               -- NotProcess.p, value to be written

    ldl         loop_control           -- Word number
    mint                               -- Base of memory
    wsub                               -- Convert to an address

    stnl        0                      -- Perform write.

    ldlp        loop_control           -- Address of loop control variables
    ldc         end_loop - loop        -- Distance to loop back
    lend                               -- Perform loop for 'count' times
end_loop:

-- -----
--
--    5/ Start low and High priority timers.
--
-- -----

    ldc        0                       -- Initial value for both timers.
    sttimer

-- -----
--
--    6/ Initialise the parameters for, and call, the network loader.
--
--    On arrival into the network loader the workspace will 
--    be viewed as :-
--
--        offset       Variable                             value
--
--          0       Return address.
--          1       Address of  [4]CHAN OF ANY links       mint
--          2       address of  [4]BYTE network.data       calculated as block
--                                                         after network loader
--          3       address of  network.data.pointer       WPTR + 11
--          4       address of  [4]BYTE memory             memstart
--          5       value of    VAL INT Buffer.address     0
--          6       address of  INT next.address           WPTR + 12
--          7       address of  INT entry.point            WPTR + 9
--          8       address of  INT data.point             WPTR + 10
--
-- -----

    ldc         return_point - addr1  -- Get and store return address
    ldpi
addr1:
    stl         return_address

--

    mint                               -- Store address of links
    stl         routine_param_1

--

    ldc         end_of_module - addr2  -- Get address of network loader block
    ldpi
addr2:
    stl         routine_param_2        -- Store this temporarily

    ldl         routine_param_2        -- Add 4 to block start to find
    adc         4                      -- network loader entry point.
    stl         loader_entry_point     -- store it.

    ldl         routine_param_2        -- Read length, 16 bits in 32 bit word
    ldnl        0                      -- OK whatever processor.

    ldl         loader_entry_point     -- add to block entry to find
    bsub                               -- start of next block.

    stl         start_of_network_commands   -- Store it,
    ldl         start_of_network_commands   -- and then
    stl         routine_param_2        -- Write it to parameter block

--

    ldlp        loader_var_param_3     -- Store pointer for network.data.pointer
    stl         routine_param_3

--

    ldl         memstart               -- Store memstart.
    stl         routine_param_4

--

    ldc         0                      -- Store zero
    stl         routine_param_5

--

    ldlp        loader_var_param_4     -- Store pointer for next.address
    stl         routine_param_6

--

    ldlp        loader_var_param_1     -- Store pointer for entry.point
    stl         routine_param_7

--

    ldlp        loader_var_param_2     -- Store pointer for data point.
    stl         routine_param_8

--

    ldl         loader_entry_point     -- Finally perform call
    gcall

--

return_point:

    ajw         -4                     -- Restore Workspace pointer
                                       -- to its value prior to the call.

-- -----
--
--    7/ Initialise the parameters for, and call, the system initialisation code
--
--    On arrival into the initialisation code the workspace will 
--    be viewed as :-
--
--        offset       Variable                             value
--
--          0       Return address.
--          1       Address of  CHAN OF ANY boot.link.in   mint+4words
--          2       Address of  CHAN OF ANY boot.link.out  mint
--          3       value of    VAL INT code.address       start_of_network_commands + 
--							   loader_var_param_3
--                                                         rounded up to 4 byte
--                                                         boundary.
--          4       value of    VAL INT data.address       memstart + 120
--          5       value of    VAL INT external.address   dummy mint
--          6       address of  [processor.size]INT processor  
--                                                         content of WPTR + 10
--                                                         + memstart + 120
--
--     The address of this routine is in WPTR+9, specified as an offset from
--     memstart, returned by the network loader.
--
-- -----

    ldl         memstart               -- Advance memstart by loader_buffer_size
    adc         loader_buffer_size
    stl         memstart

--

    ldc         return_point2 - addr3  -- Get and store return address
    ldpi
addr3:
    stl         return_address

--

    ldc         4                      -- Get and Store address of link0 in
    mint
    wsub
    stl         routine_param_1

--

    mint                               -- Get and Store address of link0 out
    stl         routine_param_2

--

    ldl         loader_var_param_3     -- Round up to 4 byte boundary. 
    adc         3                      -- the length of commands block
    ldc         -4
    and
    ldl         start_of_network_commands  -- add to start of network commands.
    bsub
    stl         routine_param_3        -- and store.

--

    ldl         memstart               -- Store memstart in data.address
    stl         routine_param_4

--

    mint                               -- Store dummy mint.
    stl         routine_param_5

--

    ldl         loader_var_param_2     -- Use data point as base of
    ldl         memstart               -- processor table
    bsub
    stl         routine_param_6

--

    ldl         loader_var_param_1     -- Finally perform call
    ldl         routine_param_3        -- To address entry.point + code base.
    bsub
    gcall

--

return_point2:

-- -----
--
--    Should the program ever terminate then stop.
--
-- -----

    stopp

-- -----
--
--    Here we have the end of this block, we have an alligned label
--    that is used as the pointer to the next block, containing a 16 
--    bit word giving the length of the network loader. followed by
--    the network loader.
--
-- -----

    align

end_of_module:

