-- occam 2 compiler Beta Vn 2.01.78 (19:24:22 Sep 15 1992) (SunOS-Sun4)
-- Compiling (T2,UNIVERSAL) "mloader.occ"

	j       $Floating.loader.memstart	-- jump to entrypoint
L0:	-- section label	-- PROC Get.encoded.value, lexlevel: 1, WS: 3, VS: 0
	-- "mloader.occ": 73
	ldc     0
	ldl     2	-- Address
	stnl    0
	-- "mloader.occ": 74
	ldc     1
	ldl     1	-- staticlink
	stnl    6	-- More
	-- "mloader.occ": 75
L1:
	ldl     1	-- staticlink
	ldnl    6	-- More
	cj      L2
	-- "mloader.occ": 77
	ldl     2	-- Address
	ldnl    0
	ldc     6
	shl     
	ldl     2	-- Address
	stnl    0
	-- "mloader.occ": 78
	ldl     1	-- staticlink
	ldnlp   1	-- command
	ldl     1	-- staticlink
	ldnl    24	-- bootlink.in
	ldc     1
	in      
	-- "mloader.occ": 79
	ldl     2	-- Address
	ldnl    0
	ldl     1	-- staticlink
	ldnl    1	-- command
	ldc     63
	and     
	bsub    
	ldl     2	-- Address
	stnl    0
	-- "mloader.occ": 80
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
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	ldc     1
	stl     0	-- Count
	-- "mloader.occ": 418
	ldl     0	-- Count
	stl     1	-- Index
	-- "mloader.occ": 418
	ldl     5	-- Value
	ldl     3	-- Buffer
	sb      
	-- "mloader.occ": 418
L4:
	ldl     4	-- $temp-1
	ldl     1	-- Index
	gt      
	cj      L5
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	ldl     0	-- Count
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	gt      
	cj      L7
	-- "mloader.occ": 418
	ldl     4	-- $temp-1
	ldl     1	-- Index
	diff    
	stl     0	-- Count
	j       L6
L7:
	-- "mloader.occ": 418
L6:
	-- "mloader.occ": 418
	ldl     3	-- Buffer
	ldl     1	-- Index
	ldl     3	-- Buffer
	bsub    
	ldl     0	-- Count
	move    
	-- "mloader.occ": 418
	ldl     1	-- Index
	ldl     0	-- Count
	bsub    
	stl     1	-- Index
	-- "mloader.occ": 418
	ldl     0	-- Count
	ldl     0	-- Count
	bsub    
	stl     0	-- Count
	j       L4
L5:
	ajw     2
	ret     
L8:	-- section label	-- PROC Floating.loader.memstart, lexlevel: 0, WS: 30, VS: 0
$Floating.loader.memstart:
	global $Floating.loader.memstart
	descriptor $Floating.loader.memstart "Floating.loader.memstart" occam 30 0 "PROC Floating.loader.memstart([4]CHAN OF ANY links,
CHAN OF ANY bootlink.in,CHAN OF ANY bootlink.out,[4]BYTE Memory,
VAL INT Buffer.address,VAL INT Next.boot.loader,[3]INT Data.to.return,
INT Entry.point)
  SEQ
    links!
    bootlink.in?
