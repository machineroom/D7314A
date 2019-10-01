-- occam 2 compiler Version 2.01.67 (10:48:37 Jul  9 1992) (SunOS-Sun4)
-- Compiling (T2,UNIVERSAL) "loader.occ"

	j       $Loader	-- jump to entrypoint
L0:	-- section label	-- PROC get.command, lexlevel: 1, WS: 2, VS: 0
	-- "loader.occ": 71
	ldl     1	-- staticlink
	ldnl    19	-- network.data.pointer
	ldnl    0
	ldl     1	-- staticlink
	ldnl    18	-- network.data
	bsub    
	lb      
	ldl     1	-- staticlink
	stnl    1	-- command
	-- "loader.occ": 72
	ldl     1	-- staticlink
	ldnl    19	-- network.data.pointer
	ldnl    0
	adc     1
	ldl     1	-- staticlink
	ldnl    19	-- network.data.pointer
	stnl    0
	ret     
L1:	-- section label	-- PROC get.memory, lexlevel: 1, WS: 2, VS: 0
	-- "loader.occ": 82
	ldl     1	-- staticlink
	ldnl    19	-- network.data.pointer
	ldnl    0
	ldl     1	-- staticlink
	ldnl    18	-- network.data
	bsub    
	ldl     2	-- at
	adc     120
	ldl     1	-- staticlink
	ldnl    20	-- memory
	bsub    
	ldl     3	-- len
	move    
	-- "loader.occ": 84
	ldl     1	-- staticlink
	ldnl    19	-- network.data.pointer
	ldnl    0
	ldl     3	-- len
	add     
	ldl     1	-- staticlink
	ldnl    19	-- network.data.pointer
	stnl    0
	ret     
L2:	-- section label	-- PROC Get.encoded.value, lexlevel: 1, WS: 7, VS: 0
	ajw     -1
	-- "loader.occ": 97
	ldc     0
	stl     0	-- more
	-- "loader.occ": 99
	ldc     0
	ldl     3	-- value
	stnl    0
	-- "loader.occ": 100
	ldc     1
	stl     0	-- more
	-- "loader.occ": 101
L3:
	ldl     0	-- more
	cj      L4
	-- "loader.occ": 103
	ldl     3	-- value
	ldnl    0
	ldc     6
	shl     
	ldl     3	-- value
	stnl    0
	-- "loader.occ": 104
	ldl     2	-- staticlink
	call    L0	-- Call get.command
	-- "loader.occ": 105
	ldl     3	-- value
	ldnl    0
	ldl     2	-- staticlink
	ldnl    1	-- command
	ldc     63
	and     
	bsub    
	ldl     3	-- value
	stnl    0
	-- "loader.occ": 106
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
	-- "loader.occ": 524
	-- "loader.occ": 524
	ldc     1
	stl     0	-- Count
	-- "loader.occ": 524
	ldl     0	-- Count
	stl     1	-- Index
	-- "loader.occ": 524
	ldl     5	-- Value
	ldl     3	-- Buffer
	sb      
	-- "loader.occ": 524
L6:
	ldl     4	-- $temp-1
	ldl     1	-- Index
	gt      
	cj      L7
	-- "loader.occ": 524
	-- "loader.occ": 524
	ldl     0	-- Count
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	gt      
	cj      L9
	-- "loader.occ": 524
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	stl     0	-- Count
	j       L8
L9:
	-- "loader.occ": 524
L8:
	-- "loader.occ": 524
	ldl     3	-- Buffer
	ldl     1	-- Index
	ldl     3	-- Buffer
	bsub    
	ldl     0	-- Count
	move    
	-- "loader.occ": 524
	ldl     1	-- Index
	ldl     0	-- Count
	bsub    
	stl     1	-- Index
	-- "loader.occ": 524
	ldl     0	-- Count
	ldl     0	-- Count
	bsub    
	stl     0	-- Count
	j       L6
L7:
	ajw     2
	ret     
