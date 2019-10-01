/* CMSIDENTIFIER
   PLAY:PROCS_C@404.AAAA-FILE;1(20-FEB-92)[FROZEN] */
/*****************************************************************************
 *
 *   Object Name : procs.c
 *   Revision    : 1
 *
 *   Copyright (c) Inmos Ltd, 1988
 *   All rights reserved.
 *
 *   DESCRIPTION : Procedures that access data structures required by the
 *                 buildmake declaration
 *
 *   DOCUMENTS   : The Buildmake Program, 16th May 1988 (R Knagg)
 *                 Buildmake Technical Documentation, May 31st 1988 (R Knagg)
 *
 *   HISTORY     : Created by Ray Knagg, 1st June 1988
 *                 Added set_name_file_info_t for path
 *                 searching - Ray Knagg 18th August 1988
 *
 *****************************************************************************/

#include <stdio.h>
#include "inmos.h"
#include "struct.h"
#include "header.h"

extern INT information;

/*****************************************************************************
 *
 *  Procedure    : next_dependent_info_t
 *
 *  Parameters   : the file dependent structure
 *
 *  Return value : a file name
 *
 *  Function     : returns the file_info of a dependent file or a NULL value
 *
 *****************************************************************************/

PUBLIC file_info_t *next_dependent_info_t(file_dependents)
dependent_info_t *file_dependents;
{
  file_info_t *next_file_info = NULL;

  if(file_dependents->current != NULL)
    {
      next_file_info = file_dependents->current->info;
      file_dependents->current = file_dependents->current->next;
    }

  return(next_file_info);
}

/*****************************************************************************
 *
 *  Procedure    : reset_dependent_info_t
 *
 *  Parameters   : the file dependent structure
 *
 *  Return value : None
 *
 *  Function     : resets the file dependent structure so that the next
 *                 to next_file_dependent returns the first dependent in the
 *                 structure
 *
 *****************************************************************************/

PUBLIC void reset_dependent_info_t(file_dependents)
dependent_info_t *file_dependents;
{
  file_dependents->current = file_dependents->first;
}

/*****************************************************************************
 *
 *  Procedure    : create_dependent_info_t
 *
 *  Parameters   : None
 *
 *  Return value : pointer to the dependent structure
 *
 *  Function     : This procedure creates an temp dependent structure
 *                 which consists of a linked list of item of type file_info
 *
 *****************************************************************************/

PUBLIC dependent_info_t *create_dependent_info_t ()
{
  dependent_info_t *new;

  new = my_allocate(sizeof(dependent_info_t));

  if (new != NULL)
    {
      /* allocation OK, initialise component values */
      new->first = new->last = NULL;
    }

  return(new);
}

/*****************************************************************************
 *
 *  Procedure    : inst_dependent_node_t
 *
 *  Parameters   : the file_info and a pointer to the next item on the list
 *
 *  Return value : pointer to the new node
 *
 *  Function     : to create a new node in the list and assign it's values
 *
 *****************************************************************************/

PRIVATE dependent_node_t *inst_dependent_node_t (file_info, next_node)
file_info_t    *file_info;
dependent_node_t  *next_node;
{
  dependent_node_t *new;

  new = my_allocate(sizeof(dependent_node_t));

  if (new != NULL)
    {
      new->info   = file_info;
      new->next   = next_node;
    }

  return (new);
}

/*****************************************************************************
 *
 *  Procedure    : add_dependent_info_t
 *
 *  Parameters   : the file info to add
 *
 *  Return value : a pointer to the file info that has been added
 *
 *  Function     : adds a file info element to the dependent_info_t structure.
 *
 *****************************************************************************/

PUBLIC file_info_t *add_dependent_info_t (dependents, file_info)
dependent_info_t *dependents;
file_info_t *file_info;
{
  dependent_node_t *new;

  new = inst_dependent_node_t(file_info, NULL);

  if (new != NULL)
    {
       /* allocated ok, append data item */
       if ((dependents->first) != NULL)  /* the list is not empty */
         dependents->last->next = new;
       else                         /* the list is empty */
         dependents->first = new;
       dependents->last = new;           /* update last pointer */
    }
  return(file_info);
}

