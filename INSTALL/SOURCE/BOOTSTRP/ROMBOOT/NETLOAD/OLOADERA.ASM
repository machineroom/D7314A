-- occam 2 compiler Version 2.01.67 (10:48:37 Jul  9 1992) (SunOS-Sun4)
-- Compiling (TA,UNIVERSAL) "oloader.occ"

	j       $Overlaying.loader	-- jump to entrypoint
L0:	-- section label	-- PROC get.command, lexlevel: 1, WS: 2, VS: 0
	-- "oloader.occ": 88
	ldl     1	-- staticlink
	ldnl    18	-- network.data.pointer
	ldnl    0
	ldl     1	-- staticlink
	ldnl    21	-- network.data
	bsub    
	lb      
	ldl     1	-- staticlink
	stnl    1	-- command
	-- "oloader.occ": 89
	ldl     1	-- staticlink
	ldnl    18	-- network.data.pointer
	ldnl    0
	adc     1
	ldl     1	-- staticlink
	ldnl    18	-- network.data.pointer
	stnl    0
	ret     
L1:	-- section label	-- PROC get.memory, lexlevel: 1, WS: 2, VS: 0
	-- "oloader.occ": 96
	ldl     1	-- staticlink
	ldnl    18	-- network.data.pointer
	ldnl    0
	ldl     1	-- staticlink
	ldnl    21	-- network.data
	bsub    
	ldl     2	-- at
	ldl     1	-- staticlink
	ldnl    22	-- memory
	bsub    
	ldl     3	-- len
	move    
	-- "oloader.occ": 98
	ldl     1	-- staticlink
	ldnl    18	-- network.data.pointer
	ldnl    0
	ldl     3	-- len
	add     
	ldl     1	-- staticlink
	ldnl    18	-- network.data.pointer
	stnl    0
	ret     
L2:	-- section label	-- PROC Get.encoded.value, lexlevel: 1, WS: 7, VS: 0
	ajw     -1
	-- "oloader.occ": 111
	ldc     0
	stl     0	-- more
	-- "oloader.occ": 113
	ldc     0
	ldl     3	-- value
	stnl    0
	-- "oloader.occ": 114
	ldc     1
	stl     0	-- more
	-- "oloader.occ": 115
L3:
	ldl     0	-- more
	cj      L4
	-- "oloader.occ": 117
	ldl     3	-- value
	ldnl    0
	bcnt    
	bcnt    
	bcnt    
	ldl     3	-- value
	stnl    0
	-- "oloader.occ": 118
	ldl     2	-- staticlink
	call    L0	-- Call get.command
	-- "oloader.occ": 119
	ldl     3	-- value
	ldnl    0
	ldl     2	-- staticlink
	ldnl    1	-- command
	ldc     63
	and     
	bsub    
	ldl     3	-- value
	stnl    0
	-- "oloader.occ": 120
	ldc     192
	ldl     2	-- staticlink
	ldnl    1	-- command
	gt      
	eqc     0
	stl     0	-- more
	j       L3
L4:
	ajw     1
	ret     
L5:	-- section label	-- PROC ClearByteBuffer, lexlevel: 1, WS: 4, VS: 0
	ajw     -2
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	ldc     1
	stl     0	-- Count
	-- "oloader.occ": 443
	ldl     0	-- Count
	stl     1	-- Index
	-- "oloader.occ": 443
	ldl     5	-- Value
	ldl     3	-- Buffer
	sb      
	-- "oloader.occ": 443
L6:
	ldl     4	-- $temp-1
	ldl     1	-- Index
	gt      
	cj      L7
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	ldl     0	-- Count
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	gt      
	cj      L9
	-- "oloader.occ": 443
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	stl     0	-- Count
	j       L8
L9:
	-- "oloader.occ": 443
L8:
	-- "oloader.occ": 443
	ldl     3	-- Buffer
	ldl     1	-- Index
	ldl     3	-- Buffer
	bsub    
	ldl     0	-- Count
	move    
	-- "oloader.occ": 443
	ldl     1	-- Index
	ldl     0	-- Count
	bsub    
	stl     1	-- Index
	-- "oloader.occ": 443
	ldl     0	-- Count
	ldl     0	-- Count
	bsub    
	stl     0	-- Count
	j       L6
L7:
	ajw     2
	ret     
L10:	-- section label	-- PROC Overlaying.loader, lexlevel: 0, WS: 30, VS: 0
$Overlaying.loader:
	global $Overlaying.loader
	descriptor $Overlaying.loader "Overlaying.loader" occam 30 0 "PROC Overlaying.loader([4]CHAN OF ANY links,[4]BYTE network.data,