L10:	-- section label	-- PROC Loader, lexlevel: 0, WS: 27, VS: 0
$Loader:
	global $Loader
	descriptor $Loader "Loader" occam 27 0 "PROC Loader([4]CHAN OF ANY links,[4]BYTE network.data,
INT network.data.pointer,[4]BYTE memory,VAL INT Buffer.address,
INT Next.address,INT Entry.point,INT Data.point)
  SEQ
    links!
:"
	ajw     -16
	-- "loader.occ": 12
	-- "loader.occ": 13
	-- "loader.occ": 14
	-- "loader.occ": 15
	-- "loader.occ": 16
	-- "loader.occ": 17
	-- "loader.occ": 18
	-- "loader.occ": 19
	-- "loader.occ": 20
	-- "loader.occ": 21
	-- "loader.occ": 22
	-- "loader.occ": 23
	-- "loader.occ": 25
	-- "loader.occ": 26
	-- "loader.occ": 27
	-- "loader.occ": 28
	-- "loader.occ": 29
	-- "loader.occ": 30
	-- "loader.occ": 31
	-- "loader.occ": 32
	-- "loader.occ": 33
	-- "loader.occ": 34
	-- "loader.occ": 36
	-- "loader.occ": 37
	-- "loader.occ": 38
	-- "loader.occ": 40
	-- "loader.occ": 41
	-- "loader.occ": 43
	-- "loader.occ": 44
	-- "loader.occ": 46
	-- "loader.occ": 47
	-- "loader.occ": 49
	-- "loader.occ": 50
	-- "loader.occ": 52
	-- "loader.occ": 53
	-- "loader.occ": 55
	-- "loader.occ": 56
	-- "loader.occ": 58
	-- "loader.occ": 59
	-- "loader.occ": 62
	ldc     0
	stl     1	-- command
	-- "loader.occ": 63
	-- "loader.occ": 64
	ldc     0
	stl     14	-- loading
	-- "loader.occ": 77
	-- "loader.occ": 78
	ldl     21	-- Buffer.address
	adc     -120
	stl     13	-- Buffer.mem
	-- "loader.occ": 309
	ldc     0
	ldl     19	-- network.data.pointer
	stnl    0
	-- "loader.occ": 310
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "loader.occ": 311
L11:
	ldc     133
	ldl     1	-- command
	diff    
	cj      L12
	-- "loader.occ": 312
	-- "loader.occ": 315
	ldl     1	-- command
	ldc     6
	shr     
	stl     15	-- tag
	-- "loader.occ": 316
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "loader.occ": 317
	-- "loader.occ": 319
	ldl     15	-- tag
	eqc     0
	cj      L14
	-- "loader.occ": 320
	-- "loader.occ": 322
	-- "loader.occ": 324
	ldl     14	-- loading
	cj      L16
	-- "loader.occ": 326
	ldl     12	-- last.address
	stl     0	-- load.address
	-- "loader.occ": 327
	ldl     0	-- load.address
	ldl     5	-- operand
	bsub    
	stl     12	-- last.address
	j       L15
L16:
	-- "loader.occ": 329
	-- "loader.occ": 330
	ldl     13	-- Buffer.mem
	stl     0	-- load.address
	j       L15
L17:
L15:
	-- "loader.occ": 333
	-- "loader.occ": 334
	ldl     5	-- operand
	cj      L19
	-- "loader.occ": 335
	ldl     5	-- operand
	ldl     0	-- load.address
	ldlp    0	-- staticlink
	call    L1	-- Call get.memory
	j       L18
L19:
	-- "loader.occ": 336
L18:
	-- "loader.occ": 339
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L20:
	-- "loader.occ": 340
	-- "loader.occ": 341
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L23
	-- "loader.occ": 343
	ldlp    1	-- command
	ldl     2	-- i
	ldl     17	-- links
	wsub    
	ldc     1
	out     
	-- "loader.occ": 344
	-- "loader.occ": 345
	ldl     5	-- operand
	cj      L25
	-- "loader.occ": 346
	ldl     0	-- load.address
	adc     120
	ldl     20	-- memory
	bsub    
	ldl     2	-- i
	ldl     17	-- links
	wsub    
	ldl     5	-- operand
	out     
	j       L24
