/*
 *  Example program which dynamically loads code from a file.
 *  The child code requires static, heap, i/o, stack checking and to
 *  call max_stack_usage().
 *
 *  The child is called as a parallel process, thus not needing a cast
 *  of the loaded_fn_ptr variable returned by load_code_from_file.
 *
 *  The child code is expected already to be in a .rsc file called "stack1.rsc".
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <channel.h>
#include <misc.h>
#include <fnload.h>
#include <hostlink.h>


int main( void )
{
  char* rsc_filename = "stack1.rsc";
  fn_info file_details;
  size_t header_size;
  const size_t child_heap_size_in_bytes = 4096;   /* 4K */
  const size_t child_stack_size_in_bytes = 4096;   /* 4K */

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

              if( (heap_area_base = malloc( child_heap_size_in_bytes )) == NULL )
                printf( "Malloc failed to allocate enough space for the heap.\n" );
              else
                {
                  void* child_stack;

                  if ( (child_stack = malloc( child_stack_size_in_bytes ))
                                                                   == NULL )
                    printf( "Malloc failed to allocate enough"
                            " space for the stack.\n" );
                  else
                    {
                      loaded_fn_ptr fn_ptr;
                  
                      if ( (fn_ptr = load_code_from_file( rsc_filename,
                                                          &file_details,
                                                          header_size,
                                                          code_area_base ))
                                                                    == NULL )
                        printf( "Code was not successfully loaded"
                                " from the .rsc file.\n" );
                      else
                        {
                          Process* dynamic_process;

                          if ( (dynamic_process =
                                (Process*)malloc(sizeof(Process))) == NULL )
                            printf( "Malloc failed to allocate enough"
                                    " space for the process.\n" );
                          else
                            if ( ProcInit( dynamic_process,
                                           fn_ptr,
                                           child_stack,
                                           child_stack_size_in_bytes,
                                           8,
                                           child_stack,
                                           &child_stack_size_in_bytes,
                                           static_area_base,
                                           &file_details.static_size,
                                           heap_area_base,
                                           &child_heap_size_in_bytes,
                                           from_host_link(),
                                           to_host_link() ) != 0 )
                              printf( "Could not initialise process.\n" );
                            else
                              {
                                ProcRun( dynamic_process );
                                ProcJoin( dynamic_process, NULL );
                              }
                        }
                      free( child_stack );
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
