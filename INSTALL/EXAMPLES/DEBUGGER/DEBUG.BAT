REM  PC dumb batch file to build debugger example program: debug.bah

icc /ta /g debug.c /o debug.tax
ilink /ta debug.tax /f cnonconf.lnk /o debug.cah
icollect /t debug.cah /o debug.bah
