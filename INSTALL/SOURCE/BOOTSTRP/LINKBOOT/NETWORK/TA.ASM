-- occam 2 compiler Beta Vn 2.01.78 (19:24:22 Sep 15 1992) (SunOS-Sun4)
-- Compiling (TA,UNIVERSAL) "loader.occ"

	j       $Loader	-- jump to entrypoint
L0:	-- section label	-- PROC Get.encoded.value, lexlevel: 1, WS: 3, VS: 0
	-- "loader.occ": 70
	ldc     0
	ldl     2	-- Address
	stnl    0
	-- "loader.occ": 71
	ldc     1
	ldl     1	-- staticlink
	stnl    6	-- More
	-- "loader.occ": 72
L1:
	ldl     1	-- staticlink
	ldnl    6	-- More
	cj      L2
	-- "loader.occ": 74
	ldl     2	-- Address
	ldnl    0
	bcnt    
	bcnt    
	bcnt    
	ldl     2	-- Address
	stnl    0
	-- "loader.occ": 75
	ldl     1	-- staticlink
	ldnlp   1	-- command
	ldl     1	-- staticlink
	ldnl    16	-- bootlink.in
	ldc     1
	in      
	-- "loader.occ": 76
	ldl     2	-- Address
	ldnl    0
	ldl     1	-- staticlink
	ldnl    1	-- command
	ldc     63
	and     
	bsub    
	ldl     2	-- Address
	stnl    0
	-- "loader.occ": 77
	ldc     192
	ldl     1	-- staticlink
	ldnl    1	-- command
	gt      
	eqc     0
	ldl     1	-- staticlink
	stnl    6	-- More
	j       L1
L2:
	ret     
L3:	-- section label	-- PROC ClearByteBuffer, lexlevel: 1, WS: 4, VS: 0
	ajw     -2
	-- "loader.occ": 518
	-- "loader.occ": 518
	ldc     1
	stl     0	-- Count
	-- "loader.occ": 518
	ldl     0	-- Count
	stl     1	-- Index
	-- "loader.occ": 518
	ldl     5	-- Value
	ldl     3	-- Buffer
	sb      
	-- "loader.occ": 518
L4:
	ldl     4	-- $temp-1
	ldl     1	-- Index
	gt      
	cj      L5
	-- "loader.occ": 518
	-- "loader.occ": 518
	ldl     0	-- Count
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	gt      
	cj      L7
	-- "loader.occ": 518
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	stl     0	-- Count
	j       L6
L7:
	-- "loader.occ": 518
L6:
	-- "loader.occ": 518
	ldl     3	-- Buffer
	ldl     1	-- Index
	ldl     3	-- Buffer
	bsub    
	ldl     0	-- Count
	move    
	-- "loader.occ": 518
	ldl     1	-- Index
	ldl     0	-- Count
	bsub    
	stl     1	-- Index
	-- "loader.occ": 518
	ldl     0	-- Count
	ldl     0	-- Count
	bsub    
	stl     0	-- Count
	j       L4
L5:
	ajw     2
	ret     
L8:	-- section label	-- PROC Loader, lexlevel: 0, WS: 22, VS: 0
$Loader:
	global $Loader
	descriptor $Loader "Loader" occam 22 0 "PROC Loader([4]CHAN OF ANY links,CHAN OF ANY bootlink.in,
CHAN OF ANY bootlink.out,[4]BYTE Memory,VAL INT Buffer.address,
INT Next.address,INT Entry.point,INT Data.point)
  SEQ
    links!
    bootlink.in?
