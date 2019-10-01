/*
 *  Example program which dynamically loads code from a file where that
 *  code is to be stack checked and use max_stack_usage().  The dynamically
 *  loaded code is called directly from the main program, rather than from
 *  a parallel process or as a parallel process.  The dynamically loaded
 *  code requires static, heap, i/o, stack checking and to call
 *  max_stack_usage().
 *
 *  The child code is expected already to be in a .rsc file called "stack1.rsc".
 */


#include <stdio.h>
#include <stdlib.h>
#include <fnload.h>
#include <hostlink.h>
#include <misc.h>
#define CHILD_HEAP_SIZE_IN_BYTES  (size_t)9216   /* 9K */


int main( void )
{
  char* rsc_filename = "stack1.rsc";
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
          void* static_area_base;

          if ( (static_area_base = malloc( file_details.static_size )) == NULL )
            printf( "Malloc failed to allocate enough space for static.\n" );
          else
            {
              void* heap_area_base;

              if( (heap_area_base = malloc( CHILD_HEAP_SIZE_IN_BYTES ))
                                                                == NULL )
                printf( "Malloc failed to allocate enough"
                        " space for the heap.\n" );
              else
                {
                  loaded_fn_ptr fn_ptr;
              
                  if ( (fn_ptr = load_code_from_file( rsc_filename,
                                                      &file_details,
                                                      header_size,
                                                      code_area_base )) == NULL )
                    printf( "Code was not successfully loaded"
                            " from the .rsc file.\n" );
                  else
                    {
                      void *child_stack_addr;
                      size_t child_stack_size_in_bytes;
                      typedef int (*loaded_code_fn_ptr)(void*, size_t,
                                                        void*, size_t,
                                                        void*, size_t,
                                                        Channel*, Channel*);

                      get_details_of_free_stack_space( &child_stack_addr,
                                                  &child_stack_size_in_bytes );

                      /*
                       *       call the dynamically loaded code
                       */
                      (void)( *((loaded_code_fn_ptr)fn_ptr) )(static_area_base,
                                                      file_details.static_size,
                                                      child_stack_addr,
                                                      child_stack_size_in_bytes,
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
