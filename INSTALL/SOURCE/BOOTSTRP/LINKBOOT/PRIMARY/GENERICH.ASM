#include "primary.h"

    align

Primary:

global Primary

    ajw    INITIAL_ADJUSTMENT 	-- see above
    call   0                	-- save registers

    ldc    Primary - Addr0    	-- distance to start byte
    ldpi                    	-- address of start
Addr0:
    stl    MEMSTART         	-- save for later use

    mint
    stl    NOTPROCESS       	-- save for later use

-- initialise process queues and clear error
    ldl    NOTPROCESS
    stlf                    	-- reset low priority queue

    ldl    NOTPROCESS
    sthf                    	-- reset high priority queue

-- use clrhalterr here to create bootstrap for REDUCED application

    sethalterr              	-- set halt on error
    testerr                 	-- read and clear error bit

-- initialise T8 error and rounding
    ldl    MEMSTART         	-- Check if processor has floating point unit by
    ldl    NOTPROCESS       	--   checking if (memstart >< mint) >= #70
    xor
    ldc    MEMSTART_OFFSET_T5_T8              -- Memstart for T5, T8
    rev                     	-- B = #70, A = (Memstart >< MINT)
    gt     
    eqc    0
    cj     Nofpu

    fptesterr            	-- floating check and clear error instruction
--
-- Now check if need to clear parity status registers
--
    lddevid			-- can do this since this is safe on all processors
    ldc    T426_PROCESSOR_LOWER-1
    gt     			-- Only on T426s at present
    cj     Noparityregs
    ldc    T426_PROCESSOR_UPPER+1
    lddevid
    gt
    cj     Noparityregs
    ldc    PARITY_ERROR_REGISTER -- Clear parity register by reading it
    ldnl   0
    
Noparityregs:

Nofpu:
-- initialise link and event words
    ldc    0
    stl    BASE             	-- index to words to initialise
    ldc    NUMBER_TO_INITIALISE -- no. words to initialise
    stl    COUNT            	-- count of words left
Startloop:
    ldl    NOTPROCESS
    ldl    BASE             	-- index
    ldl    NOTPROCESS
    wsub                    	-- point to next address
    stnl   0                	-- put NotProcess into addressed word
    ldlp   BASE             	-- address of loop control info
    ldc    Endloop - Startloop 	-- return jump
    lend                    	-- go back if more
Endloop:

-- set up some loader parameters. See the parameter
-- structure of the loader Done here so that the secondary is smaller
--
    ldlp   DATA_ADDRESS    	-- address of entry word
    stl    DATA_POINT      	-- store in param 7

    ldlp   ENTRY_ADDRESS    	-- address of entry word
    stl    ENTRY_POINT      	-- store in param 6

    ldlp   NEXT_ADDRESS_POINTER	-- Next code address (to be used to overlay loader)
    stl    NEXT_POINT     	-- buffer offset in param 5

    ldl    MEMSTART         	-- start of memory
    stl    MEMORY           	-- store in param 4

    ldl    BOOTLINK         	-- copy of bootlink
    stl    BOOTLINK_IN_PARAM   	-- store in param 2

--  Now find the corresponding output link and place in the parameter

    ldl	   BOOTLINK	
    ldnlp  -4		    	-- Calculate the output link address
    stl    BOOTLINK_OUT_PARAM  	-- store in param 3
  
-- load bootloader over bootstrap
-- code must be 2 bytes shorter than bootstrap

    ldlp   LOAD_LENGTH      	-- packet size word
    ldl    BOOTLINK         	-- address of link
    ldc    1                	-- bytes to load
    in                      	-- input length byte

    ldl    MEMSTART         	-- area to load bootloader
    ldl    BOOTLINK         	-- address of link
    ldl    LOAD_LENGTH      	-- message length
    in                      	-- input bootloader

-- enter code just loaded


    ldl    MEMSTART         -- start of loaded code
    gcall                   -- enter bootloader


