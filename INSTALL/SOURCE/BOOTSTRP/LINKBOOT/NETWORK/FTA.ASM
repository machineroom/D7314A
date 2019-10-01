-- occam 2 compiler Version 2.01.67 (20:23:15 Jul 14 1992) (SunOS-Sun4)
-- Compiling (TA,UNIVERSAL) "foptloader.occ"

	j       $Floating.loader	-- jump to entrypoint
L0:	-- section label	-- PROC Get.encoded.value, lexlevel: 1, WS: 3, VS: 0
	-- "foptloader.occ": 70
	ldc     0
	ldl     2	-- Address
	stnl    0
	-- "foptloader.occ": 71
	ldc     1
	ldl     1	-- staticlink
	stnl    6	-- More
	-- "foptloader.occ": 72
L1:
	ldl     1	-- staticlink
	ldnl    6	-- More
	cj      L2
	-- "foptloader.occ": 74
	ldl     2	-- Address
	ldnl    0
	bcnt    
	bcnt    
	bcnt    
	ldl     2	-- Address
	stnl    0
	-- "foptloader.occ": 75
	ldl     1	-- staticlink
	ldnlp   1	-- command
	ldl     1	-- staticlink
	ldnl    16	-- bootlink.in
	ldc     1
	in      
	-- "foptloader.occ": 76
	ldl     2	-- Address
	ldnl    0
	ldl     1	-- staticlink
	ldnl    1	-- command
	ldc     63
	and     
	bsub    
	ldl     2	-- Address
	stnl    0
	-- "foptloader.occ": 77
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
	-- "foptloader.occ": 396
	-- "foptloader.occ": 396
	ldc     1
	stl     0	-- Count
	-- "foptloader.occ": 396
	ldl     0	-- Count
	stl     1	-- Index
	-- "foptloader.occ": 396
	ldl     5	-- Value
	ldl     3	-- Buffer
	sb      
	-- "foptloader.occ": 396
L4:
	ldl     4	-- $temp-1
	ldl     1	-- Index
	gt      
	cj      L5
	-- "foptloader.occ": 396
	-- "foptloader.occ": 396
	ldl     0	-- Count
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	gt      
	cj      L7
	-- "foptloader.occ": 396
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	stl     0	-- Count
	j       L6
L7:
	-- "foptloader.occ": 396
L6:
	-- "foptloader.occ": 396
	ldl     3	-- Buffer
	ldl     1	-- Index
	ldl     3	-- Buffer
	bsub    
	ldl     0	-- Count
	move    
	-- "foptloader.occ": 396
	ldl     1	-- Index
	ldl     0	-- Count
	bsub    
	stl     1	-- Index
	-- "foptloader.occ": 396
	ldl     0	-- Count
	ldl     0	-- Count
	bsub    
	stl     0	-- Count
	j       L4
L5:
	ajw     2
	ret     
L8:	-- section label	-- PROC Floating.loader, lexlevel: 0, WS: 22, VS: 0
$Floating.loader:
	global $Floating.loader
	descriptor $Floating.loader "Floating.loader" occam 22 0 "PROC Floating.loader([4]CHAN OF ANY links,CHAN OF ANY bootlink.in,
CHAN OF ANY bootlink.out,[4]BYTE Memory,VAL INT Buffer.address,
INT Next.address,INT Entry.point,INT Data.point)
  SEQ
    links!
    bootlink.in?
