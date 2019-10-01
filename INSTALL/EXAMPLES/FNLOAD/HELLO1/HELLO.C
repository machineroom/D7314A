/*
 *  Example program which dynamically loads from a file code that
 *  prints out "hello world"; the child code requires static, heap and i/o.
 *
 *  The child code is expected already to be in a .rsc file called "hello1.rsc".
 */


#include <stdio.h>
#include <stdlib.h>
#include <fnload.h>
#include <hostlink.h>
#define CHILD_HEAP_SIZE_IN_BYTES  (size_t)8192   /* 8K */


int main( void )
{
  char* rsc_filename = "hello1.rsc";
  fn_info file_details;
  size_t header_size;

  printf( "Main program started.\n" );
  if ( get_code_details_from_file( rsc_filename, &file_details, &header_size ) != 0 )
    printf( "Details were not successfully retrieved from the .rsc file.\n" );
  else
    {
      void* code_area_base;

      if ( (code_area_base = malloc( file_details.code_size )) == NULL )
        printf( "Malloc failed to allocate enough space for code.\n" );
      else
        {
          void* static_area_base;

          if ( (static_area_base = malloc( file_details.static_size )) == NULL )
            printf( "Malloc failed to allocate enough space for static.\n" );
          else
            {
              void* heap_area_base;

              if( (heap_area_base = malloc( CHILD_HEAP_SIZE_IN_BYTES )) == NULL )
                printf( "Malloc failed to allocate enough space for the heap.\n" );
              else
                {
                  loaded_fn_ptr fn_ptr;
              
                  if ( (fn_ptr = load_code_from_file( rsc_filename, &file_details,
                                            header_size, code_area_base )) == NULL )
                    printf( "Code was not successfully loaded from the .rsc file.\n" );
                  else
                    {
                      typedef int (*loaded_code_fn_ptr)(void*, size_t,
                                                        void*, size_t,
                                                        Channel*, Channel*);

                      /*
                       *   Call the dynamically loaded code to print
                       *   out "hello world".
                       */
                      (void)( *((loaded_code_fn_ptr)fn_ptr) )(static_area_base,
                                                      file_details.static_size,
                                                      heap_area_base,
                                                      CHILD_HEAP_SIZE_IN_BYTES,
                                                      from_host_link(),
                                                      to_host_link() );
                    }
                  free( heap_area_base );
                }
              free( static_area_base );
            }
          free( code_area_base );
        }
    }
  printf( "Ending main program.\n" );
  return 0;
}
