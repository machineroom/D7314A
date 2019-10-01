/* CMSIDENTIFIER
   PLAY:OUTPUT_C@401.AAAA-FILE;4(08-DEC-92)[FROZEN] */
/*
* 08/12/92: ahp:  Ensured all opened files are closed (TS/1973)
*/
/*****************************************************************************
 *
 *   Object Name : output.c
 *   Revision    : 1
 *
 *   Copyright (c) Inmos Ltd, 1988
 *   All rights reserved.
 *
 *   DESCRIPTION : This module of the buildmake program produces the output
 *
 *   DOCUMENTS   : The Buildmake Program, 16th May 1988 (R Knagg)
 *                 Buildmake Technical Documentation, May 31st 1988 (R Knagg)
 *
 *   HISTORY     : Created by Ray Knagg, 1st July 1988
 *          17/09/92: ahp:    added space around ":" in target definition
 *
 *****************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include "inmos.h"
#include "struct.h"
#include "header.h"

extern BOOL information;
extern file_t *files;
extern char output_file[];
extern BOOL delete_rule;
extern BOOL no_isearch;
extern BOOL output_file_exists; 
extern char ESCAPE_CHAR;

#define MAX_LINE_WIDTH 80

/*****************************************************************************
 *
 *  Procedure    : generate_library_build_files
 *
 *  Parameters   : a file_t structure and the file entry for a .LBB file
 *
 *  Return value : None
 *
 *  Function     : build a list of all the files in the library build file
 *                 This is all the direct dependents of the node.
 *
 *****************************************************************************/

PRIVATE void generate_library_build_files(lbb_files, LBB_file_entry)
file_t *lbb_files;
file_entry_t *LBB_file_entry;
{
  dependent_t  *dependents;
  file_entry_t *dependent_file_entry;

  dependents = dependents_file_entry_t(LBB_file_entry);
  reset_dependent_t(dependents);
  dependent_file_entry = next_dependent_t(dependents);
  while(dependent_file_entry != NULL)
    {
      dependent_file_entry = append_file_t(lbb_files, dependent_file_entry);
      if(type_file_entry_t(dependent_file_entry) == F_LIB)
        {
          dependent_t  *libs_dependents;
          file_entry_t *libs_source;
      
          libs_dependents = dependents_file_entry_t(dependent_file_entry);
          reset_dependent_t(libs_dependents);
          libs_source = next_dependent_t(libs_dependents);
          if(libs_source != NULL)
            if(type_file_entry_t(libs_source) == F_LBB)
              generate_library_build_files(lbb_files, libs_source);
        }
      dependent_file_entry = next_dependent_t(dependents);
    }

}

/*****************************************************************************
 *
 *  Procedure    : generate_library_usage_files
 *
 *  Parameters   : a file_t structure and the file entry for a .LBB file
 *
 *  Return value : None
 *
 *  Function     : build a list of all the files referenced by
 *                 the library build file and any dependents of it.
 *
 *****************************************************************************/

PRIVATE void generate_library_usage_files(liu_files, file_entry, lbb_files)
file_t *liu_files;
file_entry_t *file_entry;
file_t *lbb_files;
{
  if(!built_file_entry_t(file_entry))
    {
      dependent_t  *dependents;
      file_entry_t *dependent_file_entry;
    
      set_built_file_entry_t(file_entry);
      /* mark the node as having been visited */
    
      dependents = dependents_file_entry_t(file_entry);
      reset_dependent_t(dependents);
      dependent_file_entry = next_dependent_t(dependents);
      while(dependent_file_entry != NULL)
        {
          file_entry_t *entry_in_lbb_list, *dummy_entry;
          INT type;
        
          type  = type_file_entry_t(dependent_file_entry);
          if((type == F_LIB) || (type == F_TXX) || (type == F_SC) ||
             (type == F_USED_LIBRARY) || (type == F_CXX) ||
              (type == F_CCXX) || (type == F_CTXX))
            {
              entry_in_lbb_list = find_file_t(lbb_files,
                        name_file_entry_t(dependent_file_entry));
              if(entry_in_lbb_list == NULL)
                if(find_file_t(liu_files, name_file_entry_t(dependent_file_entry)) == NULL)
                  dummy_entry = append_file_t(liu_files, dependent_file_entry);
              if(type == F_LIB)
                {
                  dependent_t  *dependents;
                  file_entry_t *dependent_lib_file_entry;
              
                  dependents = dependents_file_entry_t(dependent_file_entry);
                  reset_dependent_t(dependents);
                  dependent_lib_file_entry = next_dependent_t(dependents);
                  if(dependent_lib_file_entry != NULL)
                    if(type_file_entry_t(dependent_lib_file_entry) == F_LBB)
                      generate_library_build_files(lbb_files, dependent_lib_file_entry);
                }
            }
          if(!((type == F_CXX) || (type == F_CCXX)))
            generate_library_usage_files(liu_files, dependent_file_entry,
                                         lbb_files);
          dependent_file_entry = next_dependent_t(dependents);
        }
    }
}

