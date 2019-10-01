/* CMSIDENTIFIER
   PLAY:DERIVE_C@395.AAAA-FILE;4(15-DEC-92)[FROZEN] */
/*
* 27/05/92: ahp:  Put Bruce Stenning's (BAS) changes into icms
* 25/08/92: ahp:  TS/1837: Map file request did not build map files
*/
/*****************************************************************************
 *
 *   Object Name : derive.c
 *   Revision    : 1
 *
 *   Copyright (c) Inmos Ltd, 1988
 *   All rights reserved.
 *
 *   DESCRIPTION : This module of the buildmake program hold the procedures
 *                 which use the rules of the toolset to derive dependent files
 *                 and actions to update targets
 *
 *   DOCUMENTS   : The Buildmake Program, 16th May 1988 (R Knagg)
 *                 Buildmake Technical Documentation, May 31st 1988 (R Knagg)
 *
 *   HISTORY     : Created by Ray Knagg, 1st July 1988
 *                 Cludge to allow the full pathname of a file and it's
 *                 parent to be entered into the structure - this should be
 *                 done properly. Ray Knagg 18th August 1988.
 *                 Fixed the LIU file bug - 9th Dec 1988 - Ray Knagg
 *
 *****************************************************************************/

#include <stdio.h>
#include <ctype.h> 
#include "inmos.h"
#include "struct.h"
#include "header.h"

extern BOOL information;
extern file_t *files;
extern char ESCAPE_CHAR;
extern char COMPILER_OPTIONS[];
extern char C_OPTIONS[];
extern char FORTRAN_OPTIONS[];
extern BOOL mixed_language_program;
extern BOOL interactive_debugging;
extern BOOL debug_info;
extern BOOL imap_output; /* BAS 09/03/92 */


/*****************************************************************************
 *
 *  Procedure    : derive_child
 *
 *  Parameters   : two strings, parent filename, and an extension
 *
 *  Return value : pointer to the filename of the child
 *
 *  Function     : form a filename from the parent file and the given extension
 *
 *****************************************************************************/

PUBLIC char *derive_child (parent_name, extension)
char *parent_name, *extension;
{
  char *child_name;

  child_name = my_allocate((strlen(parent_name)+5) * sizeof(char));
  /* the extra space is for when a .bt file -> a .pgm file */
  /* Also if no file extension !! */
  remove_extension(child_name, parent_name);
  strcat(child_name, extension);

  return(child_name);
}

/*****************************************************************************
 *
 *  Procedure    : process_line
 *
 *  Parameters   : the line to process
 *                 the dependent info structure and the file info
 *                 of the file being searched, the line number
 *
 *  Return value : None
 *
 *  Function     : process the line for any references and add them
 *                 to the dependent_info_t structure.
 *
 *****************************************************************************/

