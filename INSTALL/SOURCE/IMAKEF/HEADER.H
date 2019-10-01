/* CMSIDENTIFIER
   PLAY:HEADER_H@397.AAAA-FILE;7(15-DEC-92)[FROZEN] */
/*****************************************************************************
 *
 *   Object Name : header.h
 *   Revision    : 1
 *
 *   Copyright (c) Inmos Ltd, 1988
 *   All rights reserved.
 *
 *   DESCRIPTION : The main header file for the program
 *
 *   DOCUMENTS   : The Buildmake Program, 16th May 1988 (R Knagg)
 *                 Buildmake Technical Documentation, May 31st 1988 (R Knagg)
 *
 *   HISTORY     : Created by Ray Knagg, 6th June 1988
 *                 Constants for Paths added 18th August 1988, RK
 *
 *****************************************************************************/

/* IBMAKE_VERSION "ibmake version 1.0d, alpha release 6th September 1988"   */
/* IBMAKE_VERSION "ibmake version 1.1a, alpha release 7th September 1988"   */
/* IBMAKE_VERSION "imakef version 1.3b, beta release 25th October 1988"     */
/* IBMAKE_VERSION "imakef version 1.3c, beta release 14th November 1988"    */
/* Not expanding files referenced from LIU files fixed 10:10:88             */
/* IBMAKE_VERSION "imakef version 1.5, post beta release 10th December 1988 */
/* First bug fixing session after the beta release */
/* IBMAKE_VERSION "imakef version 1.6, beta release 10th January 1989" */
/* Fix of the leading tabs bug */
/* IBMAKE_VERSION "imakef version 1.7, beta release 12th January 1989" */
/* Some slight alterations - no full names in lxx files */
/* IBMAKE_VERSION "imakef version 1.8, beta release 20th January 1989" */
/* IBMAKE_VERSION "imakef version 2.0, beta release 24th January 1989" */
/* Version where I attempt to make library usage files -
 * has a nasty bug in writing linker command files fixed by the next version */
/* IBMAKE_VERSION "imakef version 2.1, beta release 1st Febuary 1989" */
/* buffered output with fwrite for the lattice version */
/* IBMAKE_VERSION "imakef version 2.2, beta release 7th Febuary 1989" */
/* output file added to action strings for the compiler, linker, ect.
   added '/e' to action strings for TA, TC types. */
/* IBMAKE_VERSION "imakef version 2.3, beta release 28th February 1989" */
/* Help page alterations, Peters spelling mistake in error message */
/* IBMAKE_VERSION "Version 2.4, beta release 20th March 1989" */
/* Added '/b' option to produce a batch file which allows the complete
   rebuilding of a system */
/* IBMAKE_VERSION "Version 2.5, beta release 21st March 1989" */
/* allowed redirection to screen */
/* fixed bug of lxx file having incorrect component parts of a library */
/* IBMAKE_VERSION "Version 2.5, beta release 21st March 1989" */
/* Not allowed to have 'beta release' in the version string of the tools */
/* IBMAKE_VERSION "Version 2.60, 28th March 1989" */
/* Bug fix so that '/e' option is added for t2x, t2x */
/* IBMAKE_VERSION "Version 2.70, 14th April 1989" */
/* Fix to Michaels problem of imakef hanging intermitantly
   when making boot from rom program */
/* IBMAKE_VERSION "Version 2.80, 28th April 1989" */
/* Bug when making .TXX files causing PC, SUN to hang, Andy Sturgess
   found it. set_compiler_options not called before derive_options */
/* IBMAKE_VERSION "Version 2.90, 16th May 1989" */
/* '/r' added to action string on SUN for .BTR files should be '-r' */
/* added OCCAMBH.LIB to linker command file for .c5X files */
/* #define IBMAKE_VERSION "Version 2.95, 23rd May 1989" */
/* started making the adjustments required to bring imakef up to the
   new specification of the toolset */
/* #define IBMAKE_VERSION "Version 3.00, 13th November 1989" */
/* After my long absense due to I.M. I start altering it for the alpha release
 */