/*****************************************************************************
 *
 *  Procedure    : make_library_usage_file_list
 *
 *  Parameters   : none
 *
 *  Return value : None
 *
 *  Function     : given a lbb entry in the tree generate a list of library
 *                 usage files from it.
 *
 *****************************************************************************/

PUBLIC file_t *make_library_usage_file_list(lbb_entry)
file_entry_t *lbb_entry;
{
  file_t *usage_files, *lbb_files, *all_files;
  file_entry_t *file_entry;

  lbb_files   = create_file_t();
  usage_files = create_file_t();

  all_files = copy_file_t(files);
  reset_file_t(all_files);
  file_entry = next_file_t(all_files);
  while(file_entry != NULL)
    {
      set_not_built_file_entry_t(file_entry);
      file_entry = next_file_t(all_files);
    }

  generate_library_build_files(lbb_files,   lbb_entry);
  generate_library_usage_files(usage_files, lbb_entry, lbb_files);
  remove_file_t(lbb_files);

  return(usage_files);
}

/*****************************************************************************
 *
 *  Procedure    : output_library_usage_files
 *
 *  Parameters   : a library usage files specified as a dependent_info_node
 *
 *  Return value : None
 *
 *  Function     : search the file list for any libraries
 *                 for each file that is found traverse the tree to generate
 *                 a library usage file for that node.
 *
 *****************************************************************************/

PUBLIC void output_library_usage_file (file_info)
file_info_t *file_info;
{
  char         *library_name;
  file_entry_t *current_entry;


  library_name =  derive_child(name_file_info_t(file_info), EXT_LBB);

  reset_file_t(files);
  current_entry = find_file_t(files, library_name);

  if(current_entry != NULL)
    {
      file_t *usage_files;
      file_entry_t *usage_entry;
    
      usage_files = make_library_usage_file_list(current_entry);
    
      reset_file_t(usage_files);
      usage_entry = next_file_t(usage_files);
    
      if(usage_entry != NULL)
        {
          char *lbb_filename, *usage_filename;
          FILE *output_stream;
        
          lbb_filename   = name_file_entry_t(current_entry);
          usage_filename = derive_child(lbb_filename, EXT_LBU);
          
          if(strcmp(usage_filename, output_file) == 0)
            {
              lbb_filename   = realname_file_entry_t(current_entry);
              usage_filename = derive_child(lbb_filename, EXT_LBU);
            }
          else
            usage_filename = output_file;
          
          if(information)
            PRINT(stdout, "Generating library usage file \"%s\"\n",
                             usage_filename);
        
          output_stream = fopen(usage_filename, "w");
          if(output_stream != NULL)
            {
              fprintf(output_stream, "--\n-- %s\n--\n", IBMAKE_VERSION);
              fprintf(output_stream, "-- library usage file \"%s\"\n--\n",
                       usage_filename);
              while(usage_entry != NULL)
                {
                  fprintf(output_stream, "%s\n", name_file_entry_t(usage_entry));
                  usage_entry = next_file_t(usage_files);
                }
              fclose (output_stream);
            }
          else warning("cannot write library usage file\n", usage_filename);
        }
      remove_file_t(usage_files);
    }
}

/*****************************************************************************
 *
 *  Procedure    : test_for_filer_error
 *
 *  Parameters   : a result value from fprintf and the filename of the
 *                 file being written.
 *
 *  Return value : None
 *
 *  Function     : to abort the program cleanly when a filer error occurs.
 *
 *****************************************************************************/