/*****************************************************************************
 *
 *  Procedure    : remove_dependent_info_t
 *
 *  Parameters   : the file entry of the file to be operated on.
 *
 *  Return value : None
 *
 *  Function     : Delete the file dependent structure
 *
 *****************************************************************************/

PUBLIC void remove_dependent_info_t(file_dependent)
dependent_info_t *file_dependent;
{
  dependent_node_t *node, *prev_node;

  node = file_dependent->first;
  while(node != NULL)
    {
      free(node->info);
      prev_node = node;
      node = node->next;
      free(prev_node);
    }
  free(file_dependent);
}

/*****************************************************************************
 *
 *  Procedure    : inst_file_info_t
 *
 *  Parameters   : The file name, the parent_filename
 *                 any associated options (if the file
 *                 is referenced from a linker command file), and the
 *                 file type
 *
 *  Return value : pointer to the information
 *
 *  Function     : This procedure creates the storage space for the
 *                 structure and assigns it's values
 *
 *****************************************************************************/

PUBLIC file_info_t *inst_file_info_t (name, parent_name, options, type)
char *name, *parent_name, *options;
INT type;
{ static char* empty="\0\0";
   
  file_info_t *new;

  new = my_allocate(sizeof(file_info_t));

  if (new != NULL)
    {
      new->name        = name;
      if(parent_name!=NULL &&*parent_name!='\0') new->parent_name = parent_name;
      else new->parent_name = empty;
      if(options!=NULL && *options!='\0') new->options     = options;
      else new->options     = empty;
      new->type        = type;
    }

  return(new);
}

/*****************************************************************************
 *
 *  Procedure    : name_file_info
 *
 *  Parameters   : the file info node
 *
 *  Return value : pointer to the information
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC  char *name_file_info_t (file_info)
file_info_t *file_info;
{
  return(file_info->name);
}

/*****************************************************************************
 *
 *  Procedure    : parent_file_info
 *
 *  Parameters   : the file info node
 *
 *  Return value : pointer to the information
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC  char *parent_file_info_t (file_info)
file_info_t *file_info;
{
  return(file_info->parent_name);
}

/*****************************************************************************
 *
 *  Procedure    : type_file_info_t
 *
 *  Parameters   : the file info node
 *
 *  Return value : pointer to the information
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC INT type_file_info_t (file_info)
file_info_t *file_info;
{
  return(file_info->type);
}

/*****************************************************************************
 *
 *  Procedure    : set_type_file_info_t
 *
 *  Parameters   : the file info node, the new file type
 *
 *  Return value : pointer to the information
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC void set_type_file_info_t (file_info, new_type)
file_info_t *file_info;
INT          new_type;
{
  file_info->type = new_type;
}

/*****************************************************************************
 *
 *  Procedure    : option_file_info_t
 *
 *  Parameters   : the file info node
 *
 *  Return value : pointer to the information
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC char *options_file_info_t (file_info)
file_info_t *file_info;
{
  return(file_info->options);
}

/*****************************************************************************
 *
 *  Procedure    : inst_action_node_t
 *
 *  Parameters   : a action entry and a pointer to the next item on the list
 *
 *  Return value : pointer to the new node
 *
 *  Function     : to create a new node in the list and assign it's values
 *
 *****************************************************************************/

PRIVATE action_node_t *inst_action_node_t (action_entry, next_node)
action_entry_t *action_entry;
action_node_t  *next_node;
{
  action_node_t *new;

  new = my_allocate(sizeof(action_node_t));

  if (new != NULL)
    {
      new->action = action_entry;
      new->next   = next_node;
    }

  return (new);
}

/*****************************************************************************
 *
 *  Procedure    : inst_action_entry_t
 *
 *  Parameters   : the action string
 *
 *  Return value : pointer to the new entry
 *
 *  Function     : to create a new action entry and assign values to the fields
 *
 *****************************************************************************/

PUBLIC action_entry_t *inst_action_entry_t (action)
char *action;
{
  action_entry_t *new;

  new = my_allocate(sizeof(action_entry_t));

  if (new != NULL)
    {
      new->action_str = action;
    }

  return (new);
}