[4]BYTE memory,VAL INT Buffer.address,[5]INT Exported.data)
  SEQ
    links!
:"
	ajw     -19
	-- "oloader.occ": 15
	-- "oloader.occ": 16
	-- "oloader.occ": 17
	-- "oloader.occ": 18
	-- "oloader.occ": 19
	-- "oloader.occ": 22
	ldl     24	-- Exported.data
	stl     18	-- network.data.pointer
	-- "oloader.occ": 23
	ldl     24	-- Exported.data
	ldnlp   1
	stl     17	-- Next.address
	-- "oloader.occ": 24
	ldl     24	-- Exported.data
	ldnlp   2
	stl     15	-- Entry.point
	-- "oloader.occ": 25
	ldl     24	-- Exported.data
	ldnlp   3
	stl     14	-- Data.point
	-- "oloader.occ": 26
	ldl     24	-- Exported.data
	ldnlp   4
	stl     16	-- Invocation.stack
	-- "oloader.occ": 29
	-- "oloader.occ": 30
	-- "oloader.occ": 31
	-- "oloader.occ": 32
	-- "oloader.occ": 33
	-- "oloader.occ": 34
	-- "oloader.occ": 35
	-- "oloader.occ": 36
	-- "oloader.occ": 37
	-- "oloader.occ": 38
	-- "oloader.occ": 39
	-- "oloader.occ": 40
	-- "oloader.occ": 42
	-- "oloader.occ": 43
	-- "oloader.occ": 44
	-- "oloader.occ": 45
	-- "oloader.occ": 46
	-- "oloader.occ": 47
	-- "oloader.occ": 48
	-- "oloader.occ": 49
	-- "oloader.occ": 50
	-- "oloader.occ": 51
	-- "oloader.occ": 53
	-- "oloader.occ": 54
	-- "oloader.occ": 55
	-- "oloader.occ": 57
	-- "oloader.occ": 58
	-- "oloader.occ": 60
	-- "oloader.occ": 61
	-- "oloader.occ": 63
	-- "oloader.occ": 64
	-- "oloader.occ": 66
	-- "oloader.occ": 67
	-- "oloader.occ": 69
	-- "oloader.occ": 70
	-- "oloader.occ": 72
	-- "oloader.occ": 73
	-- "oloader.occ": 75
	-- "oloader.occ": 76
	-- "oloader.occ": 79
	ldc     0
	stl     1	-- command
	-- "oloader.occ": 80
	-- "oloader.occ": 81
	ldc     0
	stl     12	-- loading
	-- "oloader.occ": 231
	ldc     0
	ldl     18	-- network.data.pointer
	stnl    0
	-- "oloader.occ": 232
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "oloader.occ": 233
L11:
	ldc     133
	ldl     1	-- command
	diff    
	cj      L12
	-- "oloader.occ": 234
	-- "oloader.occ": 237
	ldl     1	-- command
	ldc     6
	shr     
	stl     13	-- tag
	-- "oloader.occ": 238
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "oloader.occ": 239
	-- "oloader.occ": 241
	ldl     13	-- tag
	eqc     0
	cj      L14
	-- "oloader.occ": 242
	-- "oloader.occ": 244
	-- "oloader.occ": 246
	ldl     12	-- loading
	cj      L16
	-- "oloader.occ": 248
	ldl     11	-- last.address
	stl     0	-- load.address
	-- "oloader.occ": 249
	ldl     0	-- load.address
	ldl     5	-- operand
	bsub    
	stl     11	-- last.address
	j       L15
L16:
	-- "oloader.occ": 251
	-- "oloader.occ": 252
	ldl     23	-- Buffer.address
	stl     0	-- load.address
	j       L15
L17:
L15:
	-- "oloader.occ": 254
	-- "oloader.occ": 255
	ldl     5	-- operand
	cj      L19
	-- "oloader.occ": 256
	ldl     5	-- operand
	ldl     0	-- load.address
	ldlp    0	-- staticlink
	call    L1	-- Call get.memory
	j       L18
L19:
	-- "oloader.occ": 257
L18:
	-- "oloader.occ": 260
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L20:
	-- "oloader.occ": 261
	-- "oloader.occ": 262
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L23
	-- "oloader.occ": 264
	ldlp    1	-- command
	ldl     2	-- i
	ldl     20	-- links
	wsub    
	ldc     1
	out     
	-- "oloader.occ": 265
	-- "oloader.occ": 266
	ldl     5	-- operand
	cj      L25
	-- "oloader.occ": 267
	ldl     0	-- load.address
	ldl     22	-- memory
	bsub    
	ldl     2	-- i
	ldl     20	-- links
	wsub    
	ldl     5	-- operand
	out     
	j       L24
L25:
	-- "oloader.occ": 268
L24:
	j       L22
L23:
	-- "oloader.occ": 270
L22:
	ldlp    2	-- i
	ldc     L21 - L20
	lend    
L21:
	j       L13
L14:
	-- "oloader.occ": 273
	ldl     13	-- tag
	eqc     2
	cj      L26
	-- "oloader.occ": 274
	-- "oloader.occ": 276
	ldl     5	-- operand
	eqc     0
	cj      L28
	-- "oloader.occ": 278
	ldc     1
	stl     12	-- loading
	-- "oloader.occ": 279
	ldc     0
	stl     4	-- links.to.load
	j       L27
L28:
	-- "oloader.occ": 281
	ldl     5	-- operand
	eqc     9
	cj      L29
	-- "oloader.occ": 283
	ldc     1
	stl     12	-- loading
	-- "oloader.occ": 284
	ldc     0
	stl     4	-- links.to.load
	j       L27
L29:
	-- "oloader.occ": 286
	ldl     5	-- operand
	eqc     7
	cj      L30
	-- "oloader.occ": 288
	ldc     1
	stl     12	-- loading
	-- "oloader.occ": 289
	ldc     0
	stl     4	-- links.to.load
	j       L27
L30:
	-- "oloader.occ": 291
	ldl     5	-- operand
	eqc     1
	cj      L31
	-- "oloader.occ": 293
	ldc     0
	stl     12	-- loading
	-- "oloader.occ": 294
	ldc     0
	stl     4	-- links.to.load
	j       L27
L31:
	-- "oloader.occ": 296
	ldl     5	-- operand
	eqc     2
	cj      L32
	-- "oloader.occ": 297
	-- "oloader.occ": 299
	ldc     1
	stl     0	-- depth
	-- "oloader.occ": 300
L33:
	ldl     0	-- depth
	cj      L34
	-- "oloader.occ": 302
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "oloader.occ": 303
	-- "oloader.occ": 304
	ldl     1	-- command
	eqc     130
	cj      L36
	-- "oloader.occ": 305
	ldl     0	-- depth
	ldc     1
	bsub    
	stl     0	-- depth
	j       L35
L36:
	-- "oloader.occ": 306
	ldl     1	-- command
	eqc     131
	cj      L37
	-- "oloader.occ": 307
	ldl     0	-- depth
	ldc     1
	diff    
	stl     0	-- depth
	j       L35
L37:
	-- "oloader.occ": 308
L35:
	-- "oloader.occ": 310
	-- "oloader.occ": 311
	ldl     0	-- depth
	cj      L39
	-- "oloader.occ": 312
	ldlp    1	-- command
	ldl     10	-- output.link
	ldl     20	-- links
	wsub    
	ldc     1
	out     
	j       L38
L39:
	-- "oloader.occ": 313
L38:
	j       L33
L34:
	j       L27
L32:
	-- "oloader.occ": 318
	ldl     5	-- operand
	eqc     4
	cj      L40
	-- "oloader.occ": 320
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	-- "oloader.occ": 321
	ldl     11	-- last.address
	ldl     17	-- Next.address
	stnl    0
	j       L27
L40:
	-- "oloader.occ": 323
	ldl     5	-- operand
	eqc     6
	cj      L41
	-- "oloader.occ": 325
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "oloader.occ": 326
	-- "oloader.occ": 327
	ldl     1	-- command
	eqc     0
	cj      L43
	-- "oloader.occ": 328
	ldl     14	-- Data.point
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	j       L42
L43:
	-- "oloader.occ": 329
	-- "oloader.occ": 330
	ldl     16	-- Invocation.stack
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	j       L42
L44:
L42:
	j       L27
L41:
	-- "oloader.occ": 332
	ldl     5	-- operand
	eqc     11
	cj      L45
	-- "oloader.occ": 334
	ldl     15	-- Entry.point
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	j       L27
L45:
	-- "oloader.occ": 336
	ldl     5	-- operand
	eqc     8
	cj      L46
	-- "oloader.occ": 338
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	-- "oloader.occ": 339
	ldl     11	-- last.address
	ldl     15	-- Entry.point
	stnl    0
	j       L27
L46:
	-- "oloader.occ": 341
	ldl     5	-- operand
	eqc     10
	cj      L47
	-- "oloader.occ": 343
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	-- "oloader.occ": 344
	ldl     11	-- last.address
	ldl     14	-- Data.point
	stnl    0
	j       L27
L47:
	-- "oloader.occ": 346
	ldl     5	-- operand
	eqc     12
	cj      L48
	-- "oloader.occ": 347
	-- "oloader.occ": 348
	-- "oloader.occ": 349
	ldc     0
	stl     6	-- more
	-- "oloader.occ": 351
	ldc     0
	stl     9	-- Bootstrap.depth
	-- "oloader.occ": 352
	ldc     0
	stl     8	-- Bootstrap.length
	-- "oloader.occ": 353
	ldl     23	-- Buffer.address
	stl     7	-- load.address
	-- "oloader.occ": 354
	ldc     1
	stl     6	-- more
	-- "oloader.occ": 355
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "oloader.occ": 356
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- more
	-- "oloader.occ": 357
L49:
	ldl     6	-- more
	cj      L50
	-- "oloader.occ": 359
	ldl     9	-- Bootstrap.depth
	ldc     1
	bsub    
	stl     9	-- Bootstrap.depth
	-- "oloader.occ": 360
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L51:
	-- "oloader.occ": 361
	-- "oloader.occ": 362
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L54
	-- "oloader.occ": 364
	ldlp    1	-- command
	ldl     2	-- i
	ldl     20	-- links
	wsub    
	ldc     1
	out     
	j       L53
L54:
	-- "oloader.occ": 365
L53:
	ldlp    2	-- i
	ldc     L52 - L51
	lend    
L52:
	-- "oloader.occ": 367
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "oloader.occ": 368
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- more
	j       L49
L50:
	-- "oloader.occ": 370
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "oloader.occ": 372
	-- "oloader.occ": 373
	ldl     9	-- Bootstrap.depth
	ldc     0
	gt      
	cj      L56
	-- "oloader.occ": 376
	-- "oloader.occ": 377
	ldl     5	-- operand
	cj      L58
	-- "oloader.occ": 378
	ldl     5	-- operand
	ldl     7	-- load.address
	ldlp    0	-- staticlink
	call    L1	-- Call get.memory
	j       L57
L58:
	-- "oloader.occ": 379
L57:
	-- "oloader.occ": 382
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L59:
	-- "oloader.occ": 383
	-- "oloader.occ": 384
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L62
	-- "oloader.occ": 386
	ldlp    1	-- command
	ldl     2	-- i
	ldl     20	-- links
	wsub    
	ldc     1
	out     
	-- "oloader.occ": 387
	-- "oloader.occ": 388
	ldl     5	-- operand
	cj      L64
	-- "oloader.occ": 389
	ldl     7	-- load.address
	ldl     22	-- memory
	bsub    
	ldl     2	-- i
	ldl     20	-- links
	wsub    
	ldl     5	-- operand
	out     
	j       L63
L64:
	-- "oloader.occ": 390
L63:
	j       L61
L62:
	-- "oloader.occ": 392
L61:
	ldlp    2	-- i
	ldc     L60 - L59
	lend    
L60:
	j       L55
L56:
	-- "oloader.occ": 394
	-- "oloader.occ": 396
	ldc     1
	stl     6	-- more
	-- "oloader.occ": 400
L66:
	ldl     6	-- more
	cj      L67
	-- "oloader.occ": 402
	ldl     5	-- operand
	ldl     7	-- load.address
	ldlp    0	-- staticlink
	call    L1	-- Call get.memory
	-- "oloader.occ": 403
	ldl     7	-- load.address
	ldl     5	-- operand
	bsub    
	stl     7	-- load.address
	-- "oloader.occ": 404
	ldl     8	-- Bootstrap.length
	ldl     5	-- operand
	bsub    
	stl     8	-- Bootstrap.length
	-- "oloader.occ": 405
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "oloader.occ": 408
	ldc     63
	ldl     1	-- command
	gt      
	stl     6	-- more
	-- "oloader.occ": 409
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	j       L66
L67:
	-- "oloader.occ": 411
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L68:
	-- "oloader.occ": 412
	-- "oloader.occ": 413
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L71
	-- "oloader.occ": 415
	ldl     2	-- i
	ldl     20	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	outbyte 
	-- "oloader.occ": 416
	-- "oloader.occ": 417
	ldl     8	-- Bootstrap.length
	cj      L73
	-- "oloader.occ": 418
	ldl     23	-- Buffer.address
	ldl     22	-- memory
	bsub    
	ldl     2	-- i
	ldl     20	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	out     
	j       L72
L73:
	-- "oloader.occ": 419
L72:
	j       L70
L71:
	-- "oloader.occ": 421
L70:
	ldlp    2	-- i
	ldc     L69 - L68
	lend    
L69:
	j       L55
L65:
L55:
	j       L27
L48:
	-- "oloader.occ": 424
	ldl     5	-- operand
	eqc     13
	cj      L74
	-- "oloader.occ": 426
	ldc     0
	stl     6	-- ii
	ldl     9	-- Bootstrap.depth
	stl     7	-- ii + 1
	ldl     7	-- ii + 1
	cj      L76
L75:
	-- "oloader.occ": 429
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "oloader.occ": 430
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L77:
	-- "oloader.occ": 431
	-- "oloader.occ": 432
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L80
	-- "oloader.occ": 433
	ldlp    1	-- command
	ldl     2	-- i
	ldl     20	-- links
	wsub    
	ldc     1
	out     
	j       L79
L80:
	-- "oloader.occ": 434
L79:
	ldlp    2	-- i
	ldc     L78 - L77
	lend    
L78:
	ldlp    6	-- ii
	ldc     L76 - L75
	lend    
L76:
	-- "oloader.occ": 436
	ldc     0
	stl     9	-- Bootstrap.depth
	j       L27
L74:
	-- "oloader.occ": 439
	ldl     5	-- operand
	eqc     14
	cj      L81
	-- "oloader.occ": 440
	-- "oloader.occ": 442
	ldlp    6	-- Memory.size
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	ldl     22	-- memory
	-- "oloader.occ": 443
	stl     3	-- memory.base
	-- "oloader.occ": 443
	ldl     6	-- Memory.size
	ldl     3	-- memory.base
	diff    
	stl     2	-- Memory.end
	-- "oloader.occ": 443
	ldl     23	-- Buffer.address
	stl     0	-- Free.start
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	ldl     2	-- Memory.end
	ldl     0	-- Free.start
	gt      
	cj      L83
	-- "oloader.occ": 443
L84:
	ldl     2	-- Memory.end
	ldl     0	-- Free.start
	gt      
	cj      L85
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	ldl     2	-- Memory.end
	ldl     0	-- Free.start
	diff    
	ldc     32767	-- #7FFF
	gt      
	cj      L87
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	ldc     32767	-- #7FFF
	stl     3	-- dummy
	-- "oloader.occ": 443
	ldc     255
	ldl     0	-- Free.start
	ldl     22	-- memory
	bsub    
	ldl     3	-- dummy
	rev     
	call    L5	-- Call ClearByteBuffer
	-- "oloader.occ": 443
	ldl     0	-- Free.start
	ldc     32767	-- #7FFF
	bsub    
	stl     0	-- Free.start
	j       L86
L87:
	-- "oloader.occ": 443
	-- "oloader.occ": 443
	ldl     2	-- Memory.end
	ldl     0	-- Free.start
	diff    
	stl     3	-- $anon0
	-- "oloader.occ": 443
	ldc     255
	ldl     0	-- Free.start
	ldl     22	-- memory
	bsub    
	ldl     3	-- $anon0
	rev     
	call    L5	-- Call ClearByteBuffer
	-- "oloader.occ": 443
	ldl     2	-- Memory.end
	stl     0	-- Free.start
	j       L86
L88:
L86:
	j       L84
L85:
	j       L82
L83:
	-- "oloader.occ": 443
L82:
	j       L27
L81:
L27:
	j       L13
L26:
	-- "oloader.occ": 447
	-- "oloader.occ": 449
	ldl     5	-- operand
	stl     10	-- output.link
	-- "oloader.occ": 450
	ldl     4	-- links.to.load
	ldc     1
	ldl     10	-- output.link
	shl     
	or      
	stl     4	-- links.to.load
	j       L13
L89:
L13:
	-- "oloader.occ": 452
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	j       L11
L12:
	-- "oloader.occ": 456
	-- "oloader.occ": 459
	ldl     22	-- memory
	-- "oloader.occ": 460
	stl     0	-- load.start
	-- "oloader.occ": 462
	ldl     17	-- Next.address
	ldnl    0
	ldl     0	-- load.start
	bsub    
	ldl     17	-- Next.address
	stnl    0
	-- "oloader.occ": 463
	ldl     14	-- Data.point
	ldnl    0
	ldl     0	-- load.start
	bsub    
	ldl     14	-- Data.point
	stnl    0
	-- "oloader.occ": 464
	ldl     16	-- Invocation.stack
	ldnl    0
	ldl     0	-- load.start
	bsub    
	ldl     16	-- Invocation.stack
	stnl    0
	ajw     19
	ret     
	align