PRIVATE void process_line (line, dependents, file_info, line_no)
char *line;
dependent_info_t *dependents;
file_info_t *file_info;
INT line_no;
{
  char *source_name = name_file_info_t(file_info);

  switch(type_file_info_t(file_info))
    {
      case F_LNK          :
      case F_LBU          :
      case F_LBB          :
        {
        char input_file[MAX_FILE_ID_SIZE], actual_name[MAX_FILE_ID_SIZE];
        char options[MAX_FILE_ID_SIZE];
        INT pos;
      
        while (((*line == ' ') || (*line == '\t')) && (*line))
          line++;
        if((*line) && (*line != ESCAPE_CHAR))
          {
            INT processing = TRUE;
          
            while(processing)
              {
                pos = 0;
                options[0] = '\0';
                while (((*line == ' ') || (*line == '\t')) && (*line))
                  line++;
                if((*line == '-') && (*(line+1) == '-'))
                  processing = FALSE;
                else if ((*line == 0) || (*line == '\n'))
                  processing = FALSE;
                else
                  {
                    if (*line == '#')
                      {
                        if (!strncmp(line, STR_include, strlen(STR_include)))
                          {
                            line     += strlen(STR_include);
                            while (((*line == ' ') || (*line == '\t')) && (*line))
                              line++;
                          }
                        else if (!strncmp(line, STR_INCLUDE, strlen(STR_INCLUDE)))
                          {
                            line     += strlen(STR_INCLUDE);
                            while (((*line == ' ') || (*line == '\t')) && (*line))
                              line++;
                          }
                        else if (type_file_info_t(file_info) == F_LNK)
                          /* linker directive skip line */
                          processing = FALSE;
                      }
                    if(processing)
                      {
                        while((*line != 0) && (*line != ' ') && (*line != OPTIONS_START_CHAR) &&
                              (*line != '\n') && !((*line == '-') && (*(line+1) == '-')))
                          input_file[pos++] = *line++;
                        input_file[pos] = '\0';
                        while (((*line == ' ') || (*line == '\t')) && (*line))
                          line++;
                  
                        {
                          char *child_name, *child_options, *derived_options;
                          file_info_t *child_file_info;
                          INT child_type;
                        
                          child_name = my_allocate((strlen(input_file)+1) * sizeof(char));
                          strcpy(child_name, input_file);
                          child_name[strlen(input_file)] = '\0';
                        
                          {
                            derived_options = derive_options(child_name);
                            if(type_file_info_t(file_info) == F_LBU)
                              child_type = F_USED_LIBRARY;
                            else
                              {
                                child_type = file_type(child_name);
                                if((child_type == F_TXX) && mixed_language_program)
                                   {
                                     FILE *source_f;
                                     char *source_name;
                            
                                     source_name = derive_child(child_name, EXT_C);
                                     source_f = popen_read(source_name, PATHNAME, actual_name, TEXT_MODE);
                                     if(source_f != NULL)
                                       {
                                         derived_options = derive_cc_options(child_name);
                                         child_type = F_CTXX;
                                         fclose(source_f);
                                       }
                                     else { /* Try and get fortran */
                                     source_name=derive_child(child_name,EXT_FORTRAN);
                                     source_f = popen_read(source_name, PATHNAME, actual_name, TEXT_MODE);
                                     if(source_f != NULL)
                                       {
                                         derived_options = derive_f77_options(child_name);
                                         child_type = F_FTXX;
                                         fclose(source_f);
                                       }
                                     }
                                   }
                            
                              }
                          
                            child_options = my_allocate((strlen(options)+strlen(derived_options)+1)
                                                    * sizeof(char));
                            strcpy(child_options, options);
                            strcat(child_options, derived_options);
                          
                            child_file_info = add_dependent_info_t(dependents,
                                                   inst_file_info_t(child_name,
                                                     name_file_info_t(file_info),
                                                       child_options, child_type));
                          }
                        }
                      }
                  }
              }
          }
        }
        break;
      case F_OCC          :
        {
          INT  child_type = F_UNKNOWN, pos;
          BOOL found_reference = FALSE;

          char reference[MAX_FILE_ID_SIZE];
          INT  reference_file_type;
          
          while (((*line == ' ') || (*line == '\t')) && (*line))
            line++;
          if (*line == '#')
            {
              if (!strncmp(line, STR_INCLUDE, strlen(STR_INCLUDE)))
                {
                  child_type = F_OCC;
                  line     += strlen(STR_INCLUDE);
                }
              else if (!strncmp(line, STR_USE, strlen(STR_USE)))
                {
                  if((type_file_info_t(file_info) == F_PGM) ||
                     (type_file_info_t(file_info) == F_CFS))
                    child_type = F_CXX;
                  else child_type = F_TXX;
                  line     += strlen(STR_USE);
                }
              else if (!strncmp(line, STR_SC, strlen(STR_SC)))
                {
                  if((type_file_info_t(file_info) == F_PGM) ||
                     (type_file_info_t(file_info) == F_CFS))
                    warning_on_line("#SC references are illegal in configuration text\n",
                             source_name, line_no);
                  child_type = F_SC;
                  line     += strlen(STR_SC);
                }
              else if (!strncmp(line, STR_IMPORT, strlen(STR_IMPORT)))
                {
                  if((type_file_info_t(file_info) == F_PGM) ||
                     (type_file_info_t(file_info) == F_CFS))
                    warning_on_line("#IMPORT references are illegal in configuration text\n",
                             source_name, line_no);
                  child_type = F_IMPORT;
                  line     += strlen(STR_IMPORT);
                }
              if (child_type != F_UNKNOWN)
                {
                  while (((*line == ' ') || (*line == '\t')) && (*line))
                    line++;
                  if (*line == '"')
                    {
                      pos = 0;
                      line++;
                      while((*line != '"') && (*line))
                        {
                          reference[pos++] = *line;
                          line++;
                        }
                      if(*line == '"')
                        {
                          reference[pos] = '\0';
                          found_reference = TRUE;
                        }
                      else warning_on_line("incomplete compiler directive\n", source_name, line_no);
                    }
                  else warning_on_line("incomplete compiler directive\n",
                                        source_name, line_no);
                }
              if (found_reference && (child_type != F_IMPORT))
                {
                  if((child_type == F_TXX) || (child_type == F_SC))
                    {
                      char file_type, error_mode, processor_type;
                  
                      /* if there is no extension */
                      if(!file_extension(reference))
                        if(parse_extension(parent_file_info_t(file_info),
                                           &file_type, &error_mode, &processor_type))
                          {
                            strcat(reference, EXT_TXX);
                            set_extension(reference, CHAR_TXX, error_mode, processor_type);
                          }
                    }
                  if(child_type == F_OCC)
                    {
                      /* if there is no extension */
                      if(!file_extension(reference))
                        strcat(reference, EXT_OCC);
                    }
                  reference_file_type = file_type(reference);
                  switch(reference_file_type)
                    {
                      case F_LIB          :
                        if(child_type == F_OCC)
                          warning_on_line("#INCLUDE may not reference a library\n",
                                          source_name, line_no);
                        child_type = F_LIB;
                        break;
                      case F_SC           :
                      case F_TXX          :
                        if(child_type == F_OCC)
                          warning_on_line("#INCLUDE may not reference binary files\n",
                                    source_name, line_no);
                        else if(type_file_info_t(file_info) == F_PGM)
                          child_type = F_TXX;
                        break;
                      case F_OCC          :
                      case F_PGM          :
                      case F_CFS          :
                        if((child_type == F_SC) || (child_type == F_TXX))
                          warning_on_line("#SC, #USE may not reference source files\n",
                                        source_name, line_no);
                        break;
                      case F_CXX          :
                        if(child_type == F_OCC)
                          warning_on_line("#INCLUDE may not reference binary files\n",
                                    source_name, line_no);
                        else child_type = F_CXX;
                        break;
                      case F_LBB          :
                      case F_BXX          :
                      case F_BTL          :
                      case F_LBU          :
                      case F_LXX          :
                      case F_SC_AND_LIB   :
                      case F_UNKNOWN      :
                      case F_USED_LIBRARY :
                      case F_IMPORT   :
                        {
                           char message[MAX_LINE_LEN];
                           message[0] = '\0';
                      
                           strcat(message, "\"");
                           strcat(message, reference);
                           strcat(message, "\" unknown/illegal file reference\n");
                           warning_on_line(message, source_name, line_no);
                        }
                        break;
                    }
                  if(reference_file_type == F_UNKNOWN)
                    child_type = F_UNKNOWN;
                }
            }
          if (found_reference)
            {
              char *child_name;
              file_info_t *child_file_info;
              /*
              if(added_extension)  {
              child_name = my_allocate((strlen(old_ref)+1) * sizeof(char));
              strcpy(child_name, old_ref);
              child_name[strlen(old_ref)] = '\0';
              }
              else {*/
              child_name = my_allocate((strlen(reference)+1) * sizeof(char));
              strcpy(child_name, reference);
              child_name[strlen(reference)] = '\0';
              
              
              child_file_info = add_dependent_info_t(dependents,
                                     inst_file_info_t(child_name,
                                       parent_file_info_t(file_info),
                                         derive_options(reference), child_type));
            }
        }
        break;

      case F_FORTRAN:
       {
         INT child_type=F_UNKNOWN;
         BOOL found_reference=FALSE;
         char reference[MAX_FILE_ID_SIZE];
         INT x,pos,len;
         char * copy;

         len=strlen(line);
         copy=(char*)my_allocate(len);
         /* Strip out all spaces and upper case first 8 chars */
         for(x=0,pos=0;x<len;x++) {
             if(!isspace(line[x])) {
                if(pos<=7) copy[pos]=toupper(line[x]);
                else copy[pos]=line[x];
                pos++;
             }
         }
         copy[pos]='\0'; /* Fill in \0 */

         /* Check if include */
         if(!strncmp(copy,"INCLUDE",7) || !strncmp(copy,"DINCLUDE",8)) {
            if(copy[0]=='D') x=8;
            else x=7;
            pos=0;
            switch(copy[x]) {
                case '"' : for(x++;copy[x]!='"' && copy[x]!='\0';x++) {
                                reference[pos]=copy[x];
                                pos++;
                           }
                           reference[pos]='\0';
                           if(copy[x]!='"')
                              warning_on_line("incomplete compiler directive\n",
                               source_name,line_no);
                           else found_reference=TRUE;
                           break;

                case '\'' : for(x++;copy[x]!='\'' && copy[x]!='\0';x++) {
                                reference[pos]=copy[x];
                                pos++;
                           }
                           reference[pos]='\0';
                           if(copy[x]!='\'')
                              warning_on_line("incomplete compiler directive\n",
                                              source_name,line_no);
                           else found_reference=TRUE;
                           break;                           

                default   : warning_on_line("incomplete compiler directive\n",
                                              source_name,line_no);
	    }

	    free(copy);
	    
            if (found_reference)
            {
              char *child_name;
              file_info_t *child_file_info;
              char actual_name[MAX_FILE_ID_SIZE];
              FILE *source_f;

              child_type=F_FORTRAN;
              child_name = my_allocate((strlen(reference)+1) * sizeof(char));
              strcpy(child_name, reference);
              child_name[strlen(reference)] = '\0';
              source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
              if(source_f == NULL)
                {
                   char message[MAX_LINE_LEN];
                   message[0] = '\0';
                
                   strcat(message, "\"");
                   strcat(message, reference);
                   strcat(message, "\" does not exist for INCLUDE directive\n");
                   warning_on_line(message, source_name, line_no);
                }
              else
                {
                  child_file_info = add_dependent_info_t(dependents,
                                         inst_file_info_t(child_name,
                                           parent_file_info_t(file_info),
                                             derive_options(child_name), child_type));
                  fclose(source_f);
                }
            }
        }
       }
        break;

      case F_C            :
        {
          INT  child_type = F_UNKNOWN, pos;
          BOOL found_reference = FALSE;
          char reference[MAX_FILE_ID_SIZE];

          while (((*line == ' ') || (*line == '\t')) && (*line))
            line++;
          if (*line == '#')
            {
              while (((*line == ' ') || (*line == '\t')) && (*line))
                line++;
              if (!strncmp(line, STR_include, strlen(STR_include)))
                {
                  child_type = F_C;
                  line     += strlen(STR_include);
                }
              if (child_type != F_UNKNOWN)
                {
                  while (((*line == ' ') || (*line == '\t')) && (*line))
                    line++;
                  if ((*line == '"') || (*line == '<'))
                    {
                      pos = 0;
                      if(*line == '"')
                        {
                          line++;
                          while((*line != '"') && (*line))
                            {
                              reference[pos++] = *line;
                              line++;
                            }
                          if(*line == '"')
                            {
                              reference[pos] = '\0';
                              found_reference = TRUE;
                            }
                          else warning_on_line("incomplete compiler directive\n", source_name, line_no);
                        }
                      else
                        {
                          line++;
                          while((*line != '>') && (*line))
                            {
                              reference[pos++] = *line;
                              line++;
                            }
                          if(*line == '>')
                            {
                              reference[pos] = '\0';
                              found_reference = TRUE;
                            }
                          else warning_on_line("incomplete compiler directive\n", source_name, line_no);
                        }
                    }
                  else warning_on_line("incomplete compiler directive\n",
                                        source_name, line_no);
                }
            }
          if (found_reference)
            {
              char *child_name;
              file_info_t *child_file_info;
              char actual_name[MAX_FILE_ID_SIZE];
               FILE *source_f;
            
              child_name = my_allocate((strlen(reference)+1) * sizeof(char));
              strcpy(child_name, reference);
              child_name[strlen(reference)] = '\0';
              source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
              if(source_f == NULL)
                {
                   char message[MAX_LINE_LEN];
                   message[0] = '\0';
                
                   strcat(message, "\"");
                   strcat(message, reference);
                   strcat(message, "\" does not exist for #include directive\n");
                   warning_on_line(message, source_name, line_no);
                }
              else
                {
                  child_file_info = add_dependent_info_t(dependents,
                                         inst_file_info_t(child_name,
                                           parent_file_info_t(file_info),
                                             derive_options(child_name), child_type));
                  fclose(source_f);
                }
            }
        }
        break;
      case F_CFS          :
      case F_PGM          :
        {
          INT  child_type = F_UNKNOWN, pos;
          BOOL found_reference = FALSE;
          char reference[MAX_FILE_ID_SIZE];
          INT  reference_file_type;
          while (((*line == ' ') || (*line == '\t')) && (*line))
            line++;
          if (*line == '#')
            {
              while (((*line == ' ') || (*line == '\t')) && (*line))
                line++;
              if (!strncmp(line, STR_include, strlen(STR_include)) &&
                   (type_file_info_t(file_info) == F_CFS))
                {
                  child_type = F_PGM;
                  line     += strlen(STR_include);
                }
              if (!strncmp(line, STR_INCLUDE, strlen(STR_INCLUDE)) &&
                   (type_file_info_t(file_info) == F_PGM))
                {
                  child_type = F_PGM;
                  line     += strlen(STR_INCLUDE);
                }
              if (!strncmp(line, STR_USE, strlen(STR_USE)) &&
                   (type_file_info_t(file_info) == F_PGM))
                {
                  child_type = F_CXX;
                  line     += strlen(STR_USE);
                }
              if (child_type != F_UNKNOWN)
                {
                  while (((*line == ' ') || (*line == '\t')) && (*line))
                    line++;
                  if (*line == '"')
                    {
                      pos = 0;
                      line++;
                      while((*line != '"') && (*line))
                        {
                          reference[pos++] = *line;
                          line++;
                        }
                      if(*line == '"')
                        {
                          reference[pos] = '\0';
                          found_reference = TRUE;
                        }
                      else warning_on_line("incomplete compiler directive\n", source_name, line_no);
                    }
                  else warning_on_line("incomplete compiler directive\n",
                                        source_name, line_no);
                }
              if (found_reference)
                {
                  if(child_type == F_PGM)
                    {
                      if(type_file_info_t(file_info) == F_CFS)
                        {
                          child_type = F_CFS;
                          /* if there is no extension */
                          if(!file_extension(reference))
                             strcat(reference, EXT_CFS);
                        }
                      else
                        {
                          child_type = F_PGM;
                          /* if there is no extension */
                          if(!file_extension(reference))
                             strcat(reference, EXT_PGM);
                        }
                    }
                  if(file_type(reference) == F_CXX)
                    {
                      if(!mixed_language_program)
                        {
                          ;
                        }
                      else
                        {
                          FILE *source_f;
                          char  *child_name;
                          char actual_name[MAX_FILE_ID_SIZE];
                  
                          child_name = derive_child(reference, EXT_LNK);
                          source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
                          if(source_f != NULL)
                            {
                              fclose(source_f);
                              child_type = F_CCXX;
                            }
                        }
                    }
                  reference_file_type = file_type(reference);
                  switch(reference_file_type)
                    {
                      case F_LIB          :
                        if((child_type == F_OCC) || (child_type == F_PGM))
                          warning_on_line("#INCLUDE may not reference a library\n",
                                          source_name, line_no);
                        if(child_type == F_CFS)
                          warning_on_line("#include may not reference a library\n",
                                          source_name, line_no);
                        child_type = F_LIB;
                        break;
                      case F_SC           :
                      case F_TXX          :
                        if((child_type == F_OCC) || (child_type == F_PGM) ||
                           (child_type == F_CFS))
                          warning_on_line("#INCLUDE may not reference binary files\n",
                                    source_name, line_no);
                        break;
                      case F_OCC          :
                      case F_PGM          :
                        if((child_type == F_SC) || (child_type == F_TXX))
                          warning_on_line("#SC, #USE may not reference source files\n",
                                        source_name, line_no);
                        break;
                      case F_CXX          :
                        if((child_type == F_OCC) || (child_type == F_PGM) ||
                           (child_type == F_CFS))
                          warning_on_line("#INCLUDE may not reference binary files\n",
                                    source_name, line_no);
                        break;
                      case F_LBB          :
                      case F_BXX          :
                      case F_BTL          :
                      case F_LBU          :
                      case F_LXX          :
                      case F_SC_AND_LIB   :
                      case F_UNKNOWN      :
                      case F_USED_LIBRARY :
                      case F_IMPORT   :
                        {
                           char message[MAX_LINE_LEN];
                           message[0] = '\0';
                      
                           strcat(message, "\"");
                           strcat(message, reference);
                           strcat(message, "\" unknown/illegal file reference\n");
                           warning_on_line(message, source_name, line_no);
                        }
                        break;
                    }
                  if(reference_file_type == F_UNKNOWN)
                    child_type = F_UNKNOWN;
                }
            }
          else
            {
              if (!strncmp(line, STR_use, strlen(STR_use)))
                {
                  child_type = F_CXX;
                  line     += strlen(STR_use);
                }
              if (child_type != F_UNKNOWN)
                {
                  while (((*line == ' ') || (*line == '\t')) && (*line))
                    line++;
                  if (*line == '"')
                    {
                      pos = 0;
                      line++;
                      while((*line != '"') && (*line))
                        {
                          reference[pos++] = *line;
                          line++;
                        }
                      if(*line == '"')
                        {
                          reference[pos] = '\0';
                          found_reference = TRUE;
                        }
                      else warning_on_line("incomplete 'use' directive\n", source_name, line_no);
                    }
                  else warning_on_line("incomplete 'use' directive\n",
                                        source_name, line_no);
                }
              if (found_reference)
                {
                  if(file_type(reference) == F_CXX)
                    {
                      if(!mixed_language_program)
                        {
                          ;
                        }
                      else
                        {
                          FILE *source_f;
                          char  *child_name;
                          char actual_name[MAX_FILE_ID_SIZE];
                  
                          child_name = derive_child(reference, EXT_LNK);
                          source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
                          if(source_f != NULL)
                            {
                              fclose(source_f);
                              child_type = F_CCXX;
                            }
                        }
                    }
                  reference_file_type = file_type(reference);
                  switch(reference_file_type)
                    {
                      case F_LIB          :
                        if((child_type == F_OCC) || (child_type == F_PGM))
                          warning_on_line("#INCLUDE may not reference a library\n",
                                          source_name, line_no);
                        if(child_type == F_CFS)
                          warning_on_line("#include may not reference a library\n",
                                          source_name, line_no);
                        child_type = F_LIB;
                        break;
                      case F_SC           :
                      case F_TXX          :
                        if((child_type == F_OCC) || (child_type == F_PGM) ||
                           (child_type == F_CFS))
                          warning_on_line("#INCLUDE may not reference binary files\n",
                                    source_name, line_no);
                        break;
                      case F_OCC          :
                      case F_PGM          :
                        if((child_type == F_SC) || (child_type == F_TXX))
                          warning_on_line("#SC, #USE may not reference source files\n",
                                        source_name, line_no);
                        break;
                      case F_CXX          :
                        if((child_type == F_OCC) || (child_type == F_PGM) ||
                           (child_type == F_CFS))
                          warning_on_line("#INCLUDE may not reference binary files\n",
                                    source_name, line_no);
                        break;
                      case F_LBB          :
                      case F_BXX          :
                      case F_BTL          :
                      case F_LBU          :
                      case F_LXX          :
                      case F_SC_AND_LIB   :
                      case F_UNKNOWN      :
                      case F_USED_LIBRARY :
                      case F_IMPORT   :
                        {
                           char message[MAX_LINE_LEN];
                           message[0] = '\0';
                      
                           strcat(message, "\"");
                           strcat(message, reference);
                           strcat(message, "\" unknown/illegal file reference\n");
                           warning_on_line(message, source_name, line_no);
                        }
                        break;
                    }
                  if(reference_file_type == F_UNKNOWN)
                    child_type = F_UNKNOWN;
                }
            }
          if (found_reference)
            {
              char *child_name;
              file_info_t *child_file_info;
            
              child_name = my_allocate((strlen(reference)+1) * sizeof(char));
              strcpy(child_name, reference);
              child_name[strlen(reference)] = '\0';
              child_file_info = add_dependent_info_t(dependents,
                                     inst_file_info_t(child_name,
                                       parent_file_info_t(file_info),
                                         derive_options(child_name), child_type));
            }
        }
        break;
      default             :
        error("Jumped off case loop in process_line - Remove before release",
               source_name);
        break;
    }
}