:"
	ajw     -14
	-- "loader.occ": 11
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
	-- "loader.occ": 24
	-- "loader.occ": 25
	-- "loader.occ": 26
	-- "loader.occ": 27
	-- "loader.occ": 28
	-- "loader.occ": 29
	-- "loader.occ": 30
	-- "loader.occ": 31
	-- "loader.occ": 32
	-- "loader.occ": 33
	-- "loader.occ": 35
	-- "loader.occ": 36
	-- "loader.occ": 37
	-- "loader.occ": 39
	-- "loader.occ": 40
	-- "loader.occ": 42
	-- "loader.occ": 43
	-- "loader.occ": 45
	-- "loader.occ": 46
	-- "loader.occ": 48
	-- "loader.occ": 49
	-- "loader.occ": 51
	-- "loader.occ": 52
	-- "loader.occ": 54
	-- "loader.occ": 55
	-- "loader.occ": 57
	-- "loader.occ": 58
	-- "loader.occ": 62
	ldc     0
	stl     1	-- command
	-- "loader.occ": 63
	-- "loader.occ": 64
	-- "loader.occ": 65
	ldc     0
	stl     6	-- More
	ldc     0
	stl     12	-- loading
	-- "loader.occ": 285
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "loader.occ": 287
L9:
	ldc     133
	ldl     1	-- command
	diff    
	cj      L10
	-- "loader.occ": 291
	ldl     1	-- command
	ldc     6
	shr     
	stl     13	-- tag
	-- "loader.occ": 292
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "loader.occ": 294
	-- "loader.occ": 296
	ldl     13	-- tag
	eqc     0
	cj      L12
	-- "loader.occ": 297
	-- "loader.occ": 300
	-- "loader.occ": 302
	ldl     12	-- loading
	cj      L14
	-- "loader.occ": 305
	ldl     11	-- last.address
	stl     0	-- load.address
	-- "loader.occ": 306
	ldl     0	-- load.address
	ldl     5	-- operand
	bsub    
	stl     11	-- last.address
	j       L13
L14:
	-- "loader.occ": 310
	-- "loader.occ": 311
	ldl     19	-- Buffer.address
	stl     0	-- load.address
	j       L13
L15:
L13:
	-- "loader.occ": 316
	-- "loader.occ": 317
	ldl     5	-- operand
	cj      L17
	-- "loader.occ": 318
	ldl     0	-- load.address
	ldl     18	-- Memory
	bsub    
	ldl     16	-- bootlink.in
	ldl     5	-- operand
	in      
	j       L16
L17:
	-- "loader.occ": 319
L16:
	-- "loader.occ": 323
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L18:
	-- "loader.occ": 324
	-- "loader.occ": 325
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L21
	-- "loader.occ": 327
	ldlp    1	-- command
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	-- "loader.occ": 328
	-- "loader.occ": 329
	ldl     5	-- operand
	cj      L23
	-- "loader.occ": 330
	ldl     0	-- load.address
	ldl     18	-- Memory
	bsub    
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldl     5	-- operand
	out     
	j       L22
L23:
	-- "loader.occ": 331
L22:
	j       L20
L21:
	-- "loader.occ": 333
L20:
	ldlp    2	-- i
	ldc     L19 - L18
	lend    
L19:
	j       L11
L12:
	-- "loader.occ": 339
	ldl     13	-- tag
	eqc     2
	cj      L24
	-- "loader.occ": 345
	-- "loader.occ": 347
	ldl     5	-- operand
	eqc     1
	cj      L26
	-- "loader.occ": 354
	ldc     0
	stl     12	-- loading
	-- "loader.occ": 355
	ldc     0
	stl     4	-- links.to.load
	j       L25
L26:
	-- "loader.occ": 359
	ldl     5	-- operand
	eqc     2
	cj      L27
	-- "loader.occ": 360
	-- "loader.occ": 362
	ldc     1
	stl     0	-- depth
	-- "loader.occ": 363
L28:
	ldl     0	-- depth
	cj      L29
	-- "loader.occ": 365
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "loader.occ": 366
	-- "loader.occ": 367
	ldl     1	-- command
	eqc     130
	cj      L31
	-- "loader.occ": 368
	ldc     1
	ldl     0	-- depth
	bsub    
	stl     0	-- depth
	j       L30
L31:
	-- "loader.occ": 369
	ldl     1	-- command
	eqc     131
	cj      L32
	-- "loader.occ": 370
	ldl     0	-- depth
	ldc     1
	diff    
	stl     0	-- depth
	j       L30
L32:
	-- "loader.occ": 371
L30:
	-- "loader.occ": 373
	-- "loader.occ": 374
	ldl     0	-- depth
	cj      L34
	-- "loader.occ": 375
	ldlp    1	-- command
	ldl     10	-- output.link
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	j       L33
L34:
	-- "loader.occ": 376
L33:
	j       L28
L29:
	j       L25
L27:
	-- "loader.occ": 380
	ldl     5	-- operand
	eqc     4
	cj      L35
	-- "loader.occ": 382
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "loader.occ": 383
	ldl     11	-- last.address
	ldl     20	-- Next.address
	stnl    0
	j       L25
