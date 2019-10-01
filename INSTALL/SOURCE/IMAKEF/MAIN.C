/* CMSIDENTIFIER
   PLAY:MAIN_C@399.AAAA-FILE;3(08-DEC-92)[FROZEN] */
/*
* 27/05/92: ahp:  Put Bruce Stenning's (BAS) changes into icms
* 08/12/92: ahp:  Ensured all opened files are closed (TS/1973)
*/
/*****************************************************************************
 *
 *   Object Name : main.c
 *   Revision    : 1
 *
 *   Copyright (c) Inmos Ltd, 1988
 *   All rights reserved.
 *
 *   DESCRIPTION : This is the main body of the buildmake program.
 *
 *   DOCUMENTS   : The Buildmake Program, 16th May 1988 (R Knagg)
 *                 Buildmake Technical Documentation, May 31st 1988 (R Knagg)
 *
 *   HISTORY     : Created by Ray Knagg, 1st June 1988
 *
 *****************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include "inmos.h"
#include "struct.h"
#include "header.h"
#ifdef ICC
#include <host.h>
#endif

PUBLIC file_t *files;
PUBLIC BOOL    information;
PUBLIC BOOL    mixed_language_program;
PUBLIC BOOL    interactive_debugging;
PUBLIC BOOL    no_isearch;
PUBLIC BOOL    debug_info;
PUBLIC BOOL    imap_output; /* BAS 09/03/92 */
PUBLIC BOOL    batch;
PUBLIC BOOL    delete_rule;
PUBLIC BOOL    output_file_exists;
PUBLIC char    output_file[MAX_FILE_ID_SIZE];
PUBLIC char    ESCAPE_CHAR;
PUBLIC char    COMPILER_OPTIONS[20]; /* to hold "/tX /X" */
PUBLIC char    C_OPTIONS[20];        /* to hold "/tX" */
PUBLIC char    FORTRAN_OPTIONS[20];        /* to hold "/tX" */


/*****************************************************************************
 *
 *  Procedure    : test_target
 *
 *  Parameters   : file_info
 *
 *  Return value : NONE
 *
 *  Function     : See if a make file can be made for the given target
 *                 If it cannot exit the program.
 *
 *****************************************************************************/

PRIVATE void test_target(file_info)
file_info_t *file_info;
{
  switch(file_type(name_file_info_t(file_info)))
    {
      case F_LIB :
      case F_SC  :
      case F_TXX :
      case F_BXX :
      case F_CXX :
      case F_BTL :
      case F_RXX :
      case F_LBU :
      /* library usage files are a valid target if you want to make them */
        break;
      default :
        error("cannot have a makefile\n", name_file_info_t(file_info));
        break;
    }
  if(mixed_language_program)
    {
      char *child_name, actual_name[MAX_FILE_ID_SIZE];
      FILE *source_f;

      switch(file_type(name_file_info_t(file_info)))
        {
          case F_TXX :
            child_name = derive_child(name_file_info_t(file_info), EXT_C);
            source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
            if(source_f != NULL)
              {
                fclose(source_f);
                set_type_file_info_t(file_info, F_CTXX);
              }
            else {
              child_name = derive_child(name_file_info_t(file_info), EXT_FORTRAN);
              source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
              if(source_f != NULL)
                {
                fclose(source_f);
                set_type_file_info_t(file_info, F_FTXX);
                }
            }
                 
          break;
          case F_CXX :
            child_name = derive_child(name_file_info_t(file_info), EXT_LNK);
            source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
            if(source_f != NULL)
              {
                fclose(source_f);
                set_type_file_info_t(file_info, F_CCXX);
              }
            break;
            break;
          default :
            break;
        }
    }
}

/*****************************************************************************
 *
 *  Procedure    : build_tree
 *
 *  Parameters   : file_info
 *
 *  Return value : the file entry of the node
 *
 *  Function     : generate a tree showing the dependencies and action reuqied
 *                 to generate a makefile for the file_info node
 *
 *****************************************************************************/