/*****************************************************************************
 *
 *  Procedure    : search_for_dependents
 *
 *  Parameters   : the dependent info structure and the file infor
 *                 of the file to be searched
 *
 *  Return value : None
 *
 *  Function     : Open the given source file to search it for references
 *                 the file type of the source file determines how the
 *                 references are parsed. Each references is added to the
 *                 dependent info structure in the order it is found.
 *                 The file types which are searched using this technique are
 *                 .occ, .lbu, .pgm, .lbb
 *
 *****************************************************************************/

PRIVATE void search_for_dependents(dependents, file_info)
dependent_info_t *dependents;
file_info_t      *file_info;
{
  FILE *source_f;
  char *source_name = name_file_info_t(file_info);
  char actual_name[MAX_FILE_ID_SIZE];

  source_f = popen_read(source_name, PATHNAME, actual_name, TEXT_MODE);
  if (source_f != NULL)
    {
      char line[MAX_LINE_LEN];
      INT line_no = 1;
    
      if(information)
          PRINT(stdout, "searching \"%s\" {%s}\n",
                  name_file_info_t(file_info), actual_name);
      
      while(!feof(source_f))
        {
          fgets(line, MAX_LINE_LEN, source_f);
          process_line(line, dependents, file_info, line_no++);
        }
    
      if(ferror(source_f))
        warning_on_line("error whilst reading\n", source_name, line_no);
      fclose(source_f);
    }
  else warning("source file does not exist\n", source_name);
}

