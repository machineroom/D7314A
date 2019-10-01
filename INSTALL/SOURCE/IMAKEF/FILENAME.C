/* CMSIDENTIFIER
   PLAY:FILENAME_C@396.AAAA-FILE;1(20-FEB-92)[FROZEN] */
/*****************************************************************************
 *
 *   Object Name : filename.c
 *   Revision    : 1
 *
 *   Copyright (c) Inmos Ltd, 1988
 *   All rights reserved.
 *
 *   DESCRIPTION : This module of the Buildmake program hold procedures which
 *                 deal with filename and extension handling within the occam
 *                 toolset.
 *
 *   DOCUMENTS   : The Buildmake Program, 16th May 1988 (R Knagg)
 *                 Buildmake Technical Documentation, May 31st 1988 (R Knagg)
 *
 *   HISTORY     : Created by Ray Knagg, 1st June 1988
 *                 Added find_directory_specifier, -RK 18th August 1988
 *
 *****************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include "inmos.h"
#include "struct.h"
#include "header.h"

/*****************************************************************************
 *
 *  Procedure    : remove_extension
 *
 *  Parameters   : two strings, oldfilename, newfilename
 *
 *  Return value : none
 *
 *  Function     : generates a new filename which is the oldfilename minus the
 *                 extension
 *
 *****************************************************************************/

PUBLIC void remove_extension (newfilename, oldfilename)
char *newfilename, *oldfilename;
{
  BOOL found_extension = FALSE, found_directory = FALSE;
  INT old_length;
  char *current_char;

  old_length = strlen(oldfilename);
  current_char = oldfilename + old_length;
  while(!found_extension && !found_directory)
    {
      if(current_char < oldfilename)
        found_directory = TRUE;
      else
        {
          if(*current_char == '.')
            found_extension = TRUE;
          else
            if((*current_char == ':')  ||
               (*current_char == ';')  ||
               (*current_char == '[')  ||
               (*current_char == ']')  ||
               (*current_char == '(')  ||
               (*current_char == ')')  ||
               (*current_char == '\\')  ||
               (*current_char == '/')  ||
               (*current_char == '=')  ||
               (*current_char == '!'))
              found_directory = TRUE;
          else
            current_char = current_char - 1;
        }
    }
  if(found_directory)
    strncpy(newfilename, oldfilename, old_length);
  else
    {
      INT length = current_char - oldfilename;
      strncpy(newfilename, oldfilename, length);
      newfilename[length] = '\0';
    }
}

/*****************************************************************************
 *
 *  Procedure    : directory_specifier
 *
 *  Parameters   : the filename to test
 *
 *  Return value : BOOL
 *
 *  Function     : Test the given filename to see whether it contains
 *                 directory specifier
 *
 *****************************************************************************/

PUBLIC BOOL directory_specifier (filename)
char *filename;
{
  BOOL finished = FALSE, found_directory = FALSE;
  INT length;
  char *current_char;

  length = strlen(filename);
  current_char = filename + length;
  while(!finished && !found_directory)
    {
      if(current_char < filename)
        finished = TRUE;
      else
        if((*current_char == ':')  ||
           (*current_char == ';')  ||
           (*current_char == '[')  ||
           (*current_char == ']')  ||
           (*current_char == '(')  ||
           (*current_char == ')')  ||
           (*current_char == '\\')  ||
           (*current_char == '/')  ||
           (*current_char == '=')  ||
           (*current_char == '!'))
          found_directory = TRUE;
        else
          current_char = current_char - 1;
    }
  return(found_directory);
}

/*****************************************************************************
 *
 *  Procedure    : find_directory_specifier
 *
 *  Parameters   : the filename to find the directory specifier from
 *
 *  Return value : the directory specifier
 *
 *  Function     : find the directory specifier in a given string
 *
 *****************************************************************************/