PRIVATE void test_for_filer_error(stream, output_file)
FILE *stream;
char *output_file;
{ /* Changed by djm to use ferror, instead of cheking for eof*/
  if(ferror(stream))
    error("writing file\n", output_file);
}

/*****************************************************************************
 *
 *  Procedure    : generate_linker_order
 *
 *  Parameters   : a file_t structure and a file entry
 *
 *  Return value : None
 *
 *  Function     : generate a list of the linkable files in the order they
 *                 appear in the text from the file entry given.
 *
 *****************************************************************************/

PRIVATE void generate_linker_order(file_order, file_entry)
file_t *file_order;
file_entry_t *file_entry;
{
  dependent_t  *dependents;
  file_entry_t *dependent_file_entry;
  INT file_type;

  file_type = type_file_entry_t(file_entry);
  
  if((file_type == F_SC) || (file_type == F_TXX) || (file_type == F_CXX)
     || (file_type == F_LIB) || (file_type == F_IMPORT)
       || (file_type == F_USED_LIBRARY) || (file_type == F_CTXX)
         || (file_type==F_FTXX) || (file_type == F_CCXX))
    if(find_file_t(file_order, name_file_entry_t(file_entry)) == NULL)
      append_file_t(file_order, file_entry);

  dependents = dependents_file_entry_t(file_entry);
  reset_dependent_t(dependents);
  dependent_file_entry = next_dependent_t(dependents);
  while(dependent_file_entry != NULL)
    {
      if((file_type == F_LIB) &&
         (type_file_entry_t(dependent_file_entry) == F_LBB))
        {
          file_t *usage_files;
          file_entry_t *usage_file_entry;
        
          usage_files = make_library_usage_file_list(dependent_file_entry);
          reset_file_t(usage_files);
          usage_file_entry = next_file_t(usage_files);
          while(usage_file_entry != NULL)
            {
              if(find_file_t(file_order, name_file_entry_t(usage_file_entry)) == NULL)
                append_file_t(file_order, usage_file_entry);
              usage_file_entry = next_file_t(usage_files);
            }
        }
      else
        generate_linker_order(file_order, dependent_file_entry);
      dependent_file_entry = next_dependent_t(dependents);
    }
}

/*****************************************************************************
 *
 *  Procedure    : generate_linker_command_files
 *
 *  Parameters   : a file_t structure and the file entry for a .LXX file
 *
 *  Return value : None
 *
 *  Function     : find the main mody code of the link which is the only
 *                 direct dependent of the linker command file in the tree then
 *                 generate a list of the linkable files in the order they
 *                 appear in the text.
 *
 *****************************************************************************/

PRIVATE void generate_linker_command_file(file_order, LXX_file_entry)
file_t *file_order;
file_entry_t *LXX_file_entry;
{
  dependent_t  *dependents;
  file_entry_t *main_body_file_entry;

  dependents = dependents_file_entry_t(LXX_file_entry);
  reset_dependent_t(dependents);
  main_body_file_entry = next_dependent_t(dependents);

  generate_linker_order(file_order, main_body_file_entry);

}

/*****************************************************************************
 *
 *  Procedure    : output_linker_command_files
 *
 *  Parameters   : none
 *
 *  Return value : None
 *
 *  Function     : search the file list for any linker command files
 *                 for each file that is found traverse the tree to generate
 *                 a linker command file for that node.
 *
 *****************************************************************************/