:"
	ajw     -22
	-- "mloader.occ": 10
	-- "mloader.occ": 11
	-- "mloader.occ": 12
	-- "mloader.occ": 13
	-- "mloader.occ": 14
	-- "mloader.occ": 15
	-- "mloader.occ": 16
	-- "mloader.occ": 17
	-- "mloader.occ": 18
	-- "mloader.occ": 19
	-- "mloader.occ": 20
	-- "mloader.occ": 21
	-- "mloader.occ": 23
	-- "mloader.occ": 24
	-- "mloader.occ": 25
	-- "mloader.occ": 26
	-- "mloader.occ": 27
	-- "mloader.occ": 28
	-- "mloader.occ": 29
	-- "mloader.occ": 30
	-- "mloader.occ": 31
	-- "mloader.occ": 32
	-- "mloader.occ": 34
	-- "mloader.occ": 35
	-- "mloader.occ": 36
	-- "mloader.occ": 38
	-- "mloader.occ": 39
	-- "mloader.occ": 41
	-- "mloader.occ": 42
	-- "mloader.occ": 44
	-- "mloader.occ": 45
	-- "mloader.occ": 47
	-- "mloader.occ": 48
	-- "mloader.occ": 50
	-- "mloader.occ": 51
	-- "mloader.occ": 53
	-- "mloader.occ": 54
	-- "mloader.occ": 56
	-- "mloader.occ": 57
	-- "mloader.occ": 59
	-- "mloader.occ": 60
	-- "mloader.occ": 61
	-- "mloader.occ": 65
	ldc     0
	stl     1	-- command
	-- "mloader.occ": 66
	-- "mloader.occ": 67
	-- "mloader.occ": 68
	ldc     0
	stl     6	-- More
	ldc     0
	stl     15	-- loading
	ldc     0
	stl     20	-- Loaded.ternarY
	-- "mloader.occ": 180
	ldl     29	-- Data.to.return
	ldnlp   1
	stl     19	-- Next.address
	-- "mloader.occ": 181
	ldl     29	-- Data.to.return
	stl     18	-- Data.point
	-- "mloader.occ": 182
	ldl     29	-- Data.to.return
	ldnlp   2
	stl     17	-- Invocation.stack
	-- "mloader.occ": 184
	ldc     0
	stl     20	-- Loaded.ternarY
	-- "mloader.occ": 185
	ldlp    1	-- command
	ldl     24	-- bootlink.in
	ldc     1
	in      
	-- "mloader.occ": 187
L9:
	ldc     133
	ldl     1	-- command
	diff    
	cj      L10
	-- "mloader.occ": 191
	ldl     1	-- command
	ldc     6
	shr     
	stl     21	-- tag
	-- "mloader.occ": 192
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "mloader.occ": 194
	-- "mloader.occ": 196
	ldl     21	-- tag
	eqc     0
	cj      L12
	-- "mloader.occ": 197
	-- "mloader.occ": 200
	-- "mloader.occ": 202
	ldl     15	-- loading
	cj      L14
	-- "mloader.occ": 205
	-- "mloader.occ": 206
	ldl     20	-- Loaded.ternarY
	eqc     0
	cj      L16
	-- "mloader.occ": 208
	ldc     1
	stl     20	-- Loaded.ternarY
	-- "mloader.occ": 209
	ldl     28	-- Next.boot.loader
	stl     13	-- last.address
	j       L15
L16:
	-- "mloader.occ": 210
L15:
	-- "mloader.occ": 212
	ldl     13	-- last.address
	stl     0	-- load.address
	-- "mloader.occ": 213
	ldl     0	-- load.address
	ldl     5	-- operand
	bsub    
	stl     13	-- last.address
	j       L13
L14:
	-- "mloader.occ": 217
	-- "mloader.occ": 218
	ldl     27	-- Buffer.address
	stl     0	-- load.address
	j       L13
L17:
L13:
	-- "mloader.occ": 223
	-- "mloader.occ": 224
	ldl     5	-- operand
	cj      L19
	-- "mloader.occ": 225
	ldl     0	-- load.address
	ldl     26	-- Memory
	bsub    
	ldl     24	-- bootlink.in
	ldl     5	-- operand
	in      
	j       L18
L19:
	-- "mloader.occ": 226
L18:
	-- "mloader.occ": 230
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L20:
	-- "mloader.occ": 231
	-- "mloader.occ": 232
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L23
	-- "mloader.occ": 234
	ldlp    1	-- command
	ldl     2	-- i
	ldl     23	-- links
	wsub    
	ldc     1
	out     
	-- "mloader.occ": 235
	-- "mloader.occ": 236
	ldl     5	-- operand
	cj      L25
	-- "mloader.occ": 237
	ldl     0	-- load.address
	ldl     26	-- Memory
	bsub    
	ldl     2	-- i
	ldl     23	-- links
	wsub    
	ldl     5	-- operand
	out     
	j       L24
