/*
 *  Example program which dynamically loads from a file a simple function
 *  that adds 3 to its parameter; the function does not require any static,
 *  heap or i/o.
 *  The function is expected already to be in a .rsc file called "add3.rsc".
 */


#include <stdio.h>
#include <stdlib.h>
#include <fnload.h>

int main( void )
{
  char* rsc_filename = "add3.rsc";
  fn_info file_details;
  size_t header_size;

  printf( "Main program started.\n" );
  if (get_code_details_from_file( rsc_filename, &file_details, &header_size ) != 0)
    printf( "Details were not successfully retrieved from the .rsc file.\n" );
  else
    {
      void* code_area_base;

      if ( (code_area_base = malloc( file_details.code_size )) == NULL )
        printf( "Malloc failed to allocate enough space for code.\n" );
      else
        {
          loaded_fn_ptr fn_ptr;

          if ( (fn_ptr = load_code_from_file( rsc_filename, &file_details,
                                        header_size, code_area_base )) == NULL )
            printf( "Code was not successfully loaded from the .rsc file.\n" );
          else
            {
              typedef int (*loaded_code_fn_ptr)(int);

              if ( ( *((loaded_code_fn_ptr)fn_ptr) )(71) == 74 )
                printf( "\n***Dynamically loaded code gave correct value.***\n\n" );
              else
                printf( "\n<<<Dynamically loaded code gave wrong answer.>>>\n\n" );
            }
          free( code_area_base );
        }
    }
  printf( "Ending main program.\n" );
  return 0;
}