PUBLIC void output_linker_command_files ()
{

  file_entry_t *current_entry;

  reset_file_t(files);
  current_entry = next_file_t(files);
  while(current_entry != NULL)
    {
      if(type_file_entry_t(current_entry) == F_LXX)
        {
          char *command_filename;
          FILE *output_stream;
        
          command_filename = realname_file_entry_t(current_entry);
        
          if(information)
            PRINT(stdout, "Generating linker command file \"%s\"\n",
                             command_filename);
          output_stream = fopen(command_filename, "w");
          if(output_stream != NULL)
            {
              char error_mode, file_type, processor_type;
              file_t *linker_order;
              file_entry_t *linker_entry;
            
              linker_order = create_file_t();
              generate_linker_command_file(linker_order, current_entry);
              fprintf(output_stream, "--\n-- imakef : %s\n--\n", IBMAKE_VERSION);
              test_for_filer_error(output_stream, command_filename);
              fprintf(output_stream, "-- linker command file \"%s\"\n--\n",
                               command_filename);
              test_for_filer_error(output_stream, command_filename);
              reset_file_t(linker_order);
              linker_entry = next_file_t(linker_order);
              if(linker_entry != NULL)
                {
                  fprintf(output_stream, "%s\n", name_file_entry_t(linker_entry));
                  test_for_filer_error(output_stream, command_filename);
                  linker_entry = next_file_t(linker_order);
                }
              while(linker_entry != NULL)
                {
                  if(type_file_entry_t(linker_entry) == F_SC)
                    {
                      fprintf(output_stream, "=%s\n", name_file_entry_t(linker_entry));
                      test_for_filer_error(output_stream, command_filename);
                    }
                  linker_entry = next_file_t(linker_order);
                }
              reset_file_t(linker_order);
              linker_entry = next_file_t(linker_order);
              if(linker_entry != NULL)
                linker_entry = next_file_t(linker_order);
              while(linker_entry != NULL)
                {
                  if(type_file_entry_t(linker_entry) != F_SC)
                    {
                      fprintf(output_stream, "%s\n", name_file_entry_t(linker_entry));
                      test_for_filer_error(output_stream, command_filename);
                    }
                  linker_entry = next_file_t(linker_order);
                }
              if(parse_extension(command_filename, &file_type, &error_mode, &processor_type))
                if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
                  {
                    {
                      if((processor_type == '2') || (processor_type == '3'))
                          fprintf(output_stream, "#INCLUDE occam2.lnk\n");
                      else if((processor_type == '5') || (processor_type == 'a') ||
                              (processor_type == '4') || (processor_type == 'b'))
                               fprintf(output_stream, "#INCLUDE occama.lnk\n");
                      else if((processor_type == '8') || (processor_type == '9'))
                               fprintf(output_stream, "#INCLUDE occam8.lnk\n");
                      test_for_filer_error(output_stream, command_filename);
                    }
                  }

              fclose (output_stream);         /* prevent running out of file*/
                                              /* descriptors on MS-DOS      */
              remove_file_t(linker_order);
            }
          else warning("cannot write linker command file\n", command_filename);
        }
      current_entry = next_file_t(files);
    }
}

/*****************************************************************************
 *
 *  Procedure    : output_dependents_file_entry_t
 *
 *  Parameters   : the files already output
 *                 the file entry and the output stream
 *
 *  Return value : None
 *
 *  Function     : first it makes sure that the file is not already output
 *                 Outputs the dependents of a file entry
 *                 It does this by outputing all the files below the entry
 *                 in the tree that do not have a direct action associated
 *                 with them.
 *
 *****************************************************************************/

PRIVATE void output_dependents_file_entry_t(depends,
                                            file_entry, output, length,start)
file_t       *depends;
file_entry_t *file_entry;
FILE         *output;
INT          *length;
INT          start;
{
  file_entry_t *dependent_file_entry;
  dependent_t  *dependents;
  action_t     *actions;
  char         *action_file_entry;
  INT          name_len;
  char         *fullName,*name;
  BOOL         print=TRUE;
  INT          x;
  
  fullName = realname_file_entry_t(file_entry);
  name = name_file_entry_t(file_entry);
  /* This bit added by DJM to stop things on ISEARCH being printed out */
  /* Is it already output ? */
  print=(find_file_t(depends,name)==NULL);
  /* If not, but its on ISEARCH, then don't print it */
  if(print && no_isearch && strcmp(name,fullName) ) print=FALSE;
  
  if(print)
    {
      file_entry = append_file_t(depends, file_entry);

      name_len = strlen(realname_file_entry_t(file_entry));
      if((*length + name_len+1) >= MAX_LINE_WIDTH)
        {
          fprintf(output,"\\\n");
          for(x=0;x<start;x++) fprintf(output," ");
          fprintf(output, "%s ", realname_file_entry_t(file_entry));
          *length = name_len +start+1;
        }
      else
        {
          fprintf(output, "%s ", realname_file_entry_t(file_entry));
          *length = *length + name_len+1;
        }
      test_for_filer_error(output, output_file);

      actions = actions_file_entry_t(file_entry);
      reset_action_t(actions);
      action_file_entry = next_action_t(actions);

      if(action_file_entry == NULL)
        {
          dependents = dependents_file_entry_t(file_entry);
          reset_dependent_t(dependents);
          dependent_file_entry = next_dependent_t(dependents);
          while(dependent_file_entry != NULL)
            {
              output_dependents_file_entry_t(depends, dependent_file_entry,
                                             output, length,start);
              dependent_file_entry = next_dependent_t(dependents);
            }
        }
    }
}