PRIVATE file_entry_t *build_tree (file_info)
file_info_t *file_info;
{ char parent_mode,mode;
  char parent_file_type,file_type;
  char parent_type,type;
  BOOL valid;
 
    
  file_entry_t *file_entry = find_file_t(files, name_file_info_t(file_info));

  if (file_entry != NULL) {
     /* Figure out the extensions for the files. Note that there are no
        circumstances where multiple libs can be put out with same name */
     if(file_info->type!=F_LIB && parse_extension(file_info->parent_name,&file_type,&mode,&type) &&
        parse_extension(file_entry->parent,&parent_file_type,
                                        &parent_mode,&parent_type) ) valid=TRUE;
     else valid=FALSE;                                        
  }

  /* If the file is not there, or it is to be compiled for a different
     target, then add it on the list */
  if(file_entry==NULL || (valid && (file_type==parent_file_type &&
                          (mode!=parent_mode || type!=parent_type) ) ) )
    {
      dependent_info_t  *file_dependents;
      file_info_t       *dependent;

      file_entry = append_file_t(files,
                      inst_file_entry_t(name_file_info_t(file_info),
                                        file_info->parent_name,
                                        type_file_info_t(file_info),
                                        options_file_info_t(file_info)));

      file_dependents = derive_dependent_info_t(file_info);
    
      reset_dependent_info_t(file_dependents);
      dependent = next_dependent_info_t(file_dependents);
      while (dependent != NULL)
        {
          append_dependent_file_entry_t(file_entry, build_tree(dependent));
          dependent = next_dependent_info_t(file_dependents);
        }
      remove_dependent_info_t(file_dependents);
    }
  return(file_entry);
}

/*****************************************************************************
 *
 *  Procedure    : check_tree
 *
 *  Parameters   : the root of the tree
 *
 *  Return value : a BOOLean value
 *
 *  Function     : examine the completed tree to see if it violates any rules
 *                 of the toolset such as circular references, SC's inside
 *                 libraries, and files referenced as both an SC and as a
 *                 library.
 *
 *****************************************************************************/

PRIVATE BOOL check_tree ()
{
  BOOL built = FALSE;
  BOOL building = TRUE;

  while(building)
    {
      file_entry_t *file_entry;
      reset_file_t(files);
      file_entry = next_file_t(files);
      building = FALSE;
      built    = TRUE;
      while(file_entry != NULL)
        {
          if(built_file_entry_t(file_entry) == FALSE)
            {
              if(can_build_file_entry_t(file_entry))
                building = TRUE;
              else built = FALSE;
            }
          file_entry = next_file_t(files);
        }
    }
  if(!built)
    {
      file_entry_t *file_entry;
      reset_file_t(files);
      file_entry = next_file_t(files);
    
      PRINT(stderr, "Cyclic reference in : \n");
      while(file_entry != NULL)
        {
          if(built_file_entry_t(file_entry) == FALSE)
            PRINT(stderr, "%s\n", name_file_entry_t(file_entry));
          file_entry = next_file_t(files);
        }
    }
  return(built);
}

#ifdef ICC
PUBLIC char setup_escape_char()
{
  int host, os, board;
  char escape_character;

  host_info(&host, &os, &board);
  switch(os)
    {
      case _IMS_OS_DOS:
      case _IMS_OS_VMS:
      case _IMS_OS_CMS:
        escape_character = '/';
        break;
      case _IMS_OS_HELIOS:
      case _IMS_OS_SUNOS:
        escape_character = '-';
        break;
      default:
        escape_character = '-';
        break;
    }
  return(escape_character);
}
#endif

/*****************************************************************************
 *
 *  Procedure    : error_on_line
 *
 *  Parameters   : an error string
 *                 a filename where the error occured
 *                 the line no in the file that the error occured at
 *                 var params
 *
 *  Return value : none
 *
 *  Function     : Displays the error message to the screen and aborts the
 *                 program. Should be used only for fatal errors like
 *                 MALLOC failing.
 *
 *****************************************************************************/

PUBLIC void error_on_line (message, filename, line_no)
char *message, *filename;
INT line_no;
{
  PRINT(stderr, "Error-imakef-%s(%d)-%s",filename, line_no, message);
  exit(42);
}

/*****************************************************************************
 *
 *  Procedure    : error
 *
 *  Parameters   : an error string
 *                 a filename where the error occured
 *                 the line no in the file that the error occured at
 *                 var params
 *
 *  Function     : Displays the error message to the screen and aborts the
 *                 program. Should be used only for fatal errors like
 *                 MALLOC failing.
 *
 *****************************************************************************/

PUBLIC void error (message, filename)
char *message, *filename;
{
  PRINT(stderr, "Error-imakef-%s-%s", filename, message);
  exit(42);
}

/*****************************************************************************
 *
 *  Procedure    : warning_on_line
 *
 *  Parameters   : an warning string
 *                 filename
 *                 line number
 *                 var params
 *
 *  Return value : none
 *
 *  Function     : Displays the warning message to the screen
 *
 *****************************************************************************/

PUBLIC void warning_on_line (message, filename, line_no)
char *message, *filename;
INT line_no;
{
  PRINT(stderr, "Warning-imakef-%s(%d)-%s", filename, line_no, message);
}