L25:
	-- "loader.occ": 347
L24:
	j       L22
L23:
	-- "loader.occ": 349
L22:
	ldlp    2	-- i
	ldc     L21 - L20
	lend    
L21:
	j       L13
L14:
	-- "loader.occ": 352
	ldl     15	-- tag
	eqc     2
	cj      L26
	-- "loader.occ": 353
	-- "loader.occ": 355
	ldl     5	-- operand
	eqc     0
	cj      L28
	-- "loader.occ": 357
	ldc     1
	stl     14	-- loading
	-- "loader.occ": 358
	ldc     0
	stl     4	-- links.to.load
	j       L27
L28:
	-- "loader.occ": 360
	ldl     5	-- operand
	eqc     9
	cj      L29
	-- "loader.occ": 362
	ldc     1
	stl     14	-- loading
	-- "loader.occ": 363
	ldc     0
	stl     4	-- links.to.load
	j       L27
L29:
	-- "loader.occ": 365
	ldl     5	-- operand
	eqc     7
	cj      L30
	-- "loader.occ": 367
	ldc     1
	stl     14	-- loading
	-- "loader.occ": 368
	ldc     0
	stl     4	-- links.to.load
	j       L27
L30:
	-- "loader.occ": 370
	ldl     5	-- operand
	eqc     1
	cj      L31
	-- "loader.occ": 372
	ldc     0
	stl     14	-- loading
	-- "loader.occ": 373
	ldc     0
	stl     4	-- links.to.load
	j       L27
L31:
	-- "loader.occ": 375
	ldl     5	-- operand
	eqc     2
	cj      L32
	-- "loader.occ": 376
	-- "loader.occ": 378
	ldc     1
	stl     0	-- depth
	-- "loader.occ": 379
L33:
	ldl     0	-- depth
	cj      L34
	-- "loader.occ": 381
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "loader.occ": 382
	-- "loader.occ": 383
	ldl     1	-- command
	eqc     130
	cj      L36
	-- "loader.occ": 384
	ldl     0	-- depth
	adc     1
	stl     0	-- depth
	j       L35
L36:
	-- "loader.occ": 385
	ldl     1	-- command
	eqc     131
	cj      L37
	-- "loader.occ": 386
	ldl     0	-- depth
	adc     -1
	stl     0	-- depth
	j       L35
L37:
	-- "loader.occ": 387
L35:
	-- "loader.occ": 389
	-- "loader.occ": 390
	ldl     0	-- depth
	cj      L39
	-- "loader.occ": 391
	ldlp    1	-- command
	ldl     11	-- output.link
	ldl     17	-- links
	wsub    
	ldc     1
	out     
	j       L38
L39:
	-- "loader.occ": 392
L38:
	j       L33
L34:
	j       L27
L32:
	-- "loader.occ": 397
	ldl     5	-- operand
	eqc     4
	cj      L40
	-- "loader.occ": 399
	ldlp    12	-- last.address
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	-- "loader.occ": 400
	ldl     12	-- last.address
	ldl     22	-- Next.address
	stnl    0
	j       L27
L40:
	-- "loader.occ": 402
	ldl     5	-- operand
	eqc     6
	cj      L41
	-- "loader.occ": 404
	ldl     24	-- Data.point
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	j       L27
L41:
	-- "loader.occ": 406
	ldl     5	-- operand
	eqc     11
	cj      L42
	-- "loader.occ": 408
	ldl     23	-- Entry.point
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	j       L27
L42:
	-- "loader.occ": 410
	ldl     5	-- operand
	eqc     8
	cj      L43
	-- "loader.occ": 412
	ldlp    12	-- last.address
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	-- "loader.occ": 413
	ldl     12	-- last.address
	ldl     23	-- Entry.point
	stnl    0
	j       L27