L25:
	-- "mloader.occ": 238
L24:
	j       L22
L23:
	-- "mloader.occ": 240
L22:
	ldlp    2	-- i
	ldc     L21 - L20
	lend    
L21:
	j       L11
L12:
	-- "mloader.occ": 246
	ldl     21	-- tag
	eqc     2
	cj      L26
	-- "mloader.occ": 252
	-- "mloader.occ": 254
	ldl     5	-- operand
	eqc     1
	cj      L28
	-- "mloader.occ": 261
	ldc     0
	stl     15	-- loading
	-- "mloader.occ": 262
	ldc     0
	stl     4	-- links.to.load
	j       L27
L28:
	-- "mloader.occ": 266
	ldl     5	-- operand
	eqc     2
	cj      L29
	-- "mloader.occ": 267
	-- "mloader.occ": 269
	ldc     1
	stl     0	-- depth
	-- "mloader.occ": 270
L30:
	ldl     0	-- depth
	cj      L31
	-- "mloader.occ": 272
	ldlp    1	-- command
	ldl     24	-- bootlink.in
	ldc     1
	in      
	-- "mloader.occ": 273
	-- "mloader.occ": 274
	ldl     1	-- command
	eqc     130
	cj      L33
	-- "mloader.occ": 275
	ldc     1
	ldl     0	-- depth
	bsub    
	stl     0	-- depth
	j       L32
L33:
	-- "mloader.occ": 276
	ldl     1	-- command
	eqc     131
	cj      L34
	-- "mloader.occ": 277
	ldl     0	-- depth
	ldc     1
	diff    
	stl     0	-- depth
	j       L32
L34:
	-- "mloader.occ": 278
L32:
	-- "mloader.occ": 280
	-- "mloader.occ": 281
	ldl     0	-- depth
	cj      L36
	-- "mloader.occ": 282
	ldlp    1	-- command
	ldl     12	-- output.link
	ldl     23	-- links
	wsub    
	ldc     1
	out     
	j       L35
L36:
	-- "mloader.occ": 283
L35:
	j       L30
L31:
	j       L27
L29:
	-- "mloader.occ": 287
	ldl     5	-- operand
	eqc     4
	cj      L37
	-- "mloader.occ": 289
	ldlp    13	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "mloader.occ": 290
	ldl     13	-- last.address
	ldl     19	-- Next.address
	stnl    0
	j       L27
L37:
	-- "mloader.occ": 293
	ldl     5	-- operand
	eqc     6
	cj      L38
	-- "mloader.occ": 295
	ldlp    1	-- command
	ldl     24	-- bootlink.in
	ldc     1
	in      
	-- "mloader.occ": 296
	-- "mloader.occ": 297
	ldl     1	-- command
	eqc     0
	cj      L40
	-- "mloader.occ": 298
	ldl     18	-- Data.point
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	j       L39
L40:
	-- "mloader.occ": 299
	-- "mloader.occ": 300
	ldl     17	-- Invocation.stack
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	j       L39
L41:
L39:
	j       L27
L38:
	-- "mloader.occ": 303
	ldl     5	-- operand
	eqc     11
	cj      L42
	-- "mloader.occ": 305
	ldl     30	-- Entry.point
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	j       L27
L42:
	-- "mloader.occ": 308
	ldl     5	-- operand
	eqc     8
	cj      L43
	-- "mloader.occ": 310
	ldlp    13	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "mloader.occ": 311
	ldl     13	-- last.address
	ldl     30	-- Entry.point
	stnl    0
	j       L27
L43:
	-- "mloader.occ": 314
	ldl     5	-- operand
	eqc     10
	cj      L44
	-- "mloader.occ": 316
	ldlp    13	-- last.address
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "mloader.occ": 317
	ldl     13	-- last.address
	ldl     18	-- Data.point
	stnl    0
	j       L27