/*****************************************************************************
 *
 *  Procedure    : warning
 *
 *  Parameters   : an warning string
 *                 filename
 *                 var params
 *
 *  Return value : none
 *
 *  Function     : Displays the warning message to the screen
 *
 *****************************************************************************/

PUBLIC void warning (message, filename)
char *message, *filename;
{
  PRINT(stderr, "Warning-imakef-%s-%s", filename, message);
}

#ifdef LLL
static char buffer[1024];

/*****************************************************************************
 *
 *  Procedure    : my_printf
 *
 *  Parameters   : the output stream (stderr, stdout)
 *                 a printf string
 *                 var params
 *
 *  Return value : none
 *
 *  Function     : Displays the message to the screen by buffering up the
 *                 printf and using 'write'.
 *
 *****************************************************************************/

PUBLIC void my_printf (stream, str, args1, args2, args3, args4, args5, args6,
                                    args7, args8, args9)
FILE *stream;
char *str;
INT   args1, args2, args3, args4, args5, args6, args7, args8, args9;
{
  sprintf(buffer, str,
            args1, args2, args3, args4, args5, args6, args7, args8, args9);
  write(fileno(stream), buffer, strlen(buffer));
}
#endif

/*****************************************************************************
 *
 *  Procedure    : set_compiler_options
 *
 *  Parameters   : None
 *
 *  Return value : none
 *
 *  Function     : sets the compiler options string to one of
 *                 "/tX /X"
 *                 or
 *                 "-tX -X"
 *
 *****************************************************************************/

PRIVATE void set_compiler_options ()
{
  strcpy(COMPILER_OPTIONS, COMPILER_OPTIONS_STR);
  COMPILER_OPTIONS[0] = (char) ESCAPE_CHAR;
  COMPILER_OPTIONS[4] = (char) ESCAPE_CHAR;

  strcpy(C_OPTIONS, C_OPTIONS_STR);
  C_OPTIONS[0] = (char) ESCAPE_CHAR;
  strcpy(FORTRAN_OPTIONS, FORTRAN_OPTIONS_STR);
  FORTRAN_OPTIONS[0] = (char) ESCAPE_CHAR;
}

/*****************************************************************************
 *
 *  Procedure    : parse_command_line
 *
 *  Parameters   : argc, argv  - the command line
 *                 Outputs are :-
 *                 target_file - pointer to the target file string
 *                 output_file - pointer to the output file string
 *                 informative - BOOLean
 *                 mixed_language_program - allow C programs
 *
 *  Return value : A boolean which indicates whether the command line was
 *                 parseable.
 *
 *  Function     : To parse the command line
 *
 *****************************************************************************/

PRIVATE BOOL parse_command_line (argc, argv, targets, output_file,
                                 information, debug, batch, c_programs,
                                 interactive_debugging,
                                 debug_info, delete_rule, no_isearch,
                                 imap_output) /* BAS 09/03/92 */