/*****************************************************************************
 *
 *  Procedure    : append_action_t
 *
 *  Parameters   : the action element to add
 *
 *  Return value : a pointer to the action element that has been added
 *
 *  Function     : adds a action element to the action element structure.
 *                 It actually adds the action to the end of a list
 *
 *****************************************************************************/

PUBLIC action_entry_t *append_action_t (actions, action_entry)
action_t       *actions;
action_entry_t *action_entry;
{
  action_node_t *new;

  new = inst_action_node_t(action_entry, NULL);

  if (new != NULL)
    {
       /* allocated ok, append data item */
       if ((actions->first) != NULL)  /* the list is not empty */
         actions->last->next = new;
       else                         /* the list is empty */
         actions->first = new;
       actions->last = new;           /* update last pointer */
    }
  return(action_entry);
}

/*****************************************************************************
 *
 *  Procedure    : create_action_t
 *
 *  Parameters   : None
 *
 *  Return value : pointer to the action structure
 *
 *  Function     : This procedure creates an action structure which
 *                 in this case is a headed list
 *
 *****************************************************************************/

PUBLIC action_t *create_action_t ()
{
  action_t *new;

  new = my_allocate(sizeof(action_t));

  if (new != NULL)
    {
      /* allocation OK, initialise component values */
      new->first = NULL;
      new->last  = NULL;
    }

  return(new);
}

/*****************************************************************************
 *
 *  Procedure    : next_action_t
 *
 *  Parameters   : the action structure
 *
 *  Return value : a string
 *
 *  Function     : returns an action string from the action structure
 *
 *****************************************************************************/

PUBLIC char *next_action_t(actions)
action_t *actions;
{
  char *next_action = NULL;

  if(actions->current != NULL)
    {
      next_action = actions->current->action->action_str;
      actions->current = actions->current->next;
    }

  return(next_action);
}

/*****************************************************************************
 *
 *  Procedure    : reset_action_t
 *
 *  Parameters   : the action structure
 *
 *  Return value : None
 *
 *  Function     : resets the action structure so that the next call
 *                 to next_action_t returns the first action in the
 *                 structure
 *
 *****************************************************************************/

PUBLIC void reset_action_t(actions)
action_t *actions;
{
  actions->current = actions->first;
}

/*****************************************************************************
 *
 *  Procedure    : create_dependent_t
 *
 *  Parameters   : None
 *
 *  Return value : pointer to the dependent structure
 *
 *  Function     : This procedure creates an dependent structure which
 *                 in this case is a headed list
 *
 *****************************************************************************/

PRIVATE dependent_t *create_dependent_t ()
{
  dependent_t *new;

  new = my_allocate(sizeof(dependent_t));

  if (new != NULL)
    {
      /* allocation OK, initialise component values */
      new->first = new->last = NULL;
    }

  return(new);
}

/*****************************************************************************
 *
 *  Procedure    : inst_dependent_node_t
 *
 *  Parameters   : a file entry and a pointer to the next item on the list
 *
 *  Return value : pointer to the new node
 *
 *  Function     : to create a new node in the list and assign it's values
 *
 *****************************************************************************/

PRIVATE dependent_list_t *inst_dependent_list_t (file_entry, next_node)
file_entry_t *file_entry;
dependent_list_t  *next_node;
{
  dependent_list_t *new;

  new = my_allocate(sizeof(dependent_list_t));

  if (new != NULL)
    {
      new->file   = file_entry;
      new->next   = next_node;
    }

  return (new);
}

/*****************************************************************************
 *
 *  Procedure    : append_dependent_t
 *
 *  Parameters   : the dependent structure
 *                 and the file entry of a dependent file
 *
 *  Return value : None
 *
 *  Function     : Adds the given entry to the dependent structure
 *
 *****************************************************************************/

PRIVATE void append_dependent_t(dependents, file_entry)
dependent_t  *dependents;
file_entry_t *file_entry;
{
  dependent_list_t *new;

  new = inst_dependent_list_t(file_entry, NULL);

  if (new != NULL)
    {
      /* allocated ok, append data item */
      if ((dependents->first) != NULL)  /* the list is not empty */
        dependents->last->next = new;
      else                         /* the list is empty */
        dependents->first = new;
      dependents->last = new;           /* update last pointer */
    }
}