L44:
	-- "mloader.occ": 320
	ldl     5	-- operand
	eqc     12
	cj      L45
	-- "mloader.occ": 321
	-- "mloader.occ": 322
	-- "mloader.occ": 324
	ldc     0
	stl     9	-- Bootstrap.depth
	-- "mloader.occ": 325
	ldc     0
	stl     8	-- Bootstrap.length
	-- "mloader.occ": 326
	ldl     27	-- Buffer.address
	stl     7	-- load.address
	-- "mloader.occ": 327
	ldc     1
	stl     6	-- More
	-- "mloader.occ": 328
	ldlp    1	-- command
	ldl     24	-- bootlink.in
	ldc     1
	in      
	-- "mloader.occ": 329
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- More
	-- "mloader.occ": 330
L46:
	ldl     6	-- More
	cj      L47
	-- "mloader.occ": 332
	ldc     1
	ldl     9	-- Bootstrap.depth
	bsub    
	stl     9	-- Bootstrap.depth
	-- "mloader.occ": 333
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L48:
	-- "mloader.occ": 334
	-- "mloader.occ": 335
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L51
	-- "mloader.occ": 337
	ldlp    1	-- command
	ldl     2	-- i
	ldl     23	-- links
	wsub    
	ldc     1
	out     
	j       L50
L51:
	-- "mloader.occ": 338
L50:
	ldlp    2	-- i
	ldc     L49 - L48
	lend    
L49:
	-- "mloader.occ": 340
	ldlp    1	-- command
	ldl     24	-- bootlink.in
	ldc     1
	in      
	-- "mloader.occ": 341
	ldc     63
	ldl     1	-- command
	gt      
	eqc     0
	stl     6	-- More
	j       L46
L47:
	-- "mloader.occ": 343
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	-- "mloader.occ": 345
	-- "mloader.occ": 346
	ldl     9	-- Bootstrap.depth
	ldc     0
	gt      
	cj      L53
	-- "mloader.occ": 349
	-- "mloader.occ": 350
	ldl     5	-- operand
	cj      L55
	-- "mloader.occ": 351
	ldl     7	-- load.address
	ldl     26	-- Memory
	bsub    
	ldl     24	-- bootlink.in
	ldl     5	-- operand
	in      
	j       L54
L55:
	-- "mloader.occ": 352
L54:
	-- "mloader.occ": 355
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L56:
	-- "mloader.occ": 356
	-- "mloader.occ": 357
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L59
	-- "mloader.occ": 359
	ldlp    1	-- command
	ldl     2	-- i
	ldl     23	-- links
	wsub    
	ldc     1
	out     
	-- "mloader.occ": 360
	-- "mloader.occ": 361
	ldl     5	-- operand
	cj      L61
	-- "mloader.occ": 362
	ldl     7	-- load.address
	ldl     26	-- Memory
	bsub    
	ldl     2	-- i
	ldl     23	-- links
	wsub    
	ldl     5	-- operand
	out     
	j       L60
L61:
	-- "mloader.occ": 363
L60:
	j       L58
L59:
	-- "mloader.occ": 365
L58:
	ldlp    2	-- i
	ldc     L57 - L56
	lend    
L57:
	j       L52
L53:
	-- "mloader.occ": 367
	-- "mloader.occ": 369
	ldc     1
	stl     6	-- More
	-- "mloader.occ": 372
L63:
	ldl     6	-- More
	cj      L64
	-- "mloader.occ": 374
	ldl     7	-- load.address
	ldl     26	-- Memory
	bsub    
	ldl     24	-- bootlink.in
	ldl     5	-- operand
	in      
	-- "mloader.occ": 375
	ldl     7	-- load.address
	ldl     5	-- operand
	bsub    
	stl     7	-- load.address
	-- "mloader.occ": 376
	ldl     8	-- Bootstrap.length
	ldl     5	-- operand
	bsub    
	stl     8	-- Bootstrap.length
	-- "mloader.occ": 377
	ldlp    1	-- command
	ldl     24	-- bootlink.in
	ldc     1
	in      
	-- "mloader.occ": 380
	ldc     63
	ldl     1	-- command
	gt      
	stl     6	-- More
	-- "mloader.occ": 381
	ldl     1	-- command
	ldc     63
	and     
	stl     5	-- operand
	j       L63