INT argc;
char *argv[];
dependent_info_t *targets;
char *output_file;
BOOL *information, *debug, *batch, *c_programs, *interactive_debugging,
     *debug_info, *delete_rule, *no_isearch, *imap_output;
{
  INT command_line_valid = TRUE;
  file_info_t *target_info;
  BOOL output_file_set = FALSE;

  *information = FALSE;
  *debug = FALSE;
  output_file[0] = '\0';
  *batch = FALSE;
  *c_programs = FALSE;
  *no_isearch = FALSE;
  *interactive_debugging = TRUE;
  *debug_info = TRUE;
  *delete_rule = FALSE;
  *imap_output = FALSE; /* BAS 09/03/92 */

  {
    int i = 1;
    while (i < argc)
      {
        char *s = argv[i++];
        while (*s != 0)
          if((*s++) == ESCAPE_CHAR)
            switch (*s)
              {
                case 'N': case 'n':
                  s++;
                  if(*s=='I' || *s=='i') {*no_isearch=TRUE;s++;}
                  else {
                    char mess[MAX_LINE_LEN];
            
                    sprintf(mess, "'%c%c' is not a valid option\n",*(s-1),*s++);
                    error(mess, "command line");
                    command_line_valid = FALSE;
                  }
                  break;
                case 'I': case 'i': *information = TRUE;   s++;   break;
                case 'Z': case 'z': *debug = TRUE;         s++;   break;
                case 'B': case 'b': *batch = TRUE;         s++;   break;
                case 'C': case 'c': *c_programs = TRUE;    s++;   break;
                case 'Y': case 'y': *interactive_debugging = FALSE;    s++;   break;
                case 'D': case 'd': *debug_info = FALSE;    s++;   break;
                case 'R': case 'r': *delete_rule = TRUE;    s++;   break;
                case 'M': case 'm': *imap_output = TRUE;    s++;   break; /* BAS 09/03/92 */
                case 'O': case 'o':
                  {
                    int j = 0;
                    if (*++s == 0)
                      {
                        if (i < argc)
                          s = argv[i++];
                      }
                    while ((*s != 0) && (*s != ESCAPE_CHAR))
                      if(*s != ' ')
                        output_file[j++] = *s++;
                    output_file[j] = '\0';
                    output_file_set = TRUE;
                  }
                  break;
                default:
                  {
                    char mess[MAX_LINE_LEN];
            
                    sprintf(mess, "'%c' is not a valid option\n", *s++);
                    error(mess, "command line");
                    command_line_valid = FALSE;
                  }
                  break;
              }
          else
            {
            
              INT i = 0, target_type;
              char target_file[MAX_LINE_LEN];
            
              s--;
              while ((*s != 0) && (*s != ESCAPE_CHAR))
                target_file[i++] = *s++;
              target_file[i] = '\0';
            
              target_type = file_type(target_file);
              if(target_type != F_UNKNOWN)
                {
                  char *name;
                
                  name = my_allocate((strlen(target_file)+1) * sizeof(char));
                  name[0] = '\0';
                  strcpy(name, target_file);
                
                  target_info = add_dependent_info_t(targets,
                              inst_file_info_t(name, "", derive_options(name), target_type));
                }
              else
                {
                  char message[MAX_LINE_LEN];
                
                  message[0] = '\0';
                  strcat(message, "\"");
                  strcat(message, target_file);
                  strcat(message, "\" is of unknown type\n");
                  error(message, "command line");
                }
            }
      }
  }

  reset_dependent_info_t(targets);
  target_info = next_dependent_info_t(targets);
  if (target_info == NULL)
    {
      if(*information == FALSE)
      {
        PRINT(stdout, "imakef : INMOS Toolset Makefile generator\n");
        PRINT(stdout, "%s\n", IBMAKE_VERSION);
        PRINT(stdout, "(c) Copyright INMOS Limited 1988, 1989, 1990, 1991\n\n");
        PRINT(stdout, "Usage: imakef {filename} {%coption} \n\n", ESCAPE_CHAR);
        PRINT(stdout, "Options :\n");
        PRINT(stdout, "    I display information during processing\n");
        PRINT(stdout, "    O filename specify output filename (for makefile)\n");
        PRINT(stdout, "    Y disable interactive debugging \n");
        PRINT(stdout, "    D disable generation of debug information\n");
        PRINT(stdout, "    C Enable the building of C and FORTRAN programs\n");
        PRINT(stdout, "    R Enable the deletion of intermediate files\n");
        PRINT(stdout, "    NI Do not include files on ISEARCH\n");
        PRINT(stdout, "    M Produce output files for imap\n");
        if(*debug)
          PRINT(stdout, "    B make a file containing the commands required for building\n");
      }
      else
        PRINT(stdout, "%s\n", IBMAKE_VERSION);
      exit(OK_RETURN_VALUE);
    }
  
  if((output_file[0] == '\0') && (!output_file_set) && (target_info != NULL))
    {
      if(file_type(name_file_info_t(target_info)) == F_LBU)
        strcpy(output_file, name_file_info_t(target_info));
      else
        {
          remove_extension(output_file, name_file_info_t(target_info));
          strcat(output_file, MAKEFILE_EXTENSION);
        }
    }

  return(command_line_valid);
}

#ifdef LLL
/*****************************************************************************
 *
 *  Procedure    : perror
 *
 *  Parameters   : an warning string
 *
 *  Return value : none
 *
 *  Function     : prints the error number for the lattice system
 *
 *****************************************************************************/

extern INT errno;

PUBLIC void perror (message)
char *message;
{
  PRINT(stderr, "%s, errno : %d", message, errno);
}
#endif

