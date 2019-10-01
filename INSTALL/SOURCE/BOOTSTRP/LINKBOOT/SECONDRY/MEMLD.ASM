#include "memld.h"

    align
Secondary_for_floating_and_memstart:

global Secondary_for_floating_and_memstart

    ldc    0 		   -- Get ready to accept soft memstart
    stl    LOAD_LENGTH		

    ldlp   LOAD_LENGTH	   
    ldl    BOOTLINK
    ldc    1
    in

    ldlp   MEMSTART
    ldl    BOOTLINK
    ldl    LOAD_LENGTH
    in			   -- Got soft Memstart

    ldlp   LOAD_LENGTH     -- Get ready to accept network loader offset	
    ldl    BOOTLINK
    ldc    1
    in

    ldlp   NEXT_ADDRESS
    ldl    BOOTLINK
    ldl    LOAD_LENGTH
    in			  -- Got it

    --ldl    NEXT_ADDRESS
    --mint
    --bsub
    --stl    NEXT_ADDRESS

    --ldl    MEMSTART         
    --mint   
    --bsub   
    --stl    MEMSTART
    
    ldl    MEMSTART
    stl    MEMORY           -- Earlest place to load

    ldlp   TEMP_WORKSPACE   -- pointer to loaders work space zero
    stl    NEXT_WPTR        -- work space pointer of loaded code

    ldc    0
    stl    LOAD_LENGTH      -- clear bytes to load

Loadcode:
    ldl    NEXT_ADDRESS     -- adddress to load loader
    stl    LOAD_START       -- current load point

-- load code until terminator
Startload:
    ldlp   LOAD_LENGTH      -- packet length
    ldl    BOOTLINK         -- address of link
    ldc    1                -- bytes to load
    in                      -- input length byte

    ldl    LOAD_LENGTH      -- message length
    cj     Endload          -- quit if 0 bytes

    ldl    NEXT_ADDRESS     -- start of area to load loader
    ldl    BOOTLINK         -- address of link
    ldl    LOAD_LENGTH      -- message length
    in                      -- input code block
    ldl    LOAD_LENGTH      -- message length
    ldl    NEXT_ADDRESS     -- area to load
    bsub                    -- new area to load
    stl    NEXT_ADDRESS     -- save area to load

    j      Startload        -- go back for next block
Endload:

    ldl    NEXT_ADDRESS     -- Start of the network loader buffer
    stl    MOVE_WPTR_TO
    ldl    NEXT_ADDRESS

    ldl    MEMSTART
    diff
    stl    BUFFER

    ldc    INITIAL_ADJUSTMENT  -- How much workspace below the moved workspace
    bcnt
    stl    LOAD_LENGTH         -- i.e. the initial adjustment

    ldl    MOVE_WPTR_TO
    ldl    LOAD_LENGTH    
    sum
    ldc    PACKET_LENGTH
    bsub
    stl    MOVE_WPTR_TO        -- Where to move to

    --ldc    (MEMSTART-TEMP_WORKSPACE)
    ldc    MEMSTART
    bcnt
    stl    LOAD_LENGTH         -- amount to move i.e. all variables upto and
                               --   including memstart
   
    ldl    NEXT_WPTR
    ldl    MOVE_WPTR_TO
    ldl    LOAD_LENGTH
    move                       -- move the contents of the current workspace

    ldl    MOVE_WPTR_TO
    stl    NEXT_WPTR           -- stash away the destination workspace pointer

    ldl    NEXT_WPTR           -- wspace of loaded code
    gajw                       -- set up his work space

    stl    LOAD_START          -- save old workspace

    ldlp   (DATA_ADDRESS-TEMP_WORKSPACE)
    stl    (DATA_TO_RETURN-TEMP_WORKSPACE)
    ldlp   (ENTRY_ADDRESS-TEMP_WORKSPACE)
    stl    (ENTRY_POINT-TEMP_WORKSPACE)

    ldl    LOAD_START       -- get code to enter

    ldl    LOAD_START
    ldnl   LOAD_LENGTH
    ldlp   0
    bsub   
    
    stl    LOAD_START

    ldl    LOAD_START         -- Next_boot_parameter to the network loader
    ldl    (MEMSTART-TEMP_WORKSPACE)
    diff
    stl    (NEXT_BOOT-TEMP_WORKSPACE)

    ldnl   0                  -- address of network loader

    --ldnl   LOAD_START       -- address of network loader

    gcall                   -- enter loaded code

Return:
