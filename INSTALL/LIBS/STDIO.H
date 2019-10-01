/* @(#)stdio.h	1.4 9/23/92 */

/* stdio.h: ANSI X3.159 1989 library header, section 4.9 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __stdio_h
#define __stdio_h

#ifndef __size_t
#define __size_t 1
typedef unsigned int size_t;   /* from <stddef.h> */
#endif

typedef char *__va_list[1];

#ifndef NULL
#  define NULL (void *)0                /* see <stddef.h> */
#endif

typedef struct __fpos_t_struct
{ unsigned long __lo;
} fpos_t;

struct _IMS_FILE_struct;
typedef struct _IMS_FILE_struct FILE;

#define _IOFBF    0x100 /* fully buffered IO */
#define _IOLBF    0x200 /* line buffered IO */
#define _IONBF    0x400 /* unbuffered IO */
#define _IOEOF     0x40 /* end-of-file reached */
#define _IOERR     0x80 /* error occurred on stream */

#if _PTYPE == '2' || _PTYPE == '3'
#define BUFSIZ   (1024) /* system buffer size (as used by setbuf) */
#else
#define BUFSIZ   (4096) /* system buffer size (as used by setbuf) */
#endif
#define EOF      (-1)
#define FOPEN_MAX 16
#define FILENAME_MAX 64
#define L_tmpnam 20

#define SEEK_SET 0 /* start of stream (see fseek) */
#define SEEK_CUR 1 /* current position in stream (see fseek) */
#define SEEK_END 2 /* end of stream (see fseek) */

#define TMP_MAX 0x7fff

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

extern int remove(const char * /*filename*/);
extern int rename(const char * /*old*/, const char * /*new*/);
extern FILE *tmpfile(void);
extern char *tmpnam(char * /*s*/);
extern int fclose(FILE * /*stream*/);
extern int fflush(FILE * /*stream*/);
extern FILE *fopen(const char * /*filename*/, const char * /*mode*/);
extern FILE *freopen(const char * /*filename*/, const char * /*mode*/,
                     FILE * /*stream*/);
extern void setbuf(FILE * /*stream*/, char * /*buf*/);
extern int setvbuf(FILE * /*stream*/, char * /*buf*/,
                   int /*mode*/, size_t /*size*/);

#pragma IMS_on(printf_checking)   

extern int fprintf(FILE * /*stream*/, const char * /*format*/, ...);
extern int printf(const char * /*format*/, ...);
extern int sprintf(char * /*s*/, const char * /*format*/, ...);

#pragma IMS_off(printf_checking)  
#pragma IMS_on(scanf_checking)   

extern int fscanf(FILE * /*stream*/, const char * /*format*/, ...);
extern int scanf(const char * /*format*/, ...);
extern int sscanf(const char * /*s*/, const char * /*format*/, ...);

#pragma IMS_off(scanf_checking)  

extern int vprintf(const char * /*format*/, __va_list /*arg*/);
extern int vfprintf(FILE * /*stream*/,
                   const char * /*format*/, __va_list /*arg*/);
extern int vsprintf(char * /*s*/, const char * /*format*/, __va_list /*arg*/);
extern int fgetc(FILE * /*stream*/);
extern char *fgets(char * /*s*/, int /*n*/, FILE * /*stream*/);
extern int fputc(int /*c*/, FILE * /*stream*/);
extern int fputs(const char * /*s*/, FILE * /*stream*/);
extern int getc(FILE * /*stream*/);

#define getchar() getc(stdin)

extern int (getchar)(void);
extern char *gets(char * /*s*/);

extern int putc(int /*c*/, FILE * /*stream*/);

#define putchar(ch) putc(ch, stdout)

extern int (putchar)(int /*c*/);
extern int puts(const char * /*s*/);
extern int ungetc(int /*c*/, FILE * /*stream*/);
extern size_t fread(void * /*ptr*/,
                    size_t /*size*/, size_t /*nmemb*/, FILE * /*stream*/);
extern size_t fwrite(const void * /*ptr*/,
                    size_t /*size*/, size_t /*nmemb*/, FILE * /*stream*/);
extern int fgetpos(FILE * /*stream*/, fpos_t * /*pos*/);
extern int fseek(FILE * /*stream*/, long int /*offset*/, int /*whence*/);
extern int fsetpos(FILE * /*stream*/, const fpos_t * /*pos*/);
extern long int ftell(FILE * /*stream*/);
extern void rewind(FILE * /*stream*/);
extern void clearerr(FILE * /*stream*/);

extern int feof(FILE * /*stream*/);

extern int ferror(FILE * /*stream*/);
extern void perror(const char * /*s*/);

#endif

/* end of stdio.h */
