#include "memld.h"

    align
Ternary_for_floating_and_memstart:

global Ternary_for_floating_and_memstart

--
-- +2 Because of the transputer descheduling requirements NO DO FORGET
--
descriptor Ternary_for_floating_and_memstart "Ternary_for_floating_and_memstart" occam_harness ((MEMSTART+2)+TEMP_WORKSPACE)  0 ""

    ajw    -RESET_WORKSPACE     -- reset work space after return

    ldl    DATA_ADDRESS 	-- get address of processor structure
    stl    DATA_TO_RETURN       -- Write DATA TO ENTRY PARAMETER !!!

    ldl    ENTRY_ADDRESS 	-- convert to real entry address
    stl    0

    ldl    NOTPROCESS
    stl    NEXT_BOOT

    ldl    MEMORY               -- make DATA base offset and CODE base offset the same
    stl    BUFFER

    ldl    NEXT_ADDRESS_POINTER -- convert returned address of next sequence to 
    stl    NEXT_ADDRESS

    ldc    0
    stl    LOAD_LENGTH          -- clear bytes to load
    ldc    NOT_MOVED_YET
    stl    TERNARY_MOVED_WPTR

    ldlp   0
    stl    NEXT_WPTR

-- load code until terminator

Startload:

    ldlp   LOAD_LENGTH      -- packet length
    ldl    BOOTLINK_IN_PARAM         -- address of link
    ldc    1                -- bytes to load
    in                      -- input length byte

    ldl    LOAD_LENGTH      -- message length
    cj     Endload          -- quit if 0 bytes

CheckMoveStack:

    ldl    TERNARY_MOVED_WPTR   -- Need to check if the overlaying is about
    cj     AlreadyMovedStack    -- to clash with the current workspace

    ldl    NEXT_WPTR

    ldl    LOAD_LENGTH
    ldl    NEXT_ADDRESS
    sum

    gt     			-- 
    eqc    0

    cj     AlreadyMovedStack    -- Jump if not clashing

--
-- Need to move the workspace now
--

    ldl    NEXT_WPTR                                -- Get ready to move
    ldc    -TEMP_WORKSPACE
    ldl    INIT_SYSTEM_STACK
    wsub
    ldc    (DATA_TO_RETURN+2)
    bcnt
    move

    ldc    -TEMP_WORKSPACE
    ldl    INIT_SYSTEM_STACK
    wsub
    gajw
    
    ldc    ALREADY_MOVED
    stl    TERNARY_MOVED_WPTR

AlreadyMovedStack:

    ldl    NEXT_ADDRESS     -- start of area to load loader
    ldl    BOOTLINK_IN_PARAM        -- address of link
    ldl    LOAD_LENGTH      -- message length
    in                      -- input code block
    ldl    LOAD_LENGTH      -- message length
    ldl    NEXT_ADDRESS     -- area to load
    bsub                    -- new area to load
    stl    NEXT_ADDRESS     -- save area to load

    j      Startload        -- go back for next block

Endload:

    ldl    TERNARY_MOVED_WPTR   -- Need to move invocation stack if not 
    cj     FinishOverlaying     -- already moved

--
-- Need to move the workspace now
--
    ldl    NEXT_WPTR                                -- Get ready to move
    ldc    -TEMP_WORKSPACE
    ldl    INIT_SYSTEM_STACK
    wsub

    ldc    (DATA_TO_RETURN+2)
    bcnt
    move

    ldc    -TEMP_WORKSPACE
    ldl    INIT_SYSTEM_STACK
    wsub
    gajw

FinishOverlaying:

    ldc    0			-- Start timer
    sttimer	

    ldl    0
    ajw    TEMP_WORKSPACE+1

    gcall                   -- enter loaded code

Return:
