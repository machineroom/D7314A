/* CMSIDENTIFIER
   PLAY:POPEN_C@402.AAAA-FILE;1(20-FEB-92)[FROZEN] */
/*
-- ----------------------------------------------------------------------------
--
--     Object Name : popen.c
--     Revision    : 1
--
--     Copyright INMOS Limited, 1988.
--     All Rights Reserved.
--
--     DESCRIPTION
--         Standard INMOS routine for opening a file which exists an a path.
--
--     NOTES
--         None.
--
--     HISTORY
--         28-Nov-1988    Antony King    Last change.
--
-- ----------------------------------------------------------------------------
*/

/* Included files */

#include <stdio.h>
#include "popenh.h"

/* External procedures */

EXTERNAL CHAR *getenv();

/*
-- ----------------------------------------------------------------------------
--
--     Function Name : check_base_name
--
--     Input Parameters :
--         CHAR *file_name - file name to be tested for.
--
--     Output Parameters :
--         None.
--
--     Result :
--         BOOL            - TRUE if found specifier, otherwise FALSE.
--
--     DESCRIPTION
--         Returns TRUE if the file name does not have any sort of directory
--         specification in it, otherwise FALSE is returned.
--
-- ----------------------------------------------------------------------------
*/

PRIVATE BOOL check_base_name (file_name)
    CHAR *file_name;
{
    CHAR *name_ptr;

    name_ptr = file_name + (strlen(file_name) - 1);
    while (name_ptr != NULL)
    {
        switch (*name_ptr)
        {
            case '/':
            case '\\':
            case ':':
            case ']':
                return(FALSE);
                break;
            default:
                name_ptr = ((name_ptr == file_name) ? NULL : name_ptr - 1);
                break;
        }
    }
    return(TRUE);
}

/*
-- ----------------------------------------------------------------------------
--
--     Function Name : test_file_exists
--
--     Input Parameters :
--         CHAR *file_name - file name to be tested.
--         INT open_mode   - mode for the file to be opened in.
--
--     Output Parameters :
--         None.
--
--     Result :
--         FILE *          - pointer to file stream, otherwise NULL.
--
--     DESCRIPTION
--         Returns a pointer to the file stream if it can open the file in the
--         specified mode (text, value 0 or binary, value 1). If the file does
--         not exist then NULL is returned.
--
-- ----------------------------------------------------------------------------
*/

PRIVATE FILE *test_file_exists (file_name, open_mode)
    INT open_mode;
    CHAR *file_name;
{
    FILE *file_stream = NULL;

    if (open_mode == POPEN_TEXT_MODE)
        FOPEN_READ_TEXT(file_name, file_stream);
    else if (open_mode == POPEN_BINARY_MODE)
        FOPEN_READ_BINARY(file_name, file_stream);
    return(file_stream);
}

/*
-- ----------------------------------------------------------------------------
--
--     Function Name : find_next_name
--
--     Input Parameters :
--         CHAR *path_string - start of path string to be searched along.
--         CHAR *file_name   - file name to be added to the path.
--
--     Output Parameters :
--         CHAR *full_name   - full path name of the file to be tested.
--
--     Result :
--         CHAR *            - new start of the path string.
--
--     DESCRIPTION
--         Finds the next directory section from the path string and then
--         concatenates the directory section and file name together to create
--         a new full path name for the file. If there are no more directory
--         sections in the path string then no new full path name is created.
--
-- ----------------------------------------------------------------------------
*/

PRIVATE CHAR *find_next_name (path_string, file_name, full_name)
    CHAR *path_string, *file_name, *full_name;
{
    if (*path_string != '\0')
    {
        BOOL found_directory = FALSE;
        
        while ((! found_directory) && (*path_string != '\0'))
        {
            switch (*path_string)
            {
                case ';' :
                case ' ' :
                    found_directory = TRUE;
                    while ((*path_string == ';') || (*path_string == ' ')) 
                        *path_string++;
                    break;
                default :
                    *full_name++ = *path_string++;
                    break;
            }
        }
        *full_name = '\0';
        strcat(full_name, file_name);
    }
    return(path_string);
}

/*
-- ----------------------------------------------------------------------------
--
--     Function Name : popen_read
--
--     Input Parameters :
--         CHAR *file_name - file name to be searched for and opened.
--         CHAR *path_name - name of the path environment variable.
--         INT open_mode   - mode for the file to be opened in.
--
--     Output Parameters :
--         CHAR *full_name - full path name of the file found on the path.
--
--     Result :
--         FILE *          - pointer to file stream, otherwise NULL.
--
--     DESCRIPTION
--         A routine for opening a file in the occam toolset, where you search
--         an environment variable for a list of directories to look in. It
--         first simply tries to open the basic file name. If it cannot and the
--         file name contains a directory specification in it then no path
--         searching is performed.
--
--         Otherwise it translates the environment variable and it scans
--         through the directories on the list specified by the variable (each
--         separated by spaces or semicolons). It adds the file name onto the
--         end of each directory specification in turn, and then trying to open
--         the full path name just created for the file.
--
--         If it succeeds in opening the file (on the path or otherwise), it
--         returns the full path name for the file and a FILE pointer to it. If
--         it cannot find the file (on the path or otherwise) then it returns
--         NULL and no full path name.
--
--         The open mode parameter specifies text, value 0 and binary value 1.
--
-- ----------------------------------------------------------------------------
*/

PUBLIC FILE *popen_read (file_name, path_name, full_name, open_mode)
    INT open_mode;
    CHAR *file_name, *path_name, *full_name;
{
    FILE *file_stream = NULL;

    if ((file_name != NULL) && (strlen(file_name) != 0))
    {
        if ((file_stream = test_file_exists(file_name, open_mode)) == NULL)
        {
            if ((path_name != NULL) && (strlen(path_name) != 0))
            {
                if (check_base_name(file_name))
                {
                    CHAR *path_string = NULL;
                    
                    if ((path_string = getenv(path_name)) != NULL)
                    {
                        while ((file_stream == NULL) && (strlen(path_string) != 0))
                        {
                            path_string = find_next_name(path_string, file_name, full_name);
                            if (strlen(full_name) != 0)
                                file_stream = test_file_exists(full_name, open_mode);
                        }
                    }
                }
            }
        }
        else
            strcpy(full_name, file_name);
    }
    if (file_stream == NULL)
        *full_name = '\0';
    return(file_stream);
}