L35:
	-- "loader.occ": 386
	ldl     5	-- operand
	eqc     6
	cj      L36
	-- "loader.occ": 388
	ldl     22	-- Data.point
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	j       L25
L36:
	-- "loader.occ": 391
	ldl     5	-- operand
	eqc     11
	cj      L37
	-- "loader.occ": 393
	ldl     21	-- Entry.point
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	j       L25
L37:
	-- "loader.occ": 396
	ldl     5	-- operand
	eqc     8
	cj      L38
	-- "loader.occ": 398
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "loader.occ": 399
	ldl     11	-- last.address
	ldl     21	-- Entry.point
	stnl    0
	j       L25
L38:
	-- "loader.occ": 402
	ldl     5	-- operand
	eqc     10
	cj      L39
	-- "loader.occ": 404
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "loader.occ": 405
	ldl     11	-- last.address
	ldl     22	-- Data.point
	stnl    0
	j       L25
L39:
	-- "loader.occ": 408
	ldl     5	-- operand
	eqc     12
	cj      L40
	-- "loader.occ": 409
	-- "loader.occ": 410
	-- "loader.occ": 412
	ldc     0
	stl     9	-- Bootstrap.depth
	-- "loader.occ": 413
	ldc     0
	stl     8	-- Bootstrap.length
	-- "loader.occ": 414
	ldl     19	-- Buffer.address
	stl     7	-- load.address
	-- "loader.occ": 415
	ldc     1
	stl     6	-- More
	-- "loader.occ": 416
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "loader.occ": 417
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- More
	-- "loader.occ": 418
L41:
	ldl     6	-- More
	cj      L42
	-- "loader.occ": 420
	ldc     1
	ldl     9	-- Bootstrap.depth
	bsub    
	stl     9	-- Bootstrap.depth
	-- "loader.occ": 421
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L43:
	-- "loader.occ": 422
	-- "loader.occ": 423
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L46
	-- "loader.occ": 425
	ldlp    1	-- command
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	j       L45
L46:
	-- "loader.occ": 426
L45:
	ldlp    2	-- i
	ldc     L44 - L43
	lend    
L44:
	-- "loader.occ": 428
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "loader.occ": 429
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- More
	j       L41
L42:
	-- "loader.occ": 431
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "loader.occ": 433
	-- "loader.occ": 434
	ldl     9	-- Bootstrap.depth
	ldc     0
	gt      
	cj      L48
	-- "loader.occ": 437
	-- "loader.occ": 438
	ldl     5	-- operand
	cj      L50
	-- "loader.occ": 439
	ldl     7	-- load.address
	ldl     18	-- Memory
	bsub    
	ldl     16	-- bootlink.in
	ldl     5	-- operand
	in      
	j       L49
L50:
	-- "loader.occ": 440
L49:
	-- "loader.occ": 443
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L51:
	-- "loader.occ": 444
	-- "loader.occ": 445
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L54
	-- "loader.occ": 447
	ldlp    1	-- command
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	-- "loader.occ": 448
	-- "loader.occ": 449
	ldl     5	-- operand
	cj      L56
	-- "loader.occ": 450
	ldl     7	-- load.address
	ldl     18	-- Memory
	bsub    
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldl     5	-- operand
	out     
	j       L55
L56:
	-- "loader.occ": 451
L55:
	j       L53
L54:
	-- "loader.occ": 453
L53:
	ldlp    2	-- i
	ldc     L52 - L51
	lend    
L52:
	j       L47
L48:
	-- "loader.occ": 455
	-- "loader.occ": 457
	ldc     1
	stl     6	-- More
	-- "loader.occ": 460
L58:
	ldl     6	-- More
	cj      L59
	-- "loader.occ": 462
	ldl     7	-- load.address
	ldl     18	-- Memory
	bsub    
	ldl     16	-- bootlink.in
	ldl     5	-- operand
	in      
	-- "loader.occ": 463
	ldl     7	-- load.address
	ldl     5	-- operand
	bsub    
	stl     7	-- load.address
	-- "loader.occ": 464
	ldl     8	-- Bootstrap.length
	ldl     5	-- operand
	bsub    
	stl     8	-- Bootstrap.length
	-- "loader.occ": 465
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "loader.occ": 468
	ldc     63
	ldl     1	-- command
	gt      
	stl     6	-- More
	-- "loader.occ": 469
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	j       L58
L59:
	-- "loader.occ": 471
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L60:
	-- "loader.occ": 472
	-- "loader.occ": 473
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L63
	-- "loader.occ": 475
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	outbyte 
	-- "loader.occ": 476
	-- "loader.occ": 477
	ldl     8	-- Bootstrap.length
	cj      L65
	-- "loader.occ": 478
	ldl     19	-- Buffer.address
	ldl     18	-- Memory
	bsub    
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	out     
	j       L64