PUBLIC int main (argc, argv)
INT argc;
char *argv[];
{
  dependent_info_t *targets;
  BOOL debug_on;
  FILE *output_stream;

  ESCAPE_CHAR = ESCAPE_CHAR_INIT;
  set_compiler_options();
  output_stream = NULL;

  targets = create_dependent_info_t();
  if (parse_command_line(argc, argv, targets, output_file,
                         &information, &debug_on, &batch,
                         &mixed_language_program,
                         &interactive_debugging, &debug_info, &delete_rule,
                         &no_isearch, &imap_output))
    {
      if(output_file[0] != '\0')
        {
          if(file_type(output_file) != F_LBU)
            {
              /* Attempt to open in update mode */
              output_file_exists=TRUE;
              output_stream = fopen(output_file, "r+");
              if (output_stream == NULL)
                 {
                   output_file_exists=FALSE;
                   /* Otherwise open in write */
                   output_stream=fopen(output_file,"w");
                 }
             if(output_stream==NULL || ferror(output_stream)) {
                char message[MAX_LINE_LEN];
                
                message[0] = '\0';
                strcat(message, "cannot open \"");
                strcat(message, output_file);
                strcat(message,"\"\n");
                error(message, "command line");
                }
            }
            
        }
      else
        output_stream = stdout;
      if (information)
        {
          file_info_t *target_info;
      
          PRINT(stdout, "imakef : Occam 2 Toolset Makefile generator\n");
          PRINT(stdout, "%s\n", IBMAKE_VERSION);
          PRINT(stdout, "(c) Copyright INMOS Limited 1988, 1989, 1990, 1991\n");
          PRINT(stdout, "input files  : ");
          reset_dependent_info_t(targets);
          target_info = next_dependent_info_t(targets);
          while(target_info != NULL)
            {
              PRINT(stdout, "%s ", name_file_info_t(target_info));
              target_info = next_dependent_info_t(targets);
            }
          PRINT(stdout, "\noutput file  : %s\n", output_file);
          if(debug_on)
            PRINT(stdout, "debug file   : debug.lis\n");
          if(batch)
            PRINT(stdout, "Generating ordered list of commands for building\n");
        }
      files = create_file_t();
      
      if (files != NULL)
        {
          file_entry_t *target_entry;
          file_info_t *target_info;
        
          reset_dependent_info_t(targets);
          target_info = next_dependent_info_t(targets);
          if(target_info != NULL)
            {
              if(file_type(name_file_info_t(target_info)) == F_LBU)
                {
                  file_info_t *next_target;
                
                  next_target = next_dependent_info_t(targets);
                  if(next_target != NULL)
                    error("a library usage file is only valid by itself", "command line");
                }
              else
                {
                  file_info_t *next_target;
                
                  next_target = next_dependent_info_t(targets);
                  while(next_target != NULL)
                    {
                      if(file_type(name_file_info_t(next_target)) == F_LBU)
                        error("a library usage file is only valid by itself", "command line");
                      next_target = next_dependent_info_t(targets);
                    }
                }
              reset_dependent_info_t(targets);
              target_info = next_dependent_info_t(targets);
              if(file_type(name_file_info_t(target_info)) == F_LBU)
                {
                  char         *library_name;
                  dependent_t  *library_dependents;
                  file_entry_t *library_entry, *library_source;
                  file_info_t  *library_info;
                
                  library_name = derive_child(name_file_info_t(target_info), EXT_LIB);
                  library_info  = add_dependent_info_t(targets,
                            inst_file_info_t(library_name, "", "", F_LIB));
                  library_entry = build_tree(library_info);
                  library_dependents = dependents_file_entry_t(library_entry);
                  reset_dependent_t(library_dependents);
                  library_source = next_dependent_t(library_dependents);
                  if(type_file_entry_t(library_source) != F_LBB)
                    error("cannot make library usage file for a library with no source",
                           name_file_info_t(target_info));
                }
              else
                {
                  test_target(target_info);
                  target_entry = build_tree(target_info);
              
                  target_info = next_dependent_info_t(targets);
              
                  while(target_info != NULL)
                    {
                      test_target(target_info);
                      target_entry = build_tree(target_info);
                      target_info = next_dependent_info_t(targets);
                    }
                }
        
              derive_real_names(); /* implement path searching */
              if (check_tree())
                {
                  add_actions_file_t(files);
                  reset_dependent_info_t(targets);
                  target_info = next_dependent_info_t(targets);
                  if(type_file_info_t(target_info) == F_LBU)
                    output_library_usage_file(target_info);
                  else
                    {
                      output_linker_command_files();
                      if(batch)
                        output_batch_file(output_stream);
                      else
                        output_tree(output_stream);
                    }
                }
              else error("tree checking failed - no output performed", "");
        
              if (debug_on) debug();
            }
        }
      else error("creating root node of file structure", "");
    }
  else error("command line is invalid", "");
  if ((output_stream != NULL) && (output_stream != stdout))
    fclose (output_stream);
  exit(OK_RETURN_VALUE);
}