:"
	ajw     -14
	-- "foptloader.occ": 11
	-- "foptloader.occ": 12
	-- "foptloader.occ": 13
	-- "foptloader.occ": 14
	-- "foptloader.occ": 15
	-- "foptloader.occ": 16
	-- "foptloader.occ": 17
	-- "foptloader.occ": 18
	-- "foptloader.occ": 19
	-- "foptloader.occ": 20
	-- "foptloader.occ": 21
	-- "foptloader.occ": 22
	-- "foptloader.occ": 24
	-- "foptloader.occ": 25
	-- "foptloader.occ": 26
	-- "foptloader.occ": 27
	-- "foptloader.occ": 28
	-- "foptloader.occ": 29
	-- "foptloader.occ": 30
	-- "foptloader.occ": 31
	-- "foptloader.occ": 32
	-- "foptloader.occ": 33
	-- "foptloader.occ": 35
	-- "foptloader.occ": 36
	-- "foptloader.occ": 37
	-- "foptloader.occ": 39
	-- "foptloader.occ": 40
	-- "foptloader.occ": 42
	-- "foptloader.occ": 43
	-- "foptloader.occ": 45
	-- "foptloader.occ": 46
	-- "foptloader.occ": 48
	-- "foptloader.occ": 49
	-- "foptloader.occ": 51
	-- "foptloader.occ": 52
	-- "foptloader.occ": 54
	-- "foptloader.occ": 55
	-- "foptloader.occ": 57
	-- "foptloader.occ": 58
	-- "foptloader.occ": 62
	ldc     0
	stl     1	-- command
	-- "foptloader.occ": 63
	-- "foptloader.occ": 64
	-- "foptloader.occ": 65
	ldc     0
	stl     6	-- More
	ldc     0
	stl     12	-- loading
	-- "foptloader.occ": 175
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "foptloader.occ": 177
L9:
	ldc     133
	ldl     1	-- command
	diff    
	cj      L10
	-- "foptloader.occ": 181
	ldl     1	-- command
	ldc     6
	shr     
	stl     13	-- tag
	-- "foptloader.occ": 182
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "foptloader.occ": 184
	-- "foptloader.occ": 186
	ldl     13	-- tag
	eqc     0
	cj      L12
	-- "foptloader.occ": 187
	-- "foptloader.occ": 190
	-- "foptloader.occ": 192
	ldl     12	-- loading
	cj      L14
	-- "foptloader.occ": 195
	ldl     11	-- last.address
	stl     0	-- load.address
	-- "foptloader.occ": 196
	ldl     0	-- load.address
	ldl     5	-- operand
	bsub    
	stl     11	-- last.address
	j       L13
L14:
	-- "foptloader.occ": 200
	-- "foptloader.occ": 201
	ldl     19	-- Buffer.address
	stl     0	-- load.address
	j       L13
L15:
L13:
	-- "foptloader.occ": 206
	-- "foptloader.occ": 207
	ldl     5	-- operand
	cj      L17
	-- "foptloader.occ": 208
	ldl     0	-- load.address
	ldl     18	-- Memory
	bsub    
	ldl     16	-- bootlink.in
	ldl     5	-- operand
	in      
	j       L16
L17:
	-- "foptloader.occ": 209
L16:
	-- "foptloader.occ": 213
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L18:
	-- "foptloader.occ": 214
	-- "foptloader.occ": 215
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L21
	-- "foptloader.occ": 217
	ldlp    1	-- command
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	-- "foptloader.occ": 218
	-- "foptloader.occ": 219
	ldl     5	-- operand
	cj      L23
	-- "foptloader.occ": 220
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
	-- "foptloader.occ": 221
L22:
	j       L20
L21:
	-- "foptloader.occ": 223
L20:
	ldlp    2	-- i
	ldc     L19 - L18
	lend    
L19:
	j       L11
L12:
	-- "foptloader.occ": 229
	ldl     13	-- tag
	eqc     2
	cj      L24
	-- "foptloader.occ": 235
	-- "foptloader.occ": 237
	ldl     5	-- operand
	eqc     1
	cj      L26
	-- "foptloader.occ": 244
	ldc     0
	stl     12	-- loading
	-- "foptloader.occ": 245
	ldc     0
	stl     4	-- links.to.load
	j       L25
L26:
	-- "foptloader.occ": 249
	ldl     5	-- operand
	eqc     2
	cj      L27
	-- "foptloader.occ": 250
	-- "foptloader.occ": 252
	ldc     1
	stl     0	-- depth
	-- "foptloader.occ": 253
L28:
	ldl     0	-- depth
	cj      L29
	-- "foptloader.occ": 255
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "foptloader.occ": 256
	-- "foptloader.occ": 257
	ldl     1	-- command
	eqc     130
	cj      L31
	-- "foptloader.occ": 258
	ldl     0	-- depth
	ldc     1
	bsub    
	stl     0	-- depth
	j       L30
L31:
	-- "foptloader.occ": 259
	ldl     1	-- command
	eqc     131
	cj      L32
	-- "foptloader.occ": 260
	ldl     0	-- depth
	ldc     1
	diff    
	stl     0	-- depth
	j       L30
L32:
	-- "foptloader.occ": 261
L30:
	-- "foptloader.occ": 263
	-- "foptloader.occ": 264
	ldl     0	-- depth
	cj      L34
	-- "foptloader.occ": 265
	ldlp    1	-- command
	ldl     10	-- output.link
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	j       L33
L34:
	-- "foptloader.occ": 266
L33:
	j       L28
L29:
	j       L25
L27:
	-- "foptloader.occ": 270
	ldl     5	-- operand
	eqc     4
	cj      L35
	-- "foptloader.occ": 272
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "foptloader.occ": 273
	ldl     11	-- last.address
	ldl     20	-- Next.address
	stnl    0
	j       L25
L35:
	-- "foptloader.occ": 276
	ldl     5	-- operand
	eqc     6
	cj      L36
	-- "foptloader.occ": 278
	ldl     22	-- Data.point
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	j       L25
L36:
	-- "foptloader.occ": 281
	ldl     5	-- operand
	eqc     11
	cj      L37
	-- "foptloader.occ": 283
	ldl     21	-- Entry.point
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	j       L25
L37:
	-- "foptloader.occ": 286
	ldl     5	-- operand
	eqc     8
	cj      L38
	-- "foptloader.occ": 288
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "foptloader.occ": 289
	ldl     11	-- last.address
	ldl     21	-- Entry.point
	stnl    0
	j       L25
L38:
	-- "foptloader.occ": 292
	ldl     5	-- operand
	eqc     10
	cj      L39
	-- "foptloader.occ": 294
	ldlp    11	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "foptloader.occ": 295
	ldl     11	-- last.address
	ldl     22	-- Data.point
	stnl    0
	j       L25
L39:
	-- "foptloader.occ": 298
	ldl     5	-- operand
	eqc     12
	cj      L40
	-- "foptloader.occ": 299
	-- "foptloader.occ": 300
	-- "foptloader.occ": 302
	ldc     0
	stl     9	-- Bootstrap.depth
	-- "foptloader.occ": 303
	ldc     0
	stl     8	-- Bootstrap.length
	-- "foptloader.occ": 304
	ldl     19	-- Buffer.address
	stl     7	-- load.address
	-- "foptloader.occ": 305
	ldc     1
	stl     6	-- More
	-- "foptloader.occ": 306
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "foptloader.occ": 307
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- More
	-- "foptloader.occ": 308
L41:
	ldl     6	-- More
	cj      L42
	-- "foptloader.occ": 310
	ldl     9	-- Bootstrap.depth
	ldc     1
	bsub    
	stl     9	-- Bootstrap.depth
	-- "foptloader.occ": 311
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L43:
	-- "foptloader.occ": 312
	-- "foptloader.occ": 313
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L46
	-- "foptloader.occ": 315
	ldlp    1	-- command
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	j       L45
L46:
	-- "foptloader.occ": 316
L45:
	ldlp    2	-- i
	ldc     L44 - L43
	lend    
L44:
	-- "foptloader.occ": 318
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "foptloader.occ": 319
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- More
	j       L41
L42:
	-- "foptloader.occ": 321
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "foptloader.occ": 323
	-- "foptloader.occ": 324
	ldl     9	-- Bootstrap.depth
	ldc     0
	gt      
	cj      L48
	-- "foptloader.occ": 327
	-- "foptloader.occ": 328
	ldl     5	-- operand
	cj      L50
	-- "foptloader.occ": 329
	ldl     7	-- load.address
	ldl     18	-- Memory
	bsub    
	ldl     16	-- bootlink.in
	ldl     5	-- operand
	in      
	j       L49
L50:
	-- "foptloader.occ": 330
L49:
	-- "foptloader.occ": 333
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L51:
	-- "foptloader.occ": 334
	-- "foptloader.occ": 335
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L54
	-- "foptloader.occ": 337
	ldlp    1	-- command
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	-- "foptloader.occ": 338
	-- "foptloader.occ": 339
	ldl     5	-- operand
	cj      L56
	-- "foptloader.occ": 340
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
	-- "foptloader.occ": 341
L55:
	j       L53
L54:
	-- "foptloader.occ": 343
L53:
	ldlp    2	-- i
	ldc     L52 - L51
	lend    
L52:
	j       L47
L48:
	-- "foptloader.occ": 345
	-- "foptloader.occ": 347
	ldc     1
	stl     6	-- More
	-- "foptloader.occ": 350
L58:
	ldl     6	-- More
	cj      L59
	-- "foptloader.occ": 352
	ldl     7	-- load.address
	ldl     18	-- Memory
	bsub    
	ldl     16	-- bootlink.in
	ldl     5	-- operand
	in      
	-- "foptloader.occ": 353
	ldl     7	-- load.address
	ldl     5	-- operand
	bsub    
	stl     7	-- load.address
	-- "foptloader.occ": 354
	ldl     8	-- Bootstrap.length
	ldl     5	-- operand
	bsub    
	stl     8	-- Bootstrap.length
	-- "foptloader.occ": 355
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "foptloader.occ": 358
	ldc     63
	ldl     1	-- command
	gt      
	stl     6	-- More
	-- "foptloader.occ": 359
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	j       L58
L59:
	-- "foptloader.occ": 361
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L60:
	-- "foptloader.occ": 362
	-- "foptloader.occ": 363
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L63
	-- "foptloader.occ": 365
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	outbyte 
	-- "foptloader.occ": 366
	-- "foptloader.occ": 367
	ldl     8	-- Bootstrap.length
	cj      L65
	-- "foptloader.occ": 368
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
	-- "foptloader.occ": 369
