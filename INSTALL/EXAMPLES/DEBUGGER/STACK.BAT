REM  PC dumb batch file to build debugger example program: stack.bah

REM  Note icc stack checking option /ks

icc /ta /g stack.c /o stack.tax /ks
ilink /ta stack.tax /f cnonconf.lnk /o stack.cah
icollect /t stack.cah /o stack.bah