/* #define IBMAKE_VERSION "Version 3.01, 27th February 1989" */
/* imakef to alpha 4.6 */
/* #define IBMAKE_VERSION "Version 3.02, 2nd March 1989" */
/* Fixed johnw's bug in generate_library_usage_files */
/* #define IBMAKE_VERSION "Version 3.03, 12th March 1989" */
/* Fix to have ILINK /tx /m ...
   and to avoid the library bug with fclose(NULL) hanging
   and to implement the new compiler library scheme */
/* #define IBMAKE_VERSION "Version 3.04, 22nd March 1989" */
/* added /r delete intermediate files */
/* #define IBMAKE_VERSION "Version 3.05, 26th March 1989" */
/* fixed lot's of bugs and did some serious testing so it looks like it works*/
/* #define IBMAKE_VERSION "Version 3.06, 29th March 1989" */
/* Added -y to linker call, year is 1990 not 1989, and
 * nigels .bah bug ts10182 */
/* #define IBMAKE_VERSION "Version 3.07, 19th April 1990" */
/* exit properly when ok and BOOTOPT gone */
/* #define IBMAKE_VERSION "Version 3.08, 30th April 1990" */
/* Major Bug fixing session */
/* #define IBMAKE_VERSION "Version 3.09, 29th June 1990" */
/* Fixed transputer version and the delete rule */
/* #define IBMAKE_VERSION "Version 3.10, 13th July 1990" */
/* Updated to work with the new Occam toolset */
/* #define IBMAKE_VERSION "Version 3.20, 3rd September 1990" */
/* Bug fixing to beta release */
/*#define IBMAKE_VERSION "Version 3.30, 15th October 1990"*/
/* Fixed lots of bugs, and added some new features */
/*#define IBMAKE_VERSION "Version 3.35, 18th February 1990"*/
/* Fixed the multiple compilation bug */
/*#define IBMAKE_VERSION "Version 3.37, 19th February 1990"*/
/* Fixed another -y bug */
/*#define IBMAKE_VERSION "Version 3.39, 22nd February 1990"*/
/* Fixed bug causing PC version to crash */
/*#define IBMAKE_VERSION "Version 3.40, 13th March 1991"*/
/* Added in FORTRAN Support */
/*#define IBMAKE_VERSION "Version 3.50, 22nd March 1991"*/
/* Added imap support */
/*#define IBMAKE_VERSION "Version 3.60, 16th March 1992"*/
/* Put back inot icms ahp */
/* #define IBMAKE_VERSION "Version 3.70, 27 May 1992" */
/* TS/1837 - make map output work on C compiler and linker lines */
/* #define IBMAKE_VERSION "Version 3.75, 25 August 1992"*/
/* TS/1826 - -ni option still put the isearch'ed names in the delete actions */
/* #define IBMAKE_VERSION "Version 3.76, 26 August 1992"*/
/* TS/1448 - add space before colon in target definition */
/* #define IBMAKE_VERSION "Version 3.77, 17 September 1992" */
/* Removed 't' flag so that VAX/VMS C compiler could cope (non-ANSI too) */
/* #define IBMAKE_VERSION "Version 3.78, 3 November 1992" */

/* TS/1973 - closed all output files to stop DOS running out of descriptors */
#define IBMAKE_VERSION "Version 3.79, 08 December 1992"

#ifdef ANSI
extern void warning_on_line (char *message, char *filename, INT line_no);
extern void warning (char *message, char *filename);
extern void error_on_line (char *message, char *filename, INT line_no);
extern void error (char *message, char *filename);

extern void set_extension (char *filename, INT file_type, INT error_mode,
                           INT processor_type);
extern BOOL parse_extension(char *filename,
                            char *file_type, char *mode, char *type);
extern BOOL directory_specifier (char *filename);
extern BOOL file_extension (char *filename);
extern BOOL valid_error_mode (INT mode);
extern BOOL valid_processor_type (INT type);
extern void remove_extension (char *newfilename, char *oldfilename);
extern INT  file_type(char *name);
extern char *find_directory_specifier (char *filename);

extern void *my_allocate(INT size);

extern void output_linker_command_files (void);
extern void output_tree (FILE *output_stream);
extern void debug (void);
extern void output_library_usage_file (file_info_t *file_info);
extern file_t *make_library_usage_file_list(file_entry_t *lbb_entry);