/*****************************************************************************
 *
 *  Procedure    : output deletable files
 *
 *  Parameters   : the output stream
 *
 *  Return value : None
 *
 *  Function     : Output a rule to delete all intermediate files
 *
 *****************************************************************************/

PUBLIC void output_deletable_files (output)
FILE *output;
{
  file_entry_t *current_entry;
  action_t     *actions;
  char         *action_file_entry;
  char         *s,*fileName; /* General string handler */

  fprintf(output, "clean  : delete\n"); 
  fprintf(output, "delete :\n");
  test_for_filer_error(output, output_file);
  reset_file_t(files);
  current_entry = next_file_t(files);
  while(current_entry != NULL)
    {
      if ( (! no_isearch) ||
           (strcmp(name_file_entry_t(current_entry),
                   realname_file_entry_t(current_entry)) == 0) )
      {
        switch(type_file_entry_t(current_entry))
          {
            case F_CFB_OC           :
              /* Simple way of deleting .clu files */
              fileName=realname_file_entry_t(current_entry);
              s=(char*) my_allocate(strlen(fileName) +2);
              remove_extension(s,fileName);
#ifdef VMS
              fprintf(output, "\t-$(DELETE) %s.clu;*\n",s);
#else
              fprintf(output, "\t-$(DELETE) %s.clu\n",s);
#endif
              free(s);
              test_for_filer_error(output, output_file);

              /* Drop through to delete .cfb */
            case F_SC               :
            case F_TXX              :
            case F_CXX              :
            case F_CCXX             :
            case F_CFB              :
            case F_SC_AND_LIB       :
            case F_CTXX             :
            case F_FTXX             :
#ifdef VMS
              fprintf(output, "\t-$(DELETE) %s;*\n",
                                   realname_file_entry_t(current_entry));
#else
              fprintf(output, "\t-$(DELETE) %s\n",
                                   realname_file_entry_t(current_entry));
#endif
              test_for_filer_error(output, output_file);
              break;
            default :
              break;
          }
      }
      current_entry = next_file_t(files);
    }
  fprintf(output, "\n");
  test_for_filer_error(output, output_file);
}

/*****************************************************************************
 *
 *  Procedure    : output_file_entry
 *
 *  Parameters   : the file entry and the output stream
 *
 *  Return value : None
 *
 *  Function     : Outputs the file entry in a make like format
 *
 *                 filename : dependent1 dependent2 ...
 *                   action a
 *                   action b
 *
 *****************************************************************************/

PUBLIC void output_file_entry_t (file_entry, output)
file_entry_t *file_entry;
FILE *output;
{
  file_entry_t *dependent_file_entry;
  dependent_t  *dependents;
  action_t     *actions;
  char         *action_file_entry;
  char         *fullName;
  char         *name;
  BOOL         print=TRUE;
  
  actions = actions_file_entry_t(file_entry);
  reset_action_t(actions);
  action_file_entry = next_action_t(actions);
  fullName=realname_file_entry_t(file_entry);
  name = name_file_entry_t(file_entry);
  
  print=(action_file_entry!=NULL);
  if(print && no_isearch && strcmp(name,fullName)) print=FALSE;
  
  if(print)
    {
      INT     length ;
      file_t *dependent_files;
    
      fprintf(output, "%s : ", realname_file_entry_t(file_entry));
      test_for_filer_error(output, output_file);
      length = strlen(realname_file_entry_t(file_entry))+2;
      /* should deal with tabs here */
    
      dependents = dependents_file_entry_t(file_entry);
      reset_dependent_t(dependents);
      dependent_file_entry = next_dependent_t(dependents);
      dependent_files = create_file_t();
      while(dependent_file_entry != NULL)
        {
          output_dependents_file_entry_t(dependent_files, dependent_file_entry,
                                         output, &length,length);
          dependent_file_entry = next_dependent_t(dependents);
        }
      fprintf(output, "\n");
      test_for_filer_error(output, output_file);
    
      while(action_file_entry != NULL)
        {
          fprintf(output, "\t%s\n", action_file_entry);
          test_for_filer_error(output, output_file);
          action_file_entry = next_action_t(actions);
        }
      fprintf(output, "\n");
      test_for_filer_error(output, output_file);
    
      remove_file_t(dependent_files);
    }
}


