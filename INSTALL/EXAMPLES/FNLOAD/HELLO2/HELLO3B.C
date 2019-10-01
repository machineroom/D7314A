/*
 *  Second child in a chain of children; this child dynamically engenders
 *  a child.
 *  Requires static, heap and i/o.
 *
 *  The code of the child of this child is expected already to be in a
 *  .rsc file called "helloc.rsc".
 */


#pragma IMS_off(stack_checking)


#include <stdio.h>
#include <stdlib.h>
#include <fnload.h>
#include <hostlink.h>
#define CHILD_HEAP_SIZE_IN_BYTES  (size_t)65536   /* 64K */


int hello_world( void )
{
  char* rsc_filename = "helloc.rsc";
  fn_info file_details;
  size_t header_size;

  printf( "Hello world from child B.\n" );
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
                       *   out a 'hello world' message.
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
  printf( "Goodbye world from child B.\n" );
  return 0;
}