/*****************************************************************************
 *
 *  Procedure    : next_dependent_t
 *
 *  Parameters   : the file dependent structure
 *
 *  Return value : a file name
 *
 *  Function     : returns the file_entry of a dependent file or a NULL value
 *
 *****************************************************************************/

PUBLIC file_entry_t *next_dependent_t(dependents)
dependent_t *dependents;
{
  file_entry_t *next_file_entry = NULL;

  if(dependents->current != NULL)
    {
      next_file_entry = dependents->current->file;
      dependents->current = dependents->current->next;
    }

  return(next_file_entry);
}

/*****************************************************************************
 *
 *  Procedure    : reset_dependent_t
 *
 *  Parameters   : the file dependent structure
 *
 *  Return value : None
 *
 *  Function     : resets the file dependent structure so that the next
 *                 to next_file_dependent returns the first dependent in the
 *                 structure
 *
 *****************************************************************************/

PUBLIC void reset_dependent_t(dependents)
dependent_t *dependents;
{
  dependents->current = dependents->first;
}

/*****************************************************************************
 *
 *  Procedure    : inst_file_entry_t
 *
 *  Parameters   : file name, file type and options
 *
 *  Return value : pointer to the new entry
 *
 *  Function     : to create a new file entry and assign values to it's fields
 *
 *****************************************************************************/

PUBLIC file_entry_t *inst_file_entry_t (name, parent,type, options)
char *name;
char * parent;
INT type;
char *options;
{
  static char empty[]="\0\0";
  file_entry_t *new;

  new = my_allocate(sizeof(file_entry_t));

  if (new != NULL)
    {
      new->filename   = name;
      new->realname   = name;
      if(parent!=NULL && *parent!='\0') new->parent     = parent;
      else new->parent=empty;
      
      new->dependents = create_dependent_t ();
      new->actions    = NULL;
      new->built      = FALSE;
      new->file_type  = type;
      new->options    = options;
    }

  return (new);
}

/*****************************************************************************
 *
 *  Procedure    : type_file_entry_t
 *
 *  Parameters   : the file entry
 *
 *  Return value : None
 *
 *  Function     : Returns the file type of the given file entry
 *
 *****************************************************************************/

PUBLIC INT type_file_entry_t(file_entry)
file_entry_t *file_entry;
{
  return(file_entry->file_type);
}

/*****************************************************************************
 *
 *  Procedure    : add_actions_file_entry_t
 *
 *  Parameters   : the file entry and the action list
 *
 *  Return value : None
 *
 *  Function     : Adds an action list to an existing file entry
 *
 *****************************************************************************/

PUBLIC void add_actions_file_entry_t(file_entry, actions)
file_entry_t *file_entry;
action_t     *actions;
{
  if (file_entry != NULL)
    file_entry->actions = actions;
}

/*****************************************************************************
 *
 *  Procedure    : name_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : pointer to the entry
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC  char *name_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  return(file_entry->filename);
}

/*****************************************************************************
 *
 *  Procedure    : realname_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : pointer to the entry
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC  char *realname_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  return(file_entry->realname);
}

/*****************************************************************************
 *
 *  Procedure    : built_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : pointer to the entry
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC  BOOL built_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  return(file_entry->built);
}

/*****************************************************************************
 *
 *  Procedure    : dependents_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : pointer to the entry
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC  dependent_t *dependents_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  return(file_entry->dependents);
}

/*****************************************************************************
 *
 *  Procedure    : options_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : pointer to the entry
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC char *options_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  return(file_entry->options);
}

/*****************************************************************************
 *
 *  Procedure    : append_dependent_file_entry_t
 *
 *  Parameters   : the file entry and the file entry of a dependent file
 *
 *  Return value : None
 *
 *  Function     : Adds the given entry to the dependent field of the file
 *                 entry
 *
 *****************************************************************************/

PUBLIC void append_dependent_file_entry_t(file_entry, dependent_entry)
file_entry_t *file_entry, *dependent_entry;
{
  append_dependent_t(dependents_file_entry_t(file_entry), dependent_entry);
}

/*****************************************************************************
 *
 *  Procedure    : set_built_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : none
 *
 *  Function     : set built to TRUE in the file entry node
 *
 *****************************************************************************/

PUBLIC void set_built_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  file_entry->built = TRUE;
}