#define IMAKEF_CUT "##### IMAKEF CUT #####"


/***************************************************************************
* Name : get_line
* Func : Reads in one line of source text
* Param: Input stream
* Ret  : Pointer to string
*
*
*/

PRIVATE char * get_line(stream)
FILE * stream;
{ char * buf;
  char *p;
  int size=120;
  int len;
  
  buf=(char*) my_allocate(120);
  fgets(buf,120,stream);
  if(ferror(stream)) {free(buf);return NULL;}
  len=strlen(buf);
  while(len>=1 && buf[len-1]!='\n' && !feof(stream)) {
    size+=120;
    buf=(char*) realloc(buf,size);
    if(buf==NULL) error("Out Of Memory","");
    p=buf+len; /* Moves pointer on */
    fgets(p,120,stream);
    if(ferror(stream)) {free(buf);return NULL;}    
    len+=strlen(p);
  }

  /* resize the string */
  buf=(char*)realloc(buf,len+1);
  if(buf==NULL) error("Out Of Memory","");
  return (buf);
}



/* Used to link lines together */
typedef struct line_buf {
    char *s;
    struct line_buf *next;
}line_buf;


/***************************************************************************
* Name : scan_file_for_cut
* Func : looks for IMAKEF CUT
* Param: Input stream
* Ret  : linked list of lines up to that point
*
*
*/


PRIVATE line_buf * scan_file_for_cut(output_stream)
FILE * output_stream;

{ BOOL found_cut=FALSE;
  char *buf; /* Holds buffer */
  line_buf *head,*tail;
  line_buf *p;
  
  head=NULL;
  tail=NULL;
  while(!ferror(output_stream) && !feof(output_stream) && !found_cut) {
    buf=get_line(output_stream);
    if(buf==NULL) error("reading file",output_file);
    p=(line_buf*) my_allocate(sizeof(line_buf));

    p->s=buf;
    p->next=NULL;
    if(tail!=NULL) {
        tail->next=p;
        tail=p;
    }
    else {head=p;tail=p;}

    found_cut= !strncmp(buf,IMAKEF_CUT,strlen(IMAKEF_CUT));
  }

  if(ferror(output_stream) || (feof(output_stream) && !found_cut)) {
    while(head!=NULL) {
        p=head->next;
        free(head->s);
        free(head);
        head=p;
    }
  }
  
  return (head);
  
}


PRIVATE void print_header(output_stream)
FILE  * output_stream;
{
 char delete_name[200];
   
     if(ESCAPE_CHAR == '/')
        strcpy(delete_name, "DELETE=del\n");
     else strcpy(delete_name, "DELETE=rm\n");
     
    fprintf(output_stream, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
                                    LIBRARIAN_NAME,
                                    OCCAM_NAME,
                                    LINKER_NAME,
                                    CONFIG_NAME,
                                    OCONFIG_NAME,
                                    COLLECT_NAME,
                                    C_NAME,
                                    FORTRAN_NAME,
                                    delete_name,
                                    LIB_OPTIONS_NAME,
                                    OCCAM_OPTIONS_NAME,
                                    LINK_OPTIONS_NAME,
                                    CONF_OPTIONS_NAME,
                                    OCONF_OPTIONS_NAME,
                                    COLLECT_OPTIONS_NAME,
                                    C_OPTIONS_NAME,
                                    FORTRAN_OPTIONS_NAME);
    
    fprintf(output_stream,"\n%s\n\n",IMAKEF_CUT);
    test_for_filer_error(output_stream, output_file);
}
  