L43:
	-- "loader.occ": 415
	ldl     5	-- operand
	eqc     10
	cj      L44
	-- "loader.occ": 417
	ldlp    12	-- last.address
	ldlp    0	-- staticlink
	call    L2	-- Call Get.encoded.value
	-- "loader.occ": 418
	ldl     12	-- last.address
	ldl     24	-- Data.point
	stnl    0
	j       L27
L44:
	-- "loader.occ": 420
	ldl     5	-- operand
	eqc     12
	cj      L45
	-- "loader.occ": 421
	-- "loader.occ": 422
	-- "loader.occ": 423
	ldc     0
	stl     6	-- more
	-- "loader.occ": 425
	ldc     0
	stl     10	-- Bootstrap.depth
	-- "loader.occ": 426
	ldc     0
	stl     8	-- Bootstrap.length
	-- "loader.occ": 427
	ldl     13	-- Buffer.mem
	stl     7	-- load.address
	-- "loader.occ": 428
	ldc     1
	stl     6	-- more
	-- "loader.occ": 429
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "loader.occ": 430
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- more
	-- "loader.occ": 431
L46:
	ldl     6	-- more
	cj      L47
	-- "loader.occ": 433
	ldl     10	-- Bootstrap.depth
	ldc     1
	bsub    
	stl     10	-- Bootstrap.depth
	-- "loader.occ": 434
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L48:
	-- "loader.occ": 435
	-- "loader.occ": 436
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L51
	-- "loader.occ": 438
	ldlp    1	-- command
	ldl     2	-- i
	ldl     17	-- links
	wsub    
	ldc     1
	out     
	j       L50
L51:
	-- "loader.occ": 439
L50:
	ldlp    2	-- i
	ldc     L49 - L48
	lend    
L49:
	-- "loader.occ": 441
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "loader.occ": 442
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- more
	j       L46
L47:
	-- "loader.occ": 444
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "loader.occ": 446
	-- "loader.occ": 447
	ldl     10	-- Bootstrap.depth
	ldc     0
	gt      
	cj      L53
	-- "loader.occ": 450
	-- "loader.occ": 451
	ldl     5	-- operand
	cj      L55
	-- "loader.occ": 452
	ldl     5	-- operand
	ldl     7	-- load.address
	ldlp    0	-- staticlink
	call    L1	-- Call get.memory
	j       L54
L55:
	-- "loader.occ": 453
L54:
	-- "loader.occ": 456
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L56:
	-- "loader.occ": 457
	-- "loader.occ": 458
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L59
	-- "loader.occ": 460
	ldlp    1	-- command
	ldl     2	-- i
	ldl     17	-- links
	wsub    
	ldc     1
	out     
	-- "loader.occ": 461
	-- "loader.occ": 462
	ldl     5	-- operand
	cj      L61
	-- "loader.occ": 463
	ldl     7	-- load.address
	adc     120
	ldl     20	-- memory
	bsub    
	ldl     2	-- i
	ldl     17	-- links
	wsub    
	ldl     5	-- operand
	out     
	j       L60
L61:
	-- "loader.occ": 464
L60:
	j       L58
L59:
	-- "loader.occ": 466
L58:
	ldlp    2	-- i
	ldc     L57 - L56
	lend    
L57:
	j       L52
L53:
	-- "loader.occ": 468
	-- "loader.occ": 470
	ldc     1
	stl     6	-- more
	-- "loader.occ": 474