extern char *derive_options(char *filename);
extern char *derive_cc_options (char *filename);
extern char *derive_f77_options (char *filename);
extern dependent_info_t *derive_dependent_info_t(file_info_t *file_info);
extern action_t *derive_action_t(file_entry_t *file_entry);
extern void derive_real_names(void);
extern char *derive_child(char *parent, char *extension);

extern file_info_t   *next_dependent_info_t(dependent_info_t *file_dependents);
extern void          reset_dependent_info_t(dependent_info_t *file_dependents);
extern void          remove_dependent_info_t(dependent_info_t *file_dependent);
extern dependent_info_t *create_dependent_info_t(void);
extern file_info_t *add_dependent_info_t(dependent_info_t *dependents,
                                         file_info_t *file_info);

extern file_info_t *inst_file_info_t (char *name, char *parent_name,
                                      char *options, INT type);
extern char *options_file_info_t(file_info_t *file_info);
extern char *parent_file_info_t(file_info_t *file_info);
extern char        *name_file_info_t (file_info_t *file_info);
extern INT          type_file_info_t (file_info_t *file_info);
extern void         set_type_file_info_t (file_info_t *file_info, INT type);


extern action_t *create_action_t(void);
extern action_entry_t *append_action_t(action_t *actions,
                                    action_entry_t *action);
extern action_entry_t *inst_action_entry_t(char *action);
extern char *next_action_t (action_t *actions);
extern void  reset_action_t (action_t *actions);

extern file_entry_t *inst_file_entry_t (char *name, char * parent,
                                        INT type, char *options);
extern void add_actions_file_entry_t(file_entry_t *file_entry,
                                     action_t     *actions);
extern char *name_file_entry_t (file_entry_t *file_entry);
extern char *realname_file_entry_t (file_entry_t *file_entry);
extern dependent_t *dependents_file_entry_t (file_entry_t *file_entry);
extern INT type_file_entry_t (file_entry_t *file_entry);
extern void append_dependent_file_entry_t(file_entry_t *file_entry,
                                          file_entry_t *dependent_entry);
extern void output_file_entry_t (file_entry_t *file_entry, FILE *output);
extern void debug_file_entry_t(file_entry_t *current_entry, FILE *output);
extern void set_name_file_entry_t (file_entry_t *file_entry,
                                            char *new_name);
extern void set_not_built_file_entry_t (file_entry_t *file_entry);
extern void set_built_file_entry_t (file_entry_t *file_entry);
extern char *options_file_entry_t (file_entry_t *file_entry);

extern file_t       *create_file_t (void);
extern file_t *copy_file_t (file_t *files);
extern void remove_file_t(file_t *files);
extern file_entry_t *append_file_t (file_t *files, file_entry_t *file_entry);
extern file_entry_t *insert_file_t (file_t *files, file_entry_t *file_entry);
extern file_entry_t *find_file_t (file_t *files, char *filename);
extern void          reset_file_t (file_t *files);
extern file_entry_t *next_file_t(file_t *files);
extern void add_actions_file_t(file_t *files);

extern BOOL built_file_entry_t (file_entry_t *file_entry);
extern BOOL can_build_file_entry_t (file_entry_t *file_entry);
extern action_t *actions_file_entry_t(file_entry_t *file_entry);

extern void reset_dependent_t (dependent_t *dependents);
extern file_entry_t *next_dependent_t (dependent_t *dependents);

extern FILE *popen_read (char *filename, char *pathname, char *full_name,
                         INT mode);
#else
extern void warning_on_line ();
extern void warning ();
extern void error_on_line ();
extern void error ();

extern void set_extension ();
extern BOOL parse_extension();
extern BOOL directory_specifier ();
extern BOOL file_extension ();
extern BOOL valid_error_mode ();
extern BOOL valid_processor_type ();
extern void remove_extension ();
extern INT  file_type();
extern char *find_directory_specifier ();

extern void *my_allocate();

extern void output_linker_command_files ();
extern void output_tree ();
extern void debug ();
extern void output_library_usage_file ();
extern file_t *make_library_usage_file_list();

extern char *derive_options();
extern char *derive_cc_options();
extern char *derive_f77_options();
extern dependent_info_t *derive_dependent_info_t();
extern action_t *derive_action_t();
extern void derive_real_names();
extern char *derive_child();

