/* %W% %G% */

/* ocloader.c */
/* Copyright (C) INMOS Ltd, 1992 */


/********************************* NOTES *************************************

Key to this loader is the use of the dynamic code loading routines
get_code_details_from_channel and load_code_from_channel.  This loader
is compiled, linked, configured and collected into a bootable file onto
which is concatenated a .rsc file, thus effectively converting the .rsc
file into a bootable file.  This loader should be linked with the
reduced library with main entry point C.ENTRYD.RC; the linker indirect
file cstartrd.lnk encapsulates this.

The interface of the .rsc file is assumed to be (in occam):

  PROC procedure.identifier( CHAN OF SP from.server, to.server,
                             []INT free.memory )

where

  PROTOCOL SP IS INT16::[]BYTE :

It is assumed that the program comes from the occam system and so does
not have a runtime system associated with it and, especially, does not
move the stack.

This loader assumes that it has been configured for one processor.  But
it also assumes that the configuration description was a lie: it must
find out the boot/host link itself, and just how much memory there is
attached the processor (e.g. via an environment variable).  This is the
only way that this loader can be generally useful as a bootable file.

The algorithm that this loader uses is:

 1) find out the channels associated with link that booting actually
    occurred on
 2) read the header of the .rsc file that is assumed to be waiting on
    the input channel
 3) find out where free space begins
 4) read the rest of the .rsc file (the code block) from the input
    channel and put it into the free space - making the assumption
    that there will be enough free space for it
 5) calculate new beginning of free space
 6) determine the end of free space by some method, e.g. use of an
    environment variable
 7) alter the position of the stack to use what free space there is
 8) call the .rsc file's code with appropriate parameters.

****************************************************************************/


#include <stddef.h>   /* for size_t */
#include <limits.h>   /* for maxima of unsigned ints macros */
#include <channel.h>  /* for Channel*, ChanIn and ChanOut */
#include <misc.h>     /* for call_without_gsb and halt_processor */
#include <fnload.h>   /* for the dynamic code loading routines and fn_info */
#include <bootlink.h> /* for get_bootlink_channels */
#include <string.h>   /* for strlen and strcpy */


#define NUMBER_OF_BITS_IN_BYTE        8
#define MIN_SP_TRANSACTION_SIZE       8
#define MAX_SP_TRANSACTION_SIZE     510
#define GETENV_TAG                   32
#define WRITE_TAG                    13
#define SERVER_SUCCESS                0
#define FATAL                       "Fatal-loader-"


enum stream { STDOUT = 1, STDERR = 2 };
typedef enum stream stream;


#if 0   /* useful debugging routine */
/******************************** size_ttostr ********************************/
static void size_ttostr( size_t n, char* str )
/*
    Purpose:  To convert an unsigned integer into a string.
    In:       n - the unsigned integer to be converted into a string
    Out:      str - points to the base of an array large enough to
              accommodate the desired string
    Notes:    It is assumed that there is enough space for the string to
              be written to.
              A null terminating character is written into the array str.
              The string is in decimal format.
              The largest unsigned long int of 32-bits is 4294967295, which,
              with a terminating null character, is 11 characters.
*/
{
  /* do not use recursion so that the stack size can be known in advance */
  int i;

  str[0] = '\0';
  i = 1;
  do
    {
      str[i] = (int)('0' + n % 10 );
      n /= 10;
      i++;
    } while (n != 0);
  /*
   * The string is in reverse order in str; there are i (>= 2) characters
   * in the string.
   */
  {
    /* reverse the order of characters in the string */
    int a, b;

    a = 0; b = i - 1;
    do
      {
        char temp;

        temp = str[a];
        str[a] = str[b];
        str[b] = temp;
        a++; b--;
      } while ( a < b );
  }
}
#endif  /* useful debugging routine */


/**************************** valid_decimal_digit ****************************/
static int valid_decimal_digit( char ch, int* value_ptr )
/*
   Purpose:  To convert a decimal character to its int representation.
   Returned: 0 if the given digit is a valid decimal character; non-zero
             otherwise.
   In:       ch - the character to convert
   Out:      *value_ptr - ch converted to int, if operation successful;
             undefined otherwise
*/
{
  if ( ('0' <= ch) && (ch <= '9') )
    {
      *value_ptr = (int)(ch - '0');
      return 0;
    }
  else
    return 1;
}