/*****************************************************************************
 *
 *  Procedure    : derive_dependent_info_t
 *
 *  Parameters   : the file entry of the file to be operated on.
 *
 *  Return value : a dependency structure of the file
 *
 *  Function     : Uses the file type of the file to decide whether either to
 *                 search the file for references or to generate the dependent
 *                 file from the filename using the extension rules of the
 *                 occam toolset
 *
 *****************************************************************************/

PUBLIC dependent_info_t *derive_dependent_info_t(file_info)
file_info_t *file_info;
{
  char *parent_name, *child_name, actual_name[MAX_FILE_ID_SIZE];
  char file_type, error_mode, processor_type;
  file_info_t *child_file_info;
  dependent_info_t *dependents;
  FILE *source_f;

  dependents = create_dependent_info_t ();

  switch(type_file_info_t(file_info))
    {
      case F_SC_AND_LIB   :
      case F_USED_LIBRARY :
      case F_IMPORT       :
      case F_UNKNOWN      :
        /* do nothing */
        break;
      case F_LBB          :
      case F_OCC          :
      case F_PGM          :
      case F_CFS          :
      case F_LBU          :
      case F_LNK          :
      case F_C            :
      case F_FORTRAN      :
        search_for_dependents(dependents, file_info);
        break;
      case F_RXX          :
      case F_BXX          :
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_CXX);
        if(!mixed_language_program)
          {
            child_name = derive_child(parent_name, EXT_CXX);
            if(parse_extension(parent_name, &file_type, &error_mode, &processor_type))
              if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
                set_extension(child_name, CHAR_CXX, error_mode, processor_type);
            child_file_info = add_dependent_info_t(dependents,
                inst_file_info_t(child_name, parent_name,
                                  derive_options(child_name), F_CXX));
          }
        else
          {
            child_name = derive_child(parent_name, EXT_LNK);
            source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
            if(source_f != NULL)
              {
                fclose(source_f);
                child_name = derive_child(parent_name, EXT_CXX);
                if(parse_extension(parent_name, &file_type, &error_mode, &processor_type))
                  if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
                    set_extension(child_name, CHAR_CXX, error_mode, processor_type);
                child_file_info = add_dependent_info_t(dependents,
                    inst_file_info_t(child_name, parent_name,
                                      derive_options(child_name), F_CCXX));
              }
            else
              {
                child_name = derive_child(parent_name, EXT_CXX);
                if(parse_extension(parent_name, &file_type, &error_mode, &processor_type))
                  if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
                    set_extension(child_name, CHAR_CXX, error_mode, processor_type);
                child_file_info = add_dependent_info_t(dependents,
                    inst_file_info_t(child_name, parent_name,
                                      derive_options(child_name), F_CXX));
              }
          }
        break;
      case F_LIB          :
        {
          FILE *child_stream;
          char actual_name[MAX_FILE_ID_SIZE];
      
          parent_name = name_file_info_t(file_info);
          child_name = derive_child(parent_name, EXT_LBB);
          child_stream = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
          if(child_stream != NULL)
            {
              fclose(child_stream);
              child_file_info = add_dependent_info_t(dependents,
                   inst_file_info_t(child_name, parent_name, "", F_LBB));
            }
          else
            {
              child_name = derive_child(parent_name, EXT_LBU);
              child_stream = popen_read(child_name, PATHNAME, actual_name,
                                        TEXT_MODE);
              if(child_stream != NULL)
               {
                 fclose(child_stream);
                 child_file_info = add_dependent_info_t(dependents,
                     inst_file_info_t(child_name, parent_name, "", F_LBU));
               }
            }
        }
        break;
      case F_SC          :
      case F_TXX          :
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_OCC);
        child_file_info = add_dependent_info_t(dependents,
            inst_file_info_t(child_name, parent_name, "", F_OCC));
        break;
      case F_CTXX         :
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_C);
        child_file_info = add_dependent_info_t(dependents,
            inst_file_info_t(child_name, parent_name, "", F_C));
        break;
      case F_FTXX:
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_FORTRAN);
        child_file_info = add_dependent_info_t(dependents,
            inst_file_info_t(child_name, parent_name, "", F_FORTRAN));
        break;
        
      case F_CXX          :
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_LXX);
        if(parse_extension(parent_name, &file_type, &error_mode, &processor_type))
          if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
             set_extension(child_name, CHAR_LXX, error_mode, processor_type);
        child_file_info = add_dependent_info_t(dependents,
            inst_file_info_t(child_name, parent_name,
                              derive_options(child_name), F_LXX));
        break;
      case F_CCXX          :
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_LNK);
        child_file_info = add_dependent_info_t(dependents,
            inst_file_info_t(child_name, parent_name,
                              derive_options(child_name), F_LNK));
        break;
      case F_LXX          :
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_OCC);
        child_name = derive_child(parent_name, EXT_TXX);
        if(parse_extension(parent_name, &file_type, &error_mode, &processor_type))
          if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
            set_extension(child_name, CHAR_TXX, error_mode, processor_type);
        child_file_info = add_dependent_info_t(dependents,
            inst_file_info_t(child_name, parent_name,
                              derive_options(child_name), F_SC));
        break;
      case F_BTL           :
        parent_name = name_file_info_t(file_info);
        if(!mixed_language_program)
          {
            child_name = derive_child(parent_name, EXT_PGM);
            source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
            if(source_f != NULL)
              {
                fclose(source_f);
                child_name = derive_child(parent_name, EXT_CFB_OC);
                child_file_info = add_dependent_info_t(dependents,
                  inst_file_info_t(child_name, parent_name, "", F_CFB_OC));
               }
             else
               {
                 child_name = derive_child(parent_name, EXT_CFS);
                 source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
                 if(source_f != NULL)
                   {
                     fclose(source_f);
                     child_name = derive_child(parent_name, EXT_CFB);
                     child_file_info = add_dependent_info_t(dependents,
                        inst_file_info_t(child_name, parent_name, "", F_CFB));
                   }
                 else
                   {
                     child_name = derive_child(parent_name, EXT_CFB_OC);
                     child_file_info = add_dependent_info_t(dependents,
                       inst_file_info_t(child_name, parent_name, "", F_CFB_OC));
                   }
                }
          }
        else
          {
            child_name = derive_child(parent_name, EXT_CFS);
            source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
            if(source_f != NULL)
              {
                fclose(source_f);
                child_name = derive_child(parent_name, EXT_CFB);
                child_file_info = add_dependent_info_t(dependents,
                             inst_file_info_t(child_name, parent_name, "", F_CFB));
              }
            else
              {
                child_name = derive_child(parent_name, EXT_PGM);
                source_f = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
                if(source_f != NULL)
                  {
                    fclose(source_f);
                    child_name = derive_child(parent_name, EXT_CFB_OC);
                    child_file_info = add_dependent_info_t(dependents,
                         inst_file_info_t(child_name, parent_name, "", F_CFB_OC));
                  }
                else
                  {
                    child_name = derive_child(parent_name, EXT_CFB);
                    child_file_info = add_dependent_info_t(dependents,
                               inst_file_info_t(child_name, parent_name, "", F_CFB));
                  }
              }
          }
        break;
      case F_CFB           :
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_CFS);
        child_file_info = add_dependent_info_t(dependents,
                       inst_file_info_t(child_name, parent_name, "", F_CFS));
        break;
      case F_CFB_OC         :
        parent_name = name_file_info_t(file_info);
        child_name = derive_child(parent_name, EXT_PGM);
        child_file_info = add_dependent_info_t(dependents,
              inst_file_info_t(child_name, parent_name, "", F_PGM));
        break;
      default             :
        error("Jumped off case loop deriving dependents",
                name_file_info_t(file_info));
        break;
    }
  return(dependents);
}