/*****************************************************************************
 *
 *  Procedure    : set_not_built_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : none
 *
 *  Function     : set built to FALSE in the file entry node
 *
 *****************************************************************************/

PUBLIC void set_not_built_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  file_entry->built = FALSE;
}

/*****************************************************************************
 *
 *  Procedure    : set_name_file_entry_t
 *
 *  Parameters   : the file entry node. and the new file name
 *
 *  Return value : pointer to the information
 *
 *  Function     : set the realname of the file entry - required to
 *                 implement path searching since the makefile requires the
 *                 full pathname.
 *
 *****************************************************************************/

PUBLIC void set_name_file_entry_t (file_entry, new_name)
file_entry_t *file_entry;
char *new_name;
{
  file_entry->realname = new_name;
}

/*****************************************************************************
 *
 *  Procedure    : can_build_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : none
 *
 *  Function     : attempts to determine whether the node can be built.
 *                 it does this by looking at the dependents to see if it
 *                 has any. If it doesn't then the file can be made. If all
 *                 the dependents can be made then the file can be made.
 *                 Otherwise the file cannot be made.
 *
 *****************************************************************************/

PUBLIC BOOL can_build_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  BOOL built;

  built = built_file_entry_t(file_entry);
  if(built == FALSE)
    {
      dependent_t  *dependents;
      file_entry_t *dependent_file_entry;
    
      dependents = dependents_file_entry_t(file_entry);
      reset_dependent_t(dependents);
      dependent_file_entry = next_dependent_t(dependents);
      built = TRUE;
      while(dependent_file_entry != NULL)
        {
          if(!built_file_entry_t(dependent_file_entry))
            built = FALSE;
          dependent_file_entry = next_dependent_t(dependents);
        }
      if (built) set_built_file_entry_t(file_entry);
    }
  return(built);
}

/*****************************************************************************
 *
 *  Procedure    : actions_file_entry_t
 *
 *  Parameters   : the file entry node
 *
 *  Return value : pointer to the entry
 *
 *  Function     : Access the node for the required information
 *
 *****************************************************************************/

PUBLIC  action_t *actions_file_entry_t (file_entry)
file_entry_t *file_entry;
{
  return(file_entry->actions);
}

/*****************************************************************************
 *
 *  Procedure    : inst_file_node
 *
 *  Parameters   : a file entry and a pointer to the next item on the list
 *
 *  Return value : pointer to the new node
 *
 *  Function     : to create a new node in the list and assign it's values
 *
 *****************************************************************************/

PRIVATE file_node_t *inst_file_node (file_entry, next_node)
file_entry_t *file_entry;
file_node_t  *next_node;
{
  file_node_t *new;

  new = my_allocate(sizeof(file_node_t));

  if (new != NULL)
    {
      new->item = file_entry;
      new->next = next_node;
    }

  return (new);
}

/*****************************************************************************
 *
 *  Procedure    : create_file_t
 *
 *  Parameters   : None
 *
 *  Return value : pointer to the file element structure
 *
 *  Function     : This procedure creates a file element structure which
 *                 in this case is a headed list
 *
 *****************************************************************************/

PUBLIC file_t *create_file_t ()
{
  file_t *new;

  new = my_allocate(sizeof(file_t));

  if (new != NULL)
    {
      /* allocation OK, initialise component values */
      new->first = new->last = NULL;
    }

  return(new);
}

/*****************************************************************************
 *
 *  Procedure    : copy_file_t
 *
 *  Parameters   : a file element structure to copy
 *
 *  Return value : pointer to the file element structure
 *
 *  Function     : This procedure copy's a file element structure which
 *                 in this case is a headed list
 *
 *****************************************************************************/

PUBLIC file_t *copy_file_t (files)
file_t *files;
{
  file_t *new;

  new = my_allocate(sizeof(file_t));

  if (new != NULL)
    {
      /* allocation OK, initialise component values */
      new->first = files->first;
      new->last  = files->last;
    }

  return(new);
}

/*****************************************************************************
 *
 *  Procedure    : remove_file_t
 *
 *  Parameters   : the file structure to be operated on.
 *
 *  Return value : None
 *
 *  Function     : Delete the file structure
 *
 *****************************************************************************/

