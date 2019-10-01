#include "primary.h"

    align
Secondary:

global Secondary

-- initialise bootloader workspace

    ldc    PACKET_LENGTH    -- buffer size
    ldlp   BUFFER_START     -- buffer start address
    bsub                    -- end of buffer address
    stl    NEXT_ADDRESS	    -- start of area to load loader

    ldlp   BUFFER_START     -- buffer start address
    stl    MEMORY           -- Earlest place to load

    ldlp   TEMP_WORKSPACE   -- pointer to loaders work space zero
    stl    NEXT_WPTR        -- work space pointer of loaded code

    ldc    0
    stl    BUFFER           -- Where to buffer

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

-- initialise return address and enter loaded code
    ldc    Return - Addr1   -- offset to return address
    ldpi                    -- return address
Addr1:
    stl    RETURN_ADDRESS   -- save in W0


    ldl    BOOTLINK         -- Get bootlink and save for later
    stl    OCCAM_WORKSPACE

    ldl    NEXT_WPTR        -- wspace of loaded code
    gajw                    -- set up his work space
    ldnl   LOAD_START       -- address of first load packet
    gcall                   -- enter loaded code

Return:

-- Now set up invocation stack for the Init_system

    ajw    -RESET_WORKSPACE     -- reset work space after return

    ldl    OCCAM_WORKSPACE      -- get back boot link
    stl    BOOTLINK

    ldl    DATA_ADDRESS 	-- get address of processor structure
    ldl    MEMORY
    bsub
    stl    ENTRY_POINT		-- Write DATA TO ENTRY PARAMETER !!!


    ldl    ENTRY_ADDRESS 	-- convert to real entry address
    ldl    MEMORY
    bsub
    stl    LOAD_START

    ldl    NOTPROCESS
    stl    NEXT_POINT

    ldl    MEMORY               -- make DATA base offset and CODE base offset the same
    stl    BUFFER

    ldl    NEXT_ADDRESS_POINTER -- convert returned address of next sequence to 
    ldl    MEMORY               -- a real address
    bsub
    stl    NEXT_ADDRESS

    ldc    0
    stl    LOAD_LENGTH          -- clear bytes to load

    ldlp   NOTPROCESS
    stl    NEXT_WPTR
    
-- start clock

    ldc    0
    sttimer

    j      Startload 