/*****************************************************************************
 *
 *  Procedure    : add_map_file_option
 *
 *  Parameters   : string to add option to
 *                 the file entry for a file
 *                 the option string to include
 *                 the extension modification
 *
 *  Return value : void
 *
 *  Function     : adds the map file option to the action string
 *                 adds the file name as its operand
 *                 then modifies the extension appropriately
 *
 *  History      : ahp:  25/08/92:  created
 *****************************************************************************/

PRIVATE void add_map_file_option (action_string, file_entry, option, extension)
char * action_string, * option, * extension;
file_entry_t * file_entry;
{
  int i;

  if(ESCAPE_CHAR == '/')
    strcat(action_string, " /");
  else
    strcat(action_string, " -");
  strcat (action_string, option);
  strcat (action_string, " ");
  strcat (action_string, realname_file_entry_t(file_entry));
  i = strlen (action_string);
  while (action_string[i] != '.') i -= 1;
  strncpy (action_string+(i+1), extension, strlen(extension));
  return;
}

/*****************************************************************************
 *
 *  Procedure    : derive_action_t
 *
 *  Parameters   : the file entry for a file
 *
 *  Return value : an action structure
 *
 *  Function     : this uses the file type of the file to determine what
 *                 if any actions are required to update the file.
 *
 *****************************************************************************/

