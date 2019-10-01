
--
-- 
-- The initial workspace requirement is found by reading the workspace
-- requirement from the loader \occam\ and subtracting the size of the workspace
-- used by both the loader and the bootstrap (\verb|temp.workspace|). This value
-- is incremented by 4 to accomodate the workspace adjustment by the call
-- instruction used to preserve the processor registers.
-- 
-- initial.adjustment := (loader.workspace + 4) - temp.workspace
-- occam work space, + 4 for call to save registers, - adjustment made
-- when entering occam. Must be at least 4
-- IF
--   initial.adjustment < 4
--     initial.adjustment := 4
--   TRUE
--     SKIP
-- 
-- set up work space, save registers,
-- save MemStart and NotProcess

-- Address to move workspace
#define MOVE_WPTR_TO            2
-- Loop index
#define BASE 			1
-- Loop count
#define COUNT			2
-- Start of loader
#define LOAD_START		0
-- Loader block length
#define LOAD_LENGTH		1
-- Start of next block 
#define NEXT_ADDRESS		2
-- Link booted from
#define BOOTLINK		3
-- Work space of loaded code
#define NEXT_WPTR		4

#define RETURN_ADDRESS		5
-- Workspace used by both preamble and loader
#define TEMP_WORKSPACE		RETURN_ADDRESS
-- Copy of MinInt						
#define NOTPROCESS		6
-- 1st param to loader (MinInt)
#define LINKS			NOTPROCESS
-- 2nd parameter to loader
#define BOOTLINK_IN_PARAM	7
-- 3rd parameter to loader
#define BOOTLINK_OUT_PARAM	8
-- 4th parameter to loader
#define MEMORY			9
-- 5th parameter to loader
#define BUFFER			10
-- 6th parameter to loader
#define NEXT_BOOT               11
-- 7th parameter to loader
#define DATA_TO_RETURN		12
-- 8th parameter to loader
#define ENTRY_POINT		13
-- Referenced from entry point
#define ENTRY_ADDRESS		14
-- Referenced from data point
#define DATA_ADDRESS		15
-- Start of boot part 2
#define NEXT_ADDRESS_POINTER	16
-- where to move invocation stack
#define INIT_SYSTEM_STACK       17
-- Memstart
#define MEMSTART		18		

#define RESET_WORKSPACE         ((TEMP_WORKSPACE)+4)
#define PACKET_LENGTH		120

#define T426_PROCESSOR_LOWER    30
#define T426_PROCESSOR_UPPER    39

--#define PARITY_ERROR_REGISTER   2147483492      -- 7FFFFF64
#define PARITY_ERROR_REGISTER   0x7FFFFF64

#define INITIAL_ADJUSTMENT	26
#define MEMSTART_OFFSET_T5_T8	112		-- 70
--#define MEMSTART_OFFSET_T5_T8 0x70
#define NUMBER_TO_INITIALISE	11

--
-- Ternary bootstrap defines (to make reading LESS confusing)
--
 
-- bool for moved workspace or not
#define TERNARY_MOVED_WPTR	RETURN_ADDRESS		

#define ALREADY_MOVED           0
#define NOT_MOVED_YET           1

 