/****************************** valid_hex_digit ******************************/
static int valid_hex_digit( char ch, int* value_ptr )
/*
   Purpose:  To convert a hexadecimal character to its int representation.
   Returned: 0 if the given digit is a valid hexadecimal character; non-zero
             otherwise.
   In:       ch - the character to convert
   Out:      *value_ptr - ch converted to int, if operation successful;
             undefined otherwise
   Notes:    The case of ch, if a letter, is not significant.
*/
{
  if ( ('0' <= ch) && (ch <= '9') )
    {
      *value_ptr = (int)(ch - '0');
      return 0;
    }
  else
    if ( ('a' <= ch) && (ch <= 'f') )
      {
        *value_ptr = (int)(ch - ('a' - 10));
        return 0;
      }
    else
      if ( ('A' <= ch) && (ch <= 'F') )
        {
          *value_ptr = (int)(ch - ('A' - 10));
          return 0;
        }
      else
        return 1;
}


/******************************** strtosize_t ********************************/
static int strtosize_t( const char* string, int size_of_string,
                        int base, size_t* n_ptr )
/*
   Purpose:  To convert a string into a size_t representation.
   Returned: 0 if (i)   no invalid chars found in the given string;
                  (ii)  no overflow;
                  (iii) size_of_string > 0;
             non-zero otherwise.
   In:       string - a pointer to the start of an array of characters
   In:       size_of_string - the number of characters in the char array,
             not counting any null terminator
   In:       base - 10 if the char array in decimal format; 16 if the
             char array in hexadecimal format
   Out:      *n_ptr - the result of the conversion, defined as long as
             the operation succeeded; undefined otherwise
   Notes:    string does not need to be null terminated
             It is assumed that there is no white-space in string, nor
             any special first character indicating hex.
             Behaviour is undefined if base is not 10 or 16.
*/
{
  /*  The way that the assignment to size_t_max is constructed might
   *  generate an 'implicit narrowing cast' warning.  We construct
   *  size_t_max this way to avoid using any knowledge about which
   *  unsigned integral type size_t actually is.
   */
  const size_t size_t_max =
                (sizeof(size_t) == sizeof(unsigned short)) ? USHRT_MAX :
                (sizeof(size_t) == sizeof(unsigned int))   ? UINT_MAX  :
                                                             ULONG_MAX ;
  int error;
  int chars_scanned; /* counts number of valid digits in string */
  int digit;


  *n_ptr = 0;
  error = (size_of_string <= 0);
  chars_scanned = 0;

  while ( (chars_scanned < size_of_string) &&
          ((base == 10) ? (valid_decimal_digit(string[chars_scanned], &digit) == 0) :
                          (valid_hex_digit(string[chars_scanned], &digit) == 0)) )
    {
      if ( *n_ptr <= ((size_t_max - digit) / base) )
        {
          *n_ptr = (*n_ptr * base) + digit;
          chars_scanned++;
        }
      else
        break;
    }
  error |= (chars_scanned < size_of_string);
  return error;
}


/******************************* sp_transaction *******************************/
static int sp_transaction( Channel* in, Channel* out,
                           char* message, int message_length,
                           char* reply )
/*
  Purpose:  To send and receive messages using sp protocol on the
            given channels.
  Returned: The length in bytes of the reply, or -1 if an error
            occurs.
  In:       *in - the outwards communication channel
  In:       *out - the inwards communication channel
  In:       message - points to an array of characters which is the
            message to send
  In:       message_length - the number of characters in the array
            pointed to by message; should be >= 8, <= 510, and even
  Out:      reply - points to the array in which the reply is stored
  Notes:    If the array reply is not large enough for the reply then
            the behaviour is undefined.
            This routine does not replace server_transaction which
            performs much safer communication with the server, but
            which is not in the reduced library.
            sp protocol is the counted array protocol INT16::[]BYTE
            (in occam).
*/
{
  if ( (message_length < MIN_SP_TRANSACTION_SIZE) ||
       (message_length > MAX_SP_TRANSACTION_SIZE) ||
       (message_length % 2 != 0) )
    return -1;
  else
    {
      int count;

      /* send message using counted array protocol */
      ChanOut( out, (void*)&message_length, 2 );
      ChanOut( out, (void*)message, message_length );

      /* receive message using counted array protocol */
      ChanIn( in, (void*)reply, 2 );
      count = (int)reply[0] | ( ((int)reply[1]) << NUMBER_OF_BITS_IN_BYTE );
      ChanIn( in, (void*)reply, count );
      return count;
    }
}


/******************************* output_message *******************************/
static void output_message( Channel* in, Channel* out,
                            stream output_stream,
                            char* string )