L64:
	j       L62
L63:
	-- "foptloader.occ": 371
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
	-- "foptloader.occ": 376
	ldl     5	-- operand
	eqc     13
	cj      L66
	-- "foptloader.occ": 378
	ldc     0
	stl     7	-- ii
	ldl     9	-- Bootstrap.depth
	stl     8	-- ii + 1
	ldl     8	-- ii + 1
	cj      L68
L67:
	-- "foptloader.occ": 381
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	-- "foptloader.occ": 382
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L69:
	-- "foptloader.occ": 383
	-- "foptloader.occ": 384
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L72
	-- "foptloader.occ": 385
	ldlp    1	-- command
	ldl     2	-- i
	ldl     15	-- links
	wsub    
	ldc     1
	out     
	j       L71
L72:
	-- "foptloader.occ": 386
L71:
	ldlp    2	-- i
	ldc     L70 - L69
	lend    
L70:
	ldlp    7	-- ii
	ldc     L68 - L67
	lend    
L68:
	-- "foptloader.occ": 388
	ldc     0
	stl     9	-- Bootstrap.depth
	j       L25
L66:
	-- "foptloader.occ": 392
	ldl     5	-- operand
	eqc     14
	cj      L73
	-- "foptloader.occ": 393
	-- "foptloader.occ": 395
	ldlp    2	-- Memory.size
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "foptloader.occ": 396
	-- "foptloader.occ": 396
	-- "foptloader.occ": 396
	-- "foptloader.occ": 396
	ldc     2048
	stl     0	-- Free.start
	-- "foptloader.occ": 396
	-- "foptloader.occ": 396
	ldl     2	-- Memory.size
	ldl     0	-- Free.start
	gt      
	cj      L75
	-- "foptloader.occ": 396
L76:
	ldl     2	-- Memory.size
	ldl     0	-- Free.start
	gt      
	cj      L77
	-- "foptloader.occ": 396
	-- "foptloader.occ": 396
	ldl     2	-- Memory.size
	ldl     0	-- Free.start
	diff    
	ldc     32767	-- #7FFF
	gt      
	cj      L79
	-- "foptloader.occ": 396
	ldc     255
	ldl     0	-- Free.start
	mint    	-- BtMemory
	bsub    
	ldc     32767	-- #7FFF
	rev     
	call    L3	-- Call ClearByteBuffer
	-- "foptloader.occ": 396
	ldl     0	-- Free.start
	ldc     32767	-- #7FFF
	bsub    
	stl     0	-- Free.start
	j       L78
L79:
	-- "foptloader.occ": 396
	-- "foptloader.occ": 396
	ldl     2	-- Memory.size
	ldl     0	-- Free.start
	diff    
	stl     3	-- $anon0
	-- "foptloader.occ": 396
	ldc     255
	ldl     0	-- Free.start
	mint    	-- BtMemory
	bsub    
	ldl     3	-- $anon0
	rev     
	call    L3	-- Call ClearByteBuffer
	-- "foptloader.occ": 396
	ldl     2	-- Memory.size
	stl     0	-- Free.start
	j       L78
L80:
L78:
	j       L76
L77:
	j       L74
L75:
	-- "foptloader.occ": 396
L74:
	j       L25
L73:
	-- "foptloader.occ": 400
	-- "foptloader.occ": 402
	ldc     1
	stl     12	-- loading
	-- "foptloader.occ": 403
	ldc     0
	stl     4	-- links.to.load
	j       L25
L81:
L25:
	j       L11
L24:
	-- "foptloader.occ": 408
	-- "foptloader.occ": 410
	ldl     5	-- operand
	stl     10	-- output.link
	-- "foptloader.occ": 411
	ldl     4	-- links.to.load
	ldc     1
	ldl     10	-- output.link
	shl     
	or      
	stl     4	-- links.to.load
	j       L11
L82:
L11:
	-- "foptloader.occ": 414
	ldlp    1	-- command
	ldl     16	-- bootlink.in
	ldc     1
	in      
	j       L9
L10:
	ajw     14
	ret     
	align