L64:
	-- "mloader.occ": 383
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L65:
	-- "mloader.occ": 384
	-- "mloader.occ": 385
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L68
	-- "mloader.occ": 387
	ldl     2	-- i
	ldl     23	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	outbyte 
	-- "mloader.occ": 388
	-- "mloader.occ": 389
	ldl     8	-- Bootstrap.length
	cj      L70
	-- "mloader.occ": 390
	ldl     27	-- Buffer.address
	ldl     26	-- Memory
	bsub    
	ldl     2	-- i
	ldl     23	-- links
	wsub    
	ldl     8	-- Bootstrap.length
	out     
	j       L69
L70:
	-- "mloader.occ": 391
L69:
	j       L67
L68:
	-- "mloader.occ": 393
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
	-- "mloader.occ": 398
	ldl     5	-- operand
	eqc     13
	cj      L71
	-- "mloader.occ": 400
	ldc     0
	stl     7	-- ii
	ldl     9	-- Bootstrap.depth
	stl     8	-- ii + 1
	ldl     8	-- ii + 1
	cj      L73
L72:
	-- "mloader.occ": 403
	ldlp    1	-- command
	ldl     24	-- bootlink.in
	ldc     1
	in      
	-- "mloader.occ": 404
	ldc     0
	stl     2	-- i
	ldc     4
	stl     3	-- i + 1
L74:
	-- "mloader.occ": 405
	-- "mloader.occ": 406
	ldl     4	-- links.to.load
	ldc     1
	ldl     2	-- i
	shl     
	and     
	cj      L77
	-- "mloader.occ": 407
	ldlp    1	-- command
	ldl     2	-- i
	ldl     23	-- links
	wsub    
	ldc     1
	out     
	j       L76
L77:
	-- "mloader.occ": 408
L76:
	ldlp    2	-- i
	ldc     L75 - L74
	lend    
L75:
	ldlp    7	-- ii
	ldc     L73 - L72
	lend    
L73:
	-- "mloader.occ": 410
	ldc     0
	stl     9	-- Bootstrap.depth
	j       L27
L71:
	-- "mloader.occ": 414
	ldl     5	-- operand
	eqc     14
	cj      L78
	-- "mloader.occ": 415
	-- "mloader.occ": 417
	ldlp    16	-- Memory.size
	ldlp    0	-- staticlink
	call    L0	-- Call Get.encoded.value
	-- "mloader.occ": 418
	ldl     16	-- Memory.size
	xdble   
	stl     7	-- Memory.size
	stl     8	-- Memory.size + 1
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	ldl     26	-- Memory
	stl     14	-- Free.start.int
	-- "mloader.occ": 418
	ldl     14	-- Free.start.int
	mint    
	xor     
	stl     14	-- Free.start.int
	-- "mloader.occ": 418
	ldl     14	-- Free.start.int
	xdble   
	stl     2	-- Free.start
	stl     3	-- Free.start + 1
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	ldl     8	-- Memory.size + 1
	ldl     3	-- Free.start + 1
	gt      
	eqc     0
	cj      L81
	ldl     8	-- Memory.size + 1
	ldl     3	-- Free.start + 1
	diff    
	eqc     0
	cj      L82
	ldl     7	-- Memory.size
	mint    
	xor     
	ldl     2	-- Free.start
	mint    
	xor     
	gt      
	eqc     0
L81:
	eqc     0
L82:
	cj      L80
	-- "mloader.occ": 418
L83:
	ldl     8	-- Memory.size + 1
	ldl     3	-- Free.start + 1
	gt      
	eqc     0
	cj      L85
	ldl     8	-- Memory.size + 1
	ldl     3	-- Free.start + 1
	diff    
	eqc     0
	cj      L86
	ldl     7	-- Memory.size
	mint    
	xor     
	ldl     2	-- Free.start
	mint    
	xor     
	gt      
	eqc     0
L85:
	eqc     0