/*
  Purpose:  To send a string to either stdout or stderr.
  In:       *in -  the communication channel from the server
  In:       *out - the communication channel to the server
  In:       output_stream - if STDOUT then the string is sent to
            stdout; if STDERR the string is sent to stderr
  In:       string - points to a string which is to be output
  Notes:    The string size is limited to 255 bytes; if it is
            greater than this then the behaviour is undefined
*/
{
  char server_packet[7 + 255];
  int send_size;

  server_packet[0] = WRITE_TAG;
  server_packet[1] = output_stream;
  server_packet[2] = 0;
  server_packet[3] = 0;
  server_packet[4] = 0;

  server_packet[5] = strlen( string );
  server_packet[6] = 0;
  strcpy(&server_packet[7], string);
  send_size = 7 + server_packet[5]; /* total length of packet */
  send_size = send_size + (send_size % 2); /* make sure even */

  (void)sp_transaction( in, out, server_packet, send_size, server_packet );
}


/****************************** get_memory_size *******************************/
static size_t get_memory_size( Channel* in, Channel* out )
/*
    Purpose:  To obtain the size in bytes of the memory attached
              to the processor that this code is running on.
    Returned: The size in bytes of the memory attached to the
              processor that this code is running on.
    In:       in - a pointer to the channel from the server
    In:       out - a pointer to the channel to the server
    Notes:    The method used here is to find out the value of an
              environment variable.  The environment variable that
              is looked for is IBOARDSIZE.  Its value can be in
              decimal or in hex, the latter indicated by a first
              character of '$' or '#'.  No whitespace is allowed
              in the value of IBOARDSIZE.
*/
{
#define ENVIRONMENT_VARIABLE_NAME  "IBOARDSIZE"

  int reply_size;
  char server_packet[MAX_SP_TRANSACTION_SIZE];

  {
    int send_size;

    server_packet[0] = GETENV_TAG;
    server_packet[1] = strlen( ENVIRONMENT_VARIABLE_NAME );
    server_packet[2] = 0;
    strcpy( &server_packet[3], ENVIRONMENT_VARIABLE_NAME );
    send_size = 3 + server_packet[1]; /* total length of packet */
    send_size = send_size + (send_size % 2); /* make sure even */

    reply_size = sp_transaction( in, out, server_packet, send_size,
                                                     server_packet );
  }

  if ( reply_size > sizeof(server_packet) )
    halt_processor(); /* memory will have been written over */
  else
    if ( server_packet[0] != SERVER_SUCCESS )
      {
        output_message( in, out, STDERR,
                        FATAL "unable to read " ENVIRONMENT_VARIABLE_NAME "\n" );
        halt_processor();
      }
    else
      {
        /* obtained characters that we can do something with */
        size_t mem_size;
        int count;
        int base;
        char* start_of_string; /* Note that no there is no null terminating
                                * byte to the characters obtained from
                                * the server call.
                                */

        count = (int)server_packet[1] |
                ( ((int)server_packet[2]) << NUMBER_OF_BITS_IN_BYTE );
        /*
         *  count now gives the number of characters in the returned
         *  block of bytes.
         */
        if ( (server_packet[3] == '$') || (server_packet[3] == '#') )
          {
            base = 16;
            count--; /* take account of '$'/'#' */
            start_of_string = &server_packet[4];
          }
        else
          {
            base = 10;
            start_of_string = &server_packet[3];
          }
        /*
         * strtoul could be used instead of strtosize_t but it
         * does a lot of unnecessary checking.
         */
        if ( strtosize_t( start_of_string, count, base, &mem_size ) != 0 )
          {
            output_message( in, out, STDERR,
                    FATAL "illegal " ENVIRONMENT_VARIABLE_NAME "\n" );
            halt_processor();
          }
        else
          return mem_size;
      }
}


/**************************** call_type0_interface ****************************/
static void call_type0_interface( void (*fn_ptr)(void),
                                  size_t ws, size_t vs,
                                  Channel* in, Channel* out,
                                  void* base_of_free_memory,
                                  size_t amount_of_free_memory )
