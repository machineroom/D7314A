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

#define BASE 			1		-- Loop index
#define COUNT			2		-- Loop count
#define LOAD_START		0		-- Start of loader
#define LOAD_LENGTH		1		-- Loader block length
#define NEXT_ADDRESS		2		-- Start of next block 
#define BOOTLINK		3		-- Link booted from
#define NEXT_WPTR		4		-- Work space of loaded code
-- Return address from loader
#define RETURN_ADDRESS		5		
-- Workspace used by both 
#define TEMP_WORKSPACE		RETURN_ADDRESS	
						--   preamble and loader
-- Copy of MinInt
#define NOTPROCESS		6		
-- 1st param to loader (MinInt)
#define LINKS			NOTPROCESS	
#define BOOTLINK_IN_PARAM	7		-- 2nd parameter to loader
#define BOOTLINK_OUT_PARAM	8		-- 3rd parameter to loader
#define MEMORY			9		-- 4th parameter to loader
#define BUFFER			10		-- 5th parameter to loader
#define NEXT_POINT		11		-- 6th parameter to loader
#define ENTRY_POINT		12		-- 7th parameter to loader
#define DATA_POINT		13		-- 8th parameter to loader
#define DATA_ADDRESS		14		-- Referenced from entry point
#define ENTRY_ADDRESS		15		-- Referenced from data point
#define NEXT_ADDRESS_POINTER	16		-- Start of boot part 2
-- Memstart
#define MEMSTART		17		

#define OCCAM_WORKSPACE 	18		-- Safe area to put bootlink
#define BUFFER_START		((MEMSTART)+2)

#define RESET_WORKSPACE         ((TEMP_WORKSPACE)+4)
#define PACKET_LENGTH		120

#define T426_PROCESSOR_LOWER    30
#define T426_PROCESSOR_UPPER    39

#define PARITY_ERROR_REGISTER   2147483492      -- 7FFFFF64

#define INITIAL_ADJUSTMENT	21              -- See above
#define MEMSTART_OFFSET_T5_T8	112		-- 70
#define NUMBER_TO_INITIALISE	11

 