L86:
	cj      L84
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	ldc     0
	ldl     7	-- Memory.size
	ldl     2	-- Free.start
	ldiff   
	stl     10	-- $temp28
	ldl     8	-- Memory.size + 1
	ldl     3	-- Free.start + 1
	ldiff   
	stl     11	-- $temp28 + 1
	ldl     11	-- $temp28 + 1
	ldc     0
	gt      
	eqc     0
	cj      L89
	ldl     11	-- $temp28 + 1
	eqc     0
	cj      L90
	ldl     10	-- $temp28
	mint    
	xor     
	ldc     -1
	gt      
	eqc     0
L89:
	eqc     0
L90:
	cj      L88
	-- "mloader.occ": 418
	ldl     2	-- Free.start
	mint    	-- BtMemory
	bsub    
	ldc     255
	rev     
	ldc     32767	-- #7FFF
	rev     
	call    L3	-- Call ClearByteBuffer
	-- "mloader.occ": 418
	ldc     0
	ldl     2	-- Free.start
	ldc     32767	-- #7FFF
	lsum    
	stl     2	-- Free.start
	ldl     3	-- Free.start + 1
	ldc     0
	lsum    
	stl     3	-- Free.start + 1
	j       L87
L88:
	-- "mloader.occ": 418
	-- "mloader.occ": 418
	ldc     0
	ldl     7	-- Memory.size
	ldl     2	-- Free.start
	ldiff   
	stl     10	-- $temp28
	ldl     8	-- Memory.size + 1
	ldl     3	-- Free.start + 1
	ldiff   
	stl     11	-- $temp28 + 1
	ldl     10	-- $temp28
	stl     0	-- $anon0
	-- "mloader.occ": 418
	ldl     2	-- Free.start
	mint    	-- BtMemory
	bsub    
	ldc     255
	rev     
	ldl     0	-- $anon0
	rev     
	call    L3	-- Call ClearByteBuffer
	-- "mloader.occ": 418
	ldl     7	-- Memory.size
	stl     2	-- Free.start
	ldl     8	-- Memory.size + 1
	stl     3	-- Free.start + 1
	j       L87
L91:
L87:
	j       L83
L84:
	j       L79
L80:
	-- "mloader.occ": 418
L79:
	j       L27
L78:
	-- "mloader.occ": 422
	-- "mloader.occ": 424
	ldc     1
	stl     15	-- loading
	-- "mloader.occ": 425
	ldc     0
	stl     4	-- links.to.load
	j       L27
L92:
L27:
	j       L11
L26:
	-- "mloader.occ": 430
	-- "mloader.occ": 432
	ldl     5	-- operand
	stl     12	-- output.link
	-- "mloader.occ": 433
	ldl     4	-- links.to.load
	ldc     1
	ldl     12	-- output.link
	shl     
	or      
	stl     4	-- links.to.load
	j       L11
L93:
L11:
	-- "mloader.occ": 436
	ldlp    1	-- command
	ldl     24	-- bootlink.in
	ldc     1
	in      
	j       L9
L10:
	-- "mloader.occ": 439
	-- "mloader.occ": 442
	ldl     26	-- Memory
	-- "mloader.occ": 443
	stl     0	-- Load.start
	-- "mloader.occ": 445
	ldl     19	-- Next.address
	ldnl    0
	ldl     0	-- Load.start
	bsub    
	ldl     19	-- Next.address
	stnl    0
	-- "mloader.occ": 446
	ldl     30	-- Entry.point
	ldnl    0
	ldl     0	-- Load.start
	bsub    
	ldl     30	-- Entry.point
	stnl    0
	-- "mloader.occ": 447
	ldl     18	-- Data.point
	ldnl    0
	ldl     0	-- Load.start
	bsub    
	ldl     18	-- Data.point
	stnl    0
	-- "mloader.occ": 448
	ldl     17	-- Invocation.stack
	ldnl    0
	ldl     0	-- Load.start
	bsub    
	ldl     17	-- Invocation.stack
	stnl    0
	ajw     22
	ret     
	align