/*
   Purpose:  To call the given occam procedure of fixed interface after
             having set up its parameters and vectorspace and workspace
             areas.
   In:       fn_ptr - a pointer to the start of the occam procedure
             that is to be called
   In:       ws - the amount of workspace required by the occam procedure,
             in bytes such that ws % sizeof(int) == 0
   In:       vs - the amount of vectorspace required by the occam procedure,
             in bytes such that vs % sizeof(int) == 0
   In:       in - a pointer to the channel from the server
   In:       out - a pointer to the channel to the server
   In:       base_of_free_memory - the address of the base of free memory
             on entry to this function, that is, the base before any workspace
             or vectorspace has been allocated
   In:       amount_of_free_memory - the size in bytes of the free memory on
             entry to this function, that is, the size before any workspace
             or vectorspace has been allocated, such that
             amount_of_free_memory % sizeof(int) == 0
   Notes:    A type0 occam interface is

                PROC procedure.identifier( CHAN OF SP from.server, to.server,
                                           []INT free.memory )

             Memory is set out by this function as follows, this being the
             position just before call to the occam procedure:


                                 top of memory            size in bytes
                            ------------------------           .
                           |                        |         / \
                           |                        |          |
                           |          free          |          |
                           |         memory         | amount_of_free_memory
                           |                        |          |
                           |                        |          |
   base_of_free_memory --> |------------------------|          V
                           |                        |          ^
                           |                        |          |
                           |      vectorspace       |          |
                           |                        |         vs
                           |                        |          |
                           |                        |          |
                           |------------------------|          V
                           |       old Wptr         |     sizeof(int)
                           |------------------------|
                           |   &vectorspace_base    |     sizeof(int)
                           |------------------------|
                           | amount_of_free_memory  |     sizeof(int)
                           |    * sizeof(int)       |
                           |------------------------|
                           |  base_of_free_memory   |     sizeof(int)
                           |------------------------|
                           |         out            |     sizeof(int)
                           |------------------------|
                           |         in             |     sizeof(int)
                           |------------------------|
              new_Wptr --> |     return address     |     sizeof(int)
                           |------------------------|
                           |                        |          ^
                           |                        |          |
                           |                        |          |
                           |       workspace        |         ws
                           |                        |          |
        original           |                        |          |
   base_of_free_memory --> |------------------------|          V
                           |                        |
                           |                        |



       original base_of_free_memory is where base_of_free_memory points on
       entry to this function, so that amount_of_free_memory on entry to this
       function is equal to the sum of amount_of_free_memory in the above
       diagram plus ws plus vs plus 7*sizeof(int).  If there is not enough
       free memory on entry to accommodate the workspace, vectorspace and
       the setup block, then an error message is generated and the processor
       halted.
*/
{
#define NUMBER_OF_WORDS_IN_SETUP_BLOCK 7
#define OFFSET_OF_OLD_WPTR_FROM_NEW    6

  void* new_Wptr;
  void* vectorspace_base;
  const size_t size_of_setup_block_in_bytes =
                                  NUMBER_OF_WORDS_IN_SETUP_BLOCK * sizeof(int);


  new_Wptr = (void*)((unsigned char*)base_of_free_memory + ws);
  vectorspace_base = (void*)((unsigned char*)new_Wptr + size_of_setup_block_in_bytes);
  base_of_free_memory = (void*)((unsigned char*)vectorspace_base + vs);
  if (amount_of_free_memory < ws + vs + size_of_setup_block_in_bytes)
    {
      output_message( in, out, STDERR,
                      FATAL "not enough memory to run program\n" );
      halt_processor();
    }
  else
    {
      amount_of_free_memory = amount_of_free_memory - ws - vs - size_of_setup_block_in_bytes;
      __asm
        {
          ldlabeldiff return_statement - here;  /* Areg = difference between
                                                   address of the two labels
                                                 */
          ldpi;                                 /* Areg = address of the statement
                                                   labelled by return_statement
                                                 */
        here:
          st *(void**)((int*)new_Wptr + 0);     /* store the return address
                                                 */
        }
      
      
          *(Channel**)((int*)new_Wptr + 1) = in; /* from.server */
          *(Channel**)((int*)new_Wptr + 2) = out; /* to.server */
             *(void**)((int*)new_Wptr + 3) = base_of_free_memory;
               *(int*)((int*)new_Wptr + 4) = (int)(amount_of_free_memory / sizeof(int)); /* words */
             *(void**)((int*)new_Wptr + 5) = vectorspace_base;
      
      
      __asm
        {
          ldab new_Wptr, fn_ptr;           /*
                                              Areg = new_Wptr;
                                              Breg = fn_ptr;
                                              Creg = undefined;
                                            */
          gajw;                            /*
                                              Wptr = new_Wptr;
                                              Areg = old Wptr;
                                              Breg = fn_ptr;
                                              Creg = undefined;
                                            */
          stl OFFSET_OF_OLD_WPTR_FROM_NEW; /*
                                              store old Wptr in ((int*)new_Wptr + OFFSET_OF_OLD_WPTR_FROM_NEW);
                                              Areg = fn_ptr;
                                              Breg = undefined;
                                              Creg = undefined;
                                            */
          gcall;                           /*
                                              call function pointed to by fn_ptr
                                            */
        return_statement:
          ldl (OFFSET_OF_OLD_WPTR_FROM_NEW - 4);
                                           /* 
                                              Areg = old Wptr;
                                              Breg = undefined;
                                              Creg = undefined;
                                              assuming that called routine
                                              followed conventions; the 4 is
                                              the 4 that 'ret' adds to the Wptr
                                            */
          gajw;                            /*
                                              restore old Wptr to allow this
                                              routine to return correctly
                                            */
        }
    }
}