L63:
	ldl     6	-- more
	cj      L64
	-- "loader.occ": 476
	ldl     5	-- operand
	ldl     7	-- load.address
	ldlp    0	-- staticlink
	call    L1	-- Call get.memory
	-- "loader.occ": 477
	ldl     7	-- load.address
	ldl     5	-- operand
	bsub    
	stl     7	-- load.address
	-- "loader.occ": 478
	ldl     8	-- Bootstrap.length
	ldl     5	-- operand
	bsub    
	stl     8	-- Bootstrap.length
	-- "loader.occ": 479
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "loader.occ": 482
	ldc     63
	ldl     1	-- command
	gt      
	stl     6	-- more
	-- "loader.occ": 483
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	j       L63
L64:
	-- "loader.occ": 485
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L65:
	-- "loader.occ": 486
	-- "loader.occ": 487
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L68
	-- "loader.occ": 489
	ldl     2	-- i
	ldl     17	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	outbyte 
	-- "loader.occ": 490
	-- "loader.occ": 491
	ldl     8	-- Bootstrap.length
	cj      L70
	-- "loader.occ": 492
	ldl     13	-- Buffer.mem
	adc     120
	ldl     20	-- memory
	bsub    
	ldl     2	-- i
	ldl     17	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	out     
	j       L69
L70:
	-- "loader.occ": 493
L69:
	j       L67
L68:
	-- "loader.occ": 495
L67:
	ldlp    2	-- i
	ldc     L66 - L65
	lend    
L66:
	j       L52
L62:
L52:
	j       L27
L45:
	-- "loader.occ": 498
	ldl     5	-- operand
	eqc     13
	cj      L71
	-- "loader.occ": 500
	ldc     0
	stl     6	-- ii
	ldl     10	-- Bootstrap.depth
	stl     7	-- ii + 1
	ldl     7	-- ii + 1
	cj      L73
L72:
	-- "loader.occ": 503
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "loader.occ": 504
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L74:
	-- "loader.occ": 505
	-- "loader.occ": 506
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L77
	-- "loader.occ": 507
	ldlp    1	-- command
	ldl     2	-- i
	ldl     17	-- links
	wsub    
	ldc     1
	out     
	j       L76
L77:
	-- "loader.occ": 508
L76:
	ldlp    2	-- i
	ldc     L75 - L74
	lend    
L75:
	ldlp    6	-- ii
	ldc     L73 - L72
	lend    
L73:
	-- "loader.occ": 510
	ldc     0
	stl     10	-- Bootstrap.depth
	j       L27
L71:
	-- "loader.occ": 513
	ldl     5	-- operand
	eqc     14
	cj      L78
	-- "loader.occ": 517
	-- "loader.occ": 519
	-- "loader.occ": 520
	-- "loader.occ": 521
	-- "loader.occ": 523
	ldc     0
	stl     0	-- more
	-- "loader.occ": 523
	ldc     0
	stl     2	-- Memory.size
	ldc     0
	stl     3	-- Memory.size + 1
	-- "loader.occ": 523
	ldc     1
	stl     0	-- more
	-- "loader.occ": 523
L81:
	ldl     0	-- more
	cj      L82
	-- "loader.occ": 523
	ldl     3	-- Memory.size + 1
	ldl     2	-- Memory.size
	ldc     6
	lshl    
	stl     2	-- Memory.size
	stl     3	-- Memory.size + 1
	-- "loader.occ": 523
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	-- "loader.occ": 523
	ldl     1	-- command
	ldc     63
	and     
	xdble   
	stl     8	-- $temp23
	stl     9	-- $temp23 + 1
	ldc     0
	ldl     2	-- Memory.size
	ldl     8	-- $temp23
	lsum    
	stl     2	-- Memory.size
	ldl     3	-- Memory.size + 1
	ldl     9	-- $temp23 + 1
	lsum    
	stl     3	-- Memory.size + 1
	-- "loader.occ": 523
	ldc     192
	ldl     1	-- command
	gt      
	eqc     0
	stl     0	-- more
	j       L81
