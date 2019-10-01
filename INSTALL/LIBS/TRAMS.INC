/*
-- ----------------------------------------------------------------------------
--
--     SCCS ID : @(#)  trams.inc 1.4 92/07/02 16:21:56
--
--     Object Name : trams.inc
--     Revision    : 1.4
--
--     (c) Copyright INMOS Limited.
--     All Rights Reserved.
--
--     DESCRIPTION
--         Include file of INMOS TRAnsputer Module definitions.
--
--     NOTES
--         None.
--
--     HISTORY
--         1-Jun-1990    Antony King    Created file.
--
-- ----------------------------------------------------------------------------
*/

/*{{{  Standard transputer TRAMs */
define t800 (memory =  32k) b401;
define t414 (memory =  32k) b401_t414;
define t425 (memory =  32k) b401_t425;
define t800 (memory =  32k) b401_t800;
define t212 (memory =   8k) b402;
define t800 (memory =   1m) b403;
define t414 (memory =   1m) b403_t414;
define t800 (memory =   1m) b403_t800;
define t800 (memory =   2m) b404;
define t800 (memory =   8m) b405;
define t801 (memory = 160k) b410;
define t800 (memory =   1m) b411;
define t425 (memory =   1m) b411_t425;
define t800 (memory =   1m) b411_t800;
define t222 (memory =  64k) b416;
define t800 (memory =   4m) b417;
define t800 (memory =   4m) b426;
define t800 (memory =   8m) b427;
define t801 (memory =   2m) b428;
define t805 (memory =  16m) b433;

define T800 (memory =  32K) B401;
define T414 (memory =  32K) B401_T414;
define T425 (memory =  32K) B401_T425;
define T800 (memory =  32K) B401_T800;
define T212 (memory =   8K) B402;
define T800 (memory =   1M) B403;
define T414 (memory =   1M) B403_T414;
define T800 (memory =   1M) B403_T800;
define T800 (memory =   2M) B404;
define T800 (memory =   8M) B405;
define T801 (memory = 160K) B410;
define T800 (memory =   1M) B411;
define T425 (memory =   1M) B411_T425;
define T800 (memory =   1M) B411_T800;
define T222 (memory =  64K) B416;
define T800 (memory =   4M) B417;
define T800 (memory =   4M) B426;
define T800 (memory =   8M) B427;
define T801 (memory =   2M) B428;
define T805 (memory =  16M) B433;
/*}}}*/

/*{{{  Application specific TRAMs */
define t222 (memory = 64k - 4) b407;
define t800 (memory =  1m) b408;
define t222 (memory =  4k) b409;
define t222 (memory =  4k) b418;
define t800 (memory =  2m) b419;
define t800 (memory =  1m) b420;
define t222 (memory = 48k) b421;
define t222 (memory = 64k) b422;
define t800 (memory =  1m) b429;
define t222 (memory = 32k) b430;
define t222 (memory = 64k - 4) b431;
define t805 (memory =  1m) b437;

define T222 (memory = 64K - 4) B407;
define T800 (memory =  1M) B408;
define T222 (memory =  4K) B409;
define T222 (memory =  4K) B418;
define T800 (memory =  2M) B419;
define T800 (memory =  1M) B420;
define T222 (memory = 48K) B421;
define T222 (memory = 64K) B422;
define T800 (memory =  1M) B429;
define T222 (memory = 32K) B430;
define T222 (memory = 64K - 4) B431;
define T805 (memory =  1M) B437;
/*}}}*/