extern file_info_t   *next_dependent_info_t();
extern void          reset_dependent_info_t();
extern void          remove_dependent_info_t();
extern dependent_info_t *create_dependent_info_t();
extern file_info_t *add_dependent_info_t();

extern file_info_t *inst_file_info_t ();
extern char *options_file_info_t();
extern char *parent_file_info_t();
extern char        *name_file_info_t ();
extern INT          type_file_info_t ();
extern void         set_type_file_info_t ();


extern action_t *create_action_t();
extern action_entry_t *append_action_t();
extern action_entry_t *inst_action_entry_t();
extern char *next_action_t ();
extern void  reset_action_t ();

extern file_entry_t *inst_file_entry_t ();
extern void add_actions_file_entry_t();
extern char *name_file_entry_t ();
extern char *realname_file_entry_t ();
extern dependent_t *dependents_file_entry_t ();
extern INT type_file_entry_t ();
extern void append_dependent_file_entry_t();
extern void output_file_entry_t ();
extern void debug_file_entry_t();
extern void set_name_file_entry_t ();
extern void set_not_built_file_entry_t ();
extern void set_built_file_entry_t ();
extern char *options_file_entry_t ();

extern file_t       *create_file_t ();
extern void remove_file_t();
extern file_t *copy_file_t ();
extern file_entry_t *append_file_t ();
extern file_entry_t *insert_file_t ();
extern file_entry_t *find_file_t ();
extern void          reset_file_t ();
extern file_entry_t *next_file_t();
extern void add_actions_file_t();

extern BOOL built_file_entry_t ();
extern BOOL can_build_file_entry_t ();
extern action_t *actions_file_entry_t();

extern void reset_dependent_t ();
extern file_entry_t *next_dependent_t ();

extern FILE *popen_read ();
#endif

#define ESCAPE_CHAR_INIT '/'
#if  defined(SUN3) || defined(SUN4)
#undef ESCAPE_CHAR_INIT
#define ESCAPE_CHAR_INIT '-'
#endif
#ifdef LLL
#undef ESCAPE_CHAR_INIT
#define ESCAPE_CHAR_INIT switchar()
#endif
#ifdef ICC
#undef ESCAPE_CHAR_INIT
#define ESCAPE_CHAR_INIT setup_escape_char()
#endif

#define OPTIONS_START_CHAR '('
#define OPTIONS_END_CHAR   ')'
#define STDOUT_STR         "-"

#ifdef VMS
#define OK_RETURN_VALUE 1
#else
#define OK_RETURN_VALUE 0
#endif

#define COMPILER_OPTIONS_STR  "/tX /X"
#define COMPILER_OPTIONS_TYPE 2    /* index into the compiler options string */
#define COMPILER_OPTIONS_MODE 5    /*  '     '    '    '        '      '     */

#define C_OPTIONS_STR         "/tX"
#define C_OPTIONS_TYPE        2    /* index into the compiler options string */
#define FORTRAN_OPTIONS_STR   "/tX"
#define FORTRAN_OPTIONS_TYPE  2    /* index into the compiler options string */

/* index's into .*XX extensions */
#define ERROR_MODE_POS        3
#define FILE_TYPE_POS         1
#define PROCESSOR_TYPE_POS    2
#define MAKEFILE_EXTENSION    ".mak"

/* Do buffered output for the LLL C Compiler as it's printf does one
 * character per system call output
 */

#ifdef LLL
#define PRINT my_printf
#else
#define PRINT fprintf
#endif

#define MAX_FILE_ID_SIZE   256
#define MAX_LINE_LEN       512

#define F_OCC              0
#define F_PGM              1
#define F_LIB              2
#define F_SC               3
#define F_TXX              4
#define F_LBB              5
#define F_LBU              6
#define F_LXX              7
#define F_BXX              8
#define F_CXX              9
#define F_BTL             10
#define F_CFB             11
#define F_SC_AND_LIB      12
#define F_IMPORT          13
#define F_USED_LIBRARY    14
#define F_UNKNOWN         15
#define F_RXX             16
#define F_C               17
#define F_FORTRAN         18
#define F_EPR             19
#define F_MEM             20
#define F_IHX             21
#define F_LNK             22
#define F_CTXX            23
#define F_CCXX            24
#define F_CFS             25
#define F_CFB_OC          26
#define F_FTXX            27