PUBLIC action_t *derive_action_t(file_entry)
file_entry_t *file_entry;
{
  INT action_size;
  char *action_str;
  action_entry_t *action_entry;
  action_t *actions;
  char source_filename_str[MAX_FILE_ID_SIZE];
  char file_type, error_mode, processor_type;

  actions = create_action_t ();

  switch(type_file_entry_t(file_entry))
    {
      case F_OCC          :
      case F_PGM          :
      case F_CFS          :
      case F_LBB          :
      case F_LBU          :
      case F_LXX          :
      case F_IMPORT       :
      case F_USED_LIBRARY :
      case F_SC_AND_LIB   :
      case F_UNKNOWN      :
      case F_C            :
      case F_FORTRAN      :
      case F_LNK          :
        break;
      case F_LIB          :
        {
          FILE *child_stream;
          char *parent_name, *child_name;
          char actual_name[MAX_FILE_ID_SIZE];
      
          parent_name = name_file_entry_t(file_entry);
          child_name = derive_child(parent_name, EXT_LBB);
          child_stream = popen_read(child_name, PATHNAME, actual_name, TEXT_MODE);
          if(child_stream != NULL)
            {
              fclose(child_stream);
              /* $(ILIBR) /f file /o output $(LIBOPT) */
              action_size  = strlen(LIBRARIAN_CALL) + 12 + strlen(child_name)
                             + strlen(realname_file_entry_t(file_entry))
                             + strlen(LIB_OPTIONS_CALL);
              action_str   = my_allocate ((action_size+1) * sizeof(char));
              if (action_str != NULL)
                {
                  strcpy(action_str, LIBRARIAN_CALL);
                  if(ESCAPE_CHAR == '/')
                    strcat(action_str, " /f ");
                  else
                    strcat(action_str, " -f ");
                  strcat(action_str, child_name);
                  strcat(action_str, " ");
                  if(ESCAPE_CHAR == '/')
                    strcat(action_str, " /o ");
                  else
                    strcat(action_str, " -o ");
                  strcat(action_str, realname_file_entry_t(file_entry));
                  strcat(action_str, " ");
                  strcat(action_str, LIB_OPTIONS_CALL);
                  action_str[action_size] = '\0';
                  action_entry = append_action_t(actions, inst_action_entry_t(action_str));
                }
            }
        }
        break;
      case F_TXX          :
      case F_SC           :
        /* format of command is OCCAM filename options */
        remove_extension(source_filename_str, name_file_entry_t(file_entry));
        action_size  = strlen(OCCAM_CALL) + 20 + strlen(source_filename_str)
                        + strlen(realname_file_entry_t(file_entry))
                        + strlen(realname_file_entry_t(file_entry)) + 4 /* BAS 09/03/92 */
                        + strlen(OCCAM_OPTIONS_CALL);
        action_str   = my_allocate ((action_size+1) * sizeof(char));
        if (action_str != NULL)
          {
            strcpy(action_str, OCCAM_CALL);
            strcat(action_str, " ");
            strcat(action_str, source_filename_str);
            strcat(action_str, " ");
            strcat(action_str, options_file_entry_t(file_entry));
            if(!debug_info)
               {
                 if(ESCAPE_CHAR == '/')
                   strcat(action_str, " /d");
                 else
                   strcat(action_str, " -d");
               }
               
            if(!interactive_debugging)
               {
                 if(ESCAPE_CHAR == '/')
                   strcat(action_str, " /y");
                 else
                   strcat(action_str, " -y");
               }

            if(imap_output)
              add_map_file_option (action_str, file_entry, "p", "m");

            if(ESCAPE_CHAR == '/')
              strcat(action_str, " /o ");
            else
              strcat(action_str, " -o ");
            strcat(action_str, realname_file_entry_t(file_entry));
            strcat(action_str, " ");
            strcat(action_str, OCCAM_OPTIONS_CALL);
            action_str[action_size] = '\0';
            action_entry = append_action_t(actions, inst_action_entry_t(action_str));
          }
        break;
      case F_CTXX         :
        /* format of command is CC filename options */
        strcpy(source_filename_str,
                 derive_child(name_file_entry_t(file_entry), EXT_C));
        action_size  = strlen(C_CALL) + 12 + strlen(source_filename_str)
                        + strlen(realname_file_entry_t(file_entry))
                        + strlen(realname_file_entry_t(file_entry)) + 4 /* ahp 25/08/92 */
                        + strlen(options_file_entry_t(file_entry))
                        + strlen(C_OPTIONS_CALL);
        action_str   = my_allocate ((action_size+1) * sizeof(char));
        if (action_str != NULL)
          {
            strcpy(action_str, C_CALL);
            strcat(action_str, " ");
            strcat(action_str, source_filename_str);
            if(debug_info)
              {
                if(ESCAPE_CHAR == '/')
                  strcat(action_str, " /g");
                else
                  strcat(action_str, " -g");
              }
            strcat(action_str, " ");
            strncat(action_str, options_file_entry_t(file_entry),3);

            if(imap_output)
              add_map_file_option (action_str, file_entry, "p", "m");

            if(ESCAPE_CHAR == '/')
              strcat(action_str, " /o ");
            else
              strcat(action_str, " -o ");
            strcat(action_str, realname_file_entry_t(file_entry));
            strcat(action_str, " ");
            strcat(action_str, C_OPTIONS_CALL);
            action_str[action_size] = '\0';
            action_entry = append_action_t(actions, inst_action_entry_t(action_str));
          }
        break;
        
      case F_FTXX         :
        /* format of command is if77 filename options */
        strcpy(source_filename_str,
                 derive_child(name_file_entry_t(file_entry), EXT_FORTRAN));
        action_size  = strlen(FORTRAN_CALL) + 12 + strlen(source_filename_str)
                        + strlen(realname_file_entry_t(file_entry))
                        + strlen(realname_file_entry_t(file_entry)) + 4 /* BAS 09/03/92 */
                        + strlen(options_file_entry_t(file_entry))
                        + strlen(FORTRAN_OPTIONS_CALL);
        action_str   = my_allocate ((action_size+1) * sizeof(char));
        if (action_str != NULL)
          {
            strcpy(action_str, FORTRAN_CALL);
            strcat(action_str, " ");
            strcat(action_str, source_filename_str);
            if(debug_info)
              {
                if(ESCAPE_CHAR == '/')
                  strcat(action_str, " /g");
                else
                  strcat(action_str, " -g");
              }
            strcat(action_str, " ");
            /* The 3 prevents anything other than -ta being put out !!
               This is because sometimes it was derived from what it thought
               was an occam file, and hence has error mode info in it*/
            strncat(action_str, options_file_entry_t(file_entry),3);

            if(imap_output)
              add_map_file_option (action_str, file_entry, "p", "m");

            if(ESCAPE_CHAR == '/')
              strcat(action_str, " /o ");
            else
              strcat(action_str, " -o ");
            strcat(action_str, realname_file_entry_t(file_entry));
            strcat(action_str, " ");
            strcat(action_str, FORTRAN_OPTIONS_CALL);
            action_str[action_size] = '\0';
            action_entry = append_action_t(actions, inst_action_entry_t(action_str));
          }
        break;
        
      case F_CXX          :
        /* format of command is LINK @filename */
        {
          char file_type, error_mode, processor_type;
          char *indirect_filename_str;
      
          indirect_filename_str = derive_child(name_file_entry_t(file_entry), EXT_LXX);
          if(parse_extension(name_file_entry_t(file_entry),
                             &file_type, &error_mode, &processor_type))
            if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
               set_extension(indirect_filename_str,
                             CHAR_LXX, error_mode, processor_type);
          action_size  = strlen(LINKER_CALL) + 16 + strlen(indirect_filename_str) +
                         strlen(realname_file_entry_t(file_entry)) +
                         strlen(realname_file_entry_t(file_entry)) + 5 + /* BAS 09/03/92 */
                         strlen(options_file_entry_t(file_entry))  +
                         strlen(LINK_OPTIONS_CALL);
          action_str   = my_allocate ((action_size+1) * sizeof(char));
          if (action_str != NULL)
            {
              strcpy(action_str, LINKER_CALL);
              if(ESCAPE_CHAR == '/')
                strcat(action_str, " /f ");
              else
                strcat(action_str, " -f ");
              strcat(action_str, indirect_filename_str);
              strcat(action_str, " ");
              strcat(action_str, options_file_entry_t(file_entry));

              if(!interactive_debugging)
                 {
                   if(ESCAPE_CHAR == '/')
                     strcat(action_str, " /y");
                   else
                     strcat(action_str, " -y");
                 }

              if(imap_output)
                add_map_file_option (action_str, file_entry, "mo", "d");

              if(ESCAPE_CHAR == '/')
                strcat(action_str, " /o ");
              else
                strcat(action_str, " -o ");
              strcat(action_str, realname_file_entry_t(file_entry));
              strcat(action_str, " ");
              strcat(action_str, LINK_OPTIONS_CALL);
              action_str[action_size] = '\0';
              action_entry = append_action_t(actions, inst_action_entry_t(action_str));
            }
        }
        break;
      case F_CCXX          :
        /* format of command is LINK @filename */
        {
          char file_type, error_mode, processor_type;
          char *indirect_filename_str;
      
          indirect_filename_str = derive_child(name_file_entry_t(file_entry), EXT_LNK);
          action_size  = strlen(LINKER_CALL) + 16 + strlen(indirect_filename_str)
                         + strlen(realname_file_entry_t(file_entry))
                         + strlen(realname_file_entry_t(file_entry)) + 5 /* ahp 25/08/92 */
                         + strlen(options_file_entry_t(file_entry))
                         + strlen(LINK_OPTIONS_CALL);
          action_str   = my_allocate ((action_size+1) * sizeof(char));
          if (action_str != NULL)
            {
              strcpy(action_str, LINKER_CALL);
              if(ESCAPE_CHAR == '/')
                strcat(action_str, " /f ");
              else
                strcat(action_str, " -f ");
              strcat(action_str, indirect_filename_str);
              strcat(action_str, " ");
              strcat(action_str, options_file_entry_t(file_entry));

              if(imap_output)
                add_map_file_option (action_str, file_entry, "mo", "d");

              if(ESCAPE_CHAR == '/')
                strcat(action_str, " /o ");
              else
                strcat(action_str, " -o ");
              strcat(action_str, realname_file_entry_t(file_entry));
              if(!interactive_debugging)
                 {
                   if(ESCAPE_CHAR == '/')
                     strcat(action_str, " /y");
                   else
                     strcat(action_str, " -y");
                 }
              strcat(action_str, " ");
              strcat(action_str, LINK_OPTIONS_CALL);
              action_str[action_size] = '\0';
              action_entry = append_action_t(actions, inst_action_entry_t(action_str));
            }
        }
        break;
      case F_CFB          :
        /* format of command is CONFIG filename */
        strcpy(source_filename_str, derive_child(name_file_entry_t(file_entry),
               EXT_CFS));
        action_size  = strlen(CONFIG_CALL) + 15 + strlen(source_filename_str) +
                       strlen(realname_file_entry_t(file_entry)) +
                       strlen(CONF_OPTIONS_CALL);
        action_str   = my_allocate ((action_size+1) * sizeof(char));
        if (action_str != NULL)
          {
            strcpy(action_str, CONFIG_CALL);
            strcat(action_str, " ");
            strcat(action_str, source_filename_str);
            if(debug_info)
              {
                if(ESCAPE_CHAR == '/')
                  strcat(action_str, " /g");
                else
                  strcat(action_str, " -g");
              }
              
            if(ESCAPE_CHAR == '/')
              strcat(action_str, " /o ");
            else
              strcat(action_str, " -o ");

            strcat(action_str, realname_file_entry_t(file_entry));
            strcat(action_str, " ");
            strcat(action_str, CONF_OPTIONS_CALL);
            action_entry = append_action_t(actions, inst_action_entry_t(action_str));
          }
        break;
      case F_CFB_OC        :
        /* format of command is CONFIG filename */
        strcpy(source_filename_str, derive_child(name_file_entry_t(file_entry),
               EXT_PGM));
        action_size  = strlen(OCONFIG_CALL) + 15 + strlen(source_filename_str) +
                       strlen(realname_file_entry_t(file_entry)) +
                       strlen(realname_file_entry_t(file_entry)) + 4 + /* BAS 09/03/92 */
                       strlen(OCONF_OPTIONS_CALL);
        action_str   = my_allocate ((action_size+1) * sizeof(char));
        if (action_str != NULL)
          {
            strcpy(action_str, OCONFIG_CALL);
            strcat(action_str, " ");
            strcat(action_str, source_filename_str);
            
            /* Added by DJM 5/2/91 */
            if(!interactive_debugging)
               {
                 if(ESCAPE_CHAR == '/')
                   strcat(action_str, " /y");
                 else
                   strcat(action_str, " -y");
               }
            
            if(ESCAPE_CHAR == '/')
              strcat(action_str, " /o ");
            else
              strcat(action_str, " -o ");
            strcat(action_str, realname_file_entry_t(file_entry));
            strcat(action_str, " ");
            strcat(action_str, OCONF_OPTIONS_CALL);
            action_entry = append_action_t(actions, inst_action_entry_t(action_str));
          }
        break;
      case F_BTL          :
        /* format of command is COLLECT filename */
        strcpy(source_filename_str, derive_child(name_file_entry_t(file_entry),
               EXT_CFB));
        action_size  = strlen(COLLECT_CALL) + 12 + strlen(source_filename_str) +
                       strlen(realname_file_entry_t(file_entry)) +
                       strlen(realname_file_entry_t(file_entry)) + 4 + /* BAS 09/03/92 */
                       strlen(COLLECT_OPTIONS_CALL);
        action_str   = my_allocate ((action_size+1) * sizeof(char));
        if (action_str != NULL)
          {
            strcpy(action_str, COLLECT_CALL);
            strcat(action_str, " ");
            strcat(action_str, source_filename_str);

            if(imap_output)
              add_map_file_option (action_str, file_entry, "p", "map");

            if(ESCAPE_CHAR == '/')
              strcat(action_str, " /o ");
            else
              strcat(action_str, " -o ");
            strcat(action_str, realname_file_entry_t(file_entry));
            strcat(action_str, " ");
            strcat(action_str, COLLECT_OPTIONS_CALL);
            action_entry = append_action_t(actions, inst_action_entry_t(action_str));
          }
        break;
      case F_BXX          :
      case F_RXX          :
        {
          /* format of command is ADDBOOT filename */
          char file_type, error_mode, processor_type;
          char *indirect_filename_str;
      
          indirect_filename_str = derive_child(name_file_entry_t(file_entry), EXT_CXX);
          if(parse_extension(name_file_entry_t(file_entry),
                             &file_type, &error_mode, &processor_type))
            if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
               set_extension(indirect_filename_str,
                             CHAR_CXX, error_mode, processor_type);
          action_size  = strlen(COLLECT_CALL) + 15
                           + strlen(indirect_filename_str)
                           + strlen(indirect_filename_str) + 4 /* BAS 09/03/92 */
                           + strlen(realname_file_entry_t(file_entry))
                           + strlen(COLLECT_OPTIONS_CALL);
          action_str   = my_allocate ((action_size+1) * sizeof(char));
          if (action_str != NULL)
            {
              strcpy(action_str, COLLECT_CALL);
              strcat(action_str, " ");
              strcat(action_str, indirect_filename_str);
              if(type_file_entry_t(file_entry) == F_RXX)
                {
                  if(ESCAPE_CHAR == '/')
                    strcat(action_str, " /t /k ");
                  else
                    strcat(action_str, " -t -k ");
                }
              else
                {
                  if(ESCAPE_CHAR == '/')
                    strcat(action_str, " /t ");
                  else
                    strcat(action_str, " -t ");
                }
                            
              /* Added by DJM 5/2/91 */
              if(!interactive_debugging &&
                 !(processor_type=='a' || processor_type=='b'))
               {
                 if(ESCAPE_CHAR == '/')
                   strcat(action_str, " /y");
                 else
                   strcat(action_str, " -y");
               }
            
              if(imap_output)
                add_map_file_option (action_str, file_entry, "p", "map");

              if(ESCAPE_CHAR == '/')
                strcat(action_str, " /o ");
              else
                strcat(action_str, " -o ");
              strcat(action_str, realname_file_entry_t(file_entry));
              strcat(action_str, " ");
              strcat(action_str, COLLECT_OPTIONS_CALL);
              action_entry = append_action_t(actions, inst_action_entry_t(action_str));
            }
        }
        break;
      default             :
        error("Jumped off case loop deriving actions",
               name_file_entry_t(file_entry));
        break;
    }

  return(actions);
}