PUBLIC char *find_directory_specifier (filename)
char *filename;
{
  BOOL finished = FALSE, found_directory = FALSE;
  INT length;
  char *current_char;
  char *directory_specifier;

  length = strlen(filename);
  current_char = filename + length;
  while(!finished && !found_directory)
    {
      if(current_char < filename)
        finished = TRUE;
      else
        if((*current_char == ':')  ||
           (*current_char == ';')  ||
           (*current_char == '[')  ||
           (*current_char == ']')  ||
           (*current_char == '(')  ||
           (*current_char == ')')  ||
           (*current_char == '\\')  ||
           (*current_char == '/')  ||
           (*current_char == '=')  ||
           (*current_char == '!'))
          found_directory = TRUE;
        else
          current_char = current_char - 1;
    }
  if(found_directory)
    {
      INT specifier_len;
      specifier_len = current_char - filename + 1;
      directory_specifier = my_allocate((specifier_len+1) * sizeof(char));
      directory_specifier[0] = '\0';
      strncpy(directory_specifier, filename, specifier_len);
      directory_specifier[specifier_len] = '\0';
    }
  else
    {
      directory_specifier = my_allocate(1 * sizeof(char));
      directory_specifier[0] = '\0';
    }
  return(directory_specifier);
}

/*****************************************************************************
 *
 *  Procedure    : file_extension
 *
 *  Parameters   : the filename to test
 *
 *  Return value : BOOL
 *
 *  Function     : Test the given filename to see whether it contains
 *                 a file extension
 *
 *****************************************************************************/

PUBLIC BOOL file_extension (filename)
char *filename;
{
  BOOL finished = FALSE, found_extension = FALSE;
  INT length;
  char *current_char;

  length = strlen(filename);
  current_char = filename + length;
  while(!finished && !found_extension)
    {
      if(current_char < filename)
        finished = TRUE;
      else
        if((*current_char == ':')  ||
           (*current_char == ';')  ||
           (*current_char == '[')  ||
           (*current_char == ']')  ||
           (*current_char == '(')  ||
           (*current_char == ')')  ||
           (*current_char == '\\')  ||
           (*current_char == '/')  ||
           (*current_char == '=')  ||
           (*current_char == '!'))
            finished = TRUE;
        else
          if(*current_char == '.')
            found_extension = TRUE;
        else
          current_char = current_char - 1;
    }
  return(found_extension);
}

/*****************************************************************************
 *
 *  Procedure    : set_extension
 *
 *  Parameters   : a filename string, and two char parameters
 *
 *  Return value : none
 *
 *  Function     : This procedure should only be called after a parse_extension
 *                 for a file with an extension it sets the values
 *                 of the characters in the extension. For instance the
 *                 file 'splod.txx' mode to 'h' and type to '4'. thus forming
 *                 the file 'splod.t4h'.
 *
 *****************************************************************************/

PUBLIC void set_extension(filename, file_type, error_mode, processor_type)
char *filename;
INT file_type, error_mode, processor_type;
{
  INT length = strlen(filename);
  INT long_ext_length = strlen(EXT_OCC);
  char *extension_pos = filename+length-long_ext_length;
  char *mode_pos = (extension_pos + ERROR_MODE_POS);
  char *type_pos = (extension_pos + PROCESSOR_TYPE_POS);
  char *file_pos = (extension_pos + FILE_TYPE_POS);

  *file_pos = file_type;
  *mode_pos = error_mode;
  *type_pos = processor_type;
}

/*****************************************************************************
 *
 *  Procedure    : valid_error_mode
 *
 *  Parameters   : a character
 *
 *  Return value : BOOL
 *
 *  Function     : uses the extension rules of the system to decide whether
 *                 the given character is a valid error mode
 *
 *****************************************************************************/

PUBLIC BOOL valid_error_mode (mode)
INT mode;
{
  BOOL valid = FALSE;

  char mode_l;

  if(isupper(mode))
    mode_l = tolower(mode);
  else
    mode_l = mode;

  if((mode_l == 'h') || (mode_l == 's') || (mode_l == 'x'))
     valid = TRUE;
  return(valid);
}

/*****************************************************************************
 *
 *  Procedure    : valid_processor
 *
 *  Parameters   : a character
 *
 *  Return value : BOOL
 *
 *  Function     : uses the extension rules of the system to decide whether
 *                 the given character is a processor type
 *
 *****************************************************************************/