PUBLIC void remove_file_t(files)
file_t *files;
{
  file_node_t *node, *prev_node;

  node = files->first;
  while(node != NULL)
    {
      /* does not remove the file_entry */
      prev_node = node;
      node = node->next;
      free(prev_node);
    }
  free(files);
}

/*****************************************************************************
 *
 *  Procedure    : append_file_t
 *
 *  Parameters   : the file element to add
 *
 *  Return value : a pointer to the file element that has been added
 *
 *  Function     : adds a file element to the file element structure.
 *                 It actually adds the file to the end of a list
 *
 *****************************************************************************/

PUBLIC file_entry_t *append_file_t (files, file_entry)
file_t       *files;
file_entry_t *file_entry;
{
  file_node_t *new;

  new = inst_file_node(file_entry, NULL);

  if (new != NULL)
    {
       /* allocated ok, append data item */
       if ((files->first) != NULL)  /* the list is not empty */
         files->last->next = new;
       else                         /* the list is empty */
         files->first = new;
       files->last = new;           /* update last pointer */
    }
  return(file_entry);
}

/*****************************************************************************
 *
 *  Procedure    : insert_file_t
 *
 *  Parameters   : the file element to add
 *
 *  Return value : a pointer to the file element that has been added
 *
 *  Function     : adds a file element to the file element structure.
 *                 It actually adds the file to the front of a list
 *
 *****************************************************************************/

PUBLIC file_entry_t *insert_file_t (files, file_entry)
file_t       *files;
file_entry_t *file_entry;
{
  file_node_t *new;

  new = inst_file_node(file_entry, files->first);

  if (new != NULL)
    {
       /* allocated ok, assign new header pointer */
       files->first = new;
       if ((files->last) == NULL)  /* this is the first element added */
         files->last = new;
    }
  return(file_entry);
}

/*****************************************************************************
 *
 *  Procedure    : find_file_t
 *
 *  Parameters   : the file element structure
 *                 the name of the file to be located in the structure
 *
 *  Return value : pointer to the file element
 *
 *  Function     : To search the file element structure for the given file
 *
 *****************************************************************************/

PUBLIC file_entry_t *find_file_t (files, filename)
file_t *files;
char *filename;
{
  BOOL         searching    = TRUE;
  file_entry_t *wanted_file = NULL;
  file_node_t  *list        = files->first;

  while((list != NULL) && (searching))
    if (!strcmp(list->item->filename, filename))
      {
        /* found the file element */
        wanted_file = list->item;
        searching = FALSE;
      }
    else list = list->next;

  return(wanted_file);
}

/*****************************************************************************
 *
 *  Procedure    : reset_file_t
 *
 *  Parameters   : the file element structure
 *
 *  Return value : none
 *
 *  Function     : sets the current file entry to be the first file
 *                 entered. This is the root entry
 *
 *****************************************************************************/

PUBLIC void reset_file_t (files)
file_t *files;
{
  files->current = files->first;
}

/*****************************************************************************
 *
 *  Procedure    : next_file_t
 *
 *  Parameters   : the file entry structure
 *
 *  Return value : a file entry
 *
 *  Function     : returns the file_entry of a file or a NULL value
 *
 *****************************************************************************/

PUBLIC file_entry_t *next_file_t(files)
file_t *files;
{
  file_entry_t *next_file_entry = NULL;

  if(files->current != NULL)
    {
      next_file_entry = files->current->item;
      files->current  = files->current->next;
    }

  return(next_file_entry);
}

/*****************************************************************************
 *
 *  Procedure    : add_actions_file_t
 *
 *  Parameters   : the file entry structure
 *
 *  Return value : none
 *
 *  Function     : sets the action string value for each of the entries
 *                 in the file entry structure -
 *                 done after 'derive_real_names' to allow the output
 *                 of the tools to be forced into the directory that
 *                 the source exists in. Should be default of tools.
 *
 *****************************************************************************/

PUBLIC void add_actions_file_t(files)
file_t *files;
{
  file_entry_t *file_entry;

  reset_file_t(files);
  file_entry = next_file_t(files);

  while(file_entry != NULL)
    {
       add_actions_file_entry_t(file_entry, derive_action_t(file_entry));
       file_entry = next_file_t(files);
    }
}