#define EXT_OCC              ".occ"
#define EXT_INC              ".inc"
#define EXT_PGM              ".pgm"
#define EXT_LIB              ".lib"
#define EXT_SC               ".sc"
#define EXT_TXX              ".txx"
#define EXT_LBB              ".lbb"
#define EXT_LBU              ".liu"
#define EXT_LXX              ".lxx"
#define EXT_BXX              ".bxx"
#define EXT_CXX              ".cxx"
#define EXT_BTL              ".btl"
#define EXT_BTR              ".btr"
#define EXT_CFB              ".cfb"
#define EXT_CFB_OC           ".cfb"
#define EXT_EPR              ".epr"
#define EXT_MEM              ".mem"
#define EXT_IHX              ".ihx"
#define EXT_LNK              ".lnk"
#define EXT_C                ".c"
#define EXT_FORTRAN          ".f77"
#define EXT_CFS              ".cfs"

#define CHAR_CXX             'c'
#define CHAR_LXX             'l'
#define CHAR_TXX             't'

#define LIBRARIAN_NAME "LIBRARIAN=ilibr\n"
#define OCCAM_NAME     "OCCAM=oc\n"
#define LINKER_NAME    "LINK=ilink\n"
#define CONFIG_NAME    "CONFIG=icconf\n"
#define OCONFIG_NAME   "OCONFIG=occonf\n"
#define ADDBOOT_NAME   "ADDBOOT=iboot\n"
#define COLLECT_NAME   "COLLECT=icollect\n"
#define C_NAME         "CC=icc\n"
#define FORTRAN_NAME   "FORTRAN=if77\n"

#if  defined(SUN3) || defined(SUN4)
#define DELETE_NAME    "DELETE=rm\n"
#else
#define DELETE_NAME    "DELETE=del\n"
#endif

#define OCCAM_OPTIONS_NAME "OCCOPT=\n"
#define LINK_OPTIONS_NAME "LINKOPT=\n"
#define CONF_OPTIONS_NAME "CONFOPT=\n"
#define OCONF_OPTIONS_NAME "OCONFOPT=\n"
#define BOOT_OPTIONS_NAME "BOOTOPT=\n"
#define COLLECT_OPTIONS_NAME "COLLECTOPT=\n"
#define LIB_OPTIONS_NAME "LIBOPT=\n"
#define C_OPTIONS_NAME   "COPT=\n"
#define FORTRAN_OPTIONS_NAME  "F77OPT=\n"

#define LIBRARIAN_CALL "$(LIBRARIAN)"
#define OCCAM_CALL     "$(OCCAM)"
#define LINKER_CALL    "$(LINK)"
#define CONFIG_CALL    "$(CONFIG)"
#define OCONFIG_CALL    "$(OCONFIG)"
#define COLLECT_CALL    "$(COLLECT)"
/* #define ADDBOOT_CALL    "$COLLECT)" */
#define C_CALL          "$(CC)"
#define FORTRAN_CALL    "$(FORTRAN)"
#define OCCAM_OPTIONS_CALL "$(OCCOPT)"
#define LINK_OPTIONS_CALL "$(LINKOPT)"
#define BOOT_OPTIONS_CALL "$(BOOTOPT)"
#define CONF_OPTIONS_CALL "$(CONFOPT)"
#define OCONF_OPTIONS_CALL "$(OCONFOPT)"
#define COLLECT_OPTIONS_CALL "$(COLLECTOPT)"
#define LIB_OPTIONS_CALL "$(LIBOPT)"
#define C_OPTIONS_CALL "$(COPT)"
#define FORTRAN_OPTIONS_CALL "$(F77OPT)"

#define STR_INCLUDE "#INCLUDE"
#define STR_include "#include"
#define STR_use     "use"
#define STR_USE     "#USE"
#define STR_SC      "#SC"
#define STR_IMPORT  "#IMPORT"

#define PATHNAME    "ISEARCH"
#define TEXT_MODE   0
#define BINARY_MODE 0
