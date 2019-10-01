REM  PC dumb batch file to build debugger example program: abort.bah

icc /ta /g abort.c /o abort.tax
ilink /ta abort.tax /f cnonconf.lnk /o abort.cah
icollect /t abort.cah /o abort.bah