/*****************************************************************************
 *
 *  Procedure    : output tree
 *
 *  Parameters   : the output stream
 *
 *  Return value : None
 *
 *  Function     : Output a textual representation of the tree in Makefile
 *                 format.
 *
 *****************************************************************************/

PUBLIC void output_tree (output_stream)
FILE *output_stream;
{
  file_entry_t *current_entry;
  action_t     *actions;
  char         *action_file_entry;
  line_buf *l,*t;

  if(output_file_exists) {
     l=scan_file_for_cut(output_stream);
     fclose(output_stream); /* Close */
     output_stream=fopen(output_file,"w"); /* then reopen */
     if(output_stream==NULL) {
        char message[MAX_LINE_LEN];
                
        message[0] = '\0';
        strcat(message, "cannot open \"");
        strcat(message, output_file);
        strcat(message,"\"\n");
        error(message, "command line");
     }
                
     
     if(l!=NULL) {
        while(l!=NULL) {
            fputs(l->s,output_stream);
            test_for_filer_error(output_stream,output_file);
            t=l->next;
            free(l->s);
            free(l);
            l=t;
        }
        fputs("\n",output_stream);
        test_for_filer_error(output_stream,output_file);
     }
     else print_header(output_stream);
  }
  else print_header(output_stream);

  test_for_filer_error(output_stream,output_file);
  
  reset_file_t(files);
  current_entry = next_file_t(files);
  actions = actions_file_entry_t(current_entry);
  reset_action_t(actions);
  action_file_entry = next_action_t(actions);
  if(action_file_entry == NULL)
    error("target is not a derivable file\n",
          name_file_entry_t(current_entry));
  else
    while(current_entry != NULL)
      {
        output_file_entry_t(current_entry, output_stream);
        current_entry = next_file_t(files);
      }
  if(delete_rule)
    output_deletable_files(output_stream);

}



PRIVATE char *instring(line,string,start)
char *line,*string;
int start;
{
     int temp = 0;

     while (*line)
       {
         temp++;
         if (temp >= start)
           break;
         line++;
       }

     while(*line)
     {
          if(strncmp(string,line,strlen(string)))
              line++;
          else
              return (line);
     }
     return(0);
}


PRIVATE INT replace (line,old,new,buf,start)
char *line,*old,*new,*buf;
int start;
{
    char *len;

    if (len=instring(line,old,start))
    {
        *(len)=0;
        strcpy(buf,line);
        strcat(buf,new);
        strcat(buf,len+strlen(old));
        start = len + strlen(old)-line;
        strcpy(line,buf);
        replace(line,old,new,buf,start);
    }
    else
    {
        strcpy(buf,line);
        return(0);
    }
}

PRIVATE void output_batch (file_entry, output_stream)
file_entry_t *file_entry;
FILE         *output_stream;
{
  if(!built_file_entry_t(file_entry))
    {
      file_entry_t *dependent_file_entry;
      dependent_t  *dependents;
      action_t     *actions;
      char         *action_file_entry;
      INT          name_len;

      dependents = dependents_file_entry_t(file_entry);
      reset_dependent_t(dependents);
      dependent_file_entry = next_dependent_t(dependents);
      while(dependent_file_entry != NULL)
        {
           output_batch(dependent_file_entry, output_stream);
           dependent_file_entry = next_dependent_t(dependents);
        }
      actions = actions_file_entry_t(file_entry);
      reset_action_t(actions);
      action_file_entry = next_action_t(actions);
      if(action_file_entry  != NULL)
        {
          char temp[MAX_LINE_LEN];
      
          while(action_file_entry != NULL)
            {
              replace(action_file_entry, LIBRARIAN_CALL, "ilibr", temp, 0);
              replace(action_file_entry, OCCAM_CALL,     "oc", temp, 0);
              replace(action_file_entry, LINKER_CALL,    "ilink", temp, 0);
              replace(action_file_entry, CONFIG_CALL,    "icconf", temp, 0);
              replace(action_file_entry, COLLECT_CALL,   "icollect", temp, 0);
              replace(action_file_entry, OCONFIG_CALL,   "occonf", temp, 0);
              replace(action_file_entry, C_CALL,         "icc", temp, 0);
              replace(action_file_entry, FORTRAN_CALL,   "if77", temp, 0);
              replace(action_file_entry, OCCAM_OPTIONS_CALL, "", temp, 0);
              replace(action_file_entry, LINK_OPTIONS_CALL,  "", temp, 0);
              replace(action_file_entry, CONF_OPTIONS_CALL,  "", temp, 0);
              replace(action_file_entry, BOOT_OPTIONS_CALL,  "", temp, 0);
              replace(action_file_entry, OCONF_OPTIONS_CALL, "", temp, 0);
              replace(action_file_entry, LIB_OPTIONS_CALL,   "", temp, 0);
              replace(action_file_entry, C_OPTIONS_CALL,     "", temp, 0);
              replace(action_file_entry, FORTRAN_OPTIONS_CALL,"", temp, 0);
              replace(action_file_entry, COLLECT_OPTIONS_CALL,"", temp, 0);
              
              fprintf(output_stream, "%s\n", action_file_entry);
              test_for_filer_error(output_stream, output_file);
              action_file_entry = next_action_t(actions);
            }
          set_built_file_entry_t(file_entry);
        }
    }
}

