--
-- Comment bootstrap for t2,t4,t8
--
        align

Comment_ternary:

global  Comment_ternary

	ajw 	4			-- _INITIAL_ADJUSTMENT 
        stl     1                       -- _LINK_LOCATION
        stl     1                       -- _LINK_LOCATION
        stl     1                       -- _LINK_LOCATION          -- Save Register C 

	mint
	ldl 	1			-- -LINK_LOCATION	-- reset link location
	stnl	0			-- link word

	mint				-- reset low priority queue
	stlf
	mint				-- reset high priority queue
	sthf


        ldc     (Comment_ternary-_Addr0)         -- Get MEMSTART
        ldpi
_Addr0:
        stl     0                       -- _MEM_START

	ldlp    6			-- One above the total workspace used

	wcnt                            -- Split address into word and byte part
	rev
	eqc     0
	eqc     0
	add
	bcnt                            -- A is word aligned
	stl	4			-- NEW_ADDRESS i.e. where to move to

        ldc     (_Main_Start-_Label1)      -- Get offset to main block section
        ldpi                           -- get address of such
_Label1:


	stl	5			-- Just temporary
	ldl	5

	ldl	4
	ldl	5			-- Get ready to calculate how much
	sub	
	stl     5
	ldl     5
	ldl	4			-- where to
	rev				-- A contains number of bytes
					-- B contains where to 
					-- C contains where from
        move                           --
        ldl     4                      -- NEW_ADDRESS            -- where to start executing
        gcall                          -- Go for it

	align

_Main_Start :
--
-- Enter here after move from initial stub. MEM_START, LINK_LOCATION have been 
-- moved as well. Now adjust workspace to point to them.
--
        --align

        ldl     4                      -- NEW_ADDRESS            -- Using old workspace pointer
	ldl     5                       
        add
        wcnt                           -- Split address into word part
                                       --   and its byte selector

        rev                            -- Get byte selector
        eqc     0                      -- if not zero then put true (1)
        eqc     0                      -- if not zero then put true (1)
--
-- The net effect of the above two instructions is to put TRUE in A if it was not
-- equal to zero. This is now to be used increment the word address
--

        add
        bcnt                           -- Address has been word adjusted correctly

        gajw                
        ajw  	-6           --

        j       _After_string           -- Jump        
	
--	align

_Before_string:
        align

    -- Reserve exactly 128 bytes for string
    --
    -- Name of file plus any padding goes here

        word    #0
     
        byte    #07
        byte    #42
        byte    #54
        byte    #4c                             --  .BTL in reverse

	byte    #1				-- Version byte
        byte    #0                             -- Primary bootstrap length
        byte    0                              -- Workspace for bootstrap and Network loader, init system
						--   and words for invocation stack

	byte    #0				-- Length of string
        blkb    128                            -- _STRING_SIZE

--	align

_After_string:

        ldc     0                      -- Make sure high bytes will be
        stl     2                      -- _NEXT_LENGTH            --   zero before getting real length in lsb
        ldlp    2                      -- _NEXT_LENGTH            -- Length of real bootstrap
        ldl     1                      -- _LINK_LOCATION          -- Link to load from
        ldc     1                      -- Number of bytes to load
        in                             -- Input the length of real bootstrap
                                       --   in lsb

        ldl     0                      -- _MEM_START              -- Start of memory for this Transputer
        ldl     1                      -- _LINK_LOCATION          -- Link to load from
        ldl     2                      -- _NEXT_LENGTH            -- Length of packet
        in                             -- Get packet of that length

        ldl     1                      -- _LINK_LOCATION          -- Restore Register C
        ldl     0                      -- _MEM_START
        ldl     2                      -- _NEXT_LENGTH
        add                            -- Address after real bootstrap
        wcnt                           -- Split address into word part
                                       --   and its byte selector
        rev      
	                      -- Get byte selector
        eqc     0                      -- if not zero then put true (1)
        eqc     0                      -- if not zero then put true (1)
--
-- The net effect of the above two instructions is to put TRUE in A if it was not
-- equal to zero. This is now to be used increment the word address
--

        add
        bcnt                           -- Address has been word adjusted correctly


--
-- B now contains Link address
--

        stl     3                      -- _NEW_WORK_POINTER       -- 
--
-- A now contains Link address
--

        ldl     0                      -- _MEM_START
        ldl     3                      -- _NEW_WORK_POINTER


--
-- C contains Link address, B contains MEM_START
--
        gajw

        rev
--
-- B contains Link address
--

        gcall                          --  Enter the real bootstrap at MEM_START
	align

_End_code :

_End_code_2:

--
-- Assume locaations after this is word aligned, and local data is here
--

--
--Where the constants are :
--

--    _MEM_START        = 0
--    _LINK_LOCATION    = 1
--    _NEXT_LENGTH      = 2        
--    _NEW_WORK_POINTER = 3
--    _NEW_ADDRESS      = 4

--    _BLOCK_LENGTH     = 256
--    _STRING_SIZE      = 128