/*****************************************************************************
 *
 *  Procedure    : derive_options
 *
 *  Parameters   : the file name
 *
 *  Return value : a string
 *
 *  Function     : uses the extension rules of the system to classify the file
 *                 and hence derive the compiler options which are necessary
 *                 to generate the particular extension.
 *
 *****************************************************************************/

PUBLIC char *derive_options (filename)
char *filename;
{
  char *options;

  switch(file_type(filename))
    {
       case F_SC_AND_LIB   :
       case F_UNKNOWN      :
       case F_USED_LIBRARY :
       case F_IMPORT       :
       case F_LBU          :
       case F_LBB          :
       case F_OCC          :
       case F_PGM          :
       case F_CFS          :
       case F_LIB          :
       case F_BTL          :
       case F_BXX          :
       case F_LXX          :
       case F_RXX          :
       case F_C            :
       case F_FORTRAN      :
       case F_LNK          :
         options = my_allocate(sizeof(char));
         options[0] = '\0';
         break;
       case F_SC           :
       case F_TXX          :
       case F_CXX          :
         {
           char file_type, error_mode, processor_type;
       
           parse_extension(filename, &file_type, &error_mode, &processor_type);
       
           options = my_allocate((strlen(COMPILER_OPTIONS)+1) * sizeof(char));
           strcpy(options, COMPILER_OPTIONS);
           options[strlen(COMPILER_OPTIONS)] = '\0';
           options[COMPILER_OPTIONS_TYPE] = processor_type;
           options[COMPILER_OPTIONS_MODE] = error_mode;
         }
         break;
       case F_CTXX         :
         {
           char file_type, error_mode, processor_type;
       
           parse_extension(filename, &file_type, &error_mode, &processor_type);
       
           options = my_allocate((strlen(C_OPTIONS)+1) * sizeof(char));
           strcpy(options, C_OPTIONS);
           options[strlen(C_OPTIONS)] = '\0';
           options[C_OPTIONS_TYPE] = processor_type;
         }
         break;
       case F_FTXX         :
         {
           char file_type, error_mode, processor_type;
       
           parse_extension(filename, &file_type, &error_mode, &processor_type);
       
           options = my_allocate((strlen(FORTRAN_OPTIONS)+1) * sizeof(char));
           strcpy(options, FORTRAN_OPTIONS);
           options[strlen(FORTRAN_OPTIONS)] = '\0';
           options[FORTRAN_OPTIONS_TYPE] = processor_type;
         }
         break;         
       default             :
         error("Jumped off case loop in derive_options", filename);
         break;
    }

  return(options);
}

/*****************************************************************************
 *
 *  Procedure    : derive_cc_options
 *
 *  Parameters   : the file name
 *
 *  Return value : a string
 *
 *  Function     : uses the extension rules of the system to classify the file
 *                 and hence derive the compiler options which are necessary
 *                 to generate the particular extension.
 *                 ** this is a hack to allow the generation of the
 *                    correct options for a C compiler given that both
 *                    Occam and C generate .TXX files
 *
 *****************************************************************************/

PUBLIC char *derive_cc_options (filename)
char *filename;
{
  char *options;

  char file_type, error_mode, processor_type;

  parse_extension(filename, &file_type, &error_mode, &processor_type);

  options = my_allocate((strlen(C_OPTIONS)+1) * sizeof(char));
  strcpy(options, C_OPTIONS);
  options[strlen(C_OPTIONS)] = '\0';
  options[C_OPTIONS_TYPE] = processor_type;

  return(options);
}