/*****************************************************************************
 *
 *  Procedure    : output batch file
 *
 *  Parameters   : the output stream
 *
 *  Return value : None
 *
 *  Function     : Output a batch file to rebuild the tools.
 *
 *****************************************************************************/

PUBLIC void output_batch_file (output_stream)
FILE *output_stream;
{
  file_entry_t *current_entry, *first_entry;
  action_t     *actions;
  char         *action_file_entry;

  reset_file_t(files);
  current_entry = next_file_t(files);
  actions = actions_file_entry_t(current_entry);
  reset_action_t(actions);
  action_file_entry = next_action_t(actions);
  if(action_file_entry == NULL)
    error("target is not a derivable file\n",
          name_file_entry_t(current_entry));
  else
    {
      first_entry = current_entry;
      while(current_entry != NULL)
        {
           set_not_built_file_entry_t(current_entry);
           current_entry = next_file_t(files);
        }
      output_batch(first_entry, output_stream);
    }
}

/*****************************************************************************
 *
 *  Procedure    : debug
 *
 *  Parameters   : None
 *
 *  Return value : None
 *
 *  Function     : Output a textual representation of the tree
 *
 *****************************************************************************/

PUBLIC void debug ()
{
  file_entry_t *current_entry;
  FILE *output_stream;

  output_stream = fopen("debug.lis", "w");

  if(output_stream != NULL)
    {
      reset_file_t(files);
      current_entry = next_file_t(files);
      while(current_entry != NULL)
         {
          debug_file_entry_t(current_entry, output_stream);
          current_entry = next_file_t(files);
        }
      output_deletable_files(output_stream);
      fclose (output_stream);
    }
}

/*****************************************************************************
 *
 *  Procedure    : debug_file_entry
 *
 *  Parameters   : the file entry and the output stream
 *
 *  Return value : None
 *
 *  Function     :
 *
 *****************************************************************************/

PUBLIC void debug_file_entry_t (file_entry, output)
file_entry_t *file_entry;
FILE *output;
{
  file_entry_t *dependent_file_entry;
  dependent_t  *dependents;
  action_t     *actions;
  char         *action_file_entry;

  dependents = dependents_file_entry_t(file_entry);
  reset_dependent_t(dependents);
  dependent_file_entry = next_dependent_t(dependents);
  actions = actions_file_entry_t(file_entry);
  reset_action_t(actions);
  action_file_entry = next_action_t(actions);
  fprintf(output, "%s(%d) : ", name_file_entry_t(file_entry)
                             , type_file_entry_t(file_entry));
  while(dependent_file_entry != NULL)
    {
      fprintf(output, "%s ", name_file_entry_t(dependent_file_entry));
      dependent_file_entry = next_dependent_t(dependents);
    }
  fprintf(output, "\n");
  while(action_file_entry != NULL)
    {
      fprintf(output, "\t\t%s\n", action_file_entry);
      action_file_entry = next_action_t(actions);
    }
  fprintf(output, "\n");
}

