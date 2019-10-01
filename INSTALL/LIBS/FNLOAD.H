/* @(#)fnload.h	1.5 9/28/92 */

/*
 *  fnload.h - header file for dynamic code loading functions
 *
 *  Copyright (C) Inmos Ltd. 1992
 */


#ifndef __fnload_h
#define __fnload_h

#include <stddef.h>  /* for size_t */
#include <channel.h>

#pragma IMS_translate(get_code_details_from_file, \
                     "get_code_details_from_file%c")
#pragma IMS_translate(get_code_details_from_memory, \
                     "get_code_details_from_memory%c")
#pragma IMS_translate(get_code_details_from_channel, \
                     "get_code_details_from_channel%c")
#pragma IMS_translate(load_code_from_file, "load_code_from_file%c")
#pragma IMS_translate(load_code_from_memory, "load_code_from_memory%c")
#pragma IMS_translate(load_code_from_channel, "load_code_from_channel%c")



struct fn_data
  {
    int    target_processor_type; /* as given in file */
    size_t stack_size;            /* in bytes */
    size_t vectorspace_size;      /* in bytes */
    size_t static_size;           /* in bytes */
    size_t entry_point_offset;    /* in bytes */
    size_t code_size;             /* in bytes */
  };

typedef struct fn_data fn_info;
typedef void (*loaded_fn_ptr)(void);


extern int get_code_details_from_file( const char* /*filename*/,
                                       fn_info* /*fn_details*/,
                                       size_t* /*file_hdr_size*/ );
extern int get_code_details_from_memory( const void* /*addr_of_file_image*/,
                                         fn_info* /*fn_details*/,
                                         size_t* /*file_hdr_size*/,
                                         loaded_fn_ptr* /*function_pointer*/ );
extern int get_code_details_from_channel( Channel* /*in_channel*/,
                                          fn_info* /*fn_details*/ );

extern loaded_fn_ptr load_code_from_file( const char* /*filename*/,
                                          const fn_info* /*fn_details*/,
                                          size_t /*file_hdr_size*/,
                                          void* /*dest*/ );
extern loaded_fn_ptr load_code_from_memory( const void* /*src*/,
                                            const fn_info* /*fn_details*/,
                                            size_t /*file_hdr_size*/,
                                            void* /*dest*/ );
extern loaded_fn_ptr load_code_from_channel( Channel* /*in_channel*/,
                                             const fn_info* /*fn_details*/,
                                             void* /*dest*/ );

#endif

/* end of fnload.h */