PUBLIC BOOL valid_processor_type (typ)
INT typ;
{
  BOOL valid = FALSE;
  char type;

  if(isupper(type))
    type = tolower(typ);
  else
    type = typ;

  if((type == '2') || (type == '3') || (type == '4') ||
     (type == '5') || (type == '8') || (type == '9') ||
     (type == 'a') || (type == 'b'))
     valid = TRUE;
  return(valid);
}

/*****************************************************************************
 *
 *  Procedure    : parse_extension
 *
 *  Parameters   : a filename string, and three char parameters
 *
 *  Return value : node
 *
 *  Function     : for a file with a  extension it returns the values
 *                 of the characters in the extension. For instance the
 *                 file 'splod.t4h' would set file_type to 't', mode to 'h'
 *                 and type to '4'.
 *
 *****************************************************************************/

PUBLIC BOOL parse_extension(filename, file_type, mode, type)
char *filename, *file_type, *mode, *type;
{
  BOOL got_extension = TRUE;
  INT  length = strlen(filename);
  INT  long_ext_length = strlen(EXT_OCC);
  char *extension_pos = filename+length-long_ext_length;

  if (*extension_pos == '.')
    {
      *file_type = *(extension_pos + FILE_TYPE_POS);
      if(isupper(*file_type))
        *file_type = tolower(*file_type);
      *mode      = *(extension_pos + ERROR_MODE_POS);
      if(isupper(*mode))
        *mode      = tolower(*mode);
      *type      = *(extension_pos + PROCESSOR_TYPE_POS);
      if(isupper(*type))
        *type      = tolower(*type);
      if(!valid_error_mode(*mode) || !valid_processor_type(*type))
        got_extension = FALSE;
    }
  else
    {
      got_extension = FALSE;
      *file_type = '\0';
      *mode      = '\0';
      *type      = '\0';
    }
  return(got_extension);
}

/*****************************************************************************
 *
 *  Procedure    : file_type
 *
 *  Parameters   : the file name to classify
 *
 *  Return value : the file type as an INT of the file
 *
 *  Function     : uses the extension rules of the system to classify the file
 *
 *****************************************************************************/

PUBLIC INT file_type (filename)
char *filename;
{
  INT type = F_UNKNOWN;
  INT length = strlen(filename);
  int pos=length-1;

  while(pos>=0 && filename[pos]!='.') pos--;

  if(pos<0) return F_UNKNOWN;
  
  
  if(!strncmp(&filename[pos], EXT_OCC,4)) return(F_OCC);
  if(!strncmp(&filename[pos], EXT_C,4)) return(F_C);
  if(!strncmp(&filename[pos], EXT_FORTRAN,4)) return(F_FORTRAN);  
  if(!strncmp(&filename[pos], EXT_INC,4)) return(F_OCC);
  if(!strncmp(&filename[pos], EXT_CFS,4)) return (F_CFS);
  if(!strncmp(&filename[pos], EXT_PGM,4)) return (F_PGM);
  if(!strncmp(&filename[pos], EXT_LIB,4)) return (F_LIB);
  if(!strncmp(&filename[pos], EXT_LBB,4)) return (F_LBB);
  if(!strncmp(&filename[pos], EXT_LBU,4)) return (F_LBU);
  if(!strncmp(&filename[pos], EXT_BTL,4)) return (F_BTL);
  if(!strncmp(&filename[pos], EXT_LNK,4)) return (F_LNK);
  else {
          char file_type, error_mode, processor_type;
      
          parse_extension(filename, &file_type, &error_mode, &processor_type);
          if(valid_error_mode(error_mode) && valid_processor_type(processor_type))
            {
              if(file_type == 't') type = F_TXX;
              if(file_type == 'l') type = F_LXX;
              if(file_type == 'b') type = F_BXX;
              if(file_type == 'c') type = F_CXX;
              if(file_type == 'r') type = F_RXX;
            }
        }

  return(type);
}

