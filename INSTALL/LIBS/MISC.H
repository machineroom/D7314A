/* @(#)misc.h	1.12 9/22/92 */

/* misc.h */
/* Copyright (C) Inmos Ltd. 1989 */

#ifndef __misc_h
#define __misc_h 1

#include <stddef.h>

#pragma IMS_translate(exit_repeat, "exit_repeat%c")
#pragma IMS_translate(exit_terminate, "exit_terminate%c")
#pragma IMS_translate(exit_noterminate, "exit_noterminate%c")
#pragma IMS_translate(set_abort_action, "set_abort_action%c")
#pragma IMS_translate(debug_message, "debug_message%c")
#pragma IMS_translate(debug_assert, "debug_assert%c")
#pragma IMS_translate(debug_stop, "debug_stop%c")
#pragma IMS_translate(max_stack_usage, "max_stack_usage%c")
#pragma IMS_translate(get_details_of_free_stack_space, \
                      "get_details_of_free_stack_space%c")
#pragma IMS_translate(get_details_of_free_memory, \
                      "get_details_of_free_memory%c" )
#pragma IMS_translate(get_param, "get_param%c")
#pragma IMS_translate(BitCnt, "BitCnt%c")
#pragma IMS_translate(BitCntSum, "BitCntSum%c")
#pragma IMS_translate(BitRevNBits, "BitRevNBits%c")
#pragma IMS_translate(BitRevWord, "BitRevWord%c")
#pragma IMS_translate(CrcByte, "CrcByte%c")
#pragma IMS_translate(CrcWord, "CrcWord%c")
#pragma IMS_translate(CrcFromMsb, "CrcFromMsb%c")
#pragma IMS_translate(CrcFromLsb, "CrcFromLsb%c")
#pragma IMS_translate(BlockMove, "BlockMove%c")
#pragma IMS_translate(Move2D, "Move2D%c")
#pragma IMS_translate(Move2DNonZero, "Move2DNonZero%c")
#pragma IMS_translate(Move2DZero, "Move2DZero%c")
#pragma IMS_translate(_halt_processor, "halt_processor%c")
#pragma IMS_translate(call_without_gsb, "call_without_gsb%c")

extern void  exit_repeat(int /*n*/);
extern void  exit_terminate(int /*n*/);
extern void  exit_noterminate(int /*n*/);
extern int   set_abort_action(int /*n*/);
extern void  debug_message(const char * /*message*/);
extern void  debug_assert(const int /*expression*/);
extern void  debug_stop(void);
extern void *get_param(int /*n*/);
extern long  max_stack_usage(void);
extern void  get_details_of_free_stack_space(void ** /*stack_limit_ptr*/,
                                             size_t * /*left_stack_space_ptr*/);
extern int   get_details_of_free_memory(void ** /*base_of_free_memory*/,
                                        size_t* /*size_of_free_memory*/ );
extern int   BitCnt(int /*word*/);
extern int   BitCntSum(int /*word*/, int /*count_in*/);
extern int   BitRevNBits(int /*numbits*/, int /*data*/);
extern int   BitRevWord(int /*data*/);
extern int   CrcByte(int /*data*/, int /*crc_in*/, int /*generator*/);
extern int   CrcWord(int /*data*/, int /*crc_in*/, int /*generator*/);
extern int   CrcFromMsb(const char * /*string*/, size_t /*length*/, 
                        int /*generator*/, int /*old_crc*/);
extern int   CrcFromLsb(const char * /*string*/, size_t /*length*/, 
                        int /*generator*/, int /*old_crc*/);
extern void  BlockMove(void * /*dest*/, const void * /*source*/, size_t /*n*/);
extern void  Move2D(const void * /*src*/, void * /*dst*/, int /*width*/,
                    int /*nrows*/, int /*srcwidth*/, int /*dstwidth*/);
extern void  Move2DNonZero(const void * /*src*/, void * /*dst*/, int /*width*/,
                           int /*nrows*/, int /*srcwidth*/, int /*dstwidth*/);
extern void  Move2DZero(const void * /*src*/, void * /*dst*/, int /*width*/,
                        int /*nrows*/, int /*srcwidth*/, int /*dstwidth*/);
void         _halt_processor(void);
void         call_without_gsb(void (* /*fn_ptr*/)(void),
                              int /*number_of_words_for_parameters*/, ...);

#pragma IMS_nolink(call_without_gsb)
#pragma IMS_nolink(_halt_processor)

#define halt_processor() (_halt_processor())

#pragma IMS_builtin_inline(BitCnt)
#pragma IMS_builtin_inline(BitCntSum)
#pragma IMS_builtin_inline(BitRevNBits)
#pragma IMS_builtin_inline(BitRevWord)
#pragma IMS_builtin_inline(CrcByte)
#pragma IMS_builtin_inline(CrcWord)
#pragma IMS_builtin_inline(BlockMove)
#pragma IMS_builtin_inline(Move2D)
#pragma IMS_builtin_inline(Move2DNonZero)
#pragma IMS_builtin_inline(Move2DZero)

#pragma IMS_nosideeffects(max_stack_usage)
#pragma IMS_nosideeffects(get_param)
#pragma IMS_nosideeffects(BitCnt)
#pragma IMS_nosideeffects(BitCntSum)
#pragma IMS_nosideeffects(BitRevNBits)
#pragma IMS_nosideeffects(BitRevWord)
#pragma IMS_nosideeffects(CrcByte)
#pragma IMS_nosideeffects(CrcWord)

#define ABORT_EXIT  0
#define ABORT_HALT  1
#define ABORT_QUERY 2

#endif