/********************************* main *************************************/
int main( void )
/*
     argv and argc should not be used as any such parameters are for
     use by the application code.
 */
{
  Channel* in;  /* pointer to the input channel associated with the boot/host link */
  Channel* out; /* pointer to the output channel associated with the boot/host link */
  fn_info fn_details; /* the structure that contains details of the
                         .rsc file that is read over the boot link */


  /* find out dynamically which link was used for booting */
  if (get_bootlink_channels( &in, &out ) != 0)
    halt_processor(); /*  Cannot output an error message as the server is
                       *  not listening to the link - as far as the server
                       *  is concerned it is still booting.  (It probably
                       *  isn't monitoring the error flag either!)
                       */
  if (get_code_details_from_channel( in, &fn_details ) != 0)
    halt_processor(); /* server still not listening */

  {
    void* const bottom_of_memory =
          /* the lowest address in the address space:
           * 0x8000 on 16-bit processor; 0x80000000 on 32-bit processor
           */
          (void* const)(1u << (sizeof(int) * NUMBER_OF_BITS_IN_BYTE - 1));
    loaded_fn_ptr ptr_to_occam_proc;
    size_t amount_of_free_memory;
    size_t total_amount_of_memory;
    size_t amount_of_memory_used;
    void*  base_of_free_space;
  
  
    if (get_details_of_free_memory( &base_of_free_space,
         &amount_of_free_memory /* dummy as value not used */ ) != 0 )
      halt_processor(); /* server still not listening */

    /* assume that there is enough free memory */
    ptr_to_occam_proc = load_code_from_channel( in, &fn_details,
                                                base_of_free_space );
    /*
     * The boot link should now be free for communication with the server;
     * we assume that the boot link and the link over which the host
     * services are obtained are the same - we cannot do anything else.
     */
  
    /*
     * Base of free space has now changed because we have loaded code
     * into the free space starting at its old base - calculate the
     * new base.
     */
    base_of_free_space = (void*)((unsigned char *)base_of_free_space +
                                 fn_details.code_size);
    /*
     * The original base_of_free_space (as calculated by the configurer)
     * is word aligned and the code_size is word sized (because the code
     * in linked units is word sized), so the new base_of_free_space 
     * is word aligned.  We need word alignment because the array in
     * the occam interface to the .rsc file is an INT array.
     */
  
    /* now for the top of free memory */
    total_amount_of_memory = get_memory_size( in, out );
    amount_of_memory_used  = (size_t)((unsigned char*)base_of_free_space -
                                      (unsigned char*)bottom_of_memory);
    if ( amount_of_memory_used > total_amount_of_memory )
      {
        output_message( in, out, STDERR,
                        FATAL "top of memory overrun\n" );
        halt_processor();
      }
    else
      {
        amount_of_free_memory = get_memory_size( in, out ) -
                    (size_t)((unsigned char*)base_of_free_space -
                             (unsigned char*)bottom_of_memory);
        /* word align the top of free memory */
        amount_of_free_memory = amount_of_free_memory -
                                (amount_of_free_memory % sizeof(int));

        call_type0_interface( ptr_to_occam_proc,
                              fn_details.stack_size,
                              fn_details.vectorspace_size,
                              in, out,
                              base_of_free_space,
                              amount_of_free_memory );
        #if 0 /* leave the called program to terminate the server */
        {
          #define EXIT_TAG  35
          char exit_packet[5] = {EXIT_TAG, 0, 0, 0, 0}; /* tag, then status */

          (void)sp_transaction( in, out, exit_packet, 8, exit_packet );
        }
        #endif /* leave the called program to terminate the server */
      }
  }
}
