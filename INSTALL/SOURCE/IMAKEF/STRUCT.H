/* CMSIDENTIFIER
   PLAY:STRUCT_H@405.AAAA-FILE;1(20-FEB-92)[FROZEN] */
/*****************************************************************************
 *
 *   Object Name : struct.h
 *   Revision    : 1
 *
 *   Copyright (c) Inmos Ltd, 1988
 *   All rights reserved.
 *
 *   DESCRIPTION : This the declaration of the data structures required by the
 *                 build make program
 *
 *   DOCUMENTS   : The Buildmake Program, 16th May 1988 (R Knagg)
 *                 Buildmake Technical Documentation, May 31st 1988 (R Knagg)
 *
 *   HISTORY     : Created by Ray Knagg, 1st June 1988
 *
 *****************************************************************************/

struct action_entry
  {
    char *action_str;
  };

typedef struct action_entry action_entry_t;

struct action_list
  {
    action_entry_t     *action;
    struct action_list *next;
  };

typedef struct action_list action_node_t;

struct action_list_head
  {
    action_node_t *first, *last, *current;
  };

typedef struct action_list_head action_t;

struct dependent_list
  {
    struct file_entry     *file;
    struct dependent_list *next;
  };

typedef struct dependent_list dependent_list_t;

struct dependent_list_head
  {
    dependent_list_t *first, *last, *current;
  };

typedef struct dependent_list_head dependent_t;

struct file_entry
  {
    char        *filename;
    char        *realname;
    char        *parent;
    
    dependent_t *dependents;
    action_t    *actions;
    BOOL        built;
    INT         file_type;
    char        *options;
  };

typedef struct file_entry file_entry_t;

struct file_node
  {
    file_entry_t     *item;
    struct file_node *next;
  };

typedef struct file_node file_node_t;

struct file_list_head
  {
    file_node_t *first, *last, *current;
  };

typedef struct file_list_head file_t;

struct file_info
  {
    char  *name, *parent_name;
    char  *options;
    INT   type;
  };

typedef struct file_info file_info_t;

struct dependent_node
  {
    file_info_t           *info;
    struct dependent_node *next;
  };

typedef struct dependent_node dependent_node_t;


struct dependent_node_head
  {
    dependent_node_t *first, *last, *current;
  };

typedef struct dependent_node_head dependent_info_t;