L82:
	-- "loader.occ": 524
	-- "loader.occ": 524
	-- "loader.occ": 524
	-- "loader.occ": 524
	ldc     2048
	stl     6	-- Free.start
	ldc     0
	stl     7	-- Free.start + 1
	-- "loader.occ": 524
	-- "loader.occ": 524
	ldl     3	-- Memory.size + 1
	ldl     7	-- Free.start + 1
	gt      
	eqc     0
	cj      L85
	ldl     3	-- Memory.size + 1
	ldl     7	-- Free.start + 1
	diff    
	eqc     0
	cj      L86
	ldl     2	-- Memory.size
	mint    
	xor     
	ldl     6	-- Free.start
	mint    
	xor     
	gt      
	eqc     0
L85:
	eqc     0
L86:
	cj      L84
	-- "loader.occ": 524
L87:
	ldl     3	-- Memory.size + 1
	ldl     7	-- Free.start + 1
	gt      
	eqc     0
	cj      L89
	ldl     3	-- Memory.size + 1
	ldl     7	-- Free.start + 1
	diff    
	eqc     0
	cj      L90
	ldl     2	-- Memory.size
	mint    
	xor     
	ldl     6	-- Free.start
	mint    
	xor     
	gt      
	eqc     0
L89:
	eqc     0
L90:
	cj      L88
	-- "loader.occ": 524
	-- "loader.occ": 524
	ldc     0
	ldl     2	-- Memory.size
	ldl     6	-- Free.start
	ldiff   
	stl     8	-- $temp23
	ldl     3	-- Memory.size + 1
	ldl     7	-- Free.start + 1
	ldiff   
	stl     9	-- $temp23 + 1
	ldl     9	-- $temp23 + 1
	ldc     0
	gt      
	eqc     0
	cj      L93
	ldl     9	-- $temp23 + 1
	eqc     0
	cj      L94
	ldl     8	-- $temp23
	mint    
	xor     
	ldc     -1
	gt      
	eqc     0
L93:
	eqc     0
L94:
	cj      L92
	-- "loader.occ": 524
	ldl     6	-- Free.start
	mint    	-- BtMemory
	bsub    
	ldc     255
	rev     
	ldc     32767	-- #7FFF
	rev     
	call    L5	-- Call ClearByteBuffer
	-- "loader.occ": 524
	ldc     0
	ldl     6	-- Free.start
	ldc     32767	-- #7FFF
	lsum    
	stl     6	-- Free.start
	ldl     7	-- Free.start + 1
	ldc     0
	lsum    
	stl     7	-- Free.start + 1
	j       L91
L92:
	-- "loader.occ": 524
	-- "loader.occ": 524
	ldc     0
	ldl     2	-- Memory.size
	ldl     6	-- Free.start
	ldiff   
	stl     8	-- $temp23
	ldl     3	-- Memory.size + 1
	ldl     7	-- Free.start + 1
	ldiff   
	stl     9	-- $temp23 + 1
	ldl     8	-- $temp23
	stl     0	-- $anon0
	-- "loader.occ": 524
	ldl     6	-- Free.start
	mint    	-- BtMemory
	bsub    
	ldc     255
	rev     
	ldl     0	-- $anon0
	rev     
	call    L5	-- Call ClearByteBuffer
	-- "loader.occ": 524
	ldl     2	-- Memory.size
	stl     6	-- Free.start
	ldl     3	-- Memory.size + 1
	stl     7	-- Free.start + 1
	j       L91
L95:
L91:
	j       L87
L88:
	j       L83
L84:
	-- "loader.occ": 524
L83:
	j       L79
L80:
L79:
	j       L27
L78:
L27:
	j       L13
L26:
	-- "loader.occ": 534
	-- "loader.occ": 536
	ldl     5	-- operand
	stl     11	-- output.link
	-- "loader.occ": 537
	ldl     4	-- links.to.load
	ldc     1
	ldl     11	-- output.link
	shl     
	or      
	stl     4	-- links.to.load
	j       L13
L96:
L13:
	-- "loader.occ": 539
	ldlp    0	-- staticlink
	call    L0	-- Call get.command
	j       L11
L12:
	ajw     16
	ret     
	align