L65:
	-- "loader.occ": 479
L64:
	j       L62
L63:
	-- "loader.occ": 481
L62:
	ldlp    2	-- i
	ldc     L61 - L60
	lend    
L61:
	j       L47
L57:
L47:
	j       L25
L40:
	-- "loader.occ": 486
	ldl     5	-- operand
	eqc     13
	cj      L66
	-- "loader.occ": 488
	ldc     0
	stl     7	-- ii
	ldl     9	-- Bootstrap.depth
	stl     8	-- ii + 1
	ldl     8	-- ii + 1
	cj      L68
L67:
	-- "loader.occ": 491
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "loader.occ": 492
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L69:
	-- "loader.occ": 493
	-- "loader.occ": 494
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L72
	-- "loader.occ": 495
	ldlp    1	-- command
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	j       L71
L72:
	-- "loader.occ": 496
L71:
	ldlp    2	-- i
	ldc     L70 - L69
	lend    
L70:
	ldlp    7	-- ii
	ldc     L68 - L67
	lend    
L68:
	-- "loader.occ": 498
	ldc     0
	stl     9	-- Bootstrap.depth
	j       L25
L66:
	-- "loader.occ": 502
	ldl     5	-- operand
	eqc     14
	cj      L73
	-- "loader.occ": 506
	-- "loader.occ": 508
	-- "loader.occ": 514
	-- "loader.occ": 515
	-- "loader.occ": 517
	ldlp    2	-- Memory.size
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "loader.occ": 518
	-- "loader.occ": 518
	-- "loader.occ": 518
	-- "loader.occ": 518
	ldc     2048
	stl     0	-- Free.start
	-- "loader.occ": 518
	-- "loader.occ": 518
	ldl     2	-- Memory.size
	ldl     0	-- Free.start
	gt      
	cj      L77
	-- "loader.occ": 518
L78:
	ldl     2	-- Memory.size
	ldl     0	-- Free.start
	gt      
	cj      L79
	-- "loader.occ": 518
	-- "loader.occ": 518
	ldl     2	-- Memory.size
	ldl     0	-- Free.start
	diff    
	mint    
	not     
	gt      
	cj      L81
	-- "loader.occ": 518
	ldc     255
	ldl     0	-- Free.start
	mint    	-- BtMemory
	bsub    
	mint    
	not     
	rev     
	call    L3	-- Call ClearByteBuffer
	-- "loader.occ": 518
	mint    
	not     
	ldl     0	-- Free.start
	bsub    
	stl     0	-- Free.start
	j       L80
L81:
	-- "loader.occ": 518
	-- "loader.occ": 518
	ldl     2	-- Memory.size
	ldl     0	-- Free.start
	diff    
	stl     3	-- $anon1
	-- "loader.occ": 518
	ldc     255
	ldl     0	-- Free.start
	mint    	-- BtMemory
	bsub    
	ldl     3	-- $anon1
	rev     
	call    L3	-- Call ClearByteBuffer
	-- "loader.occ": 518
	ldl     2	-- Memory.size
	stl     0	-- Free.start
	j       L80
L82:
L80:
	j       L78
L79:
	j       L76
L77:
	-- "loader.occ": 518
L76:
	j       L74
L75:
L74:
	j       L25
L73:
	-- "loader.occ": 522
	-- "loader.occ": 524
	ldc     1
	stl     12	-- loading
	-- "loader.occ": 525
	ldc     0
	stl     4	-- links.to.load
	j       L25
L83:
L25:
	j       L11
L24:
	-- "loader.occ": 530
	-- "loader.occ": 532
	ldl     5	-- operand
	stl     10	-- output.link
	-- "loader.occ": 533
	ldl     4	-- links.to.load
	ldc     1
	ldl     10	-- output.link
	shl     
	or      
	stl     4	-- links.to.load
	j       L11
L84:
L11:
	-- "loader.occ": 536
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	j       L9
L10:
	ajw     14
	ret     
	align
