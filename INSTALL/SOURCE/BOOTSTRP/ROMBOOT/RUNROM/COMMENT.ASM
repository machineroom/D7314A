-- -----
--
--     (c) Copyright INMOS Limited 1990.
--
--     Comment module for the boot from ROM run from ROM modules,
--     NOTE this is a non executable comment bootstrap.
--
-- -----

#define    loader_buffer_size    120
#define    loader_work_space     32
#define    bootstrap_workspace   18

--

    align

Comment_runrom:
    global  Comment_runrom

    byte    0, 0, 0, 0          -- 32 bit 0 at start to indicate this is start

    byte    #07, #42, #54, #52  -- ^g BTR to indicate this is header.

    byte    #1                  -- Version byte
    byte    loader_buffer_size  -- Unrecoverable buffer space ( bytes ) for
                                -- network loader module.
    byte    loader_work_space + bootstrap_workspace
                                -- Data space required for bootstrap ( words )
                                -- Incorporating
                                --     Workspace for loader and sys procs.
                                --     Workspace for bootstrap.


    byte    0                   -- Length of string ( patched by collector )
    blkb    128                 -- Reserved space for string.

-- -----
--
--    Ensure that module is word length.
--
-- -----

    align