PUBLIC char *derive_f77_options (filename)
char *filename;
{
  char *options;

  char file_type, error_mode, processor_type;

  parse_extension(filename, &file_type, &error_mode, &processor_type);

  options = my_allocate((strlen(FORTRAN_OPTIONS)+1) * sizeof(char));
  strcpy(options, FORTRAN_OPTIONS);
  options[strlen(FORTRAN_OPTIONS)] = '\0';
  options[FORTRAN_OPTIONS_TYPE] = processor_type;

  return(options);
}


PRIVATE void derive_name_file_entry_t(file_entry)
file_entry_t *file_entry;
{
  FILE *source_f;
  char *source_name;
  char actual_name[MAX_FILE_ID_SIZE];

  INT file_type = type_file_entry_t(file_entry);
  actual_name[0] = '\0';
  switch(file_type)
    {
      case F_LBB          :
      case F_OCC          :
      case F_PGM          :
      case F_CFS          :
      case F_LBU          :
      case F_LNK          :
      case F_C            :
      case F_FORTRAN      :
        {
          source_name = name_file_entry_t(file_entry);
          source_f = popen_read(source_name, PATHNAME, actual_name, TEXT_MODE);
          if(source_f != NULL)
            {
              fclose(source_f);
              if(strcmp(source_name, actual_name) != 0)
                {
                   char *file_name;
                   file_name = my_allocate((strlen(actual_name)+2) * sizeof(char));
                   strcpy(file_name, actual_name);
                   set_name_file_entry_t(file_entry, file_name);
                }
            }
        }
        break;
      case F_SC           :
      case F_TXX          :
      case F_CTXX         :
      case F_FTXX         :
      case F_CCXX         :
      case F_BTL          :
      case F_CFB          :
      case F_CFB_OC       :
        if(!directory_specifier(name_file_entry_t(file_entry)))
        {
          dependent_t  *dependents;
          file_entry_t *source_file_entry;
      
          dependents = dependents_file_entry_t(file_entry);
          reset_dependent_t(dependents);
          source_file_entry = next_dependent_t(dependents);
          if(source_file_entry != NULL)
            {
              source_name = name_file_entry_t(source_file_entry);
              source_f = popen_read(source_name, PATHNAME, actual_name, TEXT_MODE);
              if(source_f != NULL)
                {
                   fclose(source_f);
                   if(directory_specifier(actual_name))
                     {
                       char *child_dir, *parent_name, *new_parent_name;
          
                       child_dir   = find_directory_specifier(actual_name);
                       parent_name = name_file_entry_t(file_entry);
                       new_parent_name =
                        my_allocate((strlen(child_dir)+strlen(parent_name)+2) * sizeof(char));
                       strcpy(new_parent_name, child_dir);
                       strcat(new_parent_name, parent_name);
                       set_name_file_entry_t(file_entry, new_parent_name);
                     }
                }
            }
        }
        break;
      case F_LIB          :
        if(!directory_specifier(name_file_entry_t(file_entry)))
        {
          dependent_t  *dependents;
          file_entry_t *source_file_entry;
      
          dependents = dependents_file_entry_t(file_entry);
          reset_dependent_t(dependents);
          source_file_entry = next_dependent_t(dependents);
          if(source_file_entry != NULL)
            {
              source_name = name_file_entry_t(source_file_entry);
              source_f = popen_read(source_name, PATHNAME, actual_name, TEXT_MODE);
              if(source_f != NULL)
                {
                  fclose(source_f);
                  if(directory_specifier(actual_name))
                    {
                      char *child_dir, *parent_name, *new_parent_name;
            
                      source_f = fopen(source_name, "r");
                      if(source_f != NULL)
                        {
                          char message[MAX_LINE_LEN];
                          strcpy(message, "Library on PATH '");
                          strcat(message, actual_name);
                          strcat(message, "' also exists in the current directory");
                          warning(message, source_name);
                          fclose(source_f);
                        }
                      child_dir   = find_directory_specifier(actual_name);
                      parent_name = name_file_entry_t(file_entry);
                      new_parent_name =
                       my_allocate((strlen(child_dir)+strlen(parent_name)+2) * sizeof(char));
                      strcpy(new_parent_name, child_dir);
                      strcat(new_parent_name, parent_name);
                      set_name_file_entry_t(file_entry, new_parent_name);
                    }
                }
            }
          else
            {
               FILE *library_stream;
               char *library_name = name_file_entry_t(file_entry);
            
               library_stream = popen_read(library_name, PATHNAME, actual_name, TEXT_MODE);
               if(library_stream != NULL)
                 {
                   fclose(library_stream);
                   if((library_stream != NULL) && (actual_name != NULL))
                     {
                       char *file_name;
                       file_name = my_allocate((strlen(actual_name)+2) * sizeof(char));
                       strcpy(file_name, actual_name);
                       set_name_file_entry_t(file_entry, file_name);
                     }
                   else warning("Library without a build or usage file does not exist\n",
                                       library_name);
                 }
            }
        }
        break;
      case F_RXX          :
      case F_BXX          :
      case F_CXX          :
      case F_LXX          :
        if(!directory_specifier(name_file_entry_t(file_entry)))
        {
          source_name = derive_child(name_file_entry_t(file_entry), EXT_OCC);
          source_f = popen_read(source_name, PATHNAME, actual_name, TEXT_MODE);
          if(source_f != NULL)
            {
               fclose(source_f);
               if(directory_specifier(actual_name))
                 {
                   char *child_dir, *parent_name, *new_parent_name;
      
                   child_dir   = find_directory_specifier(actual_name);
                   parent_name = name_file_entry_t(file_entry);
                   new_parent_name =
                    my_allocate((strlen(child_dir)+strlen(parent_name)+2) * sizeof(char));
                   strcpy(new_parent_name, child_dir);
                   strcat(new_parent_name, parent_name);
                   set_name_file_entry_t(file_entry, new_parent_name);
                 }
            }
        }
        break;
      case F_USED_LIBRARY :
        if(!directory_specifier(name_file_entry_t(file_entry)))
        {
           FILE *library_stream;
           char *library_name = name_file_entry_t(file_entry);
      
           library_stream = popen_read(library_name, PATHNAME, actual_name, TEXT_MODE);
           if(library_stream != NULL)
             {
                fclose(library_stream);
                if((library_stream != NULL) && (actual_name != NULL))
                  {
                    char *file_name;
                    file_name = my_allocate((strlen(actual_name)+2) * sizeof(char));
                    strcpy(file_name, actual_name);
                    set_name_file_entry_t(file_entry, file_name);
                  }
                else warning("Library without a build or usage file does not exist\n",
                                    library_name);
             }
        }
        break;
      case F_SC_AND_LIB   :
      case F_IMPORT       :
      case F_UNKNOWN      :
        /* Have a go at generating the name anyway so that a make might work */
        {
          source_name = name_file_entry_t(file_entry);
          source_f = popen_read(source_name, PATHNAME, actual_name, TEXT_MODE);
          if(source_f != NULL)
            {
              fclose(source_f);
              if(strcmp(source_name, actual_name) != 0)
                {
                   char *file_name;
                   file_name = my_allocate((strlen(actual_name)+2) * sizeof(char));
                   strcpy(file_name, actual_name);
                   set_name_file_entry_t(file_entry, file_name);
                }
            }
        }
        break;
      default             :
        error("Jumped off case loop deriving names of the file",
                name_file_entry_t(file_entry));
        break;
    }
}

/*****************************************************************************
 *
 *  Procedure    : output tree
 *
 *  Parameters   : the root of the tree
 *
 *  Return value : None
 *
 *  Function     : Output a textual representation of the tree in Makefile
 *                 format.
 *
 *****************************************************************************/

PUBLIC void derive_real_names ()
{
  file_entry_t *current_entry;

  reset_file_t(files);
  current_entry = next_file_t(files);
  while(current_entry != NULL)
    {
      derive_name_file_entry_t(current_entry);
      current_entry = next_file_t(files);
    }
}
